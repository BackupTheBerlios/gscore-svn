/*
 * staff.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2004 Sebastien Tricaud
 * e-mail : toady@gscore.org
 * URL    : http://www.gscore.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/** 
 * @file
 * 
 * Functions to deal with staves
 */

#include <gtk/gtk.h>

#include "gscore.h"
#include "common.h"
#include "constants.h"
#include "draw.h"
#include "debug.h"
#include "macros.h"
#include "spacings.h"
#include "objects.h"

/* GtkWidget * vbox; */
/* GtkWidget * key_signature_pixmap; */
/* GtkWidget * label; */
/* GtkWidget * pixmap_wid; */

/* GtkImage  * pixmap; */
/* GdkBitmap * mask; */
/* GdkColor    c; */


/* gint old_key_signature = 0; */
gboolean already_packed = FALSE;
static gint key_signature;


gboolean staff_set_time_signature(gint staff, gint signature_type, gint number_of_beats, gint beat_duration);


/**
 * Create a staff
 *
 * @param nb_lines is the number of lines
 * @param space_btw_lines is the space (in pixels) left between the lines
 * @param extremity_begin_x is the x position of the staff
 * @param extremity_begin_y is the y position of the staff
 *
 * @return TRUE if the staff is created, FALSE if not
 */
gboolean create_staff(Score_t *score, guint8 nb_lines, guint8 space_btw_lines,
                      gdouble extremity_begin_x, gdouble extremity_begin_y)
{

        score->Staff = g_malloc(sizeof(Staff_t));
 
        score->Staff->nb_lines = nb_lines;
        score->Staff->space_btw_lines = space_btw_lines;
        score->Staff->is_selected = FALSE;
        score->Staff->key = NO_KEY;
        score->Staff->key_signature = KEY_SIGNATURE_EMPTY;
        score->Staff->time_signature[0] = TIME_SIGNATURE_NORMAL;
        score->Staff->time_signature[1] = 4;
        score->Staff->time_signature[2] = 4;
        score->Staff->measure_number = 1;
        score->Staff->total_measures = score->Staff->measure_number;
        score->Staff->extremity_begin_x = extremity_begin_x;
        score->Staff->extremity_begin_y = extremity_begin_y;

        score->Staff->current_x = extremity_begin_x + Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa;
	score->Staff->start_x = extremity_begin_x + Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa;

        score->Staff->midi_instrument = MIDI_GRAND_PIANO;
        score->Staff->Object_list = NULL;

        score->Staff_list =
                g_list_append(score->Staff_list, score->Staff);

        if (!score->Staff_list)
                return FALSE;

        score->nb_staves++;

        return TRUE;
}

extern void 
set_staff_selected(gint staff)
{

        Staff_t *staff_data;
	staff_data = g_list_nth_data(Score.Staff_list, staff);

        if (staff_data)
                staff_data->is_selected = TRUE;

}

extern void 
set_staff_unselect(gint staff)
{

        Staff_t *staff_data;
	staff_data = g_list_nth_data(Score.Staff_list, staff);

        if (staff_data)
                staff_data->is_selected = FALSE;

}

gboolean delete_staff(gint staff)
{
        GList * listrunner;
        gboolean retval;

        listrunner = g_list_first(Score.Staff_list);
        if (!listrunner) 
                retval = FALSE;
        else
                retval = TRUE;

        while (listrunner)
        {
                Staff_t *staff_data;

                staff_data = g_list_nth_data(Score.Staff_list, staff);

                Score.Staff_list = g_list_remove(Score.Staff_list, staff_data);
        }

	return TRUE;
}

gint get_staff_selected(void)
{
        GList * listrunner;
        gint    counter;

        counter = 0;

        listrunner = g_list_first(Score.Staff_list);

        while ( listrunner ) {
                        Staff_t *staff;
                        
                        staff = (Staff_t *)listrunner->data;

                        if ( staff->is_selected )
                                        return counter;
                               
                        counter++;
                        listrunner = g_list_next(listrunner);
                }


        return -1;
}

gint get_staff_key_signature(guint staff)
{
	Staff_t *staff_data;

	gint retval = 0;

	staff_data = g_list_nth_data(Score.Staff_list, staff);

        if (staff_data)
                retval = staff_data->key_signature;

	return 0;
}

/* Returns the y position where the next staff should be */
gint staff_get_y_for_next(void)
{
        Staff_t *staff_data;
        gint retval = 0;

        staff_data = g_list_nth_data(Score.Staff_list, get_staff_selected());

        retval += staff_data->extremity_begin_y;
        retval += (staff_data->nb_lines - 1) * staff_data->space_btw_lines + staff_data->nb_lines;
        retval += Spacings.Measures.slbm;

        return retval;
}

/* Function called by the ADD/REMOVE Staff dialog box to update spinbuttons */
void staff_add_remove_options(void)
{

        GtkWidget *widget;

        widget = glade_xml_get_widget(gladexml, "sb_extremityxbegin");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), Spacings.Measures.xpsfm);
        widget = glade_xml_get_widget(gladexml, "sb_extremityybegin");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(widget), staff_get_y_for_next());

}

void staff_add_remove_ok(void)
{

        GtkWidget *widget;

        guint numberoflines;
        guint spacebetweenlines;
        guint extremityxbegin;
        guint extremityybegin;


        widget = glade_xml_get_widget(gladexml, "sb_numberoflines");
        numberoflines = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        widget = glade_xml_get_widget(gladexml, "sb_spacebetweenlines");
        spacebetweenlines = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        widget = glade_xml_get_widget(gladexml, "sb_extremityxbegin");
        extremityxbegin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
        widget = glade_xml_get_widget(gladexml, "sb_extremityybegin");
        extremityybegin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));

        widget = glade_xml_get_widget(gladexml, "staff_insert_below");

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
                        /* Add a staff below ;) */
                        create_staff(&Score, numberoflines, spacebetweenlines,
                                     extremityxbegin, extremityybegin);
                }

        refresh();

}

