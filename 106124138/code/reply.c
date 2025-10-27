
#include "reply.h"

Reply *createReply(char *username, char *content) {
	Reply *ret = (Reply *) malloc(sizeof(Reply));
	if (ret == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory\n");
		exit(1);
	}
	ret->username = strdup(username);
	ret->content = strdup(content);
	if (ret->username == NULL || ret->content == NULL) {
		fprintf(stderr, "ERROR: cannot implement deep copy\n");
		if (ret->username == NULL) free(ret->username);
		free(ret);
		exit(1);
	}
	return ret;
}

void deleteReplies(Reply *reply) {
	while (reply != NULL) {
		Reply *next = reply->next;
		free(reply->username);
		free(reply->content);
		free(reply);
		reply = next;
	}
}