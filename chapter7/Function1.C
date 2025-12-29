#include "Function1.H"

defineTypeName(Function1)
defineRTSTable(Function1)

std::unique_ptr<Function1> Function1::New(const std::string& name) {
  auto iter = Function1::Function1ConstructorTable_->find(name);
  if (iter == Function1::Function1ConstructorTable_->end()) {
    std::cerr << "Failed to fine " << name << std::endl;
    return nullptr;
  }
  return iter->second();
}