#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "msdos_fs.h"

// reading the microsoft FAT-12 filesystem in Linux
int main(int argc, char *argv[])
{
    printf("FAT-12 Filesystem Reader\n");
    int cmd = cmd_check(argc, argv);
    if (cmd == 0)
        return 0;

    struct DOSBootRecord * boot_record;
    struct DOSDirEntry * root_dir;
    struct DOSFile * file;

    //
    if (cmd == 1)
        read_floppy_image_FAT12(argv[1], boot_record, root_dir, file);
        cmd_dir();
        printf("Directory Listing\n");
    if (cmd == 2)
        read_floppy_image_FAT12(argv[1], boot_record, root_dir, file);
        cmd_cp(argc, argv);
        mount_file();
        printf("File Mounted\n");


    return 0; 
}
// read the floppy image file FAT-12 filesystem
int read_floppy_image_FAT12(char * filename, struct DOSBootRecord * boot_record, struct DOSDirEntry * root_dir, struct DOSFile * file)
{
    
}
//Disply a listing of floppy root directory
int cmd_dir()
{
    printf("Directory Listing\n");
    return 0;
} 

//copy a file from the floppy image to the Linux filesystem
int cmd_cp(int argc, char *argv[])
{
    printf("Copying File\n");
    return 0;
}
//Mount a file from the floppy image to the Linux filesystem
int mount_file()
{
    printf("File Mounted\n");
    return 0;
}



int cmd_check(int argc, char *argv[]) // check if the command is valid
{
    // check if the command is valid
    if (argc>4) 
    {
            printf("error: to many input arguments\n"); // check if the command is valid
            return 0;
    }
    if (argc<2)
    {
            printf("error: to few input arguments\n"); // check if the command is valid
            return 0;
    } 
    

    char *filename = argv[0];
    if (access(filename, F_OK) == -1) 
    {
            printf("error: img file does not exist\n"); // check if the command is valid
            return 0;
    }

    if (argc == 2)
        if (strcmp(argv[1],"dir"))
            return 1;
    if (argc == 4)
        if (strcmp(argv[1],"cp"))
        return 2;

    printf("error: invalid command\n"); // check if the command is valid
    return 0;
}



