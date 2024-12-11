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

#define ASSERT_EQ(a, b) \
   do { __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     if (_a != _b)       \
     {                 \
       std::cout << _a << " != " << _b << std::endl; \
       assert(0);                  \
     }                  \
     }while(0)

#define myprint(arg) do { std::cout << "" #arg << " = " << arg << std::endl; } while(0)

using ll = int64_t;

namespace {

    std::vector<ll> input_real {0,44,175060,3442,593,54398,9,8101095};

    decltype(input_real) input_test;
//    auto &input = input_test;
    auto &input = input_real;

    std::map<std::tuple<ll, ll>, ll> memory; // {id, blinks} -> number of stones

    ll calculate(ll stone, ll depth) {
      if (depth == 0) {
        return 1;
      }
      const auto memory_key = std::make_tuple(stone, depth);
      if (auto it = memory.find(memory_key); it != memory.end()) {
        return it->second;
      }

      if (stone == 0) {
        auto ret = calculate(1, depth - 1);
        memory[memory_key] = ret;
        return ret;
      }
      auto stone_str = std::to_string(stone);
      auto stone_len = stone_str.length();
      if (stone_len % 2 == 0) {
        auto stone1 =
            strtoll(stone_str.substr(0, stone_len / 2).c_str(), 0, 10);
        auto stone2 = strtoll(
            stone_str.substr(stone_len / 2, stone_len / 2).c_str(), 0, 10);

        auto ret1 = calculate(stone1, depth - 1);
        auto ret2 = calculate(stone2, depth - 1);
        memory[memory_key] = ret1 + ret2;
        return ret1 + ret2;
      }

      auto ret = calculate(stone * 2024, depth - 1);
      memory[memory_key] = ret;
      return ret;
    }
}

int main() {
    int64_t result0 = 0;
    int64_t result1 = 0;

    for (auto i : input) {
      result0 += calculate(i, 25);
    }
    for (auto i : input) {
      result1 += calculate(i, 75);
    }

    myprint(result0);
    myprint(result1);
    return 0;
}
