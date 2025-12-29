#include "Sqrt.H"

#include <cmath>

defineTypeName(Sqrt)
addRTSTable(Function1, Object, Sqrt)

float Sqrt::operator()(float x) {
  return std::sqrt(x);
}