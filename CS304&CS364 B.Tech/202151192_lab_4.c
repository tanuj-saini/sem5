
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define uint16_t unsigned short int
#define uint32_t unsigned int
#define uint64_t unsigned long long int
#define uchar_t unsigned char

const uint32_t P = 1021;

const uint32_t a = 449;
const uint32_t b = 233;

const uint16_t G = 0x011b;
const uint32_t theta_X = 0;
const uint32_t thetaY = 1;

uint32_t _alpha[2];



uchar_t subbyte_vermafuns_array[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

    uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

const uchar_t IV[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

const uint32_t RCON[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};
uint16_t prod(uchar_t a, uchar_t b)
{
    uint16_t prod = 0;

    for (int i = 0; i < 8; i++)
    {
        if ((a >> i) & 1)
        {
            uint16_t x = b << i;
            prod = prod ^ x;
        }
    }
    return prod;
}

uint32_t cnt_pts_curve()
{
    uint32_t count = 0;
    for (uint32_t i = 1; i < P; i++)
    {
        for (uint32_t j = 1; j < P; j++)
        {
            uint32_t lhs = (j * j) % P;
            uint32_t rhs = ((i * i * i) + a * i + b) % P;
            if (lhs == rhs)
                count++;
        }
    }

    return count;
}

void ptsOnCurve(uint32_t totalpts, uint32_t pts[totalpts][2])
{
    uint32_t idx = 0;
    for (uint32_t i = 1; i < P; i++)
    {
        for (uint32_t j = 1; j < P; j++)
        {
            uint32_t lhs = (j * j) % P;
            uint32_t rhs = ((i * i * i) + a * i + b) % P;
            if (lhs == rhs)
            {
                pts[idx][0] = i;
                pts[idx][1] = j;
                idx++;
            }
        }
    }
}

int extd_euclidean(int a, int b, int *p, int *q)
{
    if (a == 0)
    {
        *p = 0;
        *q = 1;
        return b;
    }

    int p1, q1;
    int gcd = extd_euclidean(b % a, a, &p1, &q1);

    *p = q1 - (b / a) * p1;
    *q = p1;

    return gcd;
}

uint32_t positive_maker(int a)
{
    while (a < 0)
        a += P;
    return (uint32_t)(a % P);
}

void add_pts(uint32_t p1[2], uint32_t p2[2], uint32_t p3[2])
{

    uint32_t m;
    if (p1[0] == 0 || p2[0] == 0)
    {
        if (p1[0] == 0)
        {
            p3[0] = p2[0];
            p3[1] = p2[1];
        }
        else
        {
            p3[0] = p1[0];
            p3[1] = p1[1];
        }
        return;
    }
    else if ((p1[0] == p2[0]) && (p1[1] == P - p2[1]))
    {

        p3[0] = theta_X;
        p3[1] = thetaY;
        return;
    }
    else if ((p1[0] == p2[0]) && (p1[1] == p2[1]))
    {

        m = (3 * p1[0] * p1[0] + a) % P;
        int p, q;
        extd_euclidean(2 * p1[1], P, &p, &q);
        m = (m * positive_maker(p)) % P;
    }
    else
    {

        uint32_t numz = (p2[1] + P - p1[1]) % P;
        uint32_t denz = (p2[0] + P - p1[0]) % P;
        int p = 0, q = 0;
        extd_euclidean(denz, P, &p, &q);
        m = (numz * positive_maker(p)) % P;
    }

    p3[0] = (m * m + (P - p1[0]) + (P - p2[0])) % P;
    p3[1] = P - ((p1[1] + m * (p3[0] + P - p1[0])) % P);
}


uint32_t pad_Len(uint32_t l)
{

    uint32_t x = 0;

    if (l % 16 == 0)
        x = l / 16;
    else
        x = l / 16 + 1;

    if (l % 16 == 14 || l % 16 == 15 || l % 16 == 0)
        x++;

    return x * 16;
}



void point_times_N(uint32_t n, uint32_t point[2], uint32_t sol[2])
{
    sol[0] = theta_X;
    sol[1] = thetaY;
    uint32_t temp[2] = {point[0], point[1]};

    while (n > 0)
    {
        if (n & 1)
        {
            uint32_t t[2];
            add_pts(sol, temp, t);
            sol[0] = t[0];
            sol[1] = t[1];
        }

        uint32_t t[2];
        add_pts(temp, temp, t);
        temp[0] = t[0];
        temp[1] = t[1];
        n = n >> 1;
    }
}
uint32_t rotate_right(uint32_t x, uint32_t bits)
{
    return ((x >> bits) | (x << (32 - bits)));
}


uchar_t subbyte_verma(uchar_t x)
{
    uchar_t temp = ((uint16_t)x << 1) ^ 1;
    if ((x >> 7) & 1)
        temp ^= 27;
    uint16_t t2 = temp & 15;
    uint16_t t1 = temp >> 4;
    return subbyte_vermafuns_array[t1][t2];
}

uchar_t inversesubbyte_verma(uchar_t x)
{
    uchar_t inv = 0;

    for (uchar_t i = 0; i < 16; i++)
    {
        for (uchar_t j = 0; j < 16; j++)
        {
            if (subbyte_vermafuns_array[i][j] == x)
            {
                inv = ((i << 4) | j);
            }
        }
    }

    if (inv & 1)
        inv = inv >> 1;
    else
        inv = ((inv ^ 27) >> 1) | (1 << 7);

    return inv;
}

void shiftRow_verma(uchar_t s[4][4])
{
    for (int i = 1; i < 4; i++)
    {
        uchar_t temp[4];
        for (int j = 0; j < 4; j++)
            temp[j] = s[i][j];
        for (int j = 0; j < 4; j++)
        {
            s[i][j] = temp[(j + i) % 4];
        }
    }
}

void invshiftRow_verma(uchar_t s[4][4])
{
    for (int i = 1; i < 4; i++)
    {
        uchar_t temp[4];
        for (int j = 0; j < 4; j++)
            temp[j] = s[i][j];
        for (int j = 0; j < 4; j++)
        {
            s[i][j] = temp[(j + 4 - i) % 4];
        }
    }
}

uchar_t x2TimesS_verma(uchar_t x)
{
    uchar_t temp = x << 2;
    if ((x >> 6) & 1)
        temp ^= (0x1b);
    if (x >> 7)
        temp ^= (0x36);
    return temp;
}

void mixcol(uchar_t s[4][4])
{
    for (int i = 0; i < 4; i++)
    {

        uchar_t t1 = s[0][i] ^ x2TimesS_verma(s[1][i]) ^ x2TimesS_verma(s[2][i]) ^ x2TimesS_verma(s[3][i]) ^ s[3][i];
        uchar_t t2 = x2TimesS_verma(s[0][i]) ^ s[0][i] ^ s[1][i] ^ x2TimesS_verma(s[2][i]) ^ x2TimesS_verma(s[3][i]);
        uchar_t t3 = x2TimesS_verma(s[0][i]) ^ x2TimesS_verma(s[1][i]) ^ s[1][i] ^ s[2][i] ^ x2TimesS_verma(s[3][i]);
        uchar_t t4 = x2TimesS_verma(s[0][i]) ^ x2TimesS_verma(s[1][i]) ^ x2TimesS_verma(s[2][i]) ^ s[2][i] ^ s[3][i];

        s[0][i] = t1;
        s[1][i] = t2;
        s[2][i] = t3;
        s[3][i] = t4;
    }
}

uchar_t modGx(uint16_t x)
{
    for (int i = 15; i > 7; i--)
    {
        if ((x >> i) & 1)
        {

            x = x ^ (1 << i);
            x = x ^ (0x1b << (i - 8));
        }
    }
    return x & 0xff;
}

const uchar_t M_inv[4][4] = {
    {0xa5, 0x07, 0x1a, 0x73},
    {0x73, 0xa5, 0x07, 0x1a},
    {0x1a, 0x73, 0xa5, 0x07},
    {0x07, 0x1a, 0x73, 0xa5}};

void invMixCols_verma(uchar_t s[4][4])
{
    uchar_t temp[4];
    uchar_t z = 0xff;

    for (uint16_t i = 0; i < 4; i++)
    {
        for (uint16_t j = 0; j < 4; j++)
        {
            uint16_t x = (uint16_t)0;
            for (uint16_t k = 0; k < 4; k++)
            {
                uint16_t y = prod(M_inv[j][k], s[k][i]);
                x = x ^ y;
            }

            temp[j] = modGx(x);
        }

        for (uint16_t j = 0; j < 4; j++)
        {
            s[j][i] = temp[j];
        }
    }
}

uchar_t subbyte_vermafun_orgn(uchar_t x)
{
    uint16_t t2 = x & 15;
    uint16_t t1 = x >> 4;
    return subbyte_vermafuns_array[t1][t2];
}
uint32_t rotWord(uint32_t x)
{
    uchar_t z = 0xff;
    uchar_t temp = (x >> 24) & z;

    x = (x << 8) | temp;
    return x;
}
uint32_t subWord(uint32_t x)
{
    uchar_t z = 0xff;
    uchar_t x0, x1, x2, x3;
    x0 = (x >> 24) & z;
    x1 = (x >> 16) & z;
    x2 = (x >> 8) & z;
    x3 = x & z;

    x0 = subbyte_vermafun_orgn(x0);
    x1 = subbyte_vermafun_orgn(x1);
    x2 = subbyte_vermafun_orgn(x2);
    x3 = subbyte_vermafun_orgn(x3);

    x = (x0 << 24) | (x1 << 16) | (x2 << 8) | x3;
    return x;
}

void keySchedule(uchar_t key[32], uchar_t roundKeys_verma[15][4][4])
{

    uint32_t words[60];
    uchar_t z = 0xff;

    for (int i = 0; i < 8; i++)
    {
        words[i] = (key[4 * i] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | (key[4 * i + 3]);
    }

    for (int i = 8; i < 60; i++)
    {
        uint32_t temp = words[i - 1];
        if (i % 8 == 0)
            temp = subWord(rotWord(temp)) ^ (RCON[i / 8 - 1]);
        else if (i % 8 == 4)
            temp = subWord(temp);
        words[i] = words[i - 8] ^ temp;
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                roundKeys_verma[i][k][j] = (words[4 * i + j] >> (24 - 8 * k)) & z;
            }
        }
    }
}

void inverseroundFun_verma(int round, uchar_t s[4][4])
{

    if (round != 14)
        invMixCols_verma(s);

    invshiftRow_verma(s);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            s[i][j] = inversesubbyte_verma(s[i][j]);
        }
    }
}

