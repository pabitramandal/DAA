#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *start = NULL, *front, *back;

void append();
void display();
void search();

int main() {
    int n, choice;
    printf("\nEnter the number of elements in the list: ");
    scanf("%d", &n);
    printf("\nEnter the elements :\n");
    for (int i = n; i > 0; i--) {
        append();
    }
    display();
    front = start;
    back = NULL;
    do {
        printf("\nEnter <1> to search and <0> to stop: ");
        scanf("%d", &choice);
        if (1 == choice) {
            search();
        }
    } while (choice);
    printf("\n***** Thank You *****\n");
    return 0;
}

void append() {
    Node *temp = (Node *) malloc(sizeof(Node));
    scanf("%d", &temp->data);
    Node *curr;
    if (!start || start->data >= temp->data) {
        temp->next = start;
        start = temp;
    } else {
        curr = start;
        while (curr->next && curr->next->data < temp->data) {
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
    }
    temp = NULL;
    free(temp);
}

void display() {
    Node *curr = start;
    while (curr) {
        printf("|%d|-->", curr->data);
        curr = curr->next;
    }
    printf("|NULL|\n");
    curr = NULL;
    free(curr);
}

void search() {
    int key, count = 0;
    printf("\nEnter the element you want to search: ");
    scanf("%d", &key);
    Node *temp;
    while (front && key >= front->data) {
        if (key == front->data) {
            printf("\nFOUND %d\n", key);
            printf("\nThe number of forward move(s) : %d\n", count);
            return;
        }
        temp = front;
        front = front->next;
        temp->next = back;
        back = temp;
        count++;
    }
    while (back && key <= back->data) {
        if (key == back->data) {
            printf("\nFOUND %d\n", key);
            printf("\nThe number of backward move(s) : %d\n", count);
            return;
        }
        temp = back;
        back = back->next;
        temp->next = front;
        front = temp;
        count++;
    }
    printf("\nNOT FOUND %d\n", key);
    printf("\nThe number of move(s) : %d\n", count);
    temp = NULL;
    free(temp);
}
