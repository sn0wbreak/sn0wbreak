/* Code by sjeezypwn, this is a gift to the sn0wbreak developers

Thanks to Pytech for correcting some typos
*/
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/afc.h>
#include <stdio.h>
#include <stdlib.h>

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


int main(int argc, char *argv[])
{
    if (ConnectToDevice() == -1) { return -1; }
    printf("[*] Successfully connected to the iDevice. UDID: %s\n", udid);

    if (InitLockdown() == -1) { return -1; }
    printf("[*] Lockdown initialization is sucessful.\n");

    char *product = NULL;
    char *build = NULL;
    char *version = NULL;


    if ((lockdown_get_string(lockdown, "HardwareModel", &product) != LOCKDOWN_E_SUCCESS)
            || (lockdown_get_string(lockdown, "BuildVersion", &build) != LOCKDOWN_E_SUCCESS) || (lockdown_get_string(lockdown, "ProductVersion", &version) != LOCKDOWN_E_SUCCESS)) {
                 printf("can't get info about your idevice, pls ! try again\n");
                 lockdownd_client_free(lockdown);
                 device_free(iDevice);
                 return -1;
    }
             printf("build: %s\n product: %s\nios version:%s\n", build, product,version);

             return 0;
}
