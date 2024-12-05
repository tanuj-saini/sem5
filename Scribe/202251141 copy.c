// Name : Tanuj Saini
// Id   : 202251141

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include <openssl/aes.h>

// Prime number and elliptic curve parameters
#define P 1223
#define A 439
#define B 133

// Modular multiplicative inverse using extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

// Structure for a point on the elliptic curve
typedef struct {
    int x;
    int y;
} Point;

// Function prototypes
Point EL_rand();
Point EL_add(Point p1, Point p2);
Point EL_mul(Point p, int n);
int is_on_curve(Point p);
void SHA512_hash(const unsigned char *data, size_t len, unsigned char *hash);
void AES_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key);
void Triple_AES_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key);
void Triple_AES_decrypt(const unsigned char *input, unsigned char *output, const unsigned char *key);
void MAC_generate(const unsigned char *key, const unsigned char *msg, size_t msg_len, unsigned char *mac);
void print_hex(const char *label, unsigned char *data, size_t len);

// Verify if a point is on the elliptic curve
int is_on_curve(Point p) {
    // Verify y^2 = x^3 + Ax + B (mod P)
    int left = (p.y * p.y) % P;
    int right = (p.x * p.x * p.x + A * p.x + B) % P;
    return left == right;
}

// Function to generate a random point on the elliptic curve
Point EL_rand() {
    Point p;
    int attempts = 0;
    do {
        if (attempts++ > 1000) {
            fprintf(stderr, "Failed to generate a valid point\n");
            exit(1);
        }
        p.x = rand() % P;
        
        // Compute y^2
        int y_squared = (p.x * p.x * p.x + A * p.x + B) % P;
        
        // Find a quadratic residue (square root modulo P)
        for (int y = 0; y < P; y++) {
            if ((y * y) % P == y_squared) {
                p.y = y;
                break;
            }
        }
    } while (!is_on_curve(p));
    
    return p;
}

// Function to add two points on the elliptic curve
Point EL_add(Point p1, Point p2) {
    Point result = {0, 0};
    
    // Point at infinity
    if (p1.x == 0 && p1.y == 0) return p2;
    if (p2.x == 0 && p2.y == 0) return p1;
    
    // Point addition formula
    if (p1.x == p2.x) {
        // Point doubling case
        if (p1.y == p2.y && p1.y != 0) {
            int lambda = ((3 * p1.x * p1.x + A) * mod_inverse(2 * p1.y, P)) % P;
            result.x = (lambda * lambda - 2 * p1.x) % P;
            result.y = (lambda * (p1.x - result.x) - p1.y) % P;
        } else {
            // Points are inverses of each other
            result.x = 0;
            result.y = 0;
        }
    } else {
        // Different points
        int lambda = ((p2.y - p1.y) * mod_inverse(p2.x - p1.x + P, P)) % P;
        result.x = (lambda * lambda - p1.x - p2.x) % P;
        result.y = (lambda * (p1.x - result.x) - p1.y) % P;
    }
    
    // Ensure result is within the field
    result.x = (result.x + P) % P;
    result.y = (result.y + P) % P;
    
    return result;
}

// Scalar multiplication of a point using double-and-add method
Point EL_mul(Point p, int n) {
    Point result = {0, 0}; // Point at infinity
    Point addend = p;
    
    while (n > 0) {
        if (n & 1) {
            result = EL_add(result, addend);
        }
        addend = EL_add(addend, addend);
        n >>= 1;
    }
    
    return result;
}

// Secure SHA-512 hash function
void SHA512_hash(const unsigned char *data, size_t len, unsigned char *hash) {
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, data, len);
    SHA512_Final(hash, &sha512);
}

// AES Encryption function
void AES_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_encrypt(input, output, &enc_key);
}

// Triple AES encryption
void Triple_AES_encrypt(const unsigned char *input, unsigned char *output, const unsigned char *key) {
    unsigned char temp[16];
    AES_KEY enc_keys[3];
    
    // Set up three different keys
    AES_set_encrypt_key(key, 128, &enc_keys[0]);
    AES_set_encrypt_key(key + 16, 128, &enc_keys[1]);
    AES_set_encrypt_key(key + 32, 128, &enc_keys[2]);
    
    // Three-pass encryption
    AES_encrypt(input, temp, &enc_keys[0]);
    AES_encrypt(temp, output, &enc_keys[1]);
    AES_encrypt(output, temp, &enc_keys[2]);
    memcpy(output, temp, 16);
}

