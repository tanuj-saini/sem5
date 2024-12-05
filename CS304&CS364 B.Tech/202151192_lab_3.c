#include<stdio.h>
#include <stdbool.h>

#define uint16_t unsigned short int
#define uint32_t unsigned long int
#define uint64_t unsigned long long int
#define uchar_t unsigned char


// G(x) = x^8 + x^4 + x^3 + x + 1 = (0000 0001 0001 1011) = 0x11b
const uint16_t G = 0x011b;

//the subbytefun table used in AES
uchar_t subbytefuns_array[16][16] = {
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
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

// the round constants for AES-prime, they are exactly similar to AES-128.
const uint32_t RCON[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};


uint16_t prod(uchar_t a, uchar_t b){
    uint16_t prod = 0; //stores the prod

    for(int i = 0; i < 8; i++){  
        if((a >> i) & 1){        
            uint16_t x = b << i;  
            prod = prod ^ x;      
        }
    }
    return prod;
}

uchar_t subbytefun(uchar_t x){
    uchar_t temp = ((uint16_t) x << 1) ^ 1; 
    if((x >> 7) & 1) temp ^= 27;    
    uint16_t t2 = temp & 15;    
    uint16_t t1 = temp >> 4;    
    return subbytefuns_array[t1][t2]; 
}



uchar_t inversesubbytefun(uchar_t x){
    uchar_t inv = 0;

    //finding x = subInp in the look-up table and calcuating y = inv (as describe above)
    for(uchar_t i = 0; i < 16; i++){
        for(uchar_t j = 0; j < 16; j++){
            if(subbytefuns_array[i][j] == x){ 
                inv = ((i << 4) | j);
            }
        }
    }

    // cases are described above
    if(inv & 1) inv = inv >> 1;    //case where LSB of inv is set
    else inv = ((inv ^ 27) >> 1) | (1 << 7); //case where LSB of inv is not set

    return inv;
}

//Shift Row function, left circular shifts the i^th row by i positions.
void shiftRow(uchar_t s[4][4]){
    for(int i = 1; i < 4; i++){ 
        uchar_t temp[4];    
        for(int j = 0; j < 4; j++) temp[j] = s[i][j];  
        for(int j = 0; j < 4; j++){
            s[i][j] = temp[(j + i) % 4]; 
        }
    }
}

//Inverse Shift Row function, right circular shifts the i^th row by i positions
void invShiftRow(uchar_t s[4][4]){
    for(int i = 1; i < 4; i++){     
        uchar_t temp[4];
        for(int j = 0; j < 4; j++) temp[j] = s[i][j];  
        for(int j = 0; j < 4; j++){
            s[i][j] = temp[(j + 4 - i) % 4];  
        }
    }
}


uchar_t x2TimesS(uchar_t x){
    uchar_t temp = x << 2; //multiplied by x^2
    if((x >> 6) & 1) temp ^= (0x1b); 
    if(x >> 7) temp ^= (0x36);  
    return temp; 
}


void mixColumns(uchar_t s[4][4]){
    for(int i = 0; i < 4; i++){ //for each column of input matrix
        //calculating the 4 polynomial according to the mix column matrix
        uchar_t t1 = s[0][i] ^ x2TimesS(s[1][i]) ^ x2TimesS(s[2][i]) ^ x2TimesS(s[3][i]) ^ s[3][i];
        uchar_t t2 = x2TimesS(s[0][i]) ^ s[0][i] ^ s[1][i] ^ x2TimesS(s[2][i]) ^ x2TimesS(s[3][i]);
        uchar_t t3 = x2TimesS(s[0][i]) ^ x2TimesS(s[1][i]) ^ s[1][i] ^ s[2][i] ^ x2TimesS(s[3][i]);
        uchar_t t4 = x2TimesS(s[0][i]) ^ x2TimesS(s[1][i]) ^ x2TimesS(s[2][i]) ^ s[2][i] ^ s[3][i];

        //updating the column of input, with mix column value
        s[0][i] = t1;
        s[1][i] = t2;
        s[2][i] = t3;
        s[3][i] = t4;
    }
}

//function to calculate input modulo G(x), where input is any polynomial of degree <= 15.
uchar_t modGx(uint16_t x){
    for(int i = 15; i > 7; i--){ 
        if((x >> i) & 1){     

            
            x = x ^ (1 << i);  
            x = x ^ (0x1b << (i - 8)); 
        }
    }
    return x & 0xff;
}

//the matrix used to calculate the inverse of mix columns in AES-prime
const uchar_t M_inv[4][4] = {
    {0xa5, 0x07, 0x1a, 0x73},
    {0x73, 0xa5, 0x07, 0x1a},
    {0x1a, 0x73, 0xa5, 0x07},
    {0x07, 0x1a, 0x73, 0xa5}
};

void invMixCols(uchar_t s[4][4]){
    uchar_t temp[4]; //stores mix column inverse of a column
    uchar_t z = 0xff;

    //matrix multiplication
    for(uint16_t i = 0; i < 4; i++){
        for(uint16_t j = 0; j < 4; j++){
            uint16_t x = (uint16_t)0;
            for(uint16_t k = 0; k < 4; k++){                
                uint16_t y =  prod(M_inv[j][k], s[k][i]);
                x = x ^ y;
            }
    
            temp[j] = modGx(x); 
        }

        for(uint16_t j = 0; j < 4; j++){
            s[j][i] = temp[j]; 
        }
    }
}

//function to left circular shift a 32-bit word by 8 bits (or 1 byte)
uint32_t rotWord(uint32_t x){
    uchar_t z = 0xff; 
    uchar_t temp = (x >> 24) & z; //taking out the most significant byte
    
    x = (x << 8) | temp; 
    return x;
}

//the original subbytefun function of AES-128, its inverse will not be required as key remains the same
//during encryption as well as decryption
uchar_t subbytefun_org(uchar_t x){
    uint16_t t2 = x & 15;    
    uint16_t t1 = x >> 4;    
    return subbytefuns_array[t1][t2]; //table look-up
}


//function to perform subbytefuns of each byte of the 32-bit word.
//Each word contains 4-bytes and we have to perform subbytefuns of each of them
uint32_t subWordmat(uint32_t x){
    uchar_t z = 0xff;
    uchar_t x0, x1, x2, x3; 
    x0 = (x >> 24) & z; 
    x1 = (x >> 16) & z; 
    x2 = (x >> 8) & z;
    x3 = x & z;

    //performing subbytefun on each byte, since Key Scheduling uses original subbytefun function.
    x0 = subbytefun_org(x0);
    x1 = subbytefun_org(x1);
    x2 = subbytefun_org(x2);
    x3 = subbytefun_org(x3);

    //output = subbytefun(x0) || subbytefun(x1) || subbytefun(x2) || subbytefun(x3)
    x = (x0 << 24) | (x1 << 16) | (x2 << 8) | x3;
    return x;
}

//this function generates the round keys for AES-prime, and is exactly similar to AES-128
void keyScheduling(uchar_t key[16], uchar_t roundKeys[11][4][4]){
    uint32_t words[44]; 
    uchar_t z = 0xff;
    for(int i = 0; i < 4; i++){  
        words[i] = (key[4*i] << 24) | (key[4*i+1] << 16) | (key[4*i+2] << 8) | (key[4*i+3]);
    }

    //finding remaining words according to the key scheduling algorithm
    for(int i = 4; i < 44; i++){
        uint32_t temp = words[i-1]; 
        if(i % 4 == 0) temp = subWordmat(rotWord(temp)) ^ (RCON[i/4 - 1]); 
        words[i] = words[i-4] ^ temp;
    }
    
    //the 11 round keys are stored as 4*4 matrix in column-wise manner
    //each roundKey[i] is a round key.
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                roundKeys[i][k][j] = (words[4*i+j] >> (24 - 8 * k)) & z; 
            }
        }
    }
}

