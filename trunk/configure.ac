AC_INIT([Gscore], [0.1],
        [Sebastien Tricaud <toady gscore org>],
        [gscore])
AM_INIT_AUTOMAKE

dnl Gscore versions 
GSCORE_MAJOR_VERSION=0
GSCORE_MINOR_VERSION=1
GSCORE_MICRO_VERSION=0
GSCORE_VERSION=$GSCORE_MAJOR_VERSION.$GSCORE_MINOR_VERSION.$GSCORE_MICRO_VERSION
GSCORE_API_VERSION=1.0
AC_SUBST(GSCORE_MAJOR_VERSION)
AC_SUBST(GSCORE_MINOR_VERSION)
AC_SUBST(GSCORE_MICRO_VERSION)
AC_SUBST(GSCORE_VERSION)
AC_SUBST(GSCORE_API_VERSION)

dnl Libraries requirements
GLIB2_VERSION=2.6.0
GTK2_VERSION=2.8.0
LIBGLADE2_VERSION=2.4.0
CAIRO_VERSION=0.2.0
AC_SUBST(LIBGLADE2_VERSION)
AC_SUBST(GLIB2_VERSION)
AC_SUBST(GTK2_VERSION)
AC_SUBST(CAIRO_VERSION)

AM_MAINTAINER_MODE

###########################
# Check target architecture
###########################

AC_MSG_CHECKING([for target architecture])
case x"$target" in
  xNONE | x)
    target_or_host="$host" ;;
  *)
    target_or_host="$target" ;;
esac
AC_MSG_RESULT([$target_or_host])

case "$target_or_host" in
  i*86-*-*)
    have_x86=yes
    AC_DEFINE(ARCH_X86, 1, [Define to 1 if you are compiling for ix86.])
    ;;
  x86_64-*-*)
    have_x86=yes
    AC_DEFINE(ARCH_X86, 1, [Define to 1 if you are compiling for ix86.])
    AC_DEFINE(ARCH_X86_64, 1, [Define to 1 if you are compiling for amd64.])
    ;;
  ppc-*-* | powerpc-*)
    have_ppc=yes
    AC_DEFINE(ARCH_PPC, 1, [Define to 1 if you are compiling for PowerPC.])
    ;;
  ppc64-*-* | powerpc64-*)
    have_ppc=yes
    AC_DEFINE(ARCH_PPC, 1, [Define to 1 if you are compiling for PowerPC.])
    AC_DEFINE(ARCH_PPC64, 1, [Define to 1 if you are compiling for PowerPC64.])
    ;;
  *)
    ;;
esac

#################
# Check for Win32
#################

AC_MSG_CHECKING([for some Win32 platform])
case "$target_or_host" in
  *-*-mingw* | *-*-cygwin*)
    platform_win32=yes
    ;;
  *)
    platform_win32=no
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")

AC_MSG_CHECKING([for native Win32])
case "$target_or_host" in
  *-*-mingw*)
    os_win32=yes
    PATHSEP=';'
    ;;
  *)
    os_win32=no
    PATHSEP=':'
    ;;
esac
AC_MSG_RESULT([$os_win32])
AC_SUBST(PATHSEP)
AM_CONDITIONAL(OS_WIN32, test "$os_win32" = "yes")
AM_CONDITIONAL(OS_UNIX, test "$os_win32" != "yes")

if test "$os_win32" = "yes"; then
  AC_CHECK_PROG(ms_librarian, lib.exe, yes, no)
  AC_CHECK_TOOL(WINDRES, windres, :)
else
  WINDRES=":"
fi

AM_CONDITIONAL(MS_LIB_AVAILABLE, test x$ms_librarian = xyes)
AM_CONDITIONAL(HAVE_WINDRES, test "x$WINDRES" != "x:")

AC_SUBST(WINDRES)


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
dnl AC_CHECK_FUNCS(gettimeofday select socket strdup strerror strstr)

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

plugins_dir=$libdir/gscore

AC_SUBST(plugins_dir)

dnl **************************************************
dnl * Check for Gtkdoc.                              *
dnl **************************************************
AC_CHECK_PROG(GTKDOC, gtkdoc-mkdb, true, false)
AM_CONDITIONAL(HAVE_GTK_DOC, test -n $GTKDOC)
AC_SUBST(HAVE_GTK_DOC)

AC_ARG_ENABLE(gtk-doc, [  --enable-gtk-doc  Use gtk-doc to build documentation [default=no]], enable_gtk_doc="$enableval", enable_gtk_doc=no)
AM_CONDITIONAL(ENABLE_GTK_DOC, test x$enable_gtk_doc = xyes)

dnl ********************************************************
dnl languages
dnl ********************************************************
dnl ALL_LINGUAS="cs de en_CA nl pt_BR sv zh_CN"

