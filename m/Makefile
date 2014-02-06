
ifneq ($(KERNELRELEASE),)
a : aa
else
endif

obj-m 	:= my_m.o



KDIR	= /lib/modules/$(shell uname -r)/build
PWD 	= $(shell pwd)

all : default aa
default :
	$(MAKE) -C $(KDIR) M=$(PWD) modules
##	$(MAKE) -C $(KDIR) M=$(PWD) modules

in :
	sudo insmod my_m.ko
	sudo chmod 666 /dev/my_m
	echo  abcdefg > /dev/my_m


aa: 
	@echo wj_test

clean :
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf *.order
	rm -rf *.symvers
	rm -rf .tmp_versions
	sudo rmmod my_m
