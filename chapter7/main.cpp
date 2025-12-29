#include <iostream>
#include <cmath>
#include <map>
#include <memory>
#include <string>

#define TypeName(TypeNameString)                             \
  static const char* typeName_() { return TypeNameString; }  \
  static const std::string typeName;                         \
  virtual const std::string& type() { return typeName; }

#define TypeNameDerived(TypeNameString)                      \
  static const char* typeName_() { return TypeNameString; }  \
  static const std::string typeName;                         \
  virtual const std::string& type() override { return typeName; }

#define defineTypeName(thisType)  \
  const std::string thisType::typeName(thisType::typeName_());

#define declareRTSTable(baseType, argName)                                         \
  using baseType##Constructor = std::unique_ptr<baseType>(*)();                    \
  using baseType##ConstructorTable = std::map<std::string, baseType##Constructor>; \
  static baseType##ConstructorTable* baseType##ConstructorTable_;                  \
  template <class baseType##Type>                                                  \
    class add##argName##ToConstructorTable                                         \
    {                                                                              \
     public:                                                                       \
      static std::unique_ptr<baseType> New()                                       \
      {                                                                            \
        return std::unique_ptr<baseType>(new baseType##Type());                    \
      }                                                                            \
      add##argName##ToConstructorTable(                                            \
        const std::string& name = baseType##Type::typeName )                       \
      {                                                                            \
        if ( baseType##ConstructorTable_ == nullptr )                              \
        {                                                                          \
          baseType::baseType##ConstructorTable_                                    \
            = new baseType::baseType##ConstructorTable();                          \
        }                                                                          \
        baseType::baseType##ConstructorTable_->insert(                             \
          std::pair<std::string, baseType##Constructor>(name, New));               \
      }                                                                            \
    };

#define defineRTSTable(baseType)  \
  baseType::baseType##ConstructorTable* baseType::baseType##ConstructorTable_ = nullptr;

#define addRTSTable(baseType, argName, thisType)  \
  baseType::add##argName##ToConstructorTable<thisType> add##thisType##ToConstructorTable_;

class Function1 {
 public:
  Function1() = default;
  virtual ~Function1() = default;

  virtual float operator()(float x) = 0;

  TypeName("Function1")

  declareRTSTable(Function1, Object)

  static std::unique_ptr<Function1> New(const std::string& name) {
    auto iter = Function1::Function1ConstructorTable_->find(name);
    if (iter == Function1::Function1ConstructorTable_->end()) {
      std::cerr << "Failed to fine " << name << std::endl;
      return nullptr;
    }
    return iter->second();
  }
};

class Sqr : public Function1 {
 public:
  Sqr() = default;
  virtual ~Sqr() = default;

  virtual float operator()(float x) override {
    return x * x;
  }

  TypeNameDerived("sqr")
};

class Sqrt : public Function1 {
 public:
  Sqrt() = default;
  virtual ~Sqrt() = default;

  virtual float operator()(float x) override {
    return std::sqrt(x);
  }

  TypeNameDerived("sqrt")
};

class Cubic : public Function1 {
 public:
  Cubic() = default;
  virtual ~Cubic() = default;

  virtual float operator()(float x) override {
    return x * x * x;
  }

  TypeNameDerived("cubic")
};

defineTypeName(Function1)
defineRTSTable(Function1)

defineTypeName(Sqr)
addRTSTable(Function1, Object, Sqr)

defineTypeName(Sqrt)
addRTSTable(Function1, Object, Sqrt)

defineTypeName(Cubic)
addRTSTable(Function1, Object, Cubic)

int main(int argc, char** argv) {
  std::cout << "Function1RTStable" << std::endl;
  for (auto iter = Function1::Function1ConstructorTable_->begin();
       iter != Function1::Function1ConstructorTable_->end();
       ++iter) {
    std::cout << "Key: " << iter->first << std::endl;
  }

  float x;
  std::string choice;
  x = 3.0f;

  std::cout << "Select method (sqr, sqrt, cubic): " << std::endl;
  std::cin >> choice;
  std::cout << "Input value: " << x << std::endl;

  std::unique_ptr<Function1> func = Function1::New(choice);
  std::cout << "Function call: " << (*func)(x) << std::endl;

  return 0;
}
