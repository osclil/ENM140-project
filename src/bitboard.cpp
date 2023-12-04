#include <iostream>
#include <string>

#include "bitboard.h"

// Leaper Functions
uint64_t Bitboard::init_pawn_attacks(Color color, uint8_t square) {
    uint64_t attacks = 0ULL;
    uint64_t pawn = 1ULL << square;

    if (color == Color::WHITE)
        attacks |= up_left(pawn) | up_right(pawn); 
    else
        attacks |= down_left(pawn) | down_right(pawn);

    return attacks & m_allowed_squares;
}

uint64_t Bitboard::init_knight_attacks(uint8_t square) {
    uint64_t attacks = 0ULL;
    uint64_t knight = 1ULL << square;

    // attacks |= ((knight << 15) | (knight >> 17)) & NOT_A_FILE;
    // attacks |= ((knight << 17) | (knight >> 15)) & NOT_H_FILE;
    // attacks |= ((knight >> 10) | (knight << 6)) & NOT_A_OR_B_FILE;
    // attacks |= ((knight << 10) | (knight >> 6)) & NOT_G_OR_H_FILE;

    attacks |= (up_left(up(knight)) | up_right(up(knight)) | 
                down_left(down(knight)) | down_right(down(knight)) |
                up_left(left(knight)) | down_left(left(knight)) |
                up_right(right(knight)) | down_right(right(knight)));

    return attacks & m_allowed_squares;
}

uint64_t Bitboard::init_king_attacks(uint8_t square) {
    uint64_t attacks = 0ULL;
    uint64_t king = 1ULL << square;

    // attacks |= (king << 1) & NOT_H_FILE;    // Left
    // attacks |= king << 8;                   // Up
    // attacks |= (king >> 1) & NOT_A_FILE;    // Right
    // attacks |= king >> 8;                   // Down

    // attacks |= (king << 7) & NOT_A_FILE;    // Up right
    // attacks |= (king >> 7) & NOT_H_FILE;    // Down left
    // attacks |= (king << 9) & NOT_H_FILE;    // Up left
    // attacks |= (king >> 9) & NOT_A_FILE;    // Down right

    attacks |= (up(king) | down(king) | left(king) | right(king) | 
                up_left(king) | up_right(king) | down_left(king) | down_right(king));

    return attacks & m_allowed_squares;
}

void Bitboard::init_leaper_attacks() {
    for (uint8_t i = 0; i < 64; i++){
        pawn_attacks[0][i] = init_pawn_attacks(Color::WHITE, i);
        pawn_attacks[1][i] = init_pawn_attacks(Color::BLACK, i);
        knight_attacks[i] = init_knight_attacks(i);
        king_attacks[i] = init_king_attacks(i);
    }
}

// Slider Functions
uint64_t Bitboard::init_bishop_attacks(uint8_t square) {
    uint64_t attacks = 0ULL;

    int x = square % 8;
    int y = square / 8;

    for (int i = x+1, j = y+1; i < 8 && j < 8; i++, j++) {
        set_bit(attacks, j*8+i);
    }

    for (int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++) {
        set_bit(attacks ,j*8+i);
    }

    for (int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--) {
        set_bit(attacks, j*8+i);
    }

    for (int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) {
        set_bit(attacks, j*8+i);
    }

    return attacks & m_allowed_squares;
}

uint64_t Bitboard::init_rook_attacks(uint8_t square) {
    uint64_t attacks = 0ULL;

    int x = square % 8;
    int y = square / 8;
    
    for (int i = x+1; i < 8; i++) {
        set_bit(attacks, y*8+i);
    }

    for (int i = x-1; i >= 0; i--) {
        set_bit(attacks, y*8+i);
    }

    for (int i = y+1; i < 8; i++) {
        set_bit(attacks, i*8+x);
    }

    for (int i = y-1; i >= 0; i--) {
        set_bit(attacks, i*8+x);
    }

    return attacks & m_allowed_squares;
}

void Bitboard::init_slider_attacks() {
    for (uint8_t i = 0; i < 64; i++) {
        bishop_attacks[i] = init_bishop_attacks(i);
        rook_attacks[i] = init_rook_attacks(i);
    }
}

// Attack with blockers
uint64_t Bitboard::bishop_attacks_with_blockers(uint8_t square, uint64_t blockers) {
    uint64_t attacks = 0ULL;

    int x = square % 8;
    int y = square / 8;

    for (int i = x+1, j = y+1; i < 8 && j < 8; i++, j++) {
        set_bit(attacks, j*8+i);
        if (get_bit(blockers, j*8+i)) break;
    }

    for (int i = x-1, j = y+1; i >= 0 && j < 8; i--, j++) {
        set_bit(attacks ,j*8+i);
        if (get_bit(blockers, j*8+i)) break;
    }

    for (int i = x+1, j = y-1; i < 8 && j >= 0; i++, j--) {
        set_bit(attacks, j*8+i);
        if (get_bit(blockers, j*8+i)) break;
    }

    for (int i = x-1, j = y-1; i >= 0 && j >= 0; i--, j--) {
        set_bit(attacks, j*8+i);
        if (get_bit(blockers, j*8+i)) break;
    }

    return attacks & m_allowed_squares;
}

uint64_t Bitboard::rook_attacks_with_blockers(uint8_t square, uint64_t blockers) {
    uint64_t attacks = 0ULL;

    int x = square % 8;
    int y = square / 8;
    
    for (int i = x+1; i < 8; i++) {
        set_bit(attacks, y*8+i);
        if (get_bit(blockers, y*8+i)) break;
    }

    for (int i = x-1; i >= 0; i--) {
        set_bit(attacks, y*8+i);
        if (get_bit(blockers, y*8+i)) break;
    }

    for (int i = y+1; i < 8; i++) {
        set_bit(attacks, i*8+x);
        if (get_bit(blockers, i*8+x)) break;
    }

    for (int i = y-1; i >= 0; i--) {
        set_bit(attacks, i*8+x);
        if (get_bit(blockers, i*8+x)) break;
    }

    return attacks & m_allowed_squares;
}


int main(){
    Bitboard b(8, 8);
    b.init_leaper_attacks();
    b.init_slider_attacks();
    b.print_bitboard(b.rook_attacks[3]);
}