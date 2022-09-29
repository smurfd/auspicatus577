//                                                                            //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "lightssl.h"
#include "lighthash.h"
#include "lightbig/src/lightbig.h"
#include "vsh/vsh.h"

int main(int argc, char **argv) {
  b08 avail[] = {TLSCIPHER};
  b08 select[] = {TLSCIPHERAVAIL};
  b08 compress = TLSCOMPRESSION;

  if (argc == 2 && argv) {
    if (strcmp(argv[1], "server") == 0) {
      struct sockaddr *cli = NULL;
      int s = lightssl_srv_init("127.0.0.1", "12345");

      lightssl_srv_listen(s, cli);
    } else if (strcmp(argv[1], "client") == 0) {
      struct hello *hs_cli, *hs_srv_recv;
      int cl;

      hs_cli = malloc(sizeof(struct hello));
      lightssl_hs_set_hello(hs_cli, false, TLSVERSION, 1337, avail, select,
        compress, 13371337);
      cl = lightssl_cli_init("127.0.0.1", "12345");
      lightssl_hs_send_hi(cl, false, hs_cli);
      hs_srv_recv = malloc(sizeof(struct hello));
      lightssl_hs_recv_hi(cl, false, hs_srv_recv);
      lightssl_print_hello(hs_srv_recv);
      lightssl_cli_end(cl);
      free(hs_srv_recv); free(hs_cli);
    } else if (strcmp(argv[1], "big") == 0) {
      int add_t = 5, sub_t = 16, mul_t = 3, div_t = 14, mod_t = 2, hex_t = 1;
      int m_t = add_t + mul_t, s_t = m_t + sub_t, d_t = s_t + div_t;
      int mo_t = d_t + mod_t, nrt = mo_t + hex_t, a_t = add_t;
      char *cc = malloc(MAXSTR);
      bigint_t *ac, *ad, *a1;

      big_init_m(3, &ac, &ad, &a1);
      big_alloc_max_m(3, &ac, &ad, &a1);

      // Sanity checks
      cc = "21739871283971298371298371289371298371298371298371298371293";
      big_set(cc, &ac);
      big_resize(&ac, ac->len, ac->len);
      big_assert(cc, &ac);
      big_end_m(3, &ac, &ad, &a1);

      // Big test suite
      char *a[] = {"11111111111111111111111111111111111111111111111111111111111\
000", "512", "92222132222222222222222555555555555555555555555555555555555555555\
55555555555555555555555222212", "-5", "-5", "2048", "1024", "111111191112312312\
3111112312313131313234423234234223213131564345654345643456543", "600", "578",
"268","309533158886756081306558107419546609056284391055396614233847499080671621\
8932404114491826217170609713718596845014959592435043758265939038258550391868285\
3347985597634436140403892213583177172042680359040655465719887405112118172413073\
84", "0", "-5", "10338252656018848802893901210576991702514742478269684477771423\
14672936145","43770350598605623884688535000634442901375162537234380696226857770",
"600", "578", "268", "309533158886756081306558107419546609056284391055396614233\
8474990806716218932404114491826217170609713718596845014959592435043758265939038\
2585503918682853347985597634436140403892213583177172042680359040655465719887405\
11211817241307384", "0", "-5", "10338252656018848802893901210576991702514742478\
26968447777142314672936145", "4377035059860562388468853500063444290137516253723\
4380696226857770", "600", "10", "10000", "65341020041517", "6534102004151763395\
6166170261014086368942546761318486551877808671514674964848", "37286503443888916\
570650794096490365355343842882500054693645072639621059063465", "437703505986056\
23884688535000634442901375162537234380696226857770", "3728650344388891657065079\
4096490365355343842882500054693645072639621059063465", "21312662129474496654052\
3670831272617567382343028847973123306705470302545013159377534579963271436286429\
2670109702312040306070201792271107175502373632466160", "30092313036467430356606\
4152685592960036419222958287034092357419", "97783168081539600805195362086833632\
1350460074412926936453701305306078053556442431646237526946771807437838667211103\
2446309228292315519555323128477945198913056024103744583946021537585759767733218\
73548702908703766827059895408816333758974", "4042517160269506153541708461306363\
2117673617386981676717219818820800468173859275479075849450530805379691992351315\
8686561623345124674003521447119593026321813728146507711845153420872106440718351\
89688768694403662543843232206210706", "5724866722627202679010101389421076414326\
6696029206115750717130429221065424281642194297583507908841202690181999089254620\
8886126572673828199892805209973836912683769389081833793526045749043779551723092\
7894570085967472671657395676286312921561565668225928075588420652996123225739090\
3597957727047009041264559872202397082418283611487416327341366184686752004057541\
8435707781840063581235797865427874795486784310587289817150338046772311631729871\
169564273615042361442701520", "600", "10", "100", "0x123"};

      char *b[] = {"33333333333333333333333333333333333333333333333333333333333\
789", "512", "11111119111231231231111123123131313132344232342342232131315643456\
54345643456543", "0", "-5", "8", "16", "922221322222222222222225555555555555555\
5555555555555555555555555555555555555555555555555222212", "22", "22", "122", "2\
1421309181006835649040465816202741246597952501982834331452308490839135778359156\
863668440066179055920925278708336624472863330807213114639693592192652215296",
"3", "-5", "6584585857041179209398830597395186161231444517756911933267017221241\
9499", "998689668015619845290232924195546972680041504057103240236666837", "22",
"22", "122", "21421309181006835649040465816202741246597952501982834331452308490\
8391357783591568636684400661790559209252787083366244728633308072131146396935921\
92652215296", "3", "-5", "65845858570411792093988305973951861612314445177569119\
332670172212419499", "998689668015619845290232924195546972680041504057103240236\
666837", "22", "3", "3", "504510691", "5045106919579856146740481474767382148432\
7437904322077487579775336394159706815", "2", "998689668015619845290232924195546\
972680041504057103240236666837", "2", "1157920892373161954235709850086879078532\
69984665640564039457584007908834671663", "5212052218649554511876700662613639061\
93068031158944893620680", "1157920892373161954235709850086879078532699846656405\
64039457584007908834671663", "1157920892373161954235709850086879078532699846656\
40564039457584007908834671663", "1157920892373161954235709850086879078532699846\
65640564039457584007908834671663",  "22", "3", "63", "0xa23"};

      char *c[] = {"44444444444444444444444444444444444444444444444444444444444\
789", "1024", "9222213222222223333334166678678678666667867868686868789978789789\
778768687119901209901198678755", "-5", "-10", "16384", "16384", "10246910958128\
2686939166314728295487301952988652058052952481719288409956302066542765911881078\
0612014418970037103742674754147246843474781775342356329987323524031887013033311\
6", "578", "556", "146", "30953315888675608130655810741954660905628439105539661\
4233847499080671621893238269318264521033496067325278064227371299448254177543160\
7585950059552732506975641696095003547861333300433039008867643563040734739358874\
100817619624589092088", "-3", "0", "9679794070314730881954018150837473086391598\
02649399328444472142460516646", "4277166093059000403939830207643889592869512103\
3177277455990190933", "578", "556", "146", "30953315888675608130655810741954660\
9056284391055396614233847499080671621893238269318264521033496067325278064227371\
2994482541775431607585950059552732506975641696095003547861333300433039008867643\
563040734739358874100817619624589092088", "-3", "0", "9679794070314730881954018\
15083747308639159802649399328444472142460516646", "4277166093059000403939830207\
6438895928695121033177277455990190933", "27", "3", "3333", "129513", "1", "1864\
3251721944458285325397048245182677671921441250027346822536319810529531732", "43"
, "1864325172194445828532539704824518267767192144125002734682253631981052953173\
2", "18405974250791985306898387292513446207790260853623256697871975478881952846\
046", "577", "84447192140330707113963255284567556577780406282036509216346035040\
3594128933099359644309908361690869954871395818653795142918656402215217631038167\
5487752022988", "34911859582949198387415456937390592393911583298899102349220489\
6726270779361337427372490642664977924959354861526030969502847027596217666059704\
067859675", "494409139720596376570841142410692523369700046836599999455194648458\
8281241262643652065658134064764128084559749226770866873467855515093957218846865\
5800058453241754971151003429558077399455451903694889414394855896441229712823954\
9274629945080222978568386987953363923621183144968799380292173671165888872943803\
9601173911907492700592982131530147912079948541749035857752315481732903160988470\
021", "27", "1", "37", "0xb85c9"};

      big_init_m(3, &ac, &ad, &a1);
      big_alloc_max_m(2, &ac, &ad);
      for (int j = 0; j < 500; j++) { // 300mb ram
        for (int i = 0; i < nrt; i++) {
          big_alloc_max_m(1, &a1);
          big_set("0", &a1);
          big_set(a[i], &ac); big_set(b[i], &ad);

          // Addition tests
          if (i < a_t) {big_add(ac, ad, &a1); big_assert(c[i], &a1);}
          // Multiplication tests
          else if (i < m_t) {big_mul(ac, ad, &a1); big_assert(c[i], &a1);}
          // Subtraction tests
          else if (i < s_t) {big_sub(ac, ad, &a1); big_assert(c[i], &a1);}
          // Division tests
          else if (i < d_t) {big_div(ac, ad, &a1); big_assert(c[i], &a1);}
          // Modulo tests
          else if (i < mo_t) {big_mod(ac, ad, &a1); big_assert(c[i], &a1);}
          // Hex tests
          else if (i < nrt) {
            big_mul(ac, ad, &a1); (*a1).base = HEX; big_assert(c[i], &a1);
          }
        }
      }
      big_end_m(2, &ac, &ad);
      printf("OK\n");
    } else if (strcmp(argv[1], "hash") == 0) {
      const char *rh = "555cfc37fc24d4971de9b091ef13401b8c5cb8b5b55804da571fb20\
1cbb4fc5d147ac6f528656456651606546ca42a1070bdfd79d024f3b97dd1bdac7e70f3d1";
      const char *in = "smurfd";
      char *out = malloc(100);

      strcpy(out, lighthash_new(in));
      assert(lighthash_verify(out, rh));
      free(out);
      printf("OK!\n");
    } else if (strcmp(argv[1], "vsh") == 0) {
      // locally generate two keypairs
      srand(time(0));
      vsh_keys();
    }
  }
}
