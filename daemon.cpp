#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int exist_process(pid_t pid){
	int r = kill(pid, 0);
	if(r == 0) return 1;
	if(errno == EPERM) return 1;
	return 0;
}

void daemon_init(){
	FILE *fp;
	fp = fopen("PID", "r");
	if(fp != NULL){
		int p;
		fscanf(fp, "PID:%d", &p);
		if(exist_process((pid_t)p)){
			fprintf(stderr, "daemon already exists.\n");
			fclose(fp);
			exit(1);
		}
		fclose(fp);
	}
	
	fp = fopen("PID", "w");
	if(fp == NULL){
		fprintf(stderr, "error");
		return;
	}
	pid_t pid = getpid();
	fprintf(fp, "PID:%d\n", pid);
	fclose(fp);
}

int main(){
	daemon_init();

	while(1){
		sleep(3);
	}
}
