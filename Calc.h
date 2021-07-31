#ifdef _WIN32 /*define o comando de limpar a tela com base no Sistema Operacional.*/
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct
{
    int number;
} Item;

/*  definido estrutura Node (Nó da pilha)  */
typedef struct nodeEst
{
    Item item;
    struct nodeEst *next;
} Node;

/*  definido estrutura Pilha  */
typedef struct
{
    Node *top;
    int stackSize;
} Stack;

/*  faz a pilha ficar vazia */
void makeEmptyStack(Stack *);

/* verifica se a pilha esta vazia */
int stackIsEmpty(Stack *);

/*  empilhar */
int stackUp(Stack *, Item);

/*  desempilhar */
int unstack(Stack *, Item *);

/*  funcao que verifica se o paremtro openBracket e o oposto do parametro closeBracket
    retorna 1 se for, caso contrario retorna 0
 */
int isBracketPair(int, int);

/* funcao que valida se a expressao digitada e valida
    retorna 1 se for valida, caso contrario retorna 0
*/
int validateExpression(char *);

/* funcao que converte da notacao infixa para notacao polonesa reversa */
char *transformToPosfix(char *);

/* funcao que realiza o calcula dos elementos da pilha */
int calculate(int, int, char, Stack *);

/* procedimento para imprimir a pilha */
void printStack(Stack *);

/* procedimento para liberar a memoria da pilha */
void freeStack(Stack *);