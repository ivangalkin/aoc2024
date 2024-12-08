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
    {88, 54}, {65, 71}, {65, 83}, {11, 57}, {11, 36}, {11, 66}, {83, 67},
    {83, 98}, {83, 88}, {83, 99}, {16, 35}, {16, 43}, {16, 95}, {16, 83},
    {16, 66}, {96, 65}, {96, 53}, {96, 43}, {96, 92}, {96, 66}, {96, 88},
    {55, 89}, {55, 99}, {55, 81}, {55, 16}, {55, 88}, {55, 45}, {55, 54},
    {31, 57}, {31, 83}, {31, 37}, {31, 81}, {31, 87}, {31, 65}, {31, 43},
    {31, 88}, {78, 65}, {78, 45}, {78, 13}, {78, 29}, {78, 55}, {78, 16},
    {78, 33}, {78, 51}, {78, 96}, {15, 51}, {15, 45}, {15, 17}, {15, 78},
    {15, 22}, {15, 13}, {15, 18}, {15, 35}, {15, 37}, {15, 64}, {71, 95},
    {71, 15}, {71, 93}, {71, 76}, {71, 36}, {71, 57}, {71, 42}, {71, 22},
    {71, 12}, {71, 35}, {71, 59}, {37, 29}, {37, 53}, {37, 11}, {37, 89},
    {37, 96}, {37, 82}, {37, 81}, {37, 66}, {37, 57}, {37, 65}, {37, 99},
    {37, 41}, {13, 31}, {13, 37}, {13, 75}, {13, 71}, {13, 16}, {13, 82},
    {13, 86}, {13, 65}, {13, 87}, {13, 17}, {13, 18}, {13, 45}, {13, 96},
    {89, 66}, {89, 57}, {89, 35}, {89, 25}, {89, 53}, {89, 22}, {89, 12},
    {89, 98}, {89, 88}, {89, 91}, {89, 76}, {89, 15}, {89, 67}, {89, 95},
    {93, 18}, {93, 51}, {93, 29}, {93, 87}, {93, 21}, {93, 25}, {93, 96},
    {93, 13}, {93, 75}, {93, 82}, {93, 67}, {93, 86}, {93, 31}, {93, 37},
    {93, 45}, {59, 25}, {59, 42}, {59, 55}, {59, 51}, {59, 64}, {59, 35},
    {59, 21}, {59, 13}, {59, 22}, {59, 12}, {59, 33}, {59, 98}, {59, 18},
    {59, 95}, {59, 93}, {59, 17}, {76, 45}, {76, 95}, {76, 51}, {76, 22},
    {76, 75}, {76, 91}, {76, 17}, {76, 35}, {76, 25}, {76, 18}, {76, 64},
    {76, 21}, {76, 67}, {76, 33}, {76, 93}, {76, 42}, {76, 55}, {41, 93},
    {41, 51}, {41, 12}, {41, 98}, {41, 18}, {41, 13}, {41, 57}, {41, 36},
    {41, 67}, {41, 66}, {41, 75}, {41, 76}, {41, 21}, {41, 25}, {41, 35},
    {41, 91}, {41, 22}, {41, 81}, {66, 12}, {66, 93}, {66, 59}, {66, 18},
    {66, 35}, {66, 36}, {66, 51}, {66, 45}, {66, 78}, {66, 98}, {66, 75},
    {66, 25}, {66, 91}, {66, 15}, {66, 33}, {66, 55}, {66, 76}, {66, 21},
    {66, 42}, {98, 29}, {98, 65}, {98, 31}, {98, 86}, {98, 45}, {98, 22},
    {98, 64}, {98, 37}, {98, 18}, {98, 11}, {98, 21}, {98, 87}, {98, 67},
    {98, 96}, {98, 25}, {98, 17}, {98, 51}, {98, 35}, {98, 93}, {98, 75},
    {51, 46}, {51, 64}, {51, 87}, {51, 11}, {51, 83}, {51, 92}, {51, 86},
    {51, 96}, {51, 82}, {51, 54}, {51, 55}, {51, 16}, {51, 65}, {51, 71},
    {51, 17}, {51, 53}, {51, 37}, {51, 33}, {51, 29}, {51, 88}, {51, 31},
    {57, 67}, {57, 36}, {57, 33}, {57, 75}, {57, 55}, {57, 76}, {57, 12},
    {57, 51}, {57, 78}, {57, 13}, {57, 15}, {57, 66}, {57, 21}, {57, 93},
    {57, 98}, {57, 95}, {57, 59}, {57, 42}, {57, 22}, {57, 25}, {57, 18},
    {57, 35}, {67, 33}, {67, 65}, {67, 51}, {67, 21}, {67, 96}, {67, 92},
    {67, 45}, {67, 31}, {67, 46}, {67, 78}, {67, 55}, {67, 64}, {67, 75},
    {67, 13}, {67, 17}, {67, 87}, {67, 11}, {67, 82}, {67, 16}, {67, 86},
    {67, 18}, {67, 71}, {67, 37}, {25, 92}, {25, 78}, {25, 51}, {25, 11},
    {25, 18}, {25, 17}, {25, 55}, {25, 75}, {25, 37}, {25, 16}, {25, 65},
    {25, 45}, {25, 64}, {25, 82}, {25, 86}, {25, 46}, {25, 87}, {25, 21},
    {25, 31}, {25, 29}, {25, 96}, {25, 67}, {25, 33}, {25, 13}, {81, 33},
    {81, 42}, {81, 66}, {81, 93}, {81, 95}, {81, 76}, {81, 75}, {81, 57},
    {81, 22}, {81, 91}, {81, 98}, {81, 59}, {81, 78}, {81, 35}, {81, 67},
    {81, 13}, {81, 12}, {81, 21}, {81, 25}, {81, 51}, {81, 36}, {81, 15},
    {81, 17}, {81, 18}, {91, 67}, {91, 42}, {91, 75}, {91, 31}, {91, 98},
    {91, 78}, {91, 96}, {91, 95}, {91, 15}, {91, 17}, {91, 35}, {91, 33},
    {91, 13}, {91, 51}, {91, 37}, {91, 64}, {91, 25}, {91, 21}, {91, 45},
    {91, 55}, {91, 22}, {91, 93}, {91, 18}, {91, 12}, {86, 41}, {86, 46},
    {86, 42}, {86, 83}, {86, 36}, {86, 91}, {86, 95}, {86, 54}, {86, 92},
    {86, 71}, {86, 43}, {86, 66}, {86, 57}, {86, 53}, {86, 12}, {86, 82},
    {86, 88}, {86, 81}, {86, 59}, {86, 11}, {86, 89}, {86, 76}, {86, 16},
    {86, 99}, {21, 16}, {21, 31}, {21, 83}, {21, 33}, {21, 11}, {21, 17},
    {21, 46}, {21, 65}, {21, 37}, {21, 92}, {21, 45}, {21, 64}, {21, 89},
    {21, 96}, {21, 29}, {21, 86}, {21, 55}, {21, 99}, {21, 82}, {21, 18},
    {21, 51}, {21, 53}, {21, 71}, {21, 87}, {99, 54}, {99, 13}, {99, 95},
    {99, 75}, {99, 35}, {99, 57}, {99, 66}, {99, 76}, {99, 12}, {99, 91},
    {99, 93}, {99, 25}, {99, 42}, {99, 36}, {99, 81}, {99, 88}, {99, 98},
    {99, 41}, {99, 22}, {99, 59}, {99, 15}, {99, 43}, {99, 67}, {99, 78},
    {82, 71}, {82, 88}, {82, 98}, {82, 99}, {82, 41}, {82, 57}, {82, 81},
    {82, 43}, {82, 16}, {82, 12}, {82, 59}, {82, 92}, {82, 54}, {82, 83},
    {82, 46}, {82, 36}, {82, 76}, {82, 15}, {82, 89}, {82, 53}, {82, 42},
    {82, 95}, {82, 66}, {82, 91}, {64, 43}, {64, 82}, {64, 16}, {64, 66},
    {64, 29}, {64, 99}, {64, 37}, {64, 53}, {64, 65}, {64, 46}, {64, 88},
    {64, 86}, {64, 54}, {64, 81}, {64, 92}, {64, 11}, {64, 87}, {64, 31},
    {64, 57}, {64, 83}, {64, 96}, {64, 89}, {64, 41}, {64, 71}, {45, 16},
    {45, 46}, {45, 92}, {45, 53}, {45, 65}, {45, 83}, {45, 37}, {45, 71},
    {45, 86}, {45, 81}, {45, 96}, {45, 89}, {45, 43}, {45, 82}, {45, 29},
    {45, 31}, {45, 57}, {45, 41}, {45, 87}, {45, 54}, {45, 11}, {45, 64},
    {45, 88}, {45, 99}, {92, 91}, {92, 41}, {92, 59}, {92, 81}, {92, 89},
    {92, 98}, {92, 66}, {92, 95}, {92, 16}, {92, 42}, {92, 12}, {92, 99},
    {92, 15}, {92, 53}, {92, 88}, {92, 22}, {92, 57}, {92, 54}, {92, 83},
    {92, 76}, {92, 71}, {92, 46}, {92, 43}, {92, 36}, {33, 64}, {33, 11},
    {33, 29}, {33, 16}, {33, 86}, {33, 53}, {33, 99}, {33, 45}, {33, 54},
    {33, 92}, {33, 55}, {33, 37}, {33, 46}, {33, 83}, {33, 88}, {33, 87},
    {33, 96}, {33, 65}, {33, 71}, {33, 43}, {33, 31}, {33, 89}, {33, 41},
    {33, 82}, {87, 82}, {87, 81}, {87, 91}, {87, 16}, {87, 54}, {87, 88},
    {87, 41}, {87, 86}, {87, 12}, {87, 76}, {87, 89}, {87, 53}, {87, 66},
    {87, 71}, {87, 92}, {87, 83}, {87, 11}, {87, 57}, {87, 36}, {87, 99},
    {87, 65}, {87, 46}, {87, 59}, {87, 43}, {43, 22}, {43, 18}, {43, 59},
    {43, 98}, {43, 76}, {43, 15}, {43, 12}, {43, 36}, {43, 25}, {43, 57},
    {43, 75}, {43, 91}, {43, 78}, {43, 66}, {43, 35}, {43, 17}, {43, 93},
    {43, 42}, {43, 95}, {43, 51}, {43, 13}, {43, 67}, {43, 81}, {43, 21},
    {75, 17}, {75, 37}, {75, 29}, {75, 53}, {75, 96}, {75, 21}, {75, 71},
    {75, 18}, {75, 86}, {75, 31}, {75, 11}, {75, 83}, {75, 92}, {75, 33},
    {75, 87}, {75, 89}, {75, 64}, {75, 51}, {75, 55}, {75, 45}, {75, 82},
    {75, 16}, {75, 46}, {75, 65}, {42, 35}, {42, 37}, {42, 64}, {42, 45},
    {42, 21}, {42, 75}, {42, 25}, {42, 33}, {42, 78}, {42, 31}, {42, 55},
    {42, 67}, {42, 98}, {42, 22}, {42, 18}, {42, 29}, {42, 51}, {42, 95},
    {42, 93}, {42, 87}, {42, 96}, {42, 15}, {42, 13}, {42, 17}, {35, 78},
    {35, 67}, {35, 86}, {35, 21}, {35, 87}, {35, 51}, {35, 18}, {35, 25},
    {35, 29}, {35, 13}, {35, 17}, {35, 93}, {35, 65}, {35, 31}, {35, 55},
    {35, 37}, {35, 45}, {35, 96}, {35, 64}, {35, 75}, {35, 82}, {35, 92},
    {35, 33}, {35, 11}, {54, 18}, {54, 25}, {54, 42}, {54, 36}, {54, 35},
    {54, 76}, {54, 21}, {54, 59}, {54, 13}, {54, 67}, {54, 15}, {54, 81},
    {54, 12}, {54, 43}, {54, 66}, {54, 98}, {54, 22}, {54, 75}, {54, 95},
    {54, 91}, {54, 41}, {54, 93}, {54, 78}, {54, 57}, {53, 36}, {53, 93},
    {53, 35}, {53, 67}, {53, 42}, {53, 81}, {53, 22}, {53, 78}, {53, 41},
    {53, 59}, {53, 66}, {53, 98}, {53, 13}, {53, 15}, {53, 25}, {53, 95},
    {53, 91}, {53, 57}, {53, 99}, {53, 88}, {53, 12}, {53, 43}, {53, 54},
    {53, 76}, {12, 96}, {12, 51}, {12, 45}, {12, 25}, {12, 98}, {12, 33},
    {12, 67}, {12, 13}, {12, 22}, {12, 55}, {12, 18}, {12, 42}, {12, 37},
    {12, 17}, {12, 75}, {12, 35}, {12, 93}, {12, 95}, {12, 78}, {12, 21},
    {12, 64}, {12, 15}, {12, 31}, {12, 29}, {17, 53}, {17, 89}, {17, 64},
    {17, 31}, {17, 46}, {17, 37}, {17, 11}, {17, 82}, {17, 83}, {17, 92},
    {17, 96}, {17, 65}, {17, 71}, {17, 16}, {17, 45}, {17, 99}, {17, 33},
    {17, 55}, {17, 88}, {17, 41}, {17, 54}, {17, 86}, {17, 87}, {17, 29},
    {18, 37}, {18, 45}, {18, 92}, {18, 31}, {18, 99}, {18, 55}, {18, 33},
    {18, 87}, {18, 89}, {18, 11}, {18, 88}, {18, 53}, {18, 64}, {18, 29},
    {18, 51}, {18, 17}, {18, 46}, {18, 86}, {18, 83}, {18, 65}, {18, 16},
    {18, 96}, {18, 82}, {18, 71}, {95, 29}, {95, 31}, {95, 65}, {95, 55},
    {95, 75}, {95, 51}, {95, 17}, {95, 67}, {95, 64}, {95, 93}, {95, 87},
    {95, 18}, {95, 15}, {95, 33}, {95, 13}, {95, 96}, {95, 25}, {95, 22},
    {95, 45}, {95, 78}, {95, 37}, {95, 21}, {95, 35}, {95, 98}, {36, 15},
    {36, 42}, {36, 51}, {36, 78}, {36, 33}, {36, 13}, {36, 18}, {36, 25},
    {36, 37}, {36, 93}, {36, 22}, {36, 75}, {36, 67}, {36, 17}, {36, 35},
    {36, 45}, {36, 12}, {36, 31}, {36, 95}, {36, 55}, {36, 98}, {36, 21},
    {36, 91}, {36, 64}, {46, 22}, {46, 71}, {46, 57}, {46, 98}, {46, 76},
    {46, 88}, {46, 16}, {46, 95}, {46, 35}, {46, 83}, {46, 99}, {46, 66},
    {46, 91}, {46, 15}, {46, 43}, {46, 89}, {46, 12}, {46, 53}, {46, 59},
    {46, 41}, {46, 42}, {46, 81}, {46, 54}, {46, 36}, {29, 11}, {29, 46},
    {29, 54}, {29, 87}, {29, 53}, {29, 99}, {29, 41}, {29, 57}, {29, 43},
    {29, 89}, {29, 66}, {29, 81}, {29, 16}, {29, 91}, {29, 71}, {29, 86},
    {29, 88}, {29, 65}, {29, 36}, {29, 82}, {29, 59}, {29, 83}, {29, 76},
    {29, 92}, {22, 18}, {22, 17}, {22, 29}, {22, 82}, {22, 25}, {22, 37},
    {22, 64}, {22, 86}, {22, 87}, {22, 65}, {22, 78}, {22, 55}, {22, 11},
    {22, 31}, {22, 75}, {22, 21}, {22, 13}, {22, 45}, {22, 96}, {22, 33},
    {22, 51}, {22, 93}, {22, 35}, {22, 67}, {88, 42}, {88, 93}, {88, 35},
    {88, 36}, {88, 57}, {88, 75}, {88, 91}, {88, 59}, {88, 25}, {88, 43},
    {88, 12}, {88, 76}, {88, 66}, {88, 21}, {88, 81}, {88, 13}, {88, 41},
    {88, 95}, {88, 78}, {88, 67}, {88, 15}, {88, 22}, {88, 98}, {65, 59},
    {65, 41}, {65, 36}, {65, 92}, {65, 11}, {65, 46}, {65, 91}, {65, 12},
    {65, 76}, {65, 54}, {65, 81}, {65, 89}, {65, 86}, {65, 16}, {65, 57},
    {65, 53}, {65, 43}, {65, 88}, {65, 66}, {65, 99}, {65, 82}, {65, 42},
    {11, 42}, {11, 16}, {11, 91}, {11, 83}, {11, 92}, {11, 54}, {11, 89},
    {11, 81}, {11, 41}, {11, 71}, {11, 99}, {11, 53}, {11, 12}, {11, 76},
    {11, 43}, {11, 82}, {11, 88}, {11, 15}, {11, 95}, {11, 46}, {11, 59},
    {83, 54}, {83, 91}, {83, 93}, {83, 25}, {83, 42}, {83, 81}, {83, 15},
    {83, 12}, {83, 57}, {83, 53}, {83, 35}, {83, 76}, {83, 95}, {83, 41},
    {83, 43}, {83, 22}, {83, 78}, {83, 36}, {83, 66}, {83, 59}, {16, 36},
    {16, 59}, {16, 88}, {16, 57}, {16, 99}, {16, 53}, {16, 15}, {16, 93},
    {16, 22}, {16, 98}, {16, 41}, {16, 54}, {16, 71}, {16, 12}, {16, 91},
    {16, 76}, {16, 89}, {16, 81}, {16, 42}, {96, 83}, {96, 59}, {96, 41},
    {96, 76}, {96, 54}, {96, 57}, {96, 82}, {96, 46}, {96, 99}, {96, 29},
    {96, 89}, {96, 86}, {96, 87}, {96, 16}, {96, 71}, {96, 36}, {96, 81},
    {96, 11}, {55, 83}, {55, 96}, {55, 46}, {55, 82}, {55, 87}, {55, 41},
    {55, 37}, {55, 43}, {55, 53}, {55, 86}, {55, 29}, {55, 92}, {55, 64},
    {55, 71}, {55, 31}, {55, 65}, {55, 11}, {31, 82}, {31, 29}, {31, 92},
    {31, 86}, {31, 89}, {31, 59}, {31, 11}, {31, 54}, {31, 99}, {31, 66},
    {31, 46}, {31, 53}, {31, 41}, {31, 71}, {31, 96}, {31, 16}, {78, 86},
    {78, 46}, {78, 75}, {78, 37}, {78, 82}, {78, 21}, {78, 71}, {78, 87},
    {78, 31}, {78, 64}, {78, 17}, {78, 92}, {78, 11}, {78, 18}, {78, 89},
    {15, 31}, {15, 96}, {15, 86}, {15, 29}, {15, 21}, {15, 75}, {15, 93},
    {15, 33}, {15, 87}, {15, 67}, {15, 55}, {15, 98}, {15, 65}, {15, 25},
    {71, 41}, {71, 53}, {71, 81}, {71, 89}, {71, 25}, {71, 98}, {71, 83},
    {71, 99}, {71, 91}, {71, 43}, {71, 88}, {71, 54}, {71, 66}, {37, 76},
    {37, 43}, {37, 71}, {37, 88}, {37, 86}, {37, 92}, {37, 59}, {37, 16},
    {37, 87}, {37, 54}, {37, 83}, {37, 46}, {13, 21}, {13, 51}, {13, 33},
    {13, 46}, {13, 64}, {13, 55}, {13, 11}, {13, 92}, {13, 89}, {13, 83},
    {13, 29}, {89, 59}, {89, 43}, {89, 81}, {89, 42}, {89, 41}, {89, 83},
    {89, 36}, {89, 99}, {89, 54}, {89, 93}, {93, 17}, {93, 11}, {93, 78},
    {93, 92}, {93, 65}, {93, 55}, {93, 46}, {93, 33}, {93, 64}, {59, 75},
    {59, 67}, {59, 36}, {59, 45}, {59, 76}, {59, 15}, {59, 91}, {59, 78},
    {76, 13}, {76, 36}, {76, 78}, {76, 31}, {76, 15}, {76, 12}, {76, 98},
    {41, 43}, {41, 59}, {41, 78}, {41, 42}, {41, 95}, {41, 15}, {66, 17},
    {66, 95}, {66, 13}, {66, 67}, {66, 22}, {98, 33}, {98, 78}, {98, 13},
    {98, 55}, {51, 99}, {51, 45}, {51, 89}, {57, 17}, {57, 91}, {67, 29}};

