#include "test_framework/generic_test.h"

long long ReverseImpl(int x, long long tail) {
    if (x < 10) {
        return x + tail * 10;
    }
    int lsd = x % 10;
    return ReverseImpl(x / 10, tail * 10 + lsd);
}
long long Reverse(int x) {
    if (x < 0) {
        return -ReverseImpl(-x, 0);
    } else {
        return ReverseImpl(x, 0);
    }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
