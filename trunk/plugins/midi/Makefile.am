DEFS = -I$(top_srcdir) -I$(top_srcdir)/src/include $(LIBGLADE2_CFLAGS)

midi_la_SOURCES = midi.c
midi_la_LDFLAGS = -module -avoid-version $(LIBGLADE2_LFLAGS) -lsimili
mididir = $(plugins_dir)
midi_LTLIBRARIES = midi.la
