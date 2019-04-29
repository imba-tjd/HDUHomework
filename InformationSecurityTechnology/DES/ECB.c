#include "Common.c"

int ECBEncrypt(Context *con)
{
    InitScope();
    (void)prep;
    for (int i = 0; i < con->length; i += 8)
        DES_EncryptBlock(plaintext + i, subkeys, ciphertext + i);
    return 0;
}

int ECBDecrypt(Context *con)
{
    InitScope();
    (void)prep;
    for (int i = 0; i < con->length; i += 8)
        DES_DecryptBlock(ciphertext + i, subkeys, plaintext + i);
    return 0;
}

int main(void)
{
    Run(ECBEncrypt, ECBDecrypt);
    return 0;
}
