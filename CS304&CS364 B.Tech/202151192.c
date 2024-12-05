// name-archit verma
// id - 202151192
#include <stdio.h>
#include <string.h>

void generatedMatrixbysve(char key[], char keyBYMatrix[6][5])
{

    int verma_i, verma_j, k, presentVerma[26] = {0};
    char special_char[4] = {',', '.', '?', ';'};

    for (k = 0, verma_i = 0; key[k] != '\0'; ++k)
    { // gnerating key with the help of first key charachter
        if (key[k] != ',' && key[k] != '.' && key[k] != '?' && key[k] != ';' && !presentVerma[toupper(key[k]) - 'A'])
        {
            keyBYMatrix[(verma_i) / 5][verma_i % 5] = toupper(key[k]);
            presentVerma[toupper(key[k]) - 'A'] = 1;
            ++verma_i;
        }
        else if (key[k] == ',' || key[k] == '.' || key[k] == '?' || key[k] == ';')
        {
            keyBYMatrix[(verma_i) / 5][verma_i % 5] = (key[k]);
            for (int c = 0; c < 4; c++)
            {
                if (special_char[c] == key[k])
                {
                    special_char[c] = '@';
                }
            }
            ++verma_i;
        }
    }

    for (k = 0; k < 26; ++k)
    { // entering the left character in the key matrix which is not visited
        if (!presentVerma[k])
        {
            keyBYMatrix[(verma_i) / 5][verma_i % 5] = toupper('A' + k);
            ++verma_i;
        }
    }

    for (k = 0; k < 4; k++)
    {
        // entering the left character in the key matrix
        if (special_char[k] != '@')
        {
            keyBYMatrix[(verma_i) / 5][verma_i % 5] = special_char[k];
            ++verma_i;
        }
    }
}

// printing the 6X5 key matri
void printMatrixbyve(char keyBYMatrix[6][5])
{
    printf("Key Matrix:\n");
    for (int verma_i = 0; verma_i < 6; ++verma_i)
    {
        for (int verma_j = 0; verma_j < 5; ++verma_j)
        {
            printf("%c ", keyBYMatrix[verma_i][verma_j]);
        }
        printf("\n");
    }
}
void playfaireneenbyeve(char *plaintEXT, char key___MATRIX_[6][5], char *cipherverma)
{
    int verma_i, verma_j;
    int row1, col1, row2, col2;

    for (verma_i = 0; verma_i < strlen(plaintEXT); verma_i += 2)
    {
        // Find positions of the characters in the key matrix
        for (verma_j = 0; verma_j < 6; verma_j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (key___MATRIX_[verma_j][k] == plaintEXT[verma_i])
                {
                    row1 = verma_j;
                    col1 = k;
                }
                if (key___MATRIX_[verma_j][k] == plaintEXT[verma_i + 1])
                {
                    row2 = verma_j;
                    col2 = k;
                }
            }
        }
        // Encrypt the characters
        if (row1 == row2)
        {
            cipherverma[verma_i] = key___MATRIX_[row1][(col1 + 1) % 5];
            cipherverma[verma_i + 1] = key___MATRIX_[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2)
        {
            cipherverma[verma_i] = key___MATRIX_[(row1 + 1) % 6][col1];
            cipherverma[verma_i + 1] = key___MATRIX_[(row2 + 1) % 6][col2];
        }
        else
        {
            cipherverma[verma_i] = key___MATRIX_[row1][col2];
            cipherverma[verma_i + 1] = key___MATRIX_[row2][col1];
        }
    }
}

// AFFINE

// Function to encrypt using Affine cipher
char affineencrypt(char plaintEXT, int a, int b, int m)
{

    if (isalpha(plaintEXT))
    {
        char encryptionhoga;
        int x = toupper(plaintEXT) - 'A';
        int encryptedValue = (a * x + b) % m;
        encryptionhoga = encryptedValue + 'A';
        return encryptionhoga;
    }
    // If the character is not a letter, leave it unchanged
    return plaintEXT;
}

// Shift Cipher

// Function to encrypt using Shift cipher
char SHiftDEcve(char plaintEXT, int key)
{
    if (isalpha(plaintEXT))
    {
        char encryptionhoga;
        int offset = isupper(plaintEXT) ? 'A' : 'a';
        encryptionhoga = (plaintEXT - offset + key) % 26 + offset;
        return encryptionhoga;
    }
    // If the character is not a letter, leave it unchanged
    return plaintEXT;
}

char SHIFTBYSHEKDECR(char cipherverma, int key)
{
    if (isalpha(cipherverma))
    {
        char DECBYSHEKROTP;
        int offset = isupper(cipherverma) ? 'A' : 'a';
        DECBYSHEKROTP = (cipherverma - offset - key + 26) % 26 + offset;
        return DECBYSHEKROTP;
    }
    // If the character is not a letter, leave it unchanged
    return cipherverma;
}

int modInverse(int a, int m);

