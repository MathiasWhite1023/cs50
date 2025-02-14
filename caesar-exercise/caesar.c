#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2) // se for diferente de dois prompt the user como usar
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int K = strlen(argv[1]); // comprimento da KEY
    for (int i = 0; i < K; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int KEY = atoi(argv[1]); // printf("Converted integer: %i\n", KEY);

    string plain = get_string("Plaintext: ");
    int P = strlen(plain); // comprimento do plaintext
    char c[P + 1];         // !!!!!!!! o +1 indica que o tamanho do array c e do tamamho de P
                   // que eh o plaintext + o null character que vai ser usada para indicar o fim do
                   // string

    for (int i = 0; i < P; i++)
    {
        if (isupper(plain[i]))
        {
            plain[i] = plain[i] - 'A';
            c[i] = (plain[i] + KEY) % 26;
            c[i] = c[i] + 'A';
            // voltar a valor ASCII
            // printf("%c", c[i]);
        }
        else if (islower(plain[i]))
        {
            plain[i] = plain[i] - 'a';
            c[i] = (plain[i] + KEY) % 26;
            c[i] = c[i] + 'a';
            // printf("%c", c[i]);
        }
        else
        {
            c[i] = plain[i];
            // printf("%c", c[i]);
        }
    }
    c[P] = '\0';
    printf("ciphertext: %s\n", c);

    return 0;
}
