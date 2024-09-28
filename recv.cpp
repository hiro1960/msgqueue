#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MSG_MAX 1

int main() {
    int id = 50;
    key_t key = ftok(".", id);
    int msqid = msgget(key, IPC_CREAT | 0666); // メッセージキューの作成

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msgbuf  buf;
    if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Received: %d\n", static_cast<int>(buf.mtype));

    sleep(10);

    msgctl(msqid, IPC_RMID, NULL); // メッセージキューの削除

    return 0;
}