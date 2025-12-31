#pragma once

#include <string>

class object {
 private:
  const std::string name_;

 public:
  object(const std::string& name) : name_(name) {}
  virtual ~object() {}

  const std::string& name() const { return name_; }
};
