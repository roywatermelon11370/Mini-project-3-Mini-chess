#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../state/state.hpp"
#include "./submission.hpp"
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

Move Submission::get_move(State *state, int depth) {
  if(!state->legal_actions.size())
    state->get_legal_actions();

  int value=-1000000;
  Move best;
  int tmp;
  for(auto it:state->legal_actions) {
    if(value<(tmp=get_value(state->next_state(it),depth,-10000000,10000000,state->player, Move({{0,0},{0,0}}), Move({{0,0},{0,0}}), Move({{0,0},{0,0}})))) {
      value=tmp;
      best=it;
    }
  }
  return best;
}

int Submission::get_value(State *state, int depth, int alpha, int beta, int me, Move pre1, Move pre2, Move pre3) {
  if(state->legal_actions.empty()) {
        state->get_legal_actions();
  }

  if(depth==0) {
    return state->evaluate(me);
  }

  if(state->game_state==WIN) {
    if(state->player==me) return 71227122;
    else return -71227122;
  }

  if(state->player==me) {
    // 我方
    for(auto it : state->legal_actions) {
      if(!(it.second==pre1.first)&&!(it.second==pre2.first&&pre1.second==pre3.first)) {
        alpha=std::max(get_value(state->next_state(it),depth-1,alpha,beta,me,it,pre1,pre2),alpha);
        if(alpha>=beta) break;
      }
    }
    return alpha;
  }
  else {
    // 敵方
    for(auto it : state->legal_actions) {
      if(!(it.second==pre1.first)&&!(it.second==pre2.first&&pre1.second==pre3.first)) {
        beta=std::min(beta,get_value(state->next_state(it),depth-1,alpha,beta,me,it,pre1,pre2));
        if(beta<=alpha) break;
      }
    }
    return beta;
  }
}
