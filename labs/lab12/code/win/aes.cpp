/** Abstract:
    Sample program for AES-CBC encryption using CNG    
    Example for use of BCrypt/NCrypt API to 
    encrypt data with CNG by using the advanced encryption standard symmetric encryption algorithm.
    Ref: 
    1. https://docs.microsoft.com/en-us/windows/win32/seccng/encrypting-data-with-cng

    How to compile & run?
    Compile: 
        cl aes.cpp
    Run:
        1. Try to sign and verify at least three messages
        2. Usage: .\aes <message to be encrypted>
        3. example: .\aes "ITS330 is really interesting!"

--*/

#include <windows.h>
#include <stdio.h>
#include <bcrypt.h>

#pragma comment (lib, "Ncrypt.lib")
#pragma comment (lib, "Bcrypt.lib")

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

// #define MIC

#ifdef MIC
const BYTE rgbPlaintext[] = 
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x00, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A//, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};
#endif //MIC

static const BYTE rgbIV[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};

static const BYTE rgbAES128Key[] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x00, 0x01, 0x00, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x00, 0x0C, 0x0D, 0x0E, 0x0F
};

void PrintBytes(
                IN BYTE     *pbPrintData,
                IN DWORD    cbDataLen)
{
    DWORD dwCount = 0;

    for(dwCount=0; dwCount < cbDataLen;dwCount++)
    {
        printf("0x%02x, ",pbPrintData[dwCount]);

        if(0 == (dwCount + 1 )%10) putchar('\n');
    }

    printf("\n\n");

}

