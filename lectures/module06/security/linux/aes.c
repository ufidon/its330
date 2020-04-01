/**EVP Symmetric Encryption and Decryption
 * Ref: 
 * 1. https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
 * How to complile & run?
 * 
 * ATTENSION: 
 * Prerequisite: libssl-dev should be intalled before compiling.
 * run the following command to install libssl-dev:
 * sudo apt install libssl-dev
 * 
 * Compile: gcc -o aes aes.c -lcrypto
 * Run: ./aes password <message to be encrypted>
 * for example:
 * ./aes "P@ssword" "ITS330 is really interesting!"
 * try to encrypt at least three different messages with different passwords
*/

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

void handleErrors(void);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);

int main (int argc, char* argv[])
{
    if (argc == 3)
    {
        /*
        * Set up the key and iv. Do I need to say to not hard code these in a
        * real application? :-)
        */

        /* A 256 bit key */
        //unsigned char *key = (unsigned char *)"password";
        unsigned char *key = (unsigned char *)argv[1];

        /* A 128 bit IV */
        unsigned char *iv = (unsigned char *)"0123456789012345";

        /* Message to be encrypted */
        //unsigned char *plaintext = (unsigned char *)"The quick brown fox jumps over the lazy dog";
        unsigned char *plaintext = (unsigned char *)argv[2];

        /*
        * Buffer for ciphertext. Ensure the buffer is long enough for the
        * ciphertext which may be longer than the plaintext, depending on the
        * algorithm and mode.
        */
        unsigned char ciphertext[1024];

        /* Buffer for the decrypted text */
        unsigned char decryptedtext[1024];

        int decryptedtext_len, ciphertext_len;

        printf("\nThe message to be encrypted is:\n");
        printf("%s\n\n", plaintext);
        printf("The password for this encryption is:\n");
        printf("%s\n", key);

        /* Encrypt the plaintext */
        printf("\nEncrypting...\n\n");
        ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
                                ciphertext);

        /* Do something useful with the ciphertext here */
        printf("In the ciphertext, there are non-printable characters, \nso we print the ciphertext in hex format:\n\n");
        BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

        /* Decrypt the ciphertext */
        printf("\nDecrypting...\n");
        decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                    decryptedtext);

        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        /* Show the decrypted text */
        printf("\nThe decrypted text is, please compare it with the original message:\n\n");
        printf("%s\n", decryptedtext);
    }
    else
    {
        printf("Usage: ./aes password <message to be encrypted>\n");
    }
    

    return 0;
}


void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}


int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
