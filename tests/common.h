/**
 * Debug support
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/afc.h>

#include "device.h"
#include "lockdown.h"

#define DEBUG(x...) \
 	printf("[DEBUG]: "), printf(x)

#define ERROR(x...) \
 	do { printf("[ERROR]: "), printf(x); } while(0);

#define WARN(x...) \
 	printf("[WARNING]: "), printf(x)

#
