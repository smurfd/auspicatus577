//                                                                            //
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../lightkeys.h"
#include "../lighttools.h"
#include "../lightcrypto.h"

int main(void) {
  u64 sig[KB * 2], h[KB], k[KB], pubkey[KB + 1], privkey[KB], sec[KB];
  uint8_t p[256];

  assert(lrand(h, k));
  assert(lkmake_keys(pubkey, privkey, k));
  assert(lkshar_secr(pubkey, privkey, sec, k));
  assert(lksign(privkey, h, sig, k));
  assert(lkvrfy(pubkey, h, sig));
  assert(!lkvrfy(privkey, h, sig)); // assert failure
  bit_unpack(p, privkey);
  lkwrite("ca-own.key", p, 2);

  if (*sig || *pubkey || *sec || *privkey || *h || *k) {} // get rid of not used var warning
  printf("OK\n");
}
