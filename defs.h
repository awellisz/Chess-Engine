#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

typedef unsigned long long U64;

#define NAME "Garry Chess v0.1"
#define BRD_SQ_NUM 120

#define MAX_GAME_MOVES 2048 // 2048 half-moves

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
};

// Castling permissions for each side, represented by a 4-bit number
// e.g. 0 0 1 0 means white cannot castle kingside or queenside, black 
// can castle kingside but not queenside
enum castle { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

typedef struct {
    int move; // the move itself
    int castle_perms; // castle permissions before the move was played
    int en_passant; // en passant square if set
    int fifty_counter; // fifty move rule counter
    U64 pos_key; // position key

} undo_t;

typedef struct {
        
    int pieces[BRD_SQ_NUM];
    U64 pawns[3];
    int king_sq[2];

    int side;
    int en_passant;
    int fifty_move; // fifty move rule counter

    int ply; // how many half-moves we're into the current search
    int his_ply; // in the total game so far, how many half-moves have been played

    int castle_perms; // castling permissions (castle enum)

    U64 pos_key; // unique key generated for each position

    int pcs_num[13]; // how many of each piece type are on the board
    int big_pcs[3]; // any piece that isn't a pawn
    int maj_pcs[3]; // major pieces -- rooks and queens
    int min_pcs[3]; // minor pieces -- knights and bishops

    undo_t history[MAX_GAME_MOVES];
    // every time a move is made on the board, we will store in this array
    // the move about to be made, the castle permission before the move
    // was made, the en passant square, 50 move status, and the unique 
    // key before the move was made.
    // This is indexed by his_ply.
    // This history array can be used also to determine 3-fold repetitions

    // Piece list
    // One for each piece type (13) and up to 10 different pieces of 
    // each piece at one time (e.g. 2 rooks and all 8 pawns 
    // promote to rooks)
    int p_list[13][10]; 
    // e.g. a white knight on E1 looks like p_list[wN][0] = E1;
    // another white knight on F6 looks like p_list[wN][1] = F6;
    // if the piece list contains NO_SQ, we know we've reached the end,
    // so no need to keep looking for a particular piece type
    // This is overall faster than iterating over every 
    // square on the board.
} board_t;


// Convert from 64 square board representation to 12- square board
// representation, and vice versa
extern int sq120_to_64[BRD_SQ_NUM];
extern int sq64_to_120[64];

#endif