dnl ********************************************************
dnl triggers gettext
dnl ********************************************************
AM_GLIB_GNU_GETTEXT
GETTEXT_PACKAGE=gscore
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE",[fix])

dnl *******************************
dnl checking for glib
dnl *******************************
PKG_CHECK_MODULES(GLIB2,[glib-2.0 >= $GLIB2_VERSION])
AC_SUBST(GLIB2_CFLAGS)
AC_SUBST(GLIB2_LIBS)

dnl *******************************
dnl checking for gtk+
dnl *******************************
PKG_CHECK_MODULES(GKT2,[gtk+-2.0 >= $GTK2_VERSION])
AC_SUBST(GTK2_CFLAGS)
AC_SUBST(GTK2_LIBS)

dnl *******************************
dnl checking for libglade
dnl *******************************
PKG_CHECK_MODULES(LIBGLADE2,[libglade-2.0 >= $LIBGLADE2_VERSION])
AC_SUBST(LIBGLADE2_CFLAGS)
AC_SUBST(LIBGLADE2_LIBS)

dnl *******************************
dnl checking for cairo
dnl *******************************
PKG_CHECK_MODULES(CAIRO, cairo >= $CAIRO_VERSION)
AC_SUBST(CAIRO_CFLAGS)
AC_SUBST(CAIRO_LIBS)

dnl OpenGL support for cairo ?
AC_ARG_ENABLE(gl,
               [  --enable-gl            Enable OpenGL support (glitz)],
               [use_gl=$enableval],  [use_gl=yes])

if test "x$use_gl" = "xyes"; then
  PKG_CHECK_MODULES(GL, glitz-glx >= 0.4.0, [
  CAIRO_CFLAGS="$CAIRO_CFLAGS $GL_CFLAGS -DUSE_GL" 
  CAIRO_LIBS="$CAIRO_LIBS $GL_LIBS"
  use_gl=yes], [use_gl="no (bitrotted at the moment)"])
fi

dnl *******************************
dnl checking for libabcp
dnl *******************************
dnl AC_CHECK_LIB(abcp, abcScanFile, [], [
dnl         echo "*****************************************************"
dnl         echo "Error! You need to have libabcp installed."
dnl 	echo "You can download it from http://abcp.sourceforge.net/"
dnl         echo "*****************************************************"
dnl         exit -1
dnl         ])

################
# Check for alsa
################

dnl AM_PATH_ALSA(alsa_required_version,
dnl              AC_DEFINE(HAVE_ALSA, 1, [Define to 1 if alsa is available]),
dnl              AC_MSG_WARN([*** midi input controller will be built without alsa support (alsa not found or unuseable) ***]))

##########################################################
# Determine where to install the desktop & mime info files
##########################################################

AC_ARG_WITH(desktop-dir, [  --with-desktop-dir=PATH where to install desktop files (default=PREFIX/share)])

if test "x$with_desktop_dir" != x; then
  DESKTOP_DATADIR=$with_desktop_dir
else
  DESKTOP_DATADIR="$datadir"
fi

AM_CONDITIONAL(DESKTOP_DATADIR, test "x$with_desktop_dir" != xno)
AC_SUBST(DESKTOP_DATADIR)


AC_PROG_INSTALL

dnl CFLAGS="$CFLAGS -Wall -Wstrict-prototypes -Wmissing-declarations \
dnl -Wbad-function-cast -Wcast-qual -Wcast-align -Wnested-externs -Wunused"

CFLAGS="$CFLAGS -Wall"

AC_SUBST(LDFLAGS)
AC_SUBST(CFLAGS)


dnl libgscore/Makefile

dnl plugins/Makefile
dnl plugins/abc/Makefile
dnl plugins/midi/Makefile
dnl src/Makefile

dnl glade/Makefile

dnl po/Makefile.in

AC_OUTPUT([

Makefile

fonts/Makefile
pixmaps/Makefile

libgscore/Makefile
libgscorebase/Makefile
libgscorespacings/Makefile

src/Makefile

])


echo
echo "*** Dumping configuration ***"
echo
echo "    GLIB2_CFLAGS : $GLIB2_CFLAGS"
echo "    GLIB2_LIBS : $GLIB2_LIBS"
echo "    GTK2_CFLAGS : $GTK2_CFLAGS"
echo "    GTK2_LIBS : $GTK2_LIBS"
echo "    LIBGLADE2_CFLAGS : $LIBGLADE2_CFLAGS"
echo "    LIBGLADE2_LIBS : $LIBGLADE2_LIBS"
echo
echo "    - Compiler               : ${CC}"
echo "    - Generate documentation : $enable_gtk_doc"
echo "    - Prefix                 : $prefix"
echo "    - Exec prefix            : $exec_prefix"
echo "    - Data dir               : $datadir"
echo "    - Plugins dir            : $plugins_dir"
echo
echo "    You can now run 'make' to compile gscore"
echo
