libgscorebaseincludedir = $(includedir)/gscore/libgscorebase

DEFS = 	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"

INCLUDES = 		\
	-I$(top_srcdir) \
	$(GLIB2_CFLAGS) \
	-I$(includedir)

lib_LTLIBRARIES = libgscorebase.la

libgscorebase_sources = 		\
			identity.c 	\
			object_color.c 	\
			score.c 	\
			selection.c 

libgscorebase_la_SOURCES = $(libgscorebase_sources)

libgscorebaseinclude_HEADERS = 			\
			display.h		\
			identity.h 		\
			object.h		\
			object_color.h 		\
			score.h 		\
			selection.h		\
			staff.h

libgscorebase_la_LIBADD = $(GLIB2_LIBS)
