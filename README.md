dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.

This branch
-----------

This branch of dwm was hacked together to integrate one patch(shiftview), and cut out any graphical components, if you feel there are any graphical components left in this branch please let me know.
It is also my intention to develop some original functionality, such as rotating the master area to different sides of the screen.


Requirements
------------
In order to build dwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install

If you are going to use the default bluegray color scheme it is highly
recommended to also install the bluegray files shipped in the dextra package.


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
