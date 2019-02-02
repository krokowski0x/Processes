#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(void) {
  pid_t pid;
  char name[100];
  int desc;
  int desc2;
  struct stat image;
  void *ptr = NULL;
  char file[] = "./file";

  pid = fork();

  if (pid == -1) {
    printf("Fork Failed !");
    return -1;
  } else if (pid == 0) {
    execlp("display", "display", "-update", "1", file, NULL);
  } else if (pid > 0) {
    while (1) {
      printf("Type the name of the image: \n");
      scanf("%s", name);
      if (strcmp(name, "q") == 0) {
	break;
      } else {
	desc = open (name, O_RDONLY);
	stat(name, &image);
	desc = open (file, image.st_size);
	ptr = mmap(NULL, image.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, desc2, 0);
	read(desc, ptr, image.st_size);
	msync(ptr, image.st_size, MS_SYNC);
	close(desc);
	close(desc2);
      }
    }
  }
}
