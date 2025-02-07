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
#include <queue>

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
    "##########################################################################"
    "###################################################################",
    "#.....#.........#.......#.....................#.....#...#.........#.#....."
    "#.......#.........#.........#.......#...#.........#...#.....#...#E#",
    "#.#.#.#.#####.###.#.#####.###.#.#.#.#.#######.#.###.#.#.###.#.###.#.#.#.##"
    "#.###.#.###.#.###.#.#######.###.###.#.#.#.#.#####.#.#.#.#.#.#.#.#.#",
    "#.#.#.#.....#...#.#.#.......#.#.#.#.#.#.....#...#.#...#...#..............."
    "..#...#.....#.#...#.#.....#...#...#.#.#...#.#.....#.#...#.#...#...#",
    "#.#.#######.###.#.#.#.#######.#.#.#.#.#.###.#.###.#######.###.#.#.########"
    "###.#######.#.#.###.#.#######.###.#.#######.#.#####.#####.#######.#",
    "#.#.#.....#...#...#.......#...#...#...#...#.......#.....#.....#.#.....#..."
    "....#.......#.#.#...#.......#.....#.#.......#...#.#.#...#.....#...#",
    "###.#.#.#####.#############.###############.#.###.#.###.#######.###.#.#.##"
    "#########.###.#.###.#####.#########.#.#########.#.#.#.#.#.###.#.#.#",
    "#...#.#...........................#...#...#...................#.....#.#..."
    "........#.....#.#...#.....#.......#...#.....#...#...#.#.#...#...#.#",
    "#.#.#.###.#.#.#.#####.#.#####.###.#.#.#.#.#.#.#####.#####.#.#.#.###.#.####"
    "#####.#.#.#####.#.###.#####.#.#########.#####.#######.#.#########.#",
    "#...................#.#.#...#.#...#.#...#...#.....#.....#.#.#...#.#...#..."
    "....#.#.#.....#...#...#...#.#.....................................#",
    "#.###.#.#.###.###.#.#.###.#.#.#.###.###.#####.###.#.###.###.###.#.#####.##"
    "###.###.#.###.#####.###.#.#.###############.#######.#.###########.#",
    "#.#...#.#.....#...#...#...#...#...#.......................#.......#.....#."
    "..#...............#.....#...#.....#.....#.#.................#.....#",
    "#.#.#.#.###.###.#####.#.#########.#.#.###.###.#.#.#######.#####.#.#####.##"
    "#.#.#.#.###.#####.#.###########.#.###.#.#.#######.#.#.#.#####.###.#",
    "#...#.#.......#.....#.#.#.....#...#.#.....#.....#...........#...#.......#."
    "..#.#.#.#...#.......#.....#...#.#.....#.......#...#...#.....#.....#",
    "#.###.#.#.#.#.#####.###.###.###.#####.#####.#.#############.#.#.#########."
    "###.#.###.###.#####.#.###.#.#.#.#####.#########.#######.###.#####.#",
    "#.#.....#.#...#...#...#...#.#...#...#.....#.........#.......#.....#...#..."
    "..#.#.....#...#.....#...#...#...#.#...#.........#.........#.#.....#",
    "#.#.#.###.#.###.#.###.###.#.#.#.#.#.#####.#########.#.#######.###.#.#.###."
    "#.#.#.#####.###.#######.#########.#.###.#########.#########.#.###.#",
    "#.#.......#.....#.#.....#.....#.#.#.#.........#.....#.........#.#...#...#."
    "#.#.#...#...#...#.......#.......#.....#.........#.#...#.....#.....#",
    "#.#.#.#####.#######.###.###.#.#.#.#.###.#######.###############.#######.##"
    "#.#.#####.###.###.###.###.###.#.#.#############.#.###.#.###.#.###.#",
    "#.#.#.......#.......#.#.#.#.#.#.#.#...#.#.......#...............#.....#..."
    "..#.#.....#...#...#...#.....#.#.#.#...........#.#...........#...#.#",
    "#.#.#.#####.#.#######.#.#.#.#.###.###.###.#######.#######.#.#####.###.#.##"
    "###.#.#####.###.###.###.###.#.###.#.#########.#.###.#.#.#.###.#.#.#",
    "#...#.#.....#.....#.......#.#.......#.#...#.......#.......#.#.......#...#."
    "....#...#...#...#...#.#...#.#...#.#.....#.#...#.#...#.............#",
    "###.#.#.###.#####.#.#######.#########.#.#.#.#######.###.#.###.###########."
    "#######.#.#######.###.###.#.###.#.#####.#.#.###.#.###.#.#.#.#.#####",
    "#.............#...#.#.......#...#.#...#...#...#...#.#.#.#.....#.#........."
    "#...#...#.#.....#.#.......#...#...#.....#.#.....#.#...#.#...#.#...#",
    "###.#.#.###.#.#.#.#.#.#######.#.#.#.#####.#####.#.#.#.#.###.###.#.########"
    "#.#.#.#.#.#.###.#.#.#########.#####.#####.#.###.#.#.#.#.#####.#.#.#",
    "#...#.....#.#.#.#...#.......#.....#.....#.......#.....#...#.....#.#......."
    "..#...#.#...#.#...#...#.............#.....#.#...#.#.#.#.......#.#.#",
    "#.#.#.###.#.#.#.###########.#.#.#.#####.#.###########.###.#####.#.###.#.##"
    "#######.#####.#######.#.#######.#.#######.#.#.#.#.#.###.#####.#.#.#",
    "#.#.#...#.#...#.#...#...#...#.#...#.....#.#.....#...#...#...#...#.#...#.#."
    "..........#.......#.....#.....#.#...#...#.#.#.#...#.............#.#",
    "#.#.#.#.#.#####.#.#.#.#.#.###.#####.#####.#.###.#.#.#######.#####.#.###.#."
    "#######.#.#.###.###.#####.###.#####.#.#.#.#.#.#.#####.###########.#",
    "#.#.#.#.#.......#.#...#...#.....#...#.#...#.#.#...#.......#.#.....#...#.#."
    "#.#.....#...#.#.#.....#...#.#...#...#.#...#...#.......#.........#.#",
    "#.#.###.#######.#.###.#########.#.###.#.###.#.###########.#.#.#######.#.#."
    "#.#.#####.###.#.#.#####.###.###.#.###.#######.#.#######.#########.#",
    "#.#.....#.......#...#...........#.#...#...#.#...#.......#.#.#...#........."
    "..#.#.......#...#.#.#...#.#...#...#.#...........#.........#.......#",
    "#.#.###############.#.#########.#.###.###.#.#.###.#.#####.#.###.#.#.######"
    "#.#.###.#.###.###.#.#.###.#.#.#####.#.###########.#######.#.#######",
    "#...#.............#...#.....#...#...#.#...#.#.....#.....#.#.#...#.#......."
    "#.#...#.#...#.#.#.....#.....#.........#.....#...#.#.....#.#...#...#",
    "###.#.#########.#.#####.#.###.#####.#.#.###.###.#######.#.#.#.###.###.###."
    "###.#.#####.#.#.###.#.#.#######.#######.###.#.#.#.#####.#.###.#.#.#",
    "#...#.#.....#...#...#...#.#...#.#...#...#.#...#.#.....#.....#.....#...#.#."
    "..#.#.#.....#...#.#.#.#.#.....#.#.....#...#...#...#...#.#...#...#.#",
    "#.#.#.#.#####.#####.#.#####.###.#.###.###.###.###.###.#############.###.##"
    "#.###.#.#######.#.#.#.###.###.###.###.###.#########.#.#.###.#####.#",
    "#.#...#.....#...#.....#.....#...#.#.#.#.....#...#.#.#.......#.......#....."
    "..#...#.......#...#.#.......#.#...#.#.....#.........#.#...#.....#.#",
    "#.#.###.###.###.#####.#.#.#####.#.#.#.#.#######.#.#.#######.#.#.#####.####"
    "###.###.###.#####.#.#########.#.###.#######.###.#####.#.#.###.#.#.#",
    "#.#...#...#...#.....#.#.#...#.......#.#.......#.#.#.......#...#.#...#...#."
    "....#.....#.#.....#.....#.....#.#.....#.......#...#...#.#...#.#.#.#",
    "#.###.###.#.#.#####.#.#.#.#.#.#.#.#.#.###.#.#.#.#.#.#.###.#####.###.###.#."
    "###.#####.#.#.#########.#.#.###.#.#.#.#.#####.###.#.###.###.#.#.#.#",
    "#...#...#.#.....#.#.#.#...#...#...#.#...#.#.#.#.#.#.#.#...#...#...#...#..."
    "#...#...#.#.#.....#.#...#.#.#...#...#...#.....#...#.#...#.#.#.#...#",
    "###.###.#.###.#.#.#.#.#####.###.###.###.#.#.#.#.#.###.#.#####.###.#.#.####"
    "#.#.#.#.###.#####.#.#.###.###.###.#.#####.#.###.###.###.#.#.#.###.#",
    "#...#.....#.#.#...#.#.#.....#...#...#...#.#.#.#...#...#.#.......#.#.#....."
    "....#.#...#.........#...#...#...#.#...#...#.....#.#...#.#.#.#.#...#",
    "#.#.#.###.#.#.###.#.###.#####.###.#.#.#####.#.#####.###.#.###.###.########"
    "#####.###.#.###.###.###.###.###.#####.###.#######.#.#.#.#.#.#.#.###",
    "#.#.#.#.#...#...#.#.........#.#...#.#.#.............#.....#.#.#..........."
    "..#...#.#.#...#...#...#...#...#...#...#.....#.....#.#.#.#.#.#...#.#",
    "#.#.#.#.###.###.#.#########.#.#.###.#.#.###.#######.#######.#.#.###.######"
    "#.#.###.#.#####.#.#######.#.#####.#.###.#.###.#.#.#.#.#.#.#.#####.#",
    "#.#.#.#.......#.#.....#...#.#.#.#...#...#...#...#...#.....#...#.#...#....."
    "#...#...#.....#.#...#.....#.......#...#.#.#...#.#...#.#.#.#.......#",
    "#.###.#.#######.#######.#.#.#.#.###.#####.###.#.#.###.#.#.#####.#.#####.##"
    "#######.#####.#.###.#.###############.#.#.#.###.###.#.#.#.###.#####",
    "#.....#...#.....#.......#.#.#.#...#.#.....#...#...#...#.#.#.....#.....#..."
    "........#...#...#.#...#.#.....#.......#.....#.#.#...#.#.....#.....#",
    "###########.#####.###.#.#.###.###.#.###.#.#.#######.###.#.#.###.#####.####"
    "###.###.###.#####.#####.#.#.###.#.#####.#####.#.#.###.###########.#",
    "#.#.........#...#.#...#.#.....#...#.#...#.#.#...#...#...#...#.#.....#....."
    "..#...#.............#.....#.....#.#...#.......#.#...#.....#...#...#",
    "#.#.###.#####.#.#.#.###.###.###.###.#.###.#.#.###.###.#######.#.#.########"
    "#.#.#.#####.#######.###.#########.#.###.#####.#.###.#####.#.#.#.#.#",
    "#.............#...#.....#...#...#.....#...#...#...#.............#.....#..."
    "..#.#.#.....#.....#...#.#.....#...#...#.......#.#.......#.#.#...#.#",
    "#.###.#.#.#.#.###########.#.#.#.#############.#.###.#########.###.#.###.##"
    "#####.#.#####.###.###.#.###.#.#.#####.#######.#.#.###.###.#.#####.#",
    "#...#.#...#.#.......#.....#.#.#...........#...#.#...#.#.....#.....#...#..."
    "......#...#...#.#.....#...#.#.#.#...#.........#.#.#.........#...#.#",
    "#.#.#.#####.#######.#.#####.#.###########.#.###.#.###.#.###.#.#######.####"
    "###.#.#.#.#.###.#########.#.#.#.#.#.#.#########.#.#.#.#.#####.#.#.#",
    "#.#.#.#...#.............#...#.........#...#...#.#.....#.#.#...#.....#....."
    "..#...#.#.#.....#...#...#.#.#.#...#.#.#.....#...#.#...#.....#.#...#",
    "#.#.#.#.#####.#.#.#.###.#.###########.#.#.#.#.#.#####.#.#.#########.#####."
    "#.#####.#.#####.#.#.#.###.#.#.#####.#.#.###.#.#.#.###.#####.#.#####",
    "#.#.#.#.....#...#.#.#...#.#...........#.#.#...#...#...#.........#.....#..."
    "#.#.....#.....#.#.#...#...#.#.#...#.#...#...........#.............#",
    "#.###.#####.###.#.#.#.###.#.#.#########.###.#####.#############.#.###.#.##"
    "###.#####.#####.#.###.#.###.#.#.#.#.#####.#########.#.#.#######.#.#",
    "#.....#...#...#.#.#...#.#.#.#.........#.#...#.....#.....#.....#...#...#..."
    "......#.#.#.....#...#.....#.#.#.#...#.#...#.#.....#.#.#...#...#...#",
    "#.#.###.#.###.#.###.#.#.#.#.#####.#####.#.###.#####.#.#.#####.#####.######"
    "#.###.#.#.#.#####.#.#####.#.#.#.#####.#.###.#.#.#.#.#.###.#.#.###.#",
    "#.#...............#...#.#.#.......#...#.....#...#...#.#.....#...#.......#."
    "..#.#...#...#...#.#.....#.#.#.#.#.....#...#...#.#.#...#.#.#.#.....#",
    "#.#.#.#####.#.###.#####.#.#.#######.#.#########.#.###.#####.#.###.#######."
    "#.#.###.#######.#.###.#.#.###.#.#.###.###.#####.#.###.#.#.#.#######",
    "#...#...#.#.....#.......#.#.#.......#.........#...#...#...#...#.....#....."
    "..#.....#.....#.......#.#.#...#.#.#.....#...#...#.....#.#.#.......#",
    "#.#####.#.#.###########.#.#.#.#########.#####.#####.###.#.#####.#####.####"
    "#.#.#######.#.#.###.#####.#.#.#.###.#######.#.#######.#.#.###.#.#.#",
    "#.......#...#.......#...#.#.#.#.......#...#...#...#...#.#.......#...#.#..."
    "..#.#.......#.#...#.......#...#...#.#.....#.#.#.........#.........#",
    "#########.#.#.#####.#.#.#.#.#.#.#.###.#.#.#.#.#.#.#.#.#.#########.#.#.#.#."
    "###.#.#.#.###.#########.###.#####.#.#.#.###.#.#####.#.#####.#.###.#",
    "#.....#.#.#...#...#...#...#.#.#.#...#...#...#.#.#.#.#.#.........#.#...#..."
    "..#...#...#.#.........#.#.......#.#...#.....#.#...#...............#",
    "#.#.#.#.#.#.###.#.###.#.###.#.#.###.#.#####.###.#.###.#.#.#######.########"
    "#.#########.#########.#.###.###.#.#######.###.#.#.###.###.#.#####.#",
    "#...#...#.#...#.#...#.#...#.#.....#.#.......#...#...#.#.#.#.....#.......#."
    "..#.......#...#.....#.#.....#...#.#.......#...#.#.....#...#.....#.#",
    "###.#.###.#.#.#.#####.###.#####.###.#########.#####.#.#.#.#.###.#########."
    "###.###.#.#.#.#.#.###.#####.#.###.#.###.#.###.#.#######.#.#.#####.#",
    "#...#.#.....#.#.......#.#.......#...#...#.....#...#.#.....#...#..........."
    "#...#...#...#.#.#.#.........#...#.#.#.#.#...#.........#.#.#.#.....#",
    "#.#.#.#.###.#.#.#######.#########.#.#.#.#.#####.#.#.#########.############"
    "###.#.#.#####.#.#.#.###.###.###.#.#.#.#.###.#######.###.#.#.#.#####",
    "#.............#.............#.....#.#.#...#...#.#...........#.#.......#..."
    "....#.#.#...#...#.#.......#.....#.....#...#.#...#...#...#.#.#...#.#",
    "###.#.###.#.#.#############.#.#####.#.#####.#.#.#.#.###.#.#.#.#.#####.#.#."
    "#.#.#.#.#.#.#####.#######.#########.#####.#.#.#.#.###.#.###.###.#.#",
    "#.........#...#.......#.....#.#.....#.......#...#.#.....#...#.#.#...#...#."
    "#.#.#.#.#.#.#...#.#.....#.#.......#.#.....#.#.#.#.#...#.#.....#.#.#",
    "#.#.#.#####.###.#.#####.#####.###.###############.#.#.#.#.###.#.#.#.#####."
    "#.#.#.###.#.#.#.#.#.#.#.#.#.#####.#.#.#.#.#.#.#.###.###.#.###.#.#.#",
    "#.#.....#.......#.#.....#...#...#.#.............#...#...#.....#...#...#..."
    "#.#.#.....#.#.#.#.....#.#.#.#.....#.#.#...#...#.#...#.#.#.#...#...#",
    "#.#.#.#.#######.###.#####.#.###.#.#.#####.###########.#################.##"
    "#.#.#######.#.#.#.#######.#.#.#####.#.#########.#.###.#.#.#######.#",
    "#...#...#...#...#...#.#...#.#...#.#...#.#...........#.#.....#...........#."
    "#.#.#.......#.#.#.#.......#.#...#...#.#...#...#.#...#.#.#.........#",
    "#.#.#.###.#.#.###.###.#.#.###.###.###.#.#######.#####.#.#.#.#.###########."
    "#.#.#.#######.#.#.#.#######.###.#####.#.#.#.#.#.###.#.#.#.#.#######",
    "#...#.#...#.......#.....#...#.#...#...#.......#.......#.#.#...#.....#....."
    "..#.#.#.....#.#...#...#.......#.......#.#.#.#.#...................#",
    "###.#.#.###.#.#.###.#######.#.#.###.#########.#.#########.#####.###.#.####"
    "#####.#.#.###.#######.#######.###########.#.#.#######.#.#.###.#.#.#",
    "#.#.#...#...#.#.#...#.....#.#.#.#...#.......#.............#...#...#......."
    "......#.#.#...#...#...#.......#...#.......#.#.........#.#.....#.#.#",
    "#.#.#.###.###.#.#####.###.#.#.###.###.#####.#####.###.###.#.#.############"
    "#######.###.###.#.#.###.#.#.###.#.#.###.#.#.#.###.#####.###.#.#.#.#",
    "#...#.#...#...#.......#.#...#.....#.....#.........#...#.....#...#.....#..."
    "......#.....#...#...#.......#...#.#.#...#.#.....#.......#.#.....#.#",
    "#.###.#.###.#########.#.#.#############.###########.###.###.#.#.#.###.####"
    "#.#####.#####.#######.###.###.###.#.#.###.#####.#########.#.#.#.#.#",
    "#.....#...#...............#.............#...#.....#.#...#...#.#.....#...#."
    "..#...#.#.....#.....#.#.....#.#...#.#.#...#.#...#.....#.........#.#",
    "#####.###.###.#############.#######.#.###.#.###.###.#.###.#.###########.#."
    "###.#.#.#.###.#.#.#.#.#######.#.#####.#.###.#.###.###.#.###.#.#.#.#",
    "#...#...#...#.#.......#...#...#...#.#.#...#...#...#.#...#.#...........#.#."
    "#...#...#.#.....#.#...#.....#.#.....#.#...#.#.#.....#.......#.#...#",
    "#.#.#.#.#.#.#.#.#####.#.#.###.###.#.###.#####.#.#.#.###.#.###.#######.#.#."
    "#.#######.#.#####.#####.###.#.#####.#.#.#.#.#.#.###.#.#.###.#.#.#.#",
    "#.#...#.#.#.#.#.#.#...#.#...#.#...#.....#...#.#.#.#.#...#...#.#.....#...#."
    "....#...#.#.....#.....#...#...#...#.#...#...#.#.....#.#...#.....#.#",
    "#.###.#.#.#.#.#.#.#.#####.#.#.#.#.#######.#.#.###.#.#.#####.###.###.######"
    "###.#.###.#####.#.#.#.###.#####.#.#.###.###.#.###.#.#.#.#.#.#.#.#.#",
    "#.#.............#.......#...#.#.#.........#.#...#.#.#.#...#.....#.#.#....."
    "#.#.#.#...#...#.#...#.#...#.....#.#.#.......#...#.#.#.#.#.....#...#",
    "#.###.#####.#####.#####.#.###.#.#####.#####.###.#.#.#.#.#.###.###.#.#.###."
    "#.#.#.#.###.###.#####.#.###.#######.#.#####.###.#.#.###.###.#.#.###",
    "#...#.....#.#.#...#.......#...........#.......#.#...#.#...........#...#..."
    "#...#.#.#.....#.....#.......#...#...#.....#...#.#.#.#.....#...#...#",
    "#.#.#####.#.#.#.#.#.#######.###.#######.#######.#.###.#########.#.#####.##"
    "###.#.#.#####.###.#.#########.#.#.#######.#####.#.#.#.#####.#.#.#.#",
    "#.#.#.....#.#...#...#.#.....#.........#.#...#...#...#...#.....#.#...#....."
    "......#.....#.....#.....#.....#...#.....#.#.....#.#.....#...#...#.#",
    "#.#.###.###.#.#######.#.#############.#.#.#.#.#########.#.###.#.#.#.#.####"
    "#.#########.###.###.###.#.#########.#.#.#.#.#########.###.#.#.#.#.#",
    "#.#...#.#...#...#.....#.....#.......#.#...#.#.........#...#.#.#.#...#....."
    "#.........#...#.#...#...#.#.......#.#.#...#.#.......#.#...#...#...#",
    "#.###.#.#.#####.#.###.#####.#.#####.#.#####.#######.#.#####.#.#.###.#####."
    "#####.###.###.#.#.#.#####.#.###.###.#.###.#.#####.#.###.###.#.#.###",
    "#.#...#.#.#...#.#...#.#.....#...#...#...#.......#.#.#.....#.......#.#...#."
    "#...#...#...#.#.#.#.#.....#.........#.#...#...#...#...............#",
    "#.#.###.#.#.#.#.###.#.#.#######.#.#####.#.#####.#.#.###.###.#####.#.#.#.#."
    "#.#.###.#####.#.#.#.#.#######.#######.###.###.#.#######.#.#.#.#.#.#",
    "#.#...#...#.#.#...#.#.#.#.......#.....#.#.....#...#.#...#.........#...#..."
    "#.#.....#.....#...#.#.....#...#.....#...#...#...#.........#...#.#.#",
    "#####.#######.###.#.###.#.#.#########.#.###.#.#.###.#####.#####.#######.##"
    "#.#####.#.###############.#####.###.#.#.###.#####.#########.###.#.#",
    "#.....#.......#...#...#.#.#.#.....#...#.#...#...#...#.....#...#.#........."
    "..#...#.#...#...........#.......#...#.#...#.#...........#...#...#.#",
    "#.#######.#.###.#####.#.#.#.#.###.#.###.#.#####.#.###.#####.#.###.########"
    "###.###.###.###.#######.###.#####.###.###.###.#########.###.#.###.#",
    "#.#.....#.#...#.......#...#.#.#.#.......#.....#.#.#...#...#.#...#.....#..."
    "..#.....#...#...#.....#...#.#...#.#...#.#...#.....#...#.......#...#",
    "#.#.###.#.#.#.#.#####.#####.#.#.#####.#######.#.#.#.###.###.#.#.#####.#.##"
    "###.#####.###.###.#######.#.#.#.#.#.###.###.#####.#.###########.#.#",
    "#.#...#.#...#...#...#.#.....#.#.......#.....#.#.#.#...#...#...#.......#..."
    "#.....#...#.....#.........#.#.#.#.#...#...#.....#.#.............#.#",
    "#.###.#.###.#####.#.#.#.#.###.#.#####.###.#.#.#.#.###.#.#.###.###########."
    "#.#####.###.###.#.#########.###.#.###.#.#.#####.#.###.#.#########.#",
    "#.....#.....#...#.#.#...#.....#.#...#.....#.#.#.#...#.#.#...#...#.......#."
    "#...#...#...#.#.#...#.#...#.....#...#...#.#...#.#...#.#.#.#.......#",
    "#.#########.#.#.#.#.#.###.#####.#.#.#########.#.###.#.#####.###.#.#####.#."
    "###.#.###.###.#.###.#.#.#.#####.###.#####.#.#.#.###.#.#.#.#.#####.#",
    "#...#.....#.#.#...#.#.#...#.......#.........#...#...#.......#.#...#.....#."
    "....#.#.......#.#...#...#...#.....#.#...#.#.#.#.#...#.#.#...#...#.#",
    "###.#.#####.#.#####.###.###.###############.#.###.#.#######.#.#####.######"
    "###.#.#########.#.#######.#.#.#####.###.#.#.#.#.#.###.#.#####.#.###",
    "#.#.#...#...#...#...#...#...#...#...#...#...#.#.....#.....#.#...#.#......."
    "..#.#.....#...#.#.......#.#.....#...#...#...#.#...#...#...#...#...#",
    "#.#.###.#.#.###.#.###.###.#.#.#.#.#.#.#.#.###.#.#.###.###.#.#.#.#.###.####"
    "#.#.#####.#.#.#.#####.#.###.#.###.###.#######.#######.###.#.#####.#",
    "#.#...#.#.....#.#...#.#...#.#.#...#...#.#.#.....#.#...#.#.#...#...#......."
    "..#.....#...#...#.....#...#.#.#...#.......#...#.....#...#...#...#.#",
    "#.###.#.###.###.###.#.#.#.#.#.###.#######.#.###.###.###.#.#######.###.#.##"
    "#.#####.#########.###.###.#.#.#.#######.###.###.#.#.#.#####.#.###.#",
    "#...#...#...#...#.#.#.#...#.#...#.#...#.......#...#.....#.........#...#.#."
    "....#.....#.......#.#.#.#.#...#.......#.....#...#.#.#.#...#...#...#",
    "#.#####.#.#.#.###.#.#.###.#.###.###.#.#.###.#.###.#####.###########.#.#.#."
    "###.#.###.#######.#.#.#.#.###.#######.#.#######.#.#.###.#.###.#.###",
    "#.......#...#...#.#.#.#...#...#.....#.....#.#...#...#...#.....#.....#.#..."
    "#.#.#.....#...#...#.....#.#...#.....#.........#.#.#.....#...#.#...#",
    "#.#########.###.#.#.#.#.#####.#.###.#.###.#.#.###.###.###.###.#.#.########"
    "#.#.#.#####.#.#.###.#####.#.###.###.#.#######.#.#.###.#.###.###.#.#",
    "#...#.#...#...#.#.#...#.#...#...#.....#...#.#...#...#...#.#.....#.#......."
    "..#.#.....#.#.#...#.#...#.#.#.#...#.#.#.....#.#.#.#.#...#.........#",
    "###.#.#.#.#.###.#.#####.###.###.#.###.#.#######.###.###.#.#.###.#.#.#.####"
    "###.#####.#.#.###.#.#.#.#.#.#.###.#.#.#.#.###.#.#.#.###.#.###.###.#",
    "#...#.#.#...#...#.....#...#...#...#...#.........#...............#...#....."
    "..#.....#.#.#.....#.#.#...#...#...#...#.#.....#.#.#.........#...#.#",
    "#.###.#.#.###.###.#######.#.#.#####.#.#.#######.#.#####.#.###.###.########"
    "#.#.###.#.#.###.###.#.#######.#.#######.#########.#.#.#.#######.#.#",
    "#.....#.#.....#.........#.#.#...#...#.........#...............#...#.....#."
    "..#...#.#...#...#.....#.....#.#.......#.#.........#.#...#.....#...#",
    "#####.#.#.#####.#.###.#.#.#####.#.###.#.###.#########.#.###.#.#.#.#####.#."
    "#.#.#.#.#####.###.#########.#.#######.#.#.###.#####.###.#.###.###.#",
    "#.#...#...#.#.........#.#.#.....#.....#.#...#.....#.#...#...#...#.......#."
    "#.#.#...#.#...#...#.......#.......#...#.............#...#...#.....#",
    "#.#.#####.#.#.#####.#.###.#.###.#####.#.#.#.#.#.#.#.###.#.#######.#.###.#."
    "#.#.#####.#.###.###.###.#.#####.###.###.#.###.#####.#.#.###.#######",
    "#.#.#.......#.......#.......#.......#...........#...#...#...#.....#.#...#."
    "#.#.#...#.....#.#...#...#...#...#...#.#.....#.....#.#.#.#...#.....#",
    "#.#.###.#.#.###.#####.###############.#.#.#.#.#.#####.#.###.#######.#.###."
    "#.#.#.#.#.#####.#.###.#####.###.#.###.###.#.#####.###.#.#.###.#.###",
    "#.....................#.........#.....#...#.#.#.....#...#...........#...#."
    "#.#.#.#...#...............#...#.#.#.......#.....#.#...#...#...#...#",
    "#.###.###.#.###.#.#.###.#######.#.###.#.###.#.#####.###.#################."
    "#.#.#.#####.#####.#.###.#####.###.#.#.###.#####.#.#.###.#######.#.#",
    "#...#.....#.....#.#...#...#...#.#.#...#...#...#...#...#...........#......."
    "#.#.#...#...#.......................#.#.......#...#.#...#.........#",
    "#.#.#####.#######.###.###.#.###.#.#.#.#.#.#######.#.#############.#.######"
    "#.#.#####.###.#######.#.#.#########.#.#.#.###.#####.#.#####.#.###.#",
    "#S#...............................................#.................#....."
    "..#...........#.........#...........#.......#...............#.....#",
    "##########################################################################"
    "###################################################################"};

