/**
 * Debug support
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/afc.h>

#include "device.h"
#include "lockdown.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#undef DEBUG

#if 1

#define DEBUG(x...) \
 	printf("[debug] "), printf(x)

#define ERROR(x...) \
 	do { printf("[error] "), printf(x); } while(0);

#define WARN(x...) \
 	printf("[warn] "), printf(x)

#else

#define DEBUG(x...)
#define ERROR(x...)
#define WARN(x...)

#endif


#endif
