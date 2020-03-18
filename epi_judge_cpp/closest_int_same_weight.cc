#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  /*
  00110001000
  00110000111
  00000001111
  00000010000
  00000000100*/
  if (x & 1) {
      return x + 1;
  }
  auto y = ((x ^ (x - 1)) + 1) >> 2;
  return (x & (x - 1)) | y;

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
