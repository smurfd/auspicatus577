//                                                                            //
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "../lighthash.h"
#include "../lighttools.h"

int main(void) {
  uint8_t buf[512] = {0}, str[512] = {0}, s[200] = {0}, next = 0, next2 = 0;
  char sss[64], ss[64] = "6a1a9d7846436e4dca5728b6f760eef0ca92bf0be5615e96959d7\
67197a0beeb";

  memset(buf, 0xA3, 20);
  for (int i = 0; i < 200; i += 20) {next = hash_shake_touch(str,buf,next,true);}
  hash_shake_xof(str);
  for (int i = 0; i < 32; i++) s[i] = str[i];
  for (int i = 0; i < 512; i += 32) {next2 = hash_shake_touch(str,s,next2,false);}
  bit_hex_str(sss, s);
  for (int i = 0; i < 64; i++) {assert(sss[i] == ss[i]);}
  if (*ss) {} // get rid of not used var warning
  printf("OK\n");
}
