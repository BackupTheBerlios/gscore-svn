/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/* gdkcairo - replacing a gdkwindow with a cairo surface
 *
 * Copyright © 2003, 2004  Carl D. Worth <carl@theworths.org>
 *                         Evan Martin   <martine@danga.com>
 *                         Øyvind Kolås  <oeyvindk@hig.no>
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

#include <stdio.h>
#include <stdlib.h>

#include <gdk/gdkx.h>
#include "gdkcairo.h"
#include <cairo-xlib.h>
#include <string.h>

/* #ifdef CAIRO_HAS_XLIB_SURFACE */
/* #include <cairo-xlib.h> */
/* #endif */

#define SIZE 100

static void
gdkcairo_init (gdkcairo_t *self,
               GtkWidget  *widget)
{
        Display *dpy;
        Drawable drawable;
        Visual *visual;
        cairo_surface_t *surface;
        GdkDrawable *real_drawable;
        gint x_off, y_off;




        /* Unabstract X from GTK+ */
/*         gdk_window_get_internal_paint_info (widget->window, &real_drawable, &x_off, &y_off); */
        dpy = gdk_x11_drawable_get_xdisplay (widget);
        drawable = gdk_x11_drawable_get_xid (widget);

        /* Ignore GTK+ and use Cairo for drawing. */
        visual = GDK_VISUAL_XVISUAL (gdk_drawable_get_visual (widget));
        surface = cairo_xlib_surface_create (dpy, drawable, visual,
                                             widget->allocation.width,
                                             widget->allocation.height);

        self->widget = widget;
        self->cr = cairo_create (surface); /* FIXME: NULL will segfault */


        self->backend = GDKCAIRO_BACKEND_IMAGE;
#ifdef CAIRO_HAS_XLIB_SURFACE
        self->backend = GDKCAIRO_BACKEND_XLIB;
#endif
#ifdef USE_GL
        {
                char     *GTKCAIRO_GL = getenv ("GTKCAIRO_GL");
                if (GTKCAIRO_GL && atoi (GTKCAIRO_GL))
                        self->backend = GDKCAIRO_BACKEND_GL;
        }
#endif
        {
                char     *GDKCAIRO_BACKEND = getenv ("GTKCAIRO_BACKEND");
                if (GDKCAIRO_BACKEND)
                        {
                                if (!strcmp (GDKCAIRO_BACKEND, "image"))
                                        {
                                                self->backend = GDKCAIRO_BACKEND_IMAGE;
                                        }
#ifdef CAIRO_HAS_XLIB_SURFACE
                                else if (!strcmp (GDKCAIRO_BACKEND, "xlib"))
                                        {
                                                self->backend = GDKCAIRO_BACKEND_XLIB;
                                        }
#endif
#ifdef USE_GL
                                else if (!strcmp (GDKCAIRO_BACKEND, "gl"))
                                        {
                                                self->backend = GDKCAIRO_BACKEND_GL;
                                        }
#endif
                                else
                                        {
                                                self->backend = GDKCAIRO_BACKEND_IMAGE;
#ifdef CAIRO_HAS_XLIB_SURFACE
                                                self->backend = GDKCAIRO_BACKEND_XLIB;
#endif
                                                fprintf (stderr, "unknown GTKCAIRO_BACKEND '%s' falling back\n",
                                                         GDKCAIRO_BACKEND);
                                        }
                        }
        }

        switch (self->backend)
                {
                case GDKCAIRO_BACKEND_IMAGE:
                        break;
#ifdef CAIRO_HAS_XLIB_SURFACE
                case GDKCAIRO_BACKEND_XLIB:
                        break;
#endif
#ifdef USE_GL
                case GDKCAIRO_BACKEND_GL:
                        self->glitz_surface = NULL;
                        break;
#endif
                default:
                        g_assert (0);
                        break;
                }
}

gdkcairo_t *
gdkcairo_new (GtkWidget   *widget)
{
        gdkcairo_t *self = malloc (sizeof (gdkcairo_t));
        gdkcairo_init (self, widget);
        return self;
}

void
gdkcairo_destroy (gdkcairo_t *self)
{
        if (self->cr)
                {
                        cairo_destroy (self->cr);
                        self->cr = NULL;
                }
}

