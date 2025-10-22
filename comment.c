
#include <stdio.h>
#include <stdlib.h>

typedef struct Comment{
	char *username;
	char *content;
	char **replies;
} Comment;

Comment *createComment(char *username, char *content) {
	Comment *ret = (Comment *) malloc(sizeof(Comment));
	ret->username = username;
	ret->content = content;
	ret->replies = NULL;
	return ret;
}

int main() {
	return 0;
}
