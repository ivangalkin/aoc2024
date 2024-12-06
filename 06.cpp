#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
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
    "........#.............................#......#................#..........."
    ".......#..................#.........#.#.#...............",
    "...........................................#..#......................#...."
    "........................#...........................#.#.",
    ".............#..........#........#.#...........#........................#."
    "...........................##...........................",
    "............#.............#.....................................#........."
    "...............#.....#..................................",
    ".........#...........#................#................................#.."
    "....#.....................#.............#..............#",
    "...........................##............................................."
    "..............................................#.........",
    "...........#.......#......................................................"
    "...........#..............#....................#........",
    ".......................#.............................................#...."
    ".....................................#.#..............#.",
    ".#...................#..................#...........#...#.........#...##.."
    "........................................................",
    ".................#..........#.....#.........#............................."
    "........................................#..........##...",
    "....#.#............#..........#.......................#..................."
    "......#.................#.........#.............#....#..",
    "...#....................................#.............#..................."
    "...........#............#.....................#........#",
    "....................#..............................#...#.#...#.#.........."
    "#.................................#..................#..",
    ".........................................................................."
    "..............#.....#.........#............#.........#..",
    "...................#.................#...................................."
    "...................................................#...#",
    "..............#.......#..................#........#....#........#........."
    "............#..........................#................",
    "...........#..#....................................#.............#.#..#..."
    "....................................#.........#.#...#...",
    "...#.............#............................#..............#............"
    "........#.#.............................................",
    "..#...........#.#.........#..............................................."
    "#...#...............#.#...........#........##....#......",
    ".............................................#..#.........#......#........"
    "........................................................",
    ".................................#.................#..............#.....#."
    "..................................................#.....",
    "............................#.......#............#........................"
    ".......................................#................",
    ".....#....................#...........................................#..."
    ".......................#..........#..#...#......#...#...",
    "........................#......#...#.......................#....##.......#"
    "..........#...............#.............................",
    "#..#......................................................................"
    "..............................#.........................",
    "...........................................#......#......................."
    "...#..............................#.............#.....#.",
    "..............#......................#..#................................."
    "..#.#..................#.......#............#...........",
    ".................#...................................#..........#......#.."
    "..#.#.#...#....................#..........#......#......",
    "........#....................................#........#..................."
    "......................#......#.#...............#......#.",
    "..................................#......#........#........#.#......#....."
    "....................#.#.......#......................#..",
    "......#..#.........#............#........................................."
    "..................#.............#.........#.............",
    ".........................#......................#.....#........#.........."
    "#.......................................................",
    "#.......#..................#.............................................."
    "..............#.........................................",
    ".........#.....#.............#...............#......#....................."
    "#.......................................................",
    ".........#..#.........................................................#..."
    "......##..................##........#...................",
    ".#.....#..............#..............#...................................."
    ".....#.....................................#............",
    "..............................#..........................................."
    "...........................................#............",
    "..............#..........................#................................"
    "#.#.....#...........#.........#.........................",
    "....................#...#.#..............................................."
    "............................#...........#...............",
    "...........#.............................#....................#........#.."
    ".............................##....#....................",
    ".....................#......................#.#.....#....................."
    "......#.......#........#................................",
    "#..........#...............#.......#..................................#..."
    "..................................................##....",
    ".........................................................#...#....#......."
    "........................................#.........##....",
    ".....................#......................#..............#.............."
    "....................................#...................",
    "......#.............#........#............................................"
    "......#...#.............................#......#........",
    "....................#............#........#...............#......#.......#"
    "........................................................",
    ".........................................................................."
    "#........................#......#.............#.......#.",
    ".....................................................#..#........#........"
    "............#.....................#.....................",
    "..#.................#........................................#............"
    "....................................##...............#..",
    ".............#......#.........#..........................................."
    ".....................................#..................",
    "#......#.................................................................."
    ".....................................#......#...........",
    ".......##.......................#...................#.........##.........."
    "#.............................#........................#",
    "...........................................................#.............."
    "..................#...............#............##.......",
    "..........................#...................#..........................."
    "................................#.............#........#",
    "...#......................#..##..........................................."
    ".....................................................#..",
    "............#..#.........#...#............................................"
    ".............#........#..............#..................",
    ".................#.................#........#............................."
    "...............................................#........",
    "............#..#..#..#....#...........................#..................."
    "..............................#..#...................#..",
    "....................................................#..#.................."
    "...............#.#..............................#.......",
    ".........#.#................................................#..#.........."
    "..................................................#.....",
    "...##............................................#.....#.#................"
    "...........#....#.................#.#..........#........",
    "...............#.#.#.........................................#......#....."
    "#..............................................#....#...",
    ".............#........................................#....#.............."
    ".........................#...#....#.....................",
    "...........#.................................#............................"
    "...................#...........#..#..#......#...........",
    "#.......................................###....#....#....................."
    "....................#......#.............#..............",
    "...............#.#........................................................"
    ".............................#....................#.....",
    "##.........#..............#................................#..#..#........"
    "..#....................#..#..........#.....#............",
    "...................#..........................................#..........."
    ".............#.......................................#..",
    "#........#.#.....#........................................................"
    "....##......#....#...........................#..........",
    "...............##....#.............#......................................"
    "#......................#...................#.#..........",
    "....................................##....#..............................."
    "..............#..........#...................#....#.....",
    ".....#...............#........#..............#.............#..#..#...#...."
    ".............................................#.#...##...",
    "........##.....................................................#.........."
    "........................................................",
    ".........#.............................................................#.."
    "........................................................",
    ".............#.............#.............................................."
    "..............................#....#..........#.......#.",
    ".#........#...........................................#....#.........#...."
    "..#............#.#................................#....#",
    "...............................................#.......#.............#...."
    ".........#....................#.....................#...",
    "......................................#..................................."
    ".................#...................................#..",
    "....#........#.....................................................#......"
    ".................................##.....................",
    "..........................................#..............................."
    ".............#.......#.....................#...#........",
    "................#.#.............#.....#....................#............#."
    "............................................#...........",
    "..............................#..............#.................#.........."
    ".........#...#.......#..................................",
    ".#...............................................................#........"
    "..........#......#............#................#........",
    "...................................#.................................##..."
    "........................................................",
    "...............................................................#....#..##."
    "..................#..#..............................#...",
    "..............................#...........#..............................."
    "..................#.#....#...............#.....#........",
    "............................#........#.........#.........................."
    "...............#....#...................................",
    "........................#................................................#"
    "....#..............#.........................#..........",
    ".........#....#....................#.......................#.#............"
    "...........................................#............",
    ".........................#................................................"
    "......#.................................................",
    ".............#...#...........#...................#.#..............^......."
    ".................................#....#.................",
    ".................##......................................................."
    "........................................................",
    "..................#......#..............................#...............#."
    "##.........................#............................",
    "....................................................###..................."
    "........................................................",
    "........#....................................................#........#..."
    ".....................................##...#.......#.....",
    ".........................##.....#........................................."
    "................................#.........#.............",
    ".................#........................................................"
    "...................#........#..............#..#.........",
    ".........#.#..................................#..#........................"
    "...........#.................................#..........",
    ".....#............#...#............#..............................#......."
    "...#.........#....#...........#.........................",
    "#...#....................................................................."
    "......................#.....#....#.........#.....#......",
    "......................................................#.#...............#."
    ".....#.................#...............#.............#..",
    ".........................................................................."
    ".............#.........#...#...........#..............#.",
    ".........................#................#.................#............."
    "..................#........#.##....................#....",
    ".....#...#................................#......................#........"
    "...#........................................#..#........",
    ".................#................................#.#....................."
    "#............................................#....#.....",
    "...................#......................................................"
    "......................#........#.....................##.",
    ".....#.................................................................#.."
    "................#........#.......#...#..................",
    "...............................#..#...................................#..."
    ".......#...........#......................#.............",
    "....#................#..................#................................."
    ".........................................#........#.....",
    "......#.........................#........................................."
    "...#....................#....#..........................",
    ".#.......#....#.#...#....#................#........................#......"
    ".............#...................#......#...............",
    "..#...................#......#.#........#.........................#......."
    "..................#............#........................",
    "..#....#...#.............................................................."
    ".........#......................#....................#..",
    ".......#...#............................................................#."
    "................#......................................#",
    "..##..........#..................#...............#.....#..#...........#..."
    ".#...............................................#......",
    "...##....#............##.................................................."
    "................................................#.......",
    "...........#.........................#....#......#...#...................."
    ".........................#....................#........#",
    ".........................................................................."
    "..#...............#..#..............#...................",
    ".....#............................#......................................."
    "..............................................#......#.#",
    ".........#.............................#.....#............................"
    ".............................#.#.....#..................",
    ".......................#..#.#.......#..#................................#."
    "....#..............#.........................#..........",
    ".................#.....................#.................................."
    "..........................................#........#....",
    "........#...............................................................#."
    "...#........#.........#.......#......#......#...........",
    "..............#............#......#..............#.#...........#.........."
    "...................##...##.#..............#.....#.......",
    "##....................................................................#..."
    "....................#.................#.................",
    "............#............................................................."
    "......................................................#.",
    "...#....#....................#............................................"
    "..................................#........#............",
    "....#......................#.............................................."
    "........#...............................................",
    ".#...#...........#....#........#...#.................#...................."
    "..........#................#.##.........................",
    "...#.................#..............................#....................."
    "...........#...........#................................"};

