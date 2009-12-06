AC_INIT([gtans], [0.0], [mdgeorge@cs.cornell.edu])

AC_CONFIG_SRCDIR([src/gtans.cc])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE(gtans,0.1)

AC_PROG_CXX

PKG_CHECK_MODULES(gtkmm, [gtkmm-2.4])
AC_SUBST(gtkmm_CFLAGS)
AC_SUBST(gtkmm_LIBS)

AC_OUTPUT(Makefile src/Makefile data/Makefile)

