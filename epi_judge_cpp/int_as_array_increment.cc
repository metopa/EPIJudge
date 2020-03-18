#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  int carry = 1;

  for (auto it = A.rbegin(); it != A.rend() && carry; ++it) {
      auto res = *it + carry;
      carry = res / 10;
      *it = res % 10;
  }
  if (carry) {
      A.insert(A.begin(), 1);
  }
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
