#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
#include <set>
#include <map>
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

// map<State*,int> visited;
// set<State*> ifVisited;

Move Alphabeta::get_move(State *state, int depth) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int value=-1000000;
  Move best;
  int tmp;
  for(auto it:state->legal_actions) {
    if(value<(tmp=get_value(state->next_state(it),depth,-300000,300000,state->player))) {
      value=tmp;
      best=it;
    }
  }
  return best;
}

int Alphabeta::get_value(State *state, int depth, int alpha, int beta, int me) {
  if(state->legal_actions.empty())
    state->get_legal_actions();

  if(depth==0) {
    return state->evaluate(me);
  }

  if(state->player==me) {
    // 我方
    for(auto it : state->legal_actions) {
      
        alpha=std::max(get_value(state->next_state(it),depth-1,alpha,beta,me),alpha);
        if(alpha>=beta) break;
      
    }
    return alpha;
  }
  else {
    // 敵方
    for(auto it : state->legal_actions) {
      
        beta=std::min(beta,get_value(state->next_state(it),depth-1,alpha,beta,me));
        if(beta<=alpha) break;
      
    }
    return beta;
  }
}
