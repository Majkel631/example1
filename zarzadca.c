zadanie 1: 
1utworzenie + nano task1.sh

2kod w srodku : 
#!/bin/bash

FIFO="kolejka_danych"

# 1. Utwórz potok nazwany
mkfifo "$FIFO"

# 2. Uruchom podpowłokę w tle
(
    sleep 2
    echo "SYSTEM_OK" > "$FIFO"
) &

# 4. Odczytaj z FIFO, zamień na małe litery i wyświetl
read dane < "$FIFO"
echo "$dane" | tr 'A-Z' 'a-z'

# 5. Usuń potok
rm "$FIFO"

3nadanie uprawnien jak to jest terminal funjcja + chmod +x task1.sh
4odpalanie programu + ./task1.sh

zadanie 2: 
1 = nano task2.c
2=
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // 1. Utworzenie procesu potomnego
    pid = fork();

    if (pid < 0) {
        // błąd fork()
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // ===== PROCES WORKER =====
        pid_t mypid = getpid();

        if (mypid % 3 == 0) {
            exit(0); // sukces
        } else {
            exit(1); // błąd
        }
    } else {
        // ===== PROCES WATCHDOG =====
        wait(&status);

        if (WIFEXITED(status)) {
            int code = WEXITSTATUS(status);

            if (code == 0) {
                printf("Proces %d zakonczony poprawnie\n", pid);
            } else {
                printf("Awaria procesu %d. Restart...\n", pid);
            }
        }
    }

    return 0;
}
3 uprawnienia dla c = gcc task2.c -o task2
4 uruchom + ./task2

zadanie 3
1 +  nano task3.c

2 + 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

// 1. Zmienna globalna i mutex
int balance = 1000;
pthread_mutex_t mutex;

// Funkcja wątku
void* worker(void* arg) {
    for (int i = 0; i < 50; i++) {
        // 3. Sekcja krytyczna
        pthread_mutex_lock(&mutex);
        balance -= 10;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[3];

    // Inicjalizacja mutexa
    pthread_mutex_init(&mutex, NULL);

    // 2. Utworzenie 3 wątków
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    // 4. Czekanie na wątki
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("[Rodzic] Wszystkie watki zakonczone.\n");

    // Usunięcie mutexa
    pthread_mutex_destroy(&mutex);

    // 5. fork() po join
    pid_t pid = fork();

    if (pid == 0) {
        // 6. Proces potomny
        if (balance == -500) {
            printf("[Potomek] Stan konta:%d. Bilans zgodny\n", balance);
        } else {
            printf("[Potomek] Stan konta:%d. Blad synchronizacji\n", balance);
        }
    }

    return 0;
}
3 + gcc task3.c -o task3 -pthread
4 + ./task3


 -github


1rm -rf .git
2git add task1.sh task2.c task3.c
3git status
4git commit -m "Only task1 task2 task3"
5git branch -M main
6git remote add origin https://github.com/Majkel631/example2.git
7git remote -v
8git push -u origin main

