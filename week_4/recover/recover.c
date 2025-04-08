#include <getopt.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    // Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
    const char *usage = "Usage: ./recover FILE\n";
    
    // If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
    if (argc != 2) { 
        printf("%s", usage); 
        return 1;
    }

    // If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
    FILE *card = fopen(argv[1], "r");
    
    if (card == NULL) {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    
    // initialize number of passes
    int count = 0; 

    // The files you generate should each be named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up
    while (fread(buffer, 1, 512, card) == 512) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // Create the new jpg file
            char filename[8];
            
            sprintf(filename, "%03i.jpg", count);
            FILE *img = fopen(filename, "w");

            // write the buffer to the file
            fwrite(buffer, 1, 512, img);
            count++;

            // Continue writing until the next JPEG header is found
            while (fread(buffer, 1, 512, card) == 512) {
            // Check for the next JPEG header
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
                    break; // If new header is found, break the loop
                }

                // Write the current block to the JPEG file
                fwrite(buffer, 1, 512, img);
                }
            // close the new jpg
            fclose(img);
        }
    }

    // Close the raw
    fclose(card);
}