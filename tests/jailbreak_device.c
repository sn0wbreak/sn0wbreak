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

int boot_tethered_31_70()
{
    irecv_client_t client = NULL;
    
    /* DFU files */
    
    if(irecv_send_file(client, iBSS_31_70, 1) != 1)
        printf("Couldn't upload iBSS\n");
    else if(irecv_send_file(client, iBEC_31_70, 1) != 1)
        printf("Couldn't upload iBEC\n");
        
    /* DeviceTree and Kernelcache */    
        
    else if(irecv_send_file(client, DT_31_70, 1) != 1)
        printf("Couldn't upload DeviceTree\n");
    else if(irecv_send_file(client, KC_31_70, 1) != 1)
        printf("Couldn't upload KernelCache\n");
        
  else {
      printf("All Files Successfully uploaded\n");
  }
  return 0;
}

int main(int argc, char **argv[])
{
    printf("[*] Welcome to Sn0wbreak, this is a semi-tethered Jailbreak for all devices [*]\n");
    /* Going to add device detection using libimobiledevice to make this way easier */
    if(device == n90ap70)
      boot_tethered_31_70();
      
      printf("RamDisk is going to be uploaded soon\n");
      
      /* Send RamDisk File  */
}
        
        