void on_settime_ok_clicked(void)
{
        GtkWidget *widget;

        widget = glade_xml_get_widget(gladexml, "stime_radio_common");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
		staff_set_time_signature(get_staff_selected(), TIME_SIGNATURE_COMMON_TIME, 4, 4);

		Score.staff_extremity_end_x += STANDARD_TIME_SIGNATURE_SIZE;
/* 		staff_set_current_x(get_staff_selected(),  */
/* 				    staff_get_current_x(get_staff_selected()) + STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats); */
/* 		staff_set_start_x(get_staff_selected(), offset); */
	}

        widget = glade_xml_get_widget(gladexml, "stime_radio_cut");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) {
		staff_set_time_signature(get_staff_selected(), TIME_SIGNATURE_ALLA_BREVE, 2, 2);
	}

	refresh();

}

gboolean staff_update_statusbar(void)
{
        GtkWidget *widget;

        guint cid;              /* Context ID */

        widget = glade_xml_get_widget(gladexml, "statusbar");

        cid = gtk_statusbar_get_context_id(GTK_STATUSBAR(widget), "staff");

/*         printf("staff_selected= %d\n", get_staff_selected()); */

        cid = gtk_statusbar_push(GTK_STATUSBAR(widget), cid, g_strdup_printf("Staff: %d", get_staff_selected()));


	return TRUE;
}

gboolean staff_set_start_x(gint staff, gint start_x)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
        if ( staff_data ) {
                staff_data->start_x = start_x;
		return TRUE;
	}

	return FALSE;
}

/* gint staff_get_start_x(Staff_t *staff) */
/* { */
/*         Staff_t *staff_data; */


/*         staff_data = g_list_nth_data(Score.Staff_list, staff); */

/* 	if ( staff_data ) */
/* 		return staff_data->start_x; */

/* 	return -1; */
/* } */

gboolean staff_set_key(gint staff, gint key)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
        if ( staff_data ) {
                staff_data->key = key;
		return 0;
	}

	return -1;
}

void staff_set_key_callback(void)
{
        GtkWidget *widget;

        widget = glade_xml_get_widget(gladexml, "setkey_treble_rb");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) )
		staff_set_key(get_staff_selected(), TREBLE_KEY);

        widget = glade_xml_get_widget(gladexml, "setkey_bass_rb");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) )
		staff_set_key(get_staff_selected(), BASS_KEY);

        widget = glade_xml_get_widget(gladexml, "setkey_alto_rb");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) )
		staff_set_key(get_staff_selected(), ALTO_KEY);

        widget = glade_xml_get_widget(gladexml, "setkey_tenor_rb");
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) )
		staff_set_key(get_staff_selected(), TENOR_KEY);

	refresh();

}


gint staff_get_key(gint staff)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);

        return staff_data->key;
}

gboolean staff_set_current_x(gint staff, gint current_x)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
        if (staff_data) {
                staff_data->current_x = current_x;
		return 0;
	}
	
	return -1;
}

gint staff_get_current_x(gint staff)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
	return staff_data->current_x;
}

gdouble get_staff_extremity_begin_x(gint staff)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);

	if(staff_data) {
	  return staff_data->extremity_begin_x;
	} else {
	  return 0;
	}
}

gdouble get_staff_extremity_begin_y(gint staff)
{
        Staff_t *staff_data;

        staff_data = g_list_nth_data(Score.Staff_list, staff);

	if(staff_data) {
	  return staff_data->extremity_begin_y;
	} else {
	  return 0;
	}
}


gboolean staff_set_key_signature(gint staff, gint key_signature)
{
/*         GList * listrunner; */

/*         listrunner = g_list_first(Score.Staff_list); */
/*         while (listrunner) */
/*                 { */
        Staff_t *staff_data;
        
        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
        if (staff_data)
                staff_data->key_signature = key_signature;

	return TRUE;
/*                         listrunner = g_list_next(listrunner); */
/*                 } */
}

gboolean staff_set_time_signature(gint staff, gint signature_type, gint number_of_beats, gint beat_duration)
{
/*         GList * listrunner; */

/*         listrunner = g_list_first(Score.Staff_list); */
/*         while (listrunner) */
/*                 { */
        Staff_t *staff_data;
        
        staff_data = g_list_nth_data(Score.Staff_list, staff);
        
        staff_data->time_signature[0] = signature_type;
        staff_data->time_signature[1] = number_of_beats;
        staff_data->time_signature[2] = beat_duration;
        
/*         listrunner = g_list_next(listrunner); */
/*                 } */

/*         g_list_free(listrunner); */

	return TRUE;
}

gboolean staff_set_midi_instrument(gint staff, gint midi_instrument)
{
/*         GList * listrunner; */

/*         listrunner = g_list_first(Score.Staff_list); */
/*         while (listrunner) */
/*                 { */
	Staff_t *staff_data;
	
	staff_data = g_list_nth_data(Score.Staff_list, staff);
	
	staff_data->midi_instrument = midi_instrument;
	
/*                         listrunner = g_list_next(listrunner); */
/*                 } */
	
/*         g_list_free(listrunner); */
	
	return TRUE;
}


/* /\* BEGIN: glade stuff *\/ */
/* void on_add_remove_staff_activate(GtkWidget *widget) */
/* { */
/* 	widget = glade_xml_get_widget (gladexml, "add_remove_staff"); */
/* 	gtk_widget_show(widget); */
/* } */

void ValueOfRange (GtkAdjustment *adj);

