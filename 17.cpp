#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
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
//  auto &INPUT = input_test;
auto &INPUT = input_real;

decltype(registers_real) registers_test{
    729,
    0,
    0,
};
// auto &REGISTERS = registers_test;
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
    registers[A] = registers[A] >> combo();
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
    registers[B] = registers[A] >> combo();
    return pc + 2;
  }
  case 7: {
    registers[C] = registers[A] >> combo();
    return pc + 2;
  }
  }
  assert(false);
}

// Translate the given line into C++
// Use static single assignment for optimization.
void translate(ll line, ll opcode, ll operand, std::ostream &os,
               std::array<ll, 3> &ssa) {

  auto SSA_READ = [&ssa](Register r) {
    switch (r) {
    case A:
      return "ra" + std::to_string(ssa[A]);
    case B:
      return "rb" + std::to_string(ssa[B]);
    case C:
      return "rc" + std::to_string(ssa[C]);
    }
    assert(false);
  };

  auto SSA_ASSIGN = [&ssa, SSA_READ](Register r) {
    ++ssa[r];
    return SSA_READ(r);
  };

  auto combo = [operand, SSA_READ]() -> std::string {
    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
      return std::to_string(operand);
    case 4:
      return SSA_READ(A);
    case 5:
      return SSA_READ(B);
    case 6:
      return SSA_READ(C);
    case 7:
      assert(false);
    }
    assert(false);
  };

  switch (opcode) {
  case 0: {

    std::ostringstream s;
    s << " = " << SSA_READ(A) << " >> " << combo() << std::endl;
    os << line << ":\t " << SSA_ASSIGN(A) << s.str();
    return;
  }
  case 1: {
    std::ostringstream s;
    s << " = " << SSA_READ(B) << " ^ " << operand << std::endl;
    os << line << ":\t " << SSA_ASSIGN(B) << s.str();
    return;
  }
  case 2: {
    std::ostringstream s;
    s << " = " << combo() << " & 7ULL" << std::endl;
    os << line << ":\t " << SSA_ASSIGN(B) << s.str();
    return;
  }

  case 3: {
    os << line << ":\t if (" << SSA_READ(A) << " != 0) goto " << operand
       << std::endl;
    return;
  }
  case 4: {
    std::ostringstream s;
    s << " = " << SSA_READ(B) << " ^ " << SSA_READ(C) << std::endl;
    os << line << ":\t " << SSA_ASSIGN(B) << s.str();
    return;
  }
  case 5: {
    os << line << ":\t print(" << combo() << " & 7ULL)" << std::endl;
    return;
  }
  case 6: {
    std::ostringstream s;
    s << " = " << SSA_READ(A) << " >> " << combo() << std::endl;
    os << line << ":\t " << SSA_ASSIGN(B) << s.str();
    return;
  }
  case 7: {
    std::ostringstream s;
    s << " = " << SSA_READ(A) << " >> " << combo() << std::endl;
    os << line << ":\t " << SSA_ASSIGN(C) << s.str();
    return;
  }
  }
  assert(false);
}

// Run interpreted
std::vector<ll> run_i(const std::vector<ll> &input,
                      std::array<ll, 3> registers) {
  std::vector<ll> output;
  ll pc = 0;
  while (pc < input.size()) {
    ll opcode = input.at(pc);
    ll operand = input.at(pc + 1);
    pc = interpret(opcode, operand, pc, output, registers);
  }
  return output;
}

// Run compiled
void run_c(ll a, std::vector<ll> &output) {
  output.clear();
  while (a != 0) {
    auto b = (((a & 7ULL) ^ 1) ^ 5) ^ (a >> ((a & 7ULL) ^ 1));
    output.push_back(b & 7ULL);
    a = a >> 3;
  }
}

// Translate code into C++
void translate(const std::vector<ll> &input) {
  std::array<ll, 3> ssa{0, 0, 0};
  ll i = 0;
  do {
    ll opcode = input.at(i);
    ll operand = input.at(i + 1);
    translate(i, opcode, operand, std::cout, ssa);
    i += 2;
  } while (i < input.size());
}

void print(const std::vector<ll> &output) {
  if (output.empty()) {
    std::cout << "<EMPTY>" << std::endl;
    return;
  }
  std::copy(output.begin(), std::prev(output.end()),
            std::ostream_iterator<ll>(std::cout, ","));
  std::cout << output.back() << std::endl;
}

} // namespace

int main() {

  std::vector<ll> output;
  print(run_i(INPUT, REGISTERS));
  run_c(REGISTERS[A], output);
  print(output);

  translate(INPUT);

  struct Q {
    std::deque<bool> test_bits;
    uint64_t test_value = 0;
    void add(ll bits) {
      while (bits) {
        test_bits.push_back(bits & 1 == 1);
        bits = bits >> 1;
      }

      std::bitset<64> value;
      for (ll i = 0; i < test_bits.size(); i++) {
        value[i] = test_bits[i];
      }
      test_value = value.to_ullong();
    }

    std::vector<ll> run_I() {
      std::array<ll, 3UL> r;
      r.at(A) = test_value;
      r.at(B) = 0;
      r.at(C) = 0;
      auto output = run_i(INPUT, r);
      return output;
    }

    std::vector<ll> run_C() {
      std::vector<ll> output;
      run_c(test_value, output);
      return output;
    }
  };
  std::vector<Q> queue;

  // start test value with max 10 bits
  {
    ll max = (1 << 10) - 1;
    while (max > 0) {
      Q q;
      q.add(max);
      queue.push_back(q);
      max--;
    }
  }

  std::vector<Q> results;
  std::set<ll> checked;

  do {
    auto current = queue.back();
    queue.pop_back();
    auto [it, is_new] = checked.insert(current.test_value);
    if (!is_new)
      continue;

    auto output = current.run_C();

    if (output == INPUT) {
      results.push_back(current);
      myprint(current.test_value);
      continue;
    }

    if (output.size() > INPUT.size()) {
      continue;
    }

    // Since we XOR with more significant bits, we cannot compare
    // the whole output. Let's say all but 2 last output digits
    // must match.
    if (output.size() < 2)
      continue;
    auto one_before_last = std::next(output.begin(), output.size() - 2);
    if (!std::equal(output.begin(), one_before_last, INPUT.begin())) {
      continue;
    }

    // Add up to 7 next bits
    // The more bits we add the more redundant results will be generated
    ll max = (1 << 7) - 1;
    while (max > 0) {
      auto next_q = current;
      next_q.add(max);
      queue.push_back(next_q);
      max--;
    }

  } while (!queue.empty());
  myprint(checked.size());

  uint64_t min_result = -1;
  for (auto &q : results) {
    min_result = std::min(min_result, q.test_value);
  }
  myprint(min_result);

  return 0;
}