char AFFINEDECRYPTIONBYshek(char cipherverma, int a, int b, int m)
{
    if (isalpha(cipherverma))
    {
        char DECBYSHEKROTP;
        int x = toupper(cipherverma) - 'A';
        int ainverma = modInverse(a, m);

        int decryptedValue = ainverma * (x - b + m) % m;
        DECBYSHEKROTP = decryptedValue + 'A';
        return DECBYSHEKROTP;
    }
    // If the character is not a letter, leave it unchanged
    return cipherverma;
}

int modInverse(int a, int m)
{
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

void playfairverma(char *cipherverma, char key___MATRIX_[6][5], char *DecryptionVerma)
{
    int verma_i, verma_j;
    int row1, col1, row2, col2;

    for (verma_i = 0; verma_i < strlen(cipherverma); verma_i += 2)
    {
        // Find positions of the characters in the key matrix
        for (verma_j = 0; verma_j < 6; verma_j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (key___MATRIX_[verma_j][k] == cipherverma[verma_i])
                {
                    row1 = verma_j;
                    col1 = k;
                }
                if (key___MATRIX_[verma_j][k] == cipherverma[verma_i + 1])
                {
                    row2 = verma_j;
                    col2 = k;
                }
            }
        }
        // Decrypt the characters
        if (row1 == row2)
        {
            DecryptionVerma[verma_i] = key___MATRIX_[row1][(col1 - 1 + 5) % 5];
            DecryptionVerma[verma_i + 1] = key___MATRIX_[row2][(col2 - 1 + 5) % 5];
        }
        else if (col1 == col2)
        {
            DecryptionVerma[verma_i] = key___MATRIX_[(row1 - 1 + 6) % 6][col1];
            DecryptionVerma[verma_i + 1] = key___MATRIX_[(row2 - 1 + 6) % 6][col2];
        }
        else
        {
            DecryptionVerma[verma_i] = key___MATRIX_[row1][col2];
            DecryptionVerma[verma_i + 1] = key___MATRIX_[row2][col1];
        }
    }
}

int main()
{
    char plaintEXT[100]; // Adabhijust the size based on your needs
    char key[100];       // Adabhijust the size based on your needs
    char key___MATRIX_[6][5];
    char cipherverma[100]; // Adabhijust the size based on your needs

    // Input plaintEXT and key
    printf("Enter plaintEXT: ");
    scanf("%s", plaintEXT);

    printf("%s", plaintEXT);

    char DEC[100]; // Adabhijust the size based on your needs
    strcpy(DEC, plaintEXT);

    printf("Enter key: ");
    scanf("%s", key);

    // Generate key matrix
    generatedMatrixbysve(key, key___MATRIX_);

    // Print key matrix
    printMatrixbyve(key___MATRIX_);

    // Encrypt plaintEXT
    playfaireneenbyeve(plaintEXT, key___MATRIX_, cipherverma);

    // Print cipherverma

    printf("cipherverma: %s\n", cipherverma);

    printf("Affine cipherverma: ");
    for (int verma_i = 0; verma_i < strlen(cipherverma); ++verma_i)
    {
        printf("%c", affineencrypt(cipherverma[verma_i], 11, 15, 30));
    }
    printf("\n");

    for (int key = 0; key <= 29; ++key)
    {
        printf("Shift cipherverma (Key %d): ", key);
        for (int verma_i = 0; cipherverma[verma_i] != '\0'; ++verma_i)
        {
            printf("%c", SHiftDEcve(cipherverma[verma_i], key));
        }
        printf("\n");
    }

    char dec[100]; // Adabhijust the size based on your needs
    int decIndex = 0;

    for (int verma_i = 0; cipherverma[verma_i] != '\0'; ++verma_i)
    {
        dec[decIndex++] = SHiftDEcve(cipherverma[verma_i], 15);
    }

    // DECRYPTING FOR INDEX = decIndex
    dec[decIndex] = '\0';

    printf("%s", dec);

    printf("\n");

    /// DECRYPTING CODE STARTS HERE

    int decInd = 0;
    for (int verma_i = 0; cipherverma[verma_i] != '\0'; ++verma_i)
    {
        dec[decInd++] = SHIFTBYSHEKDECR(dec[verma_i], 15);
    }

    dec[decInd] = '\0'; // Null-terminate the string

    // Print decrypted text
    printf("Decrypted Text: %s\n", dec);

    int ainverma = modInverse(11, 30);

    if (ainverma == -1)
    {
        printf("Inverse doesn't exist for the given coefficient 'a' and modulus 'm'.\n");
        return 1;
    }

    // Decrypt cipherverma
    int decInde = 0;
    for (int verma_i = 0; cipherverma[verma_i] != '\0'; ++verma_i)
    {
        dec[decInde++] = AFFINEDECRYPTIONBYshek(cipherverma[verma_i], ainverma, 15, 30);
    }

    dec[decInde] = '\0'; // Null-terminate the string

    // Print decrypted text
    printf("Decrypted Text: %s\n", dec);

    playfairverma(dec, key___MATRIX_, plaintEXT);

    // Print decrypted text

    printf("DECRYPTED TEXT: %s\n", DEC);

    return 0;
}