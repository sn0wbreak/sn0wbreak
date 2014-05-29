/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to Pytech for correcting some typos
*/

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/afc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct lockdown_t {
    idevice_t *device;
    lockdownd_client_t client;
} lockdown_t;

void ERROR(char *errstr)
{
    printf("ERROR: %s\n", errstr);

}

void INFO(char *infostr)
{
    printf("[*] %s\n", infostr);
}


char *udid;
idevice_t iDevice = NULL;

int ConnectToDevice()
{
    INFO("Connecting to device...");

    if (idevice_new(&iDevice, NULL) != IDEVICE_E_SUCCESS)
    {
        ERROR("Cannot connect to device! Make sure it is plugged in.");
        return -1;
    }
    if (idevice_get_udid(iDevice, &udid) != IDEVICE_E_SUCCESS)
    {
        ERROR("Can't get UDID of the device. Make sure it is plugged in.");
        return -1;
    }
    return 0;
}

lockdownd_client_t lockdown = NULL;

int InitLockdown()
{
    INFO("Starting lockdown...");

    if (lockdownd_client_new_with_handshake(iDevice, &lockdown, "jalebr4ke") != LOCKDOWN_E_SUCCESS)
    {
        ERROR("Could not start lockdown!");
        return -1;
    }

    return 0;
}

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
    if (ConnectToDevice() == -1) { return -1; }
    printf("[*] Successfully connected to the iDevice. UDID: %s\n", udid);

    if (InitLockdown() == -1) { return -1; }
    printf("[*] Lockdown initialization is sucessful.\n");

    char product = NULL;
    char build = NULL;
    char version = NULL;

    lockdown_get_string(lockdown, "HardwareModel", product);
    lockdown_get_string(lockdown, "BuildVersion", build);
    lockdown_get_string(lockdown, "ProductVersion", version); 
    printf("can't get info about your idevice, pls ! try again\n");
                 lockdownd_client_free(lockdown);
                 idevice_free(iDevice);
                 return -1;
    }
             printf("build: %s\n product: %s\nios version:%s\n", build, product,version);

             return 0;
}
