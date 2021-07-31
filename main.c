#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Calc.h"

int main(int argc, char const *argv[])
{
    system(CLEAR);
    int j = 0;
    char expression[50], *posfix, op;
    Stack st;
    Item aux, aux2, aux3;

    makeEmptyStack(&st);

    printf("Digite a expressao na forma habitual: ");
    fgets(expression, 50, stdin);
    expression[strcspn(expression, "\n")] = 0;

    /* valida a expressao */
    if (!validateExpression(expression))
        printf("expressao mal formada\n");
    else /* se a expressao for valida */
    {
        posfix = transformToPosfix(expression);
        printf("\nRepresentacao na notacao posfixa:%s\n\n", posfix);
        for (int i = 0; posfix[i] != '\0'; i++) /* percorre a expressao (na notacao posfixa) */
        {

            /* se achar um espaço e o prox caracter nao for uma operacao */
            /* realiza a acao do caracter 'E', empilha um 0 */
            if (posfix[i] == ' ' && posfix[i + 1] != '+' && posfix[i + 1] != '-' && posfix[i + 1] != '*' && posfix[i + 1] != '/')
            {
                printf("===========================================\n");
                aux.number = 0;
                stackUp(&st, aux);
                printf("Caracter E\nEmpilhou -> 0\n");
                printStack(&st);
            }
            else
            {
                /* aqui verifica se o caracter atual e um numero (0,1...8,9) */
                /* e a realiza a acao (x*10+i) */
                if (isdigit(posfix[i]))
                {
                    printf("===========================================\n");
                    unstack(&st, &aux);
                    aux.number = aux.number * 10 + (posfix[i] - '0');
                    stackUp(&st, aux);
                    printf("Empilhou -> %c\n", posfix[i]);
                    printStack(&st);
                }
                /* verifica se o caracter atual e uma operacao */
                /* e realiza o calculo empilhando o resultado em seguida */
                else if (posfix[i] != ' ' && !isdigit(posfix[i]))
                {
                    printf("===========================================\n");
                    unstack(&st, &aux);
                    unstack(&st, &aux2);
                    aux3.number = calculate(aux2.number, aux.number, posfix[i], &st);
                    printf("Desempilhou %d e %d\n", aux.number, aux2.number);
                    printf("Operacao: %d %c %d\n", aux2.number, posfix[i], aux.number);
                    stackUp(&st, aux3);
                    printf("Empilhou -> %d\n", aux3.number);
                    printStack(&st);
                }
            }
        }
        printf("===========================================\n");
        free(posfix);
        freeStack(&st);
    }
    return 0;
}
