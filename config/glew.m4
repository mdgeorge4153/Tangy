
dnl
dnl AX_CHECK_GLEW(action-if-found, action-if-not-found): Check for GLEW
dnl
dnl Adapted from http://openlibraries.org/browser/trunk/m4/glew.m4?rev=1310
dnl
dnl This function takes two arguments: the action on success and the action on failure.
dnl If --with-glew=prefix is provided, then that prefix is checked for glew libraries and headers
dnl If --with-glew=no or --without-glew is provided, then the test fails
dnl Otherwise the standard locations are checked
dnl
dnl if the check is successful, then the variables glew_CPPFLAGS, glew_LDFLAGS and glew_LIBS are defined

AC_DEFUN([AX_CHECK_GLEW],[
	AC_ARG_WITH([glew],
	            [AC_HELP_STRING([--with-glew], [GLEW installation prefix directory])],
	            [],
	            [with_glew="yes"]
	)

	ax_have_glew="no"

	#
	# set CPPFLAGS and LDFLAGS according to --with-glew input
	#

	AS_IF([test x"$with_glew" == x"yes"],[
		GLEW_CPPFLAGS=""
		GLEW_LDFLAGS=""
	],[test x"$with_glew" != x"no"],[
		GLEW_CPPFLAGS="-I${with_glew}/include"
		GLEW_LDFLAGS="-L${with_glew}/lib"
	])

	#
	# check for library and header
	# 

	save_LDFLAGS="$LDFLAGS"
	LDFLAGS="$GLEW_LDFLAGS $LDFLAGS"

	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$GLEW_CPPFLAGS $CPPFLAGS"

	AS_IF([test x"$with_glew" != x"no"], [
		AC_CHECK_LIB([GLEW], [glewInit], [
			AC_CHECK_HEADER([GL/glew.h], [
				ax_have_glew="yes"
				GLEW_LIBS="-lGLEW"
			])
		])
	])

	LDFLAGS="$save_LDFLAGS"
	CPPFLAGS="$save_CPPFLAGS"

	#
	# output results
	#

	AC_MSG_CHECKING(glew)
	AS_IF([test x"$ax_have_glew" == x"yes"], [
		AC_MSG_RESULT(yes)
		$1
	],[
		AC_MSG_RESULT(no)
		$2
	])
])
