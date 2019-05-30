#include <time.h>
#include "mpir.h"
#include <assert.h>

//随机生成一个素数
void mygen_prime(mpz_t prime)
{
    gmp_randstate_t grt;
    gmp_randinit_default(grt);
    gmp_randseed_ui(grt, (mpir_ui)time(NULL));

    mpz_t p;
    mpz_init(p);
    mpz_urandomb(p, grt, 1024); //随机生成512位的大整数
    mpz_nextprime(prime, p);    //使用GMP自带的素数生成函数
    mpz_clear(p);
}

int ShengChengMiYao(mpz_t n, mpz_t e, mpz_t d)
{
    gmp_randstate_t grt;
    gmp_randinit_default(grt);                 //随机数生成初始化
    gmp_randseed_ui(grt, (mpir_ui)time(NULL)); //随机数生成设置种子

    // 随机生成两个不同大素数p,q;
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);
    mygen_prime(p);
    mygen_prime(q);

    // 计算n=pq;
    mpz_mul(n, p, q);

    // phi(n)=(p-1)(q-1);
    mpz_t phin, pjian1, qjian1;
    mpz_init(phin);
    mpz_init(pjian1);
    mpz_init(qjian1);
    mpir_ui one = 1;
    mpz_sub_ui(pjian1, p, one);
    mpz_sub_ui(qjian1, q, one);
    mpz_mul(phin, pjian1, qjian1);

    // 随机选取整数e, 1<e<phi(n),满足(e,phi(n))=1
    mpz_t r;
    mpz_init(r);
    mpz_t tmp2;
    mpz_init(tmp2);
    mpz_set_ui(tmp2, one); //tmp2=1;
    do
    {
        mpz_urandomm(e, grt, phin);
        mpz_gcd(r, e, phin);
    } while (mpz_cmp(r, tmp2) != 0);

    // 利用mpz自带的函数求出满足ed=1 mod(phi(n))的整数d
    assert(mpz_invert(d, e, phin) != 0);

    mpz_clears(p, q, phin, pjian1, qjian1, r, tmp2, '\0');
    return 0;
}

void Encrypt(const char *plain, mpz_t n, mpz_t e, mpz_t cipher)
{
    mpz_t base;
    mpz_init(base);

    if (mpz_set_str(base, plain, 16) == -1)
        assert(0);
    gmp_printf("base:%ZX\n", base);
    mpz_powm(cipher, base, e, n);

    mpz_clear(base);
}

void Decrypt(mpz_t cipher, mpz_t n, mpz_t d, mpz_t restored)
{
    mpz_powm(restored, cipher, d, n);
}
