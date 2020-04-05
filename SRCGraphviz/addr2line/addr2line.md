#<center>addr2line</center>

addr2line工具是一个可以将指令的地址和可执行映像转换为文件名、函数名和源代码行数的工具。这在内核执行过程中出现崩溃时，可用于快速定位出出错的位置，进而找出代码的bug。

使用
#1.自己查找一个地址，然后来定位

```cpp
#include<stdio.h>
int divide(int x, int y)
{
    return x/y;
}

int main()
{
    printf("hello world\n");
    int x = 3;
    int y = 0;
    int div = divide(x, y); 
    printf("%d / %d = %d\n", x, y, div);
    return 0;
}
```

##编译：
> g++ -Wl,-Map=test.map -g test.cpp -o test

##查找divide函数的地址
> grep divide test.map

```cpp
0x00000000004005e7                divide(int, int)
```

##使用addr2line定位
> addr2line 0x00000000004005e7 -e test -f -C -s

```cpp
divide(int, int)
test.cpp:3
```

如果不加-C选项，输出如下（是未经过demangle的）

```cpp
_Z6divideii
test.cpp:3
```

#2.查找系统信息，然后定位代码
dmesg

```cpp
[150100.451504] traps: test[7593] trap divide error ip:4005f5 sp:7ffeebd4ba70 error:0 in test[400000+1000]
```
这条信息里，ip（指令指针寄存器）字段后面的数字就是test程序出错时程序执行的位置。使用addr2line就可以将4005f5定位到代码的位置：
addr2line 4005f5 -e test -f -s -C

```cpp
divide(int, int)
test.cpp:4
```
第4行也就是除以0的位置:return x/y。

#原理
addr2line如何找到的这一行呢。在可执行程序中都包含有调试信息（所以编译的时候需要加-g选项），其中很重要的一份数据就是程序源程序的行号和编译后的机器代码之间的对应关系Line Number Table。Line Number Table存储在可执行程序的.debug_line域。
使用如下命令
readelf -w test | grep "advance Address"

```cpp
  [0x000000ca]  Special opcode 7: advance Address by 0 to 0x4005e7 and Line by 2 to 3
  [0x000000cb]  Special opcode 146: advance Address by 10 to 0x4005f1 and Line by 1 to 4
  [0x000000cc]  Special opcode 104: advance Address by 7 to 0x4005f8 and Line by 1 to 5
  [0x000000cd]  Special opcode 36: advance Address by 2 to 0x4005fa and Line by 3 to 8
  [0x000000ce]  Special opcode 118: advance Address by 8 to 0x400602 and Line by 1 to 9
  [0x000000cf]  Special opcode 146: advance Address by 10 to 0x40060c and Line by 1 to 10
  [0x000000d0]  Special opcode 104: advance Address by 7 to 0x400613 and Line by 1 to 11
  [0x000000d1]  Special opcode 104: advance Address by 7 to 0x40061a and Line by 1 to 12
  [0x000000d3]  Special opcode 20: advance Address by 1 to 0x40062c and Line by 1 to 13
  [0x000000d5]  Special opcode 132: advance Address by 9 to 0x400646 and Line by 1 to 14
  [0x000000d6]  Special opcode 76: advance Address by 5 to 0x40064b and Line by 1 to 15
```
观察第二行和第三行，源代码的第4行的指令起始地址是0x4005f1， 第5行的起始地址是0x4005f8，可以知道0x4005f5位置的指令是属于第4行代码的。


