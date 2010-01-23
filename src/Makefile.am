
AM_CPPFLAGS = $(gtkmm_CFLAGS) $(gtkglextmm_CFLAGS) $(CGAL_CPPFLAGS)
LIBS        = $(gtkmm_LIBS)   $(gtkglextmm_LIBS) $(CGAL_LIBS)
AM_LDFLAGS  = $(CGAL_LDFLAGS)
AM_CXXFLAGS = -Werror -Wall -pedantic $(CGAL_CXXFLAGS) -frounding-math

bin_PROGRAMS = tangy-gtk

tangy_gtk_SOURCES = algebra.cc algebra.h algebra.hcc    \
                    controller.h controller.hcc         \
                    geometry.h geometry.hcc             \
                    render_basic.h render_basic.hcc     \
                    tangy-gtk.cc                        \
                    tans.h tans.hcc                     \
                    tans_nocollide.h tans_nocollide.hcc \
                    traits_nocollide.h                  \
                    utils.h utils.hcc

