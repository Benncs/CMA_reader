#include "flowmap.hpp"
#include "rawdata.hpp"
#include <algorithm>
#include <string_view>

void padVector(std::vector<size_t> &vec, size_t targetSize, size_t i)
{
  while (vec.size() < targetSize)
  {
    vec.push_back(i);
  }
}
void padVectors(std::vector<std::vector<size_t>> &vecOfVecs)
{
  size_t maxSize = 0;
  for (const auto &vec : vecOfVecs)
  {
    if (vec.size() > maxSize)
    {
      maxSize = vec.size();
    }
  }

  for (size_t i = 0; i < vecOfVecs.size(); ++i)
  {
    padVector(vecOfVecs[i], maxSize, i);
  }
}

FlowMap::FlowMap(size_t n,bool _row_major):row_major(_row_major)
{ 
  if(row_major)
  {
    f_index = &lin_index_rm;
  }
  
  this->n_row = n;
  this->flows.resize(n * n);
  std::fill(flows.begin(), flows.end(), 0.);
}


FlowInfo FlowInfo::read(std::string_view filepath, bool row_major)
{
    return fromRawData(RawDataFlux::read(filepath),row_major);
}

FlowInfo FlowInfo::fromRawData(RawDataFlux &&data, bool row_major )
{
  FlowInfo result;

  FlowMap flows(data.header.n_zone,row_major);

  std::vector<std::vector<size_t>> neigbors(
      data.header
          .n_zone); // Foreach zone with at least a neighbor, vector of vector
                    // because neigbor will be redistributed amoung compartments

  for (auto &&rawflux : data.fluxes)
  {
    flows(rawflux.id_source, rawflux.id_target) += rawflux.flux_source_target;
    flows(rawflux.id_target, rawflux.id_source) = rawflux.flux_target_source;
    neigbors[rawflux.id_source].emplace_back(rawflux.id_target);
  }

  padVectors(neigbors);

  result.flows = flows;
  result.neigbors = neigbors;

  return result;
}

