AM_CFLAGS = $(XINERAMA_CFLAGS) $(MALLOC_ZERO_CFLAGS)


if LIB_XINERAMA 
lib_LTLIBRARIES = libXinerama.la libFakeNvXinerama.la
else
lib_LTLIBRARIES = libFakeNvXinerama.la
endif


if LIB_XINERAMA

libXinerama_la_SOURCES = \
												 Xinerama.c FakeNvXinerama.c \
												 NVCtrl.c  NVCtrl.h NVCtrlLib.h \
												 nv_control.h  nv_hw.h  nv_objects.h

libXinerama_la_LIBADD = $(XINERAMA_LIBS)

libXinerama_la_LDFLAGS = -version-number 1:0:0 -no-undefined

endif

libFakeNvXinerama_la_SOURCES = \
															 FakeNvXinerama.c libFakeNvXinerama.c \
															 NVCtrl.c  NVCtrl.h NVCtrlLib.h \
															 nv_control.h  nv_hw.h  nv_objects.h

libFakeNvXinerama_la_LIBADD = $(XINERAMA_LIBS) -ldl

libFakeNvXinerama_la_LDFLAGS = -version-number 1:0:0 -no-undefined


if LINT
ALL_LINT_FLAGS=$(LINT_FLAGS) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
		$(AM_CPPFLAGS) $(CPPFLAGS)

lint:
if LIB_XINERAMA
	$(LINT) $(ALL_LINT_FLAGS) $(libXinerama_la_SOURCES) $(XINERAMA_LIBS)
endif
	$(LINT) $(ALL_LINT_FLAGS) $(libFakeNvXinerama_la_SOURCES) $(XINERAMA_LIBS)
endif LINT