void on_key_signature_activate(GtkWidget *widget)
{
	GtkWidget *hscale;
	GtkAdjustment *adj;

	gint value_adj = 0;

/* 	old_key_signature = Score.Staff[get_staff_selected()].time_signature; */

        /* The adjustment */
/*         switch (Score.Staff[get_staff_selected()].key_signature) */
	switch(get_staff_key_signature(get_staff_selected())) {
	case KEY_SIGNATURE_TREBLE_EMPTY:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "C Major or A minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_empty.xpm"));

		value_adj = 0;
		break;
	case KEY_SIGNATURE_TREBLE_A_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "B Major or G sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_A_sharp.xpm"));

		value_adj = 5;
		break;
	case KEY_SIGNATURE_TREBLE_B_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "C sharp Major or A sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_B_sharp.xpm"));

		value_adj = 7;
		break;
	case KEY_SIGNATURE_TREBLE_C_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "D Major or B minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_C_sharp.xpm"));

		value_adj = 2;
		break;
	case KEY_SIGNATURE_TREBLE_D_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "E Major or C sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_D_sharp.xpm"));

		value_adj = 4;
		break;
	case KEY_SIGNATURE_TREBLE_E_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "F sharp Major or  D sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_E_sharp.xpm"));

		value_adj = 6;
		break;
	case KEY_SIGNATURE_TREBLE_F_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "G Major or E minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_F_sharp.xpm"));

		value_adj = 1;
		break;
	case KEY_SIGNATURE_TREBLE_G_SHARP:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "A Major or F sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_G_sharp.xpm"));

		value_adj = 3;
		break;
	case KEY_SIGNATURE_TREBLE_A_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "E flat Major or C minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_A_flat.xpm"));

		value_adj = -3;
		break;
	case KEY_SIGNATURE_TREBLE_B_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "F Major or D minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_B_flat.xpm"));

		value_adj = -1;
		break;
	case KEY_SIGNATURE_TREBLE_C_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "G flat Major or E flat minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_C_flat.xpm"));

		value_adj = -6;
		break;
	case KEY_SIGNATURE_TREBLE_D_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "A flat Major or F minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_D_flat.xpm"));

		value_adj = -4;
		break;
	case KEY_SIGNATURE_TREBLE_E_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "B flat Major or G minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_E_flat.xpm"));

		value_adj = -2;
		break;
	case KEY_SIGNATURE_TREBLE_F_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "D flat Major");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_F_flat.xpm"));

		value_adj = -7;
		break;
	case KEY_SIGNATURE_TREBLE_G_FLAT:
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "D flat Major or B minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_G_flat.xpm"));

		value_adj = -5;
		break;
	}



	adj = GTK_ADJUSTMENT(gtk_adjustment_new(value_adj, -7, 7, 1, 1, 0));
   
	if ( ! already_packed)
	{
		hscale = gtk_hscale_new (adj);
   
		gtk_scale_set_digits(GTK_SCALE(hscale), 0);
		gtk_scale_set_draw_value(GTK_SCALE(hscale), FALSE);
		GTK_RANGE(hscale)->round_digits = 0;


		widget = glade_xml_get_widget(gladexml, "sks_hbox");
		gtk_box_pack_start_defaults(GTK_BOX(widget), hscale);

		g_signal_connect(GTK_OBJECT(adj),"value_changed",
				 G_CALLBACK(ValueOfRange), NULL);

		gtk_widget_show(hscale);

		already_packed = TRUE;

	}
}

void on_key_signature_value_changed(void)
{
/* 	GtkWidget *widget; */

/* 	gint i = -1; */

/* 	switch (i) */
/* 	{ */
/* 	case -1: */
/* 		Score.Staff[get_staff_selected()].key_signature = */
/* 			KEY_SIGNATURE_TREBLE_B_FLAT; */
		
/* 		widget = glade_xml_get_widget (gladexml, "sks_clef_label"); */
/* 		gtk_label_set_text(GTK_LABEL(widget), "F Major or D minor"); */

/* 		widget = glade_xml_get_widget (gladexml, "sks_image"); */
/* 		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/key_signature/treble_B_flat.xpm")); */
/* 		break; */
/* 	} */
}

/* END: glade stuff */

/* gint get_staff_selected(void); */

void ValueOfRange (GtkAdjustment *adj)
{

	GtkWidget * widget;
	gint i;

	i = adj->value;
	
	switch (i) {
		
	case -1:
		/* 		Score.Staff[get_staff_selected()].key_signature = */
		key_signature = KEY_SIGNATURE_TREBLE_B_FLAT;
		
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "F Major or D minor");
		
		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_B_flat.xpm"));
		break;
	case -2:
		key_signature = KEY_SIGNATURE_TREBLE_E_FLAT;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "B flat Major or G minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_E_flat.xpm"));
		break;
	case -3:
		key_signature = KEY_SIGNATURE_TREBLE_A_FLAT;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "E flat Major or C minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_A_flat.xpm"));
		break;
	case -4:
		key_signature = KEY_SIGNATURE_TREBLE_D_FLAT;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "A flat Major or F minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_D_flat.xpm"));
		break;
	case -5:
		key_signature = KEY_SIGNATURE_TREBLE_G_FLAT;
		
		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "D flat Major or B minor");
		
		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_G_flat.xpm"));
		break;
	case -6:
		key_signature = KEY_SIGNATURE_TREBLE_C_FLAT;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "G flat Major or E flat minor");
		
		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_C_flat.xpm"));
		break;
	case -7:
		key_signature = KEY_SIGNATURE_TREBLE_F_FLAT;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "C flat Major or A flat minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_F_flat.xpm"));
		break;
	case 0:
		key_signature = KEY_SIGNATURE_TREBLE_EMPTY;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "C Major or A minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_empty.xpm"));
		break;
	case 1:
		key_signature = KEY_SIGNATURE_TREBLE_F_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "G Major or E minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_F_sharp.xpm"));
		break;
	case 2:
		key_signature = KEY_SIGNATURE_TREBLE_C_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "D Major or B minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_C_sharp.xpm"));
		break;
	case 3:
		key_signature = KEY_SIGNATURE_TREBLE_G_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "A Major or F sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_G_sharp.xpm"));
		break;
	case 4:
		key_signature = KEY_SIGNATURE_TREBLE_D_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "E Major or C sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_D_sharp.xpm"));
		break;
	case 5:
		key_signature = KEY_SIGNATURE_TREBLE_A_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "B Major or G sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_A_sharp.xpm"));
		break;
	case 6:
		key_signature = KEY_SIGNATURE_TREBLE_E_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "F sharp Major or  D sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_E_sharp.xpm"));
		break;
	case 7:
		key_signature = KEY_SIGNATURE_TREBLE_B_SHARP;

		widget = glade_xml_get_widget (gladexml, "sks_clef_label");
		gtk_label_set_text(GTK_LABEL(widget), "C sharp Major or A sharp minor");

		widget = glade_xml_get_widget (gladexml, "sks_image");
		gtk_image_set_from_file(GTK_IMAGE(widget), get_file_from_data_dir("pixmaps/treble_B_sharp.xpm"));
		break;
	}
}


