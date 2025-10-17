#include <stdio.h>
#include <stdlib.h>

struct Node {
    int songID;
    struct Node* next;
};

// Helper function to print playlist
void printPlaylist(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->songID);
        if (temp->next != NULL) printf("->");
        temp = temp->next;
    }
    printf("\n");
}

struct Node* reversePlaylistSegment(struct Node* head, int m, int n) {
    if (!head || m >= n) return head;

    struct Node dummy;
    dummy.next = head;
    struct Node* prev = &dummy;

    for (int i = 1; i < m; i++)
        prev = prev->next;

    struct Node* curr = prev->next;
    struct Node* next;
    for (int i = 0; i < n - m; i++) {
        next = curr->next;
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    return dummy.next;
}

int main() {
    // Creating playlist: 101->102->103->104->105->106->107
    struct Node* head = malloc(sizeof(struct Node));
    struct Node* temp = head;
    int songs[] = {101,102,103,104,105,106,107};
    for (int i = 0; i < 7; i++) {
        temp->songID = songs[i];
        if (i < 6) {
            temp->next = malloc(sizeof(struct Node));
            temp = temp->next;
        } else {
            temp->next = NULL;
        }
    }

    printf("Original playlist:\n");
    printPlaylist(head);

    head = reversePlaylistSegment(head, 2, 5);

    printf("Modified playlist:\n");
    printPlaylist(head);

    return 0;
}
