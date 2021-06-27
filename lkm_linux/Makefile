moduleName = my_dummy_device
obj-m := $(addsuffix .o, &(moduleName))

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
		make -C $(KDIR) -M=$(PWD) modules
clean:
		make -C $(KDIR) -M=$(PWD) clean