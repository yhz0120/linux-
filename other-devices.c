/* filename : other-devices.c
 * function : linux系统中没有卷设备(GVolume)的设备
 * compile  : gcc other-devices.c common.c `pkg-config --cflags --libs gio-2.0 glib-2.0`
 * 例如：/etc/mtab文件列出的信息、ftp、sftp、samba等
 * vim配置: set ts=4
 */
#include <stdio.h>
#include "common.h"

void other_devices();

int main(){
    other_devices();
    return 0;
}

void other_devices(){
    GFile *root;
    GList *mounts;
    GList *l;
    GMount *mount;
    GVolume *volume;
    GDrive *drive;
    GVolumeMonitor* monitor;

    monitor = g_volume_monitor_get();               //get系统磁盘监控器
    mounts = g_volume_monitor_get_mounts(monitor);  //get系统上的所有挂载信息(即已经挂载的)

    for(l = mounts; NULL != l; l = l->next){
        mount = l->data;
        if(g_mount_is_shadowed(mount)){             //这个应该指的是lsblk命令以外的设备
            g_object_unref(mount);
            continue;
        }

        volume = g_mount_get_volume(mount);         //获取挂载点的卷设备信息
        if(NULL != volume){                         //该挂载点有卷设备
            g_object_unref(volume);
            g_object_unref(mount);
            continue;
        }

        /*root = g_mount_get_default_location(mount);//get默认挂载位置
        if(!g_file_is_native(root)){ //网络设备
            printf("a network device!\n");
            g_object_unref(root);
            continue;
        }*/

        volume_get_info_from_mount(NULL,mount);     //见common.c
        g_object_unref(mount);
    }//for
    g_list_free(mounts);        //GList对象释放函数
    g_object_unref(monitor);    //gobject内置结构体内存释放函数
}
