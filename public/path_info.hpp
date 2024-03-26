#ifndef __PATH_INFO_FILE_HPP__
#define __PATH_INFO_FILE_HPP__

#include <vector> 
#include <string_view> 
#include <string>

struct VariableInfo
{
  std::string type;
  std::string name;
  std::string filepath;
};

struct CasePaths
{
  std::string geometryFilepath;
  std::vector<VariableInfo> variableInfos;
};

CasePaths get_paths(std::string_view);


#endif //__PATH_INFO_FILE_HPP__