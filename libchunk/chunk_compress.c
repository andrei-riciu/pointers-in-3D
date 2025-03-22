#include "chunk.h"
const int SIX = 6, EIGHT = 8, MASK1 = 0b111100000000, MASK2 = 0b11111111,
          BYTE = 32, nr4095 = 4095, nr255 = 255, fifteen = 15;

// Copyright [2025] <Andrei Riciu>

unsigned char*
    chunk_encode(char*** chunk, int width, int height, int depth, int* length) {
    int less = 0, more = 0, count = 0;
    char block = chunk[0][0][0];
    for (int y = 0; y < height; y++)
        for (int z = 0; z < depth; z++)
            for (int x = 0; x < width; x++) {
                if (chunk[x][y][z] != block) {
                    if (count < BYTE) {
                        less++;
                    } else if (count <= nr4095) {
                        more++;
                    } else {
                        more += count / nr4095;
                        int rest = count % nr4095;
                        if (rest > 0 && rest < BYTE)
                            less++;
                        else if (rest > 0)
                            more++;
                    }
                    count = 1;
                } else {
                    count++;
                }
                block = chunk[x][y][z];
            }
    if (count < BYTE) {
        less++;
    } else if (count <= nr4095) {
        more++;
    } else {
        more += count / nr4095;
        int rest = count % nr4095;
        if (rest > 0 && rest < BYTE)
            less++;
        else if (rest > 0)
            more++;
    }
    *length = less + more * 2;
    unsigned char* encoded = malloc(*length * sizeof(char));
    int poz = 0;
    count = 0;
    block = chunk[0][0][0];
    for (int y = 0; y < height; y++)
        for (int z = 0; z < depth; z++)
            for (int x = 0; x < width; x++) {
                if (chunk[x][y][z] != block) {
                    if (count < BYTE) {
                        encoded[poz] = (char) ((block << SIX) + count);
                        poz++;
                    } else if (count <= nr4095) {
                        encoded[poz] =
                            (char) ((block << SIX) + ((count & MASK1) >> EIGHT)
                                    + BYTE);
                        encoded[poz + 1] = (char) (count & MASK2);
                        poz += 2;
                    } else {
                        while (count > nr4095) {
                            encoded[poz] =
                                (char) ((block << SIX) + 3 * (1 + 4) + BYTE);
                            encoded[poz + 1] = (char) (nr255);
                            poz += 2;
                            count -= nr4095;
                        }
                        if (count > 0) {
                            if (count < BYTE) {
                                encoded[poz] = (char) ((block << SIX) + count),
                                poz++;
                            } else {
                                encoded[poz] =
                                    (char) ((block << SIX)
                                            + ((count & MASK1) >> EIGHT)
                                            + BYTE);
                                encoded[poz + 1] = (char) (count & MASK2);
                                poz += 2;
                            }
                        }
                    }
                    count = 1;
                } else {
                    count++;
                }
                block = chunk[x][y][z];
            }
    if (count < BYTE) {
        encoded[poz] = (char) ((block << SIX) + count);
        poz++;
    } else if (count <= nr4095) {
        encoded[poz] =
            (char) ((block << SIX) + ((count & MASK1) >> EIGHT) + BYTE);
        encoded[poz + 1] = (char) (count & MASK2);
        poz += 2;
    } else {
        while (count > nr4095) {
            encoded[poz] = (char) ((block << SIX) + 3 * (4 + 1) + BYTE);
            encoded[poz + 1] = (char) (nr255);
            poz += 2;
            count -= nr4095;
        }
        if (count > 0) {
            if (count < BYTE) {
                encoded[poz] = (char) ((block << SIX) + count), poz++;
            } else {
                encoded[poz] =
                    (char) ((block << SIX) + ((count & MASK1) >> EIGHT) + BYTE);
                encoded[poz + 1] = (char) (count & MASK2);
                poz += 2;
            }
        }
    }
    return encoded;
}
int is_double(unsigned char c) {
    if (c & BYTE)
        return 1;
    return 0;
}
char*** chunk_decode(unsigned char* code, int width, int height, int depth) {
    char*** chunk = chunk_init(width, height, depth);
    int i = 0, number_of_blocks = 0, x = 0, y = 0, z = 0;
    while (i < (int) strlen(code)) {
        char type_of_block = (char) ((code[i] >> SIX) & 0b11);
        if (is_double(code[i])) {
            number_of_blocks = ((fifteen & code[i]) << EIGHT) + code[i + 1];
            i++;
        } else {
            number_of_blocks = (BYTE - 1) & code[i];
        }
        i++;
        int j = 0;
        while (j < number_of_blocks) {
            chunk[x][y][z] = type_of_block;
            if (x < width - 1) {
                x++;
            } else if (x == width - 1) {
                x = 0;
                if (z < depth - 1)
                    z++;
                else if (z == depth - 1)
                    z = 0, y++;
            }
            j++;
        }
    }
    return chunk;
}
