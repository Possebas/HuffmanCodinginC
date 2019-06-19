#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Definição do tipo de dados 'caract'
* 'unsigned char': É o tipo que consegue gravar no intervalo que vai de 0 a 255 bytes
*/
typedef unsigned char caract;

/** Definição da árvore */
typedef struct nodeArvore
{
    int frequencia;
    caract c;
    struct nodeArvore *esquerda;
    struct nodeArvore *direita;
} nodeArvore;

/** Definição da fila de prioridade (implementada como lista simplesmente encadeada) */
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

/**
* A função strdup é dependente de implementação nas plataformas não POSIX (Windows, etc)
* Segue uma implementação desta função como solução para o problema.
*/

char *strdup(const char *s)
{
    char *p = malloc(strlen(s) + 1);
    if (p)
        strcpy(p, s);
    return p;
}

/** Função que faz alocação de memória e trata os ponteiros soltos acerca de nós da lista encadeada.
* Obs: cada nó da lista encadeada é conectado a um nó 'raiz' de árvore.
* @param: um nó de uma árvore.
*/

nodeLista *novoNodeLista(nodeArvore *nArv)
{
    // Aloca memória
    nodeLista *novo;
    if ((novo = malloc(sizeof(*novo))) == NULL)
        return NULL;

    // Adiciona a árvore ao nó
    novo->n = nArv;

    // Faz o campo próximo apontar para NULL
    novo->proximo = NULL;

    return novo;
}

/** Função que faz alocação de memória e trata os ponteiros soltos acerca de nós da árvore
* @param: o caract a ser gravado no nó, a frequencia do caract, ponteiros para os nós filhos
*/

nodeArvore *novoNodeArvore(caract c, int frequencia, nodeArvore *esquerda, nodeArvore *direita)
{
    // Aloca memória
    nodeArvore *novo;

    if ((novo = malloc(sizeof(*novo))) == NULL)
        return NULL;

    // Atribui na árvore os valores passados como parâmetro
    novo->c = c;
    novo->frequencia = frequencia;
    novo->esquerda = esquerda;
    novo->direita = direita;

    return novo;
}

/** Função que um novo nó na lista encadeada que representa a fila de prioridade.
* @param: um nó previamente criado, a lista que receberá o nó
*/

void insereLista(nodeLista *n, lista *l)
{
    // Se a lista passada como parâmetro não tem um nó no início (vazia), insira o nó no início
    if (!l->head)
    {
        l->head = n;
    }

    // Se o campo 'frequência' do 'nó' parâmetro for menor que o campo 'frequência' do primeiro item (head)
    // da lista, incluir o novo nó como head, e colocar o head antigo como next desse novo

    else if (n->n->frequencia < l->head->n->frequencia)
    {
        n->proximo = l->head;
        l->head = n;
    }
    else
    {
        // nó auxiliar que inicia apontando para o segundo nó da lista (head->proximo)
        nodeLista *aux = l->head->proximo;
        // nó auxiliar que inicia apontando para o primeiro nó da lista
        nodeLista *aux2 = l->head;

        // Laço que percorre a lista e insere o nó na posição certa de acordo com sua frequência.
        //
        // Se sabe que aux começa apontando para o segundo item da lista e aux2 apontando para o primeiro.
        // Sendo assim, os ponteiros seguirão mudando de posição enquanto aux não for o fim da lista,
        // e enquanto a frequência do nó apontado por aux for menor ou igual a frequência do 'nó' parâmetro.

        while (aux && aux->n->frequencia <= n->n->frequencia)
        {
            aux2 = aux;
            aux = aux2->proximo;
        }

        // Se insere o nó na posição certa.
        aux2->proximo = n;
        n->proximo = aux;
    }

    // Incrementa quantidade de elementos
    l->elementos++;
}

/** Função que 'solta' o nó apontado por 'head' da lista (o de menor frequência)
* (faz backup do nó e o desconecta da lista)
* @param: uma lista encadeada.
*/

nodeArvore *popMinLista(lista *l)
{

    // Ponteiro auxilar que aponta para o primeiro nó da lista
    nodeLista *aux = l->head;

    // Ponteiro auxiliar que aponta para a árvore contida em aux (árvore do primeiro nó da lista)
    nodeArvore *aux2 = aux->n;

    // Aponta o 'head' da lista para o segundo elemento dela
    l->head = aux->proximo;

    // Libera o ponteiro aux
    free(aux);
    aux = NULL;

    // Decrementa a quantidade de elementos
    l->elementos--;

    return aux2;
}