void
gdkcairo_realize (gdkcairo_t *self)
{
        GtkWidget *widget = self->widget;
        GdkWindowAttr attributes;
        gint      attributes_mask;

        g_return_if_fail (widget != NULL);

        GTK_WIDGET_SET_FLAGS (self->widget, GTK_REALIZED);

        attributes.x = widget->allocation.x;
        attributes.y = widget->allocation.y;
        attributes.width = widget->allocation.width;
        attributes.height = widget->allocation.height;
        attributes.wclass = GDK_INPUT_OUTPUT;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.event_mask = gtk_widget_get_events (widget) | GDK_EXPOSURE_MASK;
        attributes.visual = gtk_widget_get_visual (widget);

 retry:
        switch (self->backend)
                {
                case GDKCAIRO_BACKEND_IMAGE:
                        break;
#ifdef CAIRO_HAS_XLIB_SURFACE
                case GDKCAIRO_BACKEND_XLIB:
                        attributes.colormap = gtk_widget_get_colormap (widget);

                        attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
                        widget->window = gdk_window_new (widget->parent->window,
                                                         &attributes, attributes_mask);

                        break;
#endif
#ifdef USE_GL
                case GDKCAIRO_BACKEND_GL:
                        {
                                Display  *dpy = gdk_x11_get_default_xdisplay ();
                                int       screen = gdk_x11_get_default_screen ();
                                XVisualInfo *vinfo;
                                glitz_drawable_format_t *dformat;
                                glitz_drawable_format_t templ;
                                unsigned long mask;
                                char     *GTKCAIRO_GL_DOUBLEBUFFER;
                                char     *GTKCAIRO_GL_SAMPLES;

                                GTKCAIRO_GL_DOUBLEBUFFER = getenv ("GTKCAIRO_GL_DOUBLEBUFFER");
                                GTKCAIRO_GL_SAMPLES = getenv ("GTKCAIRO_GL_SAMPLES");

                                templ.types.window = 1;
                                mask = GLITZ_FORMAT_WINDOW_MASK;

                                if (GTKCAIRO_GL_DOUBLEBUFFER)
                                        {
                                                if (atoi (GTKCAIRO_GL_DOUBLEBUFFER))
                                                        templ.doublebuffer = 1;
                                                else
                                                        templ.doublebuffer = 0;

                                                mask |= GLITZ_FORMAT_DOUBLEBUFFER_MASK;
                                        }

                                if (GTKCAIRO_GL_SAMPLES)
                                        {
                                                templ.samples = atoi (GTKCAIRO_GL_SAMPLES);

                                                /* less than 1 sample is not possible */
                                                if (templ.samples < 1)
                                                        templ.samples = 1;

                                                mask |= GLITZ_FORMAT_SAMPLES_MASK;
                                        }

                                dformat =
                                        glitz_glx_find_drawable_format (dpy, screen, mask, &templ, 0);

                                if (dformat)
                                        {
                                                glitz_drawable_t *drawable;
                                                glitz_format_t *format;
                                                XID       xid;

                                                vinfo = glitz_glx_get_visual_info_from_format (dpy, screen,
                                                                                               dformat);
                                                gtk_widget_set_double_buffered (widget, FALSE);
                                                attributes.visual = gdkx_visual_get (vinfo->visualid);
                                                attributes.colormap = gdk_colormap_new (attributes.visual, TRUE);

                                                attributes_mask =
                                                        GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;

                                                widget->window =
                                                        gdk_window_new (gtk_widget_get_parent_window (widget),
                                                                        &attributes, attributes_mask);

                                                xid = gdk_x11_drawable_get_xid (widget->window);

                                                drawable =
                                                        glitz_glx_create_drawable_for_window (dpy, screen,
                                                                                              dformat, xid,
                                                                                              attributes.width,
                                                                                              attributes.height);
                                                format = glitz_find_standard_format (drawable,
                                                                                     GLITZ_STANDARD_ARGB32);
                                                self->glitz_surface =
                                                        glitz_surface_create (drawable,
                                                                              format,
                                                                              attributes.width,
                                                                              attributes.height,
                                                                              0, NULL);

                                                glitz_surface_attach (self->glitz_surface,
                                                                      drawable,
                                                                      (dformat->doublebuffer) ?
                                                                      GLITZ_DRAWABLE_BUFFER_BACK_COLOR :
                                                                      GLITZ_DRAWABLE_BUFFER_FRONT_COLOR, 0, 0);

                                                glitz_drawable_destroy (drawable);

                                                cairo_set_target_glitz (self->cr, self->glitz_surface);
                                        }
                                else
                                        {
                                                g_warning ("could not find a usable GL visual\n");
                                                self->backend = GDKCAIRO_BACKEND_XLIB;
                                                goto retry;
                                        }
                        }
                        break;
#endif
                default:
                        break;
                }

        gtk_style_attach (widget->style, widget->window);
        gtk_style_set_background (widget->style, widget->window, GTK_STATE_NORMAL);
        gdk_window_set_user_data (widget->window, widget);
}

