#include "statemachine.h"

#include <stdio.h>

void statemachine_init(statemachine_t *handle, state_functions_t *state_matrix, state_t initial_state) {
  handle->sm = state_matrix;
  handle->current_state = STATE_START;
  handle->next_state = initial_state;
}

state_t statemachine_process(statemachine_t *handle) {
  if (handle->current_state == STATE_FINAL) {
    return STATE_FINAL;
  }
  
  if (handle->next_state != handle->current_state) {
    handle->current_state = handle->next_state;
    // handle enter state
    if ((handle->sm[handle->current_state]).enter != NULL) {
      (handle->sm[handle->current_state]).enter(handle->current_state);
    }
  }

  // process current state
  handle->next_state = (handle->sm[handle->current_state]).runnable(handle->current_state);

  if (handle->next_state != handle->current_state) {
    // leave state
    if ((handle->sm[handle->current_state]).exit != NULL) {
      (handle->sm[handle->current_state]).exit(handle->current_state);
    }
    if (handle->next_state == STATE_FINAL) {
      handle->current_state = STATE_FINAL;
    }
  }

  return handle->current_state;
}
