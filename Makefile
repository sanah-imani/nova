CC=clang
LD=ld.lld

CFLAGS=-ffreestanding -O2 -Wall -Wextra -nostdlib -fno-stack-protector \
       -target x86_64-unknown-none \
       -mcmodel=kernel \
       -mno-80387 -mno-mmx -mno-sse -mno-sse2 -mno-red-zone \
       -MMD -MP \
       -I third_party/limine \
       -I kernel

LDFLAGS=-T linker.ld -m elf_x86_64

KERNEL=kernel.elf
ISO=nova.iso

SRCS := $(shell find boot kernel -name '*.c')
OBJS := $(patsubst %.c,build/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all iso run clean

all: run

# Compile each source file into build/
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Link all objects
$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KERNEL)

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
	rm -rf build *.elf iso *.iso

-include $(DEPS)
