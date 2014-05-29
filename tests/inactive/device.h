#ifndef _DEVICE_H_
#define _DEVICE_H_

typedef struct device_t {
    idevice_t client;
    unsigned char *uuid;
    unsigned char *ecid;
} device_t;

device_t *device_create(const char *uuid);
void device_free(device_t * device);
void device_enable_debug();

#endif
