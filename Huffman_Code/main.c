#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Compress/Compress.h"
#include "Compress/Decompress.h"
#include "Compress/Huffman_tree.h"
#include "Compress/Huffman_dictionary.h"

int main() {
    char file_directory[200], new_directory[200];
    int choice = 1;

    printf("Welcome to the Compress and Decompress\n\nPlease, enter the directory to be accessed\n");
    scanf("%s", file_directory);
    printf("\nChoose what to do:\n    \t(1)Compress\n    \t(2)Decompress\n");
    scanf("%d", &choice);
    printf("Please, enter the new directory and the new file name\n");
    scanf("%s", new_directory);
 
    if(choice == 1) {
        strcat(new_directory, ".huff");
        read_bytes_compress(file_directory, new_directory, 0);
    } else if (choice == 2) {
        read_bytes_decompress(file_directory, new_directory);
    }

    return 0;
}