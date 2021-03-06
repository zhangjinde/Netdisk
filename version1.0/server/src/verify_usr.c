/*******************************************************************************
    > File Name: verify_usr.c
    > Author: fengfuyuyang
    > Mail: fengfuyuyang@outlook.com
    > Created Date: 2020-08-21
 ******************************************************************************/

#include "../include/factory.h"

void get_salt(char* salt, char* passwd) {
    int i, j;
    for (i = 0, j = 0; passwd[i] && j != 3; ++i) {
        if ('$' == passwd[i]) {
            ++j;
        } 
    }
    strncpy(salt, passwd, i - 1);
}

int verify_usr(int newFd, char* usrname) {
    train_t train;
    int dataLen;
    recvCycle(newFd, &dataLen, 4);
    recvCycle(newFd, usrname, dataLen);

    struct spwd *sp;
    char salt[512] = {0};

    if (NULL == (sp = getspnam(usrname))) {
        strcpy(train.buf, "usrname error");
        train.dataLen = strlen(train.buf);
        send(newFd, &train, train.dataLen + 4, 0);
        return -1;
    } else {
        endFlag(newFd);
    }
    get_salt(salt, sp->sp_pwdp);

    train.dataLen = strlen(salt);
    strcpy(train.buf, salt);
    send(newFd, &train, 4 + train.dataLen, 0);

    char passwd[512] = {0};

    recvCycle(newFd, &dataLen, 4);
    recvCycle(newFd, passwd, dataLen);

    if (0 == strcmp(sp->sp_pwdp, passwd)) {
        endFlag(newFd);
        return 0;
    } else {
        strcpy(train.buf, "password error!");
        train.dataLen = strlen(train.buf);
        send(newFd, &train, train.dataLen + 4, 0);
        return -1;
    }
}

