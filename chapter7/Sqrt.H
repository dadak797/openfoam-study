#pragma once

#include "Function1.H"

class Sqrt : public Function1 {
 public:
  Sqrt() = default;
  virtual ~Sqrt() = default;

  virtual float operator()(float x) override;

  TypeNameDerived("sqrt")
};
