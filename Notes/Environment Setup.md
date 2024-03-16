MIT6.828这门课程在2018年之后已经改组成其他课程（MITS6.081），课程实验的更新也停止在2018年，因此环境配置方面可能会出现各种各样的问题，下面为2023年1月进行的配置流程。

**环境：VMWare虚拟机 Ubuntu 22.04LTS x86_64**

# 1. 编译器工具链检查

1. ```bash
   objdump -i
   # 第二行应显示elf32-i386
   ```

2. 安装GCC等一系列编译工具链

   ```bash
   sudo apt-get install build-essential gdb
   ```

3. ```bash
   gcc -m32 -print-libgcc-file-name
   # 应显示有/usr/lib/gcc/x86_64-linux-gnu/version/32/libgcc.a
   ```

4.  对于64位系统，还需要安装32位支持：

   ```bash
   sudo apt-get install gcc-multilib
   ```

# 2. QEMU安装

课程提供了它定制的QEMU版本，并且强烈建议安装这一版QEMU而不是通过包管理器安装的QEMU。

1. 下载课程提供的定制版QEMU源码
   
   ```bash
git clone https://github.com/mit-pdos/6.828-qemu.git qemu
   ```
   
2. 安装Python2.7（自带的太新了安装程序不认……）及一系列依赖库

   ```bash
   sudo apt-get install python2.7 &&
   sudo apt-get install libsdl1.2-dev && 
   sudo apt-get install libtool-bin &&
   sudo apt-get install libglib2.0-dev && 
   sudo apt-get install libz-dev &&
   sudo apt-get install libpixman-1-dev 
   ```

3. ```bash
   cd qemu && ./configure --disable-kvm --disable-werror --target-list="i386-softmmu x86_64-softmmu" --python=/usr/bin/python2.7 --prefix=$HOME/MIT6.828Lab/qemu
   #默认将qemu安装到/usr/local目录下
   #如果需要修改安装目录，在命令里加 --prefix=安装路径 即可
   ```

4. 找到文件`qemu/qga/commands-posix.c`，在文件前面增加一行`#include <sys/sysmacros.h>`，保存
   
   > 如果不执行这一步，可能会报错“undefined reference to 'major'”
   
5. ```bash
   sudo make && sudo make install
   #一定要有sudo，否则会出现权限不足报错
   ```

6. 检查QEMU是否安装成功

   ```bash
   ls /usr/local/bin | grep qemu # 这里假设qemu安装在默认位置
   # 应显示以下结果，其中qemu-system-i386就是我们需要的
   qemu-ga
   qemu-img
   qemu-io
   qemu-nbd
   qemu-system-i386
   qemu-system-x86_64
   ```

