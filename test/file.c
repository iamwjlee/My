#include "common.h"
#include "sys.h"

int io_read(FILE *f,unsigned char *buf,int size)
{

	fread(buf,1,size,f);

}
int io_write(FILE *f,unsigned char *buf,int size)
{

	fwrite(buf,1,size,f);

}

void make_bin_file(void)
{
	FILE *o;
	unsigned char buf[10]={1,2,3,4,5,6,7,8,9,10};
	char *file="test.bin";
	
	printf("make bin file[%s]\n",file);
	o=fopen(file,"w");
	printf("size= %d\n", sizeof(buf));
	fwrite(buf,1,sizeof(buf),o);
	fclose(o);
	printf("end of function\n");


}


void file_test(void)
{
	
    	FILE *in, *out;
	int size;
	int p_size=4;
	int eof=0;
	 int  i;
	unsigned char *buffer=NULL;
	unsigned char *buf_ptr;
	unsigned char *buf_end;
	int len;

	char *input="test.bin";
	char *output="test_out.bin";

	printf("helllo\n");
	

	in= fopen(input,"r");
	out= fopen(output,"w");


	fseek(in, 0, SEEK_END);
	size = ftell(in); 
	printf("%s filesize:%d\n",input,size);
	
	fseek(in, 0, SEEK_SET);


	buffer =(unsigned char *) malloc(sizeof(unsigned char)*p_size); 

	memset(buffer,0,p_size);
	while(!eof)
	{
		len = fread(buffer, 1, p_size, in);
	
		fwrite(buffer, len, 1, out); //
		if(len==0) eof=1;
	
		
	}
	free(buffer);
	
	fclose(in);
	fclose(out);
	return 0;



	
}
void file_test_00(void)
{
	
    	FILE *in, *out;
	int size;
	unsigned int  i;
	unsigned char *buffer=NULL;
	printf("helllo\n");
	in= fopen("1.zip","r");

	fseek(in, 0, SEEK_END);
	size = ftell(in); 
	printf("filesize:%d\n",size);

	fseek(in, 0, SEEK_SET);

	buffer =(unsigned char *) malloc(sizeof(unsigned char)*size); 
	memset(buffer,0,size);
	fread(buffer, 1, size, in);
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

	fclose(in);

	out= fopen("1-1.zip","w");


	fwrite(buffer, size, 1, out); //


	fclose(out);
	return 0;



	
}
