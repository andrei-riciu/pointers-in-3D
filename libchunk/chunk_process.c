#include "chunk.h"

// Copyright [2025] <Andrei Riciu>

char*** chunk_free(char*** chunk, int width, int height, int depth) {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++)
            free(chunk[x][y]), chunk[x][y] = NULL;
        free(chunk[x]), chunk[x] = NULL;
    }
    free(chunk), chunk = NULL;
    return chunk;
}
char*** chunk_copy(char*** chunk, int width, int height, int depth) {
    char*** chunk1 = malloc(width * sizeof *chunk1);
    for (int x = 0; x < width; x++) {
        chunk1[x] = malloc(height * sizeof **chunk1);
        for (int y = 0; y < height; y++) {
            chunk1[x][y] = malloc(depth * sizeof ***chunk1);
            for (int z = 0; z < depth; z++)
                chunk1[x][y][z] = chunk[x][y][z];
        }
    }
    return chunk1;
}
char*** chunk_shell(
    char*** chunk, int width, int height, int depth, char target_block,
    char shell_block
) {
    char*** chunk1 = chunk_copy(chunk, width, height, depth);
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            for (int z = 0; z < depth; z++) {
                if (chunk[x][y][z] == target_block) {
                    for (int i = -1; i <= 1; i++)
                        for (int j = -1; j <= 1; j++)
                            for (int k = -1; k <= 1; k++) {
                                if (i * j * k == 0
                                    && (i * i + j * j + k * k) != 0
                                    && is_in_chunk(
                                        width, height, depth, x + i, y + j,
                                        z + k
                                    )) {
                                    if (chunk[x + i][y + j][z + k]
                                        != target_block)
                                        chunk1 = chunk_place_block(
                                            chunk1, width, height, depth, x + i,
                                            y + j, z + k, shell_block
                                        );
                                }
                            }
                }
            }
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            for (int z = 0; z < depth; z++)
                chunk[x][y][z] = chunk1[x][y][z];
    chunk1 = chunk_free(chunk1, width, height, depth);
    return chunk;
}
char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
) {
    const char B = chunk[x][y][z];

    chunk = chunk_place_block(chunk, width, height, depth, x, y, z, block);
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (is_in_chunk(width, height, depth, x + i, y, z + j)
                && chunk[x + i][y][z + j] == B
                && chunk[x + i][y][z + j] != block && i * i + j * j == 1) {
                chunk = chunk_fill_xz(
                    chunk, width, height, depth, x + i, y, z + j, block
                );
            }
    return chunk;
}

char*** chunk_fill(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
) {
    const char B = chunk[x][y][z];

    chunk = chunk_place_block(chunk, width, height, depth, x, y, z, block);
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                if (is_in_chunk(width, height, depth, x + i, y + j, z + k)
                    && chunk[x + i][y + j][z + k] == B
                    && chunk[x + i][y + j][z + k] != block
                    && i * i + j * j + k * k == 1) {
                    chunk = chunk_fill(
                        chunk, width, height, depth, x + i, y + j, z + k, block
                    );
                }
    return chunk;
}
