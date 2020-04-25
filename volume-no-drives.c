/* filename : volume-no-drives.c
 * function : linux系统中所有与驱动器GDrive无关的卷设备
 * compile  : gcc volume-no-drives.c common.c `pkg-config --cflags --libs gio-2.0 glib-2.0`
 * 以下结构体来自于linux开源系统封装的libglib-2.0.so/libgio-2.0.so
 * 解决编译依赖:
 *  fedora/centos的rpm系： sudo yum install glib2-devel
 *  ubuntun/debian的deb系: sudo apt-get install libglib2.0-dev
 *
 * GVolumeMonitor : linux磁盘监控器
 * GDrive         : linux磁盘驱动器
 * GVolume        : linux卷设备
 * GMount         : 挂载的相关信息
 * GList          : glib封装的链表
 *
 * vim配置：set ts=4
 */
#include <stdio.h>
#include "common.h"

void volume_that_no_with_drives();

int main(){
    volume_that_no_with_drives();
    return 0;
}

void volume_that_no_with_drives(){
    GList *volumes;
    GList *l;
    GDrive *drive;
    GVolume *volume;
    GMount *mount;
    GVolumeMonitor* monitor;

    monitor = g_volume_monitor_get();               //get系统磁盘监控器
    volumes = g_volume_monitor_get_volumes(monitor);//获取系统上所有的卷设备(包括与驱动器有关的设备)
    for(l = volumes; l != NULL; l = l->next){
        volume = l->data;
        drive = g_volume_get_drive(volume);         //get卷设备的驱动器
        if(NULL != drive){                          //该卷设备有对应的驱动器，这里不深究,参考volume-connected-drives.c
            g_object_unref(volume);
            g_object_unref(drive);
            continue;
        }

        mount = g_volume_get_mount(volume);         //获取卷设备的挂载信息
        if(NULL != mount){
            volume_get_info_from_mount(NULL,mount);//见common.c
            g_object_unref(mount);
        }
        else
            volume_get_info_from_volume(NULL,volume);//见common.c

        g_object_unref(volume);
    }//for
    g_list_free(volumes);   //释放GList链表内存

    g_object_unref(monitor);//减少引用计数，简单的可以理解为释放内存,可以对比close()进行理解
}