void
gdkcairo_size_allocate (gdkcairo_t *self,
                        gint        x,
                        gint        y,
                        gint        width,
                        gint        height)
{
        if (GTK_WIDGET_REALIZED (self->widget))
                {
                        gdk_window_move_resize (self->widget->window, x, y, width, height);

                        switch (self->backend)
                                {
#ifdef CAIRO_HAS_XLIB_SURFACE
                                case GDKCAIRO_BACKEND_XLIB:
                                        break;
#endif
#ifdef USE_GL
                                case GDKCAIRO_BACKEND_GL:
                                        if (self->glitz_surface)
                                                {
                                                        glitz_format_t *format;
                                                        glitz_drawable_t *drawable;
                                                        glitz_drawable_format_t *dformat;

                                                        format = glitz_surface_get_format (self->glitz_surface);
                                                        drawable = glitz_surface_get_drawable (self->glitz_surface);
                                                        dformat = glitz_drawable_get_format (drawable);

                                                        glitz_surface_destroy (self->glitz_surface);

                                                        glitz_drawable_update_size (drawable, width, height);

                                                        self->glitz_surface =
                                                                glitz_surface_create (drawable, format, width, height,
                                                                                      0, NULL);

                                                        glitz_surface_attach (self->glitz_surface,
                                                                              drawable,
                                                                              (dformat->doublebuffer) ?
                                                                              GLITZ_DRAWABLE_BUFFER_BACK_COLOR :
                                                                              GLITZ_DRAWABLE_BUFFER_FRONT_COLOR, 0, 0);

                                                        cairo_set_target_glitz (self->cr, self->glitz_surface);
                                                }

                                        break;
#endif
                                default:
                                        g_assert (0);
                                        break;
                                }
                }
}

gint
gdkcairo_expose (gdkcairo_t     *self,
                 GdkEventExpose *event)
{
        GtkWidget *widget = self->widget;
        Display *dpy = XOpenDisplay (NULL);
        int screen = DefaultScreen (dpy);

        g_return_val_if_fail (widget != NULL, FALSE);
        g_return_val_if_fail (event != NULL, FALSE);

        switch (self->backend)
                {
#ifdef USE_GL
                case GDKCAIRO_BACKEND_GL:
                        {
                                glitz_drawable_t *drawable;
                                glitz_drawable_format_t *dformat;

                                cairo_save (self->cr);
                                cairo_rectangle (self->cr, 0, 0, widget->allocation.width,
                                                 widget->allocation.height);
                                gtk_cairo_set_gdk_color (self->cr,
                                                         &(self->widget->style->bg[GTK_STATE_NORMAL]));
                                cairo_fill (self->cr);
                                cairo_restore (self->cr);

                                g_signal_emit_by_name (self->widget, "paint", self->cr);

                                drawable = glitz_surface_get_drawable (self->glitz_surface);
                                dformat = glitz_drawable_get_format (drawable);

                                glitz_surface_flush (self->glitz_surface);

                                if (dformat->doublebuffer)
                                        glitz_drawable_swap_buffers (drawable);
                                else
                                        glitz_drawable_flush (drawable);
                        }
                        break;
#endif
#ifdef CAIRO_HAS_XLIB_SURFACE
                case GDKCAIRO_BACKEND_XLIB:
                        {
                                GdkDrawable *gdkdrawable;
                                gint      x_off, y_off;

                                gdk_window_get_internal_paint_info (widget->window,
                                                                    &gdkdrawable, &x_off, &y_off);

/*                                 cairo_xlib_surface_create (self->cr, */
/*                                                            gdk_x11_drawable_get_xdisplay(gdkdrawable), */
/*                                                            DefaultVisual(dpy, screen), */
/*                                                            SIZE, SIZE); */
/*                                                            gdk_x11_drawable_get_xid (gdkdrawable)); */

                                /* counter offset of expose */
                                if (x_off || y_off)
                                        {
                                                cairo_save (self->cr);
                                                cairo_translate (self->cr, -x_off, -y_off);
                                        }

                                g_signal_emit_by_name (self->widget, "paint", self->cr);

                                if (x_off || y_off)
                                        {
                                                cairo_restore (self->cr);
                                        }
                        }
                        break;
#endif
                default:
                        g_assert (0);
                }
        return FALSE;
}
