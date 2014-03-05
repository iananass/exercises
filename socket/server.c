#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>

#define SOCK_PATH "echo_socket"

static int socketalive = 0;

int MakeAClient();
void sigchld_hdl(int sig);

void sigchld_hdl(int sig)
{
    socketalive = 0;
    MakeAClient();
}

int MakeAClient()
{
    int pid = fork();
    if (pid < 0)
        return -1;
    if (pid == 0) {
        char *cmd[] = {"client", (char *) 0};
        execvp("./client", cmd);
        fprintf(stderr, "an error occurred in execvp\n");
    }
}

int main(void)
{
    MakeAClient();
    struct sigaction act;
    int i;

    memset(&act, 0, sizeof (act));
    act.sa_handler = sigchld_hdl;

    if (sigaction(SIGCHLD, &act, 0)) {
        perror("sigaction");
        return 1;
    }


    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof (local.sun_family);
    if (bind(s, (struct sockaddr *) &local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    for (;;) {
        printf("Waiting for a new connection...\n");
        t = sizeof (remote);
        if ((s2 = accept(s, (struct sockaddr *) &remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }
        socketalive = 1;

        printf("Connected.\n");

        char str[128];
        do {
            fgets(str, sizeof (str) - 1, stdin);
            if (socketalive) {
                if (send(s2, str, strlen(str) + 1, 0) < 0) {
                    perror("send");
                }
            } else
                break;
        } while (1);

        close(s2);
    }

    return 0;
}