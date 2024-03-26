#include "flowmap.hpp"
#include "rawdata.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iterator>
#include <pybind11/buffer_info.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <string_view>
namespace py = pybind11;

py::array_t<double> flow_info_to_numpy(FlowInfo &&flow_info)
{
  if (flow_info.flows.data().size() != 0)
  {
    size_t shape = flow_info.flows.getN();
    auto origin = flow_info.flows.data();

    auto result = py::array_t<double_t>(
        py::buffer_info(origin.data(),
                        sizeof(double_t),
                        py::format_descriptor<double_t>::format(),
                        2,
                        {shape, shape},
                        {sizeof(double_t) * shape,sizeof(double_t)}));

    return result;
  }
  else
  {
    return {};
  }
}

py::array_t<double> _read(std::string_view filepath)
{
  FlowInfo f = FlowInfo::read(filepath,true); //Numpy is row major
  return flow_info_to_numpy(std::move(f));
}

py::array_t<double_t> _read_scalar(std::string_view filepath)
{
  RawDataScalar f = RawDataScalar::read(filepath);

  if (f.values.size() != 0)
  {

    // Extract values from RawDataScalar to a vector
    std::vector<double> values;
    std::transform(f.values.begin(),
                   f.values.end(),
                   std::back_inserter(values),
                   [](const auto &i) { return i.value; });

    size_t s1 = 1;
    size_t s2 = values.size();

    auto result = py::array_t<double_t>(
        py::buffer_info(values.data(),
                        sizeof(double_t),
                        py::format_descriptor<double_t>::format(),
                        1,
                        {s2},
                        {sizeof(double_t) * s1}));
    return result;
  }
  else
  {
    return {};
  }
}

PYBIND11_MODULE(cma_read, m)
{
  m.def("read", &_read, "Read flowmap function");
  m.def("read_scalar", &_read_scalar, "Read scalar function");
}