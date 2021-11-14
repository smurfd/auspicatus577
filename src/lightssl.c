//                                                                            //
#include <stdbool.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "lightssl.h"

// dummy
void ls_init() {
  printf("hi from lib\n");
}

int ls_srv_init(const char *host, const char *port) {
  int ssock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in saddr;

  memset(&saddr, '\0', sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(atoi(port));
  saddr.sin_addr.s_addr = inet_addr(host);

  bind(ssock, (struct sockaddr*)&saddr, sizeof(saddr));
  return ssock;
}

void *ls_srv_handler(void *sdesc) {
  int s = *(int*)sdesc;
  int rd = 1;
  char *msg = NULL;
  char cm[2000];

  if (msg) {}
  ls_srv_send(s, "some data");
  while (rd >= 0) {
    rd = recv(s, cm, 2000, 0);
    write(s, cm, strlen(cm));
    memset(cm, '\0', 2000);
  }
  // if rd == 0, client disconnect
  // if rd < 0, received failed
  free(sdesc);
  close(s);
  pthread_exit(NULL);
  return 0;
}

int ls_srv_listen(int ssock, struct sockaddr *cli) {
  int csock = 1;
  int *new_sock;
  int c = sizeof(struct sockaddr_in);
  listen(ssock, 3);
  while(csock >= 0) {
    csock = accept(ssock, (struct sockaddr*)&cli, (socklen_t*)&c);
    pthread_t sniffer_thread;
    new_sock = (int*)malloc(sizeof *new_sock);
    *new_sock = csock;
    if (pthread_create(&sniffer_thread, NULL, ls_srv_handler, (void*)new_sock) < 0) {
      printf("rerrror\n");
      return -1;
    }
    pthread_join(sniffer_thread, NULL);
  }
  return csock;
}

void ls_srv_send(int csock, const char *msg) {
  send(csock, msg, strlen(msg), 0);
}

void ls_srv_recv(int csock, char **data) {
  recv(csock, &data, sizeof(data), 0);
}

int ls_cli_init(const char *host, const char *port) {
  int csock = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in saddr;

  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(atoi(port));
  saddr.sin_addr.s_addr = inet_addr(host);

  int cs = connect(csock, (struct sockaddr*)&saddr, sizeof(saddr));
  if (cs < 0) {
    printf("Connection error\n");
    exit(1);
  }
  return csock;
}

void ls_cli_recv(int csock, char **data) {
  recv(csock, data, sizeof(data), 0);
}

void ls_cli_send(int csock, const char *msg) {
  send(csock, msg, strlen(msg), 0);
}

void ls_cli_end(int csock) {
  close(csock);
}

void ls_hs_set_hello(struct handshake *hs, bool srv, byte8_t tls,
  uint64_t r, byte8_t avail[], byte8_t sel[], byte8_t c, uint64_t sess) {
  hs->hi.server = srv;
  hs->hi.tls_v = tls; // will be 4 = TLS1.3
  hs->hi.rnd = r;
  hs->hi.ciph_avail[0] = avail[0]; // will only use 1 cipher
  hs->hi.ciph_select[0] = sel[0]; // will only use 1 cipher
  hs->hi.compress = c;
  hs->hi.session_id = sess;
}

byte8_t ls_hs_send_hi(int csock, bool srv, struct hello *hi) {
  if (srv) {}
  if (hi) {}
  send(csock, hi, sizeof(hi), 0);
  return 0;
}

byte8_t ls_hs_recv_hi(int csock, bool srv, struct hello *hi) {
  if (srv) {}
  if (hi) {}
  recv(csock, hi, sizeof(hi), 0);
  return 0;
}