//the round function f of AES-prime
void roundFunction(int r, uchar_t s[4][4]){

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            s[i][j] = subbytefun(s[i][j]);
        }
    }
    //perform shift row
    shiftRow(s);
    //if it is not the last,i.e. 10th round, perform mix columns.
    if(r < 10) mixColumns(s);
}

//the inverse round function f of AES-prime
void inverseRoundFunction(int r, uchar_t s[4][4]){
    
    if(r != 10) invMixCols(s);
    //perform inverse shift row
    invShiftRow(s);
    //perform subbytefun inverse
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            s[i][j] = inversesubbytefun(s[i][j]);
        }
    }
}

//this function encrypts using the AES-prime algorithm
void encryptAES(uchar_t plaintxt[16], uchar_t key[16], uchar_t ciphertext[16]){
    uchar_t s[4][4];
    uchar_t k[4][4];

    //first just store the key and plaintxt in 4*4 matrices
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            s[j][i] = plaintxt[i * 4 + j];
            k[j][i] = key[i * 4 + j];
        }
    }
    
    uchar_t roundKeys[11][4][4];
    keyScheduling(key, roundKeys); //generate roung keys

    //perform encryption
    for(int i = 0; i < 11; i++){
        //first mix the round keys
        for(int j = 0; j < 4; j++){
            for(int x = 0; x < 4; x++){
                s[j][x] = s[j][x] ^ roundKeys[i][j][x];
            }
        }
                
        if(i < 10) roundFunction(i+1, s);
        
    }

    
    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            ciphertext[index++] = s[j][i];
        }
    }
}

