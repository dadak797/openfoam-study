#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "objectManager.h"

class scalarList : public object {
 private:
  std::vector<double> data_;

 public:
  scalarList(const std::string& name) : object(name) {}

  std::vector<double>& data() { return data_; }

  size_t size() const { return data_.size(); }
  void resize(size_t n) { data_.resize(n); }
  void reserve(size_t n) { data_.reserve(n); }
};

class dictionary : public object {
 private:
  std::map<std::string, std::string> dict_;

 public:
  dictionary(const std::string& name) : object(name) {}

  std::map<std::string, std::string>& dict() { return dict_; }
};

int main(int argc, char** argv) {
  objectManager manager;

  manager.checkIn(std::unique_ptr<object>(new object("myobj")));
  manager.checkIn(std::unique_ptr<object>(new scalarList("mylist")));
  manager.checkIn(std::unique_ptr<object>(new dictionary("mydict")));

  manager.showRecord();

  scalarList& cache = static_cast<scalarList&>(manager.lookupObject("mylist"));
  cache.resize(10);

  std::cout << cache.name() << std::endl;
  std::cout << cache.size() << std::endl;

  for (auto iter = cache.data().begin(); iter != cache.data().end(); ++iter) {
    std::cout << *iter << std::endl;
  }

  auto& dict = static_cast<dictionary&>(manager.lookupObject("mydict"));
  dict.dict().insert(std::make_pair("value", "uniform (1 0 0)"));
  dict.dict().insert(std::make_pair("rho", "1.21"));

  for (auto iter = dict.dict().begin(); iter != dict.dict().end(); ++iter) {
    std::cout << iter->first << " : " << iter->second << std::endl;
  }

  return 0;
}
