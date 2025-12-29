#include <vector>
#include <dlfcn.h>

#include "Function1.H"

int main(int argc, char** argv) {
  std::vector<void*> handleList;
  std::vector<std::string> libraryList;
  libraryList.push_back("chapter7/libcubic.so");
  libraryList.push_back("chapter7/libsqr.so");
  libraryList.push_back("chapter7/libsqrt.so");

  std::cout << "List table" << std::endl;
  for (const auto& library : libraryList) {
    void* handle = ::dlopen(library.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    handleList.push_back(handle);
  }

  std::cout << "Begin" << std::endl;

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
