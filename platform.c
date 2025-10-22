
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "post.c"

typedef struct Platform{
	struct PostNode *posts;
	struct Post *lastviewed;	//
} Platform;

Platform *platform;

Platform *createPlatform() {
	Platform *ret = (Platform *) malloc(sizeof(Platform));
	return ret;
}

bool addPost(char *username, char *caption) {
	Post *post = createPost(username, caption);
	PostNode *node = (PostNode *) malloc(sizeof(PostNode));
	node->post = post;
	node->next = platform->posts;
	platform->posts = node;
	if (post == NULL) return false;
	return true;
}

bool deletePost(int n) {
	// delete nth recent post
	// remove any comments or replys
	return true;
}

Post *viewPost(int n) {
	// return the nth recent post
	return NULL;
}

Post *currPost() {
	
}

int main() {
	platform = createPlatform();
	if (addPost("a", "blah blah\n")) printf("uhh?");
	if (addPost("a", "bluh bluh\n")) printf("uhh?");
	PostNode* node = platform->posts;
	while (node != NULL) {
		printf("%s", node->post->caption);
		node = node->next;
	}
	return 0;
}
