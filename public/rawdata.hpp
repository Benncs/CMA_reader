#ifndef __RAW_DATA_FLOW_HPP__
#define __RAW_DATA_FLOW_HPP__
#include <cstdint> 
#include <vector> 
#include <cmath>
#include <string_view> 
#include <string>



struct FluxFileHeader
{
  uint32_t n_zone;
  uint32_t n_max;
};

struct ScalarFileHeader{uint32_t n_zone;};


struct RawFlux
{
  uint32_t id_source;
  uint32_t id_target;
  double_t flux_source_target;
  double_t flux_target_source;
};

struct RawScalar{
  double_t value;
};


struct RawDataScalar
{
  ScalarFileHeader header;
  std::vector<RawScalar> values;

  static RawDataScalar read(std::string_view path);
  
};


struct RawDataFlux
{
  FluxFileHeader header;
  std::vector<RawFlux> fluxes;

  static RawDataFlux read(std::string_view path);
};


#endif //__RAW_DATA_FLOW_HPP__