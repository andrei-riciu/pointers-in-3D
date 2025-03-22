#include "chunk.h"

// Copyright [2025] <Andrei Riciu>

int is_in_chunk(int width, int height, int depth, int x, int y, int z) {
    if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth)
        return 1;
    return 0;
}
char*** chunk_place_block(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    char block
) {
    if (is_in_chunk(width, height, depth, x, y, z))
        chunk[x][y][z] = block;
    return chunk;
}
int mini(int x, int y) {
    if (x < y)
        return x;
    return y;
}
int maxi(int x, int y) {
    if (x > y)
        return x;
    return y;
}
char*** chunk_fill_cuboid(
    char*** chunk, int width, int height, int depth, int x0, int y0, int z0,
    int x1, int y1, int z1, char block
) {
    for (int x = mini(x0, x1); x <= maxi(x0, x1); x++)
        for (int y = mini(y0, y1); y <= maxi(y0, y1); y++)
            for (int z = mini(z0, z1); z <= maxi(z0, z1); z++)
                chunk = chunk_place_block(
                    chunk, width, height, depth, x, y, z, block
                );
    return chunk;
}
char*** chunk_fill_sphere(
    char*** chunk, int width, int height, int depth, int x, int y, int z,
    double radius, char block
) {
    for (int x0 = 0; x0 < width; x0++)
        for (int y0 = 0; y0 < height; y0++)
            for (int z0 = 0; z0 < depth; z0++) {
                double dist =
                    sqrt(pow(x - x0, 2) + pow(y - y0, 2) + pow(z - z0, 2));
                if (dist <= radius)
                    chunk = chunk_place_block(
                        chunk, width, height, depth, x0, y0, z0, block
                    );
            }
    return chunk;
}
