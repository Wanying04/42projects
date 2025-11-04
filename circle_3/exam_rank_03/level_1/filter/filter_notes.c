//read()用法

//固定缓冲区
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];
ssize_t bytes_read;

bytes_read = read(0, buffer, BUFFER_SIZE - 1);
if (bytes_read > 0)
	buffer[bytes_read] = '\0';
else if (bytes_read == 0)
	return (0);
else
	perror("read");

//动态缓冲区
