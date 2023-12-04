#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>
#include <string>

// Macros
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? (bitboard ^= (1ULL << square)) : 0)
#define count_bits(bitboard) __builtin_popcountll(bitboard)
#define get_LSB(bitboard) __builtin_ctzll(bitboard)
#define get_MSB(bitboard) (63 - __builtin_clzll(bitboard))

#define up(bitboard) (bitboard << 8)
#define down(bitboard) (bitboard >> 8)
#define left(bitboard) ((bitboard & NOT_A_FILE) << 1)
#define right(bitboard) ((bitboard & NOT_H_FILE) >> 1)
#define up_left(bitboard) ((bitboard & NOT_A_FILE) << 9)
#define up_right(bitboard) ((bitboard & NOT_H_FILE) << 7)
#define down_left(bitboard) ((bitboard & NOT_A_FILE) >> 7)
#define down_right(bitboard) ((bitboard & NOT_H_FILE) >> 9)


// Constants
const uint64_t RANK_1 = 0x00000000000000FFULL;
const uint64_t RANK_2 = 0x000000000000FF00ULL;
const uint64_t RANK_3 = 0x0000000000FF0000ULL;
const uint64_t RANK_4 = 0x00000000FF000000ULL;
const uint64_t RANK_5 = 0x000000FF00000000ULL;
const uint64_t RANK_6 = 0x0000FF0000000000ULL;
const uint64_t RANK_7 = 0x00FF000000000000ULL;
const uint64_t RANK_8 = 0xFF00000000000000ULL;

const uint64_t FILE_H = 0x0101010101010101ULL;
const uint64_t FILE_G = 0x0202020202020202ULL;
const uint64_t FILE_F = 0x0404040404040404ULL;
const uint64_t FILE_E = 0x0808080808080808ULL;
const uint64_t FILE_D = 0x1010101010101010ULL;
const uint64_t FILE_C = 0x2020202020202020ULL;
const uint64_t FILE_B = 0x4040404040404040ULL;
const uint64_t FILE_A = 0x8080808080808080ULL;

const uint64_t NOT_H_FILE = 0xfefefefefefefefeULL;
const uint64_t NOT_A_FILE = 0x7f7f7f7f7f7f7f7fULL;
const uint64_t NOT_G_OR_H_FILE = 0xfcfcfcfcfcfcfcfcULL;
const uint64_t NOT_A_OR_B_FILE = 0x3f3f3f3f3f3f3f3fULL;

const uint64_t NOT_RANK_1 = 0xFFFFFFFFFFFFFF00ULL;
const uint64_t NOT_RANK_1_OR_2 = 0xFFFFFFFFFFFF0000ULL;
const uint64_t NOT_RANK_8 = 0x00ffffffffffffffULL;
const uint64_t NOT_RANK_7_OR_8 = 0x00ffffffffffff00ULL;

const uint64_t WHITE_SQUARES = 0x55AA55AA55AA55AAULL;
const uint64_t BLACK_SQUARES = 0xAA55AA55AA55AA55ULL;


// Enumerations
enum class Color : uint8_t
{
    WHITE,
    BLACK
};

enum class Piece : uint8_t
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Bitboard class
class Bitboard {
public:
    Bitboard(uint8_t height, uint8_t width) : m_height(height), m_width(width) {
        m_board = new uint64_t*[m_height];
        for (uint8_t i = 0; i < m_height; i++) {
            m_board[i] = new uint64_t[m_width];
            for (uint8_t j = 0; j < m_width; j++) {
                m_board[i][j] = 0ULL;
            }
        }

        switch (height) {
            case 8:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3 | RANK_4 | RANK_5 | RANK_6 | RANK_7 | RANK_8;
                break;
            case 7:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3 | RANK_4 | RANK_5 | RANK_6 | RANK_7;
                break;
            case 6:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3 | RANK_4 | RANK_5 | RANK_6;
                break;
            case 5:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3 | RANK_4 | RANK_5;
                break;
            case 4:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3 | RANK_4;
                break;
            case 3:
                m_allowed_ranks = RANK_1 | RANK_2 | RANK_3;
                break;
            case 2:
                m_allowed_ranks = RANK_1 | RANK_2;
                break;
            case 1:
                m_allowed_ranks = RANK_1;
                break;
            default:
                break;
        }

        switch (width) {
            case 8:
                m_allowed_files = FILE_A | FILE_B | FILE_C | FILE_D | FILE_E | FILE_F | FILE_G | FILE_H;
                break;
            case 7:
                m_allowed_files = FILE_B | FILE_C | FILE_D | FILE_E | FILE_F | FILE_G | FILE_H;
                break;
            case 6:
                m_allowed_files = FILE_C | FILE_D | FILE_E | FILE_F | FILE_G | FILE_H;
                break;
            case 5:
                m_allowed_files = FILE_D | FILE_E | FILE_F | FILE_G | FILE_H;
                break;
            case 4:
                m_allowed_files = FILE_E | FILE_F | FILE_G | FILE_H;
                break;
            case 3:
                m_allowed_files = FILE_F | FILE_G | FILE_H;
                break;
            case 2:
                m_allowed_files = FILE_G | FILE_H;
                break;
            case 1:
                m_allowed_files = FILE_H;
                break;
            default:
                break;
        }
        
        m_allowed_squares = m_allowed_ranks & m_allowed_files;
    }

    ~Bitboard() {
        for (uint8_t i = 0; i < m_height; i++) {
            delete[] m_board[i];
        }
        delete[] m_board;
    }

    // Initialization functions
    void init_leaper_attacks();

    void print_bitboard(uint64_t bitboard) {
        for (int i = 7; i >= 0; i--) {
            for (int j = 7; j>= 0; j--) {
                std::cout << (get_bit(bitboard, i*8+j)!=0) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Attack tables
    uint64_t pawn_attacks[2][64];
    uint64_t knight_attacks[64];
    uint64_t king_attacks[64];
    uint64_t bishop_attacks[64];
    uint64_t rook_attacks[64];

    uint8_t m_height;
    uint8_t m_width;
    uint64_t** m_board;
    uint64_t m_allowed_files;
    uint64_t m_allowed_ranks;
    uint64_t m_allowed_squares;

private:
   
    // Attack functions
    uint64_t init_pawn_attacks(Color color, uint8_t square);
    uint64_t init_knight_attacks(uint8_t square);
    uint64_t init_king_attacks(uint8_t square);
};

#endif // BITBOARD_H