decltype(input_real) input_test{
    "#################", "#...#...#...#..E#", "#.#.#.#.#.#.#.#.#",
    "#.#.#.#...#...#.#", "#.#.#.#.###.#.#.#", "#...#.#.#.....#.#",
    "#.#.#.#.#.#####.#", "#.#...#.#.#.....#", "#.#.#####.#.###.#",
    "#.#.#.......#...#", "#.#.###.#####.###", "#.#.#...#.....#.#",
    "#.#.#.#####.###.#", "#.#.#.........#.#", "#.#.#.#########.#",
    "#S#.............#", "#################",
};
decltype(input_real) input_test2{
    "###############", "#.......#....E#", "#.#.###.#.###.#", "#.....#.#...#.#",
    "#.###.#####.#.#", "#.#.#.......#.#", "#.#.#####.###.#", "#...........#.#",
    "###.#.#####.#.#", "#...#.....#.#.#", "#.#.#.###.#.#.#", "#.....#...#.#.#",
    "#.###.#.#.#.#.#", "#S..#.....#...#", "###############",
};

// auto &input = input_test2;
auto &input = input_real;

struct Ctx {
  std::tuple<ll, ll> _start;
  std::tuple<ll, ll> _finish;
} ctx;

void read_ctx() {
  for (ll y = 0; y < input.size(); y++) {
    for (ll x = 0; x < input.at(y).size(); x++) {
      auto c = input.at(y).at(x);
      if (c == 'S') {
        ctx._start = {x, y};
      } else if (c == 'E') {
        ctx._finish = {x, y};
      }
    }
  }
}

