//                                                                            //
// Very simple handshake
#include "vsh.h"

//
// Client main
int main() {
  int i, s = vsh_init("127.0.0.1", "9998", false);

  if (s >= 0) {
    u64 dat[BLOCK], cd[BLOCK];
    key k1, k2;
    head h;
    h.len = 11;

    vsh_transferkey(s, false, &h, &k1);
    k2 = vsh_genkeys(h.g, h.p);
    vsh_transferkey(s, true, &h, &k2);
    vsh_genshare(&k1, &k2, h.p, false);
    printf("share : 0x%.16llx\n", k1.shar);
    for (i = 0; i < h.len+1; i++) {dat[i] = (u64)i;vsh_crypt(dat[i],k1,&cd[i]);}
    vsh_transferdata(s, cd, true, h.len);
    vsh_end(s);
  }

  // locally generate two keypairs
  srand(time(0));
  vsh_keys();
}
