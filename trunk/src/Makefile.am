SUBDIRS = 

DEFS = -I$(top_srcdir)/ -I$(srcdir)/include/	\
	-I$(top_srcdir)/libgscore 		\
	-I$(top_srcdir)/libgscore/scorewidget	\
	-DPLUGINS_DIR=\"$(plugins_dir)\"	\
	-DDATA_DIR=\"$(datadir)\"		\
	$(LIBGLADE2_CFLAGS) $(CAIRO_CFLAGS)

bin_PROGRAMS = gscore
gscore_LDFLAGS = -export-dynamic
gscore_LDADD = $(LIBGLADE2_LIBS) $(CAIRO_LIBS) -lgscore

gscore_SOURCES =				\
	articulation.c				\
	beam.c					\
	common.c				\
	chords.c				\
	debug.c					\
	display.c				\
	draw_barline.c				\
	draw_staff.c 				\
	draw_key.c				\
	draw_key_signature.c			\
	draw_note_rest.c			\
	draw_pitch_cursor.c			\
	draw_time_signature.c			\
	draw.c					\
	edit.c					\
	error.c					\
	file.c					\
	help.c					\
	include					\
	insert.c				\
	key_cursor.c				\
	key_event.c				\
	layout-engine.c				\
	libglade-garbage.c			\
	main.c					\
	Makefile.am				\
	mode.c					\
	mouse_event.c				\
	notes.c					\
	objects.c				\
	objects_callbacks.c			\
	pitch_cursor.c				\
	plugin.c				\
	position.c				\
	realize_area.c				\
	rests.c					\
	score.c					\
	score_callbacks.c			\
	score-object-manager.c 			\
	selection.c				\
	spacings.c				\
	splash.c				\
	staff.c					\
	tab_transposition.c			\
	text.c					\
	tie.c					\
	view.c


