#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/reg.h> /* For user_regs_struct
			etc. */
int main(int argc, char *argv[]) {
	pid_t traced_process;
	struct user_regs_struct regs;
	long ins;
	if (argc != 2) {
		printf("Usage: %s <pid to be traced>\n",argv[0]);
		exit(1);
	}
	traced_process = atoi(argv[1]);
	ptrace(PTRACE_ATTACH, traced_process,NULL, NULL);
	wait(NULL);
	ptrace(PTRACE_GETREGS, traced_process,NULL, &regs);
	ins = ptrace(PTRACE_PEEKTEXT, traced_process,regs.rip, NULL);
	printf("EIP: %llx Instruction executed: %lx\n",regs.rip, ins);
	ptrace(PTRACE_DETACH, traced_process,NULL, NULL);
	return 0;
}
