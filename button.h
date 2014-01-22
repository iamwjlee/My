#ifndef _GFX_BUTTON_H_
#define _GFX_BUTTON_H_

/* includes ------------------------------------------------------------------- */
#include "my_sdl.h"
#include "widget.h"


#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */
typedef enum
{
	BUTTON_NORMAL,
	BUTTON_SELECTED,
	BUTTON_DISABLED,
	BUTTON_STATE_COUNT,
} button_state_t;


/* types ---------------------------------------------------------------------- */


typedef struct
{
	gfx_pen_t				pen[BUTTON_STATE_COUNT];
	blit_source_t			base[BUTTON_STATE_COUNT];
} button_style_t;

typedef struct
{
	widget_params_t			widget;
	const char				*text;
	button_style_t			*style;
} button_params_t;

typedef struct
{
	widget_t				widget;
	button_style_t			style;
	button_state_t			state;
	const char				*text;
} button_t;


/* macros --------------------------------------------------------------------- */


/* variables ------------------------------------------------------------------ */


/* functions ------------------------------------------------------------------ */
extern button_t *	button_create(widget_t *parent, button_params_t *params);
extern button_t *	button_delete(button_t *button);
extern void			button_set_state(button_t *button, button_state_t state);
extern void			button_set_text(button_t *button, const char *text);


#ifdef __cplusplus
}
#endif
#endif /* _GFX_BUTTON_H_ */
/* end of file ---------------------------------------------------------------- */

