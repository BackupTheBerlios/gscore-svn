#include <gtk/gtk.h>

#include "gscore.h"
#include "constants.h"
#include "staff.h"
#include "position.h"
#include "draw.h"
#include "selection.h"
#include "key_cursor.h"
#include "common.h"

gint max_x = 0;
gint max_y = 0;
gint min_x = 0;
gint min_y = 0;

gboolean set_min_x = FALSE;
gboolean set_min_y = FALSE;
gboolean set_max_x = FALSE;
gboolean set_max_y = FALSE;



gboolean 
mouse_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{

/* 	printf("Selection.x_origin = %f, Selection.y_origin = %f, Selection.x = %f, Selection.y = %f\n", */
/* 	       Selection.x_origin, Selection.y_origin, Selection.x, Selection.y); */

	if ( Selection.object_type == CURSOR ) {

		highlight_selection(Selection.x_origin, Selection.y_origin, 
				    Selection.x, Selection.y);

	}

        Selection.x_origin = 0;
        Selection.y_origin = 0;

        max_x = 0;
        max_y = 0;
        min_x = 0;
        min_y = 0;

        set_min_x = FALSE;
        set_min_y = FALSE;
        set_max_x = FALSE;
        set_max_y = FALSE;

        refresh();

	return FALSE;
}


gboolean 
mouse_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{

	if ( Selection.object_type == CURSOR ) {

		undo_selection();

		set_staff_unselect(get_staff_selected());
		set_staff_selected(get_staff_id(event->y));

		set_selection_origin(widget, (GdkEventButton *)event);
	}

	return FALSE;
}


gint redraw_till_x1_then_from_x2(gdouble x1, gdouble x2, gint staff, gint coeff)
{
  /*
   * x1: the position till redraw
   * x2: the position from where to redraw 
   * staff: the staff redrawed
   * coeff: the coefficient, how long above and below the staff ?
   */

/*   gtk_widget_queue_draw_area(Score.area, 0, */
/*                              Score.Staff[staff].extremity_begin_y - coeff, */
/*                              x1,  */
/*                              Score.Staff[staff].extremity_end_y + coeff); */
/*   gtk_widget_queue_draw_area(Score.area, x2, */
/*                              Score.Staff[staff].extremity_begin_y - coeff, */
/*                              Score.width,  */
/*                              Score.Staff[staff].extremity_end_y + coeff); */
  return 0;
}

