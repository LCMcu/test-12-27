#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "proto.h"

// ./a.out ip
int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in remote_addr;
	char buf[MAX_MSG] = {};
	int cnt;

	if (argc < 2)
		exit(1);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		perror("socket()");
		exit(1);
	}

	// bind()

	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = htons(SERVER_PORT);
	inet_aton(argv[1], &remote_addr.sin_addr);

	if (connect(sd, (void *)&remote_addr, sizeof(remote_addr)) < 0) {
		perror("connect()");
		goto ERROR;
	}

	while (1) {
		cnt = read(sd, buf, MAX_MSG);
		if (cnt < 0) {
			// EINTR
			perror("read()");
			goto ERROR;
		}
		if (cnt == 0)
			break;
		puts(buf);
	}

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

