#include "Common.c"

int CFBEncrypt(Context *con)
{
    InitScope();
    for (int i = 0; i < con->length; i += 8)
    {
        DES_EncryptBlock(prep, subkeys, ciphertext + i);
        DES_XOR(ciphertext + i, plaintext + i, 8);
        prep = ciphertext + i;
    }
    memcpy(con->pre, prep, 8);
    return 0;
}

int CFBDecrypt(Context *con)
{
    InitScope();
    for (int i = 0; i < con->length; i += 8)
    {
        DES_EncryptBlock(prep, subkeys, plaintext + i);
        DES_XOR(plaintext + i, ciphertext + i, 8);
        prep = ciphertext + i;
    }
    memcpy(con->pre, prep, 8);
    return 0;
}

int main(void)
{
    Run(CFBEncrypt, CFBDecrypt);
    return 0;
}
