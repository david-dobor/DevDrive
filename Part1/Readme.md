### 1. Create a Linux loopback file system with a regular disk file

+ Do all of the following with root privileges (`sudo su`)
+ Create a 30MB disk file (zero-filled) called `virtualfs` in the root (`/`) directory

        > dd if=/dev/zero of=/virtualfs bs=1024 count=30720
+ Confirm no loopback devices are currently in use by typing:

        > losetup /dev/loop0
        
    ( A loopback device is a pseudo device that acts as a
    block-based device (It is a device driver that makes a regular file accessible
    just like a block device). When mounting a file ( e.g. `disk.iso` ) that will
    act as entire filesystem, use a loopback device. )
        
    The following assumes that `/dev/loop0` is free for use.
    
+ Attach the loopback device `/dev/loop0` with regular disk file `/virtualfs`
  created in step 1
  
        > losetup /dev/loop0 /virtualfs
        
        
    If the previous step is completed successfully, the command `echo $?` 
    should return `0`. 
    
+ Create a Linux EXT3 file system with 1% reserved block count on the loopback
  device by issuing the command:
  
        > mkfs -t ext3 -m 1 -v /dev/loop0 
        
    This creats a file system within file system, that is, a file system (`mkfs`)
    without using a disk partition directly. 
    
+ Create a directory (as mount point) in `/mnt`

        > mkdir /mnt/vfs
        
+ Mount the loopback device (regular disk file) to `/mnt/vfs` as a “regular” 
  Linux EXT3 file system. 
  
        > mount -t ext3 /dev/loop0 /mnt/vfs
        
     _Now, all the Linux file system-related commands can be used on this file
     system._
     
     For example `df -h` confirms the disk usage, or `tune2fs -l /dev/loop0`
     confirms the file system settings, etc.
     
+ To un-mount the loopback file system, type:

        > umount /mnt/vfs
        
     To effectively remove the loopback file system and release loopback 
     device, type :
     
        > losetup -d /dev/loop0
        
        
        