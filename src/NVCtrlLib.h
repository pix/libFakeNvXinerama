#ifndef __NVCTRLLIB_H
#define __NVCTRLLIB_H

#include "NVCtrl.h"

/*
 *  XNVCTRLQueryExtension -
 *
 *  Returns True if the extension exists, returns False otherwise.
 *  event_basep and error_basep are the extension event and error
 *  bases.  Currently, no extension specific errors or events are
 *  defined.
 */

Bool XNVCTRLQueryExtension (
    Display *dpy,
    int *event_basep,
    int *error_basep
);


/*
 *  XNVCTRLQueryVersion -
 *
 *  Returns True if the extension exists, returns False otherwise.
 *  major and minor are the extension's major and minor version
 *  numbers.
 */

Bool XNVCTRLQueryVersion (
    Display *dpy,
    int *major,
    int *minor
);


/*
 *  XNVCTRLIsNvScreen
 *
 *  Returns True is the specified screen is controlled by the NVIDIA
 *  driver.  Returns False otherwise.
 */

Bool XNVCTRLIsNvScreen (
    Display *dpy,
    int screen
);


/*
 *  XNVCTRLQueryTargetCount -
 *
 *  Returns True if the target type exists.  Returns False otherwise.
 *  If XNVCTRLQueryTargetCount returns True, value will contain the
 *  count of existing targets on the server of the specified target
 *  type.
 *
 *  Please see "Attribute Targets" in NVCtrl.h for the list of valid
 *  target types.
 *
 *  Possible errors:
 *     BadValue - The target doesn't exist.
 */

Bool XNVCTRLQueryTargetCount (
    Display *dpy,
    int target_type,
    int *value
);


/*
 *  XNVCTRLSetAttribute -
 *
 *  Sets the attribute to the given value.  The attributes and their
 *  possible values are listed in NVCtrl.h.
 *
 *  Not all attributes require the display_mask parameter; see
 *  NVCtrl.h for details.
 *
 *  Calling this function is equivalent to calling XNVCTRLSetTargetAttribute()
 *  with the target_type set to NV_CTRL_TARGET_TYPE_X_SCREEN and
 *  target_id set to 'screen'.
 *
 *  Possible errors:
 *     BadValue - The screen or attribute doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that screen.
 */

void XNVCTRLSetAttribute (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    int value
);


/*
 *  XNVCTRLSetTargetAttribute -
 *
 *  Sets the attribute to the given value.  The attributes and their
 *  possible values are listed in NVCtrl.h.
 *
 *  Not all attributes require the display_mask parameter; see
 *  NVCtrl.h for details.
 *
 *  Possible errors:
 *     BadValue - The target or attribute doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that target.
 */

void XNVCTRLSetTargetAttribute (
    Display *dpy,
    int target_type,
    int target_id,
    unsigned int display_mask,
    unsigned int attribute,
    int value
);


/*
 *  XNVCTRLSetAttributeAndGetStatus -
 *
 * Same as XNVCTRLSetAttribute().
 * In addition, XNVCTRLSetAttributeAndGetStatus() returns 
 * True if the operation succeeds, False otherwise.
 *
 */

Bool XNVCTRLSetAttributeAndGetStatus (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    int value
);


/*
 *  XNVCTRLQueryAttribute -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryAttribute returns True, value will contain the
 *  value of the specified attribute.
 *
 *  Not all attributes require the display_mask parameter; see
 *  NVCtrl.h for details.
 *
 *  Calling this function is equivalent to calling
 *  XNVCTRLQueryTargetAttribute() with the target_type set to
 *  NV_CTRL_TARGET_TYPE_X_SCREEN and target_id set to 'screen'.
 *
 *  Possible errors:
 *     BadValue - The screen doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that screen.
 */

Bool XNVCTRLQueryAttribute (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    int *value
);


/*
 * XNVCTRLQueryTargetAttribute -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryTargetAttribute returns True, value will contain the
 *  value of the specified attribute.
 *
 *  Not all attributes require the display_mask parameter; see
 *  NVCtrl.h for details.
 *
 *  Possible errors:
 *     BadValue - The target doesn't exist.
 *     BadMatch - The NVIDIA driver does not control the target.
 */

Bool XNVCTRLQueryTargetAttribute (
    Display *dpy,
    int target_Type,
    int target_id,
    unsigned int display_mask,
    unsigned int attribute,
    int *value
);


