#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main()
{
	char read_msg[BUFFER_SIZE];
	int fd[2];
	pid_t pid;

	if(pipe(fd)==-1)
	{
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid=fork();
	if(pid<0)
	{
		fprintf(stderr,"FORK failed");
		return 1;
	}
	if(pid>0)
	{
		close(fd[READ_END]);
	char write_msg[BUFFER_SIZE]="greetings";
		write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
		close(fd[WRITE_END]);
	}
	else
	{
		close(fd[WRITE_END]);
		read(fd[READ_END],read_msg,BUFFER_SIZE);
		printf("read %s",read_msg);
		close(fd[READ_END]);
	}
	return 0;
}
