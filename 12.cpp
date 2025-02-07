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

std::vector<std::string> input_real{
    "UUUUUUUUUUUUUUUUUUUDQQQQQQQOOOOOHHSSSSSYYYYYYYYGGGGNNNNNNNNTTTTTTTTTTTTTTD"
    "DDDDDDDDDDDDDDDDDNNNCCNJJJJOOHHHDDDDDDDDDDDDDDDDDDXXMBBBBMMCCCCCCC",
    "UUUKUUUUUUUUUUUUUDDDDDDDQQQOOOOOOOOOSSSSSYYYYYYYYGGGGGNNNNTTTTTTTTTTTTTTTT"
    "TTTTDDDDDDIIDDDNNNNNCCNJJJOOOHDDDDDDDDDDXDDDDDDDMMMXMMMMMMMMCCCCCC",
    "UUUKKUUUUUUWUUUUUUDDDDDDDDDROOOOOOOWWSSSSYYYYYYYGGGGGGGQNTTTTTTTTTTTTTTTTT"
    "TTTTDDDDDDDIDIINNNNLNNNNOOOOODDDDDDDDDDXXDDDDDDDMMMMMMMMMMMMCCCCCC",
    "UUKKUUKKXUUUUUUUUDDDDDDDDDDDDOOOOOOOOYSSSSSYYYYYGGGGGGQQNNTTTTTTTTTTTTTTTT"
    "TTTTDDDDDIDIIIINNNNNNNNNNOOOODDDDDDDXDDXXDDDDDDDMMMMMMMMMMMMMMCCCC",
    "UUKKUKKKXXUQQQQUUDDDDDDDDDDDDOOOOOOOOYYYYYYYYYYYGGGGGQQIINTTTTITTTTTTTTTTT"
    "TTTTTDDDIIIIIIIINNNNNNNNNOOODDDDDDDDXXXXXXDDDDDMMMMMMMMMMMMFFFFCCC",
    "UKKKKKKKXKAWWWWWDDDDDDDDDDDDDOOOOUUOYYYYYYYYYYYYGGGGQQQQIIDITIIIITTTTTTTTT"
    "TTTTDDDDIIIIIIINNNNNNNNLLLLODDDDDDXXXXXXXXDXDDDMMMMMMMMMMMMFFFFCCC",
    "KKKKKKKKKKKWWWWKDPPDDDDDDDWWWOOOOOUUYYYYYYYYYYYYYGRQQQQQIIIIIIIIITTTTTTTTT"
    "TTDDDDDDIIIIIIIIINNNNNNNLLLLLDDDDDXXXXXXXXXXDDDDDMMMMMMMMMMFFFCCCC",
    "KKKKKKKKKKWWWWWWDDDDDDDDDSWWWOWOOOOUYYAYYYYYYYYYYYQQQQQIIIIIIIIOIITTTTTTTT"
    "TTDDDDIIIIIIIIIIINNNNNLNNNLLLDDDDDDXXXXIXYDDDDDDDMMMMMMMMMMFFFCFCC",
    "KKKKKKKKWWWWWWWWSSDSDDDDDSSWWWWOOOOUYYAYYYYYYYYYYQQQQQQIIIIIIIIIITTTTTTTTT"
    "TDDDIIIIIIIIIIIINNNNNNLLLLLLLDDDDDDXXXXIXYDDDQDDDMMMMMMMUMFFFFFFFC",
    "KKKKKKKWWWWWWWWWSSSSDSDSSSSWWWWWOOOUYYYYYYYYYYYYYYQQQQIIIIIIIIIIIIIXXXXXTT"
    "TTDIIIIIIIIIIIKINNLNNNLLLLZLLLLDDVDXXXXXYYDDQQDDTMMYYYMMUUUFFFFFCC",
    "KKKKKKKKWWWWWWWWWWSSSSSSSSSSWWWWWWOUYPPPPPYYYYYYQQPQQQQAIIIIIIIIISSXXXXXXX"
    "TTDIIIIIIIIIIIIIIILLLLLLLLZZLLLDDDXXXXXXXYYDXXXYMMMYYYYMPUUFFFFFFC",
    "KKKKKKKKWWWWWWWWWWBBBBSSSSSWWWWWWWSSPPPPWWWWWWAYPPPPQAAAAITTIIIIIXXXXXXXUT"
    "TXXXIIIIIIIIIIIIIOLLLLLLLLZZLLLLLLLLXXXXYYXXXXXXXXRPPPPPPPPPFFCCFC",
    "KKKKKKDWWWWWWWWWWWDDBBBSSSSWWWWWWWWSSPPPPWWWWWWWPPPPPAAAAIIIIIIIIXXXXXXXXX"
    "DXXIIIIIIIIIIIIIIOLLLLLLLZZZZZZLLLLNXNNXNYYYXXXXXXPPPPPPPPPPFFCCCC",
    "KKKKKKWWWWWWWWWWWWBBBBBBBSSSWWWWWWWSSSSPPWWWWWWWPPPPPAAAAAAIIIIIIIXXUUUUUU"
    "XXXXIIIIIIIIIIIIIILLLLLLLZZZZZZZLLLNNNNNNYYYXXXXXXPPPPPPPPPPCFCCCC",
    "KTKQQKWWWWWWWWWWBWBBBBBBBSBSWWWWWSSSSSPPPWWWWWWWWPPPPPPAAFAIIYYYUUUUUUUUUU"
    "UXXXQQQIIIXXXXXXXXXXLLLLLZZZZZZZZZLNNNNNNYYXXXXXXXPPPPPPPPPPCCCCCC",
    "QQKAQQWWWWWWWWWWBWBBBBBBBBBSWWWSSSSSSSSPPWWWWWWWPPPPPPPPPPYYYYYYUUUUUUUUUU"
    "UQXQQQQQQIXXXXXXXXXXLZLLEZZZZZZZZZLNNPNNNYYXXXXXPXPPPPPPPPPPPCCCCC",
    "QQQQQQQWWWWWWWWWBBBBBBBBBBVWWWDDSSSSSSSSSPWWWPPPPPPPPPPPPPYYYYYYUUUUUUUUUU"
    "UUUUUUQQIIXXXXXXXXXXLZZZZZZZZZZZZLLUUUUUUUUXXXXXPPPPPPPPPPPPCCCCCC",
    "QQQQQQQQWWWWWWWWBBBBMMMBBBMWWWDSSSSSSSSSSPPPPPPPPPPPPPPPYYYYYYYBYYXXXXXUUU"
    "UUUUUUOIIIIZZZZZLLLZZZZZZZZZZZZZZZZIIIIUUUUUXPPXPPPPPPPPPPYYCCCCCC",
    "QQQQQQQQQWWZZZWMMMMMMMMMBMMWWDDSSSSSSSSSSSPPPPPPPPPPPPPPYYYYYYYYYXXXXXXUUU"
    "UUUUUUOOIIIZZZZLLLLLZZZZZFFFFFFFFFHHHIUUUUUPPPPPPPYPPYPPPYYYCCCCCC",
    "QQQQQQLQQQWWZZZMMMMMMMMMMMHHWSSSSSSSSSSSPPPPPPPPPPPPPPYYYYYYYYYYXXXXXXXUUU"
    "UUUUUUOIIIIIZLLLLLLZZZZZZFFFFFFFFFHHHIUMUUUPPPPPPPYYYYYYYYYYYCCCYC",
    "QQQQQLLQLLZZZZMMMMMMMMMMMMMMWSSSSSSSSSSSPPPPPPPPPBYPPPYYYYYYYYYYYYXXXXXUUU"
    "UUUUUUIIIIIIIILLZZZZZZZZZFFFFFFFFFHHFFFFQUULLPPPPPQYYYYYRYYYYYYYYY",
    "QQQLLLLLLLLZZZMMMMMMMMMMMMMMNMSSSSSSSSSSVVPPPPPPBBYYYYYYYYYYYYYYYYYXXXXUUU"
    "UUUUUUOIIIIILLLLZZZZZZZZZFFFFFFFFFFFFFFFFUUMMPPPPPYYYYYYYYYYYYYYAA",
    "QQQLLLLLLLLZZZZMMMMMMMMMMMMMMMSSSSSSSSSSVVPPPBBBBBBYYYGGGGGGGGGYYYYYYYYUUU"
    "UUUUUUIIIIILLLLZZZZZZZZZZFFFFFFFFFFFFFFFFMMMOPPPPGYYYYYYYYYYYYYYYA",
    "QQLLLLLLLLZZZZMMMMMMMMMMMMMMMSSSSSSSSRRSVVVVVVBBBBBYYYGGGGGGGGGYYYYYYYXUUU"
    "UUUUUUIIIIILLLLLZZZZZZZZZZZHHZZHHFFFFFFFFMMMMMPPPYYYYYYYYYYYYYYYYY",
    "QQLLLLLLLLLZZZMMMMMMMMMMMMMMMSSSSSSRRRRSVVVVVBBBBBBBYYGGGGGGGGGYYYYYYEEUUU"
    "UUUUUUIIIIILLLLLBZZZZZZZZZZHHHHHHFFFFFFFFMMMMMMPIIYYYYYYYYYYYYYYYY",
    "QQQLLLLLLZZZZZZMMMMMMMMMMMMMFSSSSSSRRRRRRVVVVVVVVBBYGGGGGGGGGGGYYXYYYEEEEE"
    "EEEEEEIEIILLLLLLZZZZZZZZZZZZHHHHHFFFFFFFFMMMMMMPPIIYYYYYYYYYUUYYYU",
    "QQQQQQGLLLLPPPMMMMMMMMMMMMMMMSRSSSRRRRRRVVVVVVVVBBBQGGGGGGGGGGGGGGYXXXEEEE"
    "EEEEEEEEELLLLLHZZZZZZZZZZZXZHHHHHFFFFFFFFMMMMIIIIIYYYYYYYYYYUUUUYU",
    "QQQQQQQQQLKPPPPIIMMMMMMMMMUUUURRSRRRURRRVVVVVVVVVBQQGGGGGGGGGGGGGGXXXXXEEE"
    "EEEEEEJEELLLHHHHHHHHHZZDDZZZHHHHHFFFFFFFFQMMMQQIIIIYUUUUYYYYUUUUUU",
    "JJQQQTQQQKKKPPPPPQQMUUMUUUUUURRRSRUUURRRUUUVVVUVVVQQGGGGGGGGGGGGGGXXXXXEEE"
    "EEEEEEJJJLLHHTTHHHHHHYYYDDDZHHHHHFFFFFFFFQMMMQQQQQUUUUUUUUUUUUUUUU",
    "JJJJQTTQKKKPPPPPPQQQUUUUUUUCURRRRRRUUURRUUUVUUUUVVQQGGGGGGGGGGGGGGXXXXZEEE"
    "EEEEEEJJJJJHTTTTHHHHHHYDDDDHHHHHHMMQQQHQQQQMQQQQQUUUUUUUUUUUUUUUUU",
    "JJJJJTTTPKKPPPPPPPQUUUUUUUUUUURRRRRRUUUUUUUVUUUUUVVQGGGGGGGGGGGGGGXXXXZEZZ"
    "ZZEEEJJJJJTTTTTTTTHHHHYYYMMHHHMHHMMMQQQQQQQQQQQQQUUUUUUUUUUUVUUUUU",
    "JJJJJTTPPPPPPPPPPPPUUUUUUUUUURRRRRRUUUUUUUUUUUUUUVVUGGGGGGGGGGGGGGXXRRZZZZ"
    "ZZEEDDDJJTTTTTTTTHHHHHYMMMMHMHMMMMMMMQLLLQLQQQQQQUUUUUUUUUVUVVUUUU",
    "JJJJJJJPPPPPPPPPPPUUUUUUUUUUURRRRPRRRUUUUUUUUUUUUVVUGGGGGGGGGGGGGGZRRRRRRR"
    "DDDDDDDJJJZTTTTTTTHHYYYYMMMMMHHMMMMMLLLLLLLLQQSQQSSUUUUBBBVVVVVUUU",
    "JJJJJBBPPPPPPPPPPPUUUUUUUUUUUURRRPPCCUUUUUUUUUUUUUUUGGGGGGGGGGGGZZRRRRRRRB"
    "DDDDDDDJJJTTTTTTTTYHYYYYYYUMMMHMMMMLLLLLLLLLLLSSSSUUUUBVVVVVVZVUUU",
    "JJJJBBBBPPPPPPPPPPUUUUUUUUUUUURRPPPCCGUUUUUUUUUUUUUUUGGGGGGGGGGGZZZRRRRRRR"
    "YDDDDDDJJTTTTTTTTTYYYYYYYYYMMMMMMMMMMMLLLLLLLSSSSSSUUUBVVVVVVVVVUU",
    "JJJJBBBBPPPPPPPPPPUUUUUUUUUUUURUPPPCCCCCCUUUUUUUUUUUUGGGGGGGGGGGZZZRRRRRRR"
    "RRRRRDDDJTTTTTTTTYYYYYYYYYMMMMMMMMMMMLLLLLLLLSSSSSSSSSEEEEVVVVVVVU",
    "JJJJBBBBQQQPPPPPPPUUUUUUUUUUUUUUPPCCCCCCCUUUUUUUUUUUUGGGGGGGGGGGZZZRRRRRRR"
    "RRRRRDDDTTTTTTTTTTYYYYYYYOYMMMMMMMMMMMMMLLLLLLSSSSSSEEUEEEVEEVQQVQ",
    "JJJJJBBBBQQQPPPPUUUUUUUUUUUUUUPPPPCCCCCCCCCFFUUUUUUUQGGGGGGEEKKKKZZRRRRRRR"
    "RRDDDDHDTTTTTTTTTTTTYYYYYYYMMMMMMMMMMMMMMMSSSSSSSSSSEEEEEEEEQQQQQQ",
    "JJJJBBBBBQQQQQPPUHHWUUUUUUUUUUPPPPCCCCCCCCCFFUUEUUMUQGGGGGGEEEKKKZRRRRRRRR"
    "RRRHDDHDDDTTBTTTTTTTYYYYYYYYMMMMMMMMMMMMSSSSSSSSSSSEEEEEEEEEEQQQQQ",
    "JJHBBBBBQQQQQPPPPHHWWUUUUUUUUPPPPPCCCCCCCCCCAUUEUUUUQGGGGGGEKKKKPRRRRRRRRR"
    "RRRHHHHHDTTTTTNTTTTTTTXYYAAYYMMMMMMMMMMMGGSGGGOOOSOOOEEEEEEEEEQQQQ",
    "JHHHBBBBQQQQQPPPPHHWWUUUWWWUPPPPPPPPCCCCCCAAAAAEEEUUUGGGGGGCKKKKKKKRRRRRRR"
    "RRRHHHHHDTWWTTNNNTTTXXXYAAAAMMMMMMMMMMMGGGGGGJOOOOOOEEEEEEEEEEQQQE",
    "HHHHBBBUQQQQQPPPPWHWWWUWWWWUPPPPPPPPPPCCCCAAAAAEEEEEEGGGGGGCKKKKKKKRRRRRRR"
    "RRGGHHHHHHWWNNNNNNTXXXXXXAAAAAMMMMMMMMGGGGGGJJOOOOOOEEEEEEEEEEEQEE",
    "HHHHHBBBBQQQPPPPWWWWWWWWWWWWWPPPPPPPPPCCCAAAAAEEEEEECCCCCCCCKKKUKKRRRRRRRR"
    "RRRGHHHHHWWDDDNNNNTTXNNNNVAAAAAMWMMMMMGGGGGGJJOOOODEEEEEEEEEEEEEEE",
    "HHHHHHHHUQQUPPPPWWBWWWWWWWWWWPPPPPPPPPCCAAAAAAAEEEEECCCCCCCCCKKKKRRRRRRRRE"
    "KKKKKDHHHWDDDDNNNNNNNNNNNNNAAAAAMMMMPMMEGGGEOOOOOOEEEEEEEEEEEEEEEE",
    "HHHHUHHHUQQUUPPPSUUWWWWWWWWWWPPPPPPPPPPCJPBAATTTTTEEEERRCCCCRRKKKKRRRRRRRR"
    "KKKKKKNHHWDDDDDNNNNNNNNFFNNAAAAAAAAMPMEEGGGEOOOOOOVVVEEEEEEEEEEEEE",
    "HHHHUUUUUUUUUUVVUUWWWWWWWWWWWPPPPPPPPPPPPPAATTTTTTEEEERRUCCCCRKKKKKKRRRKKK"
    "KKKDDJDDDWDDDDDNNNNNNNNNNNAAAAAAAAAMMAEEEGGEEOOOOOOVVSESSSSEEEEEEE",
    "HHHHHUUUUUUUUUUUUUWWWWWWWWWWWPPPPPLTTPPPPPPTTTTTTTTTEERRRCCCCRRKKKKKRRKKKK"
    "KKKDDDDDDDDDDDDDDNNNNNNNNNAAAAAAAAMMAAEEEEGEEEEEOOVVSSSSSSSEEEEEEE",
    "HHHHHHHHHUUUUUUUUUWWWWWWWWWWLLLLLLLTTPPPPPPTTTTTTTTTEERRPCERRRRRKKKKKKKKKK"
    "KMKLDDDEDDDBBBBBBBNNNNNNNNNAAAAAAAAAAAAAEEEEEEEEOOVVSSSSSSSSSSEGGE",
    "HHHHHHHUUUUUUUUUXUWWWWWWWWWWLLLLLLLTTTPPPTTTTTTTTTTTERRRRRRRRRRRRKKKKKKKKM"
    "KMLLLDDDDDDBBBBBBBNNNNNNANAAAAAAAAAAAAAAEEEEEEEEEESSFSSSSSSSSSESGG",
    "HHHHHHHUUUUUUUUXXXXWWWWWWLLLLLLLLLTTTTTTTTQTTTTTTTTTTRRRRRRRRRRRKKMMKKKKKM"
    "MMMMLLDDDDDBBBBBBBNNNNNNNAAAAAAAAAAAAAAAKKEEEEEEEESSSSSSSSSSSSSSGG",
    "HHHHHUUUUUUUUUUXXXXXWWWXLLLLLLLLLLTTTTTQQQQTTTTTTTTTTTRRRRRRRRRRRKMMMKKKKM"
    "MMMMMDDDDDDBBBBBBBNNNNNNNNNAAAAAAAAAKKKKKKEEEEEEEEESSSSSSSSSQSNQGG",
    "HHHKKUUUUKUUUWWXXXXXXXXXLLLLLLLLLLQQQTTQQHQTQQQTTTTTTRRRRRRRRRRRRMMMMKKKKM"
    "MMMMMDDDDDDBBBBBBBDNNNNNNNBBBBBBBAAAAKKKKKKKEEEEEEEESSSSSSSSQQQQGG",
    "HHHHKKLKAKKUWWWXXXXXXXXXLLLLLLLLLLQQQTTQQHQQQQTTTTTTTRRRRRRRRRRRRMMMMMKMMM"
    "MMMMMQQDDDDBBBBBBBNNNNNNNNBBBBBBBAAAAKKKKKKEEEEEEEESSSSSSSSSQGQQGG",
    "HHHHHKKKKKKUWWWWWXXXXXXXXLLLLLLLLLQVQQQQQQQQQQQTTTTTRRRRRRRRRRRNNMMMMMMMMM"
    "MMMMMQQZDDDBBBBBBBBBBBBBNABBBBBBBAAAAKKKKKKEEEEEENEESSSSSSQSQQQQGQ",
    "HHHHKKKKKKKRWWWWWWXXXXXXXLLLLLLIILIQQQQQQQQQQQQQTTTTRRRRRRRRRRRNMMMMMMMMMM"
    "MMMMMQQZDDDBBBBBBBBBBBBBBBBBBBBBBAAAAKKKKKKEEEENNNNSSSSSSSQQQQQQQQ",
    "HMHHKKKKKKKRWWWWWXXXXXXXXLLLLLLIIIIQQQQQQQQQQQQQTTTRRRGRRRRRRRRNMMMMMMMMMM"
    "MMMMZQZZDDDBBBBBBBBBBBBBBBBBBBBBBAAAAAAKKKKEEENNNNNSSSNSSSQQQQQQQQ",
    "MMKKKKKKKKKWWWWWWXXXXXXXXLLLLLLLLIIIQQQQQQQQQQQQQQTRRRRKKRRRRRNNMMMMMMMMMM"
    "MMBBZZZZZZDBBBBBBBBBBBBBBBBBBBBBBAAIIAKKKKKKKENNNNNNNSNSSUUQQQQQQQ",
    "NMMMMKKKKKKWWWWWWWXXXXXLLLLLLLLLLLLIIQQQQQQQQQQQQEEERRIIKRRRRNNNMMMMMMMMMM"
    "MMMBZZZZZZZBBBBBBBBBBBBBBBBBBBBBBNIIIKKKKKKKKKKNNNNNNNNSUUQVQQQQQQ",
    "MMMKKKKKKKKWWWWWWXXXXXXXXRRRRJXXXLIIQQAQQQQQQQQQQEEEEEIIIIINNNNNNMMMMMMMMM"
    "MMBBZZZZZZZDSSBBBBBBBBBBBBBBBNNNEEIIIKKKKKIKKNNNNNNNNNNNQQQQQQQQQQ",
    "MFMIFFKKKKKKWWWWWWXXXXXXRRRRJJJXXQQQQQQQQQQQQQQQQEEEEEEEIINNNNNNNNNNMMMMMM"
    "MBBBBBZZZZZDZZBBBBBBBBBBBBBBBNNNIIIIIKKKIKIINNNNNNNNNNNQQQQQQQQQQQ",
    "FFBIFFFKKKKKWWWWWWXXXXXXWWRRRJJXXXXQQQQQQQQQQQQQQEEEEEIIIINNNNNNNNNNNMMMMM"
    "MMBBBCBZZZZZZZBBBBBBBBBBBNNNNNNIIIIIIIIIIIIINNNNNNNNNNNNNQQQQQQQQQ",
    "FFBBBFFFFKKKYWWWXXXXXXVWWWRRRJXXXXXXXQQQQIQQQUQQUUEUEEIIIIIIINNINNNNMMMMMB"
    "BBBBBBBBZZZZZZZZBBBBBBBBBIINNNNIIIIIIIIIIIIIIINNNNNNNNNNNNNHQQQQQQ",
    "FBBBBFFFFFFFFWWWXXXXXXXWWWRWWXXXXXXDDPPPQQUUUUUQUUUUIIIIIIIIIIIINNNNMMMMMB"
    "BBBBBBBBZZZZZZZZBBBBBBBBBINNNNNIIIEIIIIIIIIIIIINNNNNWNNNNNNHQZQQQQ",
    "BBBBBFFFFFFFEEEQXXXXXXXXWWWWWXWXXXXDDPPZZUUUUUUUUUUUIIIIIIIIIIIINNNNNNMBBB"
    "BBBBBBBBBZZZZZZZBBBBBBBBBIIIIEEEEEEIIIIIIIIIIIWWWWWUWWNWNNNNQZZDDD",
    "BBBBBFFFFFEEEEEQXNNXXXWWWWWWWWWWXDDDDQQUUUUUUUUUUUHBIIIIIIIIIIIBNNNNNNBBBB"
    "BBBBBBBBZZZZZZZZBBBBBBBBBIIIIIEEEEEIIIIIIIIIIIWWWWUWWWWWNNNNNZDDDD",
    "BBBBBBFFFFFEEEEEENNNNWWWWWXXXXXXXXXXDDDDDDDUUUUUUBBBIIIIIIIIIIIBNNNNNBBBBB"
    "BBBBBBBDBBZZZZZZBBBBBBBBBIIIIEEEEEEEEEIIIIIIIWWWWWWWWWWWNNNZZZDDDD",
    "BBBBBBBEFFFEEEEEENENNNWWWWXXXXXXXXXXDDDDDDDDUUUUBBBBBIIIIIIIILBBBNBNNNNBBB"
    "BBBBBBBBBZZZZZZZBBBBBIIIIIIEEEEEEEEEEEIIIIIIIWWWWWWWWWWWZZZZZZDDDD",
    "BBBBBBEEEYEEEEEELEEENNWWWWXXXXXXXXXXDDDDDDUUUUUUUBBBBIIIIIIIIIBBBBBBBBBBBB"
    "BBBBBBBBBBZZZZZZHHHUUUIIIIIENEEEEEEEEEIIIIMMMWWWWWWWWWWWZZZZZZZZDD",
    "BBBBBBBEEEEEEEEEEEEENWWWWWXXXXXXXXXXDDDDDDDUUUUUUBBBBIIIIIEIIBBBBBBBTTBBBB"
    "BBBBBBBBBZZZZZZZHUUUUUUUIIEEEEEEEEEEEEEMMMMMMMWWWWXXXXXWZZIJZZZZDZ",
    "BBBBBBBBBEEEEEEEEEEEELXXXXXXXXXXXXXXDDDDDDUUUUUUUBTUBIIIIIIIBBBBBBBBTBBBBB"
    "BBBBBBBBZZZZZZZZUUUUUUUUIIIELEEEEEEEEEEMMMLWWMWXXXXXXXXXZIIIIIZZDZ",
    "BBBBBBBBBEEEEEEEEEEEEEXXXXXXXXXXXXXXDRRDZAUUUUUUUUUUUNNNNIMBBBBBBBBBBBBBBB"
    "BBBBBOOBZZZZZZZZZUUUUUUUUUEEEEEEEEEEEEEMMMLLWWWXXXXXXXXXZIIPIZZZZZ",
    "BBBBBBBBBBEEEEEEEEEEEWXXXXXXXXXXXXXXDRRDAAAUUUUUUUUMMMNMNNMBBBBBBBBBBBRNBB"
    "BBBVNOZZZZZZZZUUUUUUUUUUUUUEEEEEEEELELLMMLLLWWWXXXXXXXXXZIIIIIIZZZ",
    "BBBBBBLLLLLLEEEEEEEEEEXXXXXXXXXXXXXXWVVAAARAUUUUUUUMMMMMMMMBBBBBBBBBBBRNNB"
    "BNNNNOOZZZNNZUUUUUUUUUUUUUUUUEEEEEELLLLMLLLLWWWXXXXXXXXXZIIIIIIZZZ",
    "BBBBBBLLLLLLEEEEEEEEEEXXXXXXXXXXXXXXWVVAAAAAAUUUUUUMMMMMMMMBBBBBBBBBBRRNNN"
    "NNNNNOONZZNNZUUUUUUUUUUUUUZEEEEEEEELLLLLLLLVWWWXXXXXXXXXIIIIIIIIIZ",
    "BBBBBBLLLLLLLLXXEEEVEKXXXXXXXXXXXXXXWVVVVVVAAAAUUUUMMMMMMMMBBMBBBBBBBBRNNN"
    "NNNNNNNNNNNUUUUUUUUUUUUUUUEEEEEEEEELLLLLLLLLLLWXXXXXXXXXIIIJZZZZZZ",
    "BBBBBBLLLLLLLGLLEEEEEKXXXXXZZZZZZZWWVVVVVVVVVUUUUUMMMMMMMMMMMMBBBBBBBBNNNN"
    "NNNNNNINNNNUUUUUUUUUUUUUUJEEEEEEEELLLLLLLLLLLWWXXXXXXXXXJJJJJJJZZZ",
    "BBBBBBLLLLLLLLLLLLLLLLXXXXXXXXXXXXXWVVVVVVVVVUUUUUMMMMMMMMMMMMBBBBBBBBBNNN"
    "NNNNNNNNNNNUUUUUUUUUUUUVVICCELEEEELLLLLLLLLLDDWXXXXXXXXXWWJJJJZZZZ",
    "BLLLLLLLOOOLLLLLLLLLLLXXXXXXXXXXXXXWVVVVVVVVVVURRUFRMMMMMMMMMBBBBBBBBNNNNN"
    "NVKKNNNNNNNNNNNUUUUIVVVVVICCCEEEEELLLLLLLLLDDDDXXXXXXXXXJJJJJJJZZZ",
    "BLLLLLLLOOOLLLLLLLLLLLCZZZXXXXXXXXXZVVVVVVVVVVRRRRRRRRMMMMMMMIIIBBBBBBBBVV"
    "VVVKYNNNNNNNNNNNUIIIIVVVIIIIEEEEELLLLLLLLLLDDDDDDXXXJJJJJJJJJJJZZZ",
    "BLLLLLLLOOOLLLLLLLLLLLLLZZXXXXXXXXXZVVVVVVVVVRRRRRRRRRRRTTTIIIIIIIBBBYYVFV"
    "VVVVYYNNNNNNNINNNIIIIVVIIIIEEEEEEEELVLLLLGLLDDDDDXXXJJJJJJJJJJJJJZ",
    "LLLLLLLLOOOLLLLLLLLLLLLNZZXXXXXXXXXZVVVVVVVVRRRRRRRRRRRRRRRNIIIIIBBBBYYVVV"
    "VVYYYYYYNNNNNIIIBIIIIVIIIIIBEEEDDKELVVDLLLLDDDDDDDDDJJJJJJJJJJJJJZ",
    "LLLLLLLLOOOLLLLLLLLLLALNZZXXXXXXXXXZVVVVVVVVKRRRRRRRRRRRRRRRRIIIIBBBBBYYYY"
    "VVYYYYYYNNNIIDIIIIIIIIIIIIIIDREDVDEVVVDLLDLDDDDDDDDJJJJJJJJJJJJJJJ",
    "LLLLLLLLOOOLLLLBBBLLAAZZZZZZZZZZZZZMVVVVVVVRRRRRRRRRRRRRRXRRIIIIIIIIBYYYYY"
    "VVYYYYYYNNNIIIIIIIIIIIIIIIIIDDDDDDDVVDDDDDDDDDDDQDDDJJJJJJJJJJTJJC",
    "LLLLLLLLOOOLLLBBBBLLLAAAAAMZZZZMZZMMMVVVVVVRCCCRRRRRRRRRRRRRIIIIIKKYYYYYYY"
    "YYYYYYYYYYNNIIIIIIIIIIIIIIIIDDDDDDDVDDDDDDDDDDDQQDDDJJJJJJJJJTTTJC",
    "LLLLLLLLOOOLLLLBBBLQLAAAAAMMMZZMZMMMVVVVVVVRCCCCCRRRRRRIIIRRRIIIIKKYYYYYYY"
    "YYYYYYYYYYYIIIIIIIIIIIIIIISIDDDDDDDVVDDDDDDDDDQQQDQQGJJJJJJJJGGGCC",
    "LLLLLLLLOOOLLLBBBBBBAAAAAAMMMMMMMMMMMVVVVVVCCCCCCRRRRRRIIIIIIIIIIIKYYYYYYY"
    "YYYYYYYYOOOIIIIIIIIIIIIIIIGIDDDDDDDDDDDDWWQQQQQQQQQQGJTJJWWWWGGGCC",
    "LLLLLLLLOOOLLLBBBBBBAAAAAAAMMMMMMMMMXXVVVVVCCCCCCCEEERJJJIIIIIIIIKKKKYYYYY"
    "YYYYYIIIIIIIIIIIIIIIIIIIIGGGDDDDDDDDDDIWWGQQQQQQQQTTJJTTGGGGWGGGGC",
    "TLLLLLLLLLLLLLBBBBBBBAAAAAAMMMMMMMMXXXVVXVVCCCCCCCEEEEAAAAAIIIIIIKKKKYYYYY"
    "YYYYYIIIIIIIGIIIIIIIIIIFGGGGDDDDDDDSDWWWGGQQQQQQQQTTTTTGGGGGGGGCCC",
    "TLLLLLLLLLLLLLCBBBBBBBACAAAMMMMMMMMXXXXXXXCCCCCCCCEEECAUUUUUUIIIIKKKYYYYYY"
    "YYYIIIIIIIIIGIIIIIIFFFFFGGGGDDDDDDSSSSWWWGGQQQQQQQTTTTGGGGGGGGGCCC",
    "ZLLLLLLEELLLLLBBBBBBBUCCCMMMMMMMMMMMXXXXXCCCCIIIIIIIIIIUUUUUUHIIKKKKYYYYYY"
    "YYYYGXIIIIIIGIIIIIIGGFFFGGGGGDDDDDSSSSSGGGGGQQQQQTTTTGGGGGGGGCCCCC",
    "ZZLLLZZLLLLLLLBBBSBBBBBCMMMMMMMMMMXXXXXXXXCCCIIIIIIIIIIUUUUUUHIIIIKKJYYYYY"
    "YYYGGGIIIIIGGGGIIIQGGFGGGGGGGSSSSSSSSSSSSGGQQQQQTTQTTTTGGGGGGCCCCC",
    "ZZZEZZZZZLLRLLCCKCBBCCCCMMMMMMMMMMMXXXXXXXCCCIIIIIIIIIIUUUUUUHHHIIKKJYYYGG"
    "AGGGGGGFGIWGGGGIIGGGGGSSSSSSSSSSSSSSSSSSGGGQQQQQQQQQTTGGGGGGGCCCCC",
    "ZZZZZZZZZZLLLLSCCCCCCCCCCMNNMMMMMEEXXXXXXXXCCIIIIIIIIIIUUUUUUHQHHHJJJJJYGG"
    "GGGGGGGFGGGGGGGGGGGGGGSSSSSSSSSSSSSSSSSWWWGWQQQQQQQQQTGGGGGGCCCCCC",
    "ZZZZZZZZSSLLLSSSCCCCCCCCMMNMMMMMMMMXXXXXXCCCTIIIIIIIIIIUUUUUUHQHHJJJJJJGGG"
    "GGGGGGGGGGGGGGGGGGGGGGSSSSSSSSSSSSSWWWWWWWWWQWQQQQWQTTGGGGGGGGCCCC",
    "ZZZZZZZZSSSSSSSSSCCCCCMMMMMMMMMMMMMXXXXXXCXXCIIIIIIIIIIQQQQQQQQQAJJJJJJJJJ"
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGSSSSSSSSWWWWWWWWWWQWWWQQGGGGGGGGGCCCC",
    "ZZZZZZZSSSSSSSSSSCCCCCMMMMMMMMMMMMMXXXXXXXXXXIIIIIIIIIIIIQQQQQQAAEAJJJJJJJ"
    "GGGGGGGGGGGGGGGGGGGGGGGGGGDDDSSSSSSSSWWWWWWWWWWWWQQQQQGOGGGGGGCCQC",
    "ZZZZZZZZSTTTSSSSSCCCCCCCMMMMMMMMMMXXXXXXXXXXXXXWWIIIWAIIIQQAPQQAAAAAJJJJGG"
    "GGGGMGGGGGGGGGGGGGGGGGGGGGDDDDSSSSSSSAWHWHWWWWWWWQQQQQGGGQQGGGGCQQ",
    "ZZZZZZZZZTTTSSSTSSCCHCCMMMMMMEMMMAXXXXXXXXXXXXWWWIIIIIIIIIAAPPPAAAAAJJJMGG"
    "GGGGMMMGGGGGGGGGBBGGGEGGGGDDBDSSSSSSSHHHHHWWWWYWWQQQQQQQQQQQQGQQQQ",
    "ZZZZZZZOZTTTTTTTTSCCHCHMMMEEEEEMAAXXXXXXXXXXXXWIIIIIIIIIIIAUAPAAAAAAJJJMGG"
    "GMMGMMMGGGGGGGGGGGGGEEGGGGSSSSSSSSSSSHHHHHWWWYYQQQQQQQQQQQQQQQQQQX",
    "ZZZZZZZOZZTTTTTTTTTHHHHHMEEEEEEEEAAXXGXJXXXXXXWIIIIIIIIIIIAAAAAAAAAAAMMMMM"
    "MMMMMMGGGGGGGGGGGGGWEEEEEESSSSSSSSSSSHHHHHHHWHHHHQQQQQQQQQQQQQQQQQ",
    "ZZZZZOOOTTTTTTTTTTTTTTEHEEEEEEEEAAXXXXXJXCXXXIIIIIIIIIIIIIAAAAAAAAAAMMMMMM"
    "MMMMMMGGGGGGGGGGGGGWEEEEEESSSSSSSSSSSHHHHHHHHHHHHQQQQQQQQQQQQQQQQQ",
    "ZZZZZOOOTTTTTTTTTTTTTTEEEEEEEEEEEAXXAAAJACCCCIIIIIIIIIIIIIAAAAAAAAAAAAMMMM"
    "MMMMMMMMMGGGGGGGGGGEEEEEEESSSSSSSSSSSHHHHHHHHHHHHQKKQQQQQQQQQQQQQQ",
    "OOOOOOOOOOTTTTTTTTTTTUUESSSSSSSEAAAAAAAAACCCCIIIIIIIIIIIIIFAAAAAAAAAAAMMMM"
    "MMMMMMMGGGGGGUGGGEGEEEEEEESSSSSSSSHHHHHHHHHHHHHHHHKKKKQQQQQQQQQQQQ",
    "OOOOOOOOOOTTTTTTTTTTUUUESSSSSSSEAAAAAAAAACCCCIIIIIIIIIIIIIAAAAAAAAAAAMMMMM"
    "MMMMMMMMGGGGGGGEEEEEEEEEEESSSSSSSSXXHHHHHHHHHHHHHHKKKQQQQQQQQHQQQQ",
    "OOOOOOOOOOOTTTTTTTTTCCCESSSSSSSZEAAAAAAAEEECCSIIIIIIIIIISSAAAAAAAAAAMMMMMM"
    "MMMMMMMMGGGGOOEEEEEEEEEEEESSSSSSSSXXXHHHHHHHHHQHHHHKNPPIQQQQQHQHHH",
    "OOOOOOOOOOTTTTTTTTTTCCCCSSSSSSSEEEAAAACEEEESSSIIIIIIIIIISSAAAMMAAAAAMMMMMM"
    "MMMMMMMMXXGGJEEEEEEEEEEEXBSSSSSSSSXXXXHHHHHHHQQHHKKKNNPIIIQIIHHHHH",
    "OOOYYYYYOOTTTTTTTTTTBCCCSSSSSSSEHHHAAAEEEEESSSIIIIIIIIIITGGAMMMAAAMMMMMMMM"
    "MMMMVVVMXXXJJJJEEEEEEEEEXXSSSSSSSSXXXXXHHHHHHHHHKKKKKNNIIIIIIHHHHH",
    "OOYYYYYYOTTTTTTTTTUTCCCCSSSSSSSEHHHAAAEEEEEESSIIIIIIIIIITGGAMMMAAAAAMDMMMM"
    "MMMMVVXXXXXJJJJEEEEERRREXXSSSSSSSSXXXXXHHTHTKKHHKKKKKNNTIIIIIHHHHH",
    "OOYYYYYYOYTTTTTTTCUCCCCCSSSSSSSYYHIIIIIEEEEESSIIIIIIIIIITTTTMMMMAAADDDDMMM"
    "MMMMVVVVXXXJJJJJEEEERRRXXXBBBXXXXXXXXXHHHTTTTKKKKKKKNNNTIIIIIIHHHH",
    "YYYYYYYYYYTTTTTTTCCCCCCCSSSSSSSYYHIIIIIIEEEEESSSSSSSSSTTTTTJTYYYAADDDDDDVV"
    "MVVVVVVVJJJJJJJJEEEEERRXXXBBXXXXXXXXXXGGGTTTTTKKKNNNNNIIIIIIIIIHHH",
    "YYYYYYYYYYYYTTTYYYCCCCCCSSSSSSSSSPIIIIIEEEEEESSSSSSSTSTTTTTTTTYYYADDDDDDVV"
    "VVVVVVVVJJJJJJJJEEEERRRXXXXXXXXXXXVXVVVVGTTTUTKNNNNNNNIIIIIIIIIHHH",
    "YYYYYYYYIIYYYYYYYCCCCCCCCCSSSSSSSIIIIIIIEEEEEEESSSSSTTTTTTTTTTTYYYDDDDDDVV"
    "VVVVVVVVVVVJJJJJEEERRRRRRXXXXXXXXXVVVVVGGTTTTMNNNNNNNNIIIIIIIIIHHH",
    "YYYYYYYYHHHHHHYYYYCCCCCCCCSSSSSSSIIIIIIEEEEESESSSSSSTJTTTTTTTTYYYYYDDDDDDV"
    "VVVVVVVVVJJJJJJJEEERRRRRRRRXXXXXXXVVVVVVVVATTNNNNNNNNNIIIIIIIIHHHH",
    "YYYYYYYYYHHHHHHYYYCCCCCCCCSSSSSSSIIIIIGEEEEESSSSSSSSSYTTYTYYYYYYYYYDDDDDDD"
    "DVVVVVVVVJVVVVJEEERRRRRRRRRXRRXXXXVVVVVVVVAAAANNNNNNNNNIIIIIIIIHHH",
    "YYYYYYYDYHHHHHYYYYCCCCCCCCSSSSSSSIIIGGGEEEEEESSSSSSSSYYYYYYYYYDDDYYYDDDDSD"
    "DDVVVVVVVVVVVVVEEERRRRRRRRRRRRXXXXVVVVVVVVAAAANNNNNNNNNNIIIIUUIIHH",
    "YYYYYYYYHHHHHYYYYYCCCCCCCCSSSSSSSIIIIIIIPEEEEESSSSSYYYYYYYYYYYDDDDSSDSSSSV"
    "VVVVVVVVVVVVVVEEEERRRRRRRRRREEXXXVVNVVVVVVAAAANNNNNNNNNNIIIUUUUUHH",
    "SYSSSSYYHHHHHHYYYYCCCYCHCCSSSSSSSSSSSIHPPEEEEEEESSSYYYYYYYYDDYDDDDSSSSSSSS"
    "SVVVVVVVVVVVMMMMMMKMRRRRRRRRTEXXXXTVVVVVVAAAAAANNNNNNNNNNUIUUUUUUH",
    "SYSSSSYYHHHHHHYYYYYYCYIHHCSSSSSSSSSSSHHHHEEEEEESSSSAYYYYYYYDDDDDDDFSSSSSSS"
    "SSVVVVSVVMMMMMMMMMKMMRRRRRRTTEETTTTTTVVVAAAAAAANNNNNNNNNNUUUUUUUUU",
    "SSSSSSSSSHHHHHYYYYYYYYYHHHHSSSSSSSSSSHHHHEEEEEEAASSSHYYYYYYDDDDDFFFSSSSSSS"
    "SSSVVVSVVMMMMMMMMMMMMRTRRRRTTTTTTTTTTVAAAAAAAAANNNNNNNNNNUUUUUUUMU",
    "SSSSSSSHHHHHHHHHYYYYYYYYHHHSSSSHHIIIHHHHEEEEEAAAAASHHHHSYYYDDDFFFFSSSSSSSS"
    "SSSSSSSVVMMMMMMMMMMMAATRRRTTTTTTTTTTUVAAAAAAAANNNNNNNNNNNUUUUUUUUF",
    "SSASSSSSSHHHNHHHZZJJYTYHHHHHHHHHHHIIHHHHHHEEEAAAAAAATHXXXYYADDFFFFSSRSSSSS"
    "SSSSSSVVVMMMMMMMMMMMAATTTTTTTTTTTTTTTAAAAAAAAAAUNNNNNUNUUUUUUUBBBF",
    "SSASSSSSSHHHHJHZZJJJYYYHHHHHHHHHHHHHHHHHHHGEEAAAAAAAAXXXXYYAAAAAAAASASSSSS"
    "SSSSSSSSVVMMMMMMMMMAATTTTTTTTTTTTTTTAAAAAAAAAAUUNNUNUUUUUUUUUBBBBB",
    "SAAAASSSSBHHVJHHJJJJYYHHHHHHHYYHHHHHHHHHHHGAAAAAAAAAAXXXXXYYAAAAAAAAAAASSS"
    "SSSSSSVVVMMMMMMMMMMAATTTTDTTTTTTTTTTTAAAAAAAAAUUUUUNUUUUUUUUBBBBBB",
    "SAAAAASBBBBJJJJHJJJJYYHHHHHHYYYYYHHHHHHHHAAAAAAAAAAAAXKXXXIRAAAAAAAAASSSSS"
    "GASSSSVVVTMMMMMMMMAAAATTMDTTTTTTTXZTTAAAAAAVAAVVUUUUUXUXUUUUUHHBBH",
    "AAAAAASSSBJJJJJJJJJHHHHHHHHYYYYYYYYYHHHHHAAAAAAAAAAAAXXXNIIRRAAAAAAAAAAAAS"
    "SAASSSSVTTMSMMMMMMMAAATTMMMMTTTXTXXTXAAAAAAVVVVEUUUUUXXXUUUUUUHHHH",
    "AAAAAJRJJJJJJJJJJJJHHHHHHHYYYYYYYYYYHHHHHAAAAAAAAAAAAJIIIIIRAAAAAAAAAAAAAA"
    "SAAATSRVTTMMMMMMMXXXAAATPMMMKXXXXXXXXXAAAAAVVVVUUUUUXXXXXXXUUUHHHH",
    "AAAAARRTTJAAJJJJJJJJHHHHHHHYYYYYYYYYHHHAAAAAAAAAAAAAAJIIIIIIIIIAAAAAAAAAAA"
    "AAATTTVVTTMMMGMZZXXXXAAMMMMXXXXXXXXXXXAAAVVVVVVUUUUXXXXXXXXXHHHHHH",
    "AAAAARRRJJAJJJJJJJJJHHHUUUUUYYYYYYYYYYEAAAAAAAAAAAAAAAYYIIIIIIIIAAAAAAAAAA"
    "AAAATTTTTTWMMMMZZXXXAAAAMMMXXXXXXXXXXXAAAVVVVVVUVVUXXXXXXXXXXHHHHH",
    "AAAAAAARJAAJJJJJJJJJMPPUUUUUYYYYYYYYYYAAAAAAAAAAAAAAAAAAIIIIIIIAAAAAAAAAAA"
    "AAAATTTTTWWDDDMXXXXXXXAAAXXXXXXXXXXXXXAAVVVVVVVVVVUXXXXXXXXHHHHHHH",
    "AAAAAARRRAAAJJJJJJJJPPPUUUUUYYYYYYYYYYAANNAAAAAAAAAAAIAIIIIIIIIAAISAIIIAAA"
    "ATAATWWTWWWWDDXXXXXXXXXXXXXXXXXXXXXKKKAAVVVVVVVVVVUXXXXXXXXHHHHHHH",
    "AAAAAGGRRAAAAAJJPPPJJPPUUUUUYYYYYYYYYYYOOOOROSSAAAIAAIIIIIIIIFIIAIIIIIIAAO"
    "OOAATTWWWWWWWXXXXXXXXXXXXXXXXXXXXXXXKAAKVVVVVVVVVVVTXXXXXIIXXHHHHH",
    "AAAAAGGGRRRAAAAAAPPPPPPPPPYYYYYYYYYYYYOOOOOOOSSSSAGGGGGIIIIIFFIIIIIIIIAAOO"
    "OOOOTTWWWWWWWXXXXXXXXXXXXXXXXXXXXXXXKKKKKKVVVVVVVVVVXXXXXXXEXXHHHH",
    "AAAAAGGARAAAAAAPPPPPPPPPPPPPYYYYYYOYYYOOOOOOOSSSSGGGGGIIIIIIIFIIIIIIIIAAOO"
    "OOOOOOWWWWWWIIXHXXXXXXXXXXXXXXXXXXXXKVVVVVVVVVVVVVVVXXXXXXXEXXHHHH",
    "AAAAAGGAAAAAAAAPPPPPPPPPPPPPPPYYOOOOOYOOOOOOOOOSSGGGGGGIIIIIIIIIIIIIIIOOOO"
    "OOHHHHWWWWWWIIXHXXXXXXXXXLXXXXXXXXXXXZZVVVVVVVVVVVVVVXXXXXXXXXHHHH",
    "AAAGGGAAAAAAAAPPPPPPNNNPPPPPPPPPPOOOOOOOOOOOOOCGGGGGGGGGIIIIIIIIIIIIIIIQIO"
    "OOHHHHHWWWWWWIJHHXXXXXXXXXXXXXXXXXXHXZZVVVVVVVVVVVVVVXXXXXYYXXHHHH",
    "GAAGGGGAAAAAAAAAPJJNNNNPNPPPPPPPNOOOOOOOOOOOOOCGGGGGGGGGGGIIIIIIIIIIIIIIIO"
    "HHHHHHHWIWIIIIJHHXXXXXXXXXXXXXXXZZXXZZZVVVVVVVVVVVVVVYXYYYYYYYEEHH",
    "GGGGGGGGAAAAAAAAAJJNNNNNNPPPPPPPPOOOOOOOOOOUOOOGGGGGGGGGGINIIIIIIIIIIIIIII"
    "IHHHHHHHIIIIJJJHHXXXXXXJXXXXXXXXXZZZZZVVVVVSSSZVVZVVVYYYYYYEEEEHHH",
    "GGGGGGGGGAAAAAAAAJJNNNNNNPPPPPPPPPPOOOOOOOOUUUGGGGGGGGGGGIIIIIIIIIIIIIIIIH"
    "HHHHHHHIIIIIIJJJHXXXXXXXWXXFXXXXZZZZZZVZZVVVVVZZZZZVYYYYEYYEEAEHHH",
    "GGGGGGGGAAAAAAAAAAJNNNNNNNPNPPPPXXXOOOOOOOOOUUGGGGGGGGGGGGIIIIIIIIIIIIHHII"
    "HHHHHHHHHIIIIJJJHXXXXXXXWXFFFXXXXZZZZZZZZZZZVZZZZZZZYYYYEEEEEEHHHH",
    "GGGGGGGGGGGAAAJJJJJNNNNNNNNNPPPXXXXOOXXOOOOOGGGGGGGGGGGGGGGGIIIIIIIIIIIHHH"
    "HHHHHHHHHHHHHHHHHHXXXXXXXXXFFFFXXZZZZZZZZZZZZZZZZZZZZZYYEEEEEHHHHH"};

