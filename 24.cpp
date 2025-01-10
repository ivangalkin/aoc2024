#include <algorithm>
#include <array>
#include <bitset>
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

std::map<std::string, std::optional<ll>> data_real{
    {"x00", 1}, {"x01", 0}, {"x02", 1}, {"x03", 1}, {"x04", 0}, {"x05", 0},
    {"x06", 1}, {"x07", 1}, {"x08", 0}, {"x09", 1}, {"x10", 1}, {"x11", 1},
    {"x12", 1}, {"x13", 1}, {"x14", 1}, {"x15", 0}, {"x16", 0}, {"x17", 1},
    {"x18", 0}, {"x19", 1}, {"x20", 1}, {"x21", 0}, {"x22", 1}, {"x23", 0},
    {"x24", 0}, {"x25", 1}, {"x26", 0}, {"x27", 0}, {"x28", 1}, {"x29", 0},
    {"x30", 0}, {"x31", 1}, {"x32", 1}, {"x33", 0}, {"x34", 1}, {"x35", 1},
    {"x36", 0}, {"x37", 1}, {"x38", 0}, {"x39", 1}, {"x40", 0}, {"x41", 0},
    {"x42", 0}, {"x43", 1}, {"x44", 1}, {"y00", 1}, {"y01", 0}, {"y02", 0},
    {"y03", 1}, {"y04", 1}, {"y05", 0}, {"y06", 0}, {"y07", 0}, {"y08", 0},
    {"y09", 0}, {"y10", 0}, {"y11", 1}, {"y12", 0}, {"y13", 0}, {"y14", 1},
    {"y15", 1}, {"y16", 1}, {"y17", 0}, {"y18", 1}, {"y19", 1}, {"y20", 0},
    {"y21", 0}, {"y22", 1}, {"y23", 0}, {"y24", 1}, {"y25", 0}, {"y26", 1},
    {"y27", 0}, {"y28", 0}, {"y29", 0}, {"y30", 0}, {"y31", 0}, {"y32", 1},
    {"y33", 0}, {"y34", 0}, {"y35", 1}, {"y36", 0}, {"y37", 0}, {"y38", 1},
    {"y39", 1}, {"y40", 0}, {"y41", 1}, {"y42", 0}, {"y43", 0}, {"y44", 1},
};

enum OP { AND, OR, XOR };

static const char *op_to_string(OP op) {
  switch (op) {
  case AND:
    return "AND";
  case OR:
    return "OR";
  case XOR:
    return "XOR";
  }
  assert(false);
};

struct Gate {
  Gate(std::string input0, OP op, std::string input1, std::string output)
      : _op{op}, _inputs{{
                     {input0, std::nullopt},
                     {input1, std::nullopt},
                 }},
        _output{output, std::nullopt} {}

  bool calculate() {
    if (auto output = _output.second) {
      return true;
    }
    auto &[key0, value0] = _inputs.at(0);
    auto &[key1, value1] = _inputs.at(1);

    if (value0 && value1) {
      switch (_op) {
      case AND:
        _output.second = *value0 & *value1;
        break;
      case OR:
        _output.second = *value0 | *value1;
        break;
      case XOR:
        _output.second = *value0 ^ *value1;
        break;
      }
      return true;
    }
    return false;
  }

  const auto &getOutput() { return _output; }

  std::string print() const {
    return (std::ostringstream()
            << "{" << _inputs.at(0).first << " " << op_to_string(_op) << " "
            << _inputs.at(1).first << " -> " << _output.first << "}")
        .str();
  }

  void setInput(const std::tuple<std::string, std::optional<ll>> &value) {
    if (_output.second) {
      return;
    }
    auto &[k, v] = value;
    if (_inputs.at(0).first == k) {
      _inputs.at(0).second = v;
    } else if (_inputs.at(1).first == k) {
      _inputs.at(1).second = v;
    }
  }

