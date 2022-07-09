#include "moves.h"

int Moves::encodeMove(int endSqr, int stSqr, int flag, int pieceMoved, int pieceCaptured)
{
    // 00000    00000    0000    000000    000000
    // 25..21   20..16   15..12  11..6     5..0

    int move = endSqr; // bits 0-5

    move |= stSqr << 6; // bits 6-11

    move |= flag << 12; // bits 12-15

    move |= pieceMoved << 16; // bits 16-20 (16-18 -> piece type, 19-20 -> piece colour)

    move |= pieceCaptured << 21; // bits 21-25 (21-23 -> piece type, 24-25 -> piece colour)

    // NOTE: bits 26-31 are unused space.

    return move;
}

Moves::outputMove Moves::decodeMove(int move)
{
    int endSqr, stSqr, flag, pieceMoved, pieceCaptured;

    unsigned mask;
    mask = (1 << 6) - 1;
    endSqr = move & mask;

    mask = ((1 << 6) - 1) << 6;
    stSqr = (move & mask) >> 6;

    mask = ((1 << 4) - 1) << 12;
    flag = (move & mask) >> 12;

    mask = ((1 << 5) - 1) << 16;
    pieceMoved = (move & mask) >> 16;

    mask = ((1 << 5) - 1) << 21;
    pieceCaptured = (move & mask) >> 21;

    outputMove m = { .endSqr = endSqr, .stSqr = stSqr, .flag = flag, .pieceMoved = pieceMoved, .pieceCaptured = pieceCaptured };

    return m;
}