decltype(input_real) input_test1{"EEEEE", "EXXXX", "EEEEE", "EXXXX", "EEEEE"};

decltype(input_real) input_test2{"AAAAAA", "AAABBA", "AAABBA",
                                 "ABBAAA", "ABBAAA", "AAAAAA"};
// auto &input = input_test1;
auto &input = input_real;

struct Garden {
  char id;
  std::set<std::tuple<ll, ll>> surface;
  ll perimeter = 0;
  ll sides = 0;
};

static constexpr std::tuple<ll, ll> DIFF[]{{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
void flood(ll x, ll y, char id, std::set<std::tuple<ll, ll>> &surface) {
  surface.insert(std::tie(x, y));
  input.at(y).at(x) = '%';

  for (auto [dx, dy] : DIFF) {
    auto next = std::make_tuple(x + dx, y + dy);
    auto [next_x, next_y] = next;
    if (next_y < 0 || next_y >= input.size()) {
      continue;
    }
    if (next_x < 0 || next_x >= input.at(next_y).size()) {
      continue;
    }
    auto next_id = input.at(next_y).at(next_x);
    if (next_id != id) {
      continue;
    }
    auto [it, inserted] = surface.insert(next);
    if (!inserted) {
      continue;
    }
    flood(next_x, next_y, id, surface);
  }
}

ll permimiter() {
  ll permimiter = 0;
  for (ll j = 0; j < input.size(); j++) {
    for (ll i = 0; i < input.at(j).size(); i++) {
      auto c = input.at(j).at(i);
      if (c == '%') {
        for (auto [dx, dy] : DIFF) {
          auto next = std::make_tuple(i + dx, j + dy);
          auto [next_x, next_y] = next;

          if (next_y < 0 || next_y >= input.size()) {
            permimiter++;
            continue;
          }
          if (next_x < 0 || next_x >= input.at(next_y).size()) {
            permimiter++;
            continue;
          }
          auto neighbour = input.at(next_y).at(next_x);
          if (neighbour != '%') {
            permimiter++;
          }
        }
      }
    }
  }
  return permimiter;
}

ll sides_h() {
  auto side_to_the_top = [](ll x, ll y) {
    if (input.at(y).at(x) == '%') {
      if (y == 0) {
        return true;
      }
      return input.at(y - 1).at(x) != '%';
    }
    return false;
  };
  auto side_to_the_bottom = [](ll x, ll y) {
    if (input.at(y).at(x) == '%') {
      if (y == input.size() - 1) {
        return true;
      }
      return input.at(y + 1).at(x) != '%';
    }
    return false;
  };

  std::function<bool(ll, ll)> predicate[]{side_to_the_top, side_to_the_bottom};
  bool predicate_continues[]{false, false};

  ll result = 0;
  for (ll j = 0; j < input.size(); j++) {
    for (ll i = 0; i < input.at(j).size(); i++) {
      for (ll p = 0; p < 2; p++) {
        if (predicate[p](i, j)) {
          if (!predicate_continues[p]) {
            result++;
            predicate_continues[p] = true;
          }
        } else {
          predicate_continues[p] = false;
        }
      }
    }
  }
  return result;
}

ll sides_v() {
  auto side_to_the_left = [](ll x, ll y) {
    if (input.at(y).at(x) == '%') {
      if (x == 0) {
        return true;
      }
      return input.at(y).at(x - 1) != '%';
    }
    return false;
  };
  auto side_to_the_right = [](ll x, ll y) {
    if (input.at(y).at(x) == '%') {
      if (x == input.size() - 1) {
        return true;
      }
      return input.at(y).at(x + 1) != '%';
    }
    return false;
  };

  std::function<bool(ll, ll)> predicate[]{side_to_the_left, side_to_the_right};
  bool predicate_continues[]{false, false};

  ll result = 0;

  for (ll i = 0; i < input.at(0).size(); i++) {
    for (ll j = 0; j < input.size(); j++) {

      for (ll p = 0; p < 2; p++) {
        if (predicate[p](i, j)) {
          if (!predicate_continues[p]) {
            result++;
            predicate_continues[p] = true;
          }
        } else {
          predicate_continues[p] = false;
        }
      }
    }
  }
  return result;
}

void erase_garden() {
  for (ll j = 0; j < input.size(); j++) {
    for (ll i = 0; i < input.at(j).size(); i++) {
      auto &c = input.at(j).at(i);
      if (c == '%') {
        c = '$';
      }
    }
  }
}

std::vector<Garden> scan() {
  std::vector<Garden> result;
  for (ll j = 0; j < input.size(); j++) {
    for (ll i = 0; i < input.size(); i++) {
      auto c = input.at(j).at(i);
      if (c != '$' && c != '%') {
        Garden g;
        g.id = c;
        flood(i, j, c, g.surface);
        g.perimeter = permimiter();
        g.sides = sides_h() + sides_v();
        erase_garden();
        result.push_back(std::move(g));
      }
    }
  }
  return result;
}

} // namespace

int main12() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  auto gardens = scan();
  for (auto &g : gardens) {
    result0 += (g.surface.size() * g.perimeter);
    result1 += (g.surface.size() * g.sides);
  }

  myprint(result0);
  myprint(result1);
  return 0;
}
