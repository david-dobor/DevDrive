#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>

#include <asm/uaccess.h>

/*
 * hello_read is the function called when a process calls read() on
 * /dev/hello.  It writes "Hello, world!" to the buffer passed in the
 * read() call.
 */

static ssize_t hello_read(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	char *hello_str = "Hello, world!\n";
	int len = strlen(hello_str);

	if (copy_to_user(buf, hello_str, len))
		return -EINVAL;

	*ppos = len;

	return len;
}

static const struct file_operations hello_fops = {
	.owner		= THIS_MODULE,
	.read		= hello_read,
};

static struct miscdevice hello_dev = {

	MISC_DYNAMIC_MINOR, 	/* let the kernel assign the minor number */

	"hello",   		/* Names itself /dev/hello. */

	&hello_fops
};

static int __init
hello_init(void)
{
	int ret;

	/*
	 * Create the "hello" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.
	 */
	ret = misc_register(&hello_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Hello, world!\" misc device\n");

	return ret;
}

module_init(hello_init);

static void __exit
hello_exit(void)
{
	misc_deregister(&hello_dev);
}

module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Modified by David <david.dobor@gmail.com>. Original: Valerie Henson's hello world module.");
MODULE_DESCRIPTION("\"Hello, world!\" minimal module");
MODULE_VERSION("dev");