/*
 *  XNVCTRLQueryStringAttribute -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryStringAttribute returns True, *ptr will point to an
 *  allocated string containing the string attribute requested.  It is
 *  the caller's responsibility to free the string when done.
 *
 *  Calling this function is equivalent to calling
 *  XNVCTRLQueryTargetStringAttribute() with the target_type set to
 *  NV_CTRL_TARGET_TYPE_X_SCREEN and target_id set to 'screen'.
 *
 *  Possible errors:
 *     BadValue - The screen doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that screen.
 *     BadAlloc - Insufficient resources to fulfill the request.
 */

Bool XNVCTRLQueryStringAttribute (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    char **ptr
);


/*
 *  XNVCTRLQueryTargetStringAttribute -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryTargetStringAttribute returns True, *ptr will point
 *  to an allocated string containing the string attribute requested.
 *  It is the caller's responsibility to free the string when done.
 *
 *  Possible errors:
 *     BadValue - The target doesn't exist.
 *     BadMatch - The NVIDIA driver does not control the target.
 *     BadAlloc - Insufficient resources to fulfill the request.
 */

Bool XNVCTRLQueryTargetStringAttribute (
    Display *dpy,
    int target_type,
    int target_id,
    unsigned int display_mask,
    unsigned int attribute,
    char **ptr
);


/*
 *  XNVCTRLSetStringAttribute -
 *
 *  Returns True if the operation succeded.  Returns False otherwise.
 *
 *  Possible X errors:
 *     BadValue - The screen doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that screen.
 *     BadAlloc - Insufficient resources to fulfill the request.
 */
 
Bool XNVCTRLSetStringAttribute (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    char *ptr
);


/*
 * XNVCTRLQueryValidAttributeValues -
 *
 * Returns True if the attribute exists.  Returns False otherwise.  If
 * XNVCTRLQueryValidAttributeValues returns True, values will indicate
 * the valid values for the specified attribute; see the description
 * of NVCTRLAttributeValidValues in NVCtrl.h.
 *
 *  Calling this function is equivalent to calling
 *  XNVCTRLQueryValidTargetAttributeValues() with the target_type set to
 *  NV_CTRL_TARGET_TYPE_X_SCREEN and target_id set to 'screen'.
 */

Bool XNVCTRLQueryValidAttributeValues (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,                                 
    NVCTRLAttributeValidValuesRec *values
);



/*
 * XNVCTRLQueryValidTargetAttributeValues -
 *
 * Returns True if the attribute exists.  Returns False otherwise.  If
 * XNVCTRLQueryValidTargetAttributeValues returns True, values will indicate
 * the valid values for the specified attribute.
 */

Bool XNVCTRLQueryValidTargetAttributeValues (
    Display *dpy,
    int target_type,
    int target_id,
    unsigned int display_mask,
    unsigned int attribute,                                 
    NVCTRLAttributeValidValuesRec *values
);


/*
 *  XNVCTRLSetGvoColorConversion -
 *
 *  Sets the color conversion matrix, offset, and scale that should be
 *  used for GVO (Graphic to Video Out).
 *
 *  The Color Space Conversion data is ordered like this:
 *
 *   colorMatrix[0][0] // r.Y
 *   colorMatrix[0][1] // g.Y
 *   colorMatrix[0][2] // b.Y
 *
 *   colorMatrix[1][0] // r.Cr
 *   colorMatrix[1][1] // g.Cr
 *   colorMatrix[1][2] // b.Cr
 *
 *   colorMatrix[2][0] // r.Cb
 *   colorMatrix[2][1] // g.Cb
 *   colorMatrix[2][2] // b.Cb
 *
 *   colorOffset[0]    // Y
 *   colorOffset[1]    // Cr
 *   colorOffset[2]    // Cb
 *
 *   colorScale[0]     // Y
 *   colorScale[1]     // Cr
 *   colorScale[2]     // Cb
 *
 *  where the data is used according to the following formulae:
 *
 *   Y  =  colorOffset[0] + colorScale[0] *
 *           (R * colorMatrix[0][0] +
 *            G * colorMatrix[0][1] +
 *            B * colorMatrix[0][2]);
 *
 *   Cr =  colorOffset[1] + colorScale[1] *
 *           (R * colorMatrix[1][0] +
 *            G * colorMatrix[1][1] +
 *            B * colorMatrix[1][2]);
 *
 *   Cb =  colorOffset[2] + colorScale[2] *
 *           (R * colorMatrix[2][0] +
 *            G * colorMatrix[2][1] +
 *            B * colorMatrix[2][2]);
 *
 *  Possible errors:
 *     BadMatch - The NVIDIA driver is not present on that screen.
 *     BadImplementation - GVO is not available on that screen.
 */

