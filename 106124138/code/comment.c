
#include "comment.h"

Comment *createComment(char *username, char *content) {
	Comment *ret = (Comment *) malloc(sizeof(Comment));
	if (ret == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory\n");
		exit(1);
	}

	ret->username = strdup(username);
	ret->content = strdup(content);
	if (ret->username == NULL || ret->content == NULL) {
		fprintf(stderr, "ERROR: cannot implement deep copy\n");
		if (ret->username != NULL) free(ret->username);
		free(ret);
		exit(1);
	}

	ret->replies = NULL;
	ret->next = NULL;

	return ret;
}

void deleteComments(Comment *comment) {
	while (comment != NULL) {
		Comment *next = comment->next;
		free(comment->username);
		free(comment->content);
		deleteReplies(comment->replies);
		free(comment);
		comment = next;
	}
}