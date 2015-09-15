#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#define SUCCESS	0
#define FAILURE	-1

#define IOC_MAGIC  's'

#define IOCTL_SET_SPEAKER _IOW(IOC_MAGIC, 1, int)

#endif	
