/*******************************************************************************
 * @file    finit_state_machine.h
 * @author  happy-sloth
 * @version V1.0.0
 * @date    29-Oct-2021
 * @brief
 *******************************************************************************/

/* Includes*/
#include <stdlib.h>
#include <string.h>
#include "state_machine.h"

/* Public defines */

/* Private macro*/
#define START_STATE 0xFFFF
/* Private types
 * -------------------------------------------------------------*/
typedef struct
{
    uint32_t                dest_state;
    fsm_events_register_t   event;
}   list_node_t;

typedef struct transition_list
{
    list_node_t    node;
    struct transition_list*    next_node;
}   transition_list_t;

typedef struct
{
    transition_list_t**   state_transitions_list;
}   transitions_matrix_t;

typedef struct
{
    uint32_t    previous_state;
    uint32_t    current_state;
    uint32_t    next_state;
}   fsm_status_t;

typedef struct
{
    fsm_states_list_t*      p_states;
    uint32_t                num_of_states;
    transitions_matrix_t    transition_matrix;
    fsm_status_t            status;
}   fsm_t;

/* Private function prototypes*/


/* Private constants
 * ---------------------------------------------------------*/


/* Private variables
 * ---------------------------------------------------------*/

/* Public function */
fsm_instance_t fsm_init(fsm_states_list_t* states, uint32_t num_of_states)
{
    fsm_t* p_instance = NULL;

    if ((p_instance = malloc(sizeof(fsm_t))) == NULL)
    {
        return NULL;
    }

    memset(p_instance, 0, sizeof(fsm_t));

    if((p_instance->transition_matrix.state_transitions_list =
        malloc(sizeof(transition_list_t*)*num_of_states)) == NULL)
    {
        free(p_instance);
        return NULL;
    }

    memset(p_instance->transition_matrix.state_transitions_list, 0, sizeof(transition_list_t*)*num_of_states);

    p_instance->status.previous_state = START_STATE;
    p_instance->status.current_state = 0;
    p_instance->status.next_state = 0;

    p_instance->num_of_states = num_of_states;
    p_instance->p_states = states;

    return p_instance;
}

void FSM_execute (fsm_instance_t fsm_instance, fsm_events_register_t event)
{
    fsm_t* b_fsm_instance = (fsm_t*)fsm_instance;
    transition_list_t* b_p_node = b_fsm_instance->transition_matrix.state_transitions_list[b_fsm_instance->status.current_state];

    while (b_p_node->next_node != NULL && b_p_node->node.event != event)
    {
         b_p_node = b_p_node->next_node;
    }

    if(b_p_node->node.event == event)
         b_fsm_instance->status.next_state = b_p_node->node.dest_state;

    int repeat = 0;
    do{

        if (b_fsm_instance->status.current_state != b_fsm_instance->status.previous_state)
        {
            if (b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.input_action != NULL)
                b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.input_action();

            b_fsm_instance->status.previous_state = b_fsm_instance->status.current_state;
            repeat = 0;
        }

        if (b_fsm_instance->status.current_state == b_fsm_instance->status.previous_state &&
            b_fsm_instance->status.current_state == b_fsm_instance->status.next_state)
        {
            if (b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.routine_action != NULL)
                b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.routine_action();

        }

        if (b_fsm_instance->status.current_state != b_fsm_instance->status.next_state)
        {
            if(b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.output_action != NULL)
                b_fsm_instance->p_states[b_fsm_instance->status.current_state].state.output_action();

            b_fsm_instance->status.current_state = b_fsm_instance->status.next_state;
            repeat = 1;
        }
    }while (repeat);
}

void fsm_add_transitions(fsm_instance_t fsm_instance, uint32_t state_index_from,
                         uint32_t state_index_to, fsm_events_register_t event)
{
    transition_list_t* p_node = NULL;
    fsm_t* p_fsm_instance = (fsm_t*)fsm_instance;

    if((p_node = malloc(sizeof(transition_list_t))) == NULL)
        return;

    memset(p_node, 0, sizeof(transition_list_t));

    p_node->node.dest_state = state_index_to;
    p_node->node.event = event;

    transition_list_t** p_list = &(p_fsm_instance->transition_matrix.state_transitions_list[state_index_from]);
    transition_list_t* b_p_node = *(p_list);
    if (*p_list == NULL)
    {
        *p_list = p_node;
    }
    else
    {
         while (b_p_node->next_node != NULL)
         {
             b_p_node = b_p_node->next_node;
         }
         b_p_node->next_node = p_node;
    }
}

void fsm_reset(fsm_instance_t fsm_instance)
{
    ((fsm_t*)fsm_instance)->status.previous_state = START_STATE;
    ((fsm_t*)fsm_instance)->status.current_state = 0;
    ((fsm_t*)fsm_instance)->status.next_state = 0;
}

void fsm_deinit(fsm_instance_t fsm_instance)
{
    /*
     *  Delete all elements in transition matrix and instance
     * */
}
/* Private functions ------------------------------------------------------- */

/*****************************END OF FILE**************************************/
