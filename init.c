#include "defs.h"
#include "init.h"

int sq120_to_64[BRD_SQ_NUM];
int sq64_to_120[64];

U64 set_mask[64];
U64 clear_mask[64];

int fr_to_sq(int f, int r) {
    return (21 + f) + (r * 10);
}

void init_sq120_to_64() {
    enum file file = FILE_A;
    enum rank rank = RANK_1;
    enum square sq = A1;
    int sq64 = 0;
    // Failsafe checking (should never be 64; goes 0 - 63)
    for (int i = 0; i < BRD_SQ_NUM; ++i) {
        sq120_to_64[i] = 64; 
    }
    // Failsafe checking (should never be 120; goes 0 - 119)
    for (int i = 0; i < 64; ++i) {
        sq64_to_120[i] = 120;
    }
    for (rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq = fr_to_sq(file, rank);
            sq64_to_120[sq64] = sq;
            sq120_to_64[sq] = sq64;
            sq64++;
        }
    }
}

void all_init() {
    init_sq120_to_64();
    return; 
}
