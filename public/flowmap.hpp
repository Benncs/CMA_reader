#ifndef __FLOW_MAP_HPP__
#define __FLOW_MAP_HPP__

#include <rawdata.hpp>
#include <vector>

#include <cstddef>
#include <span>

#define lin_index(i_r, i_c, n_x) (i_r) * (n_x) + (i_c)

inline double lin_index_rm(size_t i_r, size_t i_c, size_t n_c)
{
  return (i_r) * (n_c) + (i_c);
}

inline double lin_index_cm(size_t i_r, size_t i_c, size_t n_r)
{
  return i_c * n_r + i_r;
}

struct FlowInfo;

class FlowMap
{
public:
  FlowMap() = default;
  FlowMap(size_t n, bool row_major = false);
  inline double &operator()(size_t i, size_t j)
  {
    // As flow map has to be square, we can pass n_row instead of n_col when
    // using column major
    return flows[f_index(i, j, this->n_row)];
  }

  inline size_t getN() const
  {
    return n_row;
  }
  bool row_major;

  inline std::span<double const> data() const
  {
    return std::span<double const>(flows);
  }
  inline std::span<double> data()
  {
    return std::span<double>(flows);
  }

private:
  friend FlowInfo;

  size_t n_row;
  std::vector<double> flows;
  double (*f_index)(size_t, size_t, size_t) = &lin_index_cm;
};

struct FlowInfo
{
  FlowMap flows;
  std::vector<std::vector<size_t>> neigbors;

  static FlowInfo read(std::string_view filepath, bool row_major = false);

  static FlowInfo fromRawData(RawDataFlux &&data, bool row_major = false);
};

#endif //__FLOW_MAP_HPP__
