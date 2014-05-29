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
#include <string.h>

int mode = 0;

void INFO(char *infostr)
{
    if(mode != 3) // ! else
    {
        printf("[*] %s\n", infostr);
    }
}

int main(int argc, char *argv[])
{
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
        else if (mode == 3) // else
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
    else if (mode == 1)
    {
        printf("BOOT!");
    }
    else
    {
        return -1;
    }

    return 0;
}