  auto operator<=>(const Gate &) const = default;

  OP _op;
  std::array<std::pair<std::string, std::optional<ll>>, 2> _inputs;
  std::pair<std::string, std::optional<ll>> _output;
};

const std::vector<Gate> original_gates{

    {"mrh", XOR, "bnc", "z32"}, {"y14", XOR, "x14", "vvw"},
    {"bjt", XOR, "mmm", "z42"}, {"y41", AND, "x41", "gwr"},
    {"sbs", AND, "vbj", "kpf"}, {"x01", XOR, "y01", "rbr"},
    {"jkf", XOR, "kmf", "z21"}, {"x25", XOR, "y25", "knp"},
    {"y05", AND, "x05", "jcj"}, {"qpn", OR, "gmv", "krq"},
    {"x19", AND, "y19", "mfq"}, {"mrh", AND, "bnc", "rvw"},
    {"wrg", XOR, "mjr", "z44"}, {"y10", XOR, "x10", "gtn"},
    {"y42", AND, "x42", "dmw"}, {"wmj", OR, "pft", "tkg"},
    {"x13", AND, "y13", "qkc"}, {"y05", XOR, "x05", "tjs"},
    {"pmk", XOR, "vqg", "z36"}, {"tcg", OR, "fbd", "z45"},
    {"y33", AND, "x33", "wmj"}, {"sqs", OR, "thj", "sch"},
    {"y16", AND, "x16", "hbc"}, {"y09", XOR, "x09", "svf"},
    {"mjb", OR, "bbc", "bhq"},  {"dvf", XOR, "fdj", "z33"},
    {"x34", AND, "y34", "pbp"}, {"y44", XOR, "x44", "mjr"},
    {"x28", XOR, "y28", "qdq"}, {"qkc", OR, "crp", "mgc"},
    {"vgn", AND, "wfn", "khj"}, {"rwc", OR, "svg", "dng"},
    {"y33", XOR, "x33", "dvf"}, {"y29", XOR, "x29", "fqc"},
    {"vqg", AND, "pmk", "stq"}, {"rbr", XOR, "rnv", "z01"},
    {"x37", XOR, "y37", "kbh"}, {"x35", AND, "y35", "nsb"},
    {"hqn", XOR, "kbh", "z37"}, {"ftq", XOR, "fqc", "z29"},
    {"y21", XOR, "x21", "jkf"}, {"y39", XOR, "x39", "vvc"},
    {"x16", XOR, "y16", "gnc"}, {"x41", XOR, "y41", "dgn"},
    {"y12", XOR, "x12", "nvv"}, {"dmw", OR, "hgm", "cjb"},
    {"crb", OR, "bgw", "mrh"},  {"stq", OR, "cfj", "hqn"},
    {"qdh", XOR, "bhq", "z13"}, {"svf", XOR, "thf", "z09"},
    {"skb", OR, "qdj", "nbm"},  {"x24", AND, "y24", "pwp"},
    {"x07", XOR, "y07", "gpb"}, {"qsj", OR, "khj", "qvs"},
    {"y30", XOR, "x30", "rdj"}, {"x20", XOR, "y20", "vtd"},
    {"qmm", XOR, "svb", "z26"}, {"y20", AND, "x20", "tsn"},
    {"pbp", OR, "cpb", "ngc"},  {"cct", AND, "pvb", "jnk"},
    {"y06", AND, "x06", "nfr"}, {"gnc", AND, "nbm", "mfr"},
    {"tkg", XOR, "bpm", "z34"}, {"sbs", XOR, "vbj", "vkq"},
    {"srj", OR, "rvr", "wfn"},  {"y04", XOR, "x04", "brf"},
    {"x21", AND, "y21", "drv"}, {"mmk", AND, "knp", "jss"},
    {"x22", AND, "y22", "rvr"}, {"y27", AND, "x27", "srb"},
    {"vvc", AND, "hth", "qvm"}, {"mdm", OR, "hqh", "hth"},
    {"bjr", AND, "cjb", "wgc"}, {"prm", XOR, "jps", "z18"},
    {"hpg", AND, "ssv", "jvt"}, {"ngc", XOR, "mqw", "z35"},
    {"gbw", XOR, "vjb", "z02"}, {"jbf", OR, "ptp", "ghq"},
    {"pwp", OR, "cwc", "z24"},  {"hkh", OR, "nst", "gnn"},
    {"fkb", XOR, "vrp", "z03"}, {"svb", AND, "qmm", "jbf"},
    {"y09", AND, "x09", "thj"}, {"hdk", AND, "gpb", "gmv"},
    {"gnn", AND, "brf", "wfw"}, {"knv", OR, "nfr", "hdk"},
    {"mgc", XOR, "vvw", "z14"}, {"rbp", OR, "qvm", "ssv"},
    {"y34", XOR, "x34", "bpm"}, {"qvs", AND, "kmc", "cwc"},
    {"hqp", OR, "nbf", "gbw"},  {"svf", AND, "thf", "sqs"},
    {"y30", AND, "x30", "svg"}, {"vgs", OR, "gwr", "bjt"},
    {"y28", AND, "x28", "pvb"}, {"y17", AND, "x17", "jcs"},
    {"bsv", OR, "vrn", "vrp"},  {"jpk", OR, "rvw", "fdj"},
    {"x11", AND, "y11", "z11"}, {"vwh", XOR, "dgn", "z41"},
    {"y08", AND, "x08", "wwb"}, {"wrg", AND, "mjr", "tcg"},
    {"hbc", OR, "mfr", "mjp"},  {"knp", XOR, "mmk", "z25"},
    {"y44", AND, "x44", "fbd"}, {"y15", XOR, "x15", "mjc"},
    {"x32", XOR, "y32", "bnc"}, {"x04", AND, "y04", "qvq"},
    {"ssg", XOR, "shm", "z22"}, {"ghq", XOR, "fnc", "z27"},
    {"x10", AND, "y10", "jmb"}, {"y32", AND, "x32", "jpk"},
    {"y07", AND, "x07", "qpn"}, {"ngc", AND, "mqw", "hrj"},
    {"x43", AND, "y43", "cts"}, {"vmb", AND, "mjc", "skb"},
    {"sch", XOR, "gtn", "z10"}, {"rnv", AND, "rbr", "nbf"},
    {"frv", AND, "rdj", "rwc"}, {"tjs", XOR, "ncd", "z05"},
    {"qbd", OR, "jcs", "jps"},  {"prm", AND, "jps", "hrb"},
    {"qdq", OR, "jnk", "ftq"},  {"x29", AND, "y29", "jft"},
    {"y40", AND, "x40", "pqh"}, {"gtn", AND, "sch", "kbf"},
    {"wmp", XOR, "mft", "z19"}, {"tcj", AND, "mjp", "qbd"},
    {"dvf", AND, "fdj", "pft"}, {"nkj", OR, "drv", "shm"},
    {"jcj", OR, "kfn", "cpw"},  {"cpw", XOR, "gqf", "z06"},
    {"jss", OR, "qwb", "svb"},  {"x02", XOR, "y02", "vjb"},
    {"cts", OR, "wgc", "wrg"},  {"nmq", OR, "jhd", "vmb"},
    {"mks", XOR, "nvv", "z12"}, {"jmb", OR, "kbf", "sbs"},
    {"vkm", OR, "wwb", "thf"},  {"qhh", OR, "jft", "frv"},
    {"jpf", OR, "cdf", "dkp"},  {"x36", XOR, "y36", "vqg"},
    {"nbm", XOR, "gnc", "z16"}, {"gqf", AND, "cpw", "knv"},
    {"ghg", OR, "mfq", "gnk"},  {"y38", AND, "x38", "mdm"},
    {"y23", XOR, "x23", "vgn"}, {"pqh", OR, "jvt", "vwh"},
    {"vtd", AND, "gnk", "hbb"}, {"x18", AND, "y18", "sds"},
    {"x02", AND, "y02", "bsv"}, {"ssv", XOR, "hpg", "z40"},
    {"qvs", XOR, "kmc", "mmk"}, {"y26", AND, "x26", "ptp"},
    {"qdh", AND, "bhq", "crp"}, {"y12", AND, "x12", "bbc"},
    {"y23", AND, "x23", "qsj"}, {"y37", AND, "x37", "cdf"},
    {"hth", XOR, "vvc", "z39"}, {"pkp", OR, "srb", "cct"},
    {"fnc", AND, "ghq", "pkp"}, {"x18", XOR, "y18", "prm"},
    {"y43", XOR, "x43", "bjr"}, {"x26", XOR, "y26", "qmm"},
    {"kbh", AND, "hqn", "jpf"}, {"x08", XOR, "y08", "gjd"},
    {"vwh", AND, "dgn", "vgs"}, {"x27", XOR, "y27", "fnc"},
    {"gnn", XOR, "brf", "z04"}, {"kpf", OR, "vkq", "mks"},
    {"frv", XOR, "rdj", "z30"}, {"y25", AND, "x25", "qwb"},
    {"ftq", AND, "fqc", "qhh"}, {"gjd", AND, "krq", "vkm"},
    {"x35", XOR, "y35", "mqw"}, {"y06", XOR, "x06", "gqf"},
    {"x15", AND, "y15", "qdj"}, {"tjs", AND, "ncd", "kfn"},
    {"nvv", AND, "mks", "mjb"}, {"dng", XOR, "pwd", "z31"},
    {"mjc", XOR, "vmb", "z15"}, {"hdk", XOR, "gpb", "z07"},
    {"y36", AND, "x36", "cfj"}, {"y39", AND, "x39", "rbp"},
    {"y03", AND, "x03", "nst"}, {"dng", AND, "pwd", "crb"},
    {"x03", XOR, "y03", "fkb"}, {"mgc", AND, "vvw", "nmq"},
    {"x31", AND, "y31", "bgw"}, {"y13", XOR, "x13", "qdh"},
    {"wfw", OR, "qvq", "ncd"},  {"x22", XOR, "y22", "ssg"},
    {"x11", XOR, "y11", "vbj"}, {"bjr", XOR, "cjb", "z43"},
    {"x17", XOR, "y17", "tcj"}, {"pvb", XOR, "cct", "z28"},
    {"tsn", OR, "hbb", "kmf"},  {"y38", XOR, "x38", "vsb"},
    {"x42", XOR, "y42", "mmm"}, {"bjt", AND, "mmm", "hgm"},
    {"hrb", OR, "sds", "mft"},  {"x24", XOR, "y24", "kmc"},
    {"vtd", XOR, "gnk", "z20"}, {"y00", AND, "x00", "rnv"},
    {"wfn", XOR, "vgn", "z23"}, {"vsb", AND, "dkp", "z38"},
    {"y00", XOR, "x00", "z00"}, {"mjp", XOR, "tcj", "z17"},
    {"shm", AND, "ssg", "srj"}, {"dkp", XOR, "vsb", "hqh"},
    {"vrp", AND, "fkb", "hkh"}, {"gjd", XOR, "krq", "z08"},
    {"vjb", AND, "gbw", "vrn"}, {"kmf", AND, "jkf", "nkj"},
    {"x14", AND, "y14", "jhd"}, {"y31", XOR, "x31", "pwd"},
    {"x01", AND, "y01", "hqp"}, {"y40", XOR, "x40", "hpg"},
    {"nsb", OR, "hrj", "pmk"},  {"bpm", AND, "tkg", "cpb"},
    {"y19", XOR, "x19", "wmp"}, {"wmp", AND, "mft", "ghg"},
};

