#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	incrypted_msg(char c, int pid)
{
	int i = 0;
	char c2;
	
	while(i < 7)
	{	
		c2 = c >> i;
		if (c2 & 1 == 0)
	    {
			kill(SIGUSER1, pid);
	    }
	    else if (c2 & 1 == 1)
	    {
	        kill(SIGUSR2, pid);
	    }
		i++;
	}
}

int main(int argc, char *argv[])
{
	int	pid;
	int i;

	i = 0;
    if (argc == 3)
    {
		pid = atoi(argv[1]);
		while (argv[2][i])
		{
			incrypted_msg(argv[2][i], pid);
			i++;
		}
    }
}