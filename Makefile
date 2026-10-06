CC=clang
LD=ld.lld

CFLAGS=-ffreestanding -O2 -Wall -Wextra -nostdlib -fno-stack-protector \
       -target x86_64-unknown-none \
       -I third_party/limine \
       -I kernel

LDFLAGS=-T linker.ld -m elf_x86_64

KERNEL=kernel.elf
ISO=nova.iso

all: run

# Build kernel
kernel.o:
	$(CC) $(CFLAGS) -c kernel/main.c -o kernel.o

$(KERNEL): kernel.o
	$(LD) $(LDFLAGS) kernel.o -o $(KERNEL)

# Create ISO
iso: $(KERNEL)
	mkdir -p iso/boot

	cp $(KERNEL) iso/boot/
	cp limine.conf iso/boot/

	cp third_party/limine/limine-bios.sys iso/boot/
	cp third_party/limine/limine-bios-cd.bin iso/boot/
	cp third_party/limine/limine-uefi-cd.bin iso/boot/

	xorriso -as mkisofs \
		-b boot/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image \
		iso -o $(ISO)

run: iso
	qemu-system-x86_64 -cdrom $(ISO) -m 512M
clean:
	rm -rf *.o *.elf iso *.iso