int __cdecl wmain(
                   int                      argc, 
                   __in_ecount(argc) LPWSTR *wargv)
{

    BCRYPT_ALG_HANDLE       hAesAlg                     = NULL;
    BCRYPT_KEY_HANDLE       hKey                        = NULL;
    NTSTATUS                status                      = STATUS_UNSUCCESSFUL;
    DWORD                   cbCipherText                = 0, 
                            cbPlainText                 = 0,
                            cbData                      = 0, 
                            cbKeyObject                 = 0,
                            cbBlockLen                  = 0,
                            cbBlob                      = 0;
    PBYTE                   pbCipherText                = NULL,
                            pbPlainText                 = NULL,
                            pbKeyObject                 = NULL,
                            pbIV                        = NULL,
                            pbBlob                      = NULL;

#ifdef MIC
    UNREFERENCED_PARAMETER(argc);
    UNREFERENCED_PARAMETER(wargv);
    printf("Line %d: len of rgbPlaintext: %d\n", __LINE__, sizeof(rgbPlaintext));
#else    
    if(argc != 2){
        printf("Usage: ./aes <message to be encrytped\n");
        return 1;
    }


    int blen = wcslen(wargv[1])*sizeof(wchar_t);
    PBYTE rgbPlaintext = (PBYTE)calloc(wcslen(wargv[1]), sizeof(wchar_t));
    memcpy(rgbPlaintext, wargv[1], blen);
    printf("1. The plaintext with length %d in Unicode UTF-16L is:\n", blen);
    PrintBytes(rgbPlaintext, blen);
    // get the size of the pointer instead of the memory it points to
    //printf("Line %d: len of rgbPlaintext: %zd\n", __LINE__, sizeof(rgbPlaintext));
#endif

    // Open an algorithm handle.
    printf("2. Open an algorithm handle\n");
    if(!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
                                                &hAesAlg,
                                                BCRYPT_AES_ALGORITHM,
                                                NULL,
                                                0)))
    {
        wprintf(L"2. **** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
        goto Cleanup;
    }

    // Calculate the size of the buffer to hold the KeyObject.
    printf("3. Calculate the size of the buffer to hold the KeyObject\n");
    if(!NT_SUCCESS(status = BCryptGetProperty(
                                        hAesAlg, 
                                        BCRYPT_OBJECT_LENGTH, 
                                        (PBYTE)&cbKeyObject, 
                                        sizeof(DWORD), 
                                        &cbData, 
                                        0)))
    {
        wprintf(L"3. **** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    // Allocate the key object on the heap.
    printf("4. Allocate the key object on the heap\n");
    pbKeyObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbKeyObject);
    if(NULL == pbKeyObject)
    {
        wprintf(L"4. **** memory allocation failed\n");
        goto Cleanup;
    }

   // Calculate the block length for the IV.
   printf("5. Calculate the block length for the IV\n");
    if(!NT_SUCCESS(status = BCryptGetProperty(
                                        hAesAlg, 
                                        BCRYPT_BLOCK_LENGTH, 
                                        (PBYTE)&cbBlockLen, 
                                        sizeof(DWORD), 
                                        &cbData, 
                                        0)))
    {
        wprintf(L"5. **** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    // Determine whether the cbBlockLen is not longer than the IV length.
    printf("6. Determine whether the cbBlockLen is not longer than the IV length\n");
    if (cbBlockLen > sizeof (rgbIV))
    {
        wprintf (L"6. **** block length is longer than the provided IV length\n");
        goto Cleanup;
    }

    // Allocate a buffer for the IV. The buffer is consumed during the 
    // encrypt/decrypt process.
    printf("7. Allocate a buffer for the IV. The buffer is consumed during the encrypt/decrypt process\n");
    pbIV= (PBYTE) HeapAlloc (GetProcessHeap (), 0, cbBlockLen);
    if(NULL == pbIV)
    {
        wprintf(L"7. **** memory allocation failed\n");
        goto Cleanup;
    }

    memcpy(pbIV, rgbIV, cbBlockLen);

    printf("7. Set AES chain mode as CBC\n");
    if(!NT_SUCCESS(status = BCryptSetProperty(
                                hAesAlg, 
                                BCRYPT_CHAINING_MODE, 
                                (PBYTE)BCRYPT_CHAIN_MODE_CBC, 
                                sizeof(BCRYPT_CHAIN_MODE_CBC), 
                                0)))
    {
        wprintf(L"7. **** Error 0x%x returned by BCryptSetProperty\n", status);
        goto Cleanup;
    }

                

     // Generate the key from supplied input key bytes.
     printf("8. Generate the key object from supplied input key bytes\n");
    if(!NT_SUCCESS(status = BCryptGenerateSymmetricKey(
                                        hAesAlg, 
                                        &hKey, 
                                        pbKeyObject, 
                                        cbKeyObject, 
                                        (PBYTE)rgbAES128Key, 
                                        sizeof(rgbAES128Key), 
                                        0)))
    {
        wprintf(L"8. **** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
        goto Cleanup;
    }

  
    // Save another copy of the key for later.
    printf("9. Determine the space needed for saving another copy of the key for later\n");
    if(!NT_SUCCESS(status = BCryptExportKey(
                                        hKey,
                                        NULL,
                                        BCRYPT_OPAQUE_KEY_BLOB,
                                        NULL,
                                        0,
                                        &cbBlob,
                                        0)))
    {
        wprintf(L"9. **** Error 0x%x returned by BCryptExportKey\n", status);
        goto Cleanup;
    }


    // Allocate the buffer to hold the BLOB.
    printf("10. Allocate the buffer to hold the key blob\n");
    pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob);
    if(NULL == pbBlob)
    {
        wprintf(L"10. **** memory allocation failed\n");
        goto Cleanup;
    }

    printf("11. Save a copy of the key to the BLOB\n");
    if(!NT_SUCCESS(status = BCryptExportKey(
                                        hKey, 
                                        NULL, 
                                        BCRYPT_OPAQUE_KEY_BLOB,
                                        pbBlob, 
                                        cbBlob, 
                                        &cbBlob, 
                                        0)))
    {
        wprintf(L"11. **** Error 0x%x returned by BCryptExportKey\n", status);
        goto Cleanup;
    }

#ifdef MIC    
    cbPlainText = sizeof(rgbPlaintext);
#else
    cbPlainText = blen;
#endif    
    printf("Line %d: cbPlainText: %d\n", __LINE__, cbPlainText);

    printf("12. Allocate memory for a copy of the plaintext\n");
    pbPlainText = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbPlainText);
    if(NULL == pbPlainText)
    {
        wprintf(L"12. **** memory allocation failed\n");
        goto Cleanup;
    }

#ifdef MIC
    memcpy(pbPlainText, rgbPlaintext, sizeof(rgbPlaintext));
#else
    memcpy(pbPlainText, rgbPlaintext, blen);
#endif    
    
    //
    // Get the output buffer size.
    //
    printf("13. Determine the output buffer size of the ciphertext\n");
    if(!NT_SUCCESS(status = BCryptEncrypt(
                                        hKey, 
                                        pbPlainText, 
                                        cbPlainText,
                                        NULL,
                                        pbIV,
                                        cbBlockLen,
                                        NULL, 
                                        0, 
                                        &cbCipherText, 
                                        BCRYPT_BLOCK_PADDING)))
    {
        wprintf(L"13. **** Error 0x%x returned by BCryptEncrypt\n", status);
        goto Cleanup;
    }

    printf("14. Allocate memory for the ciphertext\n");
    pbCipherText = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbCipherText);
    if(NULL == pbCipherText)
    {
        wprintf(L"14. **** memory allocation failed\n");
        goto Cleanup;
    }

    // Use the key to encrypt the plaintext buffer.
    // For block sized messages, block padding will add an extra block.
    printf("15. Encrypt the plaintext buffer. For block sized messages, block padding will add an extra block\n");
    if(!NT_SUCCESS(status = BCryptEncrypt(
                                        hKey, 
                                        pbPlainText, 
                                        cbPlainText,
                                        NULL,
                                        pbIV,
                                        cbBlockLen, 
                                        pbCipherText, 
                                        cbCipherText, 
                                        &cbData, 
                                        BCRYPT_BLOCK_PADDING)))
    {
        wprintf(L"15. **** Error 0x%x returned by BCryptEncrypt\n", status);
        goto Cleanup;
    }

    printf("\n16. ==========Encryption summary=======\n");
    printf("cbPlainText: %d, cbBlockLen: %d, cbCipherText: %d\n", cbPlainText, cbBlockLen, cbCipherText);
    printf("pbPlainText: \n");
    PrintBytes(pbPlainText, cbPlainText);
    printf("pbCipherText: \n");
    PrintBytes(pbCipherText, cbCipherText);

    // Destroy the key and reimport from saved BLOB.
    printf("17. Destroy the used key\n");
    if(!NT_SUCCESS(status = BCryptDestroyKey(hKey)))
    {
        wprintf(L"17. **** Error 0x%x returned by BCryptDestroyKey\n", status);
        goto Cleanup;
    }    
    hKey = 0;

    if(pbPlainText)
    {
        HeapFree(GetProcessHeap(), 0, pbPlainText);
    }

    pbPlainText = NULL;

    // We can reuse the key object.
    memset(pbKeyObject, 0 , cbKeyObject);

    
    // Reinitialize the IV because encryption would have modified it.
    memcpy(pbIV, rgbIV, cbBlockLen);

    printf("18. Reimport the key from the saved BLOB copy\n");
    if(!NT_SUCCESS(status = BCryptImportKey(
                                        hAesAlg,
                                        NULL,
                                        BCRYPT_OPAQUE_KEY_BLOB,
                                        &hKey,
                                        pbKeyObject,
                                        cbKeyObject,
                                        pbBlob,
                                        cbBlob,
                                        0)))
    {
        wprintf(L"18. **** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
        goto Cleanup;
    }
       

    //
    // Get the output buffer size.
    //
    printf("19. Determine the output buffer size for decryption\n");
    if(!NT_SUCCESS(status = BCryptDecrypt(
                                    hKey, 
                                    pbCipherText, 
                                    cbCipherText, 
                                    NULL,
                                    pbIV,
                                    cbBlockLen,
                                    NULL, 
                                    0, 
                                    &cbPlainText, 
                                    BCRYPT_BLOCK_PADDING)))
    {
        wprintf(L"19. **** Error 0x%x returned by BCryptDecrypt\n", status);
        goto Cleanup;
    }

    printf("20. Allocate memory for decrypted message\n");
    pbPlainText = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbPlainText);
    if(NULL == pbPlainText)
    {
        wprintf(L"20. **** memory allocation failed\n");
        goto Cleanup;
    }

    printf("21. Decrypt the ciphertext\n");
    if(!NT_SUCCESS(status = BCryptDecrypt(
                                    hKey, 
                                    pbCipherText, 
                                    cbCipherText, 
                                    NULL,
                                    pbIV, 
                                    cbBlockLen,
                                    pbPlainText, 
                                    cbPlainText, 
                                    &cbPlainText, 
                                    BCRYPT_BLOCK_PADDING)))
    {
        wprintf(L"21. **** Error 0x%x returned by BCryptDecrypt\n", status);
        goto Cleanup;
    }

    printf("\n22. ==========Decryption summary=======\n");
    printf("cbPlainText: %d, cbBlockLen: %d, cbCipherText: %d\n", cbPlainText, cbBlockLen, cbCipherText);
    printf("pbCipherText: \n");
    PrintBytes(pbCipherText, cbCipherText);
    printf("pbPlainText: \n");
    PrintBytes(pbPlainText, cbPlainText);


    printf("23. Compare the decrypted message against the original plaintext\n");
    if (0 != memcmp(pbPlainText, (PBYTE)rgbPlaintext, sizeof(rgbPlaintext))) 
    {
        wprintf(L"23. Expected decrypted text comparison failed.\n");
        goto Cleanup;
    } 

    wprintf(L"\nMatched! Encryption then decryption succeeded!\n");


Cleanup:

    if(hAesAlg)
    {
        BCryptCloseAlgorithmProvider(hAesAlg,0);
    }

    if (hKey)    
    {
        BCryptDestroyKey(hKey);
    }

    if(pbCipherText)
    {
        HeapFree(GetProcessHeap(), 0, pbCipherText);
    }

    if(pbPlainText)
    {
        HeapFree(GetProcessHeap(), 0, pbPlainText);
    }

    if(pbKeyObject)
    {
        HeapFree(GetProcessHeap(), 0, pbKeyObject);
    }

    if(pbIV)
    {
        HeapFree(GetProcessHeap(), 0, pbIV);
    }

    return 0;
}