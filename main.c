#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INTERNAL 1
#define LEAF 0
#define SPACE #

int count = 0;

typedef struct node
{
    char caract;
    int freq;
    int code;
    int ch;
    struct node *next;
    struct node *left;
    struct node *right;
} node;

node *HEAD = NULL;
node *ROOT = NULL;

void insert_at_begin(int freq, char x)
{
    node *t;

    t = (node *)malloc(sizeof(node));
    count++;

    if (HEAD == NULL && ROOT == NULL)
    {
        HEAD = t;
        HEAD->caract = x;
        HEAD->freq = freq;
        //HEAD->type = LEAF;
        HEAD->next = NULL;
        HEAD->right = NULL;
        HEAD->left = NULL;
        return;
    }

    t->caract = x;
    t->freq = freq;
    //t->type = LEAF;
    t->right = NULL;
    t->left = NULL;
    t->next = HEAD;
    HEAD = t;
}

int delete_from_begin()
{
    node *t;
    char n;
    int numFreq = 0;

    if (HEAD == NULL)
    {
        printf("Linked list is already empty.\n");
        return;
    }

    n = HEAD->caract;
    numFreq = HEAD->freq;
    t = HEAD->next;
    free(HEAD);
    HEAD = t;
    count--;
    //printf("\n Par [%c,%d] deleted from beginning successfully.\n",numFreq);
    return numFreq;
}


// void treeH(node *head)
// {
//     node *p, *q, *newNode;
//     newNode = malloc(sizeof(node));
//     newNode->left = head->next;
//     newNode->right = head->next->next;
//     head->next = newNode->right->next;
//     newNode->left->next = NULL;
//     newNode->right->next = NULL;
//     newNode->ch = 35;
//     strcpy(newNode->code, "");
//     newNode->freq = (newNode->left->freq) + (newNode->right->freq);

//     p = head;
//     q = head->next;
//     while (q != NULL && q->freq <= newNode->freq)
//     {
//         p = q;
//         q = q->next;
//     }
//     newNode->next = q;
//     p->next = newNode;
// }

void imprime(node *le)
{
    if (le != NULL)
    {
        printf(" [%c, %d]   ", le->caract, le->freq);
        imprime(le->next);
    }
}



int main()
{
    char entrada[] = "aaaaabbbbcccdde";
    int *numberChars = calloc(256, sizeof numberChars);

    printf("Caracteres da mensagem em decimal:\n");
    for (int i = 0; i < strlen(entrada); i++)
    {
        printf(" [%d] ", entrada[i]);
        numberChars[entrada[i]] += 1;
    }
    //printf("\n\nVezes que cada caractere apareceu:\n");
    /*
    for(int i=0; i<255; i++){
        if(numberChars[i] > 0){
        printf(" [%d] ", numberChars[i]);
        }
    }
    */
    printf("\n\n");
    printf("Caractere em ASCII          Quantidade");
    for (int i = 0; i < 256; i++)
    {
        if (numberChars[i] > 0)
        {
            printf("\n%c                              %d\n", i, numberChars[i]);
            insert_at_begin(numberChars[i], i);
        }
    }

    printf("\n\n");
    imprime(HEAD);
    printf("\n\n");
    //treeH(HEAD);
    printf("\n\n");
    //printf("Nodo removido foi: [%c,%d]", desk.caract, desk.freq);
    printf("\n");
    //printf("\nHello world!\n");
    return 0;
}
