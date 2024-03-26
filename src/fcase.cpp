#include "fcase.hpp"
#include "flowmap.hpp"
#include "path_info.hpp"
#include "rawdata.hpp"
#include <algorithm>
#include <iterator>
#include <reactorstate.hpp>

static std::array<std::string, 5> files = {
    "./flowL.raw", "./flowG.raw", "./vofL.raw", "./vofG.raw", "./turbE.raw"};

FCase FCase::from_path(const std::string &case_path)
{
  auto paths = get_paths(case_path);
}

ReactorState ReactorState::read(const std::string &folder)
{
  ReactorState res;

  auto flowL = RawDataFlux::read(folder + files[0]);
  auto flowG = RawDataFlux::read(folder + files[1]);

  auto voll = RawDataScalar::read(folder + files[2]);
  auto volg = RawDataScalar::read(folder + files[3]);
  auto energy_disp = RawDataScalar::read(folder + files[4]);
  res.n_compartments = voll.header.n_zone;

  std::transform(voll.values.begin(),
                 voll.values.end(),
                 std::back_inserter(res.liquidVolume),
                 [](auto &&i) { return i.value; });
  std::transform(volg.values.begin(),
                 volg.values.end(),
                 std::back_inserter(res.gasVolume),
                 [](auto &&i) { return i.value; });

  std::transform(energy_disp.values.begin(),
                 energy_disp.values.end(),
                 std::back_inserter(res.energy_dissipation),
                 [](auto &&i) { return i.value; });

  res.gas_flow = FlowInfo::fromRawData(std::move(flowG));
  res.liquid_flow = FlowInfo::fromRawData(std::move(flowL));

  return res;
}
