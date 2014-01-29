#ifndef _UI_VIEW_H
#define _UI_VIEW_H

#include "my_sdl.h"
#include "slink.h"
#include "widget.h"
#include "q.h"
#include "ui.control.h"
#include "ui.h"
#include "th.h"



/* includes ------------------------------------------------------------------- */


/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */


/* macros --------------------------------------------------------------------- */


/* local function prototypes -------------------------------------------------- */


/* local variables ------------------------------------------------------------ */

/* global variables ----------------------------------------------------------- */


/* global functions ----------------------------------------------------------- */
int ui_view_init(void);

int ui_view_register(ui_view_t *view);

int ui_view_unregister(ui_view_t *view);

ui_view_t *ui_view_search(const char *name);

int ui_view_show(ui_view_t *request);

int ui_view_hide(ui_view_t *request);

int ui_view_extends(ui_view_t *request, int seconds);

int ui_view_update(ui_view_t *request) ; // need ?

int ui_view_pause(ui_view_t *request);

int ui_view_resume(ui_view_t *request);

int ui_view_ioctl(ui_view_t *request, int type, void *data);

int ui_view_lifetime(ui_view_t *request, int second);


/* local functions ------------------------------------------------------------ */


#endif
/* end of file ---------------------------------------------------------------- */
