#include <stdio.h>
#include <stdint.h>

const uint8_t S_BOX[16] = {0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};
const uint8_t INV_S_BOX[16] = {0xE, 0x3, 0x4, 0x8, 0x1, 0xC, 0xA, 0xF, 0x7, 0xD, 0x9, 0x6, 0xB, 0x2, 0x0, 0x5};
const uint8_t P_BOX[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
const uint8_t INV_P_BOX[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

uint16_t apply_sbox(uint16_t input, const uint8_t *box) {
    uint16_t result = 0;
    for (int i = 0; i < 4; ++i) {
        uint8_t nibble = (input >> (4 * i)) & 0xF;
        result |= (uint16_t)box[nibble] << (4 * i);
    }
    return result;
}

uint16_t apply_pbox(uint16_t input, const uint8_t *box) {
    uint16_t result = 0;
    for (int i = 0; i < 16; ++i) {
        result |= ((input >> (16 - box[i])) & 1) << (15 - i);
    }
    return result;
}

void generate_round_keys(uint32_t key, uint16_t *round_keys) {
    for (int i = 0; i < 5; ++i) {
        round_keys[i] = (key >> (16 - 4 * i)) & 0xFFFF;
    }
}

uint16_t encrypt(uint16_t plaintext, uint32_t key) {
    uint16_t round_keys[5];
    generate_round_keys(key, round_keys);

    uint16_t state = plaintext;

    for (int round = 0; round < 4; ++round) {
        state ^= round_keys[round];
        state = apply_sbox(state, S_BOX);
        state = apply_pbox(state, P_BOX);
    }

    state ^= round_keys[4];
    return state;
}

uint16_t decrypt(uint16_t ciphertext, uint32_t key) {
    uint16_t round_keys[5];
    generate_round_keys(key, round_keys);

    uint16_t state = ciphertext;
    state ^= round_keys[4];

    for (int round = 3; round >= 0; --round) {
        state = apply_pbox(state, INV_P_BOX);
        state = apply_sbox(state, INV_S_BOX);
        state ^= round_keys[round];
    }

    return state;
}

int main() {
    uint32_t key;
    uint16_t plaintext;

    printf("Enter 32-bit key (hexadecimal): ");
    scanf("%x", &key);

    printf("Enter 16-bit plaintext (hexadecimal): ");
    scanf("%hx", &plaintext);

    uint16_t ciphertext = encrypt(plaintext, key);
    printf("Ciphertext: 0x%04X\n", ciphertext);

 
printf("Round keys:\n");
uint16_t round_keys[5];
generate_round_keys(key, round_keys);
for (int i = 0; i < 5; ++i) {
    printf("K%d: 0x%04X\n", i + 1, round_keys[i]);}


    uint16_t decrypted = decrypt(ciphertext, key);
    printf("Decrypted text: 0x%04X\n", decrypted);

    return 0;
}