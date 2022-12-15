//                                                                            //
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../lightdefs.h"
#include "../lighthash.h"

#define TEST10_512                                                           \
  "\xa5\x5f\x20\xc4\x11\xaa\xd1\x32\x80\x7a\x50\x2d\x65\x82\x4e\x31\xa2\x30" \
  "\x54\x32\xaa\x3d\x06\xd3\xe2\x82\xa8\xd8\x4e\x0d\xe1\xde\x69\x74\xbf\x49" \
  "\x54\x69\xfc\x7f\x33\x8f\x80\x54\xd5\x8c\x26\xc4\x93\x60\xc3\xe8\x7a\xf5" \
  "\x65\x23\xac\xf6\xd8\x9d\x03\xe5\x6f\xf2\xf8\x68\x00\x2b\xc3\xe4\x31\xed" \
  "\xc4\x4d\xf2\xf0\x22\x3d\x4b\xb3\xb2\x43\x58\x6e\x1a\x7d\x92\x49\x36\x69" \
  "\x4f\xcb\xba\xf8\x8d\x95\x19\xe4\xeb\x50\xa6\x44\xf8\xe4\xf9\x5e\xb0\xea" \
  "\x95\xbc\x44\x65\xc8\x82\x1a\xac\xd2\xfe\x15\xab\x49\x81\x16\x4b\xbb\x6d" \
  "\xc3\x2f\x96\x90\x87\xa1\x45\xb0\xd9\xcc\x9c\x67\xc2\x2b\x76\x32\x99\x41" \
  "\x9c\xc4\x12\x8b\xe9\xa0\x77\xb3\xac\xe6\x34\x06\x4e\x6d\x99\x28\x35\x13" \
  "\xdc\x06\xe7\x51\x5d\x0d\x73\x13\x2e\x9a\x0d\xc6\xd3\xb1\xf8\xb2\x46\xf1" \
  "\xa9\x8a\x3f\xc7\x29\x41\xb1\xe3\xbb\x20\x98\xe8\xbf\x16\xf2\x68\xd6\x4f" \
  "\x0b\x0f\x47\x07\xfe\x1e\xa1\xa1\x79\x1b\xa2\xf3\xc0\xc7\x58\xe5\xf5\x51" \
  "\x86\x3a\x96\xc9\x49\xad\x47\xd7\xfb\x40\xd2"

int main() {
  int err = lighthash_hash(TEST10_512, length(TEST10_512),
  1, 0, 0, 0, 0, "C665BEFB36DA189D78822D10528CBF3B12B3EEF726039909C1A16A270D487"
  "19377966B957A878E720584779A62825C18DA26415E49A7176A894E7510FD1451F5", 64);
  assert(err == 1);
  printf("OK\n");
  return 0;
}