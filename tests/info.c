/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to PythEch for correcting some typos

And the rest of the sn0wbreak team

*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"
#include "file_get_contents.h"

bool q = false;

#define INFO(x...) \
  if (!q) { printf("[*] "), printf(x); }


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


int file_exists(const char filename[]) {
  struct stat stbuf;
  if (stat(filename, &stbuf) == -1) {
    return (0);
  }
  return (1);
}

int main(int argc, char * argv[])
{
    if (argv[1] == NULL)
    {
        printf("Usage: \n%s --boot boots your device\n%s --cache caches your current device for booting\n%s SomeInfo query's lockdown about SomeInfo and echo's it\n", argv[0], argv[0], argv[0]);
        return -1;
    }
    if (argv[2] != NULL)
    {
        if (strcmp(argv[2], "-q") == 0)
        {
            q = true;
        }
    }
    if (strcmp(argv[1], "--boot") == 0)
    {
	INFO("got --boot");
        char *homedir = getenv("HOME"); // this section works perfectly
	INFO("homedir: %s",homedir);
        char *cache = strcat(homedir, "/.sn0wbreak/device_cache"); // we get the path and are fine
	INFO("cache file: %s",cache);
        if (!file_exists(cache)) // this works too
        {
            ERROR("Please cache your device first....\n");
            return -1;
        }
        else
        {
            long unsigned int *length = 0; 
            char **plistc = NULL; 
	    INFO("next step will be fgc");
            file_get_contents(cache, plistc, length); 

            INFO("I will boot your device with opensn0w now, with deviceinfos from my cache, please place your device into DFU mode....\n");
            char *p1 = strcat("/os/bin/opensn0w_cli -p /os/bundles/", (char *)plistc); 
            printf("%s", p1);
            INFO("Done!\n");
            return 0;
        }
    }
    else // Connects to device
    {
        INFO("Connecting to device...\n");
        device_t *device = device_create(NULL);
        if (device == NULL) // Checks if the device is plugged in or not
        {
            ERROR("Cannot connect to device! Make sure it is plugged in.\n");
            return -1;
        }
        INFO("[*] Successfully connected to the iDevice. UDID: %s\n", device->uuid);


        INFO("Starting lockdown...\n");

        lockdown_t *lockdown = lockdown_open(device); // Startes the lockdown protocol
        if (lockdown == NULL)
        {
            ERROR("Could not start lockdown!\n");
            return -1;
        }
        INFO("Lockdown initialization is sucessful.\n");

        if (strcmp(argv[1], "--cache") == 0)
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
                return -1; // gets Product Type, Build Version and Product version using lockdown
            }
            printf("%s_%s_%s\n", product, version, build);
        }
        else
        {
            char * value = NULL;
            if (lockdown_get_string(lockdown, argv[1], &value) != LOCKDOWN_E_SUCCESS)
            {
                ERROR("Can't get info about your iDevice, please try again!\n"); // Couldn't find a device
                lockdown_free(lockdown);
                device_free(device);
                return -1;
            }
            printf("%s\n", value);
        }
    }


    return 0;
}
