
#include <stdio.h>
#include <stdlib.h>

typedef struct Post{
	char *username;
	char *caption;
	char **comments;
} Post;

typedef struct PostNode{
	Post *post;
	struct PostNode *next;
} PostNode;

Post *createPost(char *username, char *caption) {
	Post *ret = (Post *) malloc(sizeof(Post));
	ret->username = username;
	ret->caption = caption;
	ret->comments = NULL;
	return ret;
}
