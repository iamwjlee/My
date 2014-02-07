#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define d_print(...)  printf(__VA_ARGS__)


int sys_command(char **args)
{
	int pid;

	
	if ((args!=NULL)&&(args[0]!=NULL))
	 {
	 	
		/* Execute a fork to run the system call */
		pid = fork();
		if(pid == 0)
		{
			execvp(args[0],args);
			d_print("command not found \n");
			exit(1);
		}
	}
	return 0;

}

void test_sys_command(void)
{
char *Command[]={"free","-t","-k","-o",NULL};
char *Command2[]={"cat","/proc/meminfo",NULL};
char Command3[30] = {"uname -r"};

d_print("----------------\n");

sys_command(Command);
sys_command(Command2);
system(Command3);

}

