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


Move Alphabeta::get_move(State *state, int depth) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int value=-10000;
  Move bestMove;
  for(auto it:state->legal_actions) {
    value=std::max(value,get_value(state->next_state(it),depth,-175,175,state->player));
    bestMove=it;
  }
  return bestMove;
}

int Alphabeta::get_value(State *state, int depth, int alpha, int beta, int me) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  if(depth==0) {
    return state->evaluate(me);
  }
  else if(state->player==me) {
    // 我方
    int value=-10000;
    for(auto it : state->legal_actions) {
      value=std::max(value,get_value(state->next_state(it),depth-1,alpha,beta,me));
      alpha=std::max(value,alpha);
      if(alpha>=beta) {
        break;
      }
    }
    return alpha;
  }
  else {
    // 敵方
    int value=10000;
    for(auto it : state->legal_actions) {
      value=std::min(value,get_value(state->next_state(it),depth-1,alpha,beta,me));
      beta=std::min(beta,value);
      if(beta<=alpha) {
        break;
      }
    }
    return beta;
  }
}
