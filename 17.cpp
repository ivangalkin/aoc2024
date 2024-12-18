#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <sstream>
#include <tuple>
#include <valarray>
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

std::vector<ll> input_real{2, 4, 1, 1, 7, 5, 1, 5, 4, 2, 5, 5, 0, 3, 3, 0};

enum Register { A = 0, B, C };
std::array<ll, 3> registers_real{
    28422061,
    0,
    0,
};

decltype(input_real) input_test{0, 1, 5, 4, 3, 0};
//    auto &input = input_test;
auto &INPUT = input_real;

decltype(registers_real) registers_test{
    729,
    0,
    0,
};
//    auto &registers = registers_test;
auto &REGISTERS = registers_real;

ll interpret(ll opcode, ll operand, ll pc, std::vector<ll> &output,
             std::array<ll, 3> &registers) {

  auto combo = [&registers, operand]() {
    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
      return operand;
    case 4:
      return registers[A];
    case 5:
      return registers[B];
    case 6:
      return registers[C];
    case 7:
      assert(false);
    }
    assert(false);
  };

  switch (opcode) {
  case 0: {
    ll p = std::pow(std::valarray<ll>{2}, std::valarray<ll>{combo()})[0];
    registers[A] = registers[A] / p;
    return pc + 2;
  }
  case 1: {
    registers[B] ^= operand;
    return pc + 2;
  }
  case 2: {
    registers[B] = combo() % 8;
    return pc + 2;
  }
  case 3: {
    if (registers[A] == 0) {
      return pc + 2;
    } else {
      return operand;
    }
  }
  case 4: {
    registers[B] = registers[B] ^ registers[C];
    return pc + 2;
  }
  case 5: {
    output.push_back(combo() % 8);
    return pc + 2;
  }
  case 6: {
    ll p = std::pow(std::valarray<ll>{2}, std::valarray<ll>{combo()})[0];
    registers[B] = registers[A] / p;
    return pc + 2;
  }
  case 7: {
    ll p = std::pow(std::valarray<ll>{2}, std::valarray<ll>{combo()})[0];
    registers[C] = registers[A] / p;
    return pc + 2;
  }
  }
  assert(false);
}

std::vector<ll> run(const std::vector<ll> &input, std::array<ll, 3> registers) {
  std::vector<ll> output;
  ll pc = 0;
  while (pc < input.size()) {
    ll opcode = input.at(pc);
    ll operand = input.at(pc + 1);
    pc = interpret(opcode, operand, pc, output, registers);
  }
  return output;
}

std::vector<ll> run(const std::vector<ll> &input, std::array<ll, 3> registers,
                    const std::vector<ll> &reference_output) {
  std::vector<ll> output;
  ll pc = 0;
  while (pc < input.size()) {
    ll opcode = input.at(pc);
    ll operand = input.at(pc + 1);
    pc = interpret(opcode, operand, pc, output, registers);
    if (!output.empty()) {
      if (output.size() > reference_output.size()) {
        return {};
      }
      if (!std::equal(output.begin(), output.end(), reference_output.begin())) {
        return {};
      }
    }
  }
  return output;
}

void print(const std::vector<ll> &output) {
  std::copy(output.begin(), std::prev(output.end()),
            std::ostream_iterator<ll>(std::cout, ","));
  std::cout << output.back() << std::endl;
}

} // namespace

int main() {

  print(run(INPUT, REGISTERS));

  ll new_A = 0;

  while (true) {
    auto registers = REGISTERS;
    registers[A] = new_A;
    auto output = run(INPUT, registers, INPUT);
    if (output == INPUT) {
      myprint(new_A);
      return 0;
    }
    ++new_A;
    if (new_A % 1000000 == 0) {
      std::cout << new_A << " ";
    }
  }

  return 0;
}
