#include "Sqr.H"

defineTypeName(Sqr)
addRTSTable(Function1, Object, Sqr)

float Sqr::operator()(float x) {
  return x * x;
}
