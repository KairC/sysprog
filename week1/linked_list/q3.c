#include <stdio.h>
#include <stdlib.h>

typedef struct __list {
    int data;
    struct __list *next;
}list;

void FuncA(list **start, int value){
    list *new_node = malloc(sizeof*new_node);
    new_node->data = value;
    new_node->next = (*start);
    (*start) = new_node;
}

list *sort(list *start) {   //把一個list的head跟剩下的list切開分左右兩邊, 兩邊各自做sort.
    if (!start || !start->next) //list只有一個node或是根本沒有node
        return start;
    list *left = start;
    list *right = left->next;
    //LL0;
    left->next = NULL;      //把list的head切開

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right; ) {   //終止條件：left跟right都指到NULL時
        if (!right || (left && left->data < right->data)) { //1.right沒有node(則left必有node)  2.right還有node + left還有node且left<right
            if (!merge) {
                //LL1;
                start = merge = left;   //以left的第一個node建立一list, 用來存放已排序好的node, start指在list head, merge指在list tail.
            } else {
                //LL2;
                merge->next = left;     //由於left<right, 取出left的node加在merge的next, 作為新的tail
                merge = merge->next;    //merge指向下一個, 也就是指向新的tail
            }
            //LL3;
            left = left->next;  //因為left指向的node已加入排序好的list, 因此left指向下一個node
        } else {            //1.right還有node + left還有node且left >= right 2.right還有node + left沒有node
            if (!merge) {
                //LL4;
                start = merge = right;  //以right的第一個node建立一list, 用來存放已排序好的node, start指在list head, merge指在list tail.
            } else {
                //LL5;
                merge->next = right;    //由於left >= right, 取出right的node加在merge的next, 作為新的tail
                merge = merge->next;    //merge指向下一個, 也就是指向新的tail
            }
            //LL6;
            right = right->next;        //merge指向下一個, 也就是指向新的tail
        }
    }
    return start;
}

int main(){
    list *a = malloc(sizeof*a);
    a->data = 10;
    a->next = NULL;
    list *start = a;
    FuncA(&start, 20);
    FuncA(&start, 50);
    FuncA(&start, 5);
    start = sort(start);
    for(;start!=NULL;start = start->next)
        printf("%d ",start->data);
    printf("\n");
    return 0;
    
}
