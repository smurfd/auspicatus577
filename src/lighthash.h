//                                                                            //
// Code grabbed from https://www.rfc-editor.org/rfc/rfc6234 and massaged
#ifndef LIGHTHASH_H
#define LIGHTHASH_H 1
#include <stdint.h>
#include "lightdefs.h"

// Initial Hash Values: FIPS 180-3 sections 5.3.4 and 5.3.5
extern const uint8_t hexdigits[], masks[8], markbit[8];
extern const uint64_t h0[], k0[80];

// This structure will hold context information for the SHA hashing operation.
typedef struct ctxs {
  uint64_t imh[SHA_HSH_SZ / 8], len_hi, len_lo; // Intermediate Message Digest & Message length in bits
  int_least16_t msg_blk_i;                      // Message_Block array index
  uint8_t mb[SHA_BLK_SZ];                       // 1024-bit message blocks
  int compute, corrupt;                         // Is the hash computed. Cumulative corrupt code
} ctxs;

// This structure will hold context information for the HMAC keyed-hashing operation.
typedef struct ctxh {
  int which, size, blk_size;                     // Which SHA, Hash size & Block size is being used
  ctxs sha;                                      // SHA Context
  uint8_t k_opad[SHA_BLK_SZ];                    // Key XORd with opad
  int compute, corrupt;                          // Is the MAC computed. Cumulative corruption code
} ctxh;

// SHA Hashing (keeping the static ones as commented to get a overview)
// int lhash_sha_reset(ctxs *c);
// int lhash_sha_input(ctxs *c, cuc *bytes, uint32_t bytecount);
// int lhash_sha_final(ctxs *, uint8_t bits, uint32_t bit_count);
// int lhash_sha_result(ctxs *c, uint8_t msg_dig[SHA_HSH_SZ]);
// int lhash_sha_match_to_str(cuc *hashvalue, cc *hexstr, int hashsize, char *s);
// HMAC Keyed-Hashing for Message Authentication, RFC 2104
// int lhash_hmac_reset(ctxh *c, cuc *key, int key_len);
// int lhash_hmac_input(ctxh *c, cuc *text,int text_len);
// int lhash_hmac_final(ctxh *c, uint8_t bits, uint32_t bit_count);
// int lhash_hmac_result(ctxh *c, uint8_t digest[SHA_HSH_SZ]);
// lh for LightHash
// lh3 for LightHash3
int lh(cc *ta, int l, uint64_t r, int n, int eb, cuc *k, int kl, cc *ra,int hs);
void lhnew(cc *in, char* s);
void lh3new(uint8_t *n, char *ss);
#endif

// TODO:
// * exchange sha2 & hmac to shake
// * generalize functions, so out parameter is either first or last
