
#define NEED_EVENTS
#define NEED_REPLIES
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xext.h>
#include <X11/extensions/extutil.h>
#include <X11/extensions/panoramiXext.h>
#include <X11/extensions/panoramiXproto.h>
#include <X11/extensions/Xinerama.h>

#include "NVCtrl.h"
#include "NVCtrlLib.h"

#define MAX_NVSCREENS 10

static int num_screens = -1;
static struct
{
    int x_org, y_org;
    int width, height;
} screen_info[ MAX_NVSCREENS ];


static Bool FakeNvXineramaIsActive (Display *);
static Bool FakeNvXineramaQueryExtension (Display *, int *, int *);
static Status FakeNvXineramaQueryVersion(Display *, int *, int *);
static int FakeNvXineramaReadInt(char *, char **);
static void FakeNvXineramaInit(Display *);
static Bool FakeNvTwinviewIsActive (Display *);


extern Bool   orig_XineramaQueryExtension(Display *, int *, int *);
extern Status orig_XineramaQueryVersion(Display *, int *, int *);
extern Bool   orig_XineramaIsActive(Display *);
extern XineramaScreenInfo* orig_XineramaQueryScreens(Display *, int *);


/*******************************************************************\
 Nvidia Twinview Xinrama Replacmement functions
\*******************************************************************/


static Bool FakeNvXineramaQueryExtension (
   Display *dpy,
   int     *event_base,
   int     *error_base
)
{
   (void) dpy;
   *event_base = 0;
   *error_base = 0;
   return True;
}

static Status FakeNvXineramaQueryVersion(
   Display *dpy,
   int     *major,
   int     *minor
)
{
   (void) dpy;
   *major = 1;
   *minor = 1;
   return 1;
}

static int FakeNvXineramaReadInt(char * string, char **next_string)
{
	int result = 0;
	int sign = 1;

	if (*string == '+')
		string++;
	else if (*string == '-'){
		string++;
		sign = -1;
	}

	for (; isdigit(*string) ; string++)
	{
		result = (result * 10) + (*string - '0');
	}
	
	*next_string = string;

	return result * sign;
}

static void FakeNvXineramaInit(Display *dpy)
{

    int screen, ret;
    char *str = NULL, *mode_ptr;

    num_screens = 0;
    
    if(!FakeNvTwinviewIsActive(dpy))
	    return;

    screen = DefaultScreen(dpy);
    
    ret = XNVCTRLQueryStringAttribute(dpy, screen, 0,
            NV_CTRL_STRING_CURRENT_METAMODE,
            &str);

    if (!ret && str != NULL) {
#ifdef NV_DEBUG
        fprintf(stderr, "[NV Fake Xinerama] Failed to query the current MetaMode.\n\n");
#endif
        return;
    }else{
#ifdef NV_DEBUG
        fprintf(stderr, "[NV Fake Xinerama] Successfully loaded (NvControl v%d.%d)\n",
                major,
                minor);
#endif
    }

    mode_ptr = strchr(str, '@');
    while(mode_ptr != NULL && num_screens < MAX_NVSCREENS-1){
        
        // Parse a metamode string 
        // @1280x1024 +1280+0 [snip]

        mode_ptr++; // Skip the '@' character
        num_screens++; // Increment the number of screens

        screen_info[num_screens-1].width = FakeNvXineramaReadInt(mode_ptr, &mode_ptr);
        if(screen_info[num_screens-1].width <= 0 || *mode_ptr != 'x'){
            // Problem detected, aborting
            num_screens = 0;
            return;
        }

        // Still there ? lets parse screen height
        mode_ptr++; // Skip the 'x' character
        screen_info[num_screens-1].height = FakeNvXineramaReadInt(mode_ptr, &mode_ptr);

        // At the end of the string we expect a blank character before
        // the offsets
        if(screen_info[num_screens-1].height <= 0 || *mode_ptr != ' '){
            num_screens = 0;
            return;
        }

        // Still there ? lets parse screen height
        mode_ptr++; // Skip the whitespace character
        screen_info[num_screens-1].x_org =  FakeNvXineramaReadInt(mode_ptr, &mode_ptr);
        screen_info[num_screens-1].y_org =  FakeNvXineramaReadInt(mode_ptr, &mode_ptr);


        // Hunting for another screen
        mode_ptr = strchr(mode_ptr, '@');

    }
#ifdef NV_DEBUG
    if(num_screens > 0){
        int i;
        fprintf(stderr, "[NV Fake Xinerama] found %d screens\n", num_screens);
        for(i=0 ; i < num_screens ; i++){

            fprintf(stderr, "[NV Fake Xinerama] Screen #%d: %dx%d %d %d\n", 
                    i,
                    screen_info[i].width,
                    screen_info[i].height,
                    screen_info[i].x_org,
                    screen_info[i].y_org);
        }
    }
#endif

    // Free the allocated metamode string 
    XFree(str);
}


