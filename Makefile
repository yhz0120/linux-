CC = gcc
RM = rm -f
CFLAGS =
#INCLUDE解决 .h/.c 文件内的#include<>问题
INCLUDE = `pkg-config --cflags glib-2.0 gio-2.0`
#LIBS解决 链接阶段的函数原型问题
LIBS = `pkg-config --libs glib-2.0 gio-2.0`

INCLUDE += -I./
#列出第一个可执行文件相关项(.c .o 二进制)
with_drive_src += \
	common.c \
	volume-connected-drives.c
with_drive_target = with-drive-test
with_drive_obj = $(patsubst %.c,%.o,$(with_drive_src))

#列出第二个可执行文件相关项(.c .o 二进制)
no_drive_src += \
	common.c \
	volume-no-drives.c
no_drive_obj = $(patsubst %.c,%.o,$(no_drive_src))
no_drive_target = no-drive-test

#列出第三个可执行文件相关项(.c .o 二进制)
other_device_src += \
	common.c \
	other-devices.c
other_device_obj = $(patsubst %.c,%.o,$(other_device_src))
other_device_target = other-devices-test

#all是make命令执行时的默认编译项
#后面列出三项，表示此Makefile会生成3个可执行程序
all: $(with_drive_target) $(no_drive_target) $(other_device_target)

$(with_drive_target):$(with_drive_obj)
	$(CC) $^ -o $@ $(LIBS)

#(LIBS)表示 .o -> 二进制 需要链接的so库
$(no_drive_target):$(no_drive_obj)
	$(CC) $^ -o $@ $(LIBS)

$(other_device_target):$(other_device_obj)
	$(CC) $^ -o $@ $(LIBS)
#(INCLUDE)表示解决 预处理 阶段的头文件展开目录查找
%.o : %.c
	$(CC) -c  $< $(INCLUDE)

#make clean 会删除make命令生成的 .o 二进制文件
.PHONY:clean

clean:
	$(RM) $(with_drive_obj) $(with_drive_target) \
		  $(no_drive_obj) $(no_drive_target) \
		  $(other_device_obj) $(other_device_target)