std::vector<std::vector<ll>> pages{

    {98, 22, 35, 93, 25, 67, 78, 13, 75, 21, 18,
     51, 17, 33, 55, 45, 64, 31, 96, 29, 65},
    {41, 43, 66, 36, 91, 15, 98, 25, 67, 78, 75},
    {66, 91, 22, 15, 18, 98, 76, 13, 78, 42, 93, 67,
     95, 35, 17, 33, 36, 25, 59, 12, 21, 75, 57},
    {89, 83, 99, 54, 41, 57, 66, 59, 91, 42, 95, 15, 98, 93, 25},
    {87, 11, 92, 46, 89, 83, 53, 81, 57, 66, 91},
    {78, 75, 51, 64, 65, 16, 71},
    {31, 37, 96, 29, 87, 65, 11, 92, 46, 71, 83, 81, 66},
    {21, 51, 17, 29, 92, 71, 89},
    {17, 87, 86, 11, 82, 92, 46, 71, 53, 88, 54},
    {86, 11, 82, 46, 16, 83, 53, 99, 41, 43, 81, 66, 59, 76, 91, 12, 42},
    {43, 66, 91, 75, 41, 12, 98, 59, 76, 25, 18, 95, 22, 35, 15},
    {43, 66, 59, 76, 91, 67, 13, 75, 21, 18, 51},
    {57, 59, 76, 36, 91, 12, 95, 15, 22, 35, 93, 25, 67, 78, 13, 75, 18, 51,
     33},
    {35, 93, 67, 75, 18, 55, 96, 87, 86, 11, 82},
    {43, 92, 71, 76, 57, 88, 53, 82, 81, 86, 41, 12,
     16, 66, 89, 46, 99, 65, 11, 36, 54, 59, 83},
    {37, 21, 51, 92, 45, 89, 13, 64, 71, 11, 18},
    {42, 15, 22, 35, 78, 18, 51, 17, 33, 64, 31, 96, 29},
    {51, 17, 33, 64, 31, 37, 96, 29, 87, 86, 11, 82, 46, 16, 71, 83, 53, 99,
     88},
    {37, 96, 25, 13, 18},
    {53, 81, 88, 66, 96, 86, 87, 16, 71, 43, 57,
     37, 29, 99, 83, 82, 46, 59, 11, 65, 92},
    {59, 12, 43, 99, 76, 66, 53, 82, 16, 92, 54, 15, 41, 81, 71, 89, 88, 46,
     57},
    {76, 42, 91, 71, 54, 81, 88, 12, 41, 53, 57,
     83, 43, 66, 11, 82, 16, 92, 59, 89, 95},
    {96, 31, 35, 98, 45, 64, 55, 18, 13, 75, 12, 42, 21, 95, 33, 51, 78, 17,
     22},
    {95, 35, 33, 51, 22, 91, 12, 78, 66, 93, 59, 75, 18, 55, 15, 36, 42},
    {43, 35, 93, 95, 81, 42, 41},
    {16, 71, 89, 99, 88, 41, 59, 36, 91, 12, 95, 98, 35},
    {55, 53, 82, 64, 45, 21, 31},
    {95, 33, 35, 13, 36, 25, 51, 22, 91, 15, 98, 31, 45, 93, 42},
    {36, 22, 93, 89, 95, 99, 88, 57, 42, 12, 66,
     35, 53, 98, 25, 91, 83, 54, 76, 81, 59},
    {76, 53, 11, 43, 59, 99, 95, 92, 81, 12, 46, 88, 91},
    {35, 25, 67, 17, 33, 45, 96, 65, 11},
    {42, 95, 15, 98, 22, 35, 93, 25, 67, 78, 13,
     75, 21, 51, 17, 33, 45, 64, 31, 96, 29},
    {13, 75, 21, 17, 45, 64, 96, 87, 82, 92, 16, 71, 89},
    {71, 89, 83, 53, 99, 88, 54, 41, 66, 76, 42, 95, 15, 98, 22, 35, 93},
    {45, 64, 31, 29, 87, 82, 46, 54, 81},
    {36, 98, 66, 83, 93, 57, 25, 91, 43, 12, 22, 99, 35, 95, 89, 15, 42, 76,
     41},
    {21, 51, 17, 64, 29, 11, 89},
    {55, 78, 93, 21, 92, 45, 29, 13, 86},
    {91, 43, 83, 76, 81, 53, 16, 71, 92, 57, 82, 46, 54},
    {16, 99, 41, 81, 91, 42, 35},
    {67, 21, 25, 45, 13, 12, 42, 22, 33, 17, 55, 93, 18, 15, 91, 78, 59},
    {59, 36, 91, 12, 42, 95, 15, 98, 22, 35, 67,
     78, 13, 75, 21, 18, 51, 17, 33, 55, 45},
    {41, 65, 36, 91, 11, 99, 66, 89, 76, 86, 92, 43, 54, 16, 82, 81, 12},
    {82, 54, 65, 66, 81, 86, 88, 11, 71, 43, 29, 53, 46, 36, 57, 59, 92, 89,
     16},
    {46, 16, 65, 87, 66, 88, 36, 71, 57, 89, 99, 81, 11, 43, 29},
    {81, 46, 76, 71, 54, 43, 89, 96, 29, 53, 66, 88, 99, 41, 57},
    {12, 18, 15, 36, 95, 75, 66, 91, 41, 21, 42, 59, 35},
    {82, 64, 65, 18, 45, 29, 11, 67, 51, 87, 78, 25, 21},
    {67, 21, 17, 33, 64, 31, 65, 11, 82, 46, 16},
    {33, 91, 93, 67, 76, 75, 95, 55, 42, 35, 78, 64, 51},
    {22, 59, 95, 66, 81, 21, 15, 43, 42, 67, 51, 93, 18, 25, 57},
    {99, 88, 54, 41, 43, 81, 57, 66, 59, 76, 91,
     12, 42, 15, 98, 22, 35, 93, 25, 67, 13},
    {25, 67, 78, 13, 75, 18, 17, 33, 55, 45, 31, 96, 87, 65, 11, 82, 46},
    {35, 67, 12, 21, 81, 75, 76, 93, 59, 36, 17, 98, 42},
    {91, 25, 88, 59, 36, 12, 89},
    {12, 22, 36, 93, 81, 66, 35, 57, 15, 91, 76, 95, 88, 25, 98, 99, 89, 43,
     54},
    {67, 78, 13, 75, 21, 17, 55, 45, 31, 37, 29, 65, 11, 82, 46},
    {25, 67, 78, 75, 51, 31, 96, 29, 65, 86, 82, 92, 46},
    {78, 65, 45, 33, 15, 17, 55, 13, 25, 67, 87, 35, 37, 64, 21, 18, 31},
    {98, 41, 92, 54, 71, 66, 91, 57, 99, 43, 83, 46, 15},
    {98, 51, 36, 33, 75, 64, 93, 31, 95, 67, 22, 18, 12},
    {87, 86, 92, 71, 89, 53, 99, 88, 54, 41, 81, 57, 59, 36, 91},
    {66, 83, 22, 53, 88},
    {17, 59, 35, 33, 45, 18, 25, 95, 42, 51, 15, 21,
     13, 75, 67, 98, 22, 55, 91, 78, 76, 93, 12},
    {21, 75, 55, 17, 66, 12, 15, 22, 93, 59, 98},
    {81, 57, 66, 59, 76, 36, 91, 12, 42, 95, 15, 98,
     22, 35, 93, 67, 78, 13, 75, 21, 18, 51, 17},
    {12, 98, 22, 25, 67},
    {86, 11, 82, 46, 16, 83, 53, 99, 88, 54, 41, 57, 66, 59, 36, 91, 42},
    {35, 67, 78, 13, 75, 21, 18, 51, 17, 33, 55,
     45, 64, 31, 37, 96, 29, 87, 65, 11, 82},
    {92, 46, 71, 53, 99, 43, 57, 59, 76, 91, 12},
    {95, 15, 98, 22, 35, 93, 25, 67, 13, 75, 21, 18,
     51, 17, 33, 55, 45, 64, 31, 37, 96, 29, 87},
    {36, 16, 81, 66, 83, 46, 53, 88, 57, 54, 12, 11, 41, 89, 76, 95, 71},
    {12, 81, 53, 42, 83, 89, 99, 82, 66, 71, 92, 76, 16, 59, 11, 91, 95, 54,
     88},
    {36, 57, 76, 13, 33, 21, 12, 18, 95},
    {87, 65, 86, 82, 46, 16, 71, 89, 53, 88, 54, 41, 43, 81, 66, 59, 76, 36,
     91},
    {76, 42, 35, 93, 25, 13, 75, 21, 18, 51, 64},
    {21, 18, 17, 55, 45, 37, 29, 65, 92, 16, 53},
    {25, 67, 18, 92, 93, 33, 31},
    {15, 93, 13, 31, 37, 96, 65},
    {42, 35, 93, 67, 75, 18, 45, 64, 96},
    {78, 31, 29, 64, 15, 33, 42, 37, 17, 96, 75},
    {41, 54, 25, 42, 59, 53, 36, 88, 91, 67, 57, 22, 15, 95, 78},
    {55, 64, 37, 96, 92, 16, 71, 83, 53, 54, 43},
    {99, 96, 11, 46, 51, 89, 86, 37, 33, 31, 55, 64, 53, 71, 45},
    {81, 66, 59, 12, 95, 22, 35, 67, 78, 13, 21, 18, 17},
    {76, 81, 95, 15, 98, 75, 57, 13, 88, 66, 22},
    {53, 93, 15, 83, 57, 91, 66, 42, 22, 99, 59, 67, 88, 25, 54},
    {45, 64, 37, 29, 86, 11, 46, 16, 89, 83, 88, 43, 81},
    {96, 12, 25, 15, 98, 95, 35},
    {64, 51, 15, 22, 45, 12, 93, 91, 25, 13, 17, 18,
     42, 78, 55, 36, 76, 75, 98, 35, 67, 33, 95},
    {93, 25, 67, 33, 31, 86, 92},
    {17, 33, 55, 45, 64, 31, 37, 29, 87, 65, 86, 11,
     82, 92, 46, 16, 71, 89, 83, 53, 99, 88, 54},
    {98, 46, 81, 89, 71, 57, 54, 88, 92, 42, 95, 12, 16, 76, 41},
    {92, 11, 57, 99, 29, 37, 59, 41, 53, 65, 87, 71,
     16, 82, 81, 86, 96, 66, 43, 88, 46, 83, 89},
    {33, 45, 31, 37, 96, 29, 87, 65, 86, 82, 92, 46, 16, 71, 89, 53, 99, 88,
     41},
    {65, 86, 11, 92, 46, 88, 81, 91, 12},
    {15, 98, 22, 35, 93, 25, 67, 78, 13, 75, 21, 18,
     51, 17, 33, 55, 45, 64, 31, 96, 29, 87, 65},
    {86, 41, 43, 87, 65, 54, 59, 92, 11},
    {66, 59, 76, 36, 15, 98, 22, 25, 67, 78, 13, 21, 18, 17, 55},
    {35, 75, 76, 42, 95, 54, 21, 13, 57},
    {17, 55, 45, 64, 31, 37, 96, 29, 87, 65, 86, 11,
     82, 92, 46, 16, 71, 89, 83, 53, 99, 88, 54},
    {66, 59, 76, 36, 91, 12, 42, 95, 15, 98, 22, 35,
     93, 25, 67, 78, 75, 21, 18, 51, 17, 33, 55},
    {59, 54, 71, 43, 91, 12, 76, 81, 83, 46, 36, 16, 53, 57, 41, 88, 92, 82,
     11},
    {29, 75, 17, 37, 13, 22, 65, 67, 78, 18, 55, 93, 21},
    {41, 57, 66, 59, 76, 91, 98, 22, 35, 67, 78, 13, 18},
    {87, 65, 86, 11, 92, 46, 16, 71, 89, 53, 88, 54, 41, 43, 81, 57, 59, 76,
     91},
    {76, 91, 12, 95, 22, 93, 25, 67, 75, 17, 64},
    {35, 13, 75, 18, 33, 37, 96, 65, 82},
    {18, 65, 87, 67, 35, 55, 29, 45, 13, 93, 51, 86,
     78, 96, 11, 21, 64, 33, 22, 17, 75, 37, 25},
    {25, 29, 21, 75, 22, 37, 33, 67, 55, 11, 18, 86, 51},
    {16, 71, 89, 53, 99, 88, 54, 43, 81, 59, 76, 36, 91, 12, 95, 15, 98, 22,
     35},
    {25, 11, 13, 65, 29, 17, 46, 86, 75, 92, 96},
    {65, 11, 82, 16, 71, 83, 53, 66, 12},
    {95, 98, 93, 51, 96},
    {67, 13, 75, 21, 18, 51, 17, 33, 64, 37, 96, 29, 87, 65, 86, 11, 82, 46,
     16},
    {81, 57, 66, 59, 36, 91, 42, 15, 35, 25, 67, 75, 21},
    {12, 57, 88, 42, 53, 98, 78, 36, 22, 43, 15, 91, 35, 99, 25, 54, 95, 41,
     76},
    {57, 91, 15, 98, 22, 35, 93, 67, 78, 13, 75, 17, 33},
    {41, 89, 15, 81, 98, 54, 57, 35, 43, 36, 91,
     95, 71, 53, 12, 83, 76, 66, 42, 59, 93},
    {46, 17, 16, 65, 18, 99, 86, 29, 71, 89, 82, 96, 83, 51, 53, 55, 87},
    {95, 42, 15, 18, 41, 75, 22, 36, 59, 93, 21},
    {37, 45, 29, 92, 31, 16, 18, 51, 86, 75, 17, 55, 82, 67, 13, 78, 46},
    {81, 59, 76, 36, 91, 42, 15, 98, 22, 35, 25, 78, 13, 75, 18, 51, 17},
    {65, 45, 55, 17, 18, 78, 31, 93, 64, 51, 87,
     67, 35, 75, 22, 29, 86, 96, 33, 25, 98},
    {92, 46, 71, 89, 83, 53, 99, 88, 54, 43, 81,
     57, 66, 59, 76, 36, 91, 12, 42, 15, 98},
    {54, 59, 53, 82, 87, 36, 86, 88, 99, 81, 41, 11, 89, 92, 46},
    {33, 17, 89, 45, 46, 92, 53, 51, 87, 18, 55, 11, 64, 37, 65},
    {78, 21, 51, 64, 37, 87, 65, 11, 46, 16, 71},
    {76, 36, 12, 42, 95, 15, 22, 93, 25, 67, 78, 13, 51, 17, 33, 45, 64},
    {41, 96, 29, 88, 89, 65, 76},
    {15, 98, 22, 35, 93, 25, 67, 78, 13, 75, 21, 18,
     51, 33, 55, 45, 64, 31, 37, 96, 29, 87, 65},
    {82, 46, 71, 53, 99, 54, 41, 81, 12, 95, 15},
    {45, 11, 88, 54, 92, 46, 96, 29, 86, 81, 41},
    {41, 15, 88, 83, 54, 98, 43, 67, 22, 93, 76, 42, 53, 25, 99},
    {87, 22, 17, 51, 55, 86, 25, 96, 13, 45, 29, 31, 65, 64, 35, 93, 21},
    {18, 64, 93, 55, 17, 95, 98, 45, 15, 13, 36, 12, 78, 75, 91, 76, 25},
    {22, 35, 93, 25, 67, 78, 75, 21, 18, 51, 33,
     45, 64, 31, 37, 96, 29, 87, 65, 86, 11},
    {71, 89, 99, 88, 54, 41, 43, 81, 57, 59, 76, 91, 12, 98, 22, 35, 93},
    {13, 81, 93, 21, 42, 66, 25, 35, 67, 95, 91, 17, 36},
    {95, 89, 22, 15, 66, 25, 76},
    {95, 22, 35, 67, 64, 29, 87},
    {18, 51, 17, 33, 55, 45, 64, 96, 29, 87, 65,
     86, 11, 82, 92, 46, 71, 89, 83, 53, 99},
    {41, 36, 57, 91, 59, 66, 42, 99, 82, 43, 88, 92, 83, 71, 15, 16, 95, 89,
     54},
    {36, 22, 35, 93, 25, 67, 78},
    {41, 81, 59, 93, 25},
    {95, 15, 98, 22, 35, 93, 25, 13, 75, 21, 51, 17, 33, 55, 45, 31, 37, 96,
     29},
    {16, 71, 46, 53, 92, 41, 66, 54, 65, 89, 29,
     86, 59, 43, 82, 81, 36, 83, 99, 76, 88},
    {29, 93, 51, 55, 33},
    {51, 64, 87, 86, 11, 83, 88},
    {53, 46, 95, 76, 88, 22, 89, 99, 91, 81, 83},
    {81, 76, 57, 15, 42},
    {89, 53, 99, 57, 59},
    {64, 37, 96, 29, 87, 86, 82, 92, 46, 83, 54, 41, 43, 81, 57},
    {71, 92, 89, 57, 53, 31, 43, 66, 16},
    {81, 12, 98, 35, 67, 78, 17},
    {46, 71, 89, 83, 53, 99, 41, 43, 57, 66, 12, 42, 95, 15, 22},
    {57, 66, 59, 76, 36, 91, 12, 42, 15, 98, 22, 35, 93, 25, 13, 75, 18, 51,
     33},
    {29, 13, 17, 11, 37, 92, 65, 55, 75},
    {99, 36, 86, 53, 11, 12, 54, 46, 82, 59, 89,
     42, 92, 16, 57, 88, 91, 66, 41, 83, 43},
    {75, 18, 17, 33, 55, 45, 64, 31, 37, 96, 29,
     87, 65, 86, 11, 82, 92, 46, 16, 89, 83},
    {12, 42, 95, 15, 35, 93, 25, 67, 13, 17, 33, 64, 31, 37, 96},
    {92, 46, 71, 83, 88, 54, 41, 81, 59, 76, 98},
    {51, 17, 33, 55, 45, 64, 31, 37, 29, 87, 65, 86,
     11, 82, 92, 46, 16, 71, 89, 83, 53, 99, 88},
    {59, 46, 16, 12, 42, 82, 36, 43, 83, 57, 99,
     95, 11, 71, 92, 54, 53, 41, 89, 91, 66},
    {93, 25, 67, 13, 75, 21, 18, 51, 55, 45, 64, 31, 37, 96, 87, 65, 11, 82,
     92},
    {91, 42, 98, 93, 25, 78, 13, 21, 51},
    {82, 86, 17, 33, 45, 89, 65, 31, 71, 16, 29, 11, 13},
    {43, 81, 57, 66, 59, 36, 91, 15, 21},
    {31, 92, 16, 89, 83, 41, 66},
    {95, 15, 98, 22, 93, 25, 67, 78, 13, 75, 21, 18,
     51, 17, 33, 55, 45, 64, 31, 37, 96, 29, 87},
    {46, 54, 87, 43, 89, 88, 66, 71, 83, 96, 41, 31, 65},
    {82, 95, 12, 15, 36, 91, 89},
    {59, 15, 66, 12, 89},
    {87, 54, 64, 96, 11, 46, 37, 92, 16, 41, 53, 89, 33, 45, 29, 31, 99, 82,
     55},
    {55, 45, 64, 31, 37, 96, 29, 87, 65, 86, 11, 46, 16, 89, 83, 53, 99, 54,
     43},
    {17, 33, 55, 45, 64, 31, 37, 96, 29, 87, 86, 11,
     82, 92, 46, 16, 71, 89, 83, 53, 99, 88, 54},
    {67, 13, 22, 29, 21, 33, 45, 31, 55, 95, 25, 15, 17, 51, 37},
    {43, 81, 57, 66, 59, 76, 91, 12, 42, 95, 15, 35, 93, 67, 13, 75, 21, 18,
     51},
    {18, 17, 33, 55, 45, 64, 31, 37, 96, 29, 87,
     65, 86, 11, 82, 92, 16, 89, 83, 53, 99},
    {22, 57, 75, 15, 78, 43, 21, 41, 18, 42, 13, 36, 67, 91, 76},
    {53, 71, 16, 11, 57, 92, 64, 29, 88, 54, 43, 96, 86, 89, 81, 46, 31},
    {91, 12, 95, 15, 22, 93, 78, 13, 51, 17, 33, 64, 37},
    {59, 76, 36, 91, 12, 42, 95, 15, 98, 22, 35,
     25, 67, 75, 21, 18, 51, 17, 33, 55, 45},
    {46, 16, 71, 89, 83, 53, 99, 41, 43, 81, 57, 59, 76, 36, 91, 12, 95, 98,
     22},
    {83, 53, 99, 88, 54, 41, 57, 66, 76, 36, 91, 12, 95, 15, 98, 22, 93, 25,
     67},
    {75, 21, 18, 51, 17, 33, 55, 64, 31, 37, 96,
     87, 65, 86, 11, 82, 92, 46, 16, 71, 83},
    {64, 43, 71, 53, 81, 31, 65, 37, 92},
    {46, 42, 66, 15, 59, 95, 53, 99, 81, 71, 83,
     76, 91, 54, 92, 36, 89, 88, 57, 16, 43},
    {15, 51, 35, 78, 55, 33, 95, 67, 45, 31, 21,
     18, 29, 22, 17, 75, 37, 64, 13, 98, 96},
    {53, 99, 88, 54, 41, 43, 57, 66, 59, 12, 95, 15, 98, 22, 93, 67, 78},
    {11, 82, 46, 16, 71, 89, 83, 53, 99, 88, 54, 41,
     43, 81, 57, 66, 59, 76, 36, 91, 12, 42, 95},
    {33, 71, 55, 21, 65, 45, 86, 37, 29, 13, 11, 87, 75, 46, 78, 18, 51},
    {96, 17, 51, 88, 33, 89, 92, 83, 46},
    {43, 54, 36, 53, 71, 92, 83, 76, 89, 66, 46, 99, 29},
    {89, 99, 88, 17, 11, 86, 82, 83, 46, 33, 55, 64, 96, 87, 31, 54, 53},
    {78, 18, 45, 65, 93, 87, 29, 31, 13, 25, 11, 92, 82, 51, 55, 86, 96, 37,
     64}};

decltype(input_real) input_test;
//    auto &input = input_test;
auto &input = input_real;

using RULES = std::map<ll, std::set<ll>>;

RULES build_rules() {
  RULES less_false;
  for (auto [p1, p2] : input) {
    less_false[p2].insert(p1);
  }
  return less_false;
}

auto less_false = build_rules();

bool my_less_predicate(ll p1, ll p2) {
  if (auto it = less_false.find(p1); it != less_false.end()) {
    if (it->second.count(p2)) {
      return false;
    }
  }
  return true;
}

} // namespace

int main05() {
  int64_t result0 = 0;
  int64_t result1 = 0;

  for (const auto &p : pages) {
    assert(p.size() % 2 == 1);
    if (std::is_sorted(p.begin(), p.end(), my_less_predicate)) {
      result0 += p.at(p.size() / 2);
    } else {
      auto sorted_p = p;
      std::sort(sorted_p.begin(), sorted_p.end(), my_less_predicate);
      result1 += sorted_p.at(sorted_p.size() / 2);
    }
  }

  myprint(result0);
  myprint(result1);
  return 0;
}