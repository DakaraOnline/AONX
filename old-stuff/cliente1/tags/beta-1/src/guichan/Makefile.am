INCLUDES = -I$(top_srcdir)/include
METASOURCES = AUTO
SUBDIRS = sdl opengl widgets
noinst_LTLIBRARIES = libguichan.la
libguichan_la_SOURCES = actionevent.cpp basiccontainer.cpp cliprectangle.cpp \
	color.cpp defaultfont.cpp event.cpp exception.cpp focushandler.cpp font.cpp \
	genericinput.cpp graphics.cpp guichan.cpp gui.cpp image.cpp imagefont.cpp inputevent.cpp \
	key.cpp keyevent.cpp keyinput.cpp mouseevent.cpp mouseinput.cpp rectangle.cpp \
	widget.cpp
AM_CFLAGS = $(LIBSDL_CFLAGS)
