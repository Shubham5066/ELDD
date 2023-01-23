#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define WR_DATA _IOW('a','a',int32_t*)
#define RD_DATA _IOR('a','b',int32_t*)

int main()
{
    int fd;
    int32_t val,num;
    fd=open("/dev/driver4_device",O_RDWR);
    if(fd>0)
    {
        printf("\nsuccessfully opend");
    }
    else
    {
        printf("\nbad luck");
    }
    printf("Enter a number=");
    scanf("%d",&num);
    printf("\nwriting value in driver");
    ioctl(fd,WR_DATA,(int32_t*)&num);
    printf("Reading value \n");
    ioctl(fd,RD_DATA,(int32_t*)&val);
    printf("\nvalue=%d",val);
    printf("\nclosing driver");
    close(fd);
}