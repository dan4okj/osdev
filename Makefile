CC = gcc
CPARAMS = -m32 -I include -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore

AS = as
ASPARAMS = --32

OBJ = arch/loader.o  \
	  mmgt/gdt.o \
	  io/video_mem.o \
	  kernel.o

LDPARAMS = -m elf_i386

%.o: %.c
	$(CC) $(CPARAMS) -o $@ -c $<

%.o: %.s
	$(AS) $(ASPARAMS) -o $@ $<

kernel.bin: linker.ld $(OBJ)	
	ld $(LDPARAMS) -T $< -o $@ $(OBJ)

kernel.iso: kernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	cp ./.buildtools/boot/x86_64/* iso/boot/grub/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $@ iso
	rm -rf iso

run: kernel.iso
	(killall VirtualBox & sleep 1) || true
	VirtualBox --startvm "Osdev" &

install: kernel.bin
	sudo cp $< /boot/kernel.bin

clean:
	rm -f $(OBJ) kernel.bin kernel.iso
