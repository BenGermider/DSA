//
// Created by Ben on 5/31/2024.
//

#ifndef DSA_NODE_H
#define DSA_NODE_H

typedef struct Node Node;

struct Node {
    int data;
    Node *prev;
    Node *next;
};

Node* createNode(int data);

#endif //DSA_NODE_H
