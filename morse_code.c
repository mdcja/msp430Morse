/* author: Julian Martinez del Campo
 * class : CMPT 464
 * date  : October 17, 2014
 *
 * Implements morse_code.h and provides definitions for the morse code
 * characters.
 */
#include <stdlib.h>
#include "morse_code.h"

#define BITS 7

/* The letters of the alphabet in morse code
 */
const morse_code_t letter_a = { 0x40, 2 };     /* .-     => 01   => 01000000 => 0x40 */ 
const morse_code_t letter_b = { 0x80, 4 };     /* -...   => 1000 => 10000000 => 0x80 */
const morse_code_t letter_c = { 0xA0, 4 };     /* -.-.   => 1010 => 10100000 => 0xA0 */
const morse_code_t letter_d = { 0x80, 3 };     /* -..    => 100  => 10000000 => 0x80 */
const morse_code_t letter_e = { 0x00, 1 };     /* .      => 0    => 00000000 => 0x00 */
const morse_code_t letter_f = { 0x20, 4 };     /* ..-.   => 0010 => 00100000 => 0x20 */
const morse_code_t letter_g = { 0xC0, 3 };     /* --.    => 110  => 11000000 => 0xC0 */
const morse_code_t letter_h = { 0x00, 4 };     /* ....   => 0000 => 00000000 => 0x00 */
const morse_code_t letter_i = { 0x00, 2 };     /* ..     => 00   => 00000000 => 0x00 */
const morse_code_t letter_j = { 0x70, 4 };     /* .---   => 0111 => 01110000 => 0x70 */
const morse_code_t letter_k = { 0xA0, 3 };     /* -.-    => 101  => 10100000 => 0xA0 */
const morse_code_t letter_l = { 0x40, 4 };     /* .-..   => 0100 => 01000000 => 0x40 */
const morse_code_t letter_m = { 0xC0, 2 };     /* --     => 11   => 11000000 => 0xC0 */
const morse_code_t letter_n = { 0x80, 2 };     /* -.     => 10   => 10000000 => 0x80 */
const morse_code_t letter_o = { 0xE0, 3 };     /* ---    => 111  => 11100000 => 0xE0 */
const morse_code_t letter_p = { 0x60, 4 };     /* .--.   => 0110 => 01100000 => 0x60 */
const morse_code_t letter_q = { 0xD0, 4 };     /* --.-   => 1101 => 11010000 => 0xD0 */
const morse_code_t letter_r = { 0x40, 3 };     /* .-.    => 010  => 01000000 => 0x40 */
const morse_code_t letter_s = { 0x00, 3 };     /* ...    => 000  => 00000000 => 0x00 */
const morse_code_t letter_t = { 0x80, 1 };     /* -      => 1    => 10000000 => 0x80 */
const morse_code_t letter_u = { 0x20, 3 };     /* ..-    => 001  => 00100000 => 0x20 */
const morse_code_t letter_v = { 0x10, 4 };     /* ...-   => 0001 => 00010000 => 0x10 */
const morse_code_t letter_w = { 0x60, 3 };     /* .--    => 011  => 01100000 => 0x60 */
const morse_code_t letter_x = { 0x90, 4 };     /* -..-   => 1001 => 10010000 => 0x90 */
const morse_code_t letter_y = { 0xB0, 4 };     /* -.--   => 1011 => 10110000 => 0xB0 */
const morse_code_t letter_z = { 0xC0, 4 };     /* --..   => 1100 => 11000000 => 0xC0 */

/* Numbers in morse code
 */
const morse_code_t number_1 = { 0x78, 5 };     /* .----  => 01111 => 01111000 => 0x78 */
const morse_code_t number_2 = { 0x38, 5 };     /* ..---  => 00111 => 00111000 => 0x38 */
const morse_code_t number_3 = { 0x18, 5 };     /* ...--  => 00011 => 00011000 => 0x18 */
const morse_code_t number_4 = { 0x08, 5 };     /* ....-  => 00001 => 00001000 => 0x08 */
const morse_code_t number_5 = { 0x00, 5 };     /* .....  => 00000 => 00000000 => 0x00 */
const morse_code_t number_6 = { 0x80, 5 };     /* -....  => 10000 => 10000000 => 0x80 */
const morse_code_t number_7 = { 0xC0, 5 };     /* --...  => 11000 => 11000000 => 0xC0 */
const morse_code_t number_8 = { 0xE0, 5 };     /* ---..  => 11100 => 11100000 => 0xE0 */
const morse_code_t number_9 = { 0xF0, 5 };     /* ----.  => 11110 => 11110000 => 0xF0 */
const morse_code_t number_0 = { 0xF8, 5 };     /* -----  => 11111 => 11111000 => 0xF8 */

