/**
 * draw_staff:
 * @sw: #ScoreWidget object
 * @cr: cairo_t pointer
 * @nb_lines: number of lines you want the staff to have
 * @space_btwn_lines:
 * @x1:
 * @y1:
 * @x2:
 * @selected: If we should draw the selected staff
 *
 * Draws a staff on the score widget and fills the cairo structure
 * 
 * Returns: 0 if success, -1 if failed.
 */

#include <gtk/gtk.h>
#include <cairo.h>

extern gint 
draw_staff(cairo_t *cr, 
           guint16 nb_lines, gdouble space_btwn_lines,
           gdouble x1, gdouble y1, gdouble x2,
           gboolean selected)
{

        const gdouble cairo_padding = 0.5;
        gdouble offset = 0;
	gint16 i = 0;

        cairo_set_rgb_color (cr, 0, 0, 0);

        while ( i < nb_lines ) {
                cairo_move_to(cr, x1, y1 + offset + cairo_padding);
                cairo_rel_line_to(cr, x2, 0);

                offset += space_btwn_lines;

                i++;
        }

/*         cairo_move_to (cr, x1, y1 + cairo_padding); */
/*         cairo_rel_line_to (cr, x2, 0); */
/*         cairo_move_to (cr, x1, 58.5); */
/*         cairo_rel_line_to (cr, x2, 0); */
/*         cairo_move_to (cr, x1, 66.5); */
/*         cairo_rel_line_to (cr, x2, 0); */
/*         cairo_move_to (cr, x1, 74.5); */
/*         cairo_rel_line_to (cr, x2, 0); */
/*         cairo_move_to (cr, x1, 82.5); */
/*         cairo_rel_line_to (cr, x2, 0); */

        cairo_set_line_width(cr, 1);
        cairo_stroke(cr);

}
