#include <lib/pwgen.h>

unsigned circular_shift(int bits, unsigned word)
{
    return ((word << bits) & 0xFFFFFFFF) | ((word & 0xFFFFFFFF) >> (32 - bits));
}

std::string parser_to_lower(std::string sha_key)
{
    for (int i = 0; i < (int)sha_key.length(); i++) {
        if (sha_key[i] >= 'A' && sha_key[i] <= 'Z') {
            sha_key[i] = sha_key[i] + 32;
        }
    }
    return sha_key;
}

std::string sha_gen(std::string mess)
{
    unsigned int lm = mess.length();
    unsigned int lmb = lm * 8;
    unsigned char* messc;
    messc = (unsigned char*)malloc((sizeof(unsigned char)) * 64);

    for (unsigned short int i = 0; i < 64; i++) {
        messc[i] = char(0x00);
    }
    for (int i = 0; i < (int)mess.length(); i++) {
        messc[i] = mess[i];
    }
    messc[lm] = (unsigned char)128;
    messc[56] = (lmb >> 24) & 0xFF;
    messc[57] = (lmb >> 16) & 0xFF;
    messc[58] = (lmb >> 8) & 0xFF;
    messc[60] = (lmb >> 24) & 0xFF;
    messc[61] = (lmb >> 16) & 0xFF;
    messc[62] = (lmb >> 8) & 0xFF;
    messc[63] = (lmb)&0xFF;

    unsigned* H;
    H = (unsigned*)malloc(5 * sizeof(unsigned));
    H[0] = 0x67452301;
    H[1] = 0xEFCDAB89;
    H[2] = 0x98BADCFE;
    H[3] = 0x10325476;
    H[4] = 0xC3D2E1F0;
    const unsigned K[] = {0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6};
    int t;
    unsigned temp;
    unsigned* W;
    unsigned A, B, C, D, E;
    W = (unsigned*)malloc(80 * sizeof(unsigned));

    for (t = 0; t < 16; t++) {
        W[t] = ((unsigned)messc[t * 4]) << 24;
        ;
        W[t] |= ((unsigned)messc[t * 4 + 1]) << 16;
        W[t] |= ((unsigned)messc[t * 4 + 2]) << 8;
        W[t] |= ((unsigned)messc[t * 4 + 3]);
    }
    for (t = 16; t < 80; t++) {
        W[t] = circular_shift(1, W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16]);
    }

    A = H[0];
    B = H[1];
    C = H[2];
    D = H[3];
    E = H[4];

    for (t = 0; t < 20; t++) {
        temp = circular_shift(5, A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = circular_shift(30, B);
        B = A;
        A = temp;
    }

    for (t = 20; t < 40; t++) {
        temp = circular_shift(5, A) + (B ^ C ^ D) + E + W[t] + K[1];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = circular_shift(30, B);
        B = A;
        A = temp;
    }

    for (t = 40; t < 60; t++) {
        temp = circular_shift(5, A) + ((B & C) | (B & D) | (C & D)) + E + W[t]
                + K[2];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = circular_shift(30, B);
        B = A;
        A = temp;
    }

    for (t = 60; t < 80; t++) {
        temp = circular_shift(5, A) + (B ^ C ^ D) + E + W[t] + K[3];
        temp &= 0xFFFFFFFF;
        E = D;
        D = C;
        C = circular_shift(30, B);
        B = A;
        A = temp;
    }

    H[0] = (H[0] + A) & 0xFFFFFFFF;
    H[1] = (H[1] + B) & 0xFFFFFFFF;
    H[2] = (H[2] + C) & 0xFFFFFFFF;
    H[3] = (H[3] + D) & 0xFFFFFFFF;
    H[4] = (H[4] + E) & 0xFFFFFFFF;

    std::string s;
    char c[5][8];
    for (int i = 0; i < 5; i++) {
        sprintf(c[i], "%02X", H[i]);
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            s.push_back(c[i][j]);
        }
    }
    s = parser_to_lower(s);
    return s;
}
