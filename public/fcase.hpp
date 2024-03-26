#ifndef __FCASE_HPP__
#define __FCASE_HPP__

#include "flowmap.hpp"
#include <vector>
#include <unordered_map>
#include <string> 

struct FCase
{
  std::unordered_map<std::string, std::vector<double>> scalars;
  std::unordered_map<std::string, FlowMap> flows;
  
  static FCase from_path(const std::string& case_path );
};

#endif //__FCASE_HPP__