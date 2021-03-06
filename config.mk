# dwm patched local version, Archlinux
VERSION = 6.1

# Customize below to fit your system

# paths ~/.dotfiles
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/include/X11
X11LIB = /usr/lib/X11

# Xinerama, comment if you don't want it
# XINERAMALIBS  = -lXinerama
# XINERAMAFLAGS = -DXINERAMA

# Xft
XFTLIBS = `pkg-config --libs xft`
XFTFLAGS = `pkg-config --cflags xft`

# includes and libs
INCS = -I${X11INC}
LIBS = -L${X11LIB} -lX11 ${XFTLIBS} ${XINERAMALIBS}

# flags
CPPFLAGS = -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\" ${XFTFLAGS} # ${XINERAMAFLAGS}
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -O2 ${INCS} ${CPPFLAGS}
LDFLAGS  = -s ${LIBS}

# compiler and linker
CC = cc
