/*
 * =====================================================================================
 *
 *       Filename:  clear.cpp
 *
 *    Description:  clear cache.
 *
 *        Version:  1.0
 *        Created:  03/29/2007 03:00:32 PM CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <signal.h>

const int REMAIN = 128 * 1024 * 1024;	// 128M
key_t g_key = 0xd71140fc;
int g_sem_id = -1;

#define long int64_t

long get_value(const char *buf)
{
	const char *ptr = NULL;
	char *endptr = NULL;
	long value = -1;

	ptr = buf + strspn(buf, " \t");
	value = strtol(buf, &endptr, 0);
	if (endptr == ptr || (*endptr != ' ' && *endptr != '\t'))
		return -1;

	ptr = endptr + strspn(endptr, " \t");

	if (*ptr == 'k' || *ptr == 'K')
		value *= 1024;
	else if (*ptr == 'm' || *ptr == 'M')
		value *= 1024 * 1024;
	else if (*ptr == 'g' || *ptr == 'G')
		value *= 1024 * 1024 * 1024;
	else if (*ptr == 'B')
		ptr--;
	else
		return -1;

	ptr++;
	if (*ptr != 'B')
		return -1;

	ptr++;
	ptr += strspn(ptr, " \t\n");
	if (*ptr)
		return -1;

	return value;
}

long get_free_mem()
{
	__label__ failure;
	FILE *fp = NULL;
	char buf[1024] = { 0 };
	long mem_total = -1;
	long mem_free = -1;
	long mem_cache = -1;

	fp = fopen("/proc/meminfo", "r");
	if (!fp) {
		fprintf(stderr, "open meminfo file failed. [%d]: %m", errno);
		return -1;
	}

	while (fgets(buf, sizeof(buf), fp)) {
		if (!strncasecmp(buf, "MemTotal:", strlen("MemTotal:"))) {
			mem_total = get_value(buf + strlen("MemTotal:"));

			if (mem_total < 0)
				goto failure;

		} else if (!strncasecmp(buf, "MemFree:", strlen("MemFree:"))) {
			mem_free = get_value(buf + strlen("MemFree:"));

			if (mem_free < 0)
				goto failure;

		} else if (!strncasecmp(buf, "Cached:", strlen("Cached:"))) {
			mem_cache = get_value(buf + strlen("Cached:"));

			if (mem_free < 0)
				goto failure;

		} else {
			continue;
		}

		// ok
		if (mem_total > 0 && mem_free > 0 && mem_cache > 0)
			break;
	}

	fclose(fp);

	if (mem_total <= 0 || mem_free < 0 || mem_cache < 0)
		return -1;
	else if (mem_free + mem_cache >= mem_total)
		return -1;
	else
		return mem_free + mem_cache;

failure:
	if (fp)
		fclose(fp);
	return -1;
}

void help(const char *prog)
{
	fprintf(stdout, "%s:\n", prog);
	fprintf(stdout, "\t-m   最大清理内存数(MB).\n");
	fprintf(stdout, "\t-r   保留系统内存数(MB).\n");
	fprintf(stdout, "\t-s   显示进度.\n");
	fprintf(stdout, "\t-v   显示版本号.\n\n");
	exit(0);
}

void version(const char *prog)
{
	fprintf(stdout, "%s:\n", prog);
	fprintf(stdout, "   Version: %s\n", VERSION);
	fprintf(stdout, "Build Date: %s %s\n\n", __DATE__, __TIME__);
	exit(0);
}

int sem_creat()
{
	g_sem_id = semget(g_key, 1, 0666 | IPC_CREAT);
	if (g_sem_id < 0) {
		fprintf(stderr, "create sem failed. [%d]: %m", errno);
		return -1;
	}

	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = IPC_NOWAIT;

	int ret;
	while ((ret = semop(g_sem_id, &sops, 1)) < 0 && errno == EINTR)
		;

	if (ret < 0) {
		fprintf(stderr, "init sem failed. [%d]: %m", errno);
		return -1;
	}

	return 0;
}

int lock()
{
	g_sem_id = semget(g_key, 1, 0);
	if (g_sem_id < 0 && errno == ENOENT) {
		if (sem_creat() < 0)
			return -1;
	} else if (g_sem_id < 0) {
		fprintf(stderr, "semget failed (key=%x). [%d]: %m", g_key, errno);
		return -1;
	}

	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = IPC_NOWAIT | SEM_UNDO;

	int ret = semop(g_sem_id, &sops, 1);
	if (ret < 0 && errno == EAGAIN) {
		fprintf(stderr, "programis already in running.\n");
		return -1;
	} else if (ret < 0) {
		fprintf(stderr, "semop falied, %m, program is already in running.\n");
		return -1;
	}

	return 0;
}


int main(int argc, char *argv[])
{
	__label__ failure;

	int arg;
	long max = -1;
	long remain = REMAIN; 
	int verborse = 0;

	if (lock() < 0)
		return -1;

//	key_t key = ftok("clear.cpp", 2007);
//	printf("%x\n", key);


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while ((arg = getopt(argc, argv, "m:r:sv")) != -1) {
		switch(arg) {
			case 'm':
				max = atol(optarg) * 1024 * 1024;
				break;
			case 'r':
				remain = atol(optarg) * 1024 * 1024;
				break;
			case 's':
				verborse = 1;
				break;
			case 'v':
				version(argv[0]);
				break;
			default:
				help(argv[0]);
				break;
		}
	}

	const int step = 128 * 1024 * 1024;	// 128M
	long size = get_free_mem();
	int page_sz = getpagesize();

	size -= remain;

	if (size <= 0 || page_sz <= 0) {
		fprintf(stderr, "get_free_mem %ld or getpagesize %d failed.\n", size, page_sz);
		return -1;
	}

	if (max > 0 && size > max)
		size = max;

	fprintf(stdout, "free memory = %ld MB\n", size/1024/1024);

	long times = size / step;

	for (long i = 0; i < times; i++) {
		char *ptr = (char *)malloc(step);
		if (!ptr) {
			fprintf(stderr, "malloc failed, [%d]: %m\n", errno);
			goto failure;
		}

		int pages = step / page_sz;
		for (int j = 0; j < pages; j++) {
			ptr[j * page_sz] = '\0';
		}

		if (verborse)
			fprintf(stdout, "clear: %ld MB\n", 128 * (i + 1));
		else
			fprintf(stdout, ".");
	}

	fprintf(stdout, "\n");
    fprintf(stdout,"Free %ld MB succeed Ctrl C to terminated\n",size/1024/1024);
    sleep(100000);
	return 0;

failure:
	return -1;
}


