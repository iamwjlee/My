#ifndef __GET_KEY_H
#define __GET_KEY_H


typedef struct msg_key
{
	char key;
	int  sent;

}msg_key_t;

int get_key(void);
int test_get_string(void);


#endif
