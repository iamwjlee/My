#include "common.h"
#include "sys.h"


void file_test(void)
{
	
    	FILE *file;
	int size;
	unsigned int  i;
	unsigned char *buffer=NULL;
	printf("helllo\n");
	file= fopen("1.zip","r");

	fseek(file, 0, SEEK_END);
	size = ftell(file); 
	printf("filesize:%d\n",size);

	fseek(file, 0, SEEK_SET);

	buffer =(unsigned char *) malloc(sizeof(unsigned char)*size); 
	memset(buffer,0,size);
	fread(buffer, 1, size, file);
	for(i=0;i<10; i++)
	{
		if(i%16==0) printf("\n");
		printf("0x%02x ",buffer[i]);	

	}
	buffer[2*1024]=buffer[5];  // test

	buffer[30*1024]=buffer[5];	// test
	//	buffer[64*1024*4]=buffer[64*1024*8+1];	// test
	//buffer[64*1024*40 ]=buffer[64*1024*11+4];  // test
	//buffer[64*1024*43 ]=buffer[64*1024*11+4];  // test

	fclose(file);

	file= fopen("1-1.zip","w");


	fwrite(buffer, size, 1, file); //


	fclose(file);
	return 0;



	
}
