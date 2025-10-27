#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern Post *createPost(char *username, char *caption);
extern void deleteComments(Comment *head);
extern Comment *createComment(char *username, char *content);
extern Reply *createReply(char *username, char *content);
extern void deleteReplies(Reply *head);

static Platform *platform = NULL;

Platform *createPlatform() {
    if (platform != NULL) {
        fprintf(stderr, "WARNING: Platform is already available (no more can be created)\n");
        return platform;
    }
    platform = (Platform *) malloc(sizeof(Platform));
    if (platform == NULL) {
        fprintf(stderr, "FATAL ERROR: cannot allocate memory\n");
        exit(1);
    }
    platform->posts = NULL;
    platform->lastviewed = NULL;
    return platform;
}

bool addPost(char *username, char *caption) {
    Post *post = createPost(username, caption);
    if (post == NULL) return false;
    
    platform->lastviewed = post; 

    post->next = platform->posts;
    platform->posts = post;
    return true;
}

bool deletePost(int n) {
    if (n <= 0 || platform->posts == NULL) return false;
    
    Post *cur = platform->posts;
    Post *prev = NULL;

    for (int i = 1; i < n && cur != NULL; i++) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL) {
        printf("LOG: Post out of bounds\n");
        return false;
    }

    if (prev == NULL) { 
        platform->posts = cur->next;
        if (platform->lastviewed == cur) platform->lastviewed = platform->posts;
    } else { 
        prev->next = cur->next;
        if (platform->lastviewed == cur) platform->lastviewed = NULL;
    }

    free(cur->username);
    free(cur->caption);
    deleteComments(cur->comments);
    free(cur);
    return true;
}

Post *viewPost(int n) {
    Post *cur = platform->posts;
    int i = n;
    while (--i > 0 && cur != NULL) cur = cur->next;
    
    if (cur == NULL) {
        printf("LOG: Post out of bounds\n");
        return NULL;
    }
    platform->lastviewed = cur;
    return cur;
}

Post *currPost() {
    if (platform->lastviewed == NULL) return platform->posts;
    return platform->lastviewed;
}

Post *nextPost() {
    Post *current = currPost();
    if (current == NULL) return NULL;

    if (current->next == NULL) {
        printf("Next post does not exist.\n");
        return current;
    }
    
    platform->lastviewed = current->next;
    return platform->lastviewed;
}

Post *previousPost() {
    Post *current = currPost();
    if (current == NULL) return NULL;

    if (platform->posts == current) {
        printf("Previous post does not exist.\n");
        return current;
    }
    
    Post *cur = platform->posts;
    while (cur->next != current) {
        if (cur->next == NULL) return NULL; 
        cur = cur->next;
    }
    
    platform->lastviewed = cur;
    return cur;
}

bool addComment(char *username, char *content) {
    Post *post = currPost(); 
    if (post == NULL) {
        printf("LOG: Cannot add comment. No post is being viewed.\n");
        return false;
    }

    Comment *comment = createComment(username, content);
    if (comment == NULL) return false;
    
    comment->next = post->comments; 
    post->comments = comment;
    return true;
}

bool deleteComment(int n) {
    Post *post = currPost();
    if (post == NULL || post->comments == NULL || n <= 0) return false;

    Comment *cur = post->comments;
    Comment *prev = NULL;

    for (int i = 1; i < n && cur != NULL; i++) {
        prev = cur;
        cur = cur->next;
    }
    
    if (cur == NULL) {
        printf("LOG: Comment out of bounds\n");
        return false;
    }

    if (prev == NULL) { 
        post->comments = cur->next;
    } else { 
        prev->next = cur->next;
    }

    free(cur->username);
    free(cur->content);
    deleteReplies(cur->replies);
    free(cur);

    return true;
}

Comment *viewComments() {
    Post *post = currPost();
    
    if (post == NULL) {
        printf("LOG: Cannot view comments. No post is being viewed.\n");
        return NULL;
    }
    
    Comment *original_head = post->comments;
    if (original_head == NULL) {
        printf("LOG: Post has no comments.\n");
        return NULL;
    }
    
    Comment *new_head = NULL;
    Comment *current = original_head;

    while (current != NULL) {
        Comment *new_node = (Comment *) malloc(sizeof(Comment));
        if (new_node == NULL) return NULL; 
        
        new_node->username = strdup(current->username);
        new_node->content = strdup(current->content);
        
        new_node->replies = current->replies; 
        
        new_node->next = new_head;
        new_head = new_node;
        
        current = current->next;
    }
    
    return new_head; 
}

bool addReply(char *username, char *content, int n) {
    Post *post = currPost();
    if (post == NULL || post->comments == NULL || n <= 0) return false;

    Comment *cur = post->comments;
    int i = n;
    while (--i > 0 && cur != NULL) cur = cur->next;
    
    if (cur == NULL) {
        printf("LOG: Comment out of bounds\n");
        return false;
    }

    Reply *reply = createReply(username, content);
    if (reply == NULL) return false;
    
    reply->next = cur->replies; 
    cur->replies = reply;
    return true;
}

bool deleteReply(int n, int m) {
    Post *post = currPost();
    if (post == NULL || post->comments == NULL || n <= 0 || m <= 0) return false;

    Comment *targetComment = post->comments;
    for (int i = 1; i < n && targetComment != NULL; i++) {
        targetComment = targetComment->next;
    }

    if (targetComment == NULL || targetComment->replies == NULL) {
        printf("LOG: Target comment (n) out of bounds or has no replies\n");
        return false;
    }

    Reply *curReply = targetComment->replies;
    Reply *prevReply = NULL;
    
    for (int j = 1; j < m && curReply != NULL; j++) {
        prevReply = curReply;
        curReply = curReply->next;
    }
    
    if (curReply == NULL) {
        printf("LOG: Reply (m) out of bounds\n");
        return false;
    }
    
    if (prevReply == NULL) { 
        targetComment->replies = curReply->next;
    } else { 
        prevReply->next = curReply->next;
    }

    free(curReply->username);
    free(curReply->content);
    free(curReply);
    return true;
}