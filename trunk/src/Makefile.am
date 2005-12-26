libgscore = $(top_srcdir)/libgscore/libgscore.la

SUBDIRS =

DEFS = \
	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"		\
	-I$(top_srcdir)/ 	\
	-I$(srcdir)/include/	\
	$(GLIB2_CFLAGS)

bin_PROGRAMS = gscore
gscore_LDFLAGS = -export-dynamic
gscore_LDADD = $(GLIB2_LIBS) ../libgscore/libgscore.la ../libgscorebase/libgscorebase.la

gscore_SOURCES = \
		main.c