// Triple AES decryption
void Triple_AES_decrypt(const unsigned char *input, unsigned char *output, const unsigned char *key) {
    unsigned char temp[16];
    AES_KEY dec_keys[3];
    
    // Set up three different keys
    AES_set_encrypt_key(key, 128, &dec_keys[0]);
    AES_set_encrypt_key(key + 16, 128, &dec_keys[1]);
    AES_set_encrypt_key(key + 32, 128, &dec_keys[2]);
    
    // Three-pass decryption (reverse order of encryption)
    AES_decrypt(input, temp, &dec_keys[2]);
    AES_decrypt(temp, output, &dec_keys[1]);
    AES_encrypt(output, temp, &dec_keys[0]);
    memcpy(output, temp, 16);
}

// MAC generation using SHA-512
void MAC_generate(const unsigned char *key, const unsigned char *input, size_t msg_len, unsigned char *mac) {
    unsigned char KA[64];
    SHA512_hash(key, 64, KA); // Use full 64-byte key
    
    unsigned char data[80]; // Combine key and input
    memcpy(data, KA, 64);
    memcpy(data + 64, input, msg_len);
    
    SHA512_hash(data, sizeof(data), mac);
}

// Print data in hexadecimal format
void print_hex(const char *label, unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    // Seed the random number generator securely
    srand((unsigned int)time(NULL) ^ getpid());

    // Generate a random point α on the elliptic curve
    Point alpha = EL_rand();
    printf("Random point α: (%d, %d)\n", alpha.x, alpha.y);

    // Get private keys for Alice and Bob
    int nA, nB;
    printf("Enter Alice's private key (nA, 1-1000): ");
    scanf("%d", &nA);
    printf("Enter Bob's private key (nB, 1-1000): ");
    scanf("%d", &nB);

    // Validate private keys
    if (nA < 1 || nA > 1000 || nB < 1 || nB > 1000) {
        fprintf(stderr, "Invalid private key. Must be between 1 and 1000.\n");
        return 1;
    }

    // Compute public points
    Point PA = EL_mul(alpha, nA);
    Point PB = EL_mul(alpha, nB);
    
    // Compute shared secret keys
    Point SK_A = EL_mul(PB, nA);
    Point SK_B = EL_mul(PA, nB);

    // Verify shared secrets match
    if (SK_A.x != SK_B.x || SK_A.y != SK_B.y) {
        fprintf(stderr, "Shared secret computation failed!\n");
        return 1;
    }

    printf("Shared secret key SK = (%d, %d)\n", SK_A.x, SK_A.y);

    // Derive keys using SHA-512
    unsigned char KA[64], KB[64];
    SHA512_hash((unsigned char *)&SK_A, sizeof(SK_A), KA);
    SHA512_hash((unsigned char *)&SK_A, sizeof(SK_A), KB);
    print_hex("KA", KA, sizeof(KA));
    print_hex("KB", KB, sizeof(KB));

    // Get Alice's message MA
    unsigned char MA[16];
    printf("Enter Alice's 128-bit message (16 bytes, space-separated hex): ");
    for (int i = 0; i < 16; i++) {
        scanf("%2hhx", &MA[i]);
    }

    // Encrypt the message MA
    unsigned char CA[16];
    Triple_AES_encrypt(MA, CA, KA);

    // Generate the MAC for MA
    unsigned char MACA[64];
    MAC_generate(KA, MA, sizeof(MA), MACA);
    print_hex("Ciphertext CA", CA, sizeof(CA));
    print_hex("MACA", MACA, sizeof(MACA));

    // Bob's part: receive ciphertext and MAC
    unsigned char CB[16], MACB[64];
    printf("Enter Bob's received ciphertext (CA) in hexadecimal (space-separated): ");
    for (int i = 0; i < 16; i++) {
        scanf("%2hhx", &CB[i]);
    }
    printf("Enter Bob's received MACA in hexadecimal (space-separated): ");
    for (int i = 0; i < 64; i++) {
        scanf("%2hhx", &MACB[i]);
    }

    // Bob decrypts the message
    unsigned char MB[16];
    Triple_AES_decrypt(CA, MB, KB);

    // Generate MAC for MB
    unsigned char MACC[64];
    MAC_generate(KB, MB, sizeof(MB), MACC);
    print_hex("Decrypted message MB", MB, sizeof(MB));
    print_hex("MACC", MACC, sizeof(MACC));

    // Verify the messages and MACs
    if (memcmp(MA, MB, sizeof(MA)) == 0 && memcmp(MACA, MACC, sizeof(MACA)) == 0) {
        printf("Success: MA = MB and MACA = MACB\n");
    } else {
        printf("Failure: MA != MB or MACA != MACB\n");
    }

    return 0;
}