/* Punctuation marks and miscellaneous signs
 */
const morse_code_t misc_period =     { 0x54, 6 };   /* .-.-.-  => 010101 => 01010100 => 0x54 */
const morse_code_t misc_comma =      { 0xCC, 6 };   /* --..--  => 110011 => 11001100 => 0xCC */
const morse_code_t misc_question =   { 0x30, 6 };   /* ..--..  => 001100 => 00110000 => 0x30 */
const morse_code_t misc_apostrophe = { 0x78, 6 };   /* .----.  => 011110 => 01111000 => 0x78 */
const morse_code_t misc_dash =       { 0x84, 6 };   /* -....-  => 100001 => 10000100 => 0x84 */

const morse_code_t misc_dot =        { 0x00, 1 };   /* .       => 0      => 00000000 => 0x00 */

int8_t morse_code_get_value( const morse_code_t * character, uint8_t position )
{
    if( ! character )
        return -1;

    if( position > character->length )
        return -1;

    return (int8_t) (( (character->character) >> (BITS - position)) & 0x01);
}

const morse_code_t * morse_code_get( uint8_t character )
{
    switch( character )
    {
        case 'a':
        case 'A':
            return &letter_a; 
            break;

        case 'b':
        case 'B':
            return &letter_b;
            break;

        case 'c':
        case 'C':
            return &letter_c;
            break;

        case 'd':
        case 'D':
            return &letter_d;
            break;

        case 'e':
        case 'E':
            return &letter_e;
            break;

        case 'f':
        case 'F':
            return &letter_f;
            break;

        case 'g':
        case 'G':
            return &letter_g;
            break;

        case 'h':
        case 'H':
            return &letter_h;
            break;

        case 'i':
        case 'I':
            return &letter_i;
            break;

        case 'j':
        case 'J':
            return &letter_j;
            break;

        case 'k':
        case 'K':
            return &letter_k;
            break;

        case 'l':
        case 'L':
            return &letter_l;
            break;

        case 'm':
        case 'M':
            return &letter_m;
            break;

        case 'n':
        case 'N':
            return &letter_n;
            break;

        case 'o':
        case 'O':
            return &letter_o;
            break;

        case 'p':
        case 'P':
            return &letter_p;
            break;

        case 'q':
        case 'Q':
            return &letter_q;
            break;

        case 'r':
        case 'R':
            return &letter_r;
            break;

        case 's':
        case 'S':
            return &letter_s;
            break;

        case 't':
        case 'T':
            return &letter_t;
            break;

        case 'u':
        case 'U':
            return &letter_u;
            break;

        case 'v':
        case 'V':
            return &letter_v;
            break;

        case 'w':
        case 'W':
            return &letter_w;
            break;

        case 'x':
        case 'X':
            return &letter_x;
            break;
        
        case 'y':
        case 'Y':
            return &letter_y;
            break;

        case 'z':
        case 'Z':
            return &letter_z;
            break;

        case '1':
            return &number_1;
            break;

        case '2':
            return &number_2;
            break;

        case '3':
            return &number_3;
            break;

        case '4':
            return &number_4;
            break;

        case '5':
            return &number_5;
            break;
        
        case '6':
            return &number_6;
            break;

        case '7':
            return &number_7;
            break;

        case '8':
            return &number_8;
            break;

        case '9':
            return &number_9;
            break;

        case '0':
            return &number_0;
            break;

        case '.':
            return &misc_period;
            break;

        case ',':
            return &misc_comma;
            break;

        case '?':
            return &misc_question;
            break;
        
        case '\'':
            return &misc_apostrophe;
            break;

        case '-':
            return &misc_dash;
            break;

        case ' ':
            return &misc_dot;
            break;

        default:
            return NULL;
            break;
    }
}
