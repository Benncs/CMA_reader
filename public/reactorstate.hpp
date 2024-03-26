#ifndef __REACTOR_STATE_HPP__
#define __REACTOR_STATE_HPP__

#include "flowmap.hpp"
#include <string_view>

struct ReactorState
{
  FlowInfo liquid_flow;
  FlowInfo gas_flow;
  std::vector<double> liquidVolume;
  std::vector<double> gasVolume;
  std::vector<double> energy_dissipation;
  size_t n_compartments;
  static ReactorState read(const std::string &folder);
};

#endif //__REACTOR_STATE_HPP__
