/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to PythEch for correcting some typos

And the rest of the sn0wbreak team

*/

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/afc.h>

#include "device.h"
#include "lockdown.h"

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _compatibility {
    char *product;
    char *build;
} compatibility_t;

compatibility_t compatible_devices[] = {
  {"n90ap", "11A465"},
  {"n90bap","11A465"},
  {"n92ap", "11A465"},
  {"90ap", "11A465"},
  {"90bap", "11A465"},
  {"n92ap", "11A465"},
  {"n90ap", "11B511"},
  {"n90bap", "11B511"},
  {"n92ap", "11B511"},
  {"n90ap", "1B554a"},
  {"n90bap", "1B554a"},
  {"n92ap", "1B554a"},
  {"n90ap", "11B651"},
  {"n90bap","11B651"},
  {"n92ap","11B651"},
  {"n90ap","11D169"},
  {"n90bap","11D169"},
  {"n92ap","11D169"},
  {"n90ap","11D201"},
  {"n90bap","11D201"},
  {"n92ap","11D201"},
  {NULL, NULL}
  
  //need to finsih this
};

int verify_product(char *product, char *build)
{
    compatibility_t *curcompat = &compatible_devices[0];
    while ((curcompat) && (curcompat->product != NULL)) {
        if (!strcmp(curcompat->product, product) &&
            !strcmp(curcompat->build, build))
            return 0;
        curcompat++;
    }
    return 1;
} // thanks to winocm for the 'verify_product' function.


void INFO(char *infostr)
{
  bool qqq = false
  if(!qqq)
  {
    printf("[*] %s\n", infostr);
  }
}

int main(int argc, char *argv[])
{
bool q = false;
if(strcmp(argv[2], "-q") != 0)
    (bool*) q = true;

  if(strcmp(argv[1], "--boot") == 0)
  {
    printf("BOOT!!!");
  }
  else // Connects to device
  {
    INFO("Connecting to device...", q);
    device_t *device = device_create(NULL);
    if (device == NULL) // Checks if the device is plugged in or not
    {
        ERROR("Cannot connect to device! Make sure it is plugged in.");
        return -1;
    }
    INFO("[*] Successfully connected to the iDevice. UDID: %s\n", device->uuid,q);

    INFO("Starting lockdown...",q);

    lockdown_t *lockdown = lockdown_open(device);   // Startes the lockdown protocol
    if (lockdown == NULL)
    {
        ERROR("Could not start lockdown!");
        return -1;
    }
    INFO("Lockdown initialization is sucessful.",q);

    if(strcmp(argv[1], "--cache") == 0)
    {
    char *product = NULL;
    char *build = NULL;
    char *version = NULL;
    if ((lockdown_get_string(lockdown, "ProductType", &product) != LOCKDOWN_E_SUCCESS)
            || (lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS)
            || (lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS)) {
                 ERROR("Can't get info about your iDevice, please try again!\n");
                 lockdown_free(lockdown);
                 device_free(device);
                 return -1; // gets Product Type, Build Version and Product version using lockdown
    }
             printf("%s_%s_%s\n", product, version, build);
           }
           else
           {
             char *value = NULL;
             if (lockdown_get_string(lockdown, argv[1], &value) != LOCKDOWN_E_SUCCESS)
             {
               ERROR("Can't get info about your iDevice, please try again!\n"); // Couldn't find a device
               lockdown_free(lockdown);
               device_free(device);
               return -1;
             }
             printf("%s",value);
           }
}



             return 0;
}
