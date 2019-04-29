#ifndef _DES_c
#define _DES_c
#include "DES.c"
#endif
#include "MakeKeys.c"
#include <assert.h>

typedef struct
{
    size_t length;
    ElemType plainText[BUFSIZ];
    ElemType cipherText[BUFSIZ];
    ElemType subKeys[16][48];
    ElemType pre[8];
} Context;

#define InitScope()                         \
    assert(con->length % 8 == 0);           \
    ElemType *prep = con->pre;              \
    ElemType *plaintext = con->plainText;   \
    ElemType *ciphertext = con->cipherText; \
    ElemType(*subkeys)[48] = con->subKeys

// void SetPre(ElemType pre[8]);
int InitContext(Context *con, const char *pw)
{
    static_assert(BUFSIZ % 8 == 0, "BUFSIZ is not an integer multiple of eight");

    // TODO: pw长度大于7
    if (strlen(pw) > 7)
    {
        perror("pw too long!");
        return 1;
    }
    char pwbuffer[7] = {0};
    strncpy(pwbuffer, pw, 7);
    MakeSubKeys(pwbuffer, con->subKeys);
    // SetPre(con->pre);
    memcpy(con->pre, "12345678", 8);

    return 0;
}

int (*Encrypter)(Context *con);
int (*Decrypter)(Context *con);

#define InitIO(srcf, destf)                  \
    FILE *srcfile = fopen((srcf), "rb");     \
    FILE *destfile = fopen((destf), "wb");   \
    if (srcfile == NULL || destfile == NULL) \
    {                                        \
        perror("File opening failed.");      \
        return 1;                            \
    }

int DES_Encrypt(char *plainFile, char *keyStr, char *cipherFile)
{
    InitIO(plainFile, cipherFile);
    Context context;
    InitContext(&context, keyStr);

    while (0 != (context.length = fread(context.plainText, sizeof(char), BUFSIZ - 1, srcfile)))
    {
        // context.plainText[context.length++] = '\0';
        // if (context.length % 8 != 0)
        // {
        //     int rest = 8 - context.length % 8;
        //     memset(context.plainText + context.length, '\0', rest);
        //     context.length += rest;
        // }

        int rest = 8 - context.length % 8;
        memset(context.plainText + context.length, '\0', rest);
        context.length += rest;

        assert(context.length % 8 == 0);
        assert(Encrypter != NULL);

        Encrypter(&context);
        fwrite(context.cipherText, sizeof(ElemType), context.length, destfile);
    }

    fclose(srcfile);
    fclose(destfile);
    return 0;
}

int DES_Decrypt(char *cipherFile, char *keyStr, char *plainFile)
{
    InitIO(cipherFile, plainFile);
    Context context;
    InitContext(&context, keyStr);

    while (0 != (context.length = fread(context.cipherText, sizeof(char), BUFSIZ, srcfile)))
    {
        assert(context.length % 8 == 0);
        assert(Decrypter != NULL);

        Decrypter(&context);
        // fwrite(context.plainText, sizeof(ElemType), context.length, destfile);
        // fprintf(destfile, "%s", context.plainText);
        fputs(context.plainText, destfile);
    }

    fclose(srcfile);
    fclose(destfile);
    return 0;
}

int Run(int (*encrypter)(Context *con), int (*decrypter)(Context *con))
{
    Encrypter = (encrypter);
    Decrypter = (decrypter);
    char *plainfile = "plain.txt";
    char *cipherfile = "cipher.bin";
    char *decreptedfile = "restored.txt";
    char *pw = "1234567";

    DES_Encrypt(plainfile, pw, cipherfile);
    DES_Decrypt(cipherfile, pw, decreptedfile);

    return 0;
}