constexpr ll INPUT_SIZE = 45;
constexpr ll OUTPUT_SIZE = INPUT_SIZE + 1;

using ull = unsigned ll;

std::string getID(char c, int nr) {
#pragma GCC diagnostic ignored "-Wformat-truncation"
  char buffer[4]{};
  snprintf(buffer, sizeof(buffer), "%c%02d", c, nr);
  return buffer;
}

struct Context {
  std::vector<Gate> _gates;
  std::map<std::string, Gate> _output_map;

  std::vector<std::string> _swaps;

  ll _correct_bit = 0;
  std::set<Gate> _correct_gates;

  void init() {
    _output_map.clear();

    for (auto &gate : _gates) {
      auto [it, inserted] =
          _output_map.insert(std::make_pair(gate._output.first, gate));
      assert(inserted);
    }
  }

  ull calculate(ull _x, ull _y) {
    std::bitset<64> x(_x), y(_y);

    std::map<std::string, std::optional<ll>> data_ready;
    for (auto i = 0; i < INPUT_SIZE; i++) {
      data_ready[getID('x', i)] = x[i];
    }
    for (auto i = 0; i < INPUT_SIZE; i++) {
      data_ready[getID('y', i)] = y[i];
    }

    for (auto &gate : _gates) {
      gate._inputs.at(0).second = std::nullopt;
      gate._inputs.at(1).second = std::nullopt;
      gate._output.second = std::nullopt;
    }

    // for (auto& [key, value]: data_ready) {
    //   std::cout << "{" << key << "," << *value << "} ";
    // }
    // std::cout << std::endl;

    ll stuck_counter = 0;
    std::vector<std::optional<ll>> Zs;
    do {
      Zs = std::vector<std::optional<ll>>(OUTPUT_SIZE, std::nullopt);
      std::map<std::string, std::optional<ll>> new_data_ready;
      for (auto &gate : _gates) {
        for (auto &d : data_ready) {
          gate.setInput(d);
        }
      }

      for (auto &gate : _gates) {

        if (gate.calculate()) {
          auto &output = gate.getOutput();
          new_data_ready.insert(output);
          if (output.first.starts_with("z")) {
            Zs.at(strtol(output.first.data() + 1, nullptr, 10)) =
                *(output.second);
          }
        }
      }

      if (std::all_of(Zs.begin(), Zs.end(), [](const std::optional<ll> &z) {
            return static_cast<bool>(z);
          })) {
        break;
      }

      if (new_data_ready == data_ready) {
        ++stuck_counter;
      } else {
        stuck_counter = 0;
      }

      if (stuck_counter > 10) {
        return INT64_MAX;
      }

      data_ready = std::move(new_data_ready);
    } while (true);

    std::bitset<OUTPUT_SIZE> result(0);
    for (ll i = 0; i < Zs.size(); i++) {
      result[i] = *Zs.at(i);
    }

    return result.to_ullong();
  }

