#pragma once
#include <filesystem>
#include <memory>

class Resources {
 static Resources* instance;
 public:
  static  Resources* getInstance() {
      if (instance == nullptr) {
          instance = new Resources();
      }
      return instance;
  }
 static std::filesystem::path getCurrentPath() {
     return std::filesystem::current_path();
  }
};
