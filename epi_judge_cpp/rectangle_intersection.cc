#include <tuple>
#include <utility>
#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
struct Rect {
  int x, y, width, height;

  int x2() const {
      return x + width;
  }

  int y2() const {
      return y + height;
  }
};

/*
 *  00000011111
 *  SSSSS----S
 */

bool intersects(const Rect& r1, const Rect& r2) {
    return !(r1.x > r2.x2() || r2.x > r1.x2()) && !(r1.y > r2.y2() || r2.y > r1.y2());
}


Rect IntersectRectangle(const Rect& r1, const Rect& r2) {
    using std::min;
    using std::max;

    if (!intersects(r1, r2)) {
        return {0, 0, -1, -1};
    }
    return {max(r1.x, r2.x), max(r1.y, r2.y),
            min(r1.x2(), r2.x2()) - max(r1.x, r2.x),
            min(r1.y2(), r2.y2()) - max(r1.y, r2.y)};
}


bool operator==(const Rect& r1, const Rect& r2) {
  return std::tie(r1.x, r1.y, r1.width, r1.height) ==
         std::tie(r2.x, r2.y, r2.width, r2.height);
}

namespace test_framework {
template <>
struct SerializationTrait<Rect> : UserSerTrait<Rect, int, int, int, int> {
  static std::vector<std::string> GetMetricNames(const std::string& arg_name) {
    return {FmtStr("height({})", arg_name), FmtStr("width({})", arg_name)};
  }

  static std::vector<int> GetMetrics(const Rect& x) {
    return {x.height, x.width};
  }
};
}  // namespace test_framework

std::ostream& operator<<(std::ostream& out, const Rect& r) {
  return PrintTo(out, std::make_tuple(r.x, r.y, r.width, r.height));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"r1", "r2"};
  return GenericTestMain(args, "rectangle_intersection.cc",
                         "rectangle_intersection.tsv", &IntersectRectangle,
                         DefaultComparator{}, param_names);
}
