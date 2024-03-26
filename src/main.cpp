#include "flow_iterator.hpp"
#include "flowmap.hpp"
#include "rawdata.hpp"
#include <iostream>
#include <tuple>
#include <path_info.hpp>
int main()
{

  std::vector<std::string> files = 
      {"../BIREM_generate/out/"};

  FlowIterator it = FlowIterator(files, 1);

  // FlowInfo *f = it.get();

  // while (f != nullptr)
  // {
  //   std::cout << f->neigbors.size() << std::endl;
  //   it.next();
  //   f = it.get();
  // }

  // auto rd = RawDataScalar::read(".vofL.raw");
  // for(auto&& i : rd.values)
  // {
  //   std::cout<<i.value<<std::endl;
  // }

  // CasePaths c = get_paths("RESULTS.encas");

  // std::cout << "Geometry filepath: " << c.geometryFilepath << std::endl;
  //   std::cout << "Variable filepaths:" << std::endl;
  //   for (const auto& varInfo : c.variableInfos) {
  //       std::cout <<varInfo.type<< varInfo.name << " " << varInfo.filepath << std::endl;
  //   }
}