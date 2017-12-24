/*
*Function：Service_InPc.c  任务是在树莓派里面，这里先在pc里面实现。
*Description：这个函数用来捕捉31003端口的mjpeg流。
*     具体网络接收时可以先接收一个FRAME_INFO大小的包，读出mjpeg的数据大小，然后根据mjpeg数据大小接收一帧mjpeg数据。
*	  FRAME_INFO也就是其数据格式
*Name：温怀雄
*Date：2017/12/20
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*系统调用*/
#include <sys/types.h> /* 提供类型 pid_t 的定义 */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*Pony提供的端口为31003*/
#define PORT 31003

#define BUFFER_SIZE	1024	//buffer

#define DEST_FILE_NAME "./first.jpg"

typedef struct _FRAME_INFO
	{
		int nWidth;					//mjpeg图片宽度
		int nHeight;				//mjpeg图片高度
		unsigned long frameID;		//帧序列号
		unsigned long dataLen;		//mjpeg数据大小
	}FRAME_INFO;



int main(int argc, char *argv[])
{
	int sockfd,recvbytes;
	char buf[BUFFER_SIZE];
	struct hostent *host;
	struct sockaddr_in serv_addr;
	FRAME_INFO frame1_info;

	int dest_file;

	if(argc < 2)
	{
		fprintf(stderr,"usage: ./client Hostname(or ip address)\n");
		exit(1);
	}

	/*地址解析函数*/
	if ((host = gethostbyname(argv[1])) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
	memset(buf, 0, sizeof(buf));

	/*创建 socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	printf("socked created success!\n");  //测试

	/*设置 sockaddr_in 结构体中相关参数*/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(serv_addr.sin_zero), 8);

	/*调用 connect 函数主动发起对服务器端的连接*/
	if(connect(sockfd,(struct sockaddr *)&serv_addr,
	sizeof(struct sockaddr))== -1)
	{
		perror("connect");
		exit(1);
	}
	printf("connected success!\n");  //测试

	/*打开第一个存储文件*/
	if((dest_file = open(DEST_FILE_NAME,
					O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0)
	{
		printf("open jpg file error\n");
	}


	/*接收一个FRAME_INFO的大小,读出mjpeg的数据大小,根据mjpeg数据大小接收一帧mjpeg数据*/
	if((read (struct file *filp, char *buff, size_t count, loff_t *offp))
	{

	}

	/**/

	// if(recvbytes = recv(sockfd,buf,BUFFER_SIZE, 0) < 0)
	// {
	// 	printf("recv error!\n");
	// 	exit(1);
	// }
	// printf("recvbytes = %d\n",recvbytes);
	// printf("%s\n",buf);
	printf("the end!\n");	//测试

	//close(sockfd);
	exit(0);
}