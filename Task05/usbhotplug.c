#include <linux/module.h>
#include <linux/usb.h>
#include <linux/hid.h>
#include <linux/kernel.h>

static struct usb_device_id usbhotplug_table[] = {

	{ USB_INTERFACE_INFO(
			USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{ }
};

MODULE_DEVICE_TABLE(usb,usbhotplug_table);

static int usbhotplug_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	printk(KERN_INFO"usbhotplug probe !!\n");
	return 0;
}

static void usbhotplug_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO"usbhotplug disconnect\n");
}

static struct usb_driver usbhotplug_driver = {
	.name = "usbhotplug",
	.probe = usbhotplug_probe,
	.disconnect = usbhotplug_disconnect,
	.id_table = usbhotplug_table,
};

static int __init usbhotplug_init(void)
{
	int ret;
	ret = usb_register(&usbhotplug_driver);
	if(ret < 0){
		printk(KERN_ERR"unable to register usbhotplug driver %d\n",ret);
		return ret;
	}
	printk(KERN_INFO"usbhotplug driver registered\n");
	return 0;
}
static void __exit usbhotplug_exit(void)
{
	usb_deregister(&usbhotplug_driver);
	printk(KERN_INFO"usbhotplug deregistered\n");

}

module_init(usbhotplug_init);
module_exit(usbhotplug_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("himanshu");
MODULE_DESCRIPTION("USB Keyboard hotplug module");
