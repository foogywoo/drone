#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "agg_basics.h"
#include "agg_rendering_buffer.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_scanline_u.h"
#include "agg_renderer_scanline.h"
#include "agg_path_storage.h"
#include "agg_conv_transform.h"
#include "agg_trans_affine.h"
#include "agg_trans_bilinear.h"
#include "agg_trans_perspective.h"
#include "agg_span_interpolator_linear.h"
#include "agg_span_interpolator_trans.h"
#include "agg_span_subdiv_adaptor.h"
#include "agg_pixfmt_rgba.h"
#include "agg_span_image_filter_rgba.h"
#include "ctrl/agg_rbox_ctrl.h"
#include "platform/agg_platform_support.h"
#include "interactive_polygon.h"


enum flip_y_e { flip_y = true };

agg::rasterizer_scanline_aa<> g_rasterizer;
agg::scanline_u8  g_scanline;
double            g_x1 = 0;
double            g_y1 = 0;
double            g_x2 = 0;
double            g_y2 = 0;



class the_application : public agg::platform_support
{
public:
    typedef agg::pixfmt_bgra32                             pixfmt;
    typedef pixfmt::color_type                             color_type;
    typedef agg::renderer_base<pixfmt>                     renderer_base;
    typedef agg::renderer_scanline_aa_solid<renderer_base> renderer_solid;

    typedef agg::pixfmt_bgra32_pre         pixfmt_pre;
    typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;

    agg::interactive_polygon   m_quad;
    agg::rbox_ctrl<agg::rgba8> m_trans_type;

    the_application(agg::pix_format_e format, bool flip_y) :
        agg::platform_support(format, flip_y),
        m_quad(4, 5.0),
        m_trans_type(420, 5.0, 420+170.0, 70.0, !flip_y)
    {
        m_trans_type.add_item("Affine Parallelogram");
        m_trans_type.add_item("Bilinear");
        m_trans_type.add_item("Perspective");
        m_trans_type.cur_item(2);
        add_ctrl(m_trans_type);
    }


    virtual void on_init()
    {
        g_x1 = 0.0;
        g_y1 = 0.0;
        g_x2 = rbuf_img(0).width();
        g_y2 = rbuf_img(0).height();

        double x1 = g_x1;// * 100.0;
        double y1 = g_y1;// * 100.0;
        double x2 = g_x2;// * 100.0;
        double y2 = g_y2;// * 100.0;

        double dx = width()  / 2.0 - (x2 - x1) / 2.0;
        double dy = height() / 2.0 - (y2 - y1) / 2.0;
        m_quad.xn(0) = floor(x1 + dx);
        m_quad.yn(0) = floor(y1 + dy);
        m_quad.xn(1) = floor(x2 + dx);
        m_quad.yn(1) = floor(y1 + dy);
        m_quad.xn(2) = floor(x2 + dx);
        m_quad.yn(2) = floor(y2 + dy);
        m_quad.xn(3) = floor(x1 + dx);
        m_quad.yn(3) = floor(y2 + dy);
    }

    virtual void on_draw()
    {
        pixfmt            pixf(rbuf_window());
        pixfmt_pre        pixf_pre(rbuf_window());
        renderer_base     rb(pixf);
        renderer_base_pre rb_pre(pixf_pre);

        renderer_solid r(rb);


        rb.clear(agg::rgba(1, 1, 1));

        if(m_trans_type.cur_item() == 0)
        {
            // For the affine parallelogram transformations we
            // calculate the 4-th (implicit) point of the parallelogram
            m_quad.xn(3) = m_quad.xn(0) + (m_quad.xn(2) - m_quad.xn(1));
            m_quad.yn(3) = m_quad.yn(0) + (m_quad.yn(2) - m_quad.yn(1));
        }

        //--------------------------
        // Render the "quad" tool and controls
        g_rasterizer.add_path(m_quad);
        r.color(agg::rgba(0, 0.3, 0.5, 0.6));
        agg::render_scanlines(g_rasterizer, g_scanline, r);

        // Prepare the polygon to rasterize. Here we need to fill
        // the destination (transformed) polygon.
        g_rasterizer.clip_box(0, 0, width(), height());
        g_rasterizer.reset();
        g_rasterizer.move_to_d(m_quad.xn(0), m_quad.yn(0));
        g_rasterizer.line_to_d(m_quad.xn(1), m_quad.yn(1));
        g_rasterizer.line_to_d(m_quad.xn(2), m_quad.yn(2));
        g_rasterizer.line_to_d(m_quad.xn(3), m_quad.yn(3));


        typedef agg::span_allocator<agg::rgba8> span_alloc_type;
        span_alloc_type sa;
        agg::image_filter_hermite filter_kernel;
        agg::image_filter_lut filter(filter_kernel, false);

        start_timer();
        switch(m_trans_type.cur_item())
        {
            case 0:
            {

                // Note that we consruct an affine matrix that transforms
                // a parallelogram to a rectangle, i.e., it's inverted.
                // It's actually the same as:
                // tr(g_x1, g_y1, g_x2, g_y2, m_triangle.polygon());
                // tr.invert();
                agg::trans_affine tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);

                // Also note that we can use the linear interpolator instead of 
                // arbitrary span_interpolator_trans. It works much faster, 
                // but the transformations must be linear and parellel.
                typedef agg::span_interpolator_linear<agg::trans_affine> interpolator_type;
                interpolator_type interpolator(tr);

                typedef agg::span_image_filter_rgba_nn<color_type, 
                                                        agg::order_bgra, 
                                                        interpolator_type> span_gen_type;
                typedef agg::renderer_scanline_aa<renderer_base_pre, span_gen_type> renderer_type;

                span_gen_type sg(sa, 
                                 rbuf_img(0), 
                                 agg::rgba_pre(0, 0, 0, 0),
                                 interpolator);
//                                 filter);

                renderer_type ri(rb_pre, sg);
                agg::render_scanlines(g_rasterizer, g_scanline, ri);
                break;
            }

            case 1:
            {
                agg::trans_bilinear tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_linear<agg::trans_bilinear> interpolator_type;
                    interpolator_type interpolator(tr);

                    typedef agg::span_image_filter_rgba_2x2<color_type,
                                                            agg::order_bgra, 
                                                            interpolator_type> span_gen_type;
                    typedef agg::renderer_scanline_aa<renderer_base_pre, span_gen_type> renderer_type;

                    span_gen_type sg(sa, 
                                     rbuf_img(0), 
                                     agg::rgba_pre(0, 0, 0, 0),
                                     interpolator,
                                     filter);

                    renderer_type ri(rb_pre, sg);
                    agg::render_scanlines(g_rasterizer, g_scanline, ri);
                }
                break;
            }

