#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_space(int height, int row);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height? ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        print_space(height, i);
        print_row(i + 1);
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}

void print_space(int height, int row)
{

    for (int i = 0; i < height - row - 1; i++)
    {
        printf(" ");
    }
}

