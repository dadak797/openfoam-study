#pragma once

#include <string>
#include <map>
#include <memory>
#include <iostream>

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

  static std::unique_ptr<Function1> New(const std::string& name);
};