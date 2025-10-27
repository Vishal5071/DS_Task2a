#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "platform.h" 
#include "post.h"     
#include "comment.h"  
#include "reply.h"    

static bool read_word(char *buffer) {
    return scanf("%s", buffer) == 1;
}

static bool read_int(int *n) {
    return scanf("%d", n) == 1;
}

static bool read_string(char *buffer) {
    return scanf("%s", buffer) == 1;
}

static void print_post_details(Post *post) {
    if (post == NULL) {
        printf("Post not found or last viewed post is NULL.\n");
        return;
    }
    printf("%s %s\n", post->username, post->caption);
}

static void print_replies(Reply *head) {
    Reply *current = head;
    while (current != NULL) {
        printf("  %s %s\n", current->username, current->content);
        current = current->next;
    }
}

static void print_all_comments() {
    Comment *head = viewComments();
    Comment *current = head;
    
    if (current == NULL) {
        printf("Comment List: Empty.\n");
        return;
    }
    
    while (current != NULL) {
        printf("%s %s\n", current->username, current->content);
        if (current->replies != NULL) {
            print_replies(current->replies);
        }
        current = current->next;
    }
}

static void help() {
    printf("Available commands:\t\ncreate_platform, add post, delete post, view_post, current_post, next_post, previous_post,\t\nadd comment, delete comment, view_comments,\t\nadd reply, delete reply,\t\nhelp, exit\n\n");
}

int main() {
    char cmd[50], sub_cmd[50];
    char arg1[100], arg2[100];
    int n, m;

    printf("List of all ");
    help();
    printf("For any help: use the 'help' command\n");

    createPlatform();

    while (1) {
        printf("\n>> ");

        if (!read_word(cmd)) break;
        
        if (strcmp(cmd, "create_platform") == 0) {
            createPlatform(); 
        } 
        else if (strcmp(cmd, "add") == 0 && read_word(sub_cmd)) { 
            if (strcmp(sub_cmd, "post") == 0 && read_string(arg1) && read_string(arg2)) {
                addPost(arg1, arg2);
            } else if (strcmp(sub_cmd, "comment") == 0 && read_string(arg1) && read_string(arg2)) { 
                addComment(arg1, arg2);
            } else if (strcmp(sub_cmd, "reply") == 0 && read_string(arg1) && read_string(arg2) && read_int(&n)) { 
                addReply(arg1, arg2, n);
            } else { fprintf(stderr, "Unknown command.\n"); }
        }
        else if (strcmp(cmd, "delete") == 0 && read_word(sub_cmd)) { 
            if (strcmp(sub_cmd, "post") == 0 && read_int(&n)) {
                deletePost(n);
            } else if (strcmp(sub_cmd, "comment") == 0 && read_int(&n)) {
                deleteComment(n);
            } else if (strcmp(sub_cmd, "reply") == 0 && read_int(&n) && read_int(&m)) {
                deleteReply(n, m);
            } else { fprintf(stderr, "Unknown command.\n"); }
        }
        else if (strcmp(cmd, "view_post") == 0 && read_int(&n)) {
            print_post_details(viewPost(n));
        } else if (strcmp(cmd, "current_post") == 0) {
            print_post_details(currPost());
        } else if (strcmp(cmd, "next_post") == 0) {
            print_post_details(nextPost());
        } else if (strcmp(cmd, "previous_post") == 0) {
            print_post_details(previousPost());
        } else if (strcmp(cmd, "view_comments") == 0 || strcmp(cmd, "view_all_comments") == 0) {
            print_all_comments();
        } else if (strcmp(cmd, "help") == 0) {
            help();
        } else if (strcmp(cmd, "exit") == 0) {
            break;
        } else {
            fprintf(stderr, "Unknown command.\n");
        }
    }

    return 0;
}