#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

	int sock0, sock;
	sock0 = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addr;
	sockaddr_in client;
	int len;
	addr.sin_family	= AF_INET;
	addr.sin_port	= htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock0, (sockaddr*)&addr, sizeof(addr));
	listen(sock0, 5);
	while(1){
		len	= sizeof(client);
		sock	= accept(sock0, (sockaddr*)&client, (socklen_t*)&len);
		fprintf(stderr, "connection from %s, port=%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		write(sock, "HELLO", 5);
		close(sock);
	}
	close(sock0);

	while(1){
		sleep(3);
	}
}
