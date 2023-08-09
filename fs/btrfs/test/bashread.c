#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
int main(int argc, const char* argv[])
{
ssize_t nr;
/* return value from read(2) */char *string;
struct stat finfo;
int fd;
size_t file_size;
int tracing;
char command[100];
if(argc < 2){
printf("please specify filename\n");
return -1;
}
tracing = open ("/sys/kernel/debug/tracing/tracing_on", O_WRONLY);
if(tracing < 0)
{
printf("failed to open tracing\n");
return -1;
}
write(tracing, "0", 1);
system("echo > /sys/kernel/debug/tracing/trace");
fd = open (argv[1], O_RDONLY);
if (fd < 0 || (fstat (fd, &finfo) == -1))
{
printf("open file %s failed\n", argv[1]);
return -1;
}
file_size = (size_t)finfo.st_size;
string = (char *)malloc (1 + file_size);
printf("trying read, %s, %d\n", argv[1], file_size);
sprintf(command,"echo %d > /sys/kernel/debug/tracing/set_ftrace_pid", getpid());
printf("set pid: %s\n", command);
system(command);
write(tracing, "1", 1);
nr = read (fd, string, file_size);
#if 0
while(1)
{
	file_size += 1;
}
#endif
write(tracing, "0", 1);
printf("end read\n");
close(fd);
return 0;
}