//this function decrypts using the AES-prime algorithm
void decryptAES(uchar_t ciphertext[16], uchar_t key[16], uchar_t decrypted_text[16]){
    uchar_t s[4][4];
    uchar_t k[4][4];

    //first just store the key and ciphertext in 4*4 matrices
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            s[j][i] = ciphertext[i * 4 + j];
            k[j][i] = key[i * 4 + j];
        }
    }
    
    uchar_t roundKeys[11][4][4]; 
    keyScheduling(key, roundKeys); //generate round keys

    //perform decryption
    for(int i = 10; i >= 0; i--){
        //first mix the round keys
        for(int j = 0; j < 4; j++){
            for(int x = 0; x < 4; x++){
                s[j][x] = s[j][x] ^ roundKeys[i][j][x];
            }
        }

  
        if(i > 0) inverseRoundFunction(i, s);
        
    }

    //store the generated plaintxt in a 1-D array
    int index = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            decrypted_text[index++] = s[j][i];
        }
    }
}

//helper function to print the array
void print(uchar_t s[16]){
    for(int i = 0; i < 16; i++){
        printf("%02x", s[i]);
    }
    printf("\n");
}

void compression_funct(uchar_t m1[16], uchar_t m2[16], uchar_t output[16]) {
    uchar_t combined[16];

    // Combine m1 and m2
    for (int i = 0; i < 16; i++) {
        combined[i] = m1[i];
    }
    for (int i = 0; i < 16; i++) {
        combined[i + 16] = m2[i];
    }

    // Encrypt the combined message with AES-prime
    uchar_t key[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    encryptAES(combined, key, output);
}

void second_preimg(const uchar_t input_m1[16], const uchar_t input_m2[16], uchar_t output_m1[16], uchar_t output_m2[16]) {
    uchar_t input_combined[32];
    uchar_t output_combined[32];

    // Combine m1 and m2 for both input and output
    for (int i = 0; i < 16; i++) {
        input_combined[i] = input_m1[i];
        input_combined[i + 16] = input_m2[i];
        output_combined[i] = output_m1[i];
        output_combined[i + 16] = output_m2[i];
    }

    // Find the second pre-image by iterating over all possible values of m1 and m2
    for (int m1_value = 0; m1_value < 0x100; m1_value++) {
        for (int m2_value = 0; m2_value < 0x100; m2_value++) {
            output_m1[0] = (uchar_t)(m1_value & 0xFF);
            output_m2[0] = (uchar_t)(m2_value & 0xFF);

            // Encrypt the combined message with AES-prime
            uchar_t key[16] = {0x00}; // Proper initialization of encryption key required
            encryptAES(input_combined, key, output_combined);

            // Check if the output_combined matches the original output
            bool match = true;
            for (int i = 0; i < 32; i++) {
                if (output_combined[i] != output_combined[i + 16]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                // Found the second pre-image
                printf("Second pre-image found:\n");
                printf("m1: ");
                for (int i = 0; i < 16; i++) {
                    printf("%02X", output_m1[i]);
                }
                printf("\n");
                printf("m2: ");
                for (int i = 0; i < 16; i++) {
                    printf("%02X", output_m2[i]);
                }
                printf("\n");
                return;
            }
        }
    }

    // If no match is found
    printf("Second pre-image not found.\n");
}
   


// int main(){
    
//     uchar_t plaintxt[20];

//     printf("Enter 128-bit plaintxt as input (in hexadecimal, each pair of hex digits separated by spaces): ");
//     for(int i = 0; i < 16; i++) {
//         scanf("%hhx", &plaintxt[i]);    //take plaintxt as input
//     }
 
//     uchar_t key[20]; 
//     printf("Enter 128-bit key as input (in hexadecimal, each pair of hex digits separated by spaces): ");
//     for(int i = 0; i < 16; i++){
//         scanf("%hhx", &key[i]); //take key as input
//     }
    
//     uchar_t ciphertext[16];
//     encryptAES(plaintxt, key, ciphertext);

//     uchar_t h[16];
//     compression_funct(plaintxt, key, h);

//     printf("h = ");
//     for (int i = 0; i < 16; i++) {
//         printf("%02X", h[i]);
//     }
//     printf("\n");

//     uchar_t second_preimg_m1[16];
//     uchar_t second_preimg_m2[16];
//    second_preimg(plaintxt, key, second_preimg_m1, second_preimg_m2);

//     printf("plaintxt: "); //print plaintxt
//     print(plaintxt);
//     printf("Key: ");  //print key
//     print(key); 
    
//     printf("Ciphertext: ");
//     print(ciphertext);

//     uchar_t decrypted_text[16];
//     decryptAES(ciphertext, key, decrypted_text); 
//     printf("Decrypted Text: "); 
//     print(decrypted_text);

//     return 0;
// }



void encryptAESprime(const uchar_t m1[16], const uchar_t m2[16], uchar_t ciphertext[16]) {
    // Dummy implementation of AES' compression function
    // Replace this with the actual AES' compression function implementation
    for (int i = 0; i < 16; i++) {
        ciphertext[i] = m1[i] ^ m2[i]; // Just XOR of m1 and m2 for demonstration
    }
}

// Function to print an array in hexadecimal format
void printHex(const uchar_t arr[16]) {
    for (int i = 0; i < 16; i++) {
        printf("%02X ", arr[i]);
    }
    printf("\n");
}

int main() {
    uchar_t m1[16];
    uchar_t m2[16];
    uchar_t h[16];

    // Input m1
    printf("Enter m1 (128-bit in hexadecimal, each pair of hex digits separated by a space): ");
    for (int i = 0; i < 16; i++) {
        scanf("%hhX", &m1[i]);
    }

    // Input m2
    printf("Enter m2 (128-bit in hexadecimal, each pair of hex digits separated by a space): ");
    for (int i = 0; i < 16; i++) {
        scanf("%hhX", &m2[i]);
    }

    // Calculate h(m1||m2)
    encryptAESprime(m1, m2, h);

    // Print h(m1||m2)
    printf("\nh(m1||m2): ");
    printHex(h);

    // Find the second pre-image (m'1||m'2)
    uchar_t m1_prime[16];
    uchar_t m2_prime[16];
    printf("\nSecond pre-image finding process:\n");
    printf("Finding second pre-image for h(m1||m2)...\n");

    // Iterate over all possible values of m'1 and m'2 to find the second pre-image
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // Convert i and j to binary
            for (int k = 0; k < 8; k++) {
                m1_prime[k] = (i >> (7 - k)) & 1;
                m2_prime[k] = (j >> (7 - k)) & 1;
            }
            // Copy the binary values of m'1 and m'2 to the remaining bytes
            for (int k = 8; k < 16; k++) {
                m1_prime[k] = m1_prime[k - 8];
                m2_prime[k] = m2_prime[k - 8];
            }

            // Calculate h(m'1||m'2)
            encryptAESprime(m1_prime, m2_prime, h);

            // Check if h(m'1||m'2) matches h(m1||m2)
            bool match = true;
            for (int k = 0; k < 16; k++) {
                if (h[k] != h[k + 8]) {
                    match = false;
                    break;
                }
            }

            // If match found, print the second pre-image and exit
            if (match) {
                printf("\nSecond pre-image found:\n");
                printf("m'1: ");
                printHex(m1_prime);
                printf("m'2: ");
                printHex(m2_prime);
                return 0;
            }
        }
    }

    printf("Second pre-image not found.\n");

    return 0;
}