            case 2:
            {
                agg::trans_perspective tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_linear<agg::trans_perspective> interpolator_type;
                    typedef agg::span_subdiv_adaptor<interpolator_type> subdiv_adaptor_type;
                    interpolator_type interpolator(tr);
                    subdiv_adaptor_type subdiv_adaptor(interpolator);

                    typedef agg::span_image_filter_rgba_2x2<color_type,
                                                            agg::order_bgra, 
                                                            subdiv_adaptor_type> span_gen_type;
                    typedef agg::renderer_scanline_aa<renderer_base_pre, span_gen_type> renderer_type;

                    span_gen_type sg(sa, 
                                     rbuf_img(0), 
                                     agg::rgba_pre(0, 0, 0, 0),
                                     subdiv_adaptor,
                                     filter);

                    renderer_type ri(rb_pre, sg);
                    agg::render_scanlines(g_rasterizer, g_scanline, ri);
                }
                break;
            }
        }
        double tm = elapsed_time();

        char buf[64]; 
        agg::gsv_text t;
        t.size(10.0);

        agg::conv_stroke<agg::gsv_text> pt(t);
        pt.width(1.5);

        sprintf(buf, "%3.2f ms", tm);
        t.start_point(10.0, 10.0);
        t.text(buf);

        g_rasterizer.add_path(pt);
        r.color(agg::rgba(0,0,0));
        agg::render_scanlines(g_rasterizer, g_scanline, r);


        //--------------------------
        agg::render_ctrl(g_rasterizer, g_scanline, r, m_trans_type);
    }



    virtual void on_mouse_button_down(int x, int y, unsigned flags)
    {
        if(flags & agg::mouse_left)
        {
            if(m_quad.on_mouse_button_down(x, y))
            {
                force_redraw();
            }
        }
    }


    virtual void on_mouse_move(int x, int y, unsigned flags)
    {
        if(flags & agg::mouse_left)
        {
            if(m_quad.on_mouse_move(x, y))
            {
                force_redraw();
            }
        }
        if((flags & agg::mouse_left) == 0)
        {
            on_mouse_button_up(x, y, flags);
        }
    }


    virtual void on_mouse_button_up(int x, int y, unsigned flags)
    {
        if(m_quad.on_mouse_button_up(x, y))
        {
            force_redraw();
        }
    }

};






int agg_main(int argc, char* argv[])
{
    the_application app(agg::pix_format_bgra32, flip_y);
    app.caption("AGG Example. Image Perspective Transformations");

    const char* img_name = "spheres";
    if(argc >= 2) img_name = argv[1];
    if(!app.load_img(0, img_name)) 
    {
        char buf[256];
        if(strcmp(img_name, "spheres") == 0)
        {
            sprintf(buf, "File not found: %s%s. Download http://www.antigrain.com/%s%s\n"
                         "or copy it from another directory if available.",
                    img_name, app.img_ext(), img_name, app.img_ext());
        }
        else
        {
            sprintf(buf, "File not found: %s%s", img_name, app.img_ext());
        }
        app.message(buf);
        return 1;
    }
    
/*
    // Testing the "black border" issue with alpha channel
    //----------------------------------------
    the_application::pixfmt pixf(app.rbuf_img(0));
    the_application::renderer_base rbase(pixf);
    the_application::renderer_solid ren(rbase);
    rbase.clear(agg::rgba8(0,0,0,0));
    unsigned i;
    for(i = 0; i < 50; i++)
    {
        agg::ellipse ell(rand() % rbase.width(), 
                         rand() % rbase.height(),
                         rand() % 20 + 5,
                         rand() % 20 + 5,
                         100);
        g_rasterizer.add_path(ell);
        ren.color(agg::rgba8((rand() & 0x7F) + 127, 
                             (rand() & 0x7F) + 127, 
                             (rand() & 0x7F) + 127, 
                             255));
        agg::render_scanlines(g_rasterizer, g_scanline, ren);
    }
*/

    if(app.init(600, 600, agg::window_resize))
    {
        return app.run();
    }
    return 1;
}