static Bool FakeNvXineramaIsActive (
    Display *dpy
){
    FakeNvXineramaInit(dpy);
    return num_screens != 0;
}

static XineramaScreenInfo * 
FakeNvXineramaQueryScreens (
    Display *dpy, 
    int *number
){
    XineramaScreenInfo *scrnInfo = NULL;
    FakeNvXineramaInit(dpy);
    if(num_screens) {
        if((scrnInfo = Xmalloc(sizeof(XineramaScreenInfo) * num_screens))) {
            int i;

            for(i = 0; i < num_screens; i++) {
                scrnInfo[i].screen_number = i;
                scrnInfo[i].x_org       = screen_info[ i ].x_org;
                scrnInfo[i].y_org       = screen_info[ i ].y_org;
                scrnInfo[i].width       = screen_info[ i ].width;
                scrnInfo[i].height       = screen_info[ i ].height;
            }

            *number = num_screens;
        } else
            ;
    }
    return scrnInfo;
}

static Bool FakeNvTwinviewIsActive (
    Display *dpy
){
    int screen, major, minor, ret, value;

    screen = DefaultScreen(dpy);

    if (!XNVCTRLIsNvScreen(dpy, screen)) {
#ifdef NV_DEBUG
        fprintf(stderr, "[NV Fake Xinerama] The NV-CONTROL X extension is not available on screen "
                "%d of '%s'.\n\n", screen, XDisplayName(NULL));
#endif
        return False;
    }

    ret = XNVCTRLQueryVersion(dpy, &major, &minor);
    if (!ret) {
#ifdef NV_DEBUG
        fprintf(stderr, "[NV Fake Xinerama] The NV-CONTROL X extension does not exist "
                "on '%s'.\n\n", XDisplayName(NULL));
#endif
        return False;
    } 

    ret = XNVCTRLQueryAttribute(dpy, screen, 0,
		    NV_CTRL_TWINVIEW,
		    &value);

    // Twinview is active
    return ret && value;
}


/*******************************************************************\
 Begin Xinerama Functions
\*******************************************************************/

Bool XineramaQueryExtension (
    Display *dpy,
    int     *event_base,
    int     *error_base
)
{
    if(FakeNvTwinviewIsActive(dpy))
        return FakeNvXineramaQueryExtension(dpy, event_base, error_base);
    else
        return orig_XineramaQueryExtension(dpy, event_base, error_base);
}

Status XineramaQueryVersion(
    Display *dpy,
    int     *major,
    int     *minor
)
{
    if(FakeNvTwinviewIsActive(dpy))
        return FakeNvXineramaQueryVersion(dpy, major, minor);
    else
	return orig_XineramaQueryVersion(dpy, major, minor);
    
}

Bool XineramaIsActive (
    Display *dpy
){
    if(FakeNvTwinviewIsActive(dpy))
        return FakeNvXineramaIsActive(dpy);
    else
	return orig_XineramaIsActive(dpy);
}

XineramaScreenInfo * XineramaQueryScreens (
    Display *dpy,
    int *number
){
    if(FakeNvTwinviewIsActive(dpy))
	 return FakeNvXineramaQueryScreens(dpy, number);
    else
	 return orig_XineramaQueryScreens(dpy, number);   
}
