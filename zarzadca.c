#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Uzycie: %s N\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "N musi byc dodatnia liczba\n");
        exit(EXIT_FAILURE);
    }

    printf("Proces glowny PID=%d tworzy %d potomkow\n", getpid(), N);

    for (int i = 0; i < N; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            printf("Potomek #%d: PID=%d, PPID=%d\n",
                   i + 1, getpid(), getppid());
            exit(i + 1);
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid > 0 && WIFEXITED(status)) {
            printf("Proces glowny: potomek PID=%d zakonczyl sie kodem %d\n",
                   child_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
