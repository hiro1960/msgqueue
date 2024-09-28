#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int id = 50;
    key_t key = ftok(".", id); // キーの生成
    int msqid = msgget(key, 0666);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msgbuf  buf;
    buf.mtype = 2;
    // strcpy(buf.mtext, "Hello, world!");

    if (msgsnd(msqid, &buf, sizeof(buf.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    return 0;
}