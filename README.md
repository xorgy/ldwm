jwm - dynamic window manager
============================
jwm is an extremely fast, small, and dynamic window manager for X, derived from dwm.

This fork of dwm was hacked together to integrate one patch(shiftview), and cut out any graphical components, if you feel there are any graphical components left in this branch please let me know.
It is also my intention to develop some original functionality, such as rotating the master area to different sides of the screen.


Requirements
------------
In order to build jwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (jwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install jwm (if
necessary as root):

    make clean install

If you are going to use the default bluegray color scheme it is highly
recommended to also install the bluegray files shipped in the dextra package.


Running jwm
-----------
Add the following line to your .xinitrc to start jwm using startx:

    exec jwm

In order to connect jwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec jwm

(This will start jwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of jwm is done by creating a custom config.h
and (re)compiling the source code.
