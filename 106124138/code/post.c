
#include "post.h"

Post *createPost(char *username, char *caption) {
	Post *ret = (Post *) malloc(sizeof(Post));
	if (ret == NULL) {
		fprintf(stderr, "ERROR: cannot allocate memory\n");
		exit(1);
	}
	ret->username = strdup(username);
	ret->caption = strdup(caption);
	if (ret->username == NULL || ret->caption == NULL) {
		fprintf(stderr, "ERROR: cannot implement deep copy\n");
		if (ret->username) free(ret->username);
		free(ret);
		exit(1);
	}
	ret->comments = NULL;
	ret->next = NULL;
	return ret;
}
