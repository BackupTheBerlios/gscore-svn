lib_LTLIBRARIES = libgscore.la
include_HEADERS = libgscore.h \
	scorewidget/gdkcairo.h \
	scorewidget/scorewidget.h

libgscore_la_SOURCES = \
	scorewidget/scorewidget.c \
	scorewidget/scorewidget.h \
	scorewidget/gdkcairo.h \
	scorewidget/gdkcairo.c

# libgscore_la_LDFLAGS = -version-info "0.1"

INCLUDES = $(CAIRO_CFLAGS) $(LIBGLADE2_CFLAGS)

libgscore_la_LIBADD = $(CAIRO_LIBS) $(LIBGLADE2_LIBS)

