#<center>使用 Valgrind 绘制程序调用栈图 打印内存使用快照</center>

##一 Valgrind工具集

Valgrind通常用来成分析程序性能及程序中的内存泄露错误，Valgrind包含下列工具：

    1、memcheck：检查程序中的内存问题，如泄漏、越界、非法指针等。

    2、callgrind：检测程序代码的运行时间和调用过程，以及分析程序性能。

    3、cachegrind：分析CPU的cache命中率、丢失率，用于进行代码优化。

    4、helgrind：用于检查多线程程序的竞态条件。

    5、massif：堆栈分析器，指示程序中使用了多少堆内存等信息。

    6、lackey：

    7、nulgrind：

这几个工具的使用是通过命令：valgrand --tool=name 程序名来分别调用的，当不指定tool参数时默认是 --tool=memcheck



##二 打印程序调用栈

如上面介绍的，我们可以使用callgrind生成函数调用关系，发现程序卡在了那里。

以mysql为例。

首先，安装 Valgrind

http://valgrind.org/downloads/

然后使用Valgrind启动程序，以mysqld为例

 (valgrind  --tool=callgrind  libexec/mysqld --defaults-file=etc/my.cnf   -uroot &)
然后，等待程序执行完成，或者手动退出。

在目录下会生成生成"callgrind.out.XXX"。这是分析文件，可以直接利用：callgrind_annotate callgrind.out.XXX 打印结果。



##三 绘制程序调用栈图

首先，确认系统安装了 python

然后，下载gprof2dot  https://pypi.org/project/gprof2dot/

接着，安装 graphviz，可以使用 yum 直接安装，或者使用源码安装 http://www.graphviz.org/

最后，执行绘图指令，出图。

python gprof2dot.py -f callgrind callgrind.out.25996 |dot -Tpdf -o report.pdf