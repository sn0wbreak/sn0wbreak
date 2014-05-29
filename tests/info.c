/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to PythEch for correcting some typos
*/

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mode = 0;

#define INFO(x...) \
    if (mode != 3) { printf("[*] "), printf(x); }

int main(int argc, char *argv[])
{
    if (argc != 2) { return -1; } //avoid crash

    if (strcmp(argv[1], "--boot") == 0)
    {
        mode = 1;
    }
    else if (strcmp(argv[1], "--cache") == 0)
    {
        mode = 2;
    }
    else
    {
        mode = 3;
    }

    if (mode != 1) // ! --boot
    {
        INFO("Connecting to device...\n");
        device_t *device = device_create(NULL);
        if (device == NULL)
        {
            ERROR("Cannot connect to device! Make sure it is plugged in.\n");
            return -1;
        }
        INFO("Successfully connected to the iDevice. UDID: %s\n", device->uuid);

        INFO("Starting lockdown...\n");
        lockdown_t *lockdown = lockdown_open(device);
        if (lockdown == NULL)
        {
            ERROR("Could not start lockdown!\n");
            return -1;
        }
        INFO("Lockdown initialization is sucessful.\n");

        if (mode == 2) // --cache
        {
            char *product = NULL;
            char *build = NULL;
            char *version = NULL;
            if (lockdown_get_string(lockdown, "ProductType", &product) != LOCKDOWN_E_SUCCESS ||
                lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS  ||
                lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS) 
            {
                ERROR("Can't get info about your iDevice, please try again!\n");
                lockdown_free(lockdown);
                device_free(device);
                return -1;
            }
            printf("%s_%s_%s\n", product, version, build);
        }
        else
        {
            char *value = NULL;
            if (lockdown_get_string(lockdown, argv[1], &value) != LOCKDOWN_E_SUCCESS)
            {
                ERROR("Can't get info about your iDevice, please try again!\n");
                lockdown_free(lockdown);
                device_free(device);
                return -1;
            }
            printf("%s\n", value);
        }
    }
    else
    {
        printf("BOOT!\n");
    }

    return 0;
}