void staff_key_signature(gpointer callback_data, guint callback_action, GtkWidget *widget)
{

/*      static GtkWidget * key_signature_dialog = NULL; */

/*      if (key_signature_dialog) */
/*      { */
/*           if (!GTK_WIDGET_VISIBLE(key_signature_dialog)) */
/*                gtk_widget_show(key_signature_dialog); */
/*           else */
/*                gdk_window_raise(key_signature_dialog->window); */
/*      } else */
/*      { */
/*           gint        value_adj = 0; */
/*           GtkWidget * hscale; */

/*           GtkAdjustment * adj; */

          
/*           key_signature_dialog = gtk_dialog_new_with_buttons("Set key signature", NULL, */
/*                                                         GTK_DIALOG_MODAL, */
/*                                                         GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                                         GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                                         NULL); */
/*           g_signal_connect(G_CALLBACK(key_signature_dialog), "destroy", */
/*                            G_CALLBACK(gtk_widget_destroyed), */
/*                            &key_signature_dialog); */
          
/*           /\* The main part *\/ */
/*           vbox = gtk_vbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(key_signature_dialog)->vbox), vbox); */
/*           gtk_widget_show(vbox); */

/*           /\* The adjustment *\/ */
/*           switch (Score.Staff[get_staff_selected()].key_signature) */
/*           { */
/*           case KEY_SIGNATURE_TREBLE_EMPTY: */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_empty.xpm")); */
/*                label = gtk_label_new("C Major or A minor"); */
/*                value_adj = 0; */
/*                break;  */
/*           case KEY_SIGNATURE_TREBLE_A_SHARP: */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_A_sharp.xpm")); */
/*                label = gtk_label_new("B Major or G sharp minor"); */
/*                value_adj = 5; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_B_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_B_sharp.xpm")); */
/*                label = gtk_label_new("C sharp Major or A sharp minor"); */
/*                value_adj = 7; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_C_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_C_sharp.xpm")); */
/*                label = gtk_label_new("D Major or B minor"); */
/*                value_adj = 2; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_D_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_D_sharp.xpm")); */
/*                label = gtk_label_new("E MAjor or C sharp minor"); */
/*                value_adj = 4; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_E_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_E_sharp.xpm")); */
/*                label = gtk_label_new("F sharp Major or  D sharp minor"); */
/*                value_adj = 6; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_F_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_empty.xpm")); */
/*                label = gtk_label_new("G Major or E minor"); */
/*                value_adj = 1; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_G_SHARP:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_G_sharp.xpm")); */
/*                label = gtk_label_new("A Major or F sharp minor"); */
/*                value_adj = 3; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_A_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_A_flat.xpm")); */
/*                label = gtk_label_new("E flat Major or C minor"); */
/*                value_adj = -3; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_B_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_B_flat.xpm")); */
/*                label = gtk_label_new("F Major or D minor"); */
/*                value_adj = -1; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_C_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_C_flat.xpm")); */
/*                label = gtk_label_new("G flat Major or E flat minor"); */
/*                value_adj = -6; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_D_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_D_flat.xpm")); */
/*                label = gtk_label_new("A flat Major or F minor"); */
/*                value_adj = -4; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_E_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_E_flat.xpm")); */
/*                label = gtk_label_new("B flat Major or G minor"); */
/*                value_adj = -2; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_F_FLAT:  */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_F_flat.xpm")); */
/*                label = gtk_label_new("D flat Major"); */
/*                value_adj = -7; */
/*                break; */
/*           case KEY_SIGNATURE_TREBLE_G_FLAT: */
/*                pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/treble_G_flat.xpm")); */
/*                label = gtk_label_new("D flat Major or B minor"); */
/*                value_adj = -5; */
/*                break; */
/*           } */


         
/*           adj = GTK_ADJUSTMENT(gtk_adjustment_new(value_adj, -7, 7, 1, 1, 0)); */

/*           hscale = gtk_hscale_new (adj); */
/*           gtk_scale_set_digits(GTK_SCALE(hscale), 0); */
/*           gtk_scale_set_draw_value(GTK_SCALE(hscale), FALSE); */
/*           GTK_RANGE(hscale)->round_digits = 0; */
/*           gtk_box_pack_end_defaults(GTK_BOX(vbox), hscale); */
/*           gtk_widget_show(hscale); */

/*           g_signal_connect(GTK_OBJECT(adj),"value_changed", */
/*                            G_CALLBACK(ValueOfRange), NULL); */

/*           /\* the label *\/ */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), label); */
/*           gtk_widget_show(label); */

/*           /\* The pixmap widget *\/ */

/*           gtk_widget_show(pixmap_wid); */
/*           gtk_box_pack_start(GTK_BOX(vbox), GTK_WIDGET(pixmap_wid), */
/*                              TRUE, FALSE, 0); */

/*           /\* Execute the OK button action *\/ */
/*           if (gtk_dialog_run(GTK_DIALOG(key_signature_dialog))==GTK_RESPONSE_ACCEPT) */
/*           { */
/*                g_message("Accept!"); */
/*           } */
/*           gtk_widget_destroy(key_signature_dialog); */
/*      } */

}

