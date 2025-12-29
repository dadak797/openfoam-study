#include "Cubic.H"

defineTypeName(Cubic)
addRTSTable(Function1, Object, Cubic)

float Cubic::operator()(float x) {
  return x * x * x;
}
