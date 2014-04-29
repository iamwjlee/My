#include "common.h"
#include "sys.h"
#include "task.h"
#include "get_key.h"

msg_key_t key_data;
int get_key(void)
{
	char key;
	int i=0;

	char buffer[16];
	while(1)
	{
		read(0,&key,1);

		//print("key=%s",&key);
		buffer[i]=key;
		print("key=0x%02x",key);
		if(key==0xa) {
			if(i>0)
			{
				
				key_data.key=buffer[i-1];
				key_data.sent=1;
				if(key_data.key=='q') break;
				print("key_buffer[0x%02x][%d] ",key_data.key,key_data.sent);
			}
			i=0;
		}
		else i++;

	}
	return 0;

}

int get_string(char *data)
{
	int i=0;
	char key;
	//char data[30];
	memset(data,0,sizeof(data));
	while(1)
	{
		/*
		   current key buffer is 16. 
		   but suppose  buffer is 4 bytes and command is 10bytes
		 */  
		read(0,&key,1);   
		if(key=='\n') 
		{
			data[i++]='\0';
			print("data[%s]",data);
			//data1=data;		
			return 0;
		}
		else
		{
			data[i++]=key;
		}
		if(i>16) return 1;

	}

}

typedef struct
{
	char *name;
	int (*func)(char *arg);

}command_t;


static int quit(char *arg)
{
	print("quit command");
	return 0;
}

static int test(char *arg)
{
	print("test command");
	return 0;
}


static command_t cmds[]=
{
	{"quit",quit},
	{"test",test},
	{NULL,NULL}

};


int test_get_string(void)
{
	int i;
	char key[16];
	char arg[2];
	while(1)
	{
		i=0;
		get_string(key);
		print("key=%s",key);
		while(cmds[i].name != NULL)
		{
			//print("key [%s] cmds.name [%s] i[%d]",key,cmds[i].name,i);
			if(!strcmp(key,cmds[i].name))
				cmds[i].func(arg);
			i++;
		}
	}

}

