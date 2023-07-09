#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} Node;

Node *rotateL(Node *t);
Node *rotateLR(Node *t);
Node *rotateR(Node *t);
Node *rotateRL(Node *t);
Node *insert(int x, Node *t);
int max(int a, int b);
int height(Node *node);
void preOrder(Node *p);
void inOrder(Node *p);
void postOrder(Node *p);

int main() {
    Node *root = NULL;
    int x, prompt;
    do {
        printf("\nEnter <1> to add new node and <0> to stop : ");
        scanf("%d", &prompt);
        if (1 == prompt) {
            printf("\nEnter the value of the element : ");
            scanf("%d", &x);
            root = insert(x, root);
            printf("\nPre-order Traversal : ");
            preOrder(root);
            printf("\n\nIn-order Traversal : ");
            inOrder(root);
            printf("\n\nPost-order Traversal : ");
            postOrder(root);
            printf("\n");
        }
    } while (prompt);
}

void preOrder(Node *p) {
    if (p) {
        printf("|%d (%d)|-->",p->data, p->height);
        preOrder(p->left);
        preOrder(p->right);
    }
}

void inOrder(Node *p) {
    if (p) {
        inOrder(p->left);
        printf("|%d (%d)|-->", p->data, p->height);
        inOrder(p->right);
    }
}

void postOrder(Node *p) {
    if (p) {
        postOrder(p->left);
        postOrder(p->right);
        printf("|%d (%d)|-->", p->data, p->height);
    }
}

int max(int a, int b) {
    if (a > b) 
        return a;
    else
        return b;
}

int height(Node *node)
{
    if (node)
        return node->height;
    else
        return 0;
}

Node *rotateL(Node *t) {
    Node *s = t->right;
    t->right = s->left;
    s->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    s->height = max(height(s->left), height(s->right)) + 1;
    return s;
}

Node *rotateR(Node *t) {
    Node *s = t->left;
    t->left = s->right;
    s->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    s->height = max(height(s->left), height(s->right)) + 1;
    return s;
}

Node *rotateLR(Node *t) {
    t->left = rotateL(t->left);
    return rotateR(t);
}

Node *rotateRL(Node *t) {
    t->right = rotateR(t->right);
    return rotateL(t);
}

Node *insert(int x, Node *t) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    if (!t)
        return temp;
    else if (x < t->data) {
        t->left = insert(x, t->left);
        if (2 == height(t->left) - height(t->right)) {
            if (x < t->left->data)
                t = rotateR(t);
            else
                t = rotateLR(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    else if (x > t->data) {
        t->right = insert(x, t->right);
        if (-2 == height(t->left) - height(t->right)) {
            if (x > t->right->data)
                t = rotateL(t);
            else
                t = rotateRL(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    else {
        printf("\nError (Duplicate insertion not allowed)!!!\n");
        return t;
    }
    return t;
}
