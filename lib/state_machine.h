/*******************************************************************************
 * @file    finit_state_machine.h
 * @author  happy-sloth
 * @version V1.0.0
 * @date    29-Oct-2021
 * @brief
 *******************************************************************************/
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
/* Includes*/
#include <stdint.h>
/* Public defines */

/* Public types */
typedef void (*fsm_routine_t)(void);


typedef struct
{
    fsm_routine_t   input_action;
    fsm_routine_t   routine_action;
    fsm_routine_t   output_action;
}   fsm_state_t;

typedef uint32_t    fsm_events_register_t;
typedef void*       fsm_instance_t;

typedef struct
{
    fsm_state_t state;
    uint32_t    state_index;
}   fsm_states_list_t;

/* Exported functions ------------------------------------------------------- */
/**
*	\brief This function execute state machine once and must be called with necessary
*          period.
*
*	\param None
*	\return None
*/
fsm_instance_t fsm_init(fsm_states_list_t* states, uint32_t num_of_states);

/**
*	\brief This function execute state machine once and must be called with necessary
*          period.
*
*	\param None
*	\return None
*/
void FSM_execute (fsm_instance_t fsm_instance, fsm_events_register_t event);

/**
*	\brief
*
*	\param None
*	\return None
*/
void fsm_add_transitions(fsm_instance_t fsm_instance, uint32_t state_index_from, uint32_t state_index_to, fsm_events_register_t event);

/**
*	\brief
*
*	\param None
*	\return None
*/
void fsm_reset(fsm_instance_t fsm_instance);

/**
*	\brief
*
*	\param None
*	\return None
*/
void fsm_deinit(fsm_instance_t fsm_instance);


#endif // STATE_MACHINE_H
