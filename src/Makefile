CC=gcc
CFLAGS= -g -Wall -L/os/lib
LIBS = -limobiledevice -lplist -lusbmuxd -lsn0wcore
TARGET=info
SOURCES=info.c \
        device.c \
        lockdown.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm $(TARGET)
