
INCLUDES    = $(gtkmm_CFLAGS) $(gtkglextmm_CFLAGS) $(CGAL_CPPFLAGS)
LIBS        = $(gtkmm_LIBS)   $(gtkglextmm_LIBS) $(CGAL_LIBS)
AM_LDFLAGS  = $(CGAL_LDFLAGS)
AM_CXXFLAGS = -g -O0 -Werror -Wall -pedantic $(CGAL_CXXFLAGS) -frounding-math

bin_PROGRAMS = tangy-gtk test

tangy_gtk_SOURCES = tangy-gtk.cc algebra.cc
test_SOURCES = test.cc controller.hcc controller.h algebra.cc


