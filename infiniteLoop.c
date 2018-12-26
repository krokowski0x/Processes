#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

void sigalrm();
void sigterm();
void sigusr();

int main()
{
    // Obsluga sygnalow
    signal(SIGALRM, sigalrm);
    signal(SIGTERM, sigterm);
    signal(SIGUSR1, sigusr);
    signal(SIGUSR2, SIG_IGN);
    
    // Nieskonczona petla
    for(;;);

    return 0;
}

void sigalrm()
{
    // Komunikat i wyjscie z programu
    printf("Quitting program...");
    exit(0);
}

void sigterm()
{
    // Komunikat i wznowienie pracy
    printf("Got your signal!\nResuming program...");
}

void sigusr()
{
    // Deklaracja dwóch masek
    sigset_t filledMask, emptyMask;

    // Maska blokująca wszystkie sygnaly
    sigfillset(&filledMask);

    // Maska odblokowujaca wszystkie sygnaly
    sigemptyset(&emptyMask);

    // Blokujemy obsluge sygnalow
    printf("I won\'t listen to signals now...");
    sigprocmask(SIG_SETMASK, &filledMask, NULL);

    // Czekamy 5 sekund
    sleep(5);

    // Odblokowujemy obsluge sygnalow
    sigprocmask(SIG_SETMASK, &emptyMask, NULL);
    printf("OK. I\'m listening again");
}
