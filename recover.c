// By: Krishna. T, Written: Jul 13

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int HEADER_SIZE = 512;

int main(int argc, char *argv[])
{
    // Checks command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Opens file, and checks if it contains anything
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    // Varibles
    uint8_t buffer[HEADER_SIZE];
    int counter = 0;
    FILE *img = NULL;
    char filename[8];
    
    while (fread(&buffer, HEADER_SIZE, 1, f) == 1)
    {
        // checks for a pattern of bytes to check if it is a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(img);
            }
            
            // creates a new file
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
            
        }
        
        if (counter != 0)
        {
            fwrite(&buffer, HEADER_SIZE, 1, img);
        }
    }
    
    fclose(f);
    fclose(img);
    
    return 0;
}

// End