
#include <stdio.h>
#include <stdlib.h>

typedef struct Reply{
	char *username;
	char *content;
} Reply;

Reply *createReply(char *username, char *content) {
	Reply *ret = (Reply *) malloc(sizeof(Reply));
	ret->username = username;
	ret->content = content;
	return ret;
}

int main() {
	return 0;
}
