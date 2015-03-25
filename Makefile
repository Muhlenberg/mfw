obj-m += mfmod.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shall uname -r)/build M=$(PWD) clean
