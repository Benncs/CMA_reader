#include <rawdata.hpp>
#include <path_info.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream> 






CasePaths get_paths(std::string_view path)
{
  CasePaths case_info;
  std::ifstream f1(path.data());
  if (f1.is_open())
  {
    std::string line;

    while (std::getline(f1, line))
    {
      std::istringstream iss(line);
      std::string token;
      if (line.find("GEOMETRY") != std::string::npos)
      {
        std::getline(f1, line);

        std::istringstream iss(line);
        std::string junk; // Dummy variable to consume unnecessary parts

        // Read and discard "model:"
        iss >> junk;
        // Read geometry filepath
        iss >> case_info.geometryFilepath;
        // std::getline(f1, case_info.geometryFilepath);
      }
      else if (line.find("VARIABLE") != std::string::npos)
      {
        // Extract variable information
        while (std::getline(f1, line) && !line.empty())
        {
          VariableInfo varInfo;
          std::istringstream iss(line);
          iss >> varInfo.type;
          if (varInfo.type == "scalar" || varInfo.type == "vector")
          {
            iss >> token; // "per"
            iss >> token; // "element:"
          }
          iss >> varInfo.name;
          iss >> varInfo.filepath;
          case_info.variableInfos.push_back(varInfo);
        }
      }
    }
  }else {
    throw std::runtime_error("No such file");
  }

return case_info;
}

RawDataFlux RawDataFlux::read(std::string_view path)
{

  FluxFileHeader header;
  std::vector<RawFlux> fluxes;

  std::ifstream f1(path.data(), std::fstream::binary);
  if (f1.is_open())
  {
    f1.read(reinterpret_cast<char *>(&header), sizeof(header));
    fluxes.resize(header.n_max);
    for (uint32_t i_flux = 0; i_flux < header.n_max; ++i_flux)
    {
      f1.read(reinterpret_cast<char *>(&fluxes[i_flux]),
          sizeof(fluxes[i_flux]));
    }
    f1.close();
  }
  else
  {
    throw std::runtime_error("No such file");
  }

  return {header, fluxes};
}

RawDataScalar RawDataScalar::read(std::string_view path)
{

  ScalarFileHeader header;
  std::vector<RawScalar> value;

  std::ifstream f1(path.data(), std::fstream::binary);
  if (f1.is_open())
  {
    f1.read(reinterpret_cast<char *>(&header), sizeof(header));
    value.resize(header.n_zone);
    for (uint32_t i_compartment = 0; i_compartment < header.n_zone;
        ++i_compartment)
    {
      f1.read(reinterpret_cast<char *>(&value[i_compartment]),
          sizeof(values[i_compartment]));
    }
    f1.close();
  }

  return {header, value};
}