void XNVCTRLSetGvoColorConversion (
    Display *dpy,
    int screen,
    float colorMatrix[3][3],
    float colorOffset[3],
    float colorScale[3]
);



/*
 *  XNVCTRLQueryGvoColorConversion -
 *
 *  Retrieves the color conversion matrix and color offset
 *  that are currently being used for GVO (Graphic to Video Out).
 *
 *  The values are ordered within the arrays according to the comments
 *  for XNVCTRLSetGvoColorConversion().
 *
 *  Possible errors:
 *     BadMatch - The NVIDIA driver is not present on that screen.
 *     BadImplementation - GVO is not available on that screen.
 */

Bool XNVCTRLQueryGvoColorConversion (
    Display *dpy,
    int screen,
    float colorMatrix[3][3],
    float colorOffset[3],
    float colorScale[3]
);


/* SPECIAL HANDLING OF VCP CODES 
 *
 * XNVCTRLQueryDDCCILutSize
 * XNVCTRLQueryDDCCISinglePointLutOperation
 * XNVCTRLSetDDCCISinglePointLutOperation
 * XNVCTRLQueryDDCCIBlockLutOperation
 * XNVCTRLSetDDCCIBlockLutOperation
 * XNVCTRLSetDDCCIRemoteProcedureCall
 * XNVCTRLQueryDDCCIDisplayControllerType
 
 * Some of DDC/CI VCP codes handle multiple values,
 * therefore they need their own NV_CONTROL structure 
 */
 
/* XNVCTRLQueryDDCCILutSize
 * Provides the size (number of entries and number of bits / entry)
 * for the Red / Green and Blue LUT in the display
 *
 * red_entries: Number of Red LUT entries
 * green_entries: Number of Green LUT entries
 * blue_entries: Number of Blue LUT entries
 * red_bits_per_entries: Number of bits / entry in Red LUT
 * green_bits_per_entries: Number of bits / entry in Green LUT
 * blue_bits_per_entries: Number of bits / entry in Blue LUT
 * Returns TRUE on success
 */
Bool XNVCTRLQueryDDCCILutSize (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int *red_entries,
    unsigned int *green_entries,
    unsigned int *blue_entries,
    unsigned int *red_bits_per_entries,
    unsigned int *green_bits_per_entries,
    unsigned int *blue_bits_per_entries
);

/* XNVCTRLQueryDDCCISinglePointLutOperation
 * Allows a single point within a display's color LUT to be read
 * Input:
 *  offset: Offset into the LUT
 * Output:
 *  red_value: Red LUT value read
 *  green_value: Green LUT value read
 *  blue_value: Blue LUT value read
 * Returns TRUE on success
 */
Bool XNVCTRLQueryDDCCISinglePointLutOperation (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int offset,
    unsigned int *red_value,
    unsigned int *green_value,
    unsigned int *blue_value
);

/* XNVCTRLSetDDCCISinglePointLutOperation
 * Allows a single point within a display's color LUT (look up table)
 * to be loaded.
 * offset: Offset into the LUT
 * red_value: Red LUT value to be loaded
 * green_value: Green LUT value to be loaded
 * blue_value: Blue LUT value to be loaded
 * Note: If display LUT cannot store 16 bit values then least significant
 * bits are discarded
 * Returns TRUE on success
 */
Bool XNVCTRLSetDDCCISinglePointLutOperation (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int offset,
    unsigned int red_value,
    unsigned int green_value,
    unsigned int blue_value
);

/* XNVCTRLQueryDDCCIBlockLutOperation
 * Provides an efficient method for reading multiple values from a display's LUT
 * color: is one of NV_CTRL_DDCCI_RED_LUT, NV_CTRL_DDCCI_GREEN_LUT, 
 *  NV_CTRL_DDCCI_BLUE_LUT. Color to be read.
 * size: Number of values to be read
 * offset: Offset into Red or Green or Blue LUT
 * value: Red or Green or Blue LUT contents. Needs to be freed when done.
 * Returns TRUE on success
 */           
Bool XNVCTRLQueryDDCCIBlockLutOperation (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int color, 
    unsigned int size,
    unsigned int offset,
    unsigned int **value
);

