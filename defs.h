#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long U64;

#define NAME "Garry Chess Engine v0.1"
#define BRD_SQ_NUM 120

enum piece {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum file {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum rank {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};
enum color {WHITE, BLACK, BOTH};

// Board representation
enum square {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
}


typedef struct board {
        
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];
    int king_sq[2];

    int side;
    int en_passant;
    int fifty_counter; // fifty move rule counter

    int ply; // how many half-moves we're into the current search
    int his_ply; // in the total game so far, how many half-moves have been played

    U64 pos_key; // unique key generated for each position

    int pcs_num[13]; // how many of each piece type are on the board
    int big_pcs[3]; // any piece that isn't a pawn
    int maj_pcs[3]; // major pieces -- rooks and queens
    int min_pcs[3]; // minor pieces -- knights and bishops

} board_t;

#endif







