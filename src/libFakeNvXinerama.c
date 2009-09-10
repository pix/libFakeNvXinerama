#ifndef RTLD_NEXT
  #define _GNU_SOURCE
#endif

#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/panoramiXext.h>
#include <X11/extensions/panoramiXproto.h>
#include <X11/extensions/Xinerama.h>

#include <fcntl.h>
#include <dlfcn.h>

#define LOAD_ORIG(name) real_##name = dlsym(RTLD_NEXT, #name);

static Bool (*real_XineramaQueryExtension)(Display *, int *, int *);
static Status (*real_XineramaQueryVersion)(Display *, int *, int *);
static Bool (*real_XineramaIsActive)(Display *);
static XineramaScreenInfo* (*real_XineramaQueryScreens)(Display *, int *);



Bool orig_XineramaQueryExtension(
    Display *dpy,
    int     *event_base,
    int     *error_base
){
  return (real_XineramaQueryExtension)(dpy, event_base, error_base);
}

Status orig_XineramaQueryVersion(
   Display *dpy,
   int     *major,
   int     *minor
){
  return (real_XineramaQueryVersion)(dpy, major, minor);
}

Bool orig_XineramaIsActive(
    Display *dpy
){
  return (real_XineramaIsActive)(dpy);
}

XineramaScreenInfo* orig_XineramaQueryScreens(
    Display *dpy,
    int     *number
){
  return (real_XineramaQueryScreens)(dpy, number);
}


static void orig_init(void) __attribute__ ((constructor));

void orig_init(void){
  perror("Init");

  LOAD_ORIG(XineramaQueryExtension)
  LOAD_ORIG(XineramaQueryVersion)
  LOAD_ORIG(XineramaIsActive)
  LOAD_ORIG(XineramaQueryScreens);
}


