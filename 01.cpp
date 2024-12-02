#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
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

std::vector<std::pair<ll, ll>> input_real{
    {14832, 78161}, {19986, 67025}, {61574, 40916}, {87318, 29281},
    {12651, 42252}, {43238, 74483}, {13498, 83990}, {89748, 81193},
    {21897, 61695}, {56707, 55826}, {53149, 71661}, {35501, 54251},
    {35575, 64490}, {93717, 93097}, {56811, 38115}, {59171, 88932},
    {29134, 48905}, {53535, 75870}, {25373, 11975}, {20739, 87207},
    {93977, 61319}, {53691, 60995}, {85586, 34987}, {57967, 20401},
    {63728, 40714}, {55803, 75870}, {61607, 93192}, {24011, 16534},
    {35757, 74483}, {17574, 69758}, {44987, 22282}, {57097, 10690},
    {41948, 20278}, {54024, 56080}, {54629, 13483}, {77940, 40714},
    {33163, 58805}, {50446, 13861}, {12025, 81227}, {38258, 22297},
    {77220, 19329}, {31100, 89115}, {22194, 30988}, {19934, 41575},
    {39003, 85537}, {16792, 72861}, {49579, 43692}, {61354, 48837},
    {20913, 10261}, {36007, 93717}, {84109, 14234}, {86082, 51528},
    {11661, 33735}, {67997, 68007}, {13318, 12950}, {14816, 65750},
    {83826, 84782}, {41231, 55630}, {95346, 23303}, {65834, 40595},
    {82985, 90097}, {22625, 85322}, {66493, 62265}, {85912, 18719},
    {87029, 83486}, {36061, 33163}, {96931, 24737}, {73557, 84455},
    {68446, 33543}, {59231, 19946}, {98226, 92133}, {89950, 15535},
    {78504, 55536}, {89239, 75209}, {62884, 48450}, {74554, 57717},
    {10690, 81436}, {75129, 48905}, {62540, 38827}, {92470, 74483},
    {59728, 16526}, {12803, 93192}, {14168, 29281}, {16934, 99503},
    {30438, 18719}, {91948, 88932}, {31738, 63047}, {95675, 28064},
    {40399, 37524}, {47357, 98562}, {47613, 83240}, {96410, 35215},
    {89334, 60324}, {79225, 71182}, {20839, 81227}, {37606, 75870},
    {24627, 16526}, {99578, 51226}, {36756, 43692}, {66045, 68007},
    {81227, 55991}, {43775, 40714}, {32169, 48905}, {87072, 30663},
    {67785, 65822}, {62885, 33163}, {70978, 10694}, {57186, 44077},
    {95376, 37198}, {27824, 45366}, {65397, 88932}, {48595, 26943},
    {63923, 38054}, {26925, 87605}, {95813, 74483}, {61184, 70558},
    {82770, 72541}, {39915, 93192}, {70056, 75055}, {80250, 18450},
    {41945, 81896}, {59350, 14484}, {92719, 82621}, {85385, 79095},
    {16782, 16526}, {60542, 81227}, {55916, 77024}, {68128, 67126},
    {54947, 23229}, {82438, 33163}, {13341, 35215}, {55486, 17165},
    {84059, 31103}, {59138, 21897}, {77153, 22214}, {89876, 94031},
    {25474, 48905}, {17942, 76901}, {74483, 22733}, {87517, 26303},
    {19733, 52498}, {69030, 17762}, {75386, 37039}, {28497, 92368},
    {11163, 18719}, {58366, 10690}, {57571, 55792}, {19592, 94111},
    {72419, 90097}, {36566, 72102}, {40849, 14145}, {55269, 76919},
    {65509, 41575}, {60617, 12813}, {54733, 93192}, {13960, 24651},
    {27364, 51488}, {98470, 12076}, {97058, 66643}, {28064, 75197},
    {15244, 30301}, {80340, 99773}, {66546, 31526}, {52697, 90097},
    {98166, 33163}, {73975, 40714}, {68182, 83486}, {63228, 93717},
    {56573, 38011}, {28180, 25141}, {37939, 15540}, {25370, 42534},
    {64919, 27367}, {70478, 48764}, {99686, 10690}, {95464, 38313},
    {54829, 84455}, {62114, 33543}, {74213, 26980}, {54323, 70873},
    {44469, 70116}, {27175, 75870}, {76725, 84455}, {49758, 31181},
    {78293, 78013}, {81467, 31854}, {18125, 69158}, {83779, 34394},
    {35292, 16800}, {35215, 29281}, {84988, 60932}, {87195, 33543},
    {45923, 84455}, {63094, 57741}, {23139, 95712}, {45876, 81241},
    {96749, 88932}, {22373, 74916}, {26413, 33212}, {72356, 42606},
    {20886, 18726}, {60547, 65391}, {12792, 43692}, {57886, 35215},
    {53980, 21897}, {98924, 56864}, {47272, 43692}, {68066, 45803},
    {43349, 76091}, {65689, 33163}, {22894, 31947}, {31343, 91101},
    {10205, 89352}, {84491, 31662}, {56668, 29281}, {67399, 48905},
    {65864, 80667}, {58361, 93192}, {83339, 38515}, {83183, 37279},
    {60409, 26382}, {79209, 99922}, {82681, 65132}, {96686, 59412},
    {66634, 50652}, {16609, 90097}, {18724, 27556}, {79737, 72541},
    {83038, 12182}, {51288, 89941}, {46843, 86570}, {11376, 67678},
    {18179, 31761}, {51996, 48112}, {23978, 93192}, {65754, 83486},
    {91433, 81227}, {82134, 46836}, {41947, 85857}, {59248, 21897},
    {34679, 85485}, {35451, 75870}, {11471, 61908}, {84595, 16676},
    {89040, 63807}, {84288, 49492}, {27228, 44537}, {37282, 97066},
    {24651, 88489}, {80363, 33163}, {88456, 56070}, {41800, 39419},
    {25159, 48077}, {42045, 77355}, {39208, 40714}, {63685, 10690},
    {44566, 37386}, {57151, 18719}, {20402, 93192}, {12727, 99458},
    {68774, 19579}, {43074, 80902}, {84348, 43692}, {95333, 88046},
    {70982, 34034}, {38107, 46234}, {92088, 29281}, {12859, 98196},
    {55747, 15751}, {44045, 46368}, {50910, 43692}, {39677, 88932},
    {24054, 14246}, {32389, 32825}, {67135, 93192}, {85340, 71337},
    {84227, 93192}, {99218, 98368}, {44571, 41575}, {14484, 70812},
    {25893, 57615}, {10730, 35215}, {92599, 71269}, {44898, 51867},
    {14022, 41575}, {51095, 21897}, {15804, 88673}, {72933, 71550},
    {98390, 81446}, {22047, 74483}, {59037, 88932}, {41492, 14484},
    {64970, 75181}, {55231, 84455}, {69345, 93192}, {38425, 43938},
    {61882, 71269}, {56850, 69700}, {79667, 40714}, {51547, 49855},
    {11130, 71769}, {85572, 54337}, {95817, 67678}, {61823, 82300},
    {19271, 97789}, {11881, 83486}, {42887, 51582}, {27906, 34579},
    {42050, 84455}, {58219, 62934}, {47734, 84167}, {88275, 99961},
    {50696, 54181}, {39410, 64516}, {39867, 84455}, {11697, 14484},
    {37836, 59838}, {32637, 10690}, {27449, 21170}, {40912, 64785},
    {95484, 84455}, {82502, 99989}, {32254, 46908}, {75920, 67723},
    {58759, 29281}, {71237, 84690}, {58054, 43692}, {74921, 57417},
    {72191, 73258}, {20925, 56916}, {70260, 93717}, {43880, 38046},
    {75354, 88932}, {29177, 33543}, {76812, 33163}, {48520, 84455},
    {88413, 44014}, {14204, 48905}, {36006, 67255}, {59611, 51220},
    {35246, 34802}, {91384, 68007}, {52764, 90097}, {15643, 94272},
    {12252, 53212}, {42561, 97277}, {42108, 33163}, {10911, 85051},
    {91308, 29281}, {76358, 75870}, {42657, 16526}, {12071, 54325},
    {81889, 15132}, {29405, 18876}, {29837, 27476}, {76631, 93717},
    {47641, 88932}, {34387, 33543}, {77357, 75870}, {28481, 21948},
    {76059, 16526}, {98029, 35246}, {97408, 80249}, {59543, 83486},
    {59031, 67678}, {69527, 75472}, {30138, 47528}, {20066, 48905},
    {79367, 93717}, {14231, 89060}, {48664, 61568}, {59260, 28064},
    {92070, 68455}, {65254, 35270}, {50807, 48846}, {18466, 91307},
    {98554, 56105}, {78229, 81227}, {17508, 15711}, {32537, 67678},
    {64637, 56999}, {14158, 15450}, {94331, 91050}, {93192, 10690},
    {63700, 25413}, {33698, 83486}, {49890, 21897}, {28284, 93717},
    {68266, 10690}, {62339, 74483}, {99083, 93192}, {88893, 76784},
    {28590, 93192}, {36855, 14484}, {99465, 29281}, {65344, 80947},
    {22897, 35215}, {62999, 53251}, {13164, 29281}, {34681, 93717},
    {21444, 93717}, {83947, 35321}, {47747, 35215}, {54938, 74483},
    {61241, 15440}, {16106, 72541}, {66912, 84455}, {86904, 41575},
    {50909, 27829}, {17878, 29281}, {57511, 71269}, {23564, 97485},
    {55568, 14592}, {38790, 19410}, {69298, 67352}, {26379, 61823},
    {60725, 43692}, {95609, 51225}, {16526, 32067}, {69930, 38183},
    {58261, 96718}, {66299, 62375}, {64363, 90429}, {15958, 32843},
    {88092, 68007}, {55317, 45626}, {73218, 24082}, {90801, 88932},
    {82391, 20291}, {15221, 48905}, {26395, 21292}, {81868, 72079},
    {29281, 35246}, {92022, 90097}, {98990, 33089}, {60704, 38235},
    {73392, 33163}, {62913, 48035}, {41494, 63930}, {78820, 25813},
    {30876, 40719}, {88601, 95093}, {59498, 40624}, {72541, 73738},
    {45001, 84455}, {51393, 83486}, {49594, 71269}, {89306, 28064},
    {95586, 29281}, {74066, 74610}, {84603, 33543}, {29412, 28436},
    {42616, 50820}, {28084, 48905}, {45298, 88932}, {36632, 13881},
    {61452, 69281}, {30530, 24651}, {81040, 24411}, {48479, 55046},
    {48905, 22390}, {92424, 26953}, {36609, 77920}, {36363, 33049},
    {42491, 16526}, {60244, 18450}, {89800, 51386}, {86057, 51511},
    {39702, 85285}, {99044, 83486}, {31142, 33163}, {26681, 15004},
    {79013, 83486}, {22300, 33543}, {36593, 29531}, {96294, 43692},
    {61854, 47611}, {77848, 68786}, {93396, 23174}, {36412, 24709},
    {10311, 74483}, {49637, 55347}, {61341, 62317}, {47003, 75141},
    {57335, 41575}, {62656, 28064}, {78660, 77537}, {55534, 84260},
    {91664, 11744}, {73241, 92188}, {44853, 38163}, {96103, 38745},
    {97685, 48323}, {18594, 29281}, {42945, 18719}, {89791, 41205},
    {43844, 29395}, {52203, 68007}, {45997, 54789}, {43455, 85063},
    {16971, 33163}, {74978, 40751}, {97187, 87588}, {40232, 95503},
    {18342, 52415}, {24965, 74483}, {49746, 23886}, {89099, 43692},
    {67825, 93192}, {16593, 79286}, {56839, 11128}, {11705, 76365},
    {91271, 40714}, {48090, 40916}, {26330, 93717}, {63509, 29785},
    {63644, 56372}, {93981, 36105}, {47622, 94886}, {89825, 10690},
    {38686, 14704}, {89672, 89181}, {77486, 16526}, {45003, 51569},
    {49032, 20690}, {25345, 43748}, {87527, 95013}, {70941, 25536},
    {21015, 80911}, {11083, 92302}, {80364, 69129}, {64499, 16526},
    {17680, 96955}, {82514, 40317}, {64068, 35215}, {40916, 48905},
    {12807, 59297}, {29336, 28064}, {85277, 20168}, {97414, 32624},
    {97987, 38285}, {26537, 39511}, {77528, 21634}, {94621, 65647},
    {67010, 35246}, {85282, 83486}, {60747, 35380}, {35816, 21364},
    {42558, 49229}, {40714, 93717}, {90403, 40714}, {12931, 27634},
    {13207, 48905}, {44081, 24654}, {17523, 12823}, {96863, 16526},
    {63915, 40714}, {92093, 17096}, {87227, 16526}, {82153, 66980},
    {95949, 33543}, {84455, 28064}, {92953, 40916}, {68133, 83486},
    {25145, 12376}, {51168, 49788}, {10426, 70470}, {30746, 36495},
    {59405, 40714}, {11053, 62066}, {28727, 63694}, {60002, 60509},
    {18727, 33163}, {51351, 83486}, {88936, 29525}, {72495, 93717},
    {95001, 53874}, {57689, 29478}, {56271, 93029}, {84192, 40916},
    {66747, 83273}, {63547, 81994}, {44376, 64160}, {78017, 74483},
    {68252, 67678}, {87058, 62841}, {24528, 49581}, {79309, 64033},
    {37689, 88932}, {82925, 14484}, {11185, 50682}, {59981, 19755},
    {19803, 51230}, {88955, 95000}, {62575, 88932}, {59187, 24136},
    {16626, 83486}, {72182, 88932}, {68140, 23920}, {55133, 23460},
    {60424, 89553}, {30277, 95983}, {59807, 35366}, {11695, 63431},
    {88218, 73975}, {86693, 83486}, {64005, 93074}, {82743, 28434},
    {65611, 45730}, {12943, 73174}, {84890, 35215}, {22850, 15532},
    {41887, 11037}, {94870, 43692}, {61232, 71818}, {90930, 96896},
    {65126, 26879}, {50230, 21897}, {62318, 66656}, {44487, 32677},
    {93072, 28064}, {87839, 33543}, {40846, 18450}, {82312, 84455},
    {37205, 21897}, {41771, 72827}, {18488, 71269}, {64975, 88406},
    {41318, 37380}, {94020, 16526}, {67770, 49678}, {92697, 50168},
    {46376, 18386}, {84236, 28064}, {11652, 29281}, {61056, 83486},
    {74605, 36264}, {52827, 88932}, {81941, 66200}, {67301, 95285},
    {21433, 41575}, {88988, 73975}, {12094, 54231}, {65678, 88932},
    {25359, 65733}, {78777, 16526}, {83486, 50212}, {43692, 33163},
    {49518, 63211}, {60987, 94849}, {72384, 71592}, {67038, 40916},
    {75521, 99187}, {99927, 99033}, {20155, 57774}, {68007, 33826},
    {78774, 18719}, {23347, 67678}, {96278, 14854}, {91486, 93192},
    {12417, 56413}, {61202, 35246}, {96627, 71269}, {25222, 75870},
    {64171, 93717}, {68576, 27065}, {69865, 10690}, {89318, 24651},
    {61846, 83486}, {63301, 93717}, {94345, 84455}, {98732, 40714},
    {49854, 18719}, {20484, 40595}, {78186, 36998}, {15151, 71269},
    {16701, 72350}, {84420, 21897}, {70969, 53101}, {96733, 28064},
    {90462, 79235}, {78081, 81241}, {89755, 83486}, {42126, 22997},
    {73585, 75870}, {29146, 74035}, {99960, 51906}, {44570, 21897},
    {12188, 84455}, {97638, 50464}, {58359, 84597}, {56831, 41575},
    {81299, 33163}, {10184, 88932}, {94180, 53663}, {93572, 97839},
    {61193, 85495}, {93057, 40714}, {41575, 33963}, {80661, 10690},
    {84971, 88036}, {68778, 93536}, {33548, 77110}, {67515, 95613},
    {53015, 93192}, {24296, 54065}, {75789, 78090}, {18450, 35693},
    {11400, 92836}, {68927, 93484}, {23360, 76846}, {70962, 24170},
    {25901, 74483}, {90104, 26929}, {92690, 68007}, {84082, 41575},
    {37781, 92073}, {39248, 50515}, {68444, 21897}, {22591, 41077},
    {78300, 88870}, {41642, 21932}, {85689, 59138}, {91716, 78832},
    {22703, 88932}, {17203, 71269}, {52010, 46499}, {20129, 27566},
    {21980, 91880}, {28582, 81241}, {79463, 33163}, {37736, 81322},
    {67994, 93717}, {16953, 74094}, {46951, 61331}, {33543, 69156},
    {18645, 69583}, {94602, 41575}, {13621, 50099}, {27057, 84455},
    {74785, 29281}, {59746, 74477}, {60110, 29281}, {62516, 59138},
    {77989, 84455}, {34023, 84455}, {45508, 41575}, {48128, 93192},
    {23009, 76128}, {67823, 35246}, {44284, 22697}, {73893, 45484},
    {26400, 62980}, {81470, 75013}, {13987, 46758}, {40402, 60999},
    {81241, 89091}, {28661, 74483}, {38754, 40714}, {60453, 36906},
    {18719, 46030}, {91986, 93717}, {36762, 81241}, {52316, 93192},
    {61231, 31543}, {18641, 88840}, {56957, 39972}, {54010, 81241},
    {43662, 92476}, {54471, 62341}, {63021, 29281}, {66926, 62298},
    {66604, 44900}, {76446, 41575}, {48576, 66303}, {10307, 95678},
    {63993, 29281}, {61993, 71211}, {85436, 97664}, {74284, 29460},
    {67739, 99460}, {92165, 11799}, {99609, 74080}, {25438, 79683},
    {99979, 94140}, {52428, 10102}, {65675, 75026}, {24431, 64163},
    {41397, 41972}, {92851, 68007}, {34998, 13243}, {11302, 83897},
    {71884, 58385}, {30217, 55856}, {97095, 12805}, {69071, 76963},
    {88734, 51981}, {41230, 40992}, {31625, 73220}, {60964, 68007},
    {40499, 46723}, {85595, 95871}, {95121, 45209}, {96723, 81227},
    {64147, 77014}, {67833, 96939}, {95487, 56021}, {13075, 79483},
    {69700, 24651}, {15306, 33543}, {34154, 23646}, {57049, 75870},
    {91952, 36106}, {37697, 67678}, {95090, 81227}, {20336, 57015},
    {51568, 14830}, {64290, 68007}, {49988, 14484}, {13744, 48905},
    {52919, 81444}, {36950, 37612}, {29163, 87576}, {30162, 93717},
    {54572, 25694}, {17704, 58919}, {63346, 48905}, {89038, 69793},
    {88932, 84047}, {51833, 57089}, {60989, 40714}, {13203, 33543},
    {21572, 56816}, {23092, 48905}, {28218, 29281}, {71269, 90097},
    {52668, 10690}, {65121, 73814}, {42781, 16309}, {29619, 46447},
    {29737, 41575}, {87960, 16526}, {36815, 29281}, {98734, 26199},
    {92414, 81227}, {27941, 83486}, {41056, 36488}, {35048, 28819},
    {33270, 14484}, {14665, 76345}, {80772, 68337}, {88159, 93717},
    {95525, 94317}, {70169, 12128}, {12374, 48333}, {97483, 81227},
    {86083, 21537}, {92285, 97903}, {83969, 54068}, {49114, 51010},
    {22237, 13379}, {78804, 57913}, {70867, 33543}, {61833, 14011},
    {88978, 11989}, {83372, 20622}, {98991, 85828}, {31890, 35215},
    {12629, 20534}, {89790, 29281}, {99514, 90097}, {21333, 79612},
    {54624, 47370}, {17056, 33543}, {80827, 33543}, {45269, 23828},
    {78475, 30335}, {23246, 16089}, {17554, 74483}, {68357, 16526},
    {28584, 83486}, {41249, 10690}, {32862, 25422}, {53163, 71269},
    {75876, 68766}, {37926, 26161}, {34044, 93192}, {52671, 38283},
    {21682, 25369}, {16611, 68809}, {36831, 81227}, {79227, 68007},
    {10599, 40916}, {68516, 40714}, {77351, 75586}, {41527, 29226},
    {49577, 79357}, {62810, 75870}, {61945, 30290}, {73971, 44700},
    {75302, 66014}, {67678, 37161}, {73242, 59683}, {40271, 23322},
    {46681, 74483}, {16749, 75213}, {64088, 21653}, {81627, 17136},
    {37975, 33300}, {58315, 91975}, {29392, 42921}, {22736, 84726},
    {75087, 64944}, {68106, 14484}, {37010, 26597}, {31609, 30595},
    {87616, 32122}, {39999, 67678}, {87987, 48905}, {73875, 62382},
    {88833, 75870}, {46716, 15944}, {52283, 14484}, {36866, 48905},
    {67346, 24651}, {24077, 30008}, {81976, 28064}, {56264, 81227},
    {83180, 12146}, {50962, 92896}, {54734, 83836}, {10575, 84455},
    {67866, 74483}, {14232, 68552}, {53607, 40916}, {51940, 50552},
    {63404, 81227}, {12755, 92386}, {42741, 94303}, {42172, 64211},
    {24590, 21143}, {69649, 14484}, {19202, 14484}, {17185, 88400},
    {78645, 10690}, {99533, 27051}, {86687, 18450}, {96579, 52391},
    {55295, 96934}, {90628, 93717}, {21113, 21897}, {35322, 35295},
    {34685, 32330}, {86136, 40595}, {96794, 21897}, {20234, 68007},
    {44198, 21897}, {29422, 81145}, {47083, 75727}, {74043, 72541},
    {48760, 48905}, {72646, 46050}, {48320, 39784}, {84231, 95347},
    {95623, 88932}, {13808, 77214}, {46006, 40916}, {66909, 40537},
    {23234, 93192}, {10780, 25237}, {24124, 94403}, {32448, 24651},
    {50298, 11923}, {76485, 33163}, {44318, 33163}, {90946, 16526},
    {42022, 14988}, {85377, 93717}, {86170, 70311}, {73678, 78731},
    {15538, 96086}, {15573, 14484}, {30475, 17329}, {91104, 68007},
    {17132, 88932}, {18658, 33543}, {90097, 42364}, {26817, 93717},
    {75870, 81227}, {26362, 29410}, {40595, 79535}, {50112, 78405},
    {17611, 36111}, {90791, 83486}, {95109, 82102}, {74143, 50625},
    {89442, 77411}, {11299, 45357}, {65424, 21897}, {17687, 33543}};

decltype(input_real) input_test;
//    auto &input = input_test;
auto &input = input_real;
} // namespace

int main() {
  std::vector<ll> first(input.size());
  std::vector<ll> second(input.size());
  int i = 0;
  for (auto [f, s] : input) {
    first[i] = f;
    second[i] = s;
    ++i;
  }
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());
  int64_t result0 = 0;
  for (i = 0; i < input.size(); ++i) {
    result0 += abs(first[i] - second[i]);
  }

  int64_t result1 = 0;
  first.erase(std::unique(first.begin(), first.end()));
  for (auto f : first) {
    result1 += f * std::count(second.begin(), second.end(), f);
  }

  myprint(result0);
  myprint(result1);
  return 0;
}
