#include <stdlib.h>
#include <stdio.h>
struct node { int data; struct node *next, *prev; };



void FuncA(struct node **start, int value) {
    if (!*start) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = value;
        new_node->next = new_node->prev = new_node;
        *start = new_node;
        return;
    }
    struct node *last = (*start)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *start;
    (*start)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;
}

void FuncB(struct node **start, int value) {
    struct node *last = (*start)->prev;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = *start;
    new_node->prev = last;
    last->next = (*start)->prev = new_node;
    *start = new_node;
}

void FuncC(struct node **start, int value1, int value2) {
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value1;
    struct node *temp = *start;
    while (temp->data != value2)
        temp = temp->next;
    struct node *next = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = next;
    next->prev = new_node;
}

void display(struct node *start, int *count) {
    struct node *temp = start;
    printf("Traversal in forward direction \n");
    for (; temp->next != start; temp = temp->next)
    {
	    printf("%d ", temp->data);
        (*count)++;
    }
    printf("%d ", temp->data);
    (*count)++;
    printf("\nTraversal in reverse direction \n");
    struct node *last = start->prev;
    for (temp = last; temp->prev != last; temp = temp->prev)
	    printf("%d ", temp->data);
    printf("%d ", temp->data);
    printf("\n");
}

struct node* MergeSort(struct node **start, int low, int high){
    
    struct node *p , *q, *now, *head, *temp, *p_start, *q_start;
    now = *start;
    head = NULL;
    if(low > high)
    {
        return NULL;
    }
    else if(low == high)
    {
       for(;low>1;low--)
           now = now->next;
       FuncA(&head, now->data);
       return head;
    }
    else
    {
        p = p_start = MergeSort(start,low, (low+high)/2);
        q = q_start = MergeSort(start,(low+high)/2+1, high);
        while(p->next != p_start && q->next != q_start) //until one is at the last.
        {
 
            if(p->data <= q->data)
            {
                FuncA(&head, p->data); p = p->next;
            }
            else
            {
                FuncA(&head, q->data); q = q->next;
            }
            

        }
        

        if(p->next == p_start) //if p is at the last.
        {
            for(; q->next != q_start; q = q->next) //add all the left node in q except the last one.
            {
                if(p->data <= q->data) //check if the last of p is smaller than q.
                {
                    FuncA(&head, p->data);
                    p = NULL;
                }
                FuncA(&head, q->data);
            }
            if(p != NULL && p->data <= q->data) //check if the last of p is still exist.
            {
                //if the last of p is smaller than the last of q.
                FuncA(&head, p->data);
                FuncA(&head, q->data);
            }
            else if(p != NULL && p->data > q->data)
            {
                FuncA(&head, q->data);
                FuncA(&head, p->data);
            }
            else //the last of p is not exist.
            {
                FuncA(&head, q->data);
            }
        }
        else
        {
            for(; p->next != p_start; p = p->next)
            {   
                if(q->data <= p->data)
                {
                    FuncA(&head, q->data);
                    q = NULL;
                }
                FuncA(&head, p->data);
            }
            if(q != NULL && q->data <= p->data)
            {
                FuncA(&head, q->data);
                FuncA(&head, p->data);
            }
            else if(q != NULL && q->data > p->data)
            {
                FuncA(&head, p->data);
                FuncA(&head, q->data);
            }
            else
            {
                FuncA(&head, p->data);
            }
        }
        return head;

    }
    
}
int main() {
    int count = 0;
    struct node *start = NULL;
    struct node *temp = NULL;
    FuncA(&start, 51); 
    FuncB(&start, 48);
    FuncA(&start, 72);
    FuncA(&start, 86);
    FuncA(&start, 77);
    FuncC(&start, 63, 51); 
    FuncB(&start, 100);
    FuncC(&start, 200, 72); 
    FuncA(&start, 51); 
    display(start, &count);
    temp = start;
    start = MergeSort(&start, 1, count);
    free(temp);
    display(start, &count);
    return 0;
}
