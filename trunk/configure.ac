AC_INIT([Gscore], [0.0.9],
        [Sebastien Tricaud <toady@gscore.org>],
        [gscore])
AM_INIT_AUTOMAKE

dnl Libraries requirements
GLIB2_VERSION=2.6.0
GTK2_VERSION=2.6.0
LIBGLADE2_VERSION=2.4.0

AC_SUBST(LIBGLADE2_VERSION)
AC_SUBST(GLIB2_VERSION)
AC_SUBST(GTK2_VERSION)


AM_MAINTAINER_MODE

dnl Put the preprocessor macros in a header instead of command line 
AM_CONFIG_HEADER(config.h)

dnl Checks for headers
AC_HEADER_STDC
AC_HEADER_DIRENT

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME

dnl Checks for library functions.
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS(gettimeofday select socket strdup strerror strstr)

dnl Checks for programs
AM_PROG_LIBTOOL

if test "x$prefix" = "xNONE"; then
	prefix="/usr/local"
fi

if test "x$localstatedir" = "x\${prefix}/var"; then
	localstatedir="$prefix/var"
fi

if test "x$sysconfdir" = "x\${prefix}/etc"; then
    sysconfdir="$prefix/etc"
fi

AC_SUBST(localstatedir)

plugin_dir=$libdir/pvs

AC_SUBST(plugin_dir)

dnl **************************************************
dnl * Check for Gtkdoc.                              *
dnl **************************************************
AC_CHECK_PROG(GTKDOC, gtkdoc-mkdb, true, false)
AM_CONDITIONAL(HAVE_GTK_DOC, test -n $GTKDOC)
AC_SUBST(HAVE_GTK_DOC)

AC_ARG_ENABLE(gtk-doc, [  --enable-gtk-doc  Use gtk-doc to build documentation [default=no]], enable_gtk_doc="$enableval", enable_gtk_doc=no)
AM_CONDITIONAL(ENABLE_GTK_DOC, test x$enable_gtk_doc = xyes)


dnl *******************************
dnl checking for glib
dnl *******************************
PKG_CHECK_MODULES(GLIB2,[glib-2.0 >= $GLIB2_VERSION])

dnl *******************************
dnl checking for gtk+
dnl *******************************
PKG_CHECK_MODULES(GKT2,[gtk+-2.0 >= $GTK2_VERSION])


dnl *******************************
dnl checking for libglade
dnl *******************************
PKG_CHECK_MODULES(LIBGLADE2,[libglade-2.0 >= $LIBGLADE2_VERSION])

AC_PROG_CC
AC_PROG_INSTALL

CFLAGS="$CFLAGS -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
-Wbad-function-cast -Wcast-qual -Wcast-align -Wnested-externs -Wunused"

AC_SUBST(LDFLAGS)
AC_SUBST(CFLAGS)
AC_SUBST(LIBGLADE2_CFLAGS)
AC_SUBST(LIBGLADE2_LIBS)

AC_OUTPUT([

Makefile

src/Makefile

])


echo
echo "*** Dumping configuration ***"
echo "    - Compiler               : ${CC}"
echo "    - Generate documentation : $enable_gtk_doc"
echo "    - Glib version           : ${GLIB2_VERSION}"
echo "    - GTK+ version           : ${GTK2_VERSION}"
echo "    - Libglade version       : ${LIBGLADE2_VERSION}"
echo
echo "    - Libglade CFLAGS        : ${LIBGLADE2_CFLAGS}"
echo "    - Libglade LIBS          : ${LIBGLADE2_LIBS}"
echo
