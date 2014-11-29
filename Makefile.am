AUTOMAKE_OPTIONS = foreign

lib_LIBRARIES = libcore.a libWire.a
bin_PROGRAMS = main.elf main.eep main.hex

CFLAGS = -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p
CXXFLAGS = -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p
CPPFLAGS = -MMD -DF_CPU=16000000L -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -I/usr/share/arduino/hardware/arduino/variants/standard
LDFLAGS = -Os -Wl,--gc-sections -mmcu=atmega328p

#
# libcore.a
#
libcore_adir = $(includedir)
libcore_a_SRCDIR = /usr/share/arduino/hardware/arduino/cores/arduino
libcore_a_CPPFLAGS = -I$(libcore_a_SRCDIR)
libcore_a_SOURCES = $(libcore_a_SRCDIR)/wiring_digital.c \
	$(libcore_a_SRCDIR)/wiring_pulse.c \
	$(libcore_a_SRCDIR)/wiring.c \
	$(libcore_a_SRCDIR)/WInterrupts.c \
	$(libcore_a_SRCDIR)/wiring_analog.c \
	$(libcore_a_SRCDIR)/wiring_shift.c \
	$(libcore_a_SRCDIR)/HID.cpp \
	$(libcore_a_SRCDIR)/Stream.cpp \
	$(libcore_a_SRCDIR)/Tone.cpp \
	$(libcore_a_SRCDIR)/WString.cpp \
	$(libcore_a_SRCDIR)/USBCore.cpp \
	$(libcore_a_SRCDIR)/WMath.cpp \
	$(libcore_a_SRCDIR)/new.cpp \
	$(libcore_a_SRCDIR)/main.cpp \
	$(libcore_a_SRCDIR)/IPAddress.cpp \
	$(libcore_a_SRCDIR)/CDC.cpp \
	$(libcore_a_SRCDIR)/HardwareSerial.cpp \
	$(libcore_a_SRCDIR)/Print.cpp

#
# libWire.a
#
libWire_adir = $(includedir)
libWire_a_SRCDIR = /usr/share/arduino/libraries/Wire
libWire_a_CPPFLAGS = -I$(libWire_a_SRCDIR) -I$(libWire_a_SRCDIR)/utility -I$(libcore_a_SRCDIR)
libWire_a_SOURCES = $(libWire_a_SRCDIR)/Wire.cpp $(libWire_a_SRCDIR)/utility/twi.c

#
# main
#
main_elf_SOURCES = src/main.cpp
main_elf_CPPFLAGS = -I$(srcdir)/src -I$(libWire_a_SRCDIR) -I$(libcore_a_SRCDIR)
main_elf_LDADD = libWire.a libcore.a

main_hex_SOURCES = 
main_hex_DEPENDENCIES = main.elf
main_hex_LINK = avr-objcopy -O ihex -R .eeprom main.elf $@

main_eep_SOURCES =
main_eep_DEPENDENCIES = main.elf
main_eep_LINK = avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 main.elf main.eep

build: all-am
.PHONY: build


UPLOAD_DEVICE = /dev/ttyACM0
upload:
	avrdude -C/usr/share/arduino/hardware/tools/avrdude.conf -v -patmega328p -carduino -P$(UPLOAD_DEVICE) -b115200 -D -Uflash:w:main.hex:i
.PHONY: upload

console:
	minicom -b 38400 -D $(UPLOAD_DEVICE)
.PHONY: console

deploy: build upload console
.PHONY: deploy

