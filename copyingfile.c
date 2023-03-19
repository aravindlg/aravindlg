#include <stdio.h>
#include <fcntl.h>
#define BUF_SIZE 1024

int main()
{
	int inputFd, outputFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE];

	inputFd = open("file1.txt",O_RDONLY);
	if(inputFd == -1)
	{
		printf("Open Error\n");
		return;
	}
	
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	outputFd = open("file2.txt",openFlags,filePerms);
	if(outputFd == -1)
	{
		printf("Opening file\n");
		return;
	}
	
	/*Transfer data until we encounter end of input or an error*/
	while((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
	{
		if(write(outputFd, buf, numRead) != numRead)
		{
			printf("Write Error\n");
			return;
		}
		printf("%d\n",numRead);	
	}	
	if(numRead == -1)
	{
		printf("Read Error\n");
		return;
	}
	if(close(inputFd) == -1)
	{
		printf("Close input\n");
		return;
	}
	if(close(outputFd) == -1)
	{
		printf("Close Output\n");
		return;
	}
}
