lib_LTLIBRARIES = libgscore.la
include_HEADERS = libgscore.h
 
libgscore_la_SOURCES = \
	scorewidget.c \
	scorewidget.h \
	gdkcairo.h \
	gdkcairo.c

libgscore_la_LDFLAGS = -version-info @VERSION_INFO@

INCLUDES = $(CAIRO_CFLAGS)

libgscore_la_LIBADD = $(CAIRO_LIBS)

