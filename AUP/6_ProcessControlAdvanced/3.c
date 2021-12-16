#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdio.h>

//To check if process is in foreground or not
int is_ps_fg(void) {

		int p_pgrp, fg_pgrp;

		if ((p_pgrp = getpgrp()) == -1) {
				perror("parent getpgrp");
				return errno;
		}

		if ((fg_pgrp = tcgetpgrp(STDIN_FILENO)) == -1) {
				perror("parent tcgetpgrp");
				return errno;
		}

		if (fg_pgrp == p_pgrp) {
				return 1;
		}
		else {
				return 0;
		}

}



int main(void) {

		int cpid;
		int status;

		if ((cpid = fork())) {
				/* parent */
				if (setpgid(cpid, 0) == -1) {
						perror("setpgid in parent");
						return errno;
				}

				if (tcsetpgrp(STDIN_FILENO, cpid) == -1) {
						perror("tcsetpgrp in parent");
						return errno;
				}

				if (is_ps_fg()) {
						printf("BEFORE WAIT: Parent is foreground\n\n");
				}
				else {
						printf("BEFORE WAIT: Parent is NOT foreground\n\n");
				}

				if (wait(&status) == -1) {
						perror("wait");
						return errno;
				}

				if (is_ps_fg()) {
						printf("AFTER WAIT: Parent is foreground\n\n");
				}
				else {
						printf("AFTER WAIT: Parent is NOT foreground\n\n");
				}
		}
		else {
				/* child */


				if (setpgid(0, 0) == -1) {
						perror("setpgid in child");
						return errno;
				}


				if (tcsetpgrp(STDIN_FILENO, getpgid(0)) == -1) {
						perror("tcsetpgrp in parent");
						return errno;
				}

				if (system("ps -o cmd,pid,ppid,pgid,tpgid") == -1) {
						perror("ps");
						return errno;
				}

				if (is_ps_fg()) {
						printf("\nIN CHILD: Process is foreground\n\n");
				}
				else {
						printf("\nIN CHILD: Process is NOT foreground\n\n");
				}
		}
}


