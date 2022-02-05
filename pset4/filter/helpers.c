#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //hard code total of color values to get float
    float divide = 3;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //averages the color values
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / divide);
            //set all values to average
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
//set color values as float to get more accurate total from equation
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
//sepia equations for each color
            int sepiaBlue = round((.272 * red) + (.534 * green) + (.131 * blue));
            int sepiaRed = round((.393 * red) + (.769 * green) + (.189 * blue));
            int sepiaGreen = round((.349 * red) + (.686 * green) + (.168 * blue));
//sets maximum value
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
//sets temp value to each pixel
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
//loops up to middle of image
        for (int j = 0; j < round((float)width / 2); j++)
        {
//temp image stores original value
            RGBTRIPLE temp = image[i][j];
//a image now equals b image
            image[i][j] = image[i][(width - 1) - j];
//b image now equal to temp (or original of a)
            image[i][(width - 1) - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
//integers for storing temp values
            float counter = 0;
            int red = 0;
            int green = 0;
            int blue = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
//makes so nested loop never goes out of dimensions of image
                    if (x + i < 0 || x + i >= height || y + j < 0 || y + j >= width)
                    {
                        continue;
                    }
                    else
                    {
//adds each surrounding pixel to current pixel value
                        red += image[x + i][y + j].rgbtRed;
                        green += image[x + i][y + j].rgbtGreen;
                        blue += image[x + i][y + j].rgbtBlue;
                        counter++;
                    }
                }
            }
//creates avg and sets to temp
            blur[i][j].rgbtRed = round(red / counter);
            blur[i][j].rgbtGreen = round(green / counter);
            blur[i][j].rgbtBlue = round(blue / counter);
        }
    }
//moves temp value to original
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = blur[a][b].rgbtRed;
            image[a][b].rgbtBlue = blur[a][b].rgbtBlue;
            image[a][b].rgbtGreen = blur[a][b].rgbtGreen;
        }
    }
    return;
}