/** Função que constrói a árvore de huffman
* @param: a fila de prioridade.
*/

nodeArvore *BuildHuffmanTree(unsigned *listaBytes)
{
    // Lista com head apontando pra NULL e com campo 'elementos' valendo 0;
    lista l = {NULL, 0};

    // Popula usando a array 'listaBytes' (que contém as frequências) uma lista encadeada de nós.
    // Cada nó contém uma árvore.
    for (int i = 0; i < 256; i++)
    {
        if (listaBytes[i]) // Se existe ocorrência do caract
        {
            // Insere na lista 'l' um nó referente ao caract i e sua respectiva frequência (guardada em listaBytes[i]).
            // Faz os nós esquerdo e direito das árvores apontarem para NULL;
            insereLista(novoNodeLista(novoNodeArvore(i, listaBytes[i], NULL, NULL)), &l);
        }
    }

    while (l.elementos > 1) // Enquanto o número de elementos da lista for maior que 1
    {
        // Nó esquerdo chama a função popMinLista() que vai na lista e pega a árvore fixada no primeiro nó
        // (que é a que contém a menor frequência)
        nodeArvore *nodeEsquerdo = popMinLista(&l);

        // Pega o outro nó que tem menor frequência
        nodeArvore *nodeDireito = popMinLista(&l);

        // Preenche com '#' o campo de caractere do nó da árvore.
        // Preenche o campo 'frequência' com a soma das frequências de 'nodeEsquerdo' e 'nodeDireito'.
        // Aponta o nó esquerdo para nodeEsquerdo e o nó direito para nodeDireito
        nodeArvore *soma = novoNodeArvore( '#',
            nodeEsquerdo->frequencia + nodeDireito->frequencia, nodeEsquerdo, nodeDireito);

        // Reinsere o nó 'soma' na lista l
        insereLista(novoNodeLista(soma), &l);
    }

    return popMinLista(&l);
}

/** Função que libera memória da árvore de huffman
* @param: nó de uma (sub)árvore.
*/

void FreeHuffmanTree(nodeArvore *n)
{
    // Caso base da recursão, enquanto o nó não for NULL
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

/** Função que conta a frequência de ocorrências dos bytes de um dado arquivo
* @param: um arquivo, uma lista de bytes
*/
/*
void getByteFrequency(unsigned int *listaBytes)
{

    caract c;

    /***
    *
    * fread( array/bloco de memoria , tamanho de cada elemento, quantos elementos, arquivo de entrada )
    * fread retorna a quantidade de blocos lidos com sucesso
    *
    * Faz a leitura de 1 bloco de tamanho 1 byte a partir do arquivo 'entrada'
    * e salva no espaco de memoria de 'c'.
    *
    * Converte esse byte num valor decimal, acessa o bucket correspondente e incrementa o valor (frequência).
    *
    ***/
    //for (int i = 0; i < 256; i++)
    //{
      //  printf(" [%d] ", listaBytes[i]);
        //listaBytes[i] += 1;
    //}

    //rewind(entrada); // "rebobina o arquivo"
//}


void imprime(nodeArvore *le)
{
    if (le != NULL)
    {
        printf(" [%c, %d]   ", le->c, le->frequencia);
        printf("Entrei na esquerda...");
        imprime(le->esquerda);
        printf("Entrei na direita...");
        imprime(le->direita);
    }
}

//node *HEAD = NULL;
//node *ROOT = NULL;

int main()
{
    char entrada[] = "aaaaabbbbcccdde";
    //unsigned *numberChars = calloc(256, sizeof numberChars);
    //printf("funcionando");
    int *listaBytes = calloc(256, sizeof listaBytes);

    for (int i = 0; i < strlen(entrada); i++)
    {
        listaBytes[entrada[i]] += 1;
        printf(" [%d] ", listaBytes[i]);
    }
    //FILE *entrada = fopen("exemplo.txt", "r");
    //getByteFrequency(entrada,&listaBytes);
    //nodeArvore *raiz = BuildHuffmanTree(&listaBytes);

    //printf("\n\n");
    //imprime(&raiz);
    /*
    printf("\n\n");
    imprime(HEAD);
    printf("\n\n");
    //treeH(HEAD);
    printf("\n\n");
    */
    //printf("Nodo removido foi: [%c,%d]", desk.caract, desk.freq);
    printf("\n");
    //printf("\nHello world!\n");
    return 0;
}
