#ifndef _DES_c
#define _DES_c
#include "DES.c"
#endif

int MakeRawKey(const char pw[7], char rawkey[56])
{
    for (int i = 0; i < 7; i++)
        ByteToBit(pw[i], rawkey + i * 8);
    return 0;
}

int MakeKey(const char rawkey[56], ElemType key[64])
{
    for (int i = 0; i < 8; i++)
    {
        memcpy(key + 8 * i, rawkey + 7 * i, 7);
        char check = 0;
        for (int j = 8 * i; j < 8 * i + 7; j++)
            check ^= key[j];
        key[8 * i + 7] = check; // 奇数个1时check为1，即偶校验
    }
    return 0;
}

int MakeSubKeys(const char pw[7], ElemType subkeys[16][48])
{
    char rawkey[56];
    MakeRawKey(pw, rawkey);
    ElemType key[64];
    MakeKey(rawkey, key);
    DES_MakeSubKeys(key, subkeys);
    return 0;
}

#define GetProperSize(x) ((x) % 8 == 0 ? (x) : ((x) + 8 - (x) % 8))
#define Length(x) (sizeof(x) / sizeof(*x))

// 不需要使用，DES_DecryptBlock中已经反向使用子密钥了
int SwapSubKeys(ElemType subkeys[16][48])
{
    ElemType temp[48];
    for (int i = 0; i < 8; i++)
    {
        memcpy(temp, subkeys[i], Length(temp));
        memcpy(subkeys[i], subkeys[15 - i], 48);
        memcpy(subkeys[15 - i], temp, Length(temp));
    }
    return 0;
}
