#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  char fileName[] = "";
  char buffer[100];
  // Tworzymy potok nazwany FIFO
  // Mode 0400 - Dozwolony jest odczyt dla użytkownika, który utworzył FIFO.
  int filePipe = mkfifo(fileName, 0400);

  // Program dziala w nieskonczonej petli dopoki
  // uzytkownik nie poda "q" (quit) jako nazwy pliku
  while(1) {
    // Uzytkownik podaje nazwe pliku
    printf("File name:\n");
    scanf("%s", fileName);

    // Wspomniany wyzej warunek wyjscia
    if (strcmp(fileName, "q") != 0) {
      // Najczesciej uzywana funckja do otwierania plikow jest fopen()
      // poniewaz jest czescia standardu ANSI C (jest bardziej przenosna)
      // oraz zapewnia bufrowanie, ktore moze przyspieszyc proces, jednak
      // na zajeciach podane bylo wymaganie uzyacia open()
      int fileDescriptor = open(fileName, O_RDONLY);
      // Czytamy plik oznaczony przez fileDescriptor
      // poprzez utworzony bufor
      read(fileDescriptor, buffer, 100);
      // Zamykamy potok nazwany FIFO
      close(fileDescriptor);
      close(mkfifo);
    } else {
      exit(1);
    }
  }
}
