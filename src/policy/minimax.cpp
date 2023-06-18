#include <cstdlib>
#include <cmath>
#include "../state/state.hpp"
#include "./minimax.hpp"

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int max=-1000000,value;
  for(auto it:state->legal_actions) {
    value=std::max(value,get_value(state->next_state(it),depth-1));
  }
  for(auto it:state->legal_actions) {
    if(state->next_state(it)->evaluate()==max) {
      return it;
    }
  }
}

int Minimax::get_value(State *state, int depth) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  if(depth==0) {
    return state->evaluate();
  }
  else if(depth%2==1) {
    // 我方
    int max=-1000000;
    for(auto it : state->legal_actions) {
      max=std::max(max,get_value(state->next_state(it),depth-1));
    }
    return max;
  }
  else {
    // 敵方
    int min=1000000;
    for(auto it : state->legal_actions) {
      min=std::min(min,get_value(state->next_state(it),depth-1));
    }
    return min;
  }
}
