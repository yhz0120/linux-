/* filename : volume-connected-drives.c
 * function : linux系统中所有与GDrive有关的卷设备
 * compile  : gcc volume-connected-drives.c common.c `pkg-config --cflags --libs gio-2.0 glib-2.0`
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
#include "common.h"
#include <stdio.h>

void volume_that_connect_with_drive();

int main(){
    volume_that_connect_with_drive();
    return 0;
}

void volume_that_connect_with_drive(){
    char *drive_name;
    GList *l,*ll,*volumes;
    GDrive *drive;
    GVolume *volume;
    GMount  *mount;
    GVolumeMonitor* monitor;
    GList*          drives;

    monitor = g_volume_monitor_get();                        //get 磁盘监控器
    drives  = g_volume_monitor_get_connected_drives(monitor);//get所有已经连接的驱动器链表

    for(l = drives; l != NULL; l = l->next){        //遍历连接的驱动器
        drive = l->data;
        volumes = g_drive_get_volumes(drive);       //get本驱动器上的所有卷设备
        if(NULL != volumes){
            for(ll = volumes; ll != NULL; ll = ll->next){ //遍历驱动器上的所有卷设备
                volume = ll->data;
                mount = g_volume_get_mount(volume); //get当前卷设备的挂载信息
                if(NULL != mount){                  //该卷设备已挂载
                    volume_get_info_from_mount(drive,mount);    //原型见common.c
                    g_object_unref(mount);
                }else{
                    volume_get_info_from_volume(drive,volume);  //原型见common.c
                }
                g_object_unref(volume);
            }//for
        }
        g_list_free(volumes);
    }//for
    g_list_free(drives);    //GList对象释放函数

    g_object_unref(monitor);//减少系统磁盘监控器的引用计数,与标准C的close()概念原理一致
}