/* XNVCTRLSetDDCCIBlockLutOperation
 * Provides an efficient method for loading multiple values into a display's LUT
 * size: Number of values to be loaded
 * offset: Offset into Red or Green or Blue LUT
 * value: R or G or B LUT values to be loaded
 * color: NV_CTRL_DDCCI_RED_LUT, NV_CTRL_DDCCI_GREEN_LUT, NV_CTRL_DDCCI_BLUE_LUT
 * Note: If display LUT cannot store 16 bit values then least significant
 * bits are discarded
 * Returns TRUE on success
 */   
#define NV_CTRL_DDCCI_RED_LUT 1
#define NV_CTRL_DDCCI_GREEN_LUT 2
#define NV_CTRL_DDCCI_BLUE_LUT 3     
Bool XNVCTRLSetDDCCIBlockLutOperation (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int color, 
    unsigned int offset,
    unsigned int size,
    unsigned int *value
);

/* XNVCTRLSetDDCCIRemoteProcedureCall
 * Allows initiation of a routine / macro resident in the display. Only
 * one RPC is defined at this time:
 * A spline curve routine applied to the data (supplied in format
 * below) and the resulting data used to derive a full set of values 
 * for the display color LUT which shall then be loaded.
 * offset: Offset into the LUT
 * size: Number of values to be loaded
 * red_lut: Red LUT values
 * green_lut: Green LUT value
 * blue_lut: Blue LUT value
 * increment: Increment to next LUT entry
 *  Values of E0h  FFh inclusive are reserved for manufacturer
 * specific routines / macros.
 * All other values are reserved and shall be ignored.
 * Returns TRUE on success
 */
Bool XNVCTRLSetDDCCIRemoteProcedureCall (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int offset,
    unsigned int size,
    unsigned int *red_lut,
    unsigned int *green_lut,
    unsigned int *blue_lut,
    unsigned int *increment
);

/* XNVCTRLQueryDDCCIDisplayControllerType:
 * Provides the host with knowledge of the controller type being used by a 
 * particular display 
 * controller_manufacturer: Indicates controller manufacturer. (This string 
 * needs to be freed when done) (XXX This will be changed to a static string)
 * controller_type: Provide a numeric indication of controller type
 * Return TRUE on success
 */
Bool XNVCTRLQueryDDCCIDisplayControllerType (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned char **controller_manufacturer,
    unsigned int *controller_type
);

/* NVCTRLQueryDDCCICapabilities:
 * Gets the capabilities of the display as a VCP string
 * Returns :
 * nvctrl_vcp_supported: a table of 0 (not supported) and 1 (supported)
 *   which index is the NV_CTRL_DDCI* values 
 * possible_value_offset; contains the offsets in the table 
 *   nvctrl_vcp_possible_values. Index is the NV_CTRL_DDCI* values.
 *  -1 means no possible values are available.
 * possible_value_size; contains the count in the table 
 *  nvctrl_vcp_possible_values. Index is the NV_CTRL_DDCI* values.
 *  -1 means no possible values are available.
 * nvctrl_vcp_possible_values: a table of possible values for the non
 *   continuous values. 
 * nvctrl_string_vcp_supported: a table or 0 (not supported) and 1 (supported)
 *   which index is the NV_CTRL_STRING_DDCI* values.
 *
 * Returns TRUE on success
 */
Bool NVCTRLQueryDDCCICapabilities (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int **nvctrl_vcp_supported,    // Size is NV_CTRL_DDCCI_LAST_VCP+1
    unsigned int **possible_values_offset,  // Size is NV_CTRL_DDCCI_LAST_VCP+1
    unsigned int **possible_values_size,    // Size is NV_CTRL_DDCCI_LAST_VCP+1
    unsigned int **nvctrl_vcp_possible_values, 
    unsigned int **nvctrl_string_vcp_supported // Size is NV_CTRL_STRING_LAST_ATTRIBUTE+1
);

/* XNVCTRLQueryDDCCITimingReport
 * Queries the currently operating video signal timing report data.
 * - is_sync_freq_out_range: Sync. Freq. out of range          (TRUE/FALSE)
 * - is_unstable_count:      Unstable Count                    (TRUE/FALSE)
 * - is_positive_h_sync:     Positive Horizontal sync polarity (TRUE/FALSE)
 * - is_positive_v_sync:     Positive Vertical sync polarity   (TRUE/FALSE)
 * - h_freq:                 Horizontal Frequency
 * - v_freq:                 Vertical Frequency.
 *
 * Returns TRUE on success
 */           
