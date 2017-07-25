#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
int op=0;
int op2=0;
int result;
int oper_frag=-1;

void usr1_handler(int signum);
void usr2_handler(int signum);
void hup_handler(int signum);
void int_handler(int signum);
void alrm_handler(int signum);



int main(){
	//printing process id
	//printf("pid: %d\n", getpid());
	struct sigaction act1,act2,act3,act4,act5;
	act1.sa_handler=usr1_handler;
	sigemptyset(&act1.sa_mask);
	act1.sa_flags = 0;
	act2.sa_handler=usr2_handler;
	sigemptyset(&act2.sa_mask);
	act2.sa_flags = 0;
	act3.sa_handler=hup_handler;
	sigemptyset(&act3.sa_mask);
	act3.sa_flags = 0;
	act4.sa_handler=int_handler;
	sigemptyset(&act4.sa_mask);
	act4.sa_flags = 0;
	act5.sa_handler=alrm_handler;
	sigemptyset(&act5.sa_mask);
	act5.sa_flags = 0;
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	sigaction(SIGHUP, &act3, NULL);
	sigaction(SIGINT, &act4, NULL);
	sigaction(SIGALRM, &act5, NULL);

	while(1){

	}
	return 0;
}
void usr1_handler(int signum){
	assert(signum==SIGUSR1);
	op++;
}
void usr2_handler(int signum){
	assert(signum==SIGUSR2);
	op2=op;
	op=0;
	printf("%d\n", op2 );
	if(result==0){
		result=op2;
	}
	if(oper_frag==1){
		result=result+op2;
		oper_frag=-1;
	}
	if(oper_frag==0){
		result=result-op2;
		oper_frag=-1;
	}

}
void hup_handler(int signum){
	assert(signum==SIGHUP);
	printf("+\n");
	oper_frag=1;

}
void int_handler(int signum){
	assert(signum==SIGINT);
	printf("-\n");
	oper_frag=0;

}
void alrm_handler(int signum){
	assert(signum==SIGALRM);
	printf("=\n%d\n", result);
	op=0;
	op2=0;
	result=0;
}