#include "reactorstate.hpp"
#include <flow_iterator.hpp>

// FlowIterator::FlowIterator(std::span<std::string> files,
//                            size_t n_repetition)
// {
//   FlowIterator({files.begin(), files.end()}, n_repetition);
// }

FlowIterator::FlowIterator(std::span<std::string> files, size_t n_repetition)
  : current(0), current_repeat(0), n_repeat(n_repetition)
{

  try {

    for (auto &&f : files)
    {

      flows.push_back(ReactorState::read(f));
    }

    end = flows.size();
    if (flows.size() != 0)
    {
      it = &flows[current];
    }


  }
  catch (const std::exception&) 
  {
    it = nullptr;
  }
}
ReactorState * FlowIterator::next()
{
  if (current != end - 1)
  {
    current++;
  }
  else
  {
    if (current_repeat < n_repeat)
    {
      current_repeat++;
      current = 0;
    }
    else
    {

      it = nullptr;
      return it;
    }
  }
  it = &flows[current];
  return it;
}
