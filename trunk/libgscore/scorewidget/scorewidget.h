/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/* scorewidget: a score widget for gscore
 *
 * (C) Sebastien Tricaud 2005
 * See AUTHORS file to see where I started from
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#ifndef GTK_CAIRO_H
#define GTK_CAIRO_H

#include <gtk/gtkwidget.h>
#include <cairo.h>

#ifdef __cplusplus
extern    "C"
{
#endif                          /* __cplusplus */

#define GTK_TYPE_CAIRO	(gtk_cairo_get_type())
#define SCORE_WIDGET(obj)	GTK_CHECK_CAST (obj, GTK_TYPE_CAIRO, GtkCairo)
#define SCORE_WIDGET_CLASS(klass) GTK_CHECK_CLASS_CAST (klass, GTK_TYPE_CAIRO, GtkCairoClass)
#define GTK_IS_SCORE_WIDGET(obj)	GTK_CHECK_TYPE (obj, GTK_TYPE_CAIRO)

  typedef struct _ScoreWidget ScoreWidget;
  typedef struct _ScoreWidgetClass ScoreWidgetClass;

#define gdkcairo_t void

  struct _ScoreWidget
  {
          GtkWidget widget;
          gdkcairo_t *gdkcairo;
  };

#undef gdkcairo_t

  struct _ScoreWidgetClass
  {
          GtkWidgetClass parent_class;
          void      (*paint) (ScoreWidget *, cairo_t *c);
          void      (*new_staff) (ScoreWidget *, cairo_t *c);
  };

  GType     score_widget_get_type (void);

  GtkWidget *score_widget_new (void);

  cairo_t  *score_widget_get_cairo (ScoreWidget *scorewidget);


/* convenience function to set the current cairo color
 * from a GdkColor
 */
  void      cairo_set_gdk_color (cairo_t  *cr,
                                 GdkColor *color);

#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* GTK_CAIRO_H */
