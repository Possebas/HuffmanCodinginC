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
    //char *code;
    //int type;
    struct node *next;
    struct node *left;
    struct node *right;
} node;

node *HEAD = NULL;
node *ROOT = NULL;

// node *newNode(char c, int freq)
// {
//     node *q;
//     q = (node *)malloc(sizeof(node));
//     q->caract = c;
//     //q->type = LEAF; //leafnode
//     q->freq = freq;
//     q->next = NULL;
//     q->left = NULL;
//     q->right = NULL;
//     return q;
// }

void insert_at_begin(int freq, char x)
{
    struct node *t;

    t = (struct node *)malloc(sizeof(struct node));
    count++;

    if (HEAD == NULL)
    {
        HEAD = t;
        HEAD->caract = x;
        HEAD->freq = freq;
        HEAD->next = NULL;
        return;
    }

    t->caract = x;
    t->freq = freq;
    t->next = HEAD;
    HEAD = t;
}

void imprime(node *le)
{
    if (le != NULL)
    {
        printf(" [%c, %d]   ", le->caract, le->freq);
        imprime(le->next);
    }
}

// void busca_e_remove(char y, celula *le)
// {
//     celula *p, *q;
//     p = le;
//     q = le->prox;
//     while (q != NULL && q->caract != y)
//     {
//         p = q;
//         q = q->prox;
//     }
//     if (q != NULL)
//     {
//         p->prox = q->prox;
//         free(q);
//     }
// }

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
    printf("\n");
    imprime(HEAD);
    printf("\n");

    //printf("\nHello world!\n");
    return 0;
}
