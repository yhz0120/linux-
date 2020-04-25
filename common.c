/* filename : common.c
 * function ：主要用于查询卷设备的信息
 * GIcon    : glib封装的图标struct
 * GFile    : gio封装的文件操作struct
 * g_free() : char* 类型内存释放函数，glib在free()的基础上优化封装的函数
 * g_object_unref() : 内存释放函数，用于glib封装的内置数据类型
 *
 * 知识点：
 *  三目运算符
 *  GFile是否是本地文件
 *  U盘驱动可以弹出，/dev设备不可弹出
 */

#include <stdio.h>
#include "common.h"

//根据挂载点GMount获取卷设备信息
void volume_get_info_from_mount(GDrive* drive,GMount* mount){
    GIcon *icon;
    GFile *root;
    char  *name,*mount_uri,*tooltip;
    gboolean can_eject = FALSE;                 //卷设备默认不可弹出
    char  *drive_name;                          //驱动器名字
    gboolean native_device = TRUE;

    icon = g_mount_get_icon(mount);             //get挂载点的icon信息
    root = g_mount_get_default_location(mount); //获取默认挂载位置
    native_device = g_file_is_native(root);     //判断设备是本地设备or网络设备
    name = g_mount_get_name(mount);             //get挂载点的名字
    mount_uri = g_file_get_uri(root);           //get挂载点的uri路径
    tooltip = g_file_get_parse_name(root);      //提示，即文件的解释
    if(NULL != drive){
        drive_name = g_drive_get_name(drive);   //get驱动器的名字
        can_eject = g_drive_can_eject(drive);   //驱动器是否可以弹出
        printf("%-20s-> %-10s %-10s %s\n",drive_name,name,can_eject ? "可弹出":"不可弹出",mount_uri);
        g_free(drive_name);
    }else
        printf("%-10s %-10s %s%s\n",name,can_eject ? "可弹出":"不可弹出",mount_uri,native_device?"":"(网络设备)");

    g_free(name);
    g_free(mount_uri);
    g_free(tooltip);
    g_object_unref(icon);
    g_object_unref(root);
}

//根据卷GVolume获取卷设备信息
void volume_get_info_from_volume(GDrive* drive,GVolume* volume){
    GIcon *icon;
    char  *name;
    gboolean can_eject = FALSE;                 //卷设备默认不可弹出
    char  *drive_name;                          //驱动器名字


    icon = g_volume_get_icon(volume);           //获取卷设备的icon信息
    name = g_volume_get_name(volume);           //获取卷设备的名字

    if(NULL != drive){
        drive_name = g_drive_get_name(drive);   //get驱动器名
        can_eject = g_drive_can_eject(drive);   //驱动器是否可以弹出
        printf("%-20s-> %-10s %-10s\n",drive_name,name,can_eject ? "可弹出":"不可弹出");
        g_free(drive_name);
    }else
        printf("%-10s %-10s\n",name,can_eject ? "可弹出":"不可弹出");

    g_free(name);
    g_object_unref(icon);
}

/*
void volume_get_info_from_mount(GMount* mount);
void volume_get_info_from_mount(GMount* mount);
*/
