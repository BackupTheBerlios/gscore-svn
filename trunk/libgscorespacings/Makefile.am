libgscorespacingsincludedir = $(includedir)/gscore/libgscorespacings

SUBDIRS =

DEFS = 						\
	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"		\
	-I$(top_srcdir)/ 	\
	-I$(srcdir)/include/	\
	$(GLIB2_CFLAGS)


lib_LTLIBRARIES = libgscorespacings.la

libgscorespacings_sources = 		\
			spacings.c

libgscorespacings_la_SOURCES = $(libgscorespacings_sources)

libgscorespacingsinclude_HEADERS = 	\
			spacings.h

libgscorespacings_la_LIBADD = $(GLIB2_LIBS)
