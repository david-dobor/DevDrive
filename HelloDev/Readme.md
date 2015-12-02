## Hello World Device Driver

+ First, implement "Hello, World!" using a device file in `/dev`. 
  Name of this file: `/dev/hello_world`. The program is `hello_dev.c`.

+ The current version of `/dev` support is called `udev` - it creates
 `/dev` links with a userspace program. When kernel modules register
  devices, they appear in the `sysfs` filesystem, mounted on `/sys`. 
  A userspace program, udev, notices changes in `/sys` and dynamically 
  creates `/dev` entries according to a set of rules usually located in `/etc/udev/`.
  
+ Creating a device reqires quite a bit of kernel support: 
      * `fs.h` includes the 
         definitions for a file operations structure, which must be filled out and 
         attached to our `/dev` file. 
      * `miscdevice.h` includes support for registering a miscellaneous device file.
      * `asm/uaccess.h` includes functions for testing whether we can read or write 
         to userspace memory without violating permissions.
         
+ `hello_read()` is the function called when a process calls `read()` on `/dev/hello`. 
   It writes "Hello, world!" to the buffer passed in the `read()` call.
   
   
+ Create a file operations struct defining what actions to take when the file is accessed. 
  The only file operation we care about is `read`.
  
+ Create the structure containing the information needed to register a miscellaneous device 
  with the kernel.
  
+ Register the device in the module's initialization function.

+ Finally, remember to unregister the device in the exit function.

+  [Reference](http://www.linuxdevcenter.com/lpt/a/7060)

   