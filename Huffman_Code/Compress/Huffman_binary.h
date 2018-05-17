#ifndef HUFFMAN_BINARY_H
#define HUFFMAN_BINARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char set (unsigned char c, int i);

bool isBitiSet(unsigned char byte, int i);

void reverse(char string[]);

void to_binary (int x, char string[],int k);

#endif