  void print_dotty() const {

    std::cout << "graph graphname {" << std::endl;
    for (auto &gate : _gates) {
      auto gate_id = std::to_string((uintptr_t)&gate);
      std::cout << gate_id << "[label = " << op_to_string(gate._op)
                << ", shape = box];" << std::endl;
      std::cout << gate._inputs.at(0).first << " -- " << gate_id << ";"
                << std::endl;
      std::cout << gate._inputs.at(1).first << " -- " << gate_id << ";"
                << std::endl;
      std::cout << gate_id << " -- " << gate._output.first << ";" << std::endl;
    }
    std::cout << "}" << std::endl;
  }

  std::set<Gate> get_involved_gates(const std::string &output) const {
    std::set<Gate> involved_gates;
    std::vector<std::string> queue{output};
    do {
      auto current = std::move(queue.back());
      queue.pop_back();

      auto current_it = _output_map.find(current);
      if (current_it == _output_map.end()) {
        assert(current.starts_with("x") || current.starts_with("y"));
        continue;
      }
      auto current_gate = current_it->second;
      auto input0 = current_gate._inputs.at(0).first;
      auto input1 = current_gate._inputs.at(1).first;

      involved_gates.insert(std::move(current_gate));

      queue.push_back(std::move(input0));
      queue.push_back(std::move(input1));

    } while (!queue.empty());

    return involved_gates;
  }

