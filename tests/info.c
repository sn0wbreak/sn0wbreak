/* Code by sjeezypwn, this is a gift to the sn0wbreak developers
*/

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct lockdown_t {
    idevice_t *device;
    lockdownd_client_t client;
    } lockdown_t;

struct idevice_private {
	char *udid;
	void *conn_data;
};

int lockdown_get_string(lockdown_t * lockdown, const char *key, char **value)
{
    if (!lockdown || !lockdown->client) {
        return -1;
    }

    char *str = NULL;
    plist_t pl = NULL;
    lockdownd_error_t err =
        lockdownd_get_value(lockdown->client, NULL, key, &pl);
    if (err == LOCKDOWN_E_SUCCESS) {
        if (pl != NULL && plist_get_node_type(pl) == PLIST_STRING) {
            plist_get_string_val(pl, &str);
            plist_free(pl);
            if (str != NULL) {
                *value = str;
                return 0;
            }
        }
    }
    if (pl) {
        plist_free(pl);
    }
    return -1;
}
int main(int argc, char *argv[])
{
    idevice_private *device = NULL;
    char *product = NULL;
    char *build = NULL;
    char *version = NULL;
    device = device_create(NULL);


lockdown_t *lockdown = lockdown_open(device);

if ((lockdown_get_string(lockdown, "HardwareModel", &product) != LOCKDOWN_E_SUCCESS)
        || (lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS) || (lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS)) {
             printf("can't get info about your idevice, pls ! try again\n");
             lockdownd_client_free(lockdown);
             idevice_free(device);
             return -1;
}
             printf("build: %s\n product: %s\nios version:%s\n", build, product,version);

             return 0;
}
