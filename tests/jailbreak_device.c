#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>

#include <signal.h>
#include <plist/plist.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>

#include <assert.h>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/notification_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/sbservices.h>
#include <libimobiledevice/file_relay.h>

#include <zlib.h>

#include "common.h"

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
  
  //need to finsih this
}

int jailbreak(const char *uuid)
{
    device_t *device = NULL;
    char *build = NULL;
    char *product = NULL;
    
    if(!uuid) {
       INFO("No UUID Found\n");
       
       
    device = device_create(uuid);
       INFO("Couldn't create Device\n");
    
       lockdown_t *lockdown = lockdown_open(device);
    if (lockdown == NULL) {
        ERROR("Lockdown Connection failed\n");
        device_free(device);
        return -1;
        
    /* ... still in the making ... */
    
    INFO("Jailbreak a %s running %s (%s)", product, build, version);
    
    /* ... still in the making ... */
    
    uint16_t port = 0;
    
    if(lockdown_start_service(lockdown, "com.apple.afc", &port) != 0) {
        ERROR("Couldn't connect to AFC");
      }
      else {
         lockdown_start_service(lockdown, "com.apple.afc", &port);
    }
    
      lockdown_free(lockdown);
      lockdown = NULL;
      
      afc_client_t afc = NULL;
      char *port2 = &port;
      afc_client_new(device->client, &desc, &afc);
           if (!afc) {
             ERROR("Could not connect to AFC service\n");
             device_free(device);
             return -1;
        }
      
      /*  .... Very Lazy .... it's still getting worked on ..... */
      
       if (backup_mkdir
            (backup, "MediaDomain", "Media/Recordings", 0755, 501, 501,
             4) != 0) {
            ERROR("Could not make folder\n");
        }

        if (backup_symlink
            (backup, "MediaDomain", "Media/Recordings/.haxx", "/", 501, 501,
             4) != 0) {
            ERROR("Failed to symlink root!\n");
        }

        if (backup_mkdir
            (backup, "MediaDomain", "Media/Recordings/.haxx/var/unthreadedjb",
             0755, 0, 0, 4) != 0) {
            ERROR("Could not make folder\n");
        }

        /* This is bad */
        if (!strcmp(product, "N18AP") || !strcmp(product, "N88AP")) {
            if (backup_add_file_from_path
                (backup, "MediaDomain", "payload/Unthread.app/unthread@1x.png",
                 "Media/Recordings/.haxx/var/unthreadedjb/unthread.png",
                 0100644, 0, 0, 4) != 0) {
                ERROR("Could not add unthread.png");
            }
        } else if (!strcmp(product, "K48AP")) {
            if (backup_add_file_from_path
                (backup, "MediaDomain",
                 "payload/Unthread.app/unthread-ipad.png",
                 "Media/Recordings/.haxx/var/unthreadedjb/unthread.png",
                 0100644, 0, 0, 4) != 0) {
                ERROR("Could not add unthread.png");
            }
        } else {
            if (backup_add_file_from_path
                (backup, "MediaDomain", "payload/Unthread.app/unthread.png",
                 "Media/Recordings/.haxx/var/unthreadedjb/unthread.png",
                 0100644, 0, 0, 4) != 0) {
                ERROR("Could not add unthread.png");
            }
        }

        {
            char jb_path[128];
            char amfi_path[128];
            char launchd_conf_path[128];

            snprintf(jb_path, 128, "payload/%s_%s/var/unthreadedjb/jb", build,
                     product);
            snprintf(amfi_path, 128,
                     "payload/%s_%s/var/unthreadedjb/amfi.dylib", build,
                     product);
            snprintf(launchd_conf_path, 128,
                     "payload/%s_%s/var/unthreadedjb/launchd.conf", build,
                     product);

            if (backup_add_file_from_path
                (backup, "MediaDomain", launchd_conf_path,
                 "Media/Recordings/.haxx/var/unthreadedjb/launchd.conf",
                 0100644, 0, 0, 4) != 0) {
                ERROR("Could not add launchd.conf");
            }
            if (backup_symlink
                (backup, "MediaDomain",
                 "Media/Recordings/.haxx/private/etc/launchd.conf",
                 "/private/var/unthreadedjb/launchd.conf", 0, 0, 4) != 0) {
                ERROR("Failed to symlink launchd.conf!\n");
            }
            if (backup_add_file_from_path(backup, "MediaDomain", jb_path,
                                          "Media/Recordings/.haxx/var/unthreadedjb/jb",
                                          0100755, 0, 0, 4) != 0) {
                ERROR("Could not add jb");
            }
            if (backup_add_file_from_path(backup, "MediaDomain", amfi_path,
                                          "Media/Recordings/.haxx/var/unthreadedjb/amfi.dylib",
                                          0100755, 0, 0, 4) != 0) {
                ERROR("Could not add amfi");
            }
            if (backup_add_file_from_path
                (backup, "MediaDomain", "payload/Cydia.tar",
                 "Media/Recordings/.haxx/var/unthreadedjb/Cydia.tar", 0100644,
                 0, 0, 4) != 0) {
                ERROR("Could not add amfi");
            }
        }
    }
    idevicebackup2(5, rargv2);

    backup_free(backup);

    DEBUG("Installed jailbreak, fixing up directories.\n");

    /********************************************************/
    /* move back any remaining dirs via AFC */
    /********************************************************/
 fix:
    DEBUG("Recovering files...\n", 80);
    if (!afc) {
        lockdown = lockdown_open(device);
        port = 0;
        if (lockdown_start_service(lockdown, "com.apple.afc", &port) != 0) {
            WARN("Could not start AFC service. Aborting.\n");
            lockdown_free(lockdown);
            goto leave;
        }
        lockdown_free(lockdown);

        desc.port = port;
        afc_client_new(device->client, &desc, &afc);
        if (!afc) {
            WARN("Could not connect to AFC. Aborting.\n");
            goto leave;
        }
    }

// this obviously was a fork of unthreadedjb's code

// I am going to finish this next time
         
    
    
    
    
