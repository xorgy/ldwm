# ldwm version
VERSION = 6-devel

# Customize below to fit your system

# paths
PREFIX = /usr/pkg
MANPREFIX = ${PREFIX}/man

X11INC = /usr/pkg/X11R6/include
X11LIB = /usr/pkg/X11R6/lib

# includes and libs
INCS = -I${X11INC}
LIBS = -L${X11LIB} -lX11

# flags
CPPFLAGS = -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\"
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = -s ${LIBS}

# compiler and linker
CC = cc
