/* Code by sjeezypwn, this is a gift to the sn0wbreak developers
*/

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobile_image_mounter.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/sbservices.h>
#include <libimobiledevice/file_relay.h>
#include <libimobiledevice/diagnostics_relay.h>
#include <string.h>
#include <zlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct lockdown_t {
    idevice_t *device;
    lockdownd_client_t client;
    } lockdown_t;

struct idevice_private {
	char *udid;
	void *conn_data;
};


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
             lockdown_free(lockdown);
             device_free(device);
             return -1;
}
             printf("build: %s\n product: %s\nios version:%s\n", build, product,version);
 
             return 0;
}
