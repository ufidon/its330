/** Abstract:
    Sample program for ECDSA 256 signing using CNG    
    Example for use of BCrypt/NCrypt API    
    Persisted key for signing and ephemeral key for verification
    Ref: 
    1. https://docs.microsoft.com/en-us/windows/win32/seccng/signing-data-with-cng

    How to compile & run?
    Compile: 
        cl signverify.c
    Run:
        1. Try to sign and verify at least three messages
        2. Usage: .\signverify <message to be signed>
        3. example: .\signverify "ITS330 is really interesting!"

--*/
#pragma comment (lib, "Ncrypt.lib")
#pragma comment (lib, "Bcrypt.lib")

#include <windows.h>
#include <stdio.h>
#include <bcrypt.h>
#include <ncrypt.h>


#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

void printbufinhex(PBYTE buf, int len)
{
    int i = len;
    for (i = 0; i < len; i++)
    {
        if (i%10 == 0)
        {
            printf("\n");
        }
        printf("%02X ", buf[i]);        
    } 
    printf("\n\n");
}

void __cdecl wmain(
                   int                      argc, 
                   __in_ecount(argc) LPWSTR *wargv)
{
    NCRYPT_PROV_HANDLE      hProv           = NULL;
    NCRYPT_KEY_HANDLE       hKey            = NULL;
    BCRYPT_KEY_HANDLE       hTmpKey         = NULL;
    SECURITY_STATUS         secStatus       = ERROR_SUCCESS;
    BCRYPT_ALG_HANDLE       hHashAlg        = NULL,
                            hSignAlg        = NULL;
    BCRYPT_HASH_HANDLE      hHash           = NULL;
    NTSTATUS                status          = STATUS_UNSUCCESSFUL;
    DWORD                   cbData          = 0,
                            cbHash          = 0,
                            cbBlob          = 0,
                            cbSignature     = 0,
                            cbHashObject    = 0;
    PBYTE                   pbHashObject    = NULL;
    PBYTE                   pbHash          = NULL,
                            pbBlob          = NULL,
                            pbSignature     = NULL;

    if (argc == 2)
    {


        PBYTE rgbMsg = (PBYTE)wargv[1];

        //open an algorithm handle
        wprintf(L"1. open a hash algorithm handle\n");
        if(!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
                                                    &hHashAlg,
                                                    BCRYPT_SHA1_ALGORITHM,
                                                    NULL,
                                                    0)))
        {
            wprintf(L"1. **** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
            goto Cleanup;
        }

        wprintf(L"2. open a signing algorithm handle\n");
        if(!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
                                                    &hSignAlg,
                                                    BCRYPT_ECDSA_P256_ALGORITHM,
                                                    NULL,
                                                    0)))
        {
            wprintf(L"2. **** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
            goto Cleanup;
        }

        //calculate the size of the buffer to hold the hash object
        wprintf(L"3. calculate the size of the buffer to hold the hash object\n");
        if(!NT_SUCCESS(status = BCryptGetProperty(
                                            hHashAlg, 
                                            BCRYPT_OBJECT_LENGTH, 
                                            (PBYTE)&cbHashObject, 
                                            sizeof(DWORD), 
                                            &cbData, 
                                            0)))
        {
            wprintf(L"3. **** Error 0x%x returned by BCryptGetProperty\n", status);
            goto Cleanup;
        }

        //allocate the hash object on the heap
        wprintf(L"4. allocate the hash object on the heap\n");
        pbHashObject = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHashObject);
        if(NULL == pbHashObject)
        {
            wprintf(L"4. **** memory allocation failed\n");
            goto Cleanup;
        }

        //calculate the length of the hash
        wprintf(L"5. calculate the length of the hash\n");
        if(!NT_SUCCESS(status = BCryptGetProperty(
                                            hHashAlg, 
                                            BCRYPT_HASH_LENGTH, 
                                            (PBYTE)&cbHash, 
                                            sizeof(DWORD), 
                                            &cbData, 
                                            0)))
        {
            wprintf(L"5. **** Error 0x%x returned by BCryptGetProperty\n", status);
            goto Cleanup;
        }

        //allocate the hash buffer on the heap
        wprintf(L"6. allocate the hash buffer on the heap\n");
        pbHash = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbHash);
        if(NULL == pbHash)
        {
            wprintf(L"6. **** memory allocation failed\n");
            goto Cleanup;
        }

        //create a hash
        wprintf(L"7. create a hash\n");
        if(!NT_SUCCESS(status = BCryptCreateHash(
                                            hHashAlg, 
                                            &hHash, 
                                            pbHashObject, 
                                            cbHashObject, 
                                            NULL, 
                                            0, 
                                            0)))
        {
            wprintf(L"7. **** Error 0x%x returned by BCryptCreateHash\n", status);
            goto Cleanup;
        }
        

        //hash some data
        wprintf(L"8. hash the message:\n %s\n\n", (wchar_t*)rgbMsg);
        if(!NT_SUCCESS(status = BCryptHashData(
                                            hHash,
                                            (PBYTE)rgbMsg,
                                            sizeof(rgbMsg),
                                            0)))
        {
            wprintf(L"8. **** Error 0x%x returned by BCryptHashData\n", status);
            goto Cleanup;
        }
        
        //close the hash
        wprintf(L"9. close the hash\n");
        if(!NT_SUCCESS(status = BCryptFinishHash(
                                            hHash, 
                                            pbHash, 
                                            cbHash, 
                                            0)))
        {
            wprintf(L"9. **** Error 0x%x returned by BCryptFinishHash\n", status);
            goto Cleanup;
        }
        wprintf(L"\n10. The generated hash is:\n");
        printbufinhex(pbHash, cbHash);

        //open handle to KSP
        wprintf(L"11. open handle to KSP: Key Storage Provider\n");
        if(FAILED(secStatus = NCryptOpenStorageProvider(
                                                    &hProv, 
                                                    MS_KEY_STORAGE_PROVIDER, 
                                                    0)))
        {
            wprintf(L"11. **** Error 0x%x returned by NCryptOpenStorageProvider\n", secStatus);
            goto Cleanup;
        }

        //create a persisted key
        wprintf(L"12. create a persisted key\n");
        if(FAILED(secStatus = NCryptCreatePersistedKey(
                                                    hProv,
                                                    &hKey,
                                                    NCRYPT_ECDSA_P256_ALGORITHM,
                                                    L"my ecc key",
                                                    0,
                                                    0)))
        {
            wprintf(L"12. **** Error 0x%x returned by NCryptCreatePersistedKey\n", secStatus);
            goto Cleanup;
        }

        //create key on disk
        wprintf(L"13. create key on disk\n");
        if(FAILED(secStatus = NCryptFinalizeKey(hKey, 0)))
        {
            wprintf(L"13. **** Error 0x%x returned by NCryptFinalizeKey\n", secStatus);
            goto Cleanup;
        }

        //sign the hash
        wprintf(L"14. sign the hash\n");
        if(FAILED(secStatus = NCryptSignHash(
                                        hKey,
                                        NULL,
                                        pbHash,
                                        cbHash,
                                        NULL,
                                        0,
                                        &cbSignature,
                                        0)))
        {
            wprintf(L"14. **** Error 0x%x returned by NCryptSignHash\n", secStatus);
            goto Cleanup;
        }


        //allocate the signature buffer
        wprintf(L"15. allocate the signature buffer\n");
        pbSignature = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbSignature);
        if(NULL == pbSignature)
        {
            wprintf(L"15. **** memory allocation failed\n");
            goto Cleanup;
        }

        wprintf(L"16. save the signature in the signature buffer\n");
        if(FAILED(secStatus = NCryptSignHash(
                                        hKey,
                                        NULL,
                                        pbHash,
                                        cbHash,
                                        pbSignature,
                                        cbSignature,
                                        &cbSignature,
                                        0)))
        {
            wprintf(L"16. **** Error 0x%x returned by NCryptSignHash\n", secStatus);
            goto Cleanup;
        }

        wprintf(L"\n17. The signature on the hash is:\n");
        printbufinhex(pbSignature, cbSignature);

        wprintf(L"18. export the public key\n");
        if(FAILED(secStatus = NCryptExportKey(
                                            hKey,
                                            NULL,
                                            BCRYPT_ECCPUBLIC_BLOB,
                                            NULL,
                                            NULL,
                                            0,
                                            &cbBlob,
                                            0)))
        {
            wprintf(L"18. **** Error 0x%x returned by NCryptExportKey\n", secStatus);
            goto Cleanup;
        }

        wprintf(L"19. allocate the public key buffer\n");
        pbBlob = (PBYTE)HeapAlloc (GetProcessHeap (), 0, cbBlob);
        if(NULL == pbBlob)
        {
            wprintf(L"19. **** memory allocation failed\n");
            goto Cleanup;
        }

        wprintf(L"20. save the public key in the key buffer\n");
        if(FAILED(secStatus = NCryptExportKey(
                                            hKey,
                                            NULL,
                                            BCRYPT_ECCPUBLIC_BLOB,
                                            NULL,
                                            pbBlob,
                                            cbBlob,
                                            &cbBlob,
                                            0)))
        {
            wprintf(L"20. **** Error 0x%x returned by NCryptExportKey\n", secStatus);
            goto Cleanup;
        }

        wprintf(L"\n21. The public key is:\n");
        printbufinhex(pbBlob, cbBlob);

        wprintf(L"22. import key pair for signature verification\n");
        if(!NT_SUCCESS(status = BCryptImportKeyPair(
                                                hSignAlg,
                                                NULL,
                                                BCRYPT_ECCPUBLIC_BLOB,
                                                &hTmpKey,
                                                pbBlob,
                                                cbBlob,
                                                0)))
        {
            wprintf(L"22. **** Error 0x%x returned by BCryptImportKeyPair\n", status);
            goto Cleanup;
        }


        wprintf(L"23. signature verifying...\n");
        if(!NT_SUCCESS(status = BCryptVerifySignature(
                                                hTmpKey,
                                                NULL,
                                                pbHash,
                                                cbHash,
                                                pbSignature,
                                                cbSignature,
                                                0)))
        {
            wprintf(L"23. **** Error 0x%x returned by BCryptVerifySignature\n", status);
            goto Cleanup;
        }

        wprintf(L"24. Succeeded in signature verification!\n");

    Cleanup:

        if(hHashAlg)
        {
            BCryptCloseAlgorithmProvider(hHashAlg,0);
        }

        if(hSignAlg)
        {
            BCryptCloseAlgorithmProvider(hSignAlg,0);
        }

        if (hHash)    
        {
            BCryptDestroyHash(hHash);
        }

        if(pbHashObject)
        {
            HeapFree(GetProcessHeap(), 0, pbHashObject);
        }

        if(pbHash)
        {
            HeapFree(GetProcessHeap(), 0, pbHash);
        }

        if(pbSignature)
        {
            HeapFree(GetProcessHeap(), 0, pbSignature);
        }

        if(pbBlob)
        {
            HeapFree(GetProcessHeap(), 0, pbBlob);
        }

        if (hTmpKey)    
        {
            BCryptDestroyKey(hTmpKey);
        }

        if (hKey)    
        {
            NCryptDeleteKey(hKey, 0);
        }

        if (hProv)    
        {
            NCryptFreeObject(hProv);
        }

    }
    else
    {
        wprintf(L"Usage: .\\signverify <message to be signed>\n");
    }
    
}