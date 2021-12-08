#include "statemachine.h"

#include <stdio.h>
#include <stdint.h>

enum states {
  STATE_A,
  STATE_B,
  STATE_MAX,
};

static void StateAEnter(statemachine_t *sm);
static void StateARunnable(statemachine_t *sm);
static void StateALeave(statemachine_t *sm);

static void StateBEnter(statemachine_t *sm);
static void StateBRunnable(statemachine_t *sm);
static void StateBLeave(statemachine_t *sm);


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


void StateAEnter(statemachine_t *sm) {
  printf("entering state A\n");
}

void StateARunnable(statemachine_t *sm) {
  static uint8_t i = 0;
  printf("running stateA for the %u. time\n", ++i);

  if (i == 10) {
    sm->next_state = STATE_B;
  }
}

void StateALeave(statemachine_t *sm) {
  printf("leaving state A\n");
}


void StateBEnter(statemachine_t *sm) {
  printf("entering state B\n");
}

void StateBRunnable(statemachine_t *sm) {
  static uint8_t i = 0;
  printf("running stateB for the %u. time\n", ++i);
  if (i == 5) {
    sm->next_state = STATE_FINAL;
  }
}

void StateBLeave(statemachine_t *sm) {
  printf("leaving state B\n");
}