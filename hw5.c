#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

#include "msdos_fs.h"
#include "hw5.h"

struct fat_boot_sector *boot_record;
struct fat_boot_fsinfo *fs_info;
struct msdos_dir_entry *root_dir;
struct msdos_dir_slot *dir_slot;

// reading the microsoft FAT-12 filesystem in Linux
int main(int argc, char *argv[])
{
    int cmd;
    int output;
    printf("FAT-12 Filesystem Reader\n");
    cmd = cmd_check(argc, argv);
    if (cmd == 0)
        return 0;


    //
    if (cmd == 1)
    {
        output = read_floppy_image_FAT12(argv[1], boot_record, fs_info, root_dir, dir_slot);
        //cmd_dir();
    }
    if (cmd == 2)
    {
        //output = read_floppy_image_FAT12(argv[1], boot_record, root_dir, file);
        //cmd_cp(argc, argv);
        //mount_file();
    }


    return 0; 
}
// read the floppy image file FAT-12 filesystem
int read_floppy_image_FAT12(char *filename, struct fat_boot_sector *boot_record, struct fat_boot_fsinfo *fs_info, struct msdos_dir_entry *root_dir, struct msdos_dir_slot *dir_slot)
{
    printf("Reading FAT-12 Filesystem\n");
    // open the floppy image file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("error: failed to open floppy image file\n");
        return 0;
    }
    printf("File Opened\n");
    // read the reserved region and the boot sector
    boot_record = malloc(sizeof(struct fat_boot_sector));
    fread(boot_record, sizeof(struct fat_boot_sector), 1, fp);
    printf("Boot Record Read\n");
    // read the FAT region
    fs_info = malloc(sizeof(struct fat_boot_fsinfo));
    fread(fs_info, sizeof(struct fat_boot_fsinfo), 1, fp);
    printf("FS Info Read\n");
    // read the root directory region
    root_dir = malloc(sizeof(struct msdos_dir_entry));
    fread(root_dir, sizeof(struct msdos_dir_entry), 1, fp);
    printf("Root Directory Read\n\n");
    // read the data region
    dir_slot = malloc(sizeof(struct msdos_dir_slot));
    fread(dir_slot, sizeof(struct msdos_dir_slot), 1, fp);
    
    // print the reserved region and the boot sector
    printf("Data Region Read:\n");
    printf("BS_jmpBoot: 0x%x 0x%x 0x%x\n", boot_record->ignored[0], boot_record->ignored[1], boot_record->ignored[2]);
    printf("BS_OEMName: %s\n", boot_record->system_id);
    // print 2 bytes of the sector size in int format
    printf("BPB_BytsPerSec: %d\n", boot_record->sector_size[0] + boot_record->sector_size[1]*256);
    printf("BPB_SecPerClus: %d\n", boot_record->sec_per_clus);
    printf("BPB_RsvdSecCnt: %d\n", boot_record->reserved);
    printf("BPB_NumFATs: %d\n", boot_record->fats);
    // print 2 bytes of the root directory entries in int format
    printf("BPB_RootEntCnt: %d\n", boot_record->dir_entries[0] + boot_record->dir_entries[1]*256);
    // print 2 bytes of the sectors in int format
    printf("BPB_TotSec16: %d\n", boot_record->sectors[0] + boot_record->sectors[1]*256);
    printf("BPB_Media: 0x%x\n", boot_record->media);
    printf("BPB_FATSz16: %d\n", boot_record->fat_length);
    printf("BPB_SecPerTrk: %d\n", boot_record->secs_track);
    printf("BPB_NumHeads: %d\n", boot_record->heads);
    printf("BPB_HiddSec: %d\n", boot_record->hidden);
    printf("BPB_TotSec32: %d\n\n", boot_record->total_sect);
    
       
    // print the FAT region
    printf("FAT Region:\n");
    // print 4 bytes of the FAT signature in int format
    printf("FAT Signature1: 0x%8x\n", fs_info->signature1);
    // print 4 bytes of the FAT signature in int format
    printf("FAT Signature2: 0x%8x\n", fs_info->signature2);
    printf("Free Cluster Count: %d\n", fs_info->free_clusters);
    printf("Most Recently Allocated Cluster: 0x%8x\n\n", fs_info->next_cluster);

    // print the root directory region
    printf("Root Directory Region:\n");
    printf("File Name: %s\n", root_dir->name);
    printf("File Size: %d\n", root_dir->size);
    printf("File Attributes: %d\n", root_dir->attr);
    printf("File Creation Time: %d\n", root_dir->ctime);
    printf("File Creation Date: %d\n", root_dir->cdate);
    printf("File Last Access Date: %d\n", root_dir->adate);
    printf("File Starting Cluster: %d\n\n", root_dir->start);

    // print the data region
    printf("Data Region:\n");

    int index = 0;
    while(1)
    {
        fread(dir_slot, sizeof(struct msdos_dir_slot), 1, fp);
        if (dir_slot->id == 0 || feof(fp))
            break;
        printf("File Id: %d\n", dir_slot->id);
        printf("File Name: %x%x%x\n", dir_slot->name0_4, dir_slot->name5_10, dir_slot->name11_12);
        printf("File Attributes: %d\n", dir_slot->attr);
        printf("File reserved: %d\n", dir_slot->reserved);
        printf("File alias checksum: %d\n", dir_slot->alias_checksum);
        printf("File Starting Cluster: %d\n\n", dir_slot->start);
        index++;
    }
    printf("Number of Files: %d\n", index);
    // close the floppy image file
    fclose(fp);
    return 0;


    
}
//Disply a listing of floppy root directory
int cmd_dir(int argc, char *argv[])
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
    printf("Checking Command\n");

    // check if the command is valid
    if (argc>5) 
    {
            printf("error: to many input arguments\n"); // check if the command is valid
            return 0;
    }
    if (argc<3)
    {
            printf("error: to few input arguments\n"); // check if the command is valid
            return 0;
    } 
    

    char *filename = argv[1];
    if (access(filename, F_OK) == -1) 
    {
            printf("error: img file does not exist\n"); // check if the command is valid
            return 0;
    }

    if (argc == 3)
            if (strcmp(argv[2],"dir\n"))
                return 1;
    if (argc == 5)
        if (strcmp(argv[2],"cp"))
        return 2;

    printf("error: invalid command\n"); // check if the command is valid
    return 0;
}



