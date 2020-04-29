.PHONY: build flash openocd gdb

build:
	$(MAKE) -f Makefile.chibi

flash: build
	st-flash --reset --format ihex write build/ch.hex

openocd:
	openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg

gdb: build
	arm-none-eabi-gdb -x gdbinit build/ch.elf
