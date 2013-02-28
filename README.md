ldwm - less dynamic window manager
============================
ldwm is an extremely fast, small, and dynamic window manager for X, reduced from dwm.

This fork of dwm was hacked together to integrate one patch(shiftview), and cut out any graphical components, if you feel there are any graphical components left in this branch please let me know.
It is also my intention to develop some original functionality, such as rotating the master area to different sides of the screen.


Requirements
------------
In order to build ldwm you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (ldwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install ldwm (if
necessary as root):

    make clean install


Running ldwm
-----------
Add the following line to your .xinitrc to start ldwm using startx:

    exec ldwm

In order to connect ldwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec ldwm

(This will start ldwm on display :1 of the host foo.bar.)

Configuration
-------------
The configuration of ldwm is done by creating a custom config.h
and (re)compiling the source code.
