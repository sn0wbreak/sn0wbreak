CC=gcc
CFLAGS= -g -Wall
LIBS = -limobiledevice -lplist -lusbmuxd
TARGET=info
SOURCES=info.c \
        device.c \
        lockdown.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm $(TARGET)
