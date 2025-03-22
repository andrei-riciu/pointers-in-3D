#include <stdio.h>
#include <stdlib.h>
#include "../libchunk/chunk.h"

void print_chunk(char*** chunk, int width, int height, int depth) {
    printf("%d\n%d\n%d\n", width, height, depth);

    for (int x = 0; x < width; x++) {
        for (int y = height - 1; y >= 0; y--) {
            for (int z = 0; z < depth; z++)
                printf("%d ", chunk[x][y][z]);
            printf("\n");
        }
        printf("\n");
    }
}
void printbin(int n) {
    for (int i = 7; i >= 0; i--)
        printf("%d", (n & (1 << i)) != 0);
}
char*** read_chunk(int* width, int* height, int* depth) {
    scanf("%d%d%d", width, height, depth);

    char*** chunk = malloc(*width * sizeof *chunk);

    for (int x = 0; x < *width; x++) {
        chunk[x] = malloc(*height * sizeof **chunk);
        for (int y = *height - 1; y >= 0; y--) {
            chunk[x][y] = malloc(*depth * sizeof ***chunk);

            for (int z = 0; z < *depth; z++)
                scanf("%hhd", &chunk[x][y][z]);
        }
    }

    return chunk;
}
#include <string.h>
int main(void) {
    int *width = calloc(1, sizeof(int)), *height = calloc(1, sizeof(int)),
        *depth = calloc(1, sizeof(int)), *length = calloc(1, sizeof(int));
    // scanf("%d %d %d", width, height, depth);
    char*** chunk = read_chunk(width, height, depth);
    printf("main merge\n");
    chunk = chunk_apply_gravity(chunk, *width, *height, *depth, length);

    // for (int i = 0; i < *length; i++)
    //   printbin(encoded[i]), printf(" ");
    // print_chunk(chunk, width, height, depth);

    return 0;
}
