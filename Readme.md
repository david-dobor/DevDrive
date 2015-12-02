### A Simple Linux Device Driver

+ `Part1` just lists the steps to follow to create a file system within a file.

+ `HelloDev` directory has the module that creates the device named `/dev/hello` 
   that will print "Hello, world!" to console when read by root.
   
     * Steps to compile, load, check output, and remove modules:

              cd HelloDev
              make                  
              sudo insmod hello_dev.ko  # insert the module
              
     * Now there is a device named `/dev/hello` that will produce 
       "Hello, world!" when read by root: 
       
              sudo cat /dev/hello
              Hello, world!

+ `SimpleDriver` dirctory has the simple driver that also outputs
   information (like the current working directory) to the kernel log.
   
+ Steps to compile, load, check output, and remove modules (assume `simple.ko` is the name of the compiled module; each directory contains the needed `Makefile`):

        make                   # compile the module 
        sudo insmod simple.ko  # insert the module
        dmesg                  # check the log buffer to see the outuput
        sudo rmmod simple      # remove the module
        #sudo dmesg -c         # clears the kernel log
   