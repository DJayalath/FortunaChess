#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Board orientation a1-h1 = bottom row

// Numbered constants for piece types
const uint8_t W_PAWN = 1;
const uint8_t W_KNIGHT = 2;
const uint8_t W_BISHOP = 3;
const uint8_t W_ROOK = 4;
const uint8_t W_QUEEN = 5;
const uint8_t W_KING = 6;

const uint8_t B_PAWN = 7;
const uint8_t B_KNIGHT = 8;
const uint8_t B_BISHOP = 9;
const uint8_t B_ROOK = 10;
const uint8_t B_QUEEN = 11;
const uint8_t B_KING = 12;

// Bit masks for excluding A and H files in east/west pushes
const uint64_t NOT_A_FILE = ~0x8080808080808080;
const uint64_t NOT_H_FILE = ~0x0101010101010101;


// Single pushes
uint64_t one_north(uint64_t b) { return b << 8; }                
uint64_t one_south(uint64_t b) { return b >> 8; }                
                                                                 
uint64_t one_east(uint64_t b) { return (b >> 1) & NOT_A_FILE; }  
uint64_t one_neast(uint64_t b) { return (b << 7) & NOT_A_FILE; } 
uint64_t one_seast(uint64_t b) { return (b >> 9) & NOT_A_FILE; } 
                                                                 
uint64_t one_west(uint64_t b) { return (b << 1) & NOT_H_FILE; }  
uint64_t one_nwest(uint64_t b) { return (b << 9) & NOT_H_FILE; } 
uint64_t one_swest(uint64_t b) { return (b >> 7) & NOT_H_FILE; } 


// Bit boards where orientation places a1-a8 on bottom row
struct bitboards {                           
    uint64_t w_k, w_q, w_r, w_b, w_n, w_p, w; 
    uint64_t b_k, b_q, b_r, b_b, b_n, b_p, b; 
};                                           

uint8_t idx(char file, uint8_t rnk);
void init_bbs(uint8_t* squares, bitboards* bb);
void print_bb(uint64_t bitboard);

int main() {
    
    uint8_t* squares = (uint8_t*) calloc(64, sizeof(uint8_t));

    // Set initial squares of pieces
    for (char i = 'a'; i <= 'h'; i++) {
        squares[idx(i, 2)] = W_PAWN;
        squares[idx(i, 7)] = B_PAWN;
    }
    squares[idx('a', 1)] = W_ROOK;
    squares[idx('b', 1)] = W_KNIGHT;
    squares[idx('c', 1)] = W_BISHOP;
    squares[idx('d', 1)] = W_QUEEN;
    squares[idx('e', 1)] = W_KING;
    squares[idx('f', 1)] = W_BISHOP;
    squares[idx('g', 1)] = W_KNIGHT;
    squares[idx('h', 1)] = W_ROOK;

    squares[idx('a', 8)] = B_ROOK;
    squares[idx('b', 8)] = B_KNIGHT;
    squares[idx('c', 8)] = B_BISHOP;
    squares[idx('d', 8)] = B_QUEEN;
    squares[idx('e', 8)] = B_KING;
    squares[idx('f', 8)] = B_BISHOP;
    squares[idx('g', 8)] = B_KNIGHT;
    squares[idx('h', 8)] = B_ROOK;

    // Initialise bitboards
    bitboards bb;
    memset(&bb, 0, sizeof(bitboards));

    init_bbs(squares, &bb);

    print_bb(bb.w_p);
    printf("\n");
    print_bb(one_swest(bb.w_p));
    printf("\n");

}

void print_bb(uint64_t bitboard) {
    for (int i = 0; i < 64; i++) {
       if (i % 8 == 0) printf("\n");
       printf("%d", (int) ((bitboard >> (63 - i)) & 1));
    }
}

uint8_t idx(char file, uint8_t rnk) {
    return (8 - rnk) * 8 + (file - 'a'); 
}

void init_bbs(uint8_t* squares, bitboards* bb) {
    
    for (uint8_t i = 0; i < 64; i++) {
        
        if (squares[i] == W_PAWN)
            bb->w_p |= 1 << (63 - i);
        if (squares[i] == W_KNIGHT)
            bb->w_n |= 1 << (63 - i);
        if (squares[i] == W_BISHOP)
            bb->w_b |= 1 << (63 - i);
        if (squares[i] == W_ROOK)
            bb->w_r |= 1 << (63 - i);
        if (squares[i] == W_QUEEN)
            bb->w_q |= 1 << (63 - i);
        if (squares[i] == W_KING)
            bb->w_k |= 1 << (63 - i);

        if (squares[i] == B_PAWN)
            bb->b_p |= 1 << (63 - i);
        if (squares[i] == B_KNIGHT)
            bb->b_n |= 1 << (63 - i);
        if (squares[i] == B_BISHOP)
            bb->b_b |= 1 << (63 - i);
        if (squares[i] == B_ROOK)
            bb->b_r |= 1 << (63 - i);
        if (squares[i] == B_QUEEN)
            bb->b_q |= 1 << (63 - i);
        if (squares[i] == B_KING)
            bb->b_k |= 1 << (63 - i);

    }

    bb->w = bb->w_p | bb->w_n | bb->w_b | bb->w_r | bb->w_q | bb->w_k;
    bb->b = bb->b_p | bb->b_n | bb->b_b | bb->b_r | bb->b_q | bb->b_k;

}


