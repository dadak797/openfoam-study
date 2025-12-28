#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <string>

class Function1 {
 public:
  Function1() = default;
  virtual ~Function1() = default;

  virtual float operator()(float x) = 0;

  static constexpr const char* typeName_{"Function1"};
  static const std::string typeName;
};

class Sqr : public Function1 {
 public:
  Sqr() = default;
  virtual ~Sqr() = default;

  virtual float operator()(float x) override {
    return x * x;
  }

  static constexpr const char* typeName_{"sqr"};
  static const std::string typeName;
};

class Sqrt : public Function1 {
 public:
  Sqrt() = default;
  virtual ~Sqrt() = default;

  virtual float operator()(float x) override {
    return std::sqrt(x);
  }

  static constexpr const char* typeName_{"sqrt"};
  static const std::string typeName;
};

class Cubic : public Function1 {
 public:
  Cubic() = default;
  virtual ~Cubic() = default;

  virtual float operator()(float x) override {
    return x * x * x;
  }

  static constexpr const char* typeName_{"cubic"};
  static const std::string typeName;
};

std::unique_ptr<Function1> Sqr_factory() {
  std::cout << "sqr object created" << std::endl;
  return std::unique_ptr<Function1>(new Sqr());
}

std::unique_ptr<Function1> Sqrt_factory() {
  std::cout << "sqrt object created" << std::endl;
  return std::unique_ptr<Function1>(new Sqrt());
}

std::unique_ptr<Function1> Cubic_factory() {
  std::cout << "cubic object created" << std::endl;
  return std::unique_ptr<Function1>(new Cubic());
}

using Function1Ptr = std::unique_ptr<Function1>(*)();
std::map<std::string, Function1Ptr> Function1RTStable;

class SqrAddToTable {
 public:
  SqrAddToTable(const std::string& name = Sqr::typeName) {
    Function1RTStable.insert(std::pair<std::string, Function1Ptr>(name, Sqr_factory));
  }
};

class SqrtAddToTable {
 public:
  SqrtAddToTable(const std::string& name = Sqrt::typeName) {
    Function1RTStable.insert(std::pair<std::string, Function1Ptr>(name, Sqrt_factory));
  }
};

class CubicAddToTable {
 public:
  CubicAddToTable(const std::string& name = Cubic::typeName) {
    Function1RTStable.insert(std::pair<std::string, Function1Ptr>(name, Cubic_factory));
  }
};

const std::string Function1::typeName = Function1::typeName_;

const std::string Sqr::typeName = Sqr::typeName_;
SqrAddToTable SqrDelegator(Sqr::typeName);

const std::string Sqrt::typeName = Sqrt::typeName_;
SqrtAddToTable SqrtDelegator(Sqrt::typeName);

const std::string Cubic::typeName = Cubic::typeName_;
CubicAddToTable CubicDelegator(Cubic::typeName);

int main(int argc, char** argv) {
  std::cout << "Function1RTStable" << std::endl;
  for (auto iter = Function1RTStable.begin(); iter != Function1RTStable.end(); ++iter) {
    std::cout << "Key: " << iter->first << " -> ";
    iter->second();
  }

  float x;
  std::string choice;
  x = 3.0f;

  std::cout << "Select method (sqr, sqrt, cubic): " << std::endl;
  std::cin >> choice;
  std::cout << "Input value: " << x << std::endl;

  std::unique_ptr<Function1> func = Function1RTStable[choice]();
  std::cout << "Function call: " << (*func)(x) << std::endl;

  return 0;
}
