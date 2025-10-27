
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "post.h"
#include "comment.h"
#include "reply.h"

typedef struct Platform{
	struct Post *posts;
	struct Post *lastviewed;
} Platform;

Platform *createPlatform();
bool addPost(char *username, char *caption);
bool deletePost(int n);
Post *viewPost(int n);
Post *currPost();
Post *nextPost();
Post *previousPost();
bool addComment(char *username, char *content);
bool deleteComment(int n);
Comment *viewComments();
bool addReply(char *username, char *content, int n);
bool deleteReply(int n, int m);

#endif