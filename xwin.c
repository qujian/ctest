#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>


Window
create_simple_window(Display* display, int width, int height, int x, int y)
{
  int screen_num = DefaultScreen(display);
  int win_border_width = 2;
  Window win;
  win = XCreateSimpleWindow(display, RootWindow(display, screen_num),
                            x, y, width, height, win_border_width,
                            BlackPixel(display, screen_num),
                            WhitePixel(display, screen_num));
  XMapWindow(display, win);
  XFlush(display);
  return win;
}

GC
create_gc(Display* display, Window win, int reverse_video)
{
  GC gc; 
  unsigned long valuemask = 0; 
  XGCValues values; /* initial values for the GC. */
  gc = XCreateGC(display, win, valuemask, &values);
  if (gc < 0) {
        fprintf(stderr, "XCreateGC: \n");
  }
  return gc;
}

void
main(int argc, char* argv[])
{
  Display* display; 
  int screen_num; 
  Window win; 
  unsigned int display_width,
               display_height; 
  unsigned int width, height; 
  char *display_name = getenv("DISPLAY"); 
  GC gc; 
  Colormap screen_colormap; 
  XColor blue;
  Status rc; 
  display = XOpenDisplay(display_name);
  screen_num = DefaultScreen(display);
  display_width = DisplayWidth(display, screen_num);
  display_height = DisplayHeight(display, screen_num);

  width = (display_width / 3);
  height = (display_height / 3);
  
  win = create_simple_window(display, width, height, 0, 0);

  gc = create_gc(display, win, 0);
  XSync(display, False);

  screen_colormap = DefaultColormap(display, DefaultScreen(display));

  rc = XAllocNamedColor(display, screen_colormap, "blue", &blue, &blue);
  
  XSetForeground(display, gc, blue.pixel);
  XDrawArc(display, win, gc, 100-(30/2), 50-(50/2), 30, 30, 0, 360*64);

     XFlush(display);
       sleep(10); 
   XCloseDisplay(display); 

}
