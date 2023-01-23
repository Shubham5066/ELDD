obj-m=ioctl.o
KERN_DIR=/lib/modules/5.15.0-58-generic/build/
PWD=$(shell pwd)
all:
	make -C $(KERN_DIR) M=$(PWD) modules
clean:
	make -C $(KERN_DIR) M=$(PWD) clean
