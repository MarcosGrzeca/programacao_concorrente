#ifndef IOCTLDRIVER
#define IOCTLDRIVER

#include <linux/ioctl.h>
    
#define IOCTLID 0x15
#define WRITE_IOCTL _IOW(IOCTLID, 1, char *)
#endif
