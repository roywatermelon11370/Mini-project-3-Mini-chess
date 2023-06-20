#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../state/state.hpp"
#include "./minimax.hpp"
#include <map>
#include <set>
using namespace std;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

// struct cmp {
//   bool operator()(const State& lhs, const State& rhs) const {
//     return lhs.value<rhs.value;
//   }
// };
// map<State,int,cmp> visited;
// set<State,cmp> ifVisited;

Move Minimax::get_move(State *state, int depth) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int value=-10000000;
  Move best;
  int tmp;
  for(auto it:state->legal_actions) {
    if(value<(tmp=get_value(state->next_state(it),depth,!state->player))) {
      value=tmp;
      best=it;
    }
  }
  return best;
}

int Minimax::get_value(State *state, int depth, int me) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  if(depth==0) {
    int value;
    value=state->evaluate(me);
    return value;
  }
  else if(state->player==me) {
    // 我方
    int max=-10000;
    for(auto it : state->legal_actions) {
      max=std::max(max,get_value(state->next_state(it),depth-1,me));
    }
    //visited[state]=max;
    return max;
  }
  else {
    // 敵方
    int min=10000;
    for(auto it : state->legal_actions) {
      min=std::min(min,get_value(state->next_state(it),depth-1,me));
    }
    //visited[state]=min;
    return min;
  }
}
