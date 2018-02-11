#include "ps4.h"
 
int _main(void) {
    initKernel();
    initLibc();
 
        FILE *usbdir = fopen("/mnt/usb0/.dirtest", "wb");
   
         if (!usbdir)
            {
                usbdir = fopen("/mnt/usb1/.dirtest", "wb");
                if (!usbdir)
                {
                        copyFile("/system_data/priv/mms/app.db", "/system_data/priv/mms/app.db_backup");
                        copyFile("/system_data/priv/mms/addcont.db", "/system_data/priv/mms/addcont.db_backup");
                        return 0;
                }
                else
                {
                        fclose(usbdir);
                        unlink("/mnt/usb1/.dirtest");
                        mkdir("/mnt/usb1/DB_Dackup/", 0777);
                    copyFile("/system_data/priv/mms/app.db", "/mnt/usb1/DB_Dackup/app.db");
                    copyFile("/system_data/priv/mms/addcont.db", "/mnt/usb1/DB_Dackup/addcont.db");
                }
            }
            else
            {
                        fclose(usbdir);
                        unlink("/mnt/usb0/.dirtest");
                        mkdir("/mnt/usb0/DB_Dackup/", 0777);
                    copyFile("/system_data/priv/mms/app.db", "/mnt/usb0/DB_Dackup/app.db");
                    copyFile("/system_data/priv/mms/addcont.db", "/mnt/usb0/DB_Dackup/addcont.db");
            }
    return 0;
}
 
void copyFile(char *sourcefile, char* destfile)
{
    FILE *src = fopen(sourcefile, "r");
    FILE *out = fopen(destfile,"w");
    char buffer[60480];
    size_t bytes;
    while (0 < (bytes = fread(buffer, 1, sizeof(buffer), src)))
            fwrite(buffer, 1, bytes, out);
    fclose(src);
    fclose(out);
}
