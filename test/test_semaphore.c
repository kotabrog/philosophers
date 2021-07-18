#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define SEMAPHORE_NAME ("/interproc_semaphore_sample")
#define CHILD_MAX (10)

sem_t* semaphore = NULL;

int	msleep(int milliseconds)
{
	struct timespec	t;

	t.tv_sec = milliseconds / 1000;
	t.tv_nsec = (milliseconds % 1000) * 1000000;

	return nanosleep(&t, NULL);
}

void child_main()
{
	pid_t pid = getpid();
	int semval = 0;

	printf( "ProcessID %d, started\n", pid );

	// セマフォのカウンタを表示する
	sem_getvalue( semaphore, &semval );

	printf( "->semaphore count: %d\n", semval );

	printf( "ProcessID %d, wait for semaphore\n", pid );

	// セマフォに入る
	sem_wait( semaphore );

	printf( "ProcessID %d, access to semaphore\n", pid );

	// 適当な時間だけ待ち合わせる
	msleep( 1500 );

	printf( "ProcessID %d, release semaphore\n", pid );

	// セマフォを出る
	sem_post( semaphore );

	// セマフォのカウンタを表示する
	sem_getvalue( semaphore, &semval );

	printf( "->semaphore count: %d\n", semval );

	printf( "ProcessID %d, exited\n", pid );
}

int main( void )
{
	// 初期値3のセマフォを作成する
	// (すでに同名のセマフォが存在する場合は、modeとvalueは無視される)
	semaphore = sem_open( SEMAPHORE_NAME, O_CREAT | O_EXCL, 0777, 3 );

	printf( "semaphore created\n" );

	// 250ミリ秒おきに子プロセスを生成する
	for ( int count = 0; count < CHILD_MAX; count++ )
	{
		pid_t pid = fork();

		if ( 0 == pid )
		{
			// 子プロセスの処理を開始する
			child_main();

			_exit( 0 );
		}
		else if ( -1 == pid )
		{
			printf( "fork failed\n" );

			return 1;
		}

		msleep( 300 );
	}

	// すべての子プロセスの終了を待機する
	for ( int count = 0; count < CHILD_MAX; )
	{
		int status;
		pid_t pid;

		pid = waitpid( -1, &status, WNOHANG );

		if( 0 < pid )
		{
			// 子プロセスが終了した
			count++;

			continue;
		}
		else if ( -1 == pid )
		{
			break;
		}

		// 500ミリ秒おきに子プロセスの状態を監視する
		msleep( 500 );
	}

	printf( "all processes are finished\n" );

	// セマフォを破棄する
	sem_close( semaphore );

	printf( "semaphore closed\n" );

	// セマフォを削除する
	sem_unlink( SEMAPHORE_NAME );

	printf( "semaphore unlinked\n" );

	return 0;
}