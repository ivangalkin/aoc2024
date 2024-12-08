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
    "................n................L..Y.............",
    "........m.........................................",
    ".............n.............................l......",
    "...............T.m..e....M........................",
    "...........T..y...........i.......L.....2.........",
    ".....................e.....h.......Y........l.....",
    "...................i......d.......................",
    "...5..............T....o......i...................",
    "......C.5...........m..p...o.........2....I.......",
    ".......C.n...........d..............o....p........",
    "..............e........dp.....M...................",
    "..8.........w.N.....n.p.....F.....................",
    ".......N.......m.....D....o.......................",
    "........DU...........y.........I..................",
    "..D..X......N.T....M..............................",
    "...........D..............2c..hl.A....M...........",
    ".5.w.8...............h6...........................",
    "5.....P...............d.Y.y......FA......L........",
    "........w.................h.......................",
    "...................N..............................",
    ".............B...............u.f..................",
    ".........wX.......6...............................",
    "..............XC..............Ax..................",
    ".P.......8......................c........f........",
    "...e....U.u.........s.........f............Y......",
    "..........U..X.........2..........W.....f.........",
    "........P.........................................",
    ".........s.u......................S...............",
    ".....U...................c.....F............H.....",
    ".........BC..........6............................",
    "...................s..7..A...S............3I......",
    "........B.s...u............S...i........H.........",
    "..O.........................c....W....S...........",
    "..........................a..........3......IE....",
    "0........P................F.......................",
    ".............7.................W........3.........",
    "......t.W............7........................E...",
    "...O.....9............................E...........",
    ".....a19..........................................",
    "....t.......O..........x..........................",
    "..................................b..............3",
    "........1......................b..................",
    ".......1....8...........x.........................",
    ".......40.........................................",
    ".....t...O.0...4...........................H......",
    ".......0..............x.......b...................",
    "..4.......a.B..............b...........6..........",
    ".......t9..........17..................H..........",
    "........................9.........................",
    "...........a......................................",

};

decltype(input_real) input_test{"............",
                                "........0...",
                                ".....0......",
                                ".......0....",
                                "....0.......",
                                "......A.....",
                                "............",
                                "............",
                                "........A...",
                                ".........A..",
                                "............",
                                "............"

};
// auto &input = input_test;
auto &input = input_real;

bool insert_antinode(std::tuple<ll, ll> antinode,
                     std::set<std::tuple<ll, ll>> &result) {
  auto [x, y] = antinode;
  if (y < 0 || y >= input.size()) {
    return false;
  }
  if (x < 0 || x >= input.at(y).size()) {
    return false;
  }
  result.insert(antinode);
  return true;
}

struct Antennas {
  std::set<std::tuple<ll, ll>> coord_antennas;

  void calc_antinodes1(std::set<std::tuple<ll, ll>> &result) {
    for (auto &first : coord_antennas) {
      for (auto &second : coord_antennas) {
        if (first == second) {
          continue;
        }
        auto [x0, y0] = first;
        auto [x1, y1] = second;
        auto dx = x0 - x1;
        auto dy = y0 - y1;

        {
          auto antinode = first;
          std::get<0>(antinode) += dx;
          std::get<1>(antinode) += dy;
          insert_antinode(antinode, result);
        }
        {
          auto antinode = second;
          std::get<0>(antinode) -= dx;
          std::get<1>(antinode) -= dy;
          insert_antinode(antinode, result);
        }
      }
    }
  }
  void calc_antinodes2(std::set<std::tuple<ll, ll>> &result) {
    for (auto &first : coord_antennas) {
      for (auto &second : coord_antennas) {
        if (first == second) {
          continue;
        }
        auto [x0, y0] = first;
        auto [x1, y1] = second;
        auto dx = x0 - x1;
        auto dy = y0 - y1;

        {
          auto antinode = first;
          do {
            std::get<0>(antinode) += dx;
            std::get<1>(antinode) += dy;
          } while (insert_antinode(antinode, result));
        }
        {
          auto antinode = first;
          do {
            std::get<0>(antinode) -= dx;
            std::get<1>(antinode) -= dy;
          } while (insert_antinode(antinode, result));
        }
      }
    }
  }
};

std::map<char, Antennas> scan() {
  std::map<char, Antennas> result;
  for (ll j = 0; j < input.size(); j++) {
    for (ll i = 0; i < input.at(j).size(); i++) {
      auto c = input.at(j).at(i);
      if (c != '.') {
        result[c].coord_antennas.insert({i, j});
      }
    }
  }
  return result;
}

template <bool with_harmonics> ll calc_antinodes() {
  auto antennas = scan();
  std::set<std::tuple<ll, ll>> result;
  for (auto &[key, value] : antennas) {
    if (with_harmonics) {
      value.calc_antinodes2(result);
    } else {
      value.calc_antinodes1(result);
    }
  }
  return result.size();
}
} // namespace

int main() {
  int64_t result0 = calc_antinodes<false>();
  int64_t result1 = calc_antinodes<true>();

  myprint(result0);
  myprint(result1);
  return 0;
}