void roundFun_verma(int round, uchar_t s[4][4])
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            s[i][j] = subbyte_verma(s[i][j]);
        }
    }

    shiftRow_verma(s);

    if (round < 14)
        mixcol(s);
}

void AES_encrypt(int length, uchar_t plaintext_verma[length], uchar_t key[32], uchar_t ciphertext[length + 16])
{
    uint32_t index = 0;

    uchar_t roundKeys_verma[15][4][4];
    keySchedule(key, roundKeys_verma);
    int blocks = length / 16;

    uchar_t block__verma[4][4];
    for (uchar_t i = 0; i < 4; i++)
    {
        for (uchar_t j = 0; j < 4; j++)
        {
            block__verma[i][j] = IV[i][j];
            ciphertext[index++] = IV[i][j];
        }
    }

    for (uint32_t k = 0; k < blocks; k++)
    {

        uchar_t s[4][4];
        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++){
                s[j][i] = plaintext_verma[k * 16 + i * 4 + j];
            }
        }

        for (uint32_t i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++)
            {
                s[i][j] = s[i][j] ^ block__verma[i][j];
            }
        }

        for (uint32_t i = 0; i < 15; i++){
            for (uint32_t j = 0; j < 4; j++){
                for (uint32_t x = 0; x < 4; x++){
                    s[j][x] = s[j][x] ^ roundKeys_verma[i][j][x];
                }
            }

            if (i < 14)
                roundFun_verma(i + 1, s);
        }

        for (uint32_t i = 0; i < 4; i++){
            for (uint32_t j = 0; j < 4; j++)
            {
                block__verma[i][j] = s[i][j];
                ciphertext[index++] = s[j][i];
            }
        }
    }
}
void show(uchar_t s[], int a)
{
    for (int i = a; i < a + 16; i++)
    {
        printf("%02x ", s[i]);
    }
    printf("\n");
}

