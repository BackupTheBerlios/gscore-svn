libgscorespacingsincludedir = $(includedir)/gscore/libgscorespacings

DEFS = 	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"

INCLUDES = 		\
	-I$(top_srcdir) \
	$(GLIB_CFLAGS)  \
	-I$(includedir)

lib_LTLIBRARIES = libgscorespacings.la

libgscorespacings_sources = 		\
			spacings.c

libgscorespacings_la_SOURCES = $(libgscorespacings_sources)

libgscorespacingsinclude_HEADERS = 	\
			spacings.h

libgscorespacings_la_LIBADD = $(GLIB_LIBS)
