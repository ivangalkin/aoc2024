#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

#ifdef NDEBUG
#undef NDEBUG
#endif
#include <assert.h>

#define ASSERT_EQ(a, b)                                                        \
  do {                                                                         \
    __typeof__(a) _a = (a);                                                    \
    __typeof__(b) _b = (b);                                                    \
    if (_a != _b) {                                                            \
      std::cout << _a << " != " << _b << std::endl;                            \
      assert(0);                                                               \
    }                                                                          \
  } while (0)

#define myprint(arg)                                                           \
  do {                                                                         \
    std::cout << "" #arg << " = " << arg << std::endl;                         \
  } while (0)

using ll = int64_t;

namespace {

std::vector<std::string> towels{
    "grbb",     "burb",     "wrwbrwg",  "uwwb",     "bwbbw",    "ubgrbu",
    "gguu",     "uru",      "gwr",      "wrw",      "gubwb",    "g",
    "gwbu",     "rbw",      "bbuu",     "rwgbr",    "urrr",     "rwww",
    "wrrb",     "ug",       "rubbwuuu", "gbrbr",    "brb",      "wrubb",
    "gwrgbbgu", "wggwbrww", "rwwb",     "br",       "buuwr",    "rgrbb",
    "wgubb",    "gbb",      "gbrb",     "rubw",     "ubr",      "guu",
    "wrugbg",   "gubwru",   "bww",      "rbu",      "burr",     "ugu",
    "bbggguw",  "bguw",     "ubu",      "uuuw",     "uugww",    "urugr",
    "uwgur",    "gugrgggw", "b",        "gugu",     "wgb",      "rwgwuu",
    "guw",      "brg",      "ubur",     "wbwwb",    "ggbg",     "wr",
    "urw",      "wur",      "brwgrw",   "uuur",     "rwwg",     "rrbrbggw",
    "gwrurwg",  "rurru",    "r",        "bug",      "ruwrww",   "brgwu",
    "bwgurbu",  "rwuu",     "guub",     "rrbwb",    "rbgwbr",   "grbrugbu",
    "bwugwugb", "guwww",    "ugwggg",   "buggrug",  "urb",      "bbbwuur",
    "ururgur",  "wu",       "bbbru",    "ruuw",     "grr",      "buw",
    "bub",      "gbwwug",   "rwrbw",    "wrbg",     "wubr",     "u",
    "wgrb",     "wbuub",    "ugrugwg",  "wggbrr",   "gr",       "uur",
    "ugb",      "wbg",      "uub",      "bbbrww",   "uwbr",     "buwguww",
    "wbwgw",    "ubuuwr",   "wuuwgr",   "wggw",     "gwurgub",  "rwwu",
    "bruwg",    "bgbrbwb",  "rbgg",     "rbg",      "bubggwu",  "gubgrur",
    "gwb",      "rgu",      "wrr",      "uug",      "bgw",      "ruuugu",
    "uwbg",     "rgurgwwb", "wrwgb",    "brbbr",    "wgrgu",    "brgbwb",
    "gub",      "uugw",     "wrrbb",    "wwruuru",  "grrw",     "urgg",
    "gbwg",     "ubbur",    "bggwwgw",  "ubggw",    "uwgw",     "ruu",
    "wwuu",     "bwuu",     "uggw",     "gwu",      "urg",      "rwbb",
    "uwwub",    "ruug",     "bwbbu",    "wbb",      "bwwwu",    "rbwrruu",
    "gg",       "ugrbbwgb", "wbbwwr",   "bbwrrrb",  "rgwwu",    "bbr",
    "wbuwb",    "grub",     "ubwwgu",   "ubb",      "brrbuu",   "grw",
    "bwugg",    "wurbu",    "uwrb",     "rwgg",     "rurbuu",   "gbrug",
    "brwgr",    "gru",      "bgrub",    "uuwr",     "gbwww",    "bbrw",
    "rbr",      "bwrg",     "ruur",     "gbbgr",    "brgwug",   "ugg",
    "bwgubu",   "rrg",      "ub",       "gbuwu",    "ubuwuw",   "ggw",
    "wrgww",    "uuwb",     "bwr",      "bb",       "ruwu",     "bwugrw",
    "buu",      "wug",      "gggwbwu",  "brurg",    "rrur",     "gb",
    "wg",       "ggruwbu",  "gbg",      "bruur",    "gug",      "rgr",
    "gwuuu",    "uwwurr",   "ubw",      "uugbuw",   "ruugwu",   "bu",
    "ubrbw",    "ggu",      "rug",      "wgurwurr", "ugrrbr",   "brgrb",
    "rrbrgwww", "rrgg",     "grb",      "brbw",     "bruwgw",   "uwbw",
    "rgg",      "wrg",      "rrruwr",   "gguw",     "bugbbrw",  "bbg",
    "rwg",      "wbuwg",    "uuu",      "wruwur",   "ugwb",     "bur",
    "urgb",     "bg",       "uwubrwu",  "rwbwwg",   "rub",      "wwwwbw",
    "rbbugbr",  "wgg",      "bwbb",     "brw",      "ggugb",    "guggw",
    "bgg",      "wwr",      "gwrbb",    "rbb",      "bgb",      "brrubwb",
    "wwu",      "bggrrwu",  "bugb",     "gwugw",    "grg",      "wrb",
    "wuub",     "bru",      "gggrr",    "wuw",      "uwg",      "gbgurg",
    "wguwug",   "gbwgw",    "bgrb",     "wguuw",    "rwr",      "ubuww",
    "wruuw",    "wurur",    "wuu",      "bbw",      "brbgubb",  "bubg",
    "wgw",      "wwuwrw",   "bbwu",     "bbrgubw",  "uwu",      "bw",
    "wbr",      "bbu",      "bgr",      "ubg",      "rwrgg",    "uggu",
    "wugggb",   "wwbgguur", "wrwuwb",   "rgrr",     "wgbu",     "ggb",
    "ubuw",     "rgugg",    "gwuru",    "guuubbw",  "bgbrrw",   "rrgwg",
    "gbw",      "wbu",      "wuwg",     "gugb",     "uww",      "ruugb",
    "rubu",     "ugwbw",    "bbrgrg",   "grbrr",    "guwgruwr", "wwbr",
    "wgruw",    "grwg",     "wgr",      "ururwr",   "gbbg",     "gbuub",
    "uwr",      "grwgrwr",  "ruw",      "wru",      "ggr",      "guwuu",
    "uwuuwu",   "gbu",      "rwbbgg",   "ruruww",   "wwwur",    "rgrug",
    "rbbwg",    "rgwugwg",  "wbw",      "bbru",     "ggg",      "bbuugrrg",
    "uugb",     "rw",       "gburwww",  "rububugg", "gguubbg",  "rrrurwwg",
    "buruwrb",  "bbwrggwb", "gbrbwr",   "uruwwu",   "wwwurbu",  "rrwb",
    "bbb",      "bwg",      "wurggubb", "wgu",      "gwwg",     "wururruu",
    "bbbu",     "ur",       "rwb",      "uwww",     "wgwr",     "rr",
    "rru",      "uuw",      "uu",       "bwgw",     "brr",      "wub",
    "bwgbrrw",  "gwrgrw",   "uw",       "ggguwbg",  "bubbur",   "ubbggu",
    "ugr",      "rrrw",     "ru",       "rb",       "gwwbgw",   "rrr",
    "rrw",      "gruw",     "rwrrbb",   "rugr",     "uubw",     "ruwb",
    "uubbbu",   "gur",      "wb",       "rrrrwww",  "bbub",     "bgurwg",
    "ubbugw",   "gwbw",     "gggbru",   "ugru",     "brru",     "ggwg",
    "wwg",      "ugubr",    "urggbu",   "ggwuww",   "gbr",      "guwubu",
    "rwu",      "gwg",      "rrbur",    "gwrg",     "wwubr",    "uwb",
    "gbrr",     "rurburb",  "brrg",     "ggur",     "rurbw",    "uwbu",
    "grbbu",    "wgur",     "urr",      "rgggg",    "rrb",      "ww",
    "rww",      "bwwwr",    "wubwubgw", "ggubw",    "wwb",      "uurb",
    "wbrggwu",  "ugw",      "rggwwr",   "urwu",     "gwwggg",   "uwuubwr",
    "gwuubww",  "uwbwu",    "www",      "gwgwr",    "bwu",      "gu",
    "rur",      "wwwg",     "uwruub"};

std::vector<std::string> patterns{
    "rrwuwuurrrguggbrrrrgwwururguggwuwrwwurwuuwbw",
    "wrrugrgbuuuurgubbbbbggrrwgrbgggbwuwwbuubwrbgwwgbww",
    "uurwwrgbuuburbgbrrgugrgwugbwrwguruugwwgguwugrgwggrur",
    "rgruurwubbgggwwuwwgurrwuugggbrbuwgwrubrgw",
    "gugwbgbwbbgurrbrurwbwwgwwgbrgwuwruubwuwuggrrrgbgb",
    "urwguwuggwbbwgbrbbgubwbggwggwgrbrrruguruggbgruwb",
    "grwbubrugwuuubgbgburrgbuuuwruruuugrwgrrbwwrgbwrbwrugubgu",
    "wwrbruwrgbgubuurwrgbubbwwgbwurwrrbwwurrgugggrbwurrrb",
    "bwugbgrugbuwbuurrgurwbrggrggrbrgurgwwbbgrrbgbubrgrrbwgrbwu",
    "grggrbwrwbuwrgwrbggwrrggugugggrwbwwrguuuuwgrrgbgwuurug",
    "gbugrrruubgbgwrggbwgrwwubrrbubrgbbgubbbuurwbb",
    "bgrrbbrwbrguurggwrrrgrrgwururbggururgwwgrwgbuugbg",
    "uwwubbuwgwuggrruuuwbgwrrgwrbbrgggubwugubuuubwwbbwuwru",
    "ruwgguggbgbbwwrbbrubrrruugbwwgrguwubwgbbgburu",
    "wrbubwugwgurrrrrbwwwuubbubgrbbgwrurrrrbugggw",
    "rbwbbrbrrwbugurbbbrubbgbbgbuwbrbbwrggwbrwbguguubggwgbruww",
    "gggwrrgubuurrrrrurwubgwgbuuggrrwrurbbgugruruwrrgurugu",
    "gurrbwbrbubguwbbrgwggruwuwrrrwwrggggrwuwubgubugwwgbgwrwgurgw",
    "grbgrgguwrwrububbrburbgrubuwrwwbbwwgbbuwwwbubgrbgbr",
    "ubbuwuguwbwwbubbbbburbuububwrwwbwgubrubuwwwuwrrwrwwggubggg",
    "buwrgrrbuuwbbrgggbbwuruugbwwgwggwwgrrbbggrbuwuu",
    "gguguwbwrrggguurrrwuwbrwwwwrruwuwguuggrrrbgwwgrbbbrgrbrgb",
    "bgbugwgwwgwwwgrbwuwugwbgbururwugwuwwurwwbuubrw",
    "gwggguurbubwbgwgrwwrgrubuurrrugrbbuugrrgbuurggbgwbwwwur",
    "gwruwwbrwwgwrbgbguwwugrwruwrgubwbbwbbugrwbgguwurguwu",
    "gwbruubwwrbbbbbgruwgwgwgbrwgururrrwugwgrubbggbuwuwwbb",
    "buuuwwguwbwgwbbuwgubbrggwgggburwbgbwwrbuguwgwbwugrggr",
    "ubwrubuwgbgbwgggwrwgrwrrggrgbgrbbuwwggbwgbwbbgurbrguguwrrgw",
    "wrrubggwruurbbbrgbwguwbwgggbrrwrwgubwuguwbrgw",
    "rgbwwuurgwbwrrwwgruurbruubwurggugbuubgrrrwbgrggrggrgwbr",
    "grurgwbgbggbwbwwuuubugbuuugbbwrwuugbbubbuw",
    "ubggwwbgwwrruuwwuwbrrbbwugwruurrugrbbwgbwwwgbwbwbwbubbrr",
    "wgbwubuugwrrgwrwbbwwgrrgwuggrubgrrubwrubrwuurgruwwwgrwr",
    "uggwguwruuwugbwbuwwgwugwrbbwrubrburgrgbuuburw",
    "grbbrgbwbbubwrwrurgugbggrwbuugbubbgugbwrgrwwgbbbguuwg",
    "rwurubwguwuububwrurwgrrwuubbubrwwbrgugrbgubu",
    "grrbrgrbbuguwgrwugurrbbwrggwbguguugrurgw",
    "gurrwrwgruubrubgrgbrwbrgwwrbrgbugrbwgwgbbgw",
    "wubrubbuwrubrrrrwgbgugbrrbrgwbwgrwbuugugbgrbuur",
    "bbrgbbgrbrbwgruwrgwgrgugrrwgruwwgwwbwwwguurbuwbwruwbubr",
    "wugrwrggbwbwrbwrwbbggrgburuggwurbubruugbwgruwbrguwb",
    "buwrbwruwrbgrrruugbruugrrwbgrwgwugrbwgbrwwuuwbwgurgw",
    "wwggrrwwbgrbwguwwuwwurbgwburwggrwugwguubugwgugggbwb",
    "ubwrguuwrgbgugurgguuwwggbuuubwgwwrwuguubgwbwgrwuwwb",
    "rgurubgwubguggbgguwwwwwuuwugrwgubrrurgubrrgw",
    "uggggbwwgbbrbwururggrwugggurgugubrbrgrurbgb",
    "rwrrgbbbbrwggbrgguwubrgwwuugugwwwbuburugubguwguubuguwrrug",
    "rggguuwuuburuwubgbuwwrububgwrrbwwrubbrgw",
    "ggrbrbbrgrwuggwubrbbwwbgruubrbgggguuggrgw",
    "rwgwubgrruggwruurwwuubgbrwggwbrwwbggbrgw",
    "gbrrrggwbrrbwwuugwgbugrrgggwubgruwburburrbbrggwbbgww",
    "wruwbbuwubbwwrrubbbrurwrbggwwgguurrruwubruuwwuwubgbwug",
    "rbuwguwbugbrrrrbubbwubgwuwbuwwrwuugbubrggrbrwrwwbrwbrgrwbb",
    "gwbuububgrwuuwbwbwbguwggubgrgubgwrrrbwgrrwwwbugb",
    "wwrbugruuwrgwubgbwrwugwwrgrrubggubuwurwgurwubruu",
    "ubgwwuburrwrgrbgurbgubgwwwbwurgbbbwwrgwrbgguguwbbuug",
    "wwwburwwguwrbugwgwwrbwbruugbggburrgrbruwggrrgw",
    "wubuwruubgwubrwwbrrrgwruwgbuugburrbgurbwrruugwbgrwu",
    "brugwggbbgbbgggwbwuuwbuuggwrbuguurwubrggbrggbw",
    "uuurbrwbbbbwggwbrruggwbwwurbbbbubbwwuwuurrgruububwrgrrwubb",
    "gbwugbgbrurrbrggguwuwrgburwbwbuwuurwubwbwguugurrwrgguwgubg",
    "bwrrrrbgwuubggbrbguuuuwwbwbgggbwbguuwbrgwggbuug",
    "rrwwwubwurguurrggbbgrbrrbbrrbrrwurwwgrrbugugbb",
    "wwbwrurrwrgbgggguruurwbrwbbrbwubwubgwgruruuuwrubbgwwrgw",
    "wuburburbbrbbwrugbbrbbbuwbrwrbuwgugrugbgwrrgrwguggbg",
    "gugrggwurbuuwgrwguwbrwubrbrwuwugbuwgbwbwrwrrwwrgbuurg",
    "wwbwbwrwrruuwbbrrggbugwbrwbbbubugbrwruuwbg",
    "urbwgrrgbbgbrgwbwwrrrbrgubrwrrwrwwgurgubuguwwuurgw",
    "gwwrwbuurrbgbwwbwwwurburrgrwggwrrwwwrbbrwgrrgw",
    "rwruurbbbwrbrgrwbbuwrwbbuurrgurrrwggbubwwwguwgbwgggruuugrr",
    "uwbbuwbggbrrbwrrrrgbrbwwgbbruguwubwbwuwuggb",
    "uburbbwbruuwugwrgwwuwrbrrrbgrbwrwrurrbubrgugurgbrgbgb",
    "wbuwrwwruwguggbwrwwrbburgguwgruubuwgurugbgugbubbgbrrguwbg",
    "rbguwgburgwgrwubggbbggwwguwuuuwgbbuwbrbrwrrbgguwr",
    "guwbgwwwgbrrbuwbwbrbbwrbbgbguuwbwrbugbbbgu",
    "rwrbgwggubwbwuubbwruwbgrbgrbuubrurgrwbgbgwbrwbburub",
    "gggwbrugrbbbuwbuwrwgugrugrrrrbwrgbbwwgwwgugggr",
    "wwrrbrwrgugrugwrbuugrrgrbwwrbuggbbruuwrrwrwrugbwbgurrrrr",
    "burwrruurbgggguuwubrrrgubgruwwwrwuggbwbwuwurg",
    "ubbgbbrguwubrwwbrurbuuuguwggruwgrgbbrgbbgbburwrbrguwrgw",
    "rwrgbbrbwwrwggwwbguwrgrrrurgrrgruurbuugbbgb",
    "ggugwrrgwgrrwbwrwgrurggggwurgbgwwurwrrwrrgwubrw",
    "rgbuwbbrrguuwwgbrugruuurbgwuwwuurbugrbrugbuwubbruuggug",
    "rwuwbwrgrwbwugrwubrgbubuwuwbbbwwgggugrbuwrrbbgbwurgw",
    "gubgbwuurgbwbguuubgurggwwrgrwbuwbuugwuugwubwwwwggugr",
    "wbrbrbugwrwrwurrbrruubgbbwwuuuuwwrwwwurruwgwbgugw",
    "wurbrruububbrgwwrwbwurgggrrbrgrwbgbbrwbbrbwbuwugwgubwur",
    "gbwbgbgurwurguwgrgwbwubgggruuuwuuggggbguugbrwgbwburgw",
    "ugbwbbubwrggwuwwubbguurbbrubburuwugwrurbugurbubrgbrrrrr",
    "wrwrrwgwbwrwurggrrbbgrwgbrbguububrwrururrrrrwuwbbgrrbrgg",
    "uuubrrrubwguurguwgruwrbruwugrubuubbrbwbugwrwwbruurwbur",
    "wwwwwbbbggggubguuugbbbbuburrugrbbwubrgbrguuug",
    "wwbgguguugbggrrbwwuwrubgugwuwugbgrwwrggwgwrwurburgbrb",
    "ubrgwbwbwwuwbwggrrrrwwbwgruuurbwrruwwrgburrwurrwrr",
    "uuwrgwbbbrggrrruurwrrrrbrwgbgugbburbuburwrrbubr",
    "gbwubgbggwwbgbwbbwwwwwrwbbwwrgbrgwwwrrbrgwwwr",
    "bbuubrbuwrgrbrgrrbggbuwrugrwubwwwbwbbrwggugurwgbrgbrgbb",
    "bbuwrurgurgrbubuguwrrurwrbggwuwguwugbwbwbbwrbugrw",
    "brrbububggbrgurwurwbwuguwuwrgubwugwrrbugrbrwgwgrgguwg",
    "burgwuurbrgruwbrrwurwuwwgwuubwrgrgwgrguubguggbbuugrrggrgw",
    "rgwrgwurbgguuwrbguwwgwuwubgwguwgbruwrrguuwbbwbr",
    "brrrubwrugrggugrwgbwgugggbuugrwguuwrwwgwuruwwbrg",
    "rggbwgwgugrrbrbwububgrwgubrwbwbubwburbubbw",
    "uubrrwwuugwubguruggugwwrrggrrwwgugrurubrgbwurgrwug",
    "uwrwwbguggwugwwrguuwbrugggugbburgwubruubgugbwgurgw",
    "wbwgugrurrbgbuggwwwrrwwgrgubgbbgbwrrwrrbubuwbr",
    "uwggguggbgwgrgrbbgruwurwggburububrgbwwwguburubrugrruugbwu",
    "wgwgbrwurgwbrrbgwruugurbgwguurbuwubbuubrbuwwwgbuwbb",
    "guwrrbwwgburbgggggrguwuwbbwrbuurrwururgw",
    "rurwbgrwurugrwwwbgrrubrwwwbugurbbwbrgurbgwrwwrgwrwwgwbr",
    "rurwbbwwbubwbrgugwbggbbbguubwrbwbwggwwbguurrub",
    "gbuwbugrrwgwrgbbguugwuwwwubuuwugggrbbbggwrugbubu",
    "bguubggwggrwuruubgubrrrwbwuuggwwbwwuuuurbuugbggrrwbu",
    "uguuwugurrbgbwggwrrgwruwuwrbruruuwwuwrubrruw",
    "rbgwbrbrwbuuwgrgrwwggwrwggrgwgbgrubbgwwuwwrgw",
    "guwuugbwubruguwbbgrbbbwbwbrrurgrbrurrbgbbbwbubr",
    "uubrbuubrruwwggguugrugburwrrrubbbggbbrrbuwrwrurgw",
    "wubbgrruruuwrgubgruwubruggwrwgbwwwggwurggwgrrub",
    "bugbbrbwruuwbrbrguwrbbbgbgwbbbwbbwwwwbwwurruuubururuwwbuw",
    "wrubrrguurwrbwwrwrwugwuuurbgbrgrwrburbrrgwwbbugwwbgbrugb",
    "wwrrurrwugubgbuuurrgrbbwwgwurugurbgurbuwwrguurbguu",
    "wbugrbwggburugrbgguggwbuubbgbggbbburgbbgugurrurgguggw",
    "buurgrruuwwggbwwrrbrbwgbgruwbwwbwrrurwwbggbwwbuggbuwrgw",
    "ggwuwgubbuwwwurbugrbwbrburrgggubuwwururruuwgbwurwwu",
    "uwuburwwrrwggrgwbubwrwuggurububrrubgwbwbrruubrrbrww",
    "wurgwwggruuurwuwbburbrurburbwubuubbwwwwuubwugbrrrgw",
    "wwubbbgbwgbgruruwbrgugubrrwwugrrwwwubrrwuubrwwrgggbwrb",
    "rbbbrbwburbuwwwwurrrgrbwubbbubbrbubggrguuwrrggwrgr",
    "gwwrrwuurgruwburuugrwugrbgbwgugrgggwubbrguwrrwwgrwbrgw",
    "wwbwggbbbuuuugbgwubwurrbgwrwggwgbrwgrbrwwuuuurwwwwwwguuwbu",
    "wuurwbwrgbrwrgrwuruwbuugurgwwwbrwwgbwuwbuwburuuwbrwbwuwuwg",
    "rgurgwwbwrbbbuuuugbrgububwgbrbwgguuuggbbgrrrgrgw",
    "rubgruwurburuuuwbwrrbwuggbbuggwurbburrrurwgrrgruuw",
    "urbgbggrwgrgwwuubwrguwwgbbbrbbrgugrwuwbuwwb",
    "ugwwrwgurrruwbrbbrurgurrubrbgrrbuwbwwubgbbguugwuguurrgw",
    "gbugwbrwbgrguwrrwgrwbbwgrubgrggrrwwwgguurguguggbgrwurgbr",
    "grrbruubggggbbbrbrwgbubgbgwugbrrrgrbuubgrrwbbuwrgugrbw",
    "uuuwbbbgrwurruwrubbrgggrrgubwwbbgwuugbubrrggbgbwguwwwru",
    "guwrwggurbrguubgrruwgggugrbwwrwwbwwbuwgwwgwwuwggwbgbwgbww",
    "uguugggrbwgrrgruwbuwugbrrwuggrwbwggbgbburburbw",
    "bbbwrwbwgrugbbgrwruwwwuwwrbguwbbuuurrgwrbgguruugwbbbb",
    "gwgwugwurwrwbwggwrgwuuugwgwbbuurguugbbruwwrwwgrwrgrwb",
    "grwrwggrrwgubrrrbbubwwwwbugwurbuuuwbuwrbbwgwbwwubugg",
    "wgbbrbbrbgugwugbrwwuwuuurgrgwbbwwwwuwguubbubwwwbrrbuwgwgwr",
    "rwbububrwrggubbwrbuugbugrrrggbrwrrbwbbbbrgw",
    "uwuuuugrguwububurbrrruwwgrbubwrwurwrggrrgw",
    "bgurrrrbwgrgbbwbwbwgrubgurgbgbgwurbgugrwrb",
    "rwrugruugugrwruwbwrrguruuurgwuuuwurbgbwrrwrgwurburwrrugbbrgw",
    "ggbwrurrrgurwgwwuwgwggrbbwgwwuugrgggrbguugrur",
    "gruubgbuubuwguggrwrgguwbwgrggrrbbruubrrrbbuw",
    "rgggbugbgrwwbwbwburrgubrgugwwwrrwburbwuubwuwrrwuu",
    "wguwggrbgrbgwwrgwuwbggbuwwwururuurbburwwwbbrburugrwrbwrrg",
    "urrbrgbrgbbruuwruwubgwbrbuwruwbwbuwgrwuwwwuwbwwuwgggb",
    "guwuwwwruuuugrwgurbbwgbwrbbrwrgbubrbwgwwuubgrbrwggrwwww",
    "buwgggwrggrbgwwwwbubrbbrgbwrrgruwrurrgrgw",
    "gwgbubruwbbwbbwgwbbruwbbubwugwugbbgwgbwuurgw",
    "bwwgwwuugrwwbuurgrwrrrbrbrruwrgugurururrwbrwbwwrwurwuu",
    "wwrwgbgugwuwuuurwgbbbggbbbugubbgbwgggrbwrgw",
    "wburrrrguggbrwuwbbrwwwuuurrwrggrbgwrrwurgw",
    "ururggggrwwrwgrbuwbbgwbugrrbgbwbgbrrbugwgbuuwwrbrw",
    "wbwwrbgbgwgurrrwburgrurwgrgrubrrwwuububwrrrwwggubuwwrgw",
    "brwrwgwubrrbgrwbrwbrurbburrgurbrgwggrubuwrgb",
    "wggbgubrggbwrguwuubguwuubbwwguwggrrggbwugbbgugrgw",
    "ggbbugbruwwubrrggrugurbuubbbwrwurbbgubbrrwgggbg",
    "bwbgggguuggggwurgwbggbggugwrbugubbbbwrgwwwwwbwrrrgw",
    "wrruggrwwgwbrwbgrrrwuurwuuurubwrgwwbrbgubrgwugbwgbwgrwrgw",
    "gwbgbwbrwbbruuwbwugrgbbrruwurbggrburrbrggggub",
    "uwbgwuurbgbgwwrgbbbbrbuwrwruwwuuurgrbwrgrruwwrbwrgrrw",
    "rwguugrubggguuwrgwugwbgubrrrurwwgbuwgbgggwwwrrrwrgw",
    "uugggwurbwrrrubwggwburwuwurwwguugrwruguuruguugwgb",
    "grwguguuwwgwbwuuruwwgwrugggugbbwwgwruguburb",
    "rbugruwbrgrrbrugwbwrgggubguwurruwrggbggguwwubbu",
    "uwbgbuubbgurbggubbbuwwurrwbuurwurwrrwuwrrbgwrwwb",
    "guuwrruggrbbrbwwrubwrwbwggbwubgrwwrbwggrgwbw",
    "rbwgggrgurgguwuguurwugwuurburbgbbgburuwbrgw",
    "rubugrgwwggbuubrbgrwwgruwbugbbbruwgwgbgrugrrrwbrrbuwuubwu",
    "gurggrgrrrwrwuwbbggbubgurbwuwrgbbwbgrrggwrgwrgg",
    "urgbrbbgguugwubrgwuuwbrbgbrbuurggrrwbrgw",
    "bguwwwbwbruwggubwguwrwugrgrubrrbuuuuubrwbrwbubububbwruuru",
    "ububgwgbrgrwwrguuwrgugbggwubrbgurwwbgguurbgrgwwgrbuggrwbrgw",
    "uwbuguggbgrurrgrurrwbrubrrubbwrrgguwugubrrurbrbrrgwwg",
    "wwurrbrguuwwrbguggbuwruwgruurwwugugggurggrrrgwrruwrubbwwur",
    "wruurbrbbbuwurrrwwrbrwwbwrbrggubwuubbbbuwbrrrwbggwwrgg",
    "bwrwburrgwgurbrbwbrruburgrgwwubguguwwwgwbrbuggrwubbr",
    "gbgrwuugbuwrwgrgrburwwrggrbgwrgguugrwguubrgwwrrwrrgw",
    "rgugubugbrwuwugwbgrwugrurwwrrwguwbbruwbwrww",
    "wrurwbbgwrrgbgwggrrgbrrwuwubrrbuuwrwgrrgrggbbwrubwrbwwgrwg",
    "rrubrwgwuwbbbugwrbbuuwgwbubgwgwuwuwgrurrwrwwgrgu",
    "ubrurbbwururburwrbubbuggggrrwrrrgwgbbwuuggubwbu",
    "rggwwuubbggugwubggwuwugwwrrguuwbwrrrbwwgbgwwbrurw",
    "bgbgguwbbrwrwburbubwrgwruuwgwrbgbrggbgbgrrrrw",
    "uwgrrggrwbbbuwbgbbrrwgwbbburwuuggwwurguuuwruwubrburgw",
    "uubugwbbrrwbuwggwgrwgwrrwggwwuugburgrrugbbuwg",
    "gbbwwgubugwbubwggwbrwwrwwrgbbbwgurugwrwwbwwgggbgrwwgubg",
    "ubgbwwburgbwuuwbrruwbwruwuugwbgwggrgrwbwurbbbwrgurwbg",
    "wrwgbgbgrwwbbbgwrggwbbwurggggbgwuuguugrgw",
    "bgrbwggwgbrgguwwwwbuuurgwrwuubbuwuguwbgbwggbgbrwbbrrwbu",
    "gwubwgbrurbwwrrgugwwgbwbwuuurgwbwrurrgwurgw",
    "rurwuwugruguggwugruburbwuuwgbrwwbrbwrgbgwgurwurrgw",
    "uburgrbugbbubbrubbrbgwbrrbugbguguurrgrrgwwrrbgbbbu",
    "gbwbggrbuwbrrbbrgugwwrbuwggwggwgrrwwuurgurggbww",
    "ubwbrbwwwwwrguruuuwwwrbwurrruguubruuwbuwruub",
    "bbwwgrbbbbbbwwugggugwgrbwrbbbbbbrrwrrwrwgwb",
    "wuubbrbbbuubruwurrwuuruurbwbguwuugbrugwwwbugbruu",
    "gbwwuwgbubwwrwguugwwbwrgbwuuggrwbgbuwwguggb",
    "wrwwwwbwugbgbuwwrrwuwbbuwgrgwwwwrbrgggubbrbuburwr",
    "uwruubbrwwrrgrururgwuguwbgbbgrwrrugbwuububrbgwuwwrbbwwr",
    "grggbuwbbrwbgubwwuuwbggrugwgggurbbburubuurrguuuwrrw",
    "gbbbbugruwwuuubguuugbuwwwugrggbrggurwbwubrrbwurgwggbgrgrr",
    "uguububuwwurruuggwgrruwbwrrbwwgwwgbgrrbgrgw",
    "rrwuwguwubggrwbwbruuwggruuwrbwgrrgugbwrugwguwugbbrb",
    "wbwggrbrwguwwugggwwrbwrrbrgwwwgubggbrgrrrgububgwubrgw",
    "wrrrrrwrrwrrwuwrbugbbwuubugrburgrbbrruurbuwwbwrrbubrgw",
    "gburugrbrugbuwgbbwuwgugrbwugwwrbuuguggurrgw",
    "rbgwwwwgwwburwbbruurggwbwggwuggwrgggwgggwwubgrbggwugbgbrww",
    "gwurwuugrbrwgbbbuwguggwrurrurwguurgururbbrruwwgrrwgbrgw",
    "rwuwgbuwrbbgwbbwgggugggwrgwuguwururrrbwggrwubrwgrrwwbubgb",
    "rwrgubburrbuwurubbwrbwgbgbuwrbrrubbwuuurguwururgw",
    "ggbguuububgggurgruwgrrggwrbwubggurugugrgggwurwbgbwr",
    "brgwrububuwrrwrbwuuugugwururbuuwurrubrbrwwuggggruburbub",
    "uuuggrrbgurruurrbrurgguuuuggrbgbwgbrurwwgwurrrrgrbu",
    "wrrrbrbggwwrgrgbuurbwggrguwwurwrrrrubgrgw",
    "wbwbrwrubwbbubgugruwrwubwguurwbwbwwgurggggrgguuug",
    "rrrbrbggwggggrurbugbuwwrgwburgbgrwgbwgrgwb",
    "ugggurrgrgwgrruguwwwbugrbrbuggwwubgbbgrggrbbuuwuwwbbubrgg",
    "wrwbuwrrburbgurggbwubrwurwbgrggbwbbruggguggbrr",
    "rbbububbrrrrwrubwrwbrugrwbgguwurbwgburrgbwwwwuug",
    "gbgubuugubwwuwrbwwgwugrwgrggruwbugwbuwubgbwrurwrgurrgr",
    "uubwbgubbrrbbggrgwgubwwgrwggrbuwbuwrbwwrguubwrgw",
    "ruwuurggwwuwbbrwbwugwugbwbgugwwburbgugwrwggrbruwgwbuggg",
    "bburgrgwuurgbrbwbgurwwrrwwgbgurwubwbbggbbrugrruugbgr",
    "grwuugwbbugrgrbuubrgurrbubbwurgbuurrurgw",
    "ubwggrrrrurwggwubbbrgbrubwbrgrbrwuruubrubugbr",
    "urguggggggguwbrbbubggbrwuurrrruugwrbuwrgwbubbbrg",
    "gbgbwggwubrgwburbuwgburgubwbwgggguwwrrwuwwuggwubwbbwbrrgw",
    "urbwbgbuguuuwwuwbgrbuwbbuuuwugwgwbgurwbwgwugbu",
    "urrgrrruwwwubbbbgrruuwwgrwbbgwrbrubggubrwwbubguu",
    "rbwwuubwwbbrbubrbgbgwbrrguwrrbwruwbugwbrgw",
    "wwggwwwbrgwwurubbggrrwgwgwbrbgbbggbrgrubgrb",
    "brbwrrugwgrgwgugrugugwurburrbwrrrgrrbrbbguwbuburgw",
    "wruubbbuwwuubgwrwwbuurgbrwrbuggggbwuwrbubggwruwwwbbguu",
    "burgbbrrurburwbuuwbgwbwrgrrwwuwuugbgubgbwwggubr",
    "uuurgwugggubbbbugrugwuurwururuguwwbgrwgrgw",
    "ubrbbbgrgwgubuwggwrrbuuuburuwwgbguruwbuuugwguruuurgubrbrug",
    "rwgwguwrgrwbbbruwrbbwbguburbguwbuwrgrwwuubrub",
    "rrbbgrurrwwwbwwgbbbwwbbrbbbbwwgguggwbubuwbuuwuubuurgu",
    "ggwgggwbwbwuburugrrbwuwuwwbgbwrubrubugruubrug",
    "wrbbgbgbubrugrruugbuggbbwubwwrbrgbwurrrubgrrrgubw",
    "rwuurgubwbwurbuguwwuwuguwruuwrrwbbrrrrwrrbgrgggburwgrbb",
    "wggwruurrwbuggruwbububgwrbburwgwbgrruwruggrgbgbguugwuwuw",
    "rurbrwgrbwwgrurwgbwbwugubwbrbgrgbgubggwbbrubugrrr",
    "ururuubgwwrwwwrbrgguwurgbbuugguugbuwurrwrurwuwrburburuwub",
    "uwwwbwrbgururuggburruguurrrwgrbgwbwbrbgwburbw",
    "ruwggwubwbwggruggbgubrubuuwuurugwrwuuwgbubrrurwuwu",
    "wwrubrbwrbwwuwgurbrwrurrubbwrbwwbrbrbubwwubbgbubwruwgwuw",
    "bwwbuggruwwurgbuwgurubuwugbgwuruurruwuurgrgrrr",
    "urbuwrbwgwurwrggugrbruwbgwggwggrubwwuubwbbububg",
    "rwbgwgbwwuggruubguubugbuggrrwbwrrbwbwruububw",
    "rgbrrburwugurwrrrubwwgwrwuwwurbwbuugurbrbuuggrrwrrw",
    "bgbrugurrrgrubrbrwwrbwurggubbuwrrgwrrgbrgw",
    "ugrgbbbrwgrbguurwbburuurwwrggurgggrrubrrbrbrugwurubbw",
    "rrwbgburwrwgwurwrwbrgrwgbuuurwuguubgguggwbbuwuubguwrrb",
    "rguuurbruwgwrugwwguuuwwwrgruwururgwrruwbbbuuwggurbu",
    "wuwguurrgwubruurruwbwbgwgrrbuwgrwbubwuwrbbubu",
    "wbbggubrgbgggbrwbwwruwwruwwgwrbgrgbwbbuburb",
    "guburbrwbgwubwwwubbggggwbwrguguwwbrbbgwuwguwrwgwg",
    "gwgwggwuubuggrburwwrrgggubuurubbgbwbrgbwwwrbgwbbbubru",
    "wbbwrbgbugbugwrgrwuguwrrrwgrugrbbuwbrwubuu",
    "gwgrrgwrgwwbgbbrububbgwggrbgwrrwubgwbguggggurgw",
    "bwbbgrwuwuugbbugbwwwgwwbrburggbbubrwuggurrbwwbrrgb",
    "gbrrbgwwrrgubbgggrgbubrgubguwrugrrguwgruwubuwbgbwguwgruwrgw",
    "bwwgwgrwbgrrgwrugrbwwwurwwrguubuwgwgrugrrgrgw",
    "rwuubggrgubbwuwgrrwurwwwbrruwrububuggbrggrggwrgwrgw",
    "rbuubuwrbbruwbuwgubguwrurwrgbwugbwwrgbrwwwggwbuubgw",
    "ubrrbwwgrbrrubuwbrubbugwbugwrrbrrubrwrurubggrgrgbgburu",
    "buwrwggubrbrrgrwwugwwburgburrgbuugrwruuuwuuwggubwbgwurw",
    "bugbwrrrwbbbubwgrrwrrbruurgruugbbwbwwurgwwrgw",
    "ugwgwrgbbguwubrrbugguruggbrwwgrwgrgwgrbrubuwwrwguwrwurgw",
    "rubwgbrgguwrgbwurugburwwwrbrgwugbbgburubwrrgrgbggu",
    "bwuubbuurbuwburwwuubuuwgggbbbgrwrgbwwwrbbrrubruuw",
    "wbbwggbbwbrgwrrbgwwwwuburwuwwrgubgububwwuuwrbrrgw",
    "rbgwrwuwuugrwwbwgrgbgruugruwrbwgwugrwbrggbgrgbrrrwuru",
    "ubgwbwwrugggrwgurrwbwwrbwgrgwggwbrubwwwuggrwgbb",
    "rgwubwbrgrbggbwuwuwugruggbrrgbbwrgruwuwrgw",
    "urwrwrurubwwgbwgguruwbuugrugwggrwurgbrwbbrgbwbgbugrrg",
    "bbrwgbuwubwubgwgrwrwuruwrrbubrwrgggugwruwwubw",
    "rrbuwbwrrwgburbwguugwbwgwuwrwwrbwgwrgubbbugbrbggbbgbruu",
    "ugwgubrbbwrbbgrgrubbwrubrbgwuuruwgugwbwgwwwrrggwgbrwuwbwb",
    "bbrbrbwrggbbuwgwburwuwuggrbgrrugwgwurrgrwuubwguuwrgw",
    "rbbuwwwbbgwurwbgbgrbguuwrrwggwguwggbuwbwbggwbb",
    "uruurrrrbrrgwbrgbuuubugggrwwgrbugrgbruwbggwuugrugububgugw",
    "wwuwwruuwwgrgwbuwruuwrbuubgrrububuggubwuuru",
    "ubwbggggwubruguwwgbwbubwwubgwbuwbwbwggrgw",
    "wurrbrbbubbbwguwbuugbwbrbwguwurwrrwgwwwugurrguuwuubbrugrwu",
    "wrrgugrwwgugrwgwgwbwrwwrrbwubwwrguuruggrugbwgrwrrbgbrwwrb",
    "uuwuggggwuuwbuubgbwrrrugwuuwbbwgrrbbrwbuururgbruwr",
    "rwbubbgwugbgbgurgggugwggbwrwubuwbwwgggbwrwrgrwubrwgwg",
    "wbwrwwurgrgrrrwwuwgbwbugbwgbwbbrggwbgwbgrggbgrrwgwrbrb",
    "gugbguwbwrwbrgbgggrrwrgbuuuggbugbwubugbbgbrrbrruburgbu",
    "rururwrrugubugububbubgwugurwgwwbrbgrwbrwbbwgu",
    "wrbggguruwgwgbrwrgguburbgwburggrbrwwuwuggru",
    "rbbbwbrbwbgbwrbbwuggrbgwbrgugggbwburwubgbrgwuuwrbguurwrg",
    "gugrrggbbwrbwrwbubuurrbrbruuwwuuugurwrrrrggwuwgrruruw",
    "uruurwbwbuwrbubbgrwwgbwurbguubbuwgrrwrbrrwrggbwrr",
    "wrbwuuwgwrgrubrurruubburgbrbbubuguurugwurbgubuuwrwrbwr",
    "wrugbwrugwggwrubguwguggbwrwwgbgwuubbubuurbubwbuuuwu",
    "uuuwurgwgubuwrwwgrwuguwggrwgggrwruugbbugggbrwrbugw",
    "bbbuuubwrwbwrwwurugrwwbrwrrrubrwwwggrurbgggbg",
    "wbgguwwwbgbrwrrruurubggrwbwwrurgurwrgrrgbuwwggg",
    "wuwwurugwugbuwgbuggwrbrugbgrgrruwwbwugbrwwbwrwgwgguubuurb",
    "bubwubbggruggwububwuwrwgbugrwgbrwgruurbgrrrwbbrgrwurrgwuwb",
    "rgrgrgubbwgwbrgrbururbwwwruwwwbrbwbbuuwbbwgbwrgg",
    "wwgbbuwgubbubrbgrbwrggggbgrbwgwurrrggugwbgbgrrurruwrb",
    "rgruruwrggwrrggbugwgguuggbgwbrwwguuuugbbbwruuugrugubbgwg",
    "rrrrurrubwrrugbgbubrbgrgbwwbbrurrrrurwwgbggr",
    "bwwrgguubgwgruuuwrwgubbgubuurrurbrgurgbwrbuwbgrruuuubugwb",
    "rrwrubugggguwbuugrbubwwwrwbbrgggruwggbwubuubrurgw",
    "bbgubbwrubguuubrwuggbwggggggbgubuguuwrwrggbwubgwrwuu",
    "rugruwrbgrgguwwrwrbggruwrbwrrrurrgggubuggugubrww",
    "bwwgrgwgwgbgggguurrwgwuugbwwrwbbuurrgwguubg",
    "wgwgwuburrwbgbuurggugbburwubwuwgwuubwwrgbrrrw",
    "wgggugwwwggbggbbgbwurwwwurbgrwugugggguubbbw",
    "grburguwbwrrgwubbbuburgburrgubbruwrwggugrgrbrubg",
    "uruurubuwgurgrubuwuwgbbrgguwubuurgwrwwbwbbuu",
    "wgurrrgwuugburwrrwwbrugwbwwrgrgwwwugbwggbgruubwurgw",
    "bggwrwggrgrwgrrbburubrbwwbrubbbbbuuuuubrwbbbwrbwubgbwrgr",
    "uwuguuwbruurwgugbggrrgrruugrrbrwrurrgrrrgbbbgwurbubrgw",
    "grwbwruwwbwrugubwrwguguwwrwgruwrgbguugwwwbuw",
    "brbggwbruwggrguruuurrgrwgugwgurbrurrburwrbubuggbguwurrgw",
    "rgubuguruuwuggurbuuuwwrrbbuburwruuwuggruggwrwwrgwrrubrrur",
    "rgbwrggwrrgurrgrrbrgrggrbbbgwubbrbgubrguwuurbwggbgwwwu",
    "grubgrwgrgrurrgrggubgugbgwrbbuwgbgruwwwbbrwruu",
    "grgwrwrugggubwgwwgwwwgrgruurbrrwuurgubbbbgrbbwrwuubgrwwb",
    "gwbuuubbwgwrbubuwbbbgrwgrwgwuubgwwrwbbbbwugugrrwwuuruuggu",
    "bgwubrgwuwwuruwbbgugbgruwwuuuggbrgbggbwgwubbbrrbggu",
    "rruuuburggwbrbwwbwrurgubburggbggwrugururbugwgwbgggu",
    "buwubugbwrgwbrrwuuurubwuubgrwrwrbubwrbwrugrwrbgrur",
    "rwbbwbrbrgwggwwubgbbbguubwwgbrwbwbguburrwbg",
    "uwwbubbbbgugrrgbrwbgwuwwwgwuwwrwurwrgwwuugrbbwgbburrbgrgw",
    "wbbgwrbrwbrubbrgbgwrrwggwubbbgbgbwwbggwrbguwwggurggurb",
    "bwrbuwwgubwubggwgrwwgbgbgwguwuuguuuuggbugwgrwgwwgbr",
    "ugruwubuwurwbgbwubuwggrbbbbburgbggrbrwrwrgrbugwwgubgguuwrgw",
    "wuwgggggbrwugbrguwururruugwwgugggwbwbbruubgbbrwwrgw",
    "rbbgggubgbburgbrrgubwubrburwggbrugbgbuwgbuwbubggugrrubuw",
    "rgurugguguwwrgbbrwbggwrggbwbrwgruwuburbwbggrgwwwuwwgur",
    "ubbbwurwuugrubwrurrrggwggbugbbwwurggubbwrrggwwbrbwbbbgrbub",
    "bwgrgbugggbgrrwwbuwuwwwbrubwuugrurrwuwugbggbubrbgubrbbgww",
    "brrggurwgwuuwburuwruugbwbuuuwuwrbugurubugbwwu",
    "uubrbgguggbbbwgwubwgrrbgbwggrrubrrrwubugbbgwrrrbg",
    "uwuruwrrwwgbwwbgbruuuggrguwbrubgbuugggrbgbugubbgwwrwrrgwbgw",
    "wgrbwurwbubwggugrgwubuggrrurwwrwuuuuggbgrbbguuuwguwgg",
    "wwururbgrurgwruuguwrruwuggrugwbrurruwurrbubb",
    "urrrbggrwwwbwbbrubwrgbwwrwrwrrruuurwggrrwgurrrrgbrg",
    "gbbugbwrggwgwrbbbgwgbuugbruguuuwuwrgbgrbwgrgw",
    "uggbrrwwubgwbrwrwrbugurgrubwbgbuuububruurrbrbwbrgw",
    "bubrrwuubuuugrbggrbrwgrrwwggwrurruuwguwrurg",
    "ggggbbuwuugbubwgugurwwwrbgbrburrbwgbgrwrugrrbggbgubbwggrgb",
    "wbrbwwwrubggwggbgubbrrubgrggbuggurgrwrrwruurubb",
    "uwbgrbgubwguuwrbburrugugbwbrggubgrrrwbubrruwbggurrwbbrgw",
    "ggbwbruwubggburubuuuuggbbburwgbwuwrwbwggwb",
    "ggwwuwwuuwruwgurbuwbgguwurbuububrwbubgwububuggb",
    "gbgbbbbrwwwgwbgrbbuwuggwrugbugbuwuuruwgwruguwuwgrrbggr",
    "rruburbbrrguwwgguguwrruwgwrrbrwbbuuuwwgurbwuwbg",
    "gwwwbwwrrgwwgurwruwbwbrgubwgbgbwurrrgwugbbugwrbrg",
    "urgrwgbbwrbgwbwggbugguwwrgggugbbbrggubbgbrugwgrgw",
    "uwgrwwbbbwwrgbbwrwrubuurbugwbwugrbbgrruururuuurbuurw",
    "uggrwwbrurgbwrggugrrbbwwwwbrwgrwbbbuwgwuuwuwbrrb",
    "wruuwuubrwbuubbbbwgwrubugbrrbgwgrguuuwbbwggwggugr",
    "wuubrurgwrruwguwgrguwugugwggrrgwwbruwrubwrrbg",
    "wwrugbubuurwuubburubwrwuwuuwrgbwbrggwbuwgru",
    "wrbggbrbgwwrgrggggwruwrwbgbuuuubwwuuurrgbbrurbgggurrrgw",
    "rwgwbbgbbbgrbgbwbrguuwgwrwrwwwuurwrruwburbwgbgbguguwrbwurg",
    "gwrbwguubgrubgwwuguuwwgugbwggrgwrbrgwbbugugrbrbrrw",
    "wgwugbbbbbugrbggubrwwbgguurggbgbbbwwrwwgrrrrbggrgrbb",
    "gggbrbuuugubgwgwuggguwbgbbugwbwrgrbrrwugrggurrwgur",
    "wbggbwgbuwuwgwgbwwgrrwrgugggwwbrwrrrbwwrgw",
    "gwgubwbrgurrguubburuwguwwbrggwwbbbuwuubbggbruu",
    "gubwrbrwrwrwwrwggbgwbggbgwgwwguwubrrwguuguubrrwruuwuwurrgw",
    "guuwrurguurguruuuwrwbgggruwrbrbbwrrrwwbuburgbwwrubwrgwwbgb",
    "rgwwuruwrrrrrrbwrrbgrurgwwuggrrubgwurwrugrrbrwgwwwrwurgwbrgw",
    "ggwggurwbggwwubwrbrurbuubrrubguuruuwbgrububbgrgw",
    "gbwwggggurwggbuwrrgrwrububwggbwbwbruubrgrrrubuurwwbuwwuu",
    "ugggbwbwbrbrgwwburbrrubbwuuugurwbbbgbuwbbwuwrbgwgwruw",
    "gwgrwurgwgwrwgbruruwrugwwguuuugugggrbgbwgbw",
    "bwuwwguggbwrrbgburbwbguwwuwwbwurguwwbugwrgw",
    "bbwbwwrgburgbbuurggwrururwruwrugbubuguwwbrubuugg",
    "gbgwwrurgbuwuwbrwubwbbgruwbbgbgrubuwwgrwgg",
    "rruggbugrgurwuburgubwbbgburrwwbggwwrrwbbwwbrwwrw",
    "grrbwrgwurbruwrbgurubrbugbuwwrbrugwgwuurggbwrguggbwruw",
    "ubbguuurwwrgbuuwwgrrbububugwbuuburwwuububwbwubrwguwwwrbw",
    "rwugwbrrwwuwwuuruubwwbwbuwuwgurwurrrrbgubwggwrwbwrgbww",
    "brbburrgububgburgbwuubrrubgbrrgwbuwwwbgwguwuurubrubur",
    "bwwubguwbrwbrbugwurrruguwwbuuuwrbbbbwwbuwwbbgggurgw",
    "wbuguubruburgwguwguwwbggruwubwbuuggwuwburburbuu",
    "brwwbwrwbgwugubuubrbwrbgbgrggbuuwwurburgbbuwruggwrrrrgb",
    "brrbbugwbgrrwwbuurbbuwbggubuwurbgwwbubwwubruuuwbwurgw",
    "urbbgbwbwbgurbubuwurggrubwgrgwwrgrrggubwrgg",
    "urgwggurwburbggugwwwugwbguwuwgbbrrbwurggugugrwurgwwrb",
    "rggwuwruugrwgbwuburuwbbwrrrgrubuugwrurggburrgw",
    "wrurbgbbugurwugrbbbwugbwubgubgruwuuguburrrwggbuuggbrrbw"};

using namespace std;
struct Longer {
  bool operator()(const std::string &a, const std::string &b) const {
    auto a_size = a.size();
    auto b_size = b.size();
    return std::tie(a_size, a) > std::tie(b_size, b);
  }
};

std::set<std::string, Longer> good_patterns{towels.begin(), towels.end()};
std::set<std::string, Longer> bad_patterns;

std::string join(const std::vector<std::string> &parts) {
  std::ostringstream o;
  for (const auto &p : parts) {
    o << p;
  }
  return o.str();
}

std::string join(const std::vector<std::string> &parts, ll from, ll to) {
  std::ostringstream o;
  for (ll i = from; i != to; i++) {
    o << parts.at(i);
  }
  return o.str();
}

bool check(const std::string &pattern) {

  std::vector<std::vector<std::string>> queue{{pattern}};
  do {
    auto parts_history = std::move(queue.back());
    queue.pop_back();

    const auto last_part = std::move(parts_history.back());
    parts_history.pop_back();

    if (bad_patterns.count(last_part)) {
      return false;
    }

    bool found_match = false;
    for (const auto &towel : good_patterns) {
      if (last_part.starts_with(towel)) {
        found_match = true;
        auto new_history = parts_history;
        new_history.push_back(towel);
        good_patterns.insert(join(new_history));

        if (last_part.size() == towel.size()) {
          return true;
        } else {
          new_history.push_back(last_part.substr(towel.size()));
          queue.push_back(std::move(new_history));
        }
      }
    }
    if (!found_match) {
      parts_history.push_back(last_part);
      for (ll i = parts_history.size() - 1; i >= 0; i--) {
        bad_patterns.insert(join(parts_history, i, parts_history.size()));
      }
    }

  } while (!queue.empty());
  return false;
}

std::vector<uint16_t> towels_to_ids(const std::vector<std::string> &tt) {
  std::vector<uint16_t> result;
  result.reserve(tt.size());
  for (auto &t : tt) {
    auto it = std::find(towels.begin(), towels.end(), t);
    assert(it != towels.end());
    result.push_back(std::distance(towels.begin(), it));
  }
  result.shrink_to_fit();
  return result;
}

ll check_without_cache(const std::string &pattern) {
  std::set<std::vector<uint16_t>> solutions;
  std::vector<std::vector<std::string>> queue{{pattern}};
  do {
    auto parts_history = std::move(queue.back());
    queue.pop_back();

    const auto last_part = std::move(parts_history.back());
    parts_history.pop_back();

    for (const auto &towel : towels) {
      if (last_part.starts_with(towel)) {
        auto new_history = parts_history;
        new_history.push_back(towel);

        if (last_part.size() == towel.size()) {
          solutions.insert(towels_to_ids(new_history));
        } else {
          new_history.push_back(last_part.substr(towel.size()));
          queue.push_back(std::move(new_history));
        }
      }
    }
  } while (!queue.empty());
  return solutions.size();
}

} // namespace

int main19() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  for (const auto &pattern : patterns) {
    myprint(pattern);
    if (check(pattern)) {
      ++result0;
      result1 += check_without_cache(pattern);
    }
  }

  //   for (const auto& towel: towels) {
  //     result1 += check_without_cache(towel);
  //   }

  myprint(towels.size());
  myprint(good_patterns.size());
  myprint(bad_patterns.size());

  myprint(result0); // 308
  myprint(result1);
  return 0;
}
