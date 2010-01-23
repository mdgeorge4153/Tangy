dnl == autoconf initialization =================================================

AC_INIT([tangy], [0.0], [mdgeorge@cs.cornell.edu])

AC_CONFIG_SRCDIR([src/tangy-gtk.cc])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])

dnl == checks ==================================================================

# checks for programs

AC_PROG_CXX
AC_LANG([C++])

# checks for libraries

PKG_CHECK_MODULES(gtkmm, [gtkmm-2.4])
AC_SUBST(gtkmm_CFLAGS)
AC_SUBST(gtkmm_LIBS)

PKG_CHECK_MODULES(gtkglextmm, [gtkglextmm-1.2])
AC_SUBST(gtkglextmm_CFLAGS)
AC_SUBST(gtkglextmm_LIBS)

ACX_CGAL()
AC_SUBST(CGAL_CPPFLAGS)
AC_SUBST(CGAL_CXXFLAGS)
AC_SUBST(CGAL_LDFLAGS)
AC_SUBST(CGAL_LIBS)

# checks for header files
# checks for functions
# checks for types and structures
# checks for compiler characteristics
# checks for library functions
# checks for system services

dnl == output ==================================================================

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	data/Makefile])
AC_OUTPUT

dnl == summary =================================================================