Bool XNVCTRLQueryDDCCITimingReport (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int *sync_freq_out_range, 
    unsigned int *unstable_count,
    unsigned int *positive_h_sync,
    unsigned int *positive_v_sync,
    unsigned int *h_freq,
    unsigned int *v_freq
);


/*
 *  XNVCTRLQueryBinaryData -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryBinaryData returns True, *ptr will point to an
 *  allocated block of memory containing the binary data attribute
 *  requested.  It is the caller's responsibility to free the data
 *  when done.  len will list the length of the binary data.
 *
 *  Calling this function is equivalent to calling
 *  XNVCTRLQueryTargetBinaryData() with the target_type set to
 *  NV_CTRL_TARGET_TYPE_X_SCREEN and target_id set to 'screen'.
 *
 *  Possible errors:
 *     BadValue - The screen doesn't exist.
 *     BadMatch - The NVIDIA driver is not present on that screen.
 *     BadAlloc - Insufficient resources to fulfill the request.
 */

Bool XNVCTRLQueryBinaryData (
    Display *dpy,
    int screen,
    unsigned int display_mask,
    unsigned int attribute,
    unsigned char **ptr,
    int *len
);


/*
 * XNVCTRLQueryTargetBinaryData -
 *
 *  Returns True if the attribute exists.  Returns False otherwise.
 *  If XNVCTRLQueryTargetBinaryData returns True, *ptr will point to an
 *  allocated block of memory containing the binary data attribute
 *  requested.  It is the caller's responsibility to free the data
 *  when done.  len will list the length of the binary data.
 *
 *  Possible errors:
 *     BadValue - The target doesn't exist.
 *     BadMatch - The NVIDIA driver does not control the target.
 *     BadAlloc - Insufficient resources to fulfill the request.
 */

Bool XNVCTRLQueryTargetBinaryData (
    Display *dpy,
    int target_type,
    int target_id,
    unsigned int display_mask,
    unsigned int attribute,
    unsigned char **ptr,
    int *len
);


/*
 * XNVCtrlSelectNotify -
 *
 * This enables/disables receiving of NV-CONTROL events.  The type
 * specifies the type of event to enable (currently, the only
 * type that can be requested per-screen with XNVCtrlSelectNotify()
 * is ATTRIBUTE_CHANGED_EVENT); onoff controls whether receiving this
 * type of event should be enabled (True) or disabled (False).
 *
 * Returns True if successful, or False if the screen is not
 * controlled by the NVIDIA driver.
 */

Bool XNVCtrlSelectNotify (
    Display *dpy,
    int screen,
    int type,
    Bool onoff
);


/*
 * XNVCtrlSelectTargetNotify -
 *
 * This enables/disables receiving of NV-CONTROL events that happen on
 * the specified target.  The notify_type specifies the type of event to
 * enable (currently, the only type that can be requested per-target with
 * XNVCtrlSelectTargetNotify() is TARGET_ATTRIBUTE_CHANGED_EVENT); onoff
 * controls whether receiving this type of event should be enabled (True)
 * or disabled (False).
 *
 * Returns True if successful, or False if the target is not
 * controlled by the NVIDIA driver.
 */

Bool XNVCtrlSelectTargetNotify (
    Display *dpy,
    int target_type,
    int target_id,
    int notify_type,
    Bool onoff
);


/*
 * XNVCtrlEvent structure
 */

typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;  /* always FALSE, we don't allow send_events */
    Display *display;
    Time time;
    int screen;
    unsigned int display_mask;
    unsigned int attribute;
    int value;
} XNVCtrlAttributeChangedEvent;

typedef union {
    int type;
    XNVCtrlAttributeChangedEvent attribute_changed;
    long pad[24];
} XNVCtrlEvent;


/*
 * XNVCtrlEventTarget structure
 */

typedef struct {
    int type;
    unsigned long serial;
    Bool send_event;  /* always FALSE, we don't allow send_events */
    Display *display;
    Time time;
    int target_type;
    int target_id;
    unsigned int display_mask;
    unsigned int attribute;
    int value;
} XNVCtrlAttributeChangedEventTarget;

typedef union {
    int type;
    XNVCtrlAttributeChangedEventTarget attribute_changed;
    long pad[24];
} XNVCtrlEventTarget;


#endif /* __NVCTRLLIB_H */