void staff_time_signature(gpointer callback_data, guint callback_action, GtkWidget *widget)
{

/*      static GtkWidget * time_signature_dialog = NULL; */

     
/*      old_key_signature = Score.Staff[get_staff_selected()].time_signature; */

/*      if (time_signature_dialog) */
/*      { */
/*           if (!GTK_WIDGET_VISIBLE(time_signature_dialog)) */
/*                gtk_widget_show(time_signature_dialog); */
/*           else */
/*                gdk_window_raise(time_signature_dialog->window); */
/*      } else */
/*      { */
/*           GtkWidget * vbox, * hbox; */
/*           GtkWidget * drawingarea; */
/*           GtkWidget * NumeratorEntry, * DenominatorEntry; */
/*           GtkWidget * radio_24, * radio_68, * radio_common_time, * radio_alla_breve, * radio_custom; */
/*           GtkWidget * pixmap_wid; */
/*           GtkWidget * hseparator; */

/*           GSList    * group; */

/*           time_signature_dialog = gtk_dialog_new_with_buttons("Set time signature", NULL, */
/*                                                         GTK_DIALOG_MODAL, */
/*                                                         GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                                         GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                                         NULL); */
/*           g_signal_connect(G_CALLBACK(time_signature_dialog), "destroy", */
/*                            G_CALLBACK(gtk_widget_destroyed), */
/*                            &time_signature_dialog); */
          
/*           /\* The main part *\/ */
/*           vbox = gtk_vbox_new(FALSE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(time_signature_dialog)->vbox), vbox); */
/*           gtk_widget_show(vbox); */

/*           /\* The widgets *\/ */

/*           /\* New hbox *\/ */
/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_24 = gtk_radio_button_new_with_label(NULL, "2/4"); */
/*           group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_24)); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_24); */
/*           gtk_widget_show(radio_24); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/time_signature/p_24.xpm")); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), pixmap_wid); */
/*           gtk_widget_show(pixmap_wid); */

/*           radio_68 = gtk_radio_button_new_with_label(group,"6/8"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_68); */
/*           gtk_widget_show(radio_68); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/time_signature/p_68.xpm")); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), pixmap_wid); */
/*           gtk_widget_show(pixmap_wid); */

/*           hseparator = gtk_hseparator_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hseparator); */
/*           gtk_widget_show(hseparator); */

/*           /\* New hbox *\/ */
/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_common_time = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_68),"Common Time"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_common_time); */
/*           gtk_widget_show(radio_common_time); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/time_signature/common_time.xpm")); */
/*           gtk_widget_show(pixmap_wid); */

/*           radio_alla_breve = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_common_time),"Alla Breve"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_alla_breve); */
/*           gtk_widget_show(radio_alla_breve); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/time_signature/alla_breve.xpm")); */
/*           gtk_widget_show(pixmap_wid); */

/*           hseparator = gtk_hseparator_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hseparator); */
/*           gtk_widget_show(hseparator); */

/*           /\* New hbox *\/ */
/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_custom = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_alla_breve),"custom"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_custom); */
/*           gtk_widget_show(radio_custom); */

/*           NumeratorEntry = gtk_entry_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), NumeratorEntry); */
/*           gtk_widget_show(NumeratorEntry); */
          
/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           drawingarea = gtk_drawing_area_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), drawingarea); */
/*           gtk_widget_show(drawingarea); */

/*           DenominatorEntry = gtk_entry_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), DenominatorEntry); */
/*           gtk_widget_show(DenominatorEntry); */
          
/*           /\* Execute the OK button action *\/ */
/*           if (gtk_dialog_run(GTK_DIALOG(time_signature_dialog))==GTK_RESPONSE_ACCEPT) */
/*           { */
/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_24))) */
/*                     Score.Staff[get_staff_selected()].time_signature = TIME_SIGNATURE_24; */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_68))) */
/*                     Score.Staff[get_staff_selected()].time_signature = TIME_SIGNATURE_68; */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_common_time))) */
/*                     Score.Staff[get_staff_selected()].time_signature = TIME_SIGNATURE_COMMON_TIME; */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_alla_breve))) */
/*                     Score.Staff[get_staff_selected()].time_signature = TIME_SIGNATURE_ALLA_BREVE; */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_custom))) */
/*                { */
/*                     g_message("custom"); */
/*                } */

/*                Score.Staff[get_staff_selected()].startx += 10; */

/*           } else */
/*           { */
/*                Score.Staff[get_staff_selected()].time_signature = old_key_signature; */
/*           } */
/*           gtk_widget_destroy(time_signature_dialog); */
/*      } */

}

void staff_display_measures_numbers(gpointer callback_data, guint callback_action, GtkWidget *widget)
{
/*      static GtkWidget * display_measures_numbers_dialog = NULL; */

/*      if (display_measures_numbers_dialog) */
/*      { */
/*           if (!GTK_WIDGET_VISIBLE(display_measures_numbers_dialog)) */
/*                gtk_widget_show(display_measures_numbers_dialog); */
/*           else */
/*                gdk_window_raise(display_measures_numbers_dialog->window); */
/*      } else */
/*      { */
/*           GtkWidget * vbox; */
/*           GtkWidget * radio_never, * radio_all_staffs, * radio_only_this_staff; */
/*           GSList    * group = NULL; */
          
/*           display_measures_numbers_dialog = gtk_dialog_new_with_buttons("Display measures numbers", NULL, */
/*                                                                         GTK_DIALOG_MODAL, */
/*                                                                         GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                                                         GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                                                         NULL); */
/*           g_signal_connect(G_CALLBACK(display_measures_numbers_dialog), "destroy", */
/*                            G_CALLBACK(gtk_widget_destroyed), */
/*                            &display_measures_numbers_dialog); */
          
/*           /\* The main part *\/ */
/*           vbox = gtk_vbox_new(FALSE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(display_measures_numbers_dialog)->vbox), vbox); */
/*           gtk_widget_show(vbox); */
          
/*           /\* the three radio buttons *\/ */
/*           radio_never = gtk_radio_button_new_with_label(group, */
/*                                                         "Never display measures numbers"); */
/*           group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_never)); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), radio_never); */
/*           gtk_widget_show(radio_never); */
/*           radio_all_staffs = gtk_radio_button_new_with_label(group, */
/*                                                             "Display measures numbers for all staffs"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), radio_all_staffs); */
/*           gtk_widget_show(radio_all_staffs); */
          
/*           radio_only_this_staff = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_all_staffs), */
/*                                                                               "Display measures numbers for this staff only"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), radio_only_this_staff); */
/*           gtk_widget_show(radio_only_this_staff); */
          
/*           if (gtk_dialog_run(GTK_DIALOG(display_measures_numbers_dialog))==GTK_RESPONSE_ACCEPT) */
/*           { */
/*                g_message("Apply!"); */
               
/*           } */
/*           gtk_widget_destroy(display_measures_numbers_dialog); */
/*      } */

}


