#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//accepts commandline argument
int main(int argc, char *argv[])
{
//only accepts second command line input
    if (argc != 2)
    {
        printf("Usage: recover [filename.raw]\n");
        return 1;
    }
//allocates 8 bytes for pointer name
    char *name = malloc(8);
    if (name == NULL)
    {
        perror("Error: \n");
        return 2;
    }
    int counter = 0;
//create type called BYTE that cointains 8 bits
    typedef uint8_t BYTE;
    BYTE buffer[512];
//opens file for reading
    FILE *file = fopen(argv[1], "r");
//declares pointer img
    FILE *img;
//reads through file as long as it returns 1
    while (fread(buffer, 512, 1, file) > 0)
    {
//looks at first four bytes to determine if JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
//if first JPEG opens and writes
            if (counter == 0)
            {
                sprintf(name, "%03i.jpg", counter);
                img = fopen(name, "w");
                fwrite(buffer, 512, 1, img);
                counter++;
            }
            else
            {
//if not first closes old then opens and writes
                fclose(img);
                sprintf(name, "%03i.jpg", counter);
                img = fopen(name, "w");
                fwrite(buffer, 512, 1, img);
                counter++;
            }
        }
//continues to write to file
        else if (counter != 0)
        {
            fwrite(buffer, 512, 1, img);
        }

    }
//free space reserved for name
    free(name);
}



