#include "Common.c"

int CBCEncrypt(Context *con)
{
    InitScope();
    char buffer[8]; // 因为DES_EncryptBlock允许明文和密文相同，其实也可以直接使用密文数组，但仍需memcpy一次
    for (int i = 0; i < con->length; i += 8)
    {
        memcpy(buffer, plaintext + i, 8);
        DES_XOR(buffer, prep, 8);
        DES_EncryptBlock(buffer, subkeys, ciphertext + i);
        prep = ciphertext + i;
    }
    memcpy(con->pre, prep, 8);
    return 0;
}

int CBCDecrypt(Context *con)
{
    InitScope();
    for (int i = 0; i < con->length; i += 8)
    {
        DES_DecryptBlock(ciphertext + i, subkeys, plaintext + i);
        DES_XOR(plaintext + i, prep, 8);
        prep = ciphertext + i;
    }
    memcpy(con->pre, prep, 8);
    return 0;
}

int main(void)
{
    Run(CBCEncrypt, CBCDecrypt);
    return 0;
}
