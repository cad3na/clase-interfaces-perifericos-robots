%.hex: %.asm
	avra -fI $<
	rm *.eep.hex *.obj *.cof

all: $(patsubst %.asm,%.hex,$(wildcard *.asm))

upload: ${program}.hex
	 sudo avrdude -c arduino -p m328p -P /dev/cu.usbserial-A603QGMH -b 115200 -U flash:w:stepper.hex

monitor:
	picocom --send-cmd "ascii_xfr -s -v -l10" --nolock /dev/cu.usbserial-A603QGMH

.PHONY: all upload monitor
