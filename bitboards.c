#include <stdio.h>
#include "init.h"
#include "defs.h"

// This is magic, see below
const int bit_table[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61,
    29, 2, 51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40,
    4, 49, 5, 52, 26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59,
    14, 12, 55, 38, 28, 58, 20, 37, 17, 36, 8
};

// Takes the first bit starting at the least significant bit
// returns the index that this bit was set at (so we know the square)
// and sets that bit to zero
// This shit is probably magic and I have no idea how it works.
// Check out these links for some idea:
// https://www.chessprogramming.org/Matt_Taylor
// https://www.chessprogramming.org/BitScan
// https://stackoverflow.com/questions/30680559/how-to-find-magic-bitboards
// https://groups.google.com/g/comp.lang.asm.x86/c/3pVGzQGb1ys
// This is apparently just a very fast way to find the LSB --
// even Stockfish uses this.
// I still can't figure out how these magic numbers are determined,
// but it seems like Matt Taylor doesn't know either.
int pop_bit(U64 *bb) {
    U64 b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
    *bb &= (*bb - 1);
    return bit_table[(fold * 0x783a9b23) >> 26];
}


/* count_bits: counts the number of 1 bits in a bitboard
 *
 * bb: a bitboard
 *
 * returns: the number of 1 bits
 */
int count_bits(U64 bb) {
    for (int r = 0; bb; r++, b &= b - 1);
    return r;
}

void print_bitboard(U64 bb) {
    U64 shift = 1ULL;

    int sq = 0;
    int sq64 = 0;

    printf("\n");

    for (int rank = RANK_8; rank >= RANK_1; rank--) {
        for (int file = FILE_A; file <= FILE_H; file++) {
            sq = fr_to_sq(file, rank); // 120 based
            sq64 = sq120_to_64[sq]; // 64 based
            if (bb & (shift << sq64)) {
                printf("X");
            } else {
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}
