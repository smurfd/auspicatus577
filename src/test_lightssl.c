//                                                                            //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lightssl.h"
#include "lighthash.h"

int main(int argc, char **argv) {
  char *out = NULL;
  char *data = NULL;
  byte8_t avail[] = {222};
  byte8_t select[] = {222};
  byte8_t compress = 123;

  const char* in = "smurfd";
  const char* rh = "555cfc37fc24d4971de9b091ef"\
                   "13401b8c5cb8b5b55804da571f"\
                   "b201cbb4fc5d147ac6f5286564"\
                   "56651606546ca42a1070bdfd79"\
                   "d024f3b97dd1bdac7e70f3d1";

  out = (char*) malloc(100);
  strcpy(out, lh_new(in));
  ls_init();

  // the hash of rh and the generated one match?
  assert(lh_verify(out, rh));
  printf("The hashes match!\nRealHash:  %s\nGenerated: %s\n", rh, out);

  if (argc == 2 && argv) {
    // For documentation, client and server example
    // Needs separate files
    if (strcmp(argv[1], "server") == 0) {
      // If you are on mac run server as root
      struct sockaddr *cli = NULL;
      struct handshake hs_srv;
      ls_hs_set_hello(&hs_srv, true, 4, 1337, avail, select, compress, 13371337);
      int s = ls_srv_init("127.0.0.1", "12345");
      int c = ls_srv_listen(s, cli);
      if (c) {}
    }
    if (strcmp(argv[1], "client") == 0) {
      struct handshake hs_cli;
      ls_hs_set_hello(&hs_cli, false, 4, 1337, avail, select, compress, 13371337);
      if(!data)
        data = (char*) malloc(2048);
      int cl = ls_cli_init("127.0.0.1", "12345");
      ls_cli_recv(cl, &data);
      printf("Rec from server: %d, %s\n", cl, (char*)&data);
      ls_cli_end(cl);
    }
  }
  return 0;
}
