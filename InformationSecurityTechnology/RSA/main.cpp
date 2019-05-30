#include <stdio.h>
#include "rsa.cpp"
#include "../MD5/getmd5.c"

#define SIGN

int main()
{
    mpz_t n, e, d;
    mpz_init(n);
    mpz_init(e);
    mpz_init(d);

    ShengChengMiYao(n, e, d);

    mpz_t *encKey, *decKey; mpz_t不可用=赋值
    char *plain;
#ifdef ENC
    plain = "1234567890ABCDEF";
    encKey = &e;
    decKey = &d;
#elif defined SIGN
    char md5[33];
    FILE *f = fopen("plain.txt", "rb");
    if (f == NULL)
        return -1;

    getmd5(f, md5);
    md5[32] = '\0';

    plain = md5;
    encKey = &d;
    decKey = &e;
#endif
    puts(plain);

    mpz_t cipher;
    mpz_init(cipher);
    Encrypt(plain, n, *encKey, cipher);
    gmp_printf("cipher:%ZX\n", cipher);

    mpz_t restored;
    mpz_init(restored);
    Decrypt(cipher, n, *decKey, restored);
    gmp_printf("restored:%ZX\n", restored);

    return 0;
}
