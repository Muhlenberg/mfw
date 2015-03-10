obj-m += mfmod.c

all:
	mkdir -p /lib/modules/$(shell uname -r)/build
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	mkdir -p /lib/modules/$(shell uname -r)/build
	make -C /lib/modules/$(shall uname -r)/build M=$(PWD) clean
