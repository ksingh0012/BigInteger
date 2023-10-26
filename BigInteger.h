#ifndef BigInteger_h
#define BigInteger_h

#include<stdio.h>
#include<stdlib.h>

struct BigInteger {
    struct node* head;
    int size;
};

struct node {
    int data;
    struct node *next;
};

struct BigInteger initialize(char *s);
struct node* reverse(struct node*head);
void insertnode(struct node **head, int val);
int compare(struct BigInteger *a, struct BigInteger *b);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
//struct BigInteger div1(struct BigInteger a, struct BigInteger b);
void display(struct BigInteger a);
// void free_num(struct BigInteger num);

#endif