gdouble get_staff_extremity_end_y(gint staff_id)
{
        Staff_t *staff_data;
        gdouble retval = 0;

        staff_data = g_list_nth_data(Score.Staff_list, staff_id);

        retval += staff_data->extremity_begin_y;
        retval += (staff_data->nb_lines - 1) * staff_data->space_btw_lines + staff_data->nb_lines;

        return retval;
}

/* Accordingly to the y position of the cursor, this function returns the staff number */
gint get_staff_id(gdouble y)
{
        GList * listrunner;
        
        Staff_t *staff_data;
        guint staff_counter = 0;

        guint staff_id = 0;
 
        listrunner = g_list_first(Score.Staff_list);

        while (listrunner) {

		staff_data = (Staff_t *)listrunner->data;

		if ( ! staff_data ) {
			debug_msg("|staff.c| get_staff_id(). Unable to browse Score.Staff_list. Memory Exhausted ?\n");
		}

		if ( y >= staff_data->extremity_begin_y ) {
			if ( y <= get_staff_extremity_end_y(staff_counter) ) {
				staff_id = staff_counter;
			}
		}

		staff_counter++;
                                        
		listrunner = g_list_next(listrunner);
	}
        
        g_list_free(listrunner);


	return staff_id;

}

void deselect_all_staffs(void)
{
/*      gint i = 0; */

/*      for ( i = 0; i < Score.nb_staves; i++ ) */
/*      { */
/*           Score.Staff[i].is_selected = FALSE; */
/*      } */

}

extern gint
staff_remove_staff(gpointer callback_data, guint callback_action, GtkWidget *widget)
{
/*      gint i; */

/*      gint staff_number = get_staff_selected(); */

/*      Score.nb_staves--; */

/*      for ( i = 0; i < Score.nb_staves; i++) */
/*      { */
/*           if (i >= staff_number) */
/*           { */
/*                Score.Staff[i].nb_lines = Score.Staff[i+1].nb_lines; */
/*                Score.Staff[i].space_btw_lines = Score.Staff[i+1].space_btw_lines; */
/*                Score.Staff[i].is_selected = Score.Staff[i].is_selected; */
/*                Score.Staff[i].key = Score.Staff[i+1].key; */
/*                Score.Staff[i].key_signature = Score.Staff[i+1].key_signature; */
/*                Score.Staff[i].time_signature = Score.Staff[i+1].time_signature; */
/*                Score.Staff[i].time_signature_x = Score.Staff[i+1].time_signature_x; */
/*                Score.Staff[i].endbar = Score.Staff[i+1].endbar; */
/*                Score.Staff[i].extremity_begin_x = Score.Staff[i+1].extremity_begin_x; */
/*                Score.Staff[i].extremity_end_x = Score.Staff[i+1].extremity_end_x; */
/*                Score.Staff[i].extremity_begin_y = Score.Staff[i].extremity_begin_y; */
/*                Score.Staff[i].extremity_end_y = Score.Staff[i].extremity_begin_y - 1 +  */
/*                     (Score.Staff[i].nb_lines + ((Score.Staff[i].nb_lines - 1) * Score.Staff[i].space_btw_lines)); */
/*                Score.Staff[i].space_with_staff_up = Score.Staff[i+1].space_with_staff_up; */
/* /\*                Score.Staff[i].middle = Score.Staff[i+1].extremity_begin_y + 17; *\/ */
/*                Score.Staff[i].total_measures = Score.Staff[i+1].total_measures; */
/*                Score.Staff[i].startx = Score.Staff[i+1].startx; */

/*                Score.Staff[i].Object_list = g_list_copy(Score.Staff[i+1].Object_list); */

/*           } */
/*      } */

/*      refresh(); */

     return 0;
}

extern gint
get_staff_key(gint staff)
{

/*      gint staff_type = -1; */
/*      gint i; */

/*      for ( i = 0; i < Score.nb_staves; i++ ) */
/*           staff_type = Score.Staff[staff].key; */

/*      return staff_type; */

	return 0;
}

/* void staff_set_midi_instrument(gpointer callback_data, guint callback_action, GtkWidget *widget) */
/* { */

/*      static GtkWidget * dialog = NULL; */

/*      if (dialog) */
/*      { */
/*           if (!GTK_WIDGET_VISIBLE(dialog)) */
/*                gtk_widget_show(dialog); */
/*           else */
/*                gdk_window_raise(dialog->window); */
/*      } else */
/*      { */
/*           GtkWidget * vbox; */
/*           GtkWidget * label; */
/*           GtkWidget * spinbutton; */

/*           GtkAdjustment * adj; */

          
/*           dialog = gtk_dialog_new_with_buttons("Set MIDI Instrument", NULL, */
/*                                                GTK_DIALOG_MODAL, */
/*                                                GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                                GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                                NULL); */
/*           g_signal_connect(G_CALLBACK(dialog), "destroy", */
/*                            G_CALLBACK(gtk_widget_destroyed), */
/*                            &dialog); */
          
/*           /\* The main part *\/ */
/*           vbox = gtk_vbox_new(FALSE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), vbox); */
/*           gtk_widget_show(vbox); */
          
/*           /\* the three radio buttons *\/ */
/*           label = gtk_label_new("Set MIDI Instrument (1..128)"); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), label); */
/*           gtk_widget_show(label); */


