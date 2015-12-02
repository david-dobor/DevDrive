#include <linux/init.h>
#include <linux/module.h>
#include<linux/sched.h>
#include <linux/slab.h>

#include <linux/fs_struct.h>
#include <linux/dcache.h>
#include <asm/uaccess.h>

#include <linux/fs.h>    	/* for character driver support*/


int (simple_open) (struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return 0;
}
ssize_t (simple_read) (struct file *pfile, char __user *buf, size_t count, loff_t * offset)
{
        printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

ssize_t (simple_write) (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return length;

}

int (simple_close) (struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
  return 0;

}


/* To hold the file operations performed on this device */
struct file_operations ex_file_operations = {
  .owner = THIS_MODULE,
  .open = simple_open,
  .read = simple_read,
  .write = simple_write,
  .release = simple_close,
};

char *cwd;
struct path pwd, root; 
char *buf;

int simple_module_init (void)
{
  printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

  /* register with the kernel and indicate that we are
     registering a character driver */
  register_chrdev(240		/* Major Number */,
		  "Simple Driver" /* Name of the driver */,
		  &ex_file_operations /* File operations */);


//printk("The process is \"%s\" (pid %i)\n",	 current->comm, current->pid);


  pwd = current->fs->pwd;
  path_get(&pwd);
  root= current->fs->root;
  path_get(&root);
  buf = (char *) kmalloc(GFP_KERNEL, 100*sizeof(char));
  cwd = d_path(&pwd, buf, 100*sizeof(char));
  printk(KERN_ALERT "Hello, David. Your current working directory is \n %s", cwd);


  printk(KERN_ALERT "Bye... About to leave function %s \n", __FUNCTION__);

  return 0;
}

void simple_module_exit(void)
{
  printk(KERN_ALERT "Leaving the %s function\n", __FUNCTION__);

  /* Unregister the character device driver */
  unregister_chrdev(240, "Simple Driver");
}

module_init(simple_module_init);
module_exit(simple_module_exit);

MODULE_AUTHOR ("david.dobor@gmail.com");
MODULE_DESCRIPTION ("A simple driver");
MODULE_LICENSE("GPL");