void decrypt_aes(uchar_t length, uchar_t ciphertext[length], uchar_t key[32], uchar_t decrypted_text[length - 16])
{

    int index = 0;

    uchar_t roundKeys_verma[15][4][4];
    keySchedule(key, roundKeys_verma);
    uint32_t blocks = length / 16 - 1;

    uchar_t decryptFedBack[4][4];

    for (uint32_t k = 0; k < blocks; k++){
        uchar_t s[4][4];
        for (uint32_t i = 0; i < 4; i++){
            for (uint32_t j = 0; j < 4; j++){
                s[j][i] = ciphertext[((k + 1) * 16) + i * 4 + j];
            }
        }
        for (uint32_t i = 0; i < 4; i++){
            for (uint32_t j = 0; j < 4; j++)    {
               decryptFedBack[j][i] = ciphertext[k * 16 + i * 4 + j];
            }
        }
        for (int i = 14; i >= 0; i--){
            for (uint32_t j = 0; j < 4; j++){
                for (uint32_t x = 0; x < 4; x++){
                    s[j][x] = s[j][x] ^ roundKeys_verma[i][j][x];
                }
            }
            if (i > 0)
                inverseroundFun_verma(i, s);
        }
        for (uint32_t i = 0; i < 4; i++){
            for (uint32_t j = 0; j < 4; j++){
                s[i][j] = s[i][j] ^ decryptFedBack[i][j];
            }
        }
        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                decrypted_text[index++] = s[j][i];
            }
        }
    }
}
void TripleAesEncrypt(const uchar_t plaintext_verma[32], const uchar_t keyA[32], const uchar_t keyB[32], uchar_t encrypted[48])
{
    uchar_t IA[48];
    uchar_t JA[32];
    uchar_t CA[48];
    AES_encrypt(32, plaintext_verma, keyA, IA);
    decrypt_aes(48, IA, keyB, JA);

    AES_encrypt(32, JA, keyA, CA);

    for (int i = 0; i < 48; ++i)
    {
        encrypted[i] = CA[i];
    }
}