/*           adj = GTK_ADJUSTMENT(gtk_adjustment_new(Score.Staff[get_staff_selected()].midi_instrument, */
/*                                                   1, 128, */
/*                                                   1.0, 10.0, 10.0 )); */

/*           spinbutton = gtk_spin_button_new(adj, 1.0, 0); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), spinbutton); */
/*           gtk_widget_show(spinbutton); */

/*           if (gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT) */
/*           { */

/*                Score.Staff[get_staff_selected()].midi_instrument = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton)); */

/*           } */
/*           gtk_widget_destroy(dialog); */
/*      } */

/*      g_print("Set midi\n"); */
/* } */

void
staff_add_staff (gpointer callback_data, guint callback_action, GtkWidget *widget)
{

/*      static GtkWidget * add_staff_dialog = NULL; */

/*      if (add_staff_dialog) */
/*      { */
/*           if (!GTK_WIDGET_VISIBLE(add_staff_dialog)) */
/*                gtk_widget_show(add_staff_dialog); */
/*           else */
/*                gdk_window_raise(add_staff_dialog->window); */
/*      } else */
/*      { */

/*           GtkWidget * vbox, * hbox; */
/*           GtkWidget * radio_treble, * radio_bass, * radio_alto; */
/*           GtkWidget * pixmap_wid; */
/*           GtkWidget * hseparator; */

/*           GSList    * group; */


/*           add_staff_dialog = gtk_dialog_new_with_buttons("Add Staff", NULL, */
/*                                                         GTK_DIALOG_MODAL, */
/*                                                         GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                                         GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                                         NULL); */
/*           g_signal_connect(G_CALLBACK(add_staff_dialog), "destroy", */
/*                            G_CALLBACK(gtk_widget_destroyed), */
/*                            &add_staff_dialog); */
          
/*           /\* The main part *\/ */
/*           vbox = gtk_vbox_new(FALSE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(add_staff_dialog)->vbox), vbox); */
/*           gtk_widget_show(vbox); */

/*           /\* The widgets *\/ */
/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_treble = gtk_radio_button_new_with_label(NULL, "Treble key"); */
/*           group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_treble)); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_treble); */
/*           gtk_widget_show(radio_treble); */

/* /\*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/lilypond/clefs-G.xpm")); *\/ */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/clefs/clefs-G.xpm")); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), pixmap_wid); */
/*           gtk_widget_show(pixmap_wid); */

/*           hseparator = gtk_hseparator_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hseparator); */
/*           gtk_widget_show(hseparator); */

/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_bass = gtk_radio_button_new_with_label(group, "Bass key"); */
/*           group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_bass)); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_bass); */
/*           gtk_widget_show(radio_bass); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/clefs/clefs-F.xpm")); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), pixmap_wid); */
/*           gtk_widget_show(pixmap_wid); */

/*           hseparator = gtk_hseparator_new(); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hseparator); */
/*           gtk_widget_show(hseparator); */

/*           hbox = gtk_hbox_new(TRUE, 4); */
/*           gtk_box_pack_start_defaults(GTK_BOX(vbox), hbox); */
/*           gtk_widget_show(hbox); */

/*           radio_alto = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio_bass), "Alto key"); */
/*           group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio_alto)); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), radio_alto); */
/*           gtk_widget_show(radio_alto); */

/*           pixmap_wid = gtk_image_new_from_file(get_file_from_data_dir("pixmaps/clefs/clefs-C.xpm")); */
/*           gtk_box_pack_start_defaults(GTK_BOX(hbox), pixmap_wid); */
/*           gtk_widget_show(pixmap_wid); */

/*           /\* Execute the OK button action *\/ */
/*           if (gtk_dialog_run(GTK_DIALOG(add_staff_dialog))==GTK_RESPONSE_ACCEPT) */
/*           { */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_treble))) { */

/*                     Score.Staff[Score.nb_staves].endbar = TRUE; */
/*                     Score.Staff[Score.nb_staves].is_selected = FALSE; */
/*                     Score.Staff[Score.nb_staves].nb_lines = 5; */
/*                     Score.Staff[Score.nb_staves].space_btw_lines = 8; */
/*                     Score.Staff[Score.nb_staves].space_with_staff_up = 50; */
/*                     Score.Staff[Score.nb_staves].key = TREBLE_KEY; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_x = Score.Staff[Score.nb_staves-1].extremity_begin_x; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_y = Score.Staff[Score.nb_staves-1].extremity_end_y + Score.Staff[Score.nb_staves].space_with_staff_up; */
/*                     Score.Staff[Score.nb_staves].extremity_end_y   = Score.Staff[Score.nb_staves].extremity_begin_y+36; */
/* /\*                     Score.Staff[Score.nb_staves].middle = Score.Staff[Score.nb_staves].extremity_begin_y+17; *\/ */
/*                     Score.Staff[Score.nb_staves].extremity_end_x = Score.Staff[Score.nb_staves-1].extremity_end_x; */
/*                     Score.Staff[Score.nb_staves].key_signature = KEY_SIGNATURE_TREBLE_EMPTY; */
/*                     Score.Staff[Score.nb_staves].startx = 100; */
/*                     Score.Staff[Score.nb_staves].time_signature_x = 70; */

/*                     Score.Staff[Score.nb_staves].Object_list = NULL; */

/*                     Score.height = Score.Staff[Score.nb_staves].extremity_end_y + 100; */

/*                     deselect_all_staffs(); */
/*                     Score.Staff[Score.nb_staves].is_selected = TRUE; */
/*                     score_new_size();  */
                    
/*                     Score.nb_staves++; */

/*                } */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_bass))) { */

/*                     Score.Staff[Score.nb_staves].endbar = TRUE; */
/*                     Score.Staff[Score.nb_staves].is_selected = FALSE; */
/*                     Score.Staff[Score.nb_staves].nb_lines = 5; */
/*                     Score.Staff[Score.nb_staves].space_btw_lines = 8; */
/*                     Score.Staff[Score.nb_staves].space_with_staff_up = 50; */
/*                     Score.Staff[Score.nb_staves].key = BASS_KEY; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_x = Score.Staff[Score.nb_staves-1].extremity_begin_x; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_y = Score.Staff[Score.nb_staves-1].extremity_end_y + Score.Staff[Score.nb_staves].space_with_staff_up; */
/*                     Score.Staff[Score.nb_staves].extremity_end_y   = Score.Staff[Score.nb_staves].extremity_begin_y+36; */
/* /\*                     Score.Staff[Score.nb_staves].middle = Score.Staff[Score.nb_staves].extremity_begin_y+17; *\/ */
/*                     Score.Staff[Score.nb_staves].extremity_end_x = Score.Staff[Score.nb_staves-1].extremity_end_x; */
/*                     Score.Staff[Score.nb_staves].key_signature = KEY_SIGNATURE_TREBLE_EMPTY; */
/*                     Score.Staff[Score.nb_staves].startx = 100; */
/*                     Score.Staff[Score.nb_staves].time_signature_x = 70; */

/*                     Score.Staff[Score.nb_staves].Object_list = NULL; */

/*                     Score.height = Score.Staff[Score.nb_staves].extremity_end_y + 100; */
                    
/*                     Score.nb_staves++; */

/*                } */

/*                if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_alto))) { */

/*                     Score.Staff[Score.nb_staves].endbar = TRUE; */
/*                     Score.Staff[Score.nb_staves].is_selected = FALSE; */
/*                     Score.Staff[Score.nb_staves].nb_lines = 5; */
/*                     Score.Staff[Score.nb_staves].space_btw_lines = 8; */
/*                     Score.Staff[Score.nb_staves].space_with_staff_up = 50; */
/*                     Score.Staff[Score.nb_staves].key = ALTO_KEY; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_x = Score.Staff[Score.nb_staves-1].extremity_begin_x; */
/*                     Score.Staff[Score.nb_staves].extremity_begin_y = Score.Staff[Score.nb_staves-1].extremity_end_y + Score.Staff[Score.nb_staves].space_with_staff_up; */
/*                     Score.Staff[Score.nb_staves].extremity_end_y   = Score.Staff[Score.nb_staves].extremity_begin_y+36; */
/* /\*                     Score.Staff[Score.nb_staves].middle = Score.Staff[Score.nb_staves].extremity_begin_y+17; *\/ */
/*                     Score.Staff[Score.nb_staves].extremity_end_x = Score.Staff[Score.nb_staves-1].extremity_end_x; */
/*                     Score.Staff[Score.nb_staves].key_signature = KEY_SIGNATURE_TREBLE_EMPTY; */
/*                     Score.Staff[Score.nb_staves].startx = 100; */
/*                     Score.Staff[Score.nb_staves].time_signature_x = 70; */

/*                     Score.Staff[Score.nb_staves].Object_list = NULL; */

/*                     Score.height = Score.Staff[Score.nb_staves].extremity_end_y + 100; */
                    
/*                     Score.nb_staves++; */
                    
/*                } */
               
/*                gtk_widget_destroy(add_staff_dialog); */
/*           } else */
/*           { */
/*                gtk_widget_destroy(add_staff_dialog); */
/*           } */
     
/*      } */

/*      refresh(); */

}

