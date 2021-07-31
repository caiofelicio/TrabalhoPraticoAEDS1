#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calc.h"

/*  cria pilha vazia */
void makeEmptyStack(Stack *st)
{
    st->top = NULL;
    st->stackSize = 0;
}

/*  verifica se a pilha esta vazia */
int stackIsEmpty(Stack *st)
{
    return st->stackSize == 0;
}

/*  empilha */
int stackUp(Stack *st, Item newItem)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    /* verifica se ocorreu erro na alocacao */
    if (!newNode)
    {
        printf("Erro ao alocar memoria...\n");
        return 0;
    }

    /* inserindo o novo item na pilha */
    newNode->item = newItem;
    newNode->next = st->top;
    st->top = newNode;
    st->stackSize++;

    return 1;
}

/*  desempilha */
int unstack(Stack *st, Item *result)
{
    /* verificando a se pilha ja esta vazia */
    if (stackIsEmpty(st))
    {
        printf("A pilha ja esta vazia...\n");
        return 0;
    }

    /* celula aux, para a remocao */
    Node *aux = st->top;
    st->top = aux->next;

    /* armazena o conteudo de de aux, antes da remocao */
    *result = aux->item;

    free(aux);
    st->stackSize--;
    return 1;
}

/*  compara os parenteses de abertura e fechamento */
int isBracketPair(int closeBracket, int openBracket)
{
    char close = closeBracket;
    char open = openBracket;

    switch (closeBracket)
    {
    case ')':
        if (openBracket == '(')
            return 1;
        return 0;
    }
}

/*  verifica se a expressao e valida */
int validateExpression(char *exp)
{

    char *p;

    /*  para a expressao ser valida,
        nao pode conter caracteres invalidos
     */

    for (p = exp; *p != '\0'; p++)
    {
        if (*p != '(' && *p != ')' && *p != '+' && *p != '-' && *p != '/' && *p != '*' && !isdigit(*p))
            return 0;
    }

    /*  para a expressao ser valida
        e necessario começar com parentese
     */
    if (exp[0] != '(')
        return 0;

    Stack st;
    Item aux, aux2;

    makeEmptyStack(&st);

    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(')
        {
            aux.number = (int)exp[i];
            stackUp(&st, aux);
        }
        else if (exp[i] == ')')
        {
            unstack(&st, &aux2);
            if (isBracketPair(exp[i], aux2.number) == 0)
            {
                return 0;
            }
        }
    }

    if (!stackIsEmpty(&st))
    {
        freeStack(&st);
        return 0;
    }
    return 1;
}

/*  transforma de infixa pra posfixa */
char *transformToPosfix(char *exp)
{
    int len = strlen(exp);
    char *posFix;
    Stack st;
    Item aux;

    posFix = (char *)malloc((len + 1) * sizeof(char));

    aux.number = exp[0];

    makeEmptyStack(&st);
    stackUp(&st, aux);

    int j = 0;
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (i == 0)
            posFix[j++] = ' ';
        switch (exp[i])
        {
        case '(':
            aux.number = (int)exp[i];
            stackUp(&st, aux);
            break;
        case ')':
            posFix[j++] = ' ';
            unstack(&st, &aux);
            while (aux.number != '(')
            {
                posFix[j++] = aux.number;
                unstack(&st, &aux);
            }
            break;
        case '+':
        case '-':
            posFix[j++] = ' ';
            unstack(&st, &aux);
            while (aux.number != '(')
            {
                posFix[j++] = aux.number;
                unstack(&st, &aux);
            }
            stackUp(&st, aux);
            aux.number = exp[i];
            stackUp(&st, aux);
            break;
        case '*':
        case '/':
            posFix[j++] = ' ';
            unstack(&st, &aux);
            while (aux.number != '(' && aux.number != '+' && aux.number != '-')
            {
                posFix[j++] = aux.number;
                unstack(&st, &aux);
            }
            stackUp(&st, aux);
            aux.number = exp[i];
            stackUp(&st, aux);
            break;
        default:
            posFix[j++] = exp[i];
        }
    }
    posFix[j] = '\0';
    return posFix;
}

/*  faz o calculo das operacoes */
int calculate(int num1, int num2, char op, Stack *st)
{
    switch (op)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        if (num2 != 0)
            return num1 / num2;
        printf("O denominador da divisao e zero, não é possivel realizar a operacao. Encerrando o programa...\n");
        freeStack(st);
        exit(1);
    }
}

/*  imprime a pilha */
void printStack(Stack *st)
{
    Node *aux = st->top;

    printf("\nINICIO PILHA\n\n");
    while (aux != NULL)
    {
        printf("| %d |\n", aux->item.number);
        aux = aux->next;
    }
    printf("\nFIM PILHA\n\n");
}

/*  libera a memoria */
void freeStack(Stack *st)
{
    if (stackIsEmpty(st))
        return;

    Item aux;

    while (!stackIsEmpty(st))
    {
        unstack(st, &aux);
    }
}