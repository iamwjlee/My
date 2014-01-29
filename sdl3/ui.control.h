

#ifndef _UI_CONTROL_H_
#define _UI_CONTROL_H_

#define UI_CONTROL(n)					((ui_control_t*)(n))

typedef struct ui_control_s				ui_control_t;
struct ui_control_s
{
	slink_t					slink;
	char					name[24];
	U8						priority;
	unsigned				active		: 1;
	unsigned				running		: 1;
	unsigned				discardable	: 1;
	unsigned				paused		: 1;
	U8						active_key[16];
	int						(*start)(ui_control_t *);
	int						(*stop)(ui_control_t *);
	int						(*ioctl)(ui_control_t *, int, void *);
	void					*instance;
	//semaphore_t				*awake;
	osclock_t				expire;
	osclock_t				lifetime;
	osclock_t				interval;
	//ui_repeat_t				repeat;
	//ui_repeat_t				repeat2; /* playback jump key behaviour */
};

typedef enum
{
	CONTROL_NONE,
	CONTROL_EXIT,
	CONTROL_KEY_PRESSED,
	CONTROL_KEY_RELEASED,
} ui_control_type_t;

typedef struct
{
	ui_control_type_t		type;
	osclock_t				stamp;
	//key_code_t				key;
	int  key;
} ui_message_t;

/*  hide q.h    */
ui_message_t *ui_message_claim(osclock_t *timeout);
//msg_queue_t *ui_message_open(const char *name, int q_size ,int m_size);
int ui_message_send(ui_message_t *msg);
ui_message_t *ui_message_receive(ui_control_t *control);
ui_message_t *ui_message_receive_timeout(ui_control_t *control,osclock_t *timeout);

int ui_message_release(ui_message_t *msg);
int ui_message_init(const char *name, int q_size );
int ui_message_delete();
int ui_control_delete(void);

int ui_control_init(void);
int ui_control_start(ui_control_t *request, int *msg);


#endif
