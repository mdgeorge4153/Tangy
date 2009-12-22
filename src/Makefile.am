
INCLUDES    = $(gtkmm_CFLAGS) $(gtkglextmm_CFLAGS) $(CGAL_CPPFLAGS)
LIBS        = $(gtkmm_LIBS)   $(gtkglextmm_LIBS) $(CGAL_LIBS)
AM_LDFLAGS  = $(CGAL_LDFLAGS)
AM_CXXFLAGS = -g -Werror -Wall -pedantic $(CGAL_CXXFLAGS) -frounding-math

bin_PROGRAMS = gtans2 test

gtans2_SOURCES = gtans.cc algebra.cc
test_SOURCES = test.cc controller.hcc controller.h algebra.cc


