#pragma once

#include "object.h"

#include <map>
#include <string>
#include <memory>

class objectManager {
 protected:
  std::map<std::string, std::unique_ptr<object>> db_;

 public:
  void checkIn(std::unique_ptr<object> obj) {
    std::string name = obj->name();  // Copy name before moving
    db_.insert(std::make_pair(name, std::move(obj)));
  }

  const std::map<std::string, std::unique_ptr<object>>& db() const {
    return db_;
  }

  object& lookupObject(const std::string& name) {
    return *(db_.find(name)->second);
  }

  const object& lookupObject(const std::string& name) const {
    return *(db_.find(name)->second);
  }

  void showRecord() const {
    for (auto iter = db_.begin(); iter != db_.end(); ++iter) {
      std::cout << iter->first << " : " << iter->second->name() << std::endl;
    }
  }
};