#include "family.h"

#define ENGINE_SW	0
#define ENGINE_GRAPHICS	1
#define ENGINE_DVD	2

#define NV_PRAMIN                                       0x00700000
#define NV_PRAMIN_END                                   0x007fffff
#define NV_PFIFO_RAMHT                                  0x00002210
#define NV_FIFO_ENABLE                                  0x00002504
#define NV_FIFO(i)					(0x00800000+0x00010000*i)
