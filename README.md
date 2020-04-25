[置顶]代码中的API可以百度"**GNOME开发者中心**"
[置顶]直达:https://developer.gnome.org/index.html.zh_CN
[置顶]代码里的注释是经过考虑的，相同代码的不同注释是为了增强读者的理解
[置顶]如果有错误的地方，请批正

## 1、 运行须知:

​    虽然该程序不涉及图形化界面，但是运行是仍然需要在本机上运行
​    远程ssh运行结果会有异常
​    当然，远程运行也不会报告程序错误，我反而也希望你能在远程ssh下运行，对比下输出结果

## 2、 项目介绍:

​    common.c 根据驱动GDrive/卷设备GVolume查看具体卷设备的信息
​    volume-connected-drives.c 查看linux系统上与驱动GDrive有关的所有卷设备
​    volume-no-drives.c  查看linux系统上与驱动无关的卷设备

## 3、 设备划分举例:(来自于项目中的理解)

​    驱动有关的设备：/dev/sd*设备、u盘设备
​    与驱动无关的设备：lvm分区

## 4、 项目涉及知识：

- linux libglib-2.0.so 和 libgio-2.0.so中磁盘操作的API的运用
- Makefile文件书写(只要实际案例，具体makefile规则请自己百度学习)
- 一个makefile生成多个可执行文件
- pkg-config命令用法
- 不使用Makefile如何编译生成二进制

5、Makefile简单介绍：[TAB]表示一个TAB按键
------------------------------------------------------------------
```makefile
all:目标二进制a.out     	 //表示make根据该makefile要生成二进制a.out

a.out : 几个.o文件       //表示生成a.out需要依赖后面这几个.o文件
[TAB]gcc *.o -o a.out	//表示使用gcc把*.o编译成二进制文件a.out

%.o : %.c               //表示某个.o文件需要由同名.c文件编译生成
[TAB]gcc -c .c          //gcc使用-c生成同名.o文件
```



## 6、pkg-config命令简介：

​    (1)出现原因：解决gcc 编译时手动挨个制定 .h 和 .so的具体路径(即-I和-L选项)
​    (2)用法实例：     

```shell
	pkg-config --cflags gio-2.0 //解决gcc -I指定gio API的头文件路径
	pkg-config --libs gio-2.0   //解决gcc -L指定libgio-2.0.so的库文件路径
```

​    (3)工作原理：
​        pkg-config 命令依赖于.pc文件
​        你可以locate gio-2.0.pc后进入对应目录查看当前linux上已安装并可用的.pc文件