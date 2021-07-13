# include <stdio.h>
# include <sys/time.h>
# include <errno.h>
# include <stdlib.h>

int main()
{
	struct timeval	time;
	time_t			sec;
	suseconds_t		usec;
	if (gettimeofday(&time, NULL))
	{
		printf("%d\n", errno);
		exit(EXIT_FAILURE);
	}
	sec = time.tv_sec;
	usec = time.tv_usec;
	printf("%ld\n", sec);
	printf("%ld\n", usec);
}
