#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <thread>
#include <atomic>
std::atomic<bool> clicking(false);
void clicker(int interval_ms) {
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display." << std::endl;
        return;
    }
    while (clicking) {
        Window root;
        int x, y;
        unsigned int mask;
        XQueryPointer(display, DefaultRootWindow(display), &root, &root, &x, &y, &x, &y, &mask);
        XEvent event;
        event.xbutton.type = ButtonPress;
        event.xbutton.display = display;
        event.xbutton.window = root;
        event.xbutton.root = root;
        event.xbutton.x = x;
        event.xbutton.y = y;
        event.xbutton.x_root = x;
        event.xbutton.y_root = y;
        event.xbutton.subwindow = None;
        event.xbutton.button = 1; // left button (normal click)
        event.xbutton.same_screen = True;

        XSendEvent(display, PointerWindow, True, 
                   ButtonPressMask | ButtonReleaseMask, &event); // press mouse
        event.xbutton.type = ButtonRelease;
        XSendEvent(display, PointerWindow, True, ButtonPressMask | ButtonReleaseMask, &event); // unpress mouse

        std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms)); // waits to click
    }

    XCloseDisplay(display); // closes display
}

int main() {
    int interval_ms;
    std::cout << "Enter click interval in milliseconds: ";
    std::cin >> interval_ms;

    char input;
    std::cout << "Press 's' to start/stop clicking and 'e' to exit." << std::endl;

    while (true) {
        if (std::cin >> input) {
            if (input == 's') {
                clicking = !clicking; // toggles clicking
                if (clicking) {
                    std::thread(clicker, interval_ms).detach(); // starts clicking 
                    std::cout << "Clicking started." << std::endl;
                } else {
                    std::cout << "Clicking stopped." << std::endl;
                }
            } else if (input == 'e') {
                clicking = false; // stops clicking
                break; // breaks loop
            }
        }
    }

    std::cout << "Exiting program." << std::endl;
    return 0;
}