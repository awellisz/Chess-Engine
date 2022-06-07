#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "defs.h"
#include "bitboards.h"
#include "init.h"

int main() {
    all_init();

    for (int i = 0; i < BRD_SQ_NUM; i++) {
        if (i % 10 == 0) printf("\n");
        printf("%5d",sq120_to_64[i]);
    }

    printf("\n\n");
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) printf("\n");
        printf("%5d", sq64_to_120[i]);
    }

    // Testing printing the bitboard
    U64 play_bitboard = 0ULL;
    printf("Start:\n\n");
    print_bitboard(play_bitboard);

    play_bitboard |= (1ULL << sq120_to_64[D2]);

    printf("End:\n\n");
    print_bitboard(play_bitboard);

    printf("\n");
    return 0;
}
