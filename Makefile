FLAGS?=-Wall -g

all:
	$(CC) $(CFLAGS) xwin.c -I/usr/include/X11 -L/usr/lib/i386-linux-gnu -lX11 -o xwin

clean:
	rm -f xwin

