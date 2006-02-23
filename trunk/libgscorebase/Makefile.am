libgscorebaseincludedir = $(includedir)/gscore/libgscorebase

DEFS = 	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"

INCLUDES = 		\
	-I$(top_srcdir) \
	$(GLIB2_CFLAGS) \
	-I$(includedir)

lib_LTLIBRARIES = libgscorebase.la

libgscorebase_sources = 			\
			display.c		\
			identity.c		\
			object.c 		\
			object-color.c 		\
			score.c 		\
			selection-area.c  	\
			staff.c

libgscorebase_la_SOURCES = $(libgscorebase_sources)

libgscorebaseinclude_HEADERS = 			\
			display.h		\
			identity.h 		\
			object.h		\
			object-color.h 		\
			score.h 		\
			selection-area.h	\
			staff.h

libgscorebase_la_LIBADD = $(GLIB2_LIBS)
