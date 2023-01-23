#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int8_t read_buf[1024];
int main()
{
    int fd;
    char option;
    printf("welcome to the demo of character device driver ....\n");
    fd=open("/dev/driver3_device",O_RDWR);
    if(fd > 0)
    {
        printf("cannot open the device file...\n");
        return 0;
    }
    else
    {
    	printf("cannot open device file...\n");
    	return 0;
    }
    while(1)
    {
        printf("******please enter your option******\n");
        printf("        1.read      \n");
        printf("        2.exit      \n");
        scanf(" %c",&option);
        printf("******your option =%c\n",option);
        switch(option)
        {
            case '1':
                    printf("    DATA IS READING............\n");
                    read(fd,read_buf,1024);
                    printf("<<<<<<<<<<<<<<DONE>>>>>>>>>>>>>>\n");
                    printf("Data=%s\n\n",read_buf);
                    break;
            case '2':
                    close(fd);
                    exit(1);
                    break;
            default:
                    printf("Enter valid option\n");
                    break;
        }
    }
    close(fd);
}