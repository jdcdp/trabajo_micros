#ifndef _MACROS_H_
#define _MACROS_H_

 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

 #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

 #define bitchange(port,pin,val) (port=(port & ~(1<<pin))|val<<pin)

#endif
