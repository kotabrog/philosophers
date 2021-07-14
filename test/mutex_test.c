#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

const size_t	loop_max = 65535;

pthread_mutex_t	m;
int	counter = 0;

void	f1();
void	f2();

int	main(int argc, char *argv[])
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			ret1;
	int			ret2;

	if (pthread_mutex_destroy(&m));
		printf("pthread_mutex_destroy error\n");
	pthread_mutex_init(&m, NULL);
	ret1 = pthread_create(&thread1, NULL, (void *)f1, NULL);
	ret2 = pthread_create(&thread2, NULL, (void *)f2, NULL);

	if (ret1 != 0)
	{
		err(EXIT_FAILURE, "can not create thread 1: %s", strerror(ret1));
	}
	if (ret2 != 0)
	{
		err(EXIT_FAILURE, "can not create thread 2: %s", strerror(ret2));
	}

	printf("execute pthread_join thread1\n");
	ret1 = pthread_join(thread1, NULL);
	if (ret1 != 0)
	{
		err(EXIT_FAILURE, "can not join thread 1");
	}

	printf("execute pthread_join thread2\n");
	ret2 = pthread_join(thread2, NULL);
	if (ret2 != 0)
	{
		err(EXIT_FAILURE, "can not join thread 2");
	}

	printf("done\n");
	printf("%d\n", counter);

	pthread_mutex_destroy(&m);
	if (pthread_mutex_destroy(&m));
		printf("pthread_mutex_destroy error\n");
}

void	f1(void)
{
	size_t	i;

	for (i = 0; i < loop_max; ++i)
	{
		int	r;
		r = pthread_mutex_lock(&m);
		if (r != 0)
		{
			err(EXIT_FAILURE, "can not lock");
		}

		counter++;

		r = pthread_mutex_unlock(&m);
		if (r != 0)
		{
			err(EXIT_FAILURE, "can not unlock");
		}
	}
}

void	f2(void)
{
	size_t	i;

	for (i = 0; i < loop_max; ++i)
	{
		if (pthread_mutex_lock(&m) != 0)
		{
			err(EXIT_FAILURE, "can not lock");
		}

		counter++;

		if (pthread_mutex_unlock(&m) != 0)
		{
			err(EXIT_FAILURE, "can not unlock");
		}
	}
}