gboolean mouse_motion_event(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{

        gdouble x;
        gdouble y;

        x = event->x;
        y = event->y;

        Selection.x = x;
        Selection.y = y;

        if ((Selection.x_origin != 0) && (Selection.y_origin != 0))
                {
                        draw_line(65535, 0, 0, Selection.x_origin, Selection.y_origin, Selection.x_origin, Selection.y);
                        draw_line(65535, 0, 0, Selection.x_origin, Selection.y_origin, Selection.x, Selection.y_origin);
                        draw_line(65535, 0, 0, Selection.x_origin, Selection.y, Selection.x, Selection.y);
                        draw_line(65535, 0, 0, Selection.x, Selection.y_origin, Selection.x, Selection.y);

                        

                        if ((Selection.x >= Selection.x_origin) && (Selection.y >= Selection.y_origin))
                                {
                                        /*    |    */
                                        /* ------- */
                                        /*    | X  */

                                        if (Selection.x > max_x)
                                                {
                                                        max_x = Selection.x;
                                                }
                                        
                                        if (Selection.y > max_y)
                                                {
                                                        max_y = Selection.y;
                                                }

					/*                                         printf("bottom/right\n"); */

                                        /* Clean inside the square */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x_origin + 1, Selection.y_origin + 1,
                                                                   Selection.x - Selection.x_origin - 1, 
                                                                   Selection.y - Selection.y_origin - 1);
                                        
                                        /* Clean around */
                                        /* (Right) */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x + 1, Selection.y_origin,
                                                                   max_x - Selection.x_origin, max_y - Selection.y_origin + 1);
                                        /* (Bottom) */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x_origin, Selection.y + 1,
                                                                   max_x - Selection.x_origin, max_y - Selection.y + 1);

                                }

                        if ((Selection.x < Selection.x_origin) && (Selection.y < Selection.y_origin))
                                {
                                        /*  X |    */
                                        /* ------- */
                                        /*    |    */

					/*                                         printf("top/left\n"); */

                                        if (!set_min_y) {
						min_y = Selection.y;
						set_min_y = TRUE;
					}
					
                                        if (Selection.y < min_y) {
						min_y = Selection.y;
					}
					
                                        if (!set_min_x) {
						min_x = Selection.x;
						set_min_x = TRUE;
					}
                                        
                                        if (Selection.x < min_x) {
						min_x = Selection.x;
					}

                                        /* Clean inside the square */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x + 1, Selection.y + 1,
                                                                   Selection.x_origin - Selection.x - 1, 
                                                                   Selection.y_origin - Selection.y - 1);

                                        /* Clean around */
                                        if (min_x < 0) min_x = 0;
                                        if (min_y < 0) min_y = 0;
                                        /* (Left) */
                                        gtk_widget_queue_draw_area(Score.area, min_x, min_y,
                                                                   Selection.x - min_x, 
                                                                   Selection.y_origin + 1);
                                        /* (Top) */
                                        gtk_widget_queue_draw_area(Score.area, min_x, min_y,
                                                                   Selection.x_origin - min_x + 1, Selection.y - min_y);

                                }

                        if ((Selection.x <= Selection.x_origin) && (Selection.y > Selection.y_origin))
                                {
                                        /*    |    */
                                        /* ------- */
                                        /*  X |    */

					/*                                         printf("bottom/left\n"); */


                                        if (!set_min_x)
                                                {
                                                        min_x = Selection.x;
                                                        set_min_x = TRUE;
                                                }
                                        
                                        if (Selection.x < min_x)
                                                {
                                                        min_x = Selection.x;
                                                }

                                        if (Selection.y > max_y)
                                                {
                                                        max_y = Selection.y;
                                                }


                                        /* Clean inside the square */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x + 1, Selection.y_origin + 1,
                                                                   Selection.x_origin - Selection.x - 1, 
                                                                   Selection.y - Selection.y_origin - 1);


                                        /* Clean around */
                                        if (min_x < 0) min_x = 0;
                                        /* (Left) */
                                        gtk_widget_queue_draw_area(Score.area, min_x, Selection.y_origin,
                                                                   Selection.x - min_x, 
                                                                   max_y - Selection.y_origin + 1);
                                        /* (Bottom) */
                                        gtk_widget_queue_draw_area(Score.area, Selection.x, Selection.y + 1,
                                                                   Selection.x_origin - min_x, 
                                                                   max_y - Selection.y);
                                }
                        
                }

	if ((Selection.x > Selection.x_origin) && (Selection.y <= Selection.y_origin))
		{
			/*    | X  */
			/* ------- */
			/*    |    */

			/*                                         printf("top/right\n"); */

			if (!set_min_y)
				{
					min_y = Selection.y;
					set_min_y = TRUE;
				}

			if (Selection.y < min_y)
				{
					min_y = Selection.y;
				}

			if (Selection.x > max_x)
				{
					max_x = Selection.x;
				}


			/* Clean inside the square */
			gtk_widget_queue_draw_area(Score.area, Selection.x_origin + 1, Selection.y + 1,
						   Selection.x - Selection.x_origin - 1, 
						   Selection.y_origin - Selection.y - 1);


			/* Clean around */
			if (min_y < 0) min_y = 0;
			/* (Right) */
			gtk_widget_queue_draw_area(Score.area, Selection.x + 1, min_y,
						   max_x - Selection.x + 1, 
						   Selection.y_origin - min_y + 1);
			/* (Top) */
			gtk_widget_queue_draw_area(Score.area, Selection.x_origin, min_y,
						   max_x - Selection.x_origin,
						   Selection.y - min_y);
		}

	return FALSE;
}


/*         printf("Mouse moving\n"); */

/*      GdkGC    * gc; */
/*      gdouble x, y; */
/*      gint position; */

/*      gint offset = 0; */

/*      x = event->x; */
/*      y = event->y; */

