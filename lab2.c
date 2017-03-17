#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *get_line(int fd);
int read_char(int fd);

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[])
{
  int exitStatus = 0;
  int count = 1;
  int numberblanks=0;
  char *line;
  int fp;
  int firstfile = 1;
  if (argc >= 2 && strncmp(argv[1],"-",1) == 0) {
    firstfile = 2;
    if (strcmp(argv[1],"-b")==0)
      numberblanks = 1; 
    else if  (strcmp(argv[1],"-n")==0)
      numberblanks = 2; 
    else {
      fprintf(stderr,"Invalid option: %s\n",argv[1]);
      exit(EXIT_FAILURE); }
  }

  if ((argc == 1) || ((argc == 2) && (numberblanks != 0))) {
    /*while ((line = get_line(stdin)) != NULL){
      if(numberblanks == 2){
        printf("%6d\t",count);
        count++;
      } else if(numberblanks == 1) {
        if(strcmp(line,"\n")!=0){
          printf("%6d\t",count);
          count++;
        }
      }
      printf("%s",line);
    }*/
  } else {
    for (int i=firstfile; i<argc; i++) {
    	//printf("check\n");
      if ((fp = open(argv[i],O_RDONLY)) == -1) {
        fprintf(stderr,"%s: %s: %s\n",
                argv[0],argv[i],strerror(errno));
        exitStatus = 1;
        continue;
      } else {
    	  //printf("check\n");
        while ((line = get_line(fp)) != NULL){
        	//printf("check\n");
          if(numberblanks == 2){
            printf("%6d\t",count);
            count++;
          } else if(numberblanks == 1) {
            if(strcmp(line,"\n")!=0){
              printf("%6d\t",count);
              count++;
            }
          }
          printf("%s",line);
        }
        close(fp);
      }
    }
  }

  return ((exitStatus == 1)?EXIT_FAILURE:EXIT_SUCCESS);
}


char *get_line(int fd) {

  static char buff[MAX_LINE_LENGTH+2];

  int pos = 0;
  int next;
  int buf;

  //if(next == EOF) return NULL;

  while ((next = read(fd, &buf, 1)) > 0 && buf != '\n') {
        buff[pos++] = buf; }

  /*do {
	  //printf("next = %d\n",next);
    if(buf == '\n') {
      buff[pos++] = buf;
      break;
    }
    buff[pos++] = buf;
  } while ((next = read(fd, &buf, 1)) > 0);*/

  if ((pos == 0 && next == 0) || errno)
        return NULL;

  buff[pos] = '\0';

  return buff;

  /*int pos = 0, next, nread;

    while ((nread = read(fd,&next,1)) > 0 && next != '\n') {
      buff[pos++] = next; }

    if ((pos == 0 && nread == 0) || errno)
      return NULL;

    buff[pos++] = '\n';
    buff[pos++] = '\0';

   return buff;*/
}

int read_char(int fd) {
	int buf;
	return read(fd, &buf, 1);
}