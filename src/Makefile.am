
AM_CPPFLAGS = \
	$(gtkmm_CFLAGS)      \
	$(gtkglextmm_CFLAGS) \
	$(CGAL_CPPFLAGS)     \
	$(BOOST_CPPFLAGS)    \
	-DDATADIR="\"$(pkgdatadir)\""

LIBS = \
	$(gtkmm_LIBS)         \
	$(gtkglextmm_LIBS)    \
	$(CGAL_LIBS)          \
	$(GLEW_LIBS)          \
	$(BOOST_SYSTEM_LIB)   \
	-lboost_system

AM_LDFLAGS = \
	$(CGAL_LDFLAGS)     \
	$(GLEW_LDFLAGS)     \
	$(BOOST_LDFLAGS)

AM_CXXFLAGS = \
	-Werror -Wall     \
	$(CGAL_CXXFLAGS)  \
	-frounding-math

bin_PROGRAMS = tangy-gtk

tangy_gtk_SOURCES = algebra.cc algebra.h algebra.hcc    \
                    controller.h controller.hcc         \
                    geometry.h geometry.hcc             \
                    render_basic.h render_basic.hcc     \
                    resources.cc resources.h            \
                    tangy-gtk.cc                        \
                    tans.h tans.hcc                     \
                    tans_nocollide.h tans_nocollide.hcc \
                    traits_nocollide.h                  \
                    utils.h utils.hcc

