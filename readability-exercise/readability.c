#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    float Wor = 1;
    float Sen = 0;
    float Let = 0;
    string text = get_string("text: ");
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            Let = Let + 1;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            Sen = Sen + 1;
        }
        else if (isblank(text[i]))
        {
            Wor = Wor + 1;
        }
        // round(math.h)
    }
    // printf("%i, %i, %i", Let, Sen , Wor);
    double L = ((double) Let / Wor) * 100;
    double S = ((double) Sen / Wor) * 100;
    double index = 0.0588 * L - 0.296 * S - 15.8;
    // printf("%i\n", index);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",
               (int) round(index)); // Arredonda o índice para o número inteiro mais próximo
    }
}
