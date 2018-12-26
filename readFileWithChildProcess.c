#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int filePipe[2];
    int bytes;
    int fileDescriptor;
    pid_t pid;
    char fileName[] = "";
    char fileBuffer[1024];

    // Tworzymy potok
    pipe(filePipe);
    // Forkujemy child process
    pid = fork();

    // fork() zwraca -1 jeśli uruchamianie
    // podprocesu się nie powoiodło
    if (pid == -1) {
        // Wypisujemy wiadomość na STDERR
        printf(stderr, "Program failed to fork child process.");
        // Wychodzimy z programu komunikując błąd kodem 1
        return 1;
    }

    // Jeśli pid jest dodatnie, jesteśmy w child process'ie
    if (pid > 0) {
        // Zamykamy "na wszelki wypadek" proces 0
        close(filePipe[0]);
        // Operacja close jest względnie asynchrniczna (może
        // zająć chwilę), a więc czekamy 200us "na wszelki wypadek"
        usleep(200);
        // Uzytkownik podaje nazwe pliku
        printf("File name:\n");
        scanf("%s", fileName);
        // Najczesciej uzywana funckja do otwierania plikow jest fopen()
        // poniewaz jest czescia standardu ANSI C (jest bardziej przenosna)
        // oraz zapewnia bufrowanie, ktore moze przyspieszyc proces, jednak
        // na zajeciach podane bylo wymaganie uzyacia open()
        fileDescriptor = open(fileName, O_RDONLY);

        // Czytamy po kolei bajty pliku z bufora
        while (bytes = read(fileDescriptor, fileBuffer, 1024) > 0) {
            write(filePipe[1], fileBuffer, bytes))
        }
        // Po czym zamykamy proces
        close(filePipe[1]);
    }

    // Jesli trafilismy do tego procesu, plik jest juz
    // odczytany i otwieramy plik funckja execlpl()
    if (pid == 0) {
        // Zamykamy plik
        close(0);
        // Klonujemy fileDescriptor tego procesu
        dup(filePipe[0]);
        // Zamykamy proces 1, ktory czytal plik
        close(fliePipe[1]);
        // Odmiana programu exec* i wartosci argumentow
        // zostaly odczytane z programu "man" - podany
        // tutaj zestaw otwiera plik JPEG/PNG
        execlp("display", "", NULL);
        exit(1);
    }
    exit(1);
}
