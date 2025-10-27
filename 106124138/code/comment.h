
#ifndef COMMENT_H
#define COMMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reply.h"

typedef struct Comment{
	char *username;
	char *content;
	Reply *replies;
	struct Comment *next;
} Comment;

Comment *createComment(char *username, char *content);
void deleteComments(Comment *comment);

#endif