  Context swap_outputs(const std::string &o1, const std::string &o2) const {
    Context new_context;
    new_context._gates = _gates;
    new_context._swaps = _swaps;
    new_context._swaps.push_back(o1);
    new_context._swaps.push_back(o2);

    Gate *other_g1 = nullptr, *other_g2 = nullptr;
    for (auto &other : new_context._gates) {
      if (other._output.first == o1) {
        other_g1 = &other;
      } else if (other._output.first == o2) {
        other_g2 = &other;
      }
      if (other_g1 && other_g2)
        break;
    }

    if (!other_g1 || !other_g2) {
      assert(false);
    }

    other_g1->_output = {o2, std::nullopt};
    other_g2->_output = {o1, std::nullopt};

    new_context.init();
    return new_context;
  }

  bool check(ull input_bit, bool x_value, bool y_value, int mode) {
    std::bitset<INPUT_SIZE> x(0), y(0);
    if (mode == 0) {
      x[input_bit] = x_value;
      y[input_bit] = y_value;
    } else if (mode == 1) {
      for (ll i = 0; i <= input_bit; i++) {
        x[i] = x_value;
      }
      for (ll i = 0; i <= input_bit; i++) {
        y[i] = y_value;
      }
    } else if (mode == 2) {
      bool x_flag = x_value;
      for (ll i = 0; i <= input_bit; i++) {
        x[i] = x_flag;
        x_flag = !x_flag;
      }
      bool y_flag = y_value;
      for (ll i = 0; i <= input_bit; i++) {
        y[i] = y_flag;
        y_flag = !y_flag;
      }
    } else {
      assert(false);
    }

    auto r = calculate(x.to_ullong(), y.to_ullong());
    auto valid = (x.to_ullong() + y.to_ullong() == r);
    //  std::cout << x.to_ullong() << "\t+\t" << y.to_ullong() << "\t=\t"
    //            << (ll)r << "\tvs\t"
    //            << (x.to_ullong() + y.to_ullong()) << "\t" << valid <<
    //            std::endl;

    return valid;
  }

