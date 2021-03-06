dnl  Copyright 2005 Red Hat, Inc.
dnl 
dnl  Permission to use, copy, modify, distribute, and sell this software and its
dnl  documentation for any purpose is hereby granted without fee, provided that
dnl  the above copyright notice appear in all copies and that both that
dnl  copyright notice and this permission notice appear in supporting
dnl  documentation, and that the name of Red Hat not be used in
dnl  advertising or publicity pertaining to distribution of the software without
dnl  specific, written prior permission.  Red Hat makes no
dnl  representations about the suitability of this software for any purpose.  It
dnl  is provided "as is" without express or implied warranty.
dnl 
dnl  RED HAT DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
dnl  INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
dnl  EVENT SHALL RED HAT BE LIABLE FOR ANY SPECIAL, INDIRECT OR
dnl  CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
dnl  DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
dnl  TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
dnl  PERFORMANCE OF THIS SOFTWARE.
dnl
dnl Process this file with autoconf to create configure.

AC_PREREQ([2.57])

AC_INIT(libFakeNvXinerama, 1.0.4-nv, [http://devlife.org/files/libs/libfakenvxinerama], libFakeNvXinerama)
AM_INIT_AUTOMAKE([dist-bzip2])
AM_MAINTAINER_MODE

AM_CONFIG_HEADER(config.h)

# Require xorg-macros version 1.1.0 or newer for XORG_WITH_LINT macro
m4_ifndef([XORG_MACROS_VERSION], [AC_FATAL([must install xorg-macros 1.1 or later])])
XORG_MACROS_VERSION(1.1)

# Check for progs
AC_PROG_CC
AC_PROG_LIBTOOL

# Check for dependencies
PKG_CHECK_MODULES(XINERAMA, x11 xext xextproto xineramaproto)

AC_SUBST(XINERAMA_CFLAGS)
AC_SUBST(XINERAMA_LIBS)

dnl Allow checking code with lint, sparse, etc.
XORG_WITH_LINT
LINT_FLAGS="${LINT_FLAGS} ${XINERAMA_CFLAGS}"
		  
XORG_CHECK_MALLOC_ZERO
XORG_MANPAGE_SECTIONS
XORG_RELEASE_VERSION

DEBUG=""
AC_MSG_CHECKING([whether to include a NVcontrol enabled libXinerama])
AC_ARG_ENABLE(libXinerama,
  [  --enable-libXinerama          include a NVControl enabled libXinerama [default=no]],
  if test x$enableval = "xyes"; then
    AC_DEFINE(LIB_XINERAMA, 1, " compile with NVControl-enabled libXinerama")
    LIB_XINERAMA=true
    AC_MSG_RESULT([yes])
  else
    AC_MSG_RESULT([no])
  fi,
  AC_MSG_RESULT([no])
)
AM_CONDITIONAL(LIB_XINERAMA, test x$LIB_XINERAMA = xtrue)

AC_OUTPUT([Makefile
	   src/Makefile
	   man/Makefile
     xinerama.pc])
