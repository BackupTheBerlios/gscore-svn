#libgscorebase     = $(top_srcdir)/libgscorebase/libgscorebase.la
libgscore         = ./libgscore.la

INCLUDES =			\
	$(WARN_CFLAGS) 		\
	$(DEPRECATED_FLAGS)	\
	-I$(top_srcdir) 	\
	$(GLIB2_CFLAGS)   	\
	-I$(includedir)

lib_LTLIBRARIES = libgscore.la 

libgscore_la_LIBADD = $(libgscorebase)

libgscore_la_SOURCES = \
			gscoretypes.h

libgscoreincludedir = $(includedir)/gscore/libgscore
libgscoreinclude_HEADERS = 		\
		constants.h		\
		datastructures.h 	\
		gscoretypes.h		\
		macros.h

#libgscore_la_DEPENDENCIES = $(libgscorebase)

extra_DIST = \
	$(gscoreinclude_HEADERS)


