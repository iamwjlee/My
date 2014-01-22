#ifndef __SCROLL_H_
#define __SCROLL_H_

/* includes ------------------------------------------------------------------- */


#ifdef __cplusplus
extern "C" {
#endif

/* constants ------------------------------------------------------------------ */


/* enumerations --------------------------------------------------------------- */


/* types ---------------------------------------------------------------------- */
typedef struct
{
	widget_params_t			widget;
	blit_source_t			thumb;
	blit_source_t			cover;
} scroll_params_t;

struct scroll_s
{
	widget_t				widget;
	U32						full;
	U32						active;
	U32						value;
	blit_source_t			thumb;
	blit_source_t			cover;
	BOOL					vertical;
};
typedef struct scroll_s				scroll_t;


/* macros --------------------------------------------------------------------- */


/* variables ------------------------------------------------------------------ */


/* functions ------------------------------------------------------------------ */
extern scroll_t *scroll_create(widget_t *parent, scroll_params_t *params);
extern void scroll_set_value(scroll_t *scroll, U32 value);
extern BOOL scroll_config(scroll_t *scroll, U32 full, U32 active);


#ifdef __cplusplus
}
#endif
#endif /* __SCROLL_H_ */
/* end of file ---------------------------------------------------------------- */

