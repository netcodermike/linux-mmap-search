#define _POSIX_C_SOURCE 200809L
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
int main(int argc,char**argv){if(argc!=3||!argv[1][0]){fprintf(stderr,"Usage: app LITERAL FILE\nPrints 1-based line and zero-based byte offset for overlapping matches.\n");return 2;}size_t length=strlen(argv[1]);if(length>4096)return 2;int fd=open(argv[2],O_RDONLY);if(fd<0){perror("open");return 1;}struct stat st;if(fstat(fd,&st)||!S_ISREG(st.st_mode)||st.st_size<0||(uintmax_t)st.st_size>SIZE_MAX){fprintf(stderr,"Regular file required\n");close(fd);return 1;}size_t size=(size_t)st.st_size;if(!size){puts("matches=0");close(fd);return 0;}const char*data=mmap(NULL,size,PROT_READ,MAP_PRIVATE,fd,0);if(data==MAP_FAILED){perror("mmap");close(fd);return 1;}size_t count=0,line=1;for(size_t i=0;i<size;i++){if(length<=size-i&&!memcmp(data+i,argv[1],length)){printf("%zu:%zu\n",line,i);count++;}if(data[i]=='\n')line++;}printf("matches=%zu\n",count);munmap((void*)data,size);close(fd);return 0;}
