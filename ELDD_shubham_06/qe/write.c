#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int8_t write_buf[1024];
int main()
{
    int fd;
    char option;
    printf("welcome to the demo of character device driver ....\n");
    fd=open("/dev/my_device",O_RDWR);
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
        printf("        1.write     \n");
        printf("        2.exit      \n");
        scanf(" %c",&option);
        printf("******your option =%c\n",option);
        switch(option)
        {
            case '1':
                    printf("    ENTER THE STRING IN DRIVER  \n");
                    scanf(" %[^\t\n]s", write_buf);
                    printf("***DATA WRITEN***\n");
                    write(fd,write_buf, strlen(write_buf)+1);
                    printf("<<<<<<<<<<<<<<DONE>>>>>>>>>>>>>>\n");
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