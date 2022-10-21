BUILD:=../build
SRC:=.

CFLAGS:= -m32
CFLAGS+= -fno-builtin
CFLAGS+= -nostdinc
CFLAGS+= -fno-pic
CFLAGS+= -fno-pie
CFLAGS+= -nostdlib
CFLAGS+= -fno-stack-protector
CFLAGS:=$(strip ${CFLAGS})

DEBUG:= -g
INCLUDE:= -I$(SRC)/include


ENTERPOINT:=0x10000
$(BUILD)/boot/%.bin: $(SRC)/boot/%.asm
	$(shell mkdir -p $(dir $@))
	nasm -f bin $< -o $@  

$(BUILD)/%.o: $(SRC)/%.asm
	$(shell mkdir -p $(dir $@))
	nasm -f elf32 $< -o $@ 

$(BUILD)/%.o: $(SRC)/%.c
	$(shell mkdir -p $(dir $@))
	gcc $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@


$(BUILD)/kernel.bin: $(BUILD)/kernel/start.o \
					$(BUILD)/kernel/main.o \
					$(BUILD)/kernel/io.o \
					$(BUILD)/lib/string.o \
					$(BUILD)/kernel/console.o \
					$(BUILD)/kernel/printk.o \
					$(BUILD)/lib/vsprintf.o \
					$(BUILD)/kernel/assert.o \
					$(BUILD)/kernel/debug.o \
					$(BUILD)/kernel/global.o \
					$(BUILD)/kernel/task.o \
					$(BUILD)/kernel/timer.o \
					$(BUILD)/kernel/schedule.o \
					$(BUILD)/kernel/interrupt.o \
					$(BUILD)/kernel/handler.o \
					$(BUILD)/lib/stdlib.o \
					$(BUILD)/kernel/clock.o \
					

	$(shell mkdir -p $(dir $@))
	ld -m elf_i386 -static $^ -o $@ -Ttext $(ENTERPOINT)

$(BUILD)/system.bin: $(BUILD)/kernel.bin
	objcopy -O binary $< $@

$(BUILD)/system.map: $(BUILD)/kernel.bin
	nm $< | sort > $@ 

$(BUILD)/master.img: $(BUILD)/boot/boot.bin \
					$(BUILD)/boot/loader.bin \
					$(BUILD)/system.bin \
					$(BUILD)/system.map \

	yes | bximage -q -hd -size=16 -mode=flat $@
	dd if=$(BUILD)/boot/boot.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD)/boot/loader.bin of=$@ bs=512 count=4 seek=2 conv=notrunc
	dd if=$(BUILD)/system.bin of=$@ bs=512 count=200 seek=10 conv=notrunc

test: $(BUILD)/master.img

.PHONY: clean
clean: 
	rm -rf $(BUILD)

.PHONY: bochs
bochs: $(BUILD)/master.img
	bochs -q

.PHONY: bochsg
bochsg: $(BUILD)/master.img
	./../bochs/bochs-gdb -q -f ../bochs/bochsrc-gdb
