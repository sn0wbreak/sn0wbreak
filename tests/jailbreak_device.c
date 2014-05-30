#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <sys/stat.h>

#include "libpois0n.h"
#include "libpartial.h"
#include "libirecovery.h"

#include "common.h"
#include "ramdisk.h"
#include "exploits.h"
#include "payloads.h"

#define LIMERA1N

/* iPhone 3,1 Support for iOS 7.0*/

#define iBSS_31_70 /Downloads/Sn0wbreak/Firmware/iBSS.n90ap_70.RELEASE.dfu
#define iBEC_31_70 /Downloads/Sn0wbreak/Firmware/iBEC.n90ap_70.RELEASE.dfu
#define DT_31_70 /Downloads/Sn0wbreak/Firmware/DeviceTree.release.n90ap_70
#define KC_31_70 /Downloads/Sn0wbreak/Firmware/KernelCache.release.n90ap_70
#define RamDisk /Downloads/Sn0wbreak/RamDisk/ramdisk.dmg

/* Support for other Devices Coming Soon */

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
  {NULL, NULL};
  
}

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
  if(strcmp(argv[2], "-q") == 0)
  {
    printf("[*] %s\n", infostr);
  }
}


int boot_tethered_31_70()
{
    irecv_client_t client = NULL;
    
    /* DFU files */
    
    if(irecv_send_file(client, iBSS_31_70, 1) != 1)
        INFO("Couldn't upload iBSS\n");
    else if(irecv_send_file(client, iBEC_31_70, 1) != 1)
        INFO("Couldn't upload iBEC\n");
        
    /* DeviceTree and Kernelcache */    
        
    else if(irecv_send_file(client, DT_31_70, 1) != 1)
        INFO("Couldn't upload DeviceTree\n");
    else if(irecv_send_file(client, KC_31_70, 1) != 1)
        INFO("Couldn't upload KernelCache\n");
        
  else {
      INFO("All Files Successfully uploaded\n");
  }
  return 0;
}

int main(int argc, char **argv[])
{
    INFO("[*] Welcome to Sn0wbreak, this is a semi-tethered Jailbreak for all devices [*]\n");
    /* Going to add device detection using libimobiledevice to make this way easier */
    if(device == n90ap70)
      boot_tethered_31_70();
      
      INFO("RamDisk is going to be uploaded soon\n");
      
       INFO("Connecting to device...");
    device_t *device = device_create(NULL);
    if (device == NULL) // Checks if the device is plugged in or not
    {
        ERROR("Cannot connect to device! Make sure it is plugged in.");
        return -1;
    }
    printf("[*] Successfully connected to the iDevice. UDID: %s\n", device->uuid);

    INFO("Starting lockdown...");

    lockdown_t *lockdown = lockdown_open(device);   // Startes the lockdown protocol
    if (lockdown == NULL)
    {
        ERROR("Could not start lockdown!");
        return -1;
    }
    INFO("Lockdown initialization is sucessful.");

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

if(verify_product(product, build) != 1)
   printf("Not Compatible Device\n");
}
   return 0;       
         
}