/*      gc = gdk_gc_new(Score.area->window); */

/* /\*      if (DEBUG == 1) *\/ */
/* /\*        g_print("GDK_EVENT_MOTION\n"); *\/ */

/*      /\*  */
/*       * When the mouse moves upon the staff, you should redraw absolutely everything */
/*       *\/ */

/*      if ((Selection.x_origin >= 0) && (Selection.y_origin >= 0)) */
/*        { */
/*          if (DEBUG == 1) */
/*            g_print("X = %f, Y = %f\n", x, y); */

/*          do_selection(Selection.x_origin, Selection.y_origin, x, y); */
/* /\*          g_print("you are selecting something\n"); *\/ */
/*        } else { */

/*          gtk_widget_queue_draw_area(GTK_WIDGET(Score.area),  */
/*                                     KeyCursor.x_returned - 50, KeyCursor.y_returned - 50 ,  */
/*                                     KeyCursor.x_returned + 50, KeyCursor.y_returned + 50); */
         
/*          switch (Selection.object_type) */
/* 	 { */
/* 	 case DOUBLEWHOLE: */
/* 	 case WHOLE: */
/* 		 offset = 0; */
/* 		 break; */
/* 	 case HALF: */
/* 	 case QUARTER: */
/* 	 case EIGHTH: */
/* 	 case SIXTEENTH: */
/* 		 offset = 21; */
/* 		 break; */
/* 	 default: */
/* 		 offset = 0; */
/* 	 } */


/*          KeyCursor.position = get_position(TREBLE_KEY, get_staff_selected(), y + offset); */

/*        } */
/* /\*          switch (Selection.note) *\/ */
/* /\*            { *\/ */

/* /\*            case DOUBLEWHOLE: *\/ */
/* /\*            case WHOLE: *\/ */
/* /\* /\\*              position = get_position(TREBLE_KEY, get_staff_selected(), y+21); *\\/ *\/ */
          
/* /\* /\\*              switch(position) *\\/ *\/ */
/* /\* /\\*                { *\\/ *\/ */
/* /\* /\\*                case 12: *\\/ *\/ */
/* /\* /\\*                case 13: *\\/ *\/ */
/* /\* /\\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y); *\\/ *\/ */
/* /\* /\\*                  draw_lines_for_object(get_staff_selected(), TRUE,  *\\/ *\/ */
/* /\* /\\*                                        3, x); *\\/ *\/ */
/* /\* /\\*                  break; *\\/ *\/ */
/* /\* /\\*                case 10: *\\/ *\/ */
/* /\* /\\*                case 11: *\\/ *\/ */
/* /\* /\\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y); *\\/ *\/ */
/* /\* /\\*                  draw_lines_for_object(get_staff_selected(), TRUE,  *\\/ *\/ */
/* /\* /\\*                                        2, x); *\\/ *\/ */
/* /\* /\\*                  break; *\\/ *\/ */
/* /\* /\\*                case 8: *\\/ *\/ */
/* /\* /\\*                case 9: *\\/ *\/ */
/* /\* /\\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y); *\\/ *\/ */
/* /\* /\\*                  draw_lines_for_object(get_staff_selected(), TRUE,  *\\/ *\/ */
/* /\* /\\*                                        1, x); *\\/ *\/ */
/* /\* /\\*                  break; *\\/ *\/ */
/* /\* /\\*                case 7: *\\/ *\/ */
/* /\* /\\*                case 6: *\\/ *\/ */
/* /\* /\\*           case 5: *\\/ *\/ */
/* /\* /\\*                case 4: *\\/ *\/ */
/* /\* /\\*                case 3: *\\/ *\/ */
/* /\* /\\*                case 2: *\\/ *\/ */
/* /\* /\\*                case 1: *\\/ *\/ */
/* /\* /\\*                case 0: *\\/ *\/ */
/* /\* /\\*                case -1: *\\/ *\/ */
/* /\* /\\*                case -2: *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y + 21); *\\/ *\/ */
/* /\* /\\*                  break; *\\/ *\/ */
/* /\* /\\*                case -4: *\\/ *\/ */
/* /\* /\\*                case -5: *\\/ *\/ */
/* /\* /\\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, y + 50 , x + 20, y + 8); *\\/ *\/ */
/* /\* /\\*                  draw_lines_for_object(get_staff_selected(), FALSE,  *\\/ *\/ */
/* /\* /\\*                                        1, x); *\\/ *\/ */
/* /\* /\\*                case -6: *\\/ *\/ */
/* /\* /\\*                case -7: *\\/ *\/ */
/* /\* /\\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, y + 50 , x + 20, y + 8); *\\/ *\/ */
/* /\* /\\*                  draw_lines_for_object(get_staff_selected(), FALSE,  *\\/ *\/ */
/* /\* /\\*                                        2, x); *\\/ *\/ */
/* /\* /\\*                  break; *\\/ *\/ */
/* /\* /\\*                } *\\/ *\/ */
         
