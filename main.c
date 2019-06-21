#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE #
#define TAM 256
#define ESQUERDA 0
#define DIREITA 1

int count = 0;

typedef unsigned char byte;

typedef struct nodeArvore
{
    int frequencia;
    char code;
    byte c;
    struct nodeArvore *esquerda;
    struct nodeArvore *direita;
} nodeArvore;

typedef struct nodeLista
{
    nodeArvore *n;
    struct nodeLista *proximo;
} nodeLista;

typedef struct lista
{
    nodeLista *head;
    int elementos;
} lista;

nodeLista *novoNodeLista(nodeArvore *nArv)
{

    nodeLista *novo;
    if ((novo = malloc(sizeof(*novo))) == NULL)
        return NULL;

    novo->n = nArv;

    novo->proximo = NULL;

    return novo;
}

nodeArvore *novoNodeArvore(byte c, int frequencia, nodeArvore *esquerda, nodeArvore *direita)
{

    nodeArvore *novo;

    if ((novo = malloc(sizeof(*novo))) == NULL)
        return NULL;

    novo->c = c;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}

void insereLista(nodeLista *n, lista *l)
{

    if (!l->head)
    {
        l->head = n;
    }

    else if (n->n->frequencia < l->head->n->frequencia)
    {
        n->proximo = l->head;
        l->head = n;
    }
    else
    {

        nodeLista *aux = l->head->proximo;

        nodeLista *aux2 = l->head;

        while (aux && aux->n->frequencia <= n->n->frequencia)
        {
            aux2 = aux;
            aux = aux2->proximo;
        }

        aux2->proximo = n;
        n->proximo = aux;
    }

    l->elementos++;
}

nodeArvore *popMinLista(lista *l)
{

    nodeLista *aux = l->head;

    nodeArvore *aux2 = aux->n;

    l->head = aux->proximo;

    free(aux);
    aux = NULL;

    l->elementos--;

    return aux2;
}

nodeArvore *BuildHuffmanTree(int *listaBytes)
{

    lista l = {NULL, 0};

    for (int i = 0; i < 256; i++)
    {
        if (listaBytes[i])
        {
            printf("Caracterer e sua frequecia => [%c:%d]\n", i, listaBytes[i]);

            insereLista(novoNodeLista(novoNodeArvore(i, listaBytes[i], NULL, NULL)), &l);
        }
    }

    while (l.elementos > 1)
    {

        nodeArvore *nodeEsquerdo = popMinLista(&l);
        printf("\n");
        printf("first Pop na lista com este elemento: %c, freq: %d", nodeEsquerdo->c, nodeEsquerdo->frequencia);

        nodeArvore *nodeDireito = popMinLista(&l);
        printf("\n");
        printf("SECOND Pop na lista com este elemento: %c, freq: %d", nodeDireito->c, nodeDireito->frequencia);

        nodeArvore *soma = novoNodeArvore('#', nodeEsquerdo->frequencia + nodeDireito->frequencia, nodeEsquerdo, nodeDireito);
        printf("\n");
        printf("\ninserindo a soma das freqs na lista: %d", soma->frequencia);
        printf("\n");

        insereLista(novoNodeLista(soma), &l);
    }
    return popMinLista(&l);
}

void FreeHuffmanTree(nodeArvore *n)
{
    if (!n)
        return;
    else
    {
        nodeArvore *esquerda = n->esquerda;
        nodeArvore *direita = n->direita;
        free(n);
        FreeHuffmanTree(esquerda);
        FreeHuffmanTree(direita);
    }
}

void completaCodigo(nodeArvore *n, char c[])
{
    char l[9], r[9];
    strcpy(l, c);
    strcat(l, '0');
    strcpy(r, c);
    strcat(r, '1');

    if (n != NULL)
    {
        if (n->esquerda == NULL && n->direita == NULL)
        {
            strcat(n->code, c);
        }
        else
        {
            completaCodigo(n->esquerda, l);
            completaCodigo(n->direita, r);
        }
    }
}

void exibirEmOrdem(nodeArvore *pRaiz){
    if(pRaiz != NULL){
        exibirEmOrdem(pRaiz->esquerda);
        printf("\nCaractere: %c\n", pRaiz->c);
        exibirEmOrdem(pRaiz->direita);
    }
}

int main()
{
    // Init
    int stage[256] = {0};
    int arraysz = 0;

    FILE *file = fopen("exemplo.txt", "r");

    if (file == NULL)
    {
        printf("Could not open the specified file!\n");
        exit(EXIT_FAILURE);
    }

    for (char c; (((c = fgetc(file)) != '\n') && (c != EOF));)
    {
        if (stage[c] == 0)
        {
            arraysz += 1;
        }
        stage[c] += 1;
    }

    nodeArvore *raiz = BuildHuffmanTree(stage);
    printf("\n");
    printf("\nRaiz com essa frequencia: %d", raiz->frequencia);
    printf("\n");
    char vazio[50];
    completaCodigo(raiz, vazio);
    //exibirEmOrdem(raiz);

}