constexpr std::tuple<ll, ll> DIFFs[]{{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

struct Vertex {
  ll id;
  std::tuple<ll, ll> coord;
  std::set<std::tuple<Vertex *, ll>> _connected;
};

std::vector<Vertex *> vertexes;
std::map<std::tuple<ll, ll>, Vertex *> toc;

void generate_graph() {
  for (ll y = 0; y < input.size(); y++) {
    for (ll x = 0; x < input.at(y).size(); x++) {
      auto c = input.at(y).at(x);
      if (c == 'E' || c == 'S') {
        Vertex *v = new Vertex();
        v->coord = {x, y};
        v->id = toc.size();
        vertexes.push_back(v);
        toc[{x, y}] = v;
        continue;
      }
      if (c == '#') {
        continue;
      }
      std::set<std::tuple<ll, ll>> dots;
      for (auto [dx, dy] : DIFFs) {
        ll new_x = x + dx;
        ll new_y = y + dy;
        auto new_c = input.at(new_y).at(new_x);
        if (new_c != '#') {
          dots.insert({new_x, new_y});
        }
      }
      if (dots.size() == 0 || dots.size() == 1) {
        continue;
      }
      if (dots.size() == 3 || dots.size() == 4) {
        Vertex *v = new Vertex();
        v->coord = {x, y};
        v->id = toc.size();
        vertexes.push_back(v);
        toc[{x, y}] = v;
        continue;
      } else if (dots.size() == 2) {
        auto [x0, y0] = *dots.begin();
        auto [x1, y1] = *std::next(dots.begin());
        if (x0 != x1 && y0 != y1) {
          Vertex *v = new Vertex();
          v->coord = {x, y};
          v->id = toc.size();
          vertexes.push_back(v);
          toc[{x, y}] = v;
        }
      }
    }
  }
}

void connect_graph() {
  for (auto *v1 : vertexes) {
    for (auto *v2 : vertexes) {
      if (v1 == v2) {
        continue;
      }
      auto [x1, y1] = v1->coord;
      auto [x2, y2] = v2->coord;
      if (x1 == x2) {
        bool found_stone = false;
        for (ll y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
          if (input.at(y).at(x1) == '#') {
            found_stone = true;
            break;
          }
        }
        if (!found_stone) {
          v1->_connected.insert({v2, abs(y1 - y2)});
          v2->_connected.insert({v1, abs(y1 - y2)});
        }
      } else if (y1 == y2) {
        bool found_stone = false;
        for (ll x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
          if (input.at(y1).at(x) == '#') {
            found_stone = true;
            break;
          }
        }
        if (!found_stone) {
          v1->_connected.insert({v2, abs(x1 - x2)});
          v2->_connected.insert({v1, abs(x1 - x2)});
        }
      }
    }
  }
}

using Path = std::vector<Vertex *>;
std::set<Path> find_paths() {
  std::set<Path> paths;
  std::vector<Path> queue;
  queue.push_back({toc.at(ctx._start)});

  while (!queue.empty()) {
    auto current_path = queue.back();
    queue.pop_back();

    auto *last_vertex = current_path.back();
    for (auto [connected_vertex, cost] : last_vertex->_connected) {

      if (std::find(current_path.begin(), current_path.end(),
                    connected_vertex) != current_path.end()) {
        continue;
      }
      auto new_path = current_path;
      new_path.push_back(connected_vertex);
      if (connected_vertex->coord == ctx._finish) {
        paths.insert(std::move(new_path));
        myprint(paths.size());
      } else {
        queue.push_back(std::move(new_path));
      }
    }
  }
  return paths;
}

// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
using namespace std;
#define INF 0x3f3f3f3f
// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// To add an edge (assumes the same weight u->v and v->u, therefore not usable
// in our task)
void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
  adj[u].push_back(make_pair(v, wt));
  adj[v].push_back(make_pair(u, wt));
}

// Prints shortest paths from src to all other vertices
int shortestPath(const vector<pair<int, int>> adj[], int V, int src,
                 int target) {
  // Create a priority queue to store vertices that
  // are being preprocessed. This is weird syntax in C++.
  // Refer below link for details of this syntax
  // http://geeksquiz.com/implement-min-heap-using-stl/
  priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

  // Create a vector for distances and initialize all
  // distances as infinite (INF)
  vector<int> dist(V, INF);

  // Insert source itself in priority queue and initialize
  // its distance as 0.
  pq.push(make_pair(0, src));
  dist[src] = 0;

  /* Looping till priority queue becomes empty (or all
  distances are not finalized) */
  while (!pq.empty()) {
    // The first vertex in pair is the minimum distance
    // vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted distance (distance must be first item
    // in pair)
    int u = pq.top().second;
    pq.pop();

    // Get all adjacent of u.
    for (const auto &[v, weight] : adj[u]) {
      // If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight) {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(make_pair(dist[v], v));
      }
    }
  }

  // Print shortest distances stored in dist[]
  //        printf("Vertex Distance from Source\n");
  //        for (int i = 0; i < V; ++i)
  //            printf("%d \t\t %d\n", i, dist[i]);

  return dist[target];
}

} // namespace

int main16() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  read_ctx();

  generate_graph();
  connect_graph();
  myprint(vertexes.size());

  const size_t vertex = vertexes.size() * vertexes.size();
  auto *adj = new std::vector<pair<int, int>>[vertex];

  for (auto *from_vertex : vertexes) {
    for (auto [to_vertex, costs] : from_vertex->_connected) {
      if (from_vertex == to_vertex) {
        continue;
      }
      ll real_costs;
      auto [x_from, y_from] = from_vertex->coord;
      auto [x_to, y_to] = to_vertex->coord;
      if (from_vertex->coord == ctx._start && y_from == y_to) {
        real_costs = costs;
      } else {
        real_costs = 1000 + costs;
      }
      adj[from_vertex->id].push_back(make_pair(to_vertex->id, real_costs));
    }
  };

  result0 = shortestPath(adj, vertexes.size(), toc.at(ctx._start)->id,
                         toc.at(ctx._finish)->id);

  myprint(result0);
  myprint(result1);
  return 0;
}
