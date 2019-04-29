#ifndef DES_c
#define DES_c
#include "DES.c"
#endif
#include "MakeKeys.c"

int Encrypt(ElemType plaintext[], ElemType subkeys[16][48], ElemType ciphertext[], size_t count)
{
  int limit = count / 8;
  for (int i = 0; i < limit; i++)
    DES_EncryptBlock(plaintext + i * 8, subkeys, ciphertext + i * 8);
  if (count % 8 != 0)
  {
    ElemType rest[8] = {0};
    // memset(ciphertext + i * 8, 0, 8 - count % 8);
    memcpy(rest, plaintext + limit * 8, count % 8);
    DES_EncryptBlock(rest, subkeys, ciphertext + limit * 8);
    // memcpy(ciphertext + limit * 8, rest, 8);
  }
  return 0;
}

int Decrypt(ElemType cipherBlock[], ElemType subKeys[16][48], ElemType plainBlock[], size_t length)
{
  for (int i = 0; i < length; i += 8)
    DES_DecryptBlock(cipherBlock + i, subKeys, plainBlock + i);
  return 0;
}

int EncodeEight(void)
{
  char plain[8] = "qwer123";
  const char pw[] = "qwertyu";
  ElemType subkeys[16][48];
  MakeSubKeys(pw, subkeys);

  char cipher[8];
  DES_EncryptBlock(plain, subkeys, cipher);
  char restored[8];
  DES_DecryptBlock(cipher, subkeys, restored);
  puts(restored);

  return 0;
}

int EncodeAny(void)
{
  char plain[] = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./`";
  // char plain[] = "qwer123";

  const char pw[] = "qwertyu";
  // const char pw[7] = {'q', 'w', 'e', 'r', 't', 'y', 'u'};
  char rawkey[56];
  MakeRawKey(pw, rawkey);
  // for (int i = 0; i < 56; i++)
  //   printf("%d", rawkey[i]);
  // printf("\n");

  ElemType key[64];
  MakeKey(rawkey, key);
  // for (int i = 0; i < 64; i++)
  //   printf("%d", key[i]);
  // printf("\n");

  ElemType subkeys[16][48];
  DES_MakeSubKeys(key, subkeys);
  // for (int i = 0; i < 16; i++)
  // {
  //   for (int j = 0; j < 48; j++)
  //     printf("%d", subkeys[i][j]);
  //   printf("\n");
  // }

#define size GetProperSize(Length(plain))
  char cipher[size];
  Encrypt(plain, subkeys, cipher, Length(plain));

  // SwapSubKeys(subkeys);
  // for (int i = 0; i < 16; i++)
  // {
  //   for (int j = 0; j < 48; j++)
  //     printf("%d", subkeys[i][j]);
  //   printf("\n");
  // }

  char restored[size];
  Decrypt(cipher, subkeys, restored, size);
  // DES_DecryptBlock(cipher, subkeys, restored);

  puts(restored);

  return 0;
}

#define UsingFile(varName, fileName, fileMode, inner) \
  FILE *(varName) = fopen((fileName), (fileMode));    \
  if ((varName) == NULL)                              \
    return 1;                                         \
  inner;                                              \
  fclose((varName));

int DES_Encrypt(char *plainFile, char *keyStr, char *cipherFile)
{
  ElemType subkeys[16][48];
  MakeSubKeys(keyStr, subkeys);

  char buffer[BUFSIZ];
  UsingFile(
      src, plainFile, "rb",
      UsingFile(
          dest, cipherFile, "wb",
          int count;
          while (0 != (count = fread(buffer, 1, BUFSIZ, src))) {
            Encrypt(buffer, subkeys, buffer, count);
            count = GetProperSize(count);
            fwrite(buffer, 1, count, dest);
          }));

  return 0;
}

int DES_Decrypt(char *cipherFile, char *keyStr, char *plainFile)
{
  ElemType subkeys[16][48];
  MakeSubKeys(keyStr, subkeys);

  FILE *src = fopen(cipherFile, "rb");
  FILE *dest = fopen(plainFile, "wb");
  char buffer[BUFSIZ];

  int count;
  while (BUFSIZ == (count = fread(buffer, 1, BUFSIZ, src)))
  {
    Decrypt(buffer, subkeys, buffer, count);
    fwrite(buffer, 1, count, dest);
  }
  if (count != 0)
  {
    Decrypt(buffer, subkeys, buffer, count);
    while (buffer[count - 1] == '\0')
      count--;
    fwrite(buffer, 1, count, dest);
  }

  fclose(src);
  fclose(dest);
  return 0;
}

int main(void)
{
  EncodeEight();
  EncodeAny();
  DES_Encrypt("plain.txt", "qwertyu", "cipher.bin");
  DES_Decrypt("cipher.bin", "qwertyu", "restored.txt");
}
