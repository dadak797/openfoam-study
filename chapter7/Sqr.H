#pragma once

#include "Function1.H"

class Sqr : public Function1 {
 public:
  Sqr() = default;
  virtual ~Sqr() = default;

  virtual float operator()(float x) override;

  TypeNameDerived("sqr")
};