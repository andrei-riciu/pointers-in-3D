#include "chunk.h"

// Copyright [2025] <Andrei Riciu>

char*** chunk_init(int width, int height, int depth) {
    char*** chunk = malloc(width * sizeof *chunk);
    for (int x = 0; x < width; x++) {
        chunk[x] = malloc(height * sizeof **chunk);
        for (int y = height - 1; y >= 0; y--) {
            chunk[x][y] = malloc(depth * sizeof ***chunk);
        }
    }
    return chunk;
}
char*** chunk_rotate_y(char*** chunk, int width, int height, int depth) {
    char*** chunk_nou = chunk_init(depth, height, width);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            for (int z = 0; z < depth; z++)
                chunk_nou[depth - z - 1][y][x] = chunk[x][y][z];
    chunk = chunk_free(chunk, width, height, depth);
    return chunk_nou;
}
int*** chunk_numerotate_structs(
    char*** chunk, int*** int_chunk, int width, int height, int depth, int x,
    int y, int z, int block
) {
    const char B = chunk[x][y][z];

    int_chunk[x][y][z] = block;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                if (is_in_chunk(width, height, depth, x + i, y + j, z + k)
                    && chunk[x + i][y + j][z + k] == B
                    && int_chunk[x + i][y + j][z + k] == 0
                    && i * i + j * j + k * k == 1) {
                    int_chunk = chunk_numerotate_structs(
                        chunk, int_chunk, width, height, depth, x + i, y + j,
                        z + k, block
                    );
                }
    return int_chunk;
}
int*** int_chunk_fill(
    int*** chunk, int width, int height, int depth, int x, int y, int z,
    int block
) {
    const int B = chunk[x][y][z];
    chunk[x][y][z] = block;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            for (int k = -1; k <= 1; k++)
                if (is_in_chunk(width, height, depth, x + i, y + j, z + k)
                    && chunk[x + i][y + j][z + k] == B
                    && chunk[x + i][y + j][z + k] != block
                    && i * i + j * j + k * k == 1) {
                    chunk = int_chunk_fill(
                        chunk, width, height, depth, x + i, y + j, z + k, block
                    );
                }
    return chunk;
}
int can_move(
    int*** chunk, int width, int height, int depth, int block, int direction
) {
    if (block == 0)
        return 0;
    int exists = 0;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            for (int z = 0; z < depth; z++)
                if (chunk[x][y][z] == block) {
                    if ((is_in_chunk(width, height, depth, x, y + direction, z)
                         && chunk[x][y + direction][z] != block
                         && chunk[x][y + direction][z] != 0)
                        || is_in_chunk(
                               width, height, depth, x, y + direction, z
                           ) == 0)
                        return 0;
                    exists = 1;
                }
    if (exists == 0)
        return 0;
    return 1;
}

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height
) {
    int*** int_chunk = malloc(width * sizeof *int_chunk);
    for (int x = 0; x < width; x++) {
        int_chunk[x] = malloc(height * sizeof **int_chunk);
        for (int y = height - 1; y >= 0; y--) {
            int_chunk[x][y] = malloc(depth * sizeof ***int_chunk);
            for (int z = 0; z < depth; z++)
                int_chunk[x][y][z] = 0;
        }
    }
    int block = 0;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            for (int z = 0; z < depth; z++) {
                if (chunk[x][y][z] && int_chunk[x][y][z] == 0)
                    int_chunk = chunk_numerotate_structs(
                        chunk, int_chunk, width, height, depth, x, y, z, ++block
                    );
            }
    for (int i = 1; i <= block; i++)
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                for (int z = 0; z < depth; z++) {
                    if (int_chunk[x][y][z] == i
                        && can_move(int_chunk, width, height, depth, i, 1) == 0
                        && can_move(int_chunk, width, height, depth, i, -1)
                               == 0) {
                        if (is_in_chunk(width, height, depth, x, y + 1, z)
                            && int_chunk[x][y + 1][z] != 0
                            && int_chunk[x][y + 1][z] != i
                            && is_in_chunk(width, height, depth, x, y - 1, z)
                            && int_chunk[x][y - 1][z] != 0
                            && int_chunk[x][y - 1][z] != i
                            && int_chunk[x][y + 1][z] == int_chunk[x][y - 1][z])
                            int_chunk = int_chunk_fill(
                                int_chunk, width, height, depth, x, y + 1, z, i
                            );
                    }
                }

    int ok = 0;
    do {
        ok = 0;
        for (int i = 1; i <= block; i++)
            if (can_move(int_chunk, width, height, depth, i, -1)) {
                ok = 1;
                for (int y = 1; y < height; y++)
                    for (int x = 0; x < width; x++)
                        for (int z = 0; z < depth; z++)
                            if (int_chunk[x][y][z] == i) {
                                int_chunk[x][y - 1][z] = i, chunk[x][y - 1][z] =
                                                                chunk[x][y][z];
                                if ((y < height - 1
                                     && int_chunk[x][y + 1][z] != i)
                                    || y == height - 1)
                                    int_chunk[x][y][z] = 0, chunk[x][y][z] = 0;
                            }
            }
    } while (ok == 1);
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            for (int z = 0; z < depth; z++) {
                if (chunk[x][y][z])
                    *new_height = y + 1;
            }
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++)
            free(int_chunk[x][y]), int_chunk[x][y] = NULL;
        free(int_chunk[x]), int_chunk[x] = NULL;
    }
    free(int_chunk), int_chunk = NULL;
    char*** chunk1 = chunk_copy(chunk, width, *new_height, depth);
    chunk = chunk_free(chunk, width, height, depth);
    return chunk1;
}
