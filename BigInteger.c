#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

struct BigInteger initialize(char *s) {
    struct BigInteger temp;
    temp.head = NULL;
    temp.size = 0;
    int value=0;
   for(int i=0; s[i]!='\0'; i++)
   { 
        if (s[i] >= '0' && s[i] <= '9') {
            value = s[i] - '0';
            struct node *temp_1 = (struct node*)malloc(sizeof(struct node));
            if (temp_1 == NULL) {
                printf("Memory allocation failed\n");
                exit(1);
            }
            temp_1->data = value;
            temp_1->next = temp.head;
            temp.head = temp_1;
            temp.size++;
        } else {
            printf("INVALID INPUT\n");
            exit(1);
        }
    }
    
    return temp;
}

void insertnode(struct node **head, int data) 
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (!new_node) 
    {
        printf("---memory not allocated---\n");
        return;   
    }
    new_node->data = data;
    new_node->next = (*head);
    (*head) = new_node;
}

int compare(struct BigInteger *n1,struct BigInteger *n2)
{

    if(n2->size > n1->size)
    {
        return 1;
    }
    else if(n2->size==n1->size)
    {
        int val=0;
        n1->head= reverse(n1->head);
        n2->head= reverse(n2->head);

        struct node *node1=n1->head, *node2=n2->head;
        while(node1!=NULL && node2!=NULL)
        {
            if(node1->data < node2->data)
            {
                val= 0;
                break;
            }

            else if(node2->data > node1->data)
            {
                val= 1;
                break;
            }
            
            node1=node1->next;
            node2=node2->next;
        }
        n1->head= reverse(n1->head);
        n2->head= reverse(n2->head);
        return val;
    }
    return 0;
}

struct node* reverse(struct node *head)
{
    struct node *next=NULL, *prev=NULL, *itr=head;
    while(itr!=NULL)
    {
        next=itr->next;
        itr->next=prev;
        prev=itr;
        itr=next;
    }
    return prev;
}

struct BigInteger add(struct BigInteger a,struct BigInteger b)
{
    if(!a.head)
    {
        return b;
    }
    if(!b.head)
    {
        return a;
    }

    struct BigInteger result;
    result.head=NULL;
    result.size=0;

    int carry=0;
    struct node *node_a=a.head,*node_b=b.head;
    while(node_a!=NULL || node_b!=NULL || carry!=0)
    {
        int sum=carry;
        if(node_a!=NULL)
        {
            sum+=node_a->data;
            node_a=node_a->next;
        }
        if(node_b!=NULL)
        {
            sum+=node_b->data;
            node_b=node_b->next;
        }

        carry=sum/10;
        sum=sum%10;

        struct node *temp_node=(struct node*)malloc(sizeof(struct node));
        temp_node->data=sum;
        temp_node->next=result.head;
        result.head=temp_node;
        result.size++;
    }
    return result;
}

struct BigInteger sub(struct BigInteger a,struct BigInteger b)
{
    struct BigInteger result;
    result.head = NULL;
    result.size = 0;
    int brw=0;
    int f=0;
    if(compare(&a,&b))
    {
        f=1;
        struct BigInteger temp=a;
        a=b;
        b=temp;
    }
    struct node *node_a=a.head,*node_b=b.head;
    int numa=0, numb=0;
    while(node_a || node_b)
    {
        if(node_a!=NULL)
        {
            numa=node_a->data;
        }
        else
        {
            numa=0;
        }

        if(node_b!=NULL)
        {
            numb=node_b->data;
        }
        else
        {
            numb=0;
        }

        int diff= numa - numb - brw;
        if(diff<0)
        {
            diff+=10;
            brw=1;
        }
        else
            brw=0;
        struct node *temp_node=(struct node*)malloc(sizeof(struct node));
        if(!temp_node)
        {
            printf("Memory Allocation Failed!!!");
            exit(1);
        }
        temp_node->data=diff;
        temp_node->next=result.head;
        result.head=temp_node;
        result.size++;

        if(node_a!=NULL)
        { 
            node_a=node_a->next;
        }
        if(node_b) 
        {
            node_b=node_b->next;
        }
    }
    if(f)
    {
        struct node *itr=result.head;
        itr->data=(-1)*(itr->data);
    }
    return result;
}


struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{

    struct BigInteger result;
    result.head=NULL;
    result.size=0;
    struct node *node_b=b.head;
    int cry=0,product=0;
    int i=0;
    while(node_b!=NULL)
    {
        struct node *node_a=a.head;
        struct BigInteger ptr;
        ptr.head=NULL;
        ptr.size=0;
        cry=0;
        for(int j=0;j<i;j++)
        {
            insertnode(&ptr.head,0);
            ptr.size++;
        }
        while(node_a!=NULL)
        {
            product=((node_a->data)*(node_b->data))+cry;
            cry=product/10;
            insertnode(&ptr.head, product%10 );
            node_a=node_a->next;
            ptr.size++;
        }
        if(cry>0)
        {
            insertnode(&ptr.head,cry);
            ptr.size++;
        }
        i++;
        ptr.head = reverse(ptr.head);
        if (i <= 2 || result.head == NULL) {
            result = add(result, ptr);
        }
        else {
            result.head = reverse(result.head);
            result = add(result, ptr);
        }
        node_b=node_b->next;
    }
    return result;
}

/*
struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger newStruct;
    newStruct.head = NULL;
    newStruct.size = 0;

    long long int quotient = 0, n1 = 0, n2 = 0;

    a.head = reverse(a.head);
    b.head = reverse(b.head);

    struct node* i1 = a.head;
    while (i1 != NULL) {
        n1 = n1 * 10 + i1->data;
        i1 = i1->next;
    }

    struct node* i2 = b.head;
    while (i2 != NULL) {
        n2 = n2 * 10 + i2->data;
        i2 = i2->next;
    }

    a.head = reverse(a.head);
    b.head = reverse(b.head);


    struct node* i3 = newStruct.head;
    struct node* i4 = NULL;
    struct node* i5 = NULL;

    while (compare(&a, &b) != -1) {
        while (compare(&a, &b) != -1) {
            a = sub(a, b);
            quotient++;
        }
        insertnode(&i3, quotient);
        quotient = 0;
        insertnode(&i4, 0);

        insertnode(&i5, 0);
    }

    struct node *temp = newStruct.head;
    while (temp != NULL) {
        newStruct.size++;
        temp = temp->next;
    }

    return newStruct;
}

*/

void display(struct BigInteger a)
{
    struct node *temp=a.head;
    while(temp!=NULL)
    {
        printf("%d",temp->data);
        temp=temp->next;
    }
}
/*
void free_num(struct BigInteger num)
{
    struct node *temp;
    while(num.head)
    {
        temp=num.head;
        num.head=num.head->next;
        free(temp);
    }
}
*/
