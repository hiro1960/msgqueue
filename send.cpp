#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {
    int id = 50;
    key_t key = ftok(".", id); // キーの生成
    int msqid = msgget(key, IPC_CREAT | 0666); // メッセージキューの作成

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

    sleep(10);

    msgctl(msqid, IPC_RMID, NULL); // メッセージキューの削除

    return 0;
}