/* /\*              break; *\/ */
/* /\*            case HALF: *\/ */
/* /\*            case QUARTER: *\/ */
/* /\*            case EIGHTH: *\/ */
/* /\*            case SIXTEENTH: *\/ */
/* /\*              position = get_position(TREBLE_KEY, get_staff_selected(), y+21); *\/ */
          
/* /\*              switch(position) *\/ */
/* /\*                { *\/ */
/* /\*                case 12: *\/ */
/* /\*                case 13: *\/ */
/* /\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y + 21); *\/ */
/* /\*                  draw_lines_for_object(get_staff_selected(), TRUE,  *\/ */
/* /\*                                        3, x); *\/ */
/* /\*                  break; *\/ */
/* /\*                case 10: *\/ */
/* /\*                case 11: *\/ */
/* /\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y + 21); *\/ */
/* /\*                  draw_lines_for_object(get_staff_selected(), TRUE,  *\/ */
/* /\*                                        2, x); *\/ */
/* /\*                  break; *\/ */
/* /\*                case 8: *\/ */
/* /\*                case 9: *\/ */
/* /\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\/ */
/* /\*                  /\\*             gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x-10, y-10, x+20, y+20); *\\/ *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y + 21); *\/ */
/* /\*             draw_lines_for_object(get_staff_selected(), TRUE,  *\/ */
/* /\*                                   1, x); *\/ */
/* /\*             break; *\/ */
/* /\*                case 7: *\/ */
/* /\*                case 6: *\/ */
/* /\*           case 5: *\/ */
/* /\*                case 4: *\/ */
/* /\*                case 3: *\/ */
/* /\*                case 2: *\/ */
/* /\*                case 1: *\/ */
/* /\*                case 0: *\/ */
/* /\*                case -1: *\/ */
/* /\*                case -2: *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, 0 , x + 20, y + 21); *\/ */
/* /\*                  break; *\/ */
                 
/* /\* /\\*           case 6: *\\/ *\/ */
/* /\* /\\*           case 7: *\\/ *\/ */
/* /\* /\\*             redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\\/ *\/ */
/* /\* /\\*             break; *\\/ *\/ */
/* /\* /\\*           case 5: *\\/ *\/ */
/* /\* /\\*                  draw_placement(x+2, y+25); *\\/ *\/ */
/* /\*                  break; *\/ */
/* /\*                case -4: *\/ */
/* /\*                case -5: *\/ */
/* /\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, y + 50 , x + 20, y + 8); *\/ */
/* /\*                  draw_lines_for_object(get_staff_selected(), FALSE,  *\/ */
/* /\*                                        1, x); *\/ */
/* /\*                case -6: *\/ */
/* /\*                case -7: *\/ */
/* /\*                  redraw_till_x1_then_from_x2(x-4, x+12, get_staff_selected(), 50); *\/ */
/* /\*                  gtk_widget_queue_draw_area(GTK_WIDGET(Score.area), x - 20, y + 50 , x + 20, y + 8); *\/ */
/* /\*                  draw_lines_for_object(get_staff_selected(), FALSE,  *\/ */
/* /\*                                        2, x); *\/ */
/* /\*                  break; *\/ */
/* /\*                } *\/ */
/* /\*              break; *\/ */
/* /\*            } *\/ */
/* /\*        } *\/ */

/*      return FALSE; */
/* } */

