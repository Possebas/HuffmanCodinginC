#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE #
#define TAM 256
#define ESQUERDA 0
#define DIREITA 1

//Utilizamos um char sem sinal para melhor compreensão do código
typedef unsigned char unique;

/*
Estrutura básica de um nodo que está inserido na árvore
Atributos: frequência, código(representação binária), caractere, referência para esquerda e direita.
 */
typedef struct nodeOfTree
{
    int frequency;
    char code;
    unique c;
    struct nodeOfTree *left;
    struct nodeOfTree *right;
} nodeOfTree;
/*
Estruturação da lista encadeada de nodos
Atributos: valor e referência pro próximo.
 */
typedef struct linkedListNodes
{
    nodeOfTree *value;
    struct linkedListNodes *next;
} linkedListNodes;
/*Estrutura simples apenas para guardar a refêrencia do primeiro elemento da lista e contador dos elementos contidos nela.*/
typedef struct listProps
{
    linkedListNodes *head;
    int count;
} listProps;

typedef struct dic
{
    char key;
    char value[20];
}dic;

struct dic dicioCode[20];

/* Aloca o espaço de memória para o novo nodo da lista e aponta uma arvore para ele */

//----------------------------------------------------------------------------------//

linkedListNodes *insertNodeLinkedList(nodeOfTree *new_Node)
{

    linkedListNodes *aux;

    if ((aux = malloc(sizeof(*aux))) == NULL)
    {
        return NULL;
    }
    aux->value = new_Node;

    aux->next = NULL;

    return aux;
}

/* Aloca o espaço de memória para o novo nodo da árvore e aponta uma arvore para ele
    Recebe por parâmetro: o caractere, frequencia, referência da esquerda e direita dele
*/

nodeOfTree *insertNodeTree(unique c, int frequency, nodeOfTree *left, nodeOfTree *right)
{

    nodeOfTree *aux;

    if ((aux = malloc(sizeof(*aux))) == NULL)
    {
        return NULL;
    }

    aux->c = c;
    aux->frequency = frequency;
    aux->left = left;
    aux->right = right;

    return aux;
}

/*
    Inserindo ordenado novamente na lista encadeada fazendo assim uma lista de prioridade
 */

void insertOrderly(linkedListNodes *value, listProps *list)
{

    if (!list->head)
    {
        list->head = value;
    }

    else if (value->value->frequency < list->head->value->frequency)
    {
        value->next = list->head;
        list->head = value;
    }
    else
    {

        linkedListNodes *aux = list->head->next;

        linkedListNodes *aux2 = list->head;

        while (aux && aux->value->frequency <= value->value->frequency)
        {
            aux2 = aux;
            aux = aux2->next;
        }

        aux2->next = value;
        value->next = aux;
    }

    list->count++;
}

/*
    Remove o primeiro nodo da lista, aquele com menor frequencia
 */
nodeOfTree *returnMin(listProps *list)
{

    linkedListNodes *aux = list->head;

    nodeOfTree *aux2 = aux->value;

    list->head = aux->next;

    free(aux);
    aux = NULL;

    list->count--;

    return aux2;
}
/*
    Principalmente função que é responsável por criar a árvore de huffman, porém sem código nesta parte.
 */
nodeOfTree *dibbeHuff(int *listFrequency)
{

    listProps list = {NULL, 0};

    for (int i = 0; i < 256; i++)
    {
        if (listFrequency[i])
        {
            printf("Caractere e sua frequencia => [%c:%d]\n", i, listFrequency[i]);

            insertOrderly(insertNodeLinkedList(insertNodeTree(i, listFrequency[i], NULL, NULL)), &list);
        }
    }
    /* Vai removendo e inserindo ordenado na árvore */
    while (list.count > 1)
    {

        nodeOfTree *nodeEsquerdo = returnMin(&list);
        printf("\n");
        //*POP*//
        printf("Primeiro elemento retirado da lista: %c, freq: %d", nodeEsquerdo->c, nodeEsquerdo->frequency);

        nodeOfTree *nodeDireito = returnMin(&list);
        printf("\n");
        //*POP*//
        printf("Segundo elemento retirado da lista: %c, freq: %d", nodeDireito->c, nodeDireito->frequency);

        nodeOfTree *soma = insertNodeTree('#', nodeEsquerdo->frequency + nodeDireito->frequency, nodeEsquerdo, nodeDireito);
        printf("\n");
        printf("\nA soma das frequencias a ser adicionada: %d", soma->frequency);
        printf("\n");

        insertOrderly(insertNodeLinkedList(soma), &list);
    }
    return returnMin(&list);
}
/* Função recursiva responsável por liberar mémoria de toda árvore */
void removeOfMemory(nodeOfTree *value)
{
    if (!value)
        return;
    else
    {
        nodeOfTree *left = value->left;
        nodeOfTree *right = value->right;
        free(value);
        removeOfMemory(left);
        removeOfMemory(right);
    }
}

void generateCodeOfChars(nodeOfTree *root, char arr[], int len, int count)
{

    //Adiciona 1 caso exista um nodo na direita
    if (root->right)
    {
        arr[len] = '1';
        generateCodeOfChars(root->right, arr, len + 1, count + 1);
    }
    //Adiciona 0 caso exista um nodo na esquerda
    if (root->left)
    {
        arr[len] = '0';
        generateCodeOfChars(root->left, arr, len + 1, count + 1);
    }

    if (root->left == NULL)
    {
        arr[count] = 0;
        printf("%c\t\t%d\t\t%s\n", root->c, root->frequency, arr); //Printa na tela os caracteres, suas respectivas frequências e bits
        dicioCode[count].key = root->c;
        //Strcpy é uma função que realiza a cópia do conteúdo de uma variável a outra
        strcpy(dicioCode[count].value, arr);
        count++;
    }
}

int main()
{
    int listFrequency[256] = {0}; //limpa todos as posições de memórias com 0, as quais serão armazenadas as frequencias de cada caractere
    int numberChars = 0; //contador local para numero de caracteres

    FILE *file = fopen("exemplo.txt", "r"); //armazena o arquivo apenas para leitura

    if (file == NULL)
    {
        printf("Could not open the specified file!\n");
        exit(EXIT_FAILURE); //retorna se houver erro na leitura do arquivo
    }

    for (char c; (((c = fgetc(file)) != '\n') && (c != EOF));)
    {
        if (listFrequency[c] == 0)
        {
            numberChars += 1;
        }
        listFrequency[c] += 1;
    }

    nodeOfTree *raiz = dibbeHuff(listFrequency); //executa a arvore e armazena a raíz
    printf("\n");
    printf("Frequencia final da Raiz: %d", raiz->frequency); //imprimi a frequencia da raiz que é a soma de todas as frequencias
    printf("\n");
    printf("-----------------------------------");
    printf("\n");
    printf("Tabela de caracteres codificados\n");
    printf("-----------------------------------");

    printf("\nCaractere\tFrequencia\tHuffman\n");
    generateCodeOfChars(raiz,listFrequency,0,0); //gera o codigo e imprime parelalemente os seus caracteres, frequencias e valores de huffman.
    removeOfMemory(raiz);
}
