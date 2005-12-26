libgscorebase     = $(top_build_dir)/libgscorebase/libgscorebase-$(GSCORE_API_VERSION).la

libgscorespacingsincludedir = $(includedir)/gscore-$(GSCORE_API_VERSION)/libgscorespacings

INCLUDES = 		\
	-I$(top_srcdir) \
	$(GLIB_CFLAGS)  \
	-I$(includedir)

lib_LTLIBRARIES = libgscorespacings-$(GSCORE_API_VERSION).la

# libgscorespacings_sources = \
# 			\

libgscorespacings_1_0_la_SOURCES = $(libgscorespacings_sources)

# libgscorespacingsinclude_HEADERS = \

libgscorespacings_1_0_la_DEPENDENCIES = $(libgscorebase)

libgscorespacings_1_0_la_LIBADD = $(GLIB_LIBS)
