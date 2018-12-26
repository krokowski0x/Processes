#include <stdio.h>
#include <time.h>

int main() 
{
    int i = 0;
    int milisec = 100; // length of time to sleep, in miliseconds
    struct timespec req = {0};

    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;

    while(1) 
    {
        nanosleep(&req, (struct timespec*)NULL);
        ++i;
    }
    
    return 0;
}