decltype(input_real) input_test{
    "....#.....", ".........#", "..........", "..#.......", ".......#..",
    "..........", ".#..^.....", "........#.", "#.........", "......#..."};
//   auto &input = input_test;
auto &input = input_real;

struct Guard {

  // x, y
  static constexpr std::tuple<ll, ll> DIFF[]{{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
  std::tuple<ll, ll> _current_position;

  enum Direction { UP = 0, RIGHT, DOWN, LEFT, LAST } _direction;
  std::map<std::tuple<ll, ll>, std::set<Direction>> _visited_positions;
  const std::vector<std::string> _map;
  enum Termination { OK, OUT, LOOP };

  Guard(ll x, ll y, Direction direction, std::vector<std::string> map)
      : _current_position{x, y}, _direction{direction}, _map{std::move(map)} {
    _visited_positions[_current_position].insert(_direction);
  }

  Termination do_step() {
    while (true) {
      auto next_position = _current_position;
      auto &[next_x, next_y] = next_position;
      next_x += std::get<0>(DIFF[_direction]);
      next_y += std::get<1>(DIFF[_direction]);

      if (next_x < 0 || next_x >= _map.at(0).size()) {
        return OUT;
      }
      if (next_y < 0 || next_y >= _map.size()) {
        return OUT;
      }
      char c = _map.at(next_y).at(next_x);
      if (c != '#') {
        _current_position = next_position;
        auto [it, not_visited_yet] =
            _visited_positions[_current_position].insert(_direction);
        if (!not_visited_yet) {
          return LOOP;
        }
        return OK;
      } else {
        _direction = (Direction)((_direction + 1) % LAST);
      }
    }
  }

  static Guard create(std::vector<std::string> map) {
    for (int y = 0; y < map.size(); y++) {
      for (int x = 0; x < map.at(y).size(); x++) {
        switch (map.at(y).at(x)) {
        case '^':
          return Guard{x, y, UP, std::move(map)};
        case '>':
          return Guard{x, y, RIGHT, std::move(map)};
        case '<':
          return Guard{x, y, LEFT, std::move(map)};
        case 'v':
          return Guard{x, y, DOWN, std::move(map)};
        }
      }
    }
    __builtin_trap();
  }

  void print_map() {
    for (ll y = 0; y < _map.size(); y++) {
      for (ll x = 0; x < _map.at(y).size(); x++) {
        if (auto it = _visited_positions.find({x, y});
            it != _visited_positions.end()) {
          std::cout << "X";
        } else {
          std::cout << _map.at(y).at(x);
        }
      }
      std::cout << std::endl;
    }
  }
};
} // namespace

int main() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  Guard guard1 = Guard::create(input);
  const Guard original_guard = guard1;

  while (!guard1.do_step()) {
  }
  result0 = guard1._visited_positions.size();

  for (ll y = 0; y < input.size(); y++) {
    for (ll x = 0; x < input.at(y).size(); x++) {
      if (std::tie(x, y) == original_guard._current_position) {
        continue;
      }
      if (input.at(y).at(x) == '#') {
        continue;
      }
      auto map_copy = input;
      map_copy.at(y).at(x) = '#';
      Guard guard2(std::get<0>(original_guard._current_position),
                   std::get<1>(original_guard._current_position),
                   original_guard._direction, std::move(map_copy));
      while (true) {
        auto rc = guard2.do_step();
        if (rc == Guard::LOOP) {
          result1++;
          break;
        } else if (rc == Guard::OUT) {
          break;
        }
      }
    }
  }

  myprint(result0);
  myprint(result1);
  return 0;
}
