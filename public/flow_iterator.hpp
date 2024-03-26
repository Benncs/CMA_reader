#ifndef __FLOW_ITERATOR_HPP__
#define __FLOW_ITERATOR_HPP__

#include "flowmap.hpp"
#include <span>
#include <string>
#include <reactorstate.hpp>

class FlowIterator
{
public:
  // FlowIterator(std::initializer_list<std::string_view> files,
  //              size_t n_repetition = 0);
  FlowIterator()=default;
  FlowIterator(std::span<std::string> files, size_t n_repetition = 0);

  ReactorState * next();

  ReactorState *get()
  {
    return this->it;
  }

  void setRepetition(size_t n_repetition){this->n_repeat = n_repetition;}

  size_t totalSteps()const{return flows.size()*(n_repeat+1);}

private:
  ReactorState *it;

  size_t current;
  size_t current_repeat;

  size_t end;
  size_t n_repeat;
  std::vector<ReactorState> flows;
};

#endif //__FLOW_ITERATOR_HPP__
