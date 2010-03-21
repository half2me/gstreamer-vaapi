/*
 *  gstvaapiwindow.h - VA window abstraction
 *
 *  gstreamer-vaapi (C) 2010 Splitted-Desktop Systems
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef GST_VAAPI_WINDOW_H
#define GST_VAAPI_WINDOW_H

#include <gst/video/gstvideosink.h>
#include <gst/vaapi/gstvaapidisplay.h>
#include <gst/vaapi/gstvaapisurface.h>

G_BEGIN_DECLS

#define GST_VAAPI_TYPE_WINDOW \
    (gst_vaapi_window_get_type())

#define GST_VAAPI_WINDOW(obj)                           \
    (G_TYPE_CHECK_INSTANCE_CAST((obj),                  \
                                GST_VAAPI_TYPE_WINDOW,  \
                                GstVaapiWindow))

#define GST_VAAPI_WINDOW_CLASS(klass)                   \
    (G_TYPE_CHECK_CLASS_CAST((klass),                   \
                             GST_VAAPI_TYPE_WINDOW,     \
                             GstVaapiWindowClass))

#define GST_VAAPI_IS_WINDOW(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_VAAPI_TYPE_WINDOW))

#define GST_VAAPI_IS_WINDOW_CLASS(klass) \
    (G_TYPE_CHECK_CLASS_TYPE((klass), GST_VAAPI_TYPE_WINDOW))

#define GST_VAAPI_WINDOW_GET_CLASS(obj)                 \
    (G_TYPE_INSTANCE_GET_CLASS((obj),                   \
                               GST_VAAPI_TYPE_WINDOW,   \
                               GstVaapiWindowClass))

typedef struct _GstVaapiWindow                  GstVaapiWindow;
typedef struct _GstVaapiWindowPrivate           GstVaapiWindowPrivate;
typedef struct _GstVaapiWindowClass             GstVaapiWindowClass;

/**
 * GstVaapiWindow:
 *
 * Base class for system-dependent windows.
 */
struct _GstVaapiWindow {
    /*< private >*/
    GObject parent_instance;

    /*< private >*/
    GstVaapiWindowPrivate *priv;
};

/**
 * GstVaapiWindowClass:
 * @create: virtual function to create a window with width and height
 * @destroy: virtual function to destroy a window
 * @show: virtual function to show (map) a window
 * @hide: virtual function to hide (unmap) a window
 * @resize: virtual function to resize a window
 * @render: virtual function to render a #GstVaapiSurface into a window
 *
 * Base class for system-dependent windows.
 */
struct _GstVaapiWindowClass {
    /*< private >*/
    GObjectClass parent_class;

    gboolean    (*create) (GstVaapiWindow *window, guint *width, guint *height);
    void        (*destroy)(GstVaapiWindow *window);
    gboolean    (*show)   (GstVaapiWindow *window);
    gboolean    (*hide)   (GstVaapiWindow *window);
    gboolean    (*resize) (GstVaapiWindow *window, guint width, guint height);
    gboolean    (*render) (GstVaapiWindow *window,
                           GstVaapiSurface *surface,
                           const GstVideoRectangle *src_rect,
                           const GstVideoRectangle *dst_rect,
                           guint flags);
};

GType
gst_vaapi_window_get_type(void);

void
gst_vaapi_window_show(GstVaapiWindow *window);

void
gst_vaapi_window_hide(GstVaapiWindow *window);

guint
gst_vaapi_window_get_width(GstVaapiWindow *window);

guint
gst_vaapi_window_get_height(GstVaapiWindow *window);

void
gst_vaapi_window_get_size(GstVaapiWindow *window, guint *pwidth, guint *pheight);

void
gst_vaapi_window_set_width(GstVaapiWindow *window, guint width);

void
gst_vaapi_window_set_height(GstVaapiWindow *window, guint height);

void
gst_vaapi_window_set_size(GstVaapiWindow *window, guint width, guint height);

gboolean
gst_vaapi_window_put_surface(
    GstVaapiWindow          *window,
    GstVaapiSurface         *surface,
    const GstVideoRectangle *src_rect,
    const GstVideoRectangle *dst_rect,
    guint                    flags
);

G_END_DECLS

#endif /* GST_VAAPI_WINDOW_H */
