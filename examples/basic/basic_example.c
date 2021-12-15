#include "statemachine.h"

#include <stdio.h>
#include <stdint.h>

enum states {
  STATE_A,
  STATE_B,
  STATE_MAX,
};

static void StateAEnter(state_t previous_state, state_t current_state);
static state_t StateARunnable(state_t current_state);
static void StateALeave(state_t current_state, state_t next_state);

static void StateBEnter(state_t previous_state, state_t current_state);
static state_t StateBRunnable(state_t current_state);
static void StateBLeave(state_t current_state, state_t next_state);


int main(int argc, char *argv[]){
  statemachine_t basic_statemachine;
  state_functions_t basic_statemachine_matrix[STATE_MAX] = {
    {.enter = StateAEnter, .runnable = StateARunnable, .exit = StateALeave},
    {.enter = StateBEnter, .runnable = StateBRunnable, .exit = StateBLeave},
  };

  statemachine_init(&basic_statemachine, basic_statemachine_matrix, STATE_A);

  while(statemachine_process(&basic_statemachine) != STATE_FINAL);
  printf("statemachine finished...\n");

  return 0;
}


void StateAEnter(state_t previous_state, state_t current_state) {
  printf("entering state A\n");
}

state_t StateARunnable(state_t current_state) {
  static uint8_t i = 0;
  printf("running stateA for the %u. time\n", ++i);
  if (i == 10) {
    return STATE_B;
  }
  return current_state;
}

void StateALeave(state_t current_state, state_t next_state) {
  printf("leaving state A\n");
}


void StateBEnter(state_t previous_state, state_t current_state) {
  printf("entering state B\n");
}

state_t StateBRunnable(state_t current_state) {
  static uint8_t i = 0;
  printf("running stateB for the %u. time\n", ++i);
  if (i == 5) {
    return STATE_FINAL;
  }
  return current_state;
}

void StateBLeave(state_t current_state, state_t next_state) {
  printf("leaving state B\n");
}