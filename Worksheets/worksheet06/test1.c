#include "apue.h"

int
main(void)
{
	pid_t	pid;
  printf("hello world(pid:%d)\n", (int)getpid());
	if ((pid = fork()) < 0)
		err_sys("fork error");
		/* parent */
	else if (pid != 0) {		
        printf("PARENT PROCESS  pid %d\n", getpid());
		sleep(2);
		/* terminate with exit status 2 */
		exit(2);				
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
		/* first child */
	else if (pid != 0) {		
        printf("1st Child Process pid %d\n", getpid());
		sleep(4);
		/* terminate with core dump */
		abort();				
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
		/* second child */
	else if (pid != 0) {		
        printf("2nd Child Process pid %d\n", getpid());
		execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
		/* shouldn't get here */
		exit(7);				
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
		/* third child */
	else if (pid != 0) {		
        printf("3rd Child process pid %d\n", getpid());
		sleep(8);
		/* normal exit */
		exit(0);				
	}

    printf("4th Child Process pid %d\n", getpid());
	/* fourth child */
	sleep(6);
	/* terminate w/signal, no core dump */				
	kill(getpid(), SIGKILL);	
	/* shouldn't get here */
	exit(6);					
}