void TripleAesdecrypt(const uchar_t ciphertext[48], const uchar_t keyA[32], const uchar_t keyB[32], uchar_t decrypted[32])
{
    uchar_t MB[32];
    uchar_t JB[48];
    uchar_t IB[32];

    decrypt_aes(48, ciphertext, keyB, IB);

    AES_encrypt(32, IB, keyA, JB);

    decrypt_aes(48, JB, keyB, MB);

    for (int i = 0; i < 32; ++i)
    {
        decrypted[i] = MB[i];
    }
}

void SHA_256_verma(uint32_t length, uint32_t m[length], uint32_t hasing_array[8])
{

    uint32_t paddedLen = pad_Len(length);
    uint32_t msg_aft_padding[paddedLen];
    for (uint32_t i = 0; i < paddedLen; i++)
        msg_aft_padding[i] = 0;

    for (uint32_t i = 0; i < length; i++)
        msg_aft_padding[i] = m[i];
    msg_aft_padding[length] = ((uint32_t)1) << 31;

    msg_aft_padding[paddedLen - 1] = 32 * length;

    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    for (uint32_t j = 0; j < paddedLen / 16; j++)
    {

        uint32_t words[64] = {0};

        for (uint32_t i = 0; i < 16; i++)
            words[i] = msg_aft_padding[16 * j + i];
        for (uint32_t i = 16; i < 64; i++)
        {
            uint32_t x = rotate_right(words[i - 15], 7) ^ rotate_right(words[i - 15], 18) ^ (words[i - 15] >> 3);
            uint32_t y = rotate_right(words[i - 2], 17) ^ rotate_right(words[i - 2], 19) ^ (words[i - 2] >> 10);
            words[i] = words[i - 16] + x + words[i - 7] + y;
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;
        for (uint32_t i = 0; i < 64; i++)
        {
            uint32_t x = rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25);
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + x + ch + k[i] + words[i];
            uint32_t y = rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = y + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;
    }

    hasing_array[0] = h0;
    hasing_array[1] = h1;
    hasing_array[2] = h2;
    hasing_array[3] = h3;
    hasing_array[4] = h4;
    hasing_array[5] = h5;
    hasing_array[6] = h6;
    hasing_array[7] = h7;
}

void convertor(uint32_t hasing_array[8], uchar_t key[32])
{
    uchar_t z = 0xff;
    for (uint32_t i = 0; i < 8; i++)
    {
        key[i * 4] = hasing_array[i] >> 24;
        key[i * 4 + 1] = (hasing_array[i] >> 16) & z;
        key[i * 4 + 2] = (hasing_array[i] >> 8) & z;
        key[i * 4 + 3] = hasing_array[i] & z;
    }
}
void convertToInt(uchar_t x[32], uint32_t y[8])
{
    for (int i = 0; i < 8; i++)
    {
        uint32_t x1 = x[4 * i];
        uint32_t x2 = x[4 * i + 1];
        uint32_t x3 = x[4 * i + 2];
        uint32_t x4 = x[4 * i + 3];

        y[i] = (x1 << 24) | (x2 << 16) | (x3 << 8) | x4;
    }
}

void gen_mac(uint32_t key[8], uchar_t M[32], uint32_t MAC[8])
{

    uint32_t inp[16];

    for (uint32_t i = 0; i < 7; i++)
    {
        inp[i] = key[i];
    }
    inp[7] = key[7] ^ 215;

    uint32_t convertedM[8];
    convertToInt(M, convertedM);

    for (uint32_t i = 8; i < 16; i++)
    {
        inp[i] = convertedM[i - 8];
    }

    uint32_t mac1[8];
    SHA_256_verma(16, inp, mac1);

    for (uint32_t i = 0; i < 7; i++)
    {
        inp[i] = key[i];
    }
    inp[7] = key[7] ^ 125;
    for (uint32_t i = 8; i < 16; i++)
        inp[i] = mac1[i - 8];

    SHA_256_verma(16, inp, MAC);
}


int main()
{
    printf("\n");

    uint32_t test_point[2] = {3, 6};
    uint32_t scalar = 5;

    uint32_t sol[2];
    point_times_N(scalar, test_point, sol);

    int totalpts = cnt_pts_curve();

    uint32_t pts[totalpts][2];

    ptsOnCurve(totalpts, pts);

    srand(time(NULL));
    uint32_t idx = (rand() % totalpts);
    _alpha[0] = pts[idx - 1][0];
    _alpha[1] = pts[idx - 1][1];

    printf("The point _alpha  on curve choosen randomly is: (%u, %u)\n", _alpha[0], _alpha[1]);
    printf("\n");

    uint32_t nA, nB;
    printf("Enter Alice's Private Key (an integer between 1 and 330 ( inclusive)): ");

    do
    {
        scanf("%u", &nA);
        if (nA < 1 || nA > 330)
        {
            printf("Error, enter a number in the given range.\n");
            printf("Enter Alice's Private Key (an integer between 1 and 330 ): ");
        }
    } while (nA > 330 || nA < 1);

    printf("Enter Bob's Private Key (an integer between 1 and 330): ");

    do
    {
        scanf("%u", &nB);
        if (nB < 1 || nB > 330)
        {
            printf("Error, enter no. in given range.\n");
            printf("Enter Alice's Private Key (an integer between 1 and 330 ): ");
        }
    } while (nB > 330 || nB < 1);

    uint32_t na_alpha[2];
    point_times_N(nA, _alpha, na_alpha);

    uint32_t nb_alpha[2];
    point_times_N(nB, _alpha, nb_alpha);

    uint32_t naNb_alpha[2];
    uint32_t nbNa_alpha[2];

    point_times_N(nA, nb_alpha, naNb_alpha);
    point_times_N(nB, na_alpha, nbNa_alpha);
    printf("\n");

    printf("The Shared Secret key between Alice and Bob is: (%u, %u)\n", nbNa_alpha[0], nbNa_alpha[1]);

    uint32_t kA[8] = {0};

    uint32_t msgA[2] = {naNb_alpha[0], naNb_alpha[1]};

    SHA_256_verma(2, msgA, kA);

    uint32_t kB[8] = {0};

    uint32_t msgB[2] = {nbNa_alpha[0], nbNa_alpha[1]};

    SHA_256_verma(2, msgB, kB);

    printf("\n");
    printf("kA: ");
    for (int i = 0; i < 8; i++)
        printf("%08x ", kA[i]);

    printf("\n");

    printf("kB: ");
    for (int i = 0; i < 8; i++)
        printf("%08x ", kB[i]);

    printf("\n\n");

    uchar_t MA[32];
    printf("Enter 128-bit message of Alice (in hexadecimal,separated by spaces): ");
    for (int i = 0; i < 16; i++)
    {
        scanf("%hhx", &MA[i]);
    }

    printf("\n");
    printf("The original message ma: \n ");
    show(MA, 0);

    uchar_t keyA[32];
    convertor(kA, keyA);
    uchar_t keyB[32];
    convertor(kB, keyB);

    uchar_t CA[48];

    TripleAesEncrypt(MA, keyA, keyB, CA);

    printf("\nCA after TRIPLE aes encryption: \n");
    show(CA, 16);

    uint32_t macA[8];
    gen_mac(kA, MA, macA);

    printf("macA: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%08x ", macA[i]);
    }
    printf("\n\n");

    uchar_t MB[32];
    TripleAesdecrypt(CA, keyA, keyB, MB);
    printf("mB after TRIPLE AES decryption: \n");
    show(MB, 0);

    uint32_t macB[8];
    gen_mac(kB, MB, macB);

    printf("macB: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%08x ", macB[i]);
    }

    return 0;
}
