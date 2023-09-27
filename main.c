#include <gtk/gtk.h>
#include <math.h>

#define CURSOR_SIZE 32

static void activate(GtkApplication* app, gpointer user_data) {
    GdkWindow *root_window = gdk_get_default_root_window();
    GdkDisplay *display = gdk_display_get_default();
    GdkCursor *cursor;

    GdkPixbuf *cursor_pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, CURSOR_SIZE, CURSOR_SIZE);
    guchar *pixels = gdk_pixbuf_get_pixels(cursor_pixbuf);

    for (int y = 0; y < CURSOR_SIZE; y++) {
        for (int x = 0; x < CURSOR_SIZE; x++) {
            int distance = sqrt(pow(x - CURSOR_SIZE / 2, 2) + pow(y - CURSOR_SIZE / 2, 2));
            int pixel_index = (y * CURSOR_SIZE + x) * 4;

            if (distance <= CURSOR_SIZE / 2) {
                pixels[pixel_index + 0] = 255; // Red
                pixels[pixel_index + 1] = 0;   // Green
                pixels[pixel_index + 2] = 0;   // Blue
                pixels[pixel_index + 3] = 255; // Alpha
            } else {
                pixels[pixel_index + 0] = 0;
                pixels[pixel_index + 1] = 0;
                pixels[pixel_index + 2] = 0;
                pixels[pixel_index + 3] = 0;
            }
        }
    }

    cursor = gdk_cursor_new_from_pixbuf(display, cursor_pixbuf, 0, 0);
    gdk_window_set_cursor(root_window, cursor);

    g_object_unref(cursor_pixbuf);
    g_object_unref(cursor);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}






// MAKE YOUR MOUSE STOP WORKING
// #include <stdio.h>
// #include <stdlib.h>
// #include <X11/Xlib.h>
// #include <X11/Xutil.h>
// #include <math.h>
// #include <unistd.h>
//
// #define CURSOR_SIZE 32
// #define TRAIL_LENGTH 10
//
// int main() {
//     Display *display = XOpenDisplay(NULL);
//     if (!display) {
//         fprintf(stderr, "Unable to open X display\n");
//         return 1;
//     }
//
//     Window root = DefaultRootWindow(display);
//
//     XColor cursorColor, trailColors[TRAIL_LENGTH];
//     Colormap colormap = DefaultColormap(display, DefaultScreen(display));
//     XAllocNamedColor(display, colormap, "#66578A", &cursorColor, &cursorColor);
//     
//     // Load trail colors from ~/.cache/wal/colors
//     char *colorStrings[TRAIL_LENGTH] = {
//         "#6E5F95", "#7B6DA9", "#AA6F99", "#8370AF",
//         "#B375A8", "#acbbc7", "#78828b", "#66578A",
//         "#6E5F95", "#7B6DA9"
//     };
//     
//     for (int i = 0; i < TRAIL_LENGTH; i++) {
//         XAllocNamedColor(display, colormap, colorStrings[i], &trailColors[i], &trailColors[i]);
//     }
//
//     XGrabPointer(display, root, False, PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
//
//     while (1) {
//         XEvent event;
//         XNextEvent(display, &event);
//
//         if (event.type == MotionNotify) {
//             XSetForeground(display, DefaultGC(display, DefaultScreen(display)),
//                            cursorColor.pixel);
//
//             for (int i = 0; i < TRAIL_LENGTH; i++) {
//                 int trailX = event.xmotion.x_root - i * 5;
//                 int trailY = event.xmotion.y_root - i * 5;
//
//                 XSetForeground(display, DefaultGC(display, DefaultScreen(display)),
//                                trailColors[i].pixel);
//
//                 XFillArc(display, root, DefaultGC(display, DefaultScreen(display)),
//                          trailX, trailY, CURSOR_SIZE, CURSOR_SIZE, 0, 360 * 64);
//             }
//
//             XFlush(display);
//         }
//     }
//
//     XCloseDisplay(display);
//     return 0;
// }



