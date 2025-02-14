#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    int sum1 = 0;
    int sum2 = 0;

    string q1 = get_string("Player 1:");
    string q2 = get_string("Player 2:");

    //preciso dar um jeito de somar todas as letras(de preferencia em looping)
    for (int i = 0; i < strlen(q1); i++)
    {
        if (isupper(q1[i]))
        {
            sum1 = sum1 + q1[i] + ('a' - 'A');
            //prinf de teste
            //printf("%i\n", sum1);
        }
        else if (islower(q1[i]))
        {
            sum1 = sum1 + q1[i];
        }
        else
        {
            q1[i] = 0;
        }
    }

    for (int i = 0; i < strlen(q2); i++)
    {
        if (isupper(q2[i]))
        {
             sum2 = sum2 + q2[i] + ('a' - 'A');
            //teste prinf para saber se esta lendo as letras certo
             //printf("%i\n", sum2);
        }
        else if (islower(q2[i]))
        {
            sum2 = sum2 + q2[i];
        }
        else
        {
            q2[i] = 0;
        }
    }

    if (sum1 > sum2)
    {
        printf("Player 1 wins!\n");
    }
    else if (sum1 < sum2)
    {
        printf("Player 2 wins!\n");
    }
    else if (sum1 == sum2)
    {
        printf("Tie!\n");
    }
}
