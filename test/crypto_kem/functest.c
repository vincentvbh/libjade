#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "print.h"

#include "api.h"
#include "jade_kem.h"

/*

int jade_kem_keypair(
  uint8_t *public_key,
  uint8_t *secret_key
);

int jade_kem_enc(
  uint8_t *ciphertext,
  uint8_t *shared_secret,
  const uint8_t *public_key
);

int jade_kem_dec(
  uint8_t *shared_secret,
  const uint8_t *ciphertext,
  const uint8_t *secret_key
);

*/

int main(void)
{
  int r;
  uint8_t public_key[JADE_KEM_PUBLICKEYBYTES];
  uint8_t secret_key[JADE_KEM_SECRETKEYBYTES];
  uint8_t shared_secret_a[JADE_KEM_BYTES];
  uint8_t ciphertext[JADE_KEM_CIPHERTEXTBYTES];
  uint8_t shared_secret_b[JADE_KEM_BYTES];

  //
  r = jade_kem_keypair(public_key, secret_key);
    assert(r == 0);

  //
  r = jade_kem_enc(ciphertext, shared_secret_a, public_key);
    assert(r == 0);

  //
  r = jade_kem_dec(shared_secret_b, ciphertext, secret_key);
    assert(r == 0);
    assert(memcmp(shared_secret_a, shared_secret_b, JADE_KEM_BYTES) == 0);

  #ifndef NOPRINT
  print_info(JADE_KEM_ALGNAME, JADE_KEM_ARCH, JADE_KEM_IMPL);
  print_str_u8("public_key", public_key, JADE_KEM_PUBLICKEYBYTES);
  print_str_u8("secret_key", secret_key, JADE_KEM_SECRETKEYBYTES);
  print_str_u8("shared_secret", shared_secret_a, JADE_KEM_BYTES);
  print_str_u8("ciphertext", ciphertext, JADE_KEM_CIPHERTEXTBYTES);
  #endif

  return 0;
}

