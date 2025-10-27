
#ifndef REPLY_H
#define REPLY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Reply{
	char *username;
	char *content;
    struct Reply *next;
} Reply;

Reply *createReply(char *username, char *content);
void deleteReplies(Reply *reply);

#endif