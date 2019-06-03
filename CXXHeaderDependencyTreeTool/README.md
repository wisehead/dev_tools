# 使用说明
- 在程序目录下执行main.go,将会分析整个工程内每一个文件(.h/.cc)的头文件依赖。
- 会在/tmp/analyze目录下生成当前工程每个.h/.cc文件依赖的头文件，以md文件的形式。
- 如果存在多个文件依赖同一个文件，在匹配过程中做了去重。如果完成的列出头文件依赖树，可以将递归方法中的去重逻辑去掉（但小心存在循环引用造成递归不能终止）。
# 用途
- 找到某个文件的头文件依赖树，然后根据其中的列举找出所有依赖的.h/.cc文件。
- 然后根据依赖，快速提取依赖的文件进行复用。

# 例如
以example作为工程，在example执行main
.go后会如下面的结果所示，同时在/tmp/analyze下生成对应文件的依赖。
我们可以观察到core/core.h依赖了头文件util/mutex.h和util/thread.h，
而util/thread.h依赖了util/queue.h和util/blocking_queue.h。
假定我们需要复用core/core.cc，我们可以快速找到core/core.cc的依赖头文件。我们可以抽取
- util/mutex.h
- util/mutex.cc
- util/thread.h
- util/thread.cc
- util/blocking_queue.h
- util/blocking_queue.cc
进行复用。

==========core/core.h==========
core/core.h
 - util/mutex.h
 - util/thread.h
 -  - util/queue.h
 -  - util/blocking_queue.h

==========test/test.h==========
test/test.h
 - core/core.h
 -  - util/mutex.h
 -  - util/thread.h
 -  -  - util/queue.h
 -  -  - util/blocking_queue.h

==========tool/tool.h==========
tool/tool.h
 - util/mutex.h

==========util/blocking_queue.h==========
util/blocking_queue.h
 - util/queue.h
 -  - util/mutex.h

==========util/mutex.h==========
util/mutex.h

==========util/queue.h==========
util/queue.h
 - util/mutex.h

==========util/thread.h==========
util/thread.h
 - util/queue.h
 -  - util/mutex.h
