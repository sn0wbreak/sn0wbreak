#ifndef _LOCKDOWN_H_
#define _LOCKDOWN_H_

typedef struct lockdown_t {
    device_t *device;
    lockdownd_client_t client;
} lockdown_t;

lockdown_t *lockdown_open(device_t * device);
int lockdown_get_value(lockdown_t * lockdown, const char *domain,
                       const char *key, plist_t * value);
int lockdown_get_string(lockdown_t * lockdown, const char *key, char **value);
int lockdown_start_service(lockdown_t * lockdown, const char *service,
                           uint16_t * port);
int lockdown_stop_service(lockdown_t * lockdown, const char *service);
int lockdown_close(lockdown_t * lockdown);
void lockdown_free(lockdown_t * lockdown);

#endif
