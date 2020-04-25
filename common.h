/* filenem : common.h
 * function: 公用函数的原型声明
 */
#ifndef COMMON_H
#define COMMON_H

#include <glib.h>
#include <gio/gio.h>
//函数原型声明中参数可以只列出类型，不用写形参名
void volume_get_info_from_mount(GDrive*,GMount*);
void volume_get_info_from_volume(GDrive*,GVolume*);

#endif /*COMMON_H*/