  bool check_i(ll i) {
    std::vector<std::function<bool()>> checks{
        [i, this]() { return check(i, false, false, 0); },
        [i, this]() { return check(i, false, true, 0); },
        [i, this]() { return check(i, true, false, 0); },
        [i, this]() { return check(i, true, true, 0); },
        [i, this]() { return check(i, false, true, 1); },
        [i, this]() { return check(i, true, false, 1); },
        [i, this]() { return check(i, true, true, 1); },
        // [i, this]() { return check(i, false, false, 2); },
        // [i, this]() { return check(i, false, true, 2); },
        // [i, this]() { return check(i, true, false, 2); },
        // [i, this]() { return check(i, true, true, 2); },

    };
    return std::all_of(checks.begin(), checks.end(),
                       [](auto val) { return val(); });
  }

  bool check_0_i(ll i) {
    for (ll j = 0; j <= i; j++) {
      auto res = check_i(j);
      if (!res)
        return false;
    }
    return true;
  }

  void print_swaps() {
    std::sort(_swaps.begin(), _swaps.end());
    for (const auto &s : _swaps) {
      std::cout << s << ",";
    }
    std::cout << std::endl;
  }
};

auto &data = data_real;

} // namespace

int main() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  {
    Context context;
    context._gates = original_gates;
    context.init();
    std::bitset<INPUT_SIZE> x(0), y(0);

    for (auto &[key, value] : data) {
      auto index = strtoul(key.data() + 1, nullptr, 10);
      if (key.starts_with("x")) {
        x[index] = *value;
      } else if (key.starts_with("y")) {
        y[index] = *value;
      } else {
        assert(false);
      }
    }

    result0 = context.calculate(x.to_ullong(), y.to_ullong());
    myprint(result0);
  }

  Context ctx;
  ctx._gates = original_gates;
  ctx.init();
  std::vector<Context> queue = {ctx};

  // This is a a DFS with some heuristics. It checks the gates only in a close
  // range and avoids already validates gates. Runtime is around 1 minute. One
  // of the improvements might be to start with the gates which
  // 1. Output "zxx" & are not the last gate (?)
  // 2. Have anything but XOR in it
  do {
    auto context = std::move(queue.back());
    queue.pop_back();

    if (context._correct_bit == INPUT_SIZE - 1) {
      std::cout << "FINISH!!!!!" << std::endl;
      context.print_swaps();
      return 0;
    }

    for (ull i = context._correct_bit; i < INPUT_SIZE; i++) {
      std::set<Gate> involved_gates_i =
          context.get_involved_gates(getID('z', i));
      if (context.check_i(i)) {
        context._correct_gates.insert(
            std::make_move_iterator(involved_gates_i.begin()),
            std::make_move_iterator(involved_gates_i.end()));

        if (i == INPUT_SIZE - 1) {
          std::cout << "FINISH!!!!!" << std::endl;
          context.print_swaps();
          return 0;
        }

      } else {
        std::cout << "ERROR on "
                  << "x/y" << std::setw(2) << std::setfill('0') << (int)i
                  << std::endl;
        std::set<Gate> involved_gates_all;
        ll min = std::max<ll>(0, i);
        ll max = std::min<ll>(OUTPUT_SIZE - 1, i + 3);
        for (auto j = min; j != max; j++) {
          auto involved_gates_im1 = context.get_involved_gates(getID('z', j));
          involved_gates_all.insert(
              std::make_move_iterator(involved_gates_im1.begin()),
              std::make_move_iterator(involved_gates_im1.end()));
        }

        std::vector<Gate> questionable_gates;

        std::set_difference(
            involved_gates_all.begin(), involved_gates_all.end(),
            context._correct_gates.begin(), context._correct_gates.end(),
            std::back_inserter(questionable_gates));

        for (auto &g : questionable_gates) {
          std::cout << g.print() << " ";
        }
        std::cout << std::endl;

        for (ll g1i = 0; g1i < questionable_gates.size() - 1; g1i++) {
          for (ll g2i = g1i + 1; g2i < questionable_gates.size(); g2i++) {
            auto &g1 = questionable_gates.at(g1i);
            auto &g2 = questionable_gates.at(g2i);
            // std::cout << "swap " << g1.print() << " " << g2.print();
            // if (!context._swaps.empty()) {
            //   std::cout << " existing swaps ";
            //   context.print_swaps();
            // } else {
            //   std::cout << std::endl;
            // }

            const auto &o1 = g1._output.first;
            const auto &o2 = g2._output.first;
            auto new_context = context.swap_outputs(o1, o2);

            if (new_context.check_i(i)) {
              std::cout << "successfull swap " << g1.print() << " "
                        << g2.print() << std::endl;
              new_context._correct_bit = i;
              for (auto j = 0; j <= i; j++) {
                auto involved_gates_im1 =
                    new_context.get_involved_gates(getID('z', j));
                new_context._correct_gates.insert(
                    std::make_move_iterator(involved_gates_im1.begin()),
                    std::make_move_iterator(involved_gates_im1.end()));
              }
              queue.push_back(std::move(new_context));
            }
          }
        }
        break;
      }
    }

  } while (!queue.empty());

  myprint(result1);
  return 0;
}
