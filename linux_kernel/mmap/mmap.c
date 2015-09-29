/// \file mmap.c


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){
	int source;
	int dest;
	struct stat statbuf;
	void *pDest, *pSource;
	if(argc < 3){
		printf("实例格式：./执行程序 源文件 目标文件\n");
		return 0;
	}
	source = open(argv[1], O_RDONLY);
	dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(source < 0 || dest < 0){
		printf("open file fail\n");
		goto fail;
	}
	if( fstat(source, &statbuf) < 0 ){
		//fstat函数将参数source所指的文件状态，复制到参数statbuf所指的结构中(struct stat)
		printf("fstat fail\n");
		goto fail;
	}
	if( ftruncate(dest, statbuf.st_size) == -1){
		//ftruncate将参数dest指定的文件大小改为参数2指定的大小
		printf("ftruncate fail\n");
		goto fail;
	}
	pSource = mmap(0, (size_t)statbuf.st_size, PROT_READ, MAP_PRIVATE | MAP_NORESERVE, source, 0);
	//void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
	if(pSource == MAP_FAILED){
		printf("mmap source file fail\n");
		goto fail;	
	}
	pDest = mmap(0, (size_t)statbuf.st_size, PROT_WRITE, MAP_SHARED, dest, 0);
	if(pDest == MAP_FAILED){
		printf("mmap dest file fail\n");
		goto fail;
	}
	memcpy(pDest, pSource, (size_t)statbuf.st_size);
	//从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中

fail:
	close(source);
	close(dest);
	return 0;
}
