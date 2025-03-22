#ifndef CHUNK_H
#define CHUNK_H
#define BLOCK_AIR 0
#define BLOCK_GRASS 1
#define BLOCK_WOOD 2
#define BLOCK_STONE 3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Partea A

// Copyright [2025] <Andrei Riciu>

char*** chunk_place_block(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
);
char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth, int x0, int y0, int z0,
    int x1, int y1, int z1, char block
);

char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    double radius, char block
);
int is_in_chunk(int width, int height, int depth, int x, int y, int z);
// Partea B

char*** chunk_shell(
    char*** chunk, int width, int height, int depth, char target_block,
    char shell_block
);

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
);

char*** chunk_fill(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
);

char*** chunk_copy(char*** chunk, int width, int height, int depth);

char*** chunk_free(char*** chunk, int width, int height, int depth);
// Partea C

char*** chunk_rotate_y(char*** chunk, int width, int height, int depth);

char*** chunk_apply_gravity(
    char*** chunk, int width, int height, int depth, int* new_height
);
int*** chunk_numerotate_structs(
    char*** chunk, int*** int_chunk, int width, int height, int depth, int x,
    int y, int z, int block
);
char*** chunk_init(int width, int height, int depth);
int can_move(
    int*** chunk, int width, int height, int depth, int block, int direction
);
int*** int_chunk_fill(
    int*** chunk, int width, int height, int depth, int x, int y, int z,
    int block
);
// Partea D

unsigned char*
    chunk_encode(char*** chunk, int width, int height, int depth, int* length);

char*** chunk_decode(unsigned char* code, int width, int height, int depth);

#endif // CHUNK_H
