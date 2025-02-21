#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop de colunas
    for (int i = 0; i < height; i++)
    {
        // loop de pixels
        for (int j = 0; j < width; j++)
        {
            // pegar os tres valores e tirar a media
            double average =
                (double) (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3;

            // deixat em float para arredondar para o inteiro mais proximo
            int new_average = round(average);

            // aplicar as mudancas em cada pixel
            image[i][j].rgbtBlue = new_average;
            image[i][j].rgbtRed = new_average;
            image[i][j].rgbtGreen = new_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaBlue;
    float sepiaGreen;
    // loop de colunas
    for (int i = 0; i < height; i++)
    {
        // loop de pixels
        for (int j = 0; j < width; j++)
        {
            // aplicar a formula de sepia para cada cor, arredondar o valor e garantir que seja
            // maior que 0 e menor que 255
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                       .189 * image[i][j].rgbtBlue;
            int new_sepiaRed = round(sepiaRed);
            if (new_sepiaRed < 0)
            {
                new_sepiaRed = 0;
            }
            else if (new_sepiaRed > 255)
            {
                new_sepiaRed = 255;
            }

            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                        .131 * image[i][j].rgbtBlue;
            int new_sepiaBlue = round(sepiaBlue);
            if (new_sepiaBlue < 0)
            {
                new_sepiaBlue = 0;
            }
            else if (new_sepiaBlue > 255)
            {
                new_sepiaBlue = 255;
            }

            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                         .168 * image[i][j].rgbtBlue;
            int new_sepiaGreen = round(sepiaGreen);
            if (new_sepiaGreen < 0)
            {
                new_sepiaGreen = 0;
            }
            else if (new_sepiaGreen > 255)
            {
                new_sepiaGreen = 255;
            }
            image[i][j].rgbtBlue = new_sepiaBlue;
            image[i][j].rgbtRed = new_sepiaRed;
            image[i][j].rgbtGreen = new_sepiaGreen;
        }
    }
    return;
}
// Reflect image horizontally

void swap(RGBTRIPLE *a, RGBTRIPLE *b);

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        // loop de colunas
    for (int i = 0; i < height; i++)
    {
        // loop de pixels
        for (int j = 0; j < (width / 2); j++)
        {
            swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int TotalRed, TotalBlue, TotalGreen;
            TotalRed = TotalBlue = TotalGreen = 0;
            float counter = 0.00;

            //get neighbor pixels
            for(int x = -1; x < 2; x++)
            {
                for(int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    //check if the pixels are valid
                    if(currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    // get image value
                    TotalRed += image[currentX][currentY].rgbtRed;
                    TotalBlue += image[currentX][currentY].rgbtBlue;
                    TotalGreen += image[currentX][currentY].rgbtGreen;

                    counter++;
                }

                //get the average
                temp[i][j].rgbtRed = round(TotalRed / counter);
                temp[i][j].rgbtGreen = round(TotalGreen / counter);
                temp[i][j].rgbtBlue = round(TotalBlue / counter);
            }

        }
    }

    //copy new values to the image
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
