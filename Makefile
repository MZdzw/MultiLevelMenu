MCU=atmega32
F_CPU=1000000
IDIR =./inc
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I$(IDIR)
TARGET=Main

ODIR=./src

_DEPS = LCD.h Menu.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = LCD.o Menu.o Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

${TARGET}.bin: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

.Phony: flash

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
