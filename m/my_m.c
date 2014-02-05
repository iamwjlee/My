/*
	device driver
	- no main function
	- can not use standard c-library
	make device driver file(*.ko)
	lsmod
	insmod my_m.ko
	dmesg
	rmmod my_m.ko
	dmesg


	+register /dev for virtual file system
	mknod /dev/my_m c 250 0
	+register kernel
	insmod my_m.ko

	cat > /dev/my_m
	1234 {enter}
	{ctrl-d}
	cat /dev/my_m
	{ctrl-c}

http://forum.falinux.com/zbxe/index.php?document_srl=406200&mid=device_driver


*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <asm/uaccess.h>  //for copy_to_user
#include <linux/slab.h>  //for kmalloc kfree

#define  BUFF_SIZE      64
#define  MAJOR_NUMBER   250

static char *buffer  = NULL;
static int   sz_data = 0;

static int my_open(struct inode *inode, struct file *filp)
{
	printk("opened");
	return 0;
}
static int my_release(struct inode *inode, struct file *filp)
{
	printk("released");
	return 0;
}

static ssize_t my_write( struct file *filp, const char *buf, size_t count, loff_t *f_pos )
{
   printk( "[VB] write to buffern");

   if (BUFF_SIZE < count)  sz_data  = BUFF_SIZE;
                           sz_data  = count;

   strncpy( buffer, buf, sz_data);
   return count;
}

static ssize_t my_read( struct file *filp, char *buf, size_t count, loff_t *f_pos )
{
  printk( "[VB] read from buffern" );
  copy_to_user( buf, buffer, sz_data);

  return sz_data;
}

static struct file_operations vd_fops = {
  .read = my_read,
  .write = my_write,
  .open = my_open,
  .release = my_release
};

static int my_m_init(void)
{
	register_chrdev( MAJOR_NUMBER, "virtual_buffer", &vd_fops );
  buffer = (char*) kmalloc( BUFF_SIZE, GFP_KERNEL );
  memset( buffer, 0, BUFF_SIZE);
	printk(" 2014-02-05 my module test\n");
	return 0;
}
static void my_m_exit(void)
{
	  unregister_chrdev( MAJOR_NUMBER, "virtual_buffer" );
  kfree( buffer );
	printk(" 2014-02-05 my module exit\n");
}
module_init(my_m_init);
module_exit(my_m_exit);
MODULE_LICENSE("Dual BSD/GPL");
