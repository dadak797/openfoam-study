#pragma once

#include "Function1.H"

class Cubic : public Function1 {
 public:
  Cubic() = default;
  virtual ~Cubic() = default;

  virtual float operator()(float x) override;

  TypeNameDerived("cubic")
};
