/* This example monitors udev events for 'block' subsystem using libudev API
			необходимо установить пакет libudev-dev */

#include <stdio.h>
#include <unistd.h>
#include <libudev.h>

int main()
{
	struct udev *udev;
	struct udev_device *dev;
  struct udev_monitor *mon;
	int fd;

	/* create udev object */
	udev = udev_new();
	if (!udev) {
		fprintf(stderr, "Can't create udev\n");
		return 1;
	}

	mon = udev_monitor_new_from_netlink(udev, "udev");
	udev_monitor_filter_add_match_subsystem_devtype(mon, "block", "partition");
	//udev_monitor_filter_add_match_tag(mon, "sdb1");
	udev_monitor_enable_receiving(mon);
	fd = udev_monitor_get_fd(mon);

	while (1) {
		fd_set fds;
		struct timeval tv;
		int ret;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = 0;
		tv.tv_usec = 0;

		ret = select(fd+1, &fds, NULL, NULL, &tv);
		if (ret > 0 && FD_ISSET(fd, &fds)) {
			dev = udev_monitor_receive_device(mon);
			if (dev) {
				printf("I: ACTION=%s\n", udev_device_get_action(dev));
				printf("I: DEVNAME=%s\n", udev_device_get_sysname(dev));
				printf("I: DEVPATH=%s\n", udev_device_get_devpath(dev));
				printf("I: DEVTYPE=%s\n", udev_device_get_devtype(dev));
				printf("I: MACADDR=%s\n", udev_device_get_sysattr_value(dev, "address"));
				printf("---\n");

				/* free dev */
				udev_device_unref(dev);
			}
		}
		/* 500 milliseconds */
		usleep(500*1000);
	}
	/* free udev */
	udev_unref(udev);

	return 0;
}
