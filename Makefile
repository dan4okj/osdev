CC = gcc
CPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore

AS = as
ASPARAMS = --32

OBJ = loader.o gdt.o video_mem.o kernel.o
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
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: kernel.iso
	(killall VirtualBox & sleep 1) || true
	VirtualBox --startvm "Osdev" &

install: kernel.bin
	sudo cp $< /boot/kernel.bin

clean:
	rm -f $(OBJ) kernel.bin kernel.iso
