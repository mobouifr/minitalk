#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void    signal_handler(int signum) 
{
    static char   c;
    static int counter;


        if (signum == SIGUSR1)
        {
            c = c | 0;
            //printf("SIGUSR1\n");
        }
        else if (signum == SIGUSR2)
        {
            c = c | 1;
            //printf("SIGUSR2\n");
        }
    counter++;
    if (counter == 8)
    {
        counter = 0;
        printf("%d\n", c);
        c = 0;
    }
    c = c << 1;

}

int main() 
{
    
    int pid;
    
    pid = getpid();
    printf("pid : %d\n", pid);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
 
    while(1) 
    {
  
    }

    return 0;
}
