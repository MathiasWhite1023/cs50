#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL) // verifica se o arquivo foi aberto corretamente
    {
        printf("Could not open input file\n");
        return 1;
    }

    uint8_t buffer[512]; // Buffer para armazenar blocos de 512 bytes

    int file_number = -1; // Número do arquivo JPEG encontrado (-1 significa nenhum ainda)

    FILE *card_out = NULL; // Ponteiro para o arquivo de saída (inicialmente NULL

    while (fread(buffer, 1, 512, card) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {

            if (card_out != NULL) // Se algum arquivo card_out ja estava sendo escrito antes, e por
                                  // isso ele nao é NULL, ele é fechado
            {
                fclose(card_out);
            }

            file_number++;
            char filename[8]; // "000.jpg" precisa de 8 bytes
            sprintf(filename, "%03i.jpg",
                    file_number); // cria um arquivo com a determinada numeracao .jpg

            card_out = fopen(filename, "w"); // abre esse arquivo
            if (card_out == NULL)

            {
                printf("Could not create output file.\n");
                fclose(card);
                return 1;
            }

            fwrite(
                buffer, sizeof(uint8_t), 512,
                card_out); // escreve nesse arquivo // o buffer é utilizado aqui como file de
                           // leitura pois ele esta armazenando os 512 bytes temporiamente no loop
                           //  e dessa forma o codigo pode analisar eles separadamente ate que o
                           //  loop reinicie e um outro bloco seja analisado
        }

        else if (card_out != NULL) // apenas escreve se um arquivo tenha sido aberto
        {
            fwrite(buffer, sizeof(uint8_t), 512, card_out);
        }
    }

    fclose(card);
    if (card_out != NULL)
    {
        fclose(card_out);
    }

    return 0;
}