extern 
void update_key_signature(void)
{

        Staff_t *staff_data;

	gint offset = 0;


        staff_data = g_list_nth_data(Score.Staff_list, get_staff_selected());

	staff_data->key_signature = key_signature;

	switch(key_signature) {
	case KEY_SIGNATURE_TREBLE_EMPTY:
		/* We don't need to update the spacing here :) */
		break;
	case KEY_SIGNATURE_TREBLE_A_SHARP:
		offset += (5 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_B_SHARP:
		offset += (7 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_C_SHARP:
		offset += (2 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_D_SHARP:
		offset += (6 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_E_SHARP:
		offset += (4 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_F_SHARP:
		offset += (1 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_G_SHARP:
		offset += (3 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_A_FLAT:
		offset += (3 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_B_FLAT:
		offset += (1 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_C_FLAT:
		offset += (6 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_D_FLAT:
		offset += (4 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_E_FLAT:
		offset += (2 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_F_FLAT:
		offset += (7 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	case KEY_SIGNATURE_TREBLE_G_FLAT:
		offset += (5 * Spacings.KeySignatures.sbksa) + Spacings.KeySignatures.saks;
		break;
	}

	Score.staff_extremity_end_x += offset;
        staff_set_current_x(get_staff_selected(), staff_get_current_x(get_staff_selected()) + offset);
	staff_set_start_x(get_staff_selected(), offset);

	refresh();
}

extern
void staff_change_key_callback(void)
{
/*         GtkWidget *widget; */

/*         widget = glade_xml_get_widget(gladexml, "changekey_treble_rb"); */
/* 	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) */
/* 		add_object(get_staff_selected(), */
/* 			   TREBLE_KEY, NULL, NULL, 0, */
/* 			   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, FALSE); */

/*         widget = glade_xml_get_widget(gladexml, "changekey_bass_rb"); */
/* 	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) */
/* 		add_object(get_staff_selected(), */
/* 			   BASS_KEY, NULL, NULL, 0, */
/* 			   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, FALSE); */

/*         widget = glade_xml_get_widget(gladexml, "changekey_alto_rb"); */
/* 	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) */
/* 		add_object(get_staff_selected(), */
/* 			   ALTO_KEY, NULL, NULL, 0, */
/* 			   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, FALSE); */

/*         widget = glade_xml_get_widget(gladexml, "changekey_tenor_rb"); */
/* 	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)) ) */
/* 		add_object(get_staff_selected(), */
/* 			   TENOR_KEY, NULL, NULL, 0, */
/* 			   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, FALSE); */

/* 	gtk_widget_set_size_request(GTK_WIDGET(Score.area), Score.width, Score.height); */

	refresh();
}
