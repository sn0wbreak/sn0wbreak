/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to PythEch for correcting some typos
*/

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/afc.h>

#include "device.h"
#include "lockdown.h"

#include "common.h"

#include <stdio.h>
#include <stdlib.h>

void INFO(char *infostr)
{
    printf("[*] %s\n", infostr);
}

int main(int argc, char *argv[])
{
    INFO("Connecting to device...");
    device_t *device = device_create(NULL);
    if (device == NULL)
    {
        ERROR("Cannot connect to device! Make sure it is plugged in.");
        return -1;
    }
    printf("[*] Successfully connected to the iDevice. UDID: %s\n", device->uuid);

    INFO("Starting lockdown...");

    lockdown_t *lockdown = lockdown_open(device);
    if (lockdown == NULL)
    {
        ERROR("Could not start lockdown!");
        return -1;
    }
    INFO("Lockdown initialization is sucessful.");

    char *product = NULL;
    char *build = NULL;
    char *version = NULL;

    if ((lockdown_get_string(lockdown, "HardwareModel", &product) != LOCKDOWN_E_SUCCESS)
            || (lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS)
            || (lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS)) {
                 printf("can't get info about your idevice, pls ! try again\n");
                 lockdown_free(lockdown);
                 device_free(device);
                 return -1;
    }
             printf("build: %s\n product: %s\nios version:%s\n", build, product,version);

             return 0;
}
