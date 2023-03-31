/**
 * Given APUE sigusr.c, extend the signal handling in the code such that it also captures the SIGCONT signal
 * such that it captures the signal, prints out "received SIGCONT" and continues running
 *
 * Author Names:
 * Diego Cruz
 * Saim Sheikh
 *
 * Author emails:
 * diego.cruz@sjsu.edu
 * saim.sheikh@sjsu.edu
 *
 * Last Modified: 04/03/2023
 * Creation Date: 03/31/2023
 */

#include "apue.h"

static void sig_usr(int); /* one handler for both signals */

static void sig_usr(int signo) /* argument is signal number */
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else if (signo == SIGCONT)
        printf("received SIGCONT\n");
    else
        err_dump("received signal %d\n", signo);
}

int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR2");
     if (signal(SIGCONT, sig_usr) == SIG_ERR)
      err_sys("can't catch SIGCONT");
    for (;;)
        pause();
}