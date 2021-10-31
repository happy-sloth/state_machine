#include <stdio.h>
#include "lib/state_machine.h"
#include <windows.h>

fsm_instance_t state_machine;

enum
{
    STATE_A = 0x00,
    STATE_B,
    STATE_C,
    STATE_D,

    NUM_OF_STATES,
}states_enum;

enum
{
    EVENT_A_AND_B = 0x01,
    EVENT_A_AND_C = 0x10,
    EVENT_B_TO_C = 0x11,
    EVENT_C_TO_D = 0x100,
    EVENT_D_TO_B = 0x110,
}events_enum;

fsm_events_register_t sm_events = 0;

char* event_to_text(fsm_events_register_t evt);

void state_a_input(void);
void state_a_action(void);
void state_a_output(void);

void state_b_input(void);
void state_b_action(void);
void state_b_output(void);

void state_c_input(void);
void state_c_action(void);

void state_d_action(void);
void state_d_output(void);

fsm_states_list_t states[NUM_OF_STATES] =
{
    [STATE_A] = {.state_index = STATE_A,
                 .state.input_action = state_a_input,
                 .state.routine_action = state_a_action,
                 .state.output_action = state_a_output},
    [STATE_B] = {.state_index = STATE_B,
                 .state.input_action = state_b_input,
                 .state.routine_action = state_b_action,
                 .state.output_action = state_b_output},
    [STATE_C] = {.state_index = STATE_C,
                 .state.input_action = state_c_input,
                 .state.routine_action = state_c_action,
                 .state.output_action = NULL},
    [STATE_D] = {.state_index = STATE_D,
                 .state.input_action = NULL,
                 .state.routine_action = state_d_action,
                 .state.output_action = state_d_output},
};

int main()
{
    printf("Start Program!\r\n");
    state_machine = fsm_init(states, NUM_OF_STATES);

    fsm_add_transitions(state_machine, STATE_A, STATE_B, EVENT_A_AND_B);
    fsm_add_transitions(state_machine, STATE_B, STATE_A, EVENT_A_AND_B);
    fsm_add_transitions(state_machine, STATE_A, STATE_C, EVENT_A_AND_C);
    fsm_add_transitions(state_machine, STATE_C, STATE_A, EVENT_A_AND_C);
    fsm_add_transitions(state_machine, STATE_B, STATE_C, EVENT_B_TO_C);
    fsm_add_transitions(state_machine, STATE_C, STATE_D, EVENT_C_TO_D);
    fsm_add_transitions(state_machine, STATE_D, STATE_B, EVENT_D_TO_B);

    fsm_events_register_t test_events[10] =
                        {0, EVENT_A_AND_B, 0, EVENT_A_AND_B, EVENT_A_AND_C, EVENT_C_TO_D, 0, EVENT_D_TO_B, EVENT_B_TO_C, EVENT_A_AND_C};
    uint8_t counter = 0;
    while(1)
    {
        if (counter < 10)
        {
            sm_events = test_events[counter];
            printf("Event is %s\n\r", event_to_text(sm_events));
            counter++;
        }
        else
        {
            break;
        }


        FSM_execute(state_machine, sm_events);
        Sleep(1000);
    }
    return 0;
}

void state_a_input(void)
{
    printf("State A input!\r\n");
}

void state_a_action(void)
{
     printf("State A action!\r\n");
}

void state_a_output(void)
{
     printf("State A output!\r\n");
}

void state_b_input(void)
{
     printf("State B input!\r\n");
}

void state_b_action(void)
{
     printf("State B action!\r\n");
}

void state_b_output(void)
{
     printf("State B output!\r\n");
}

void state_c_input(void)
{
     printf("State C input!\r\n");
}

void state_c_action(void)
{
     printf("State C action!\r\n");
}

void state_d_action(void)
{
     printf("State D action!\r\n");
}

void state_d_output(void)
{
    printf("State D output!\r\n");
}

char* event_to_text(fsm_events_register_t evt)
{
    char* str = NULL;
    switch(evt)
    {
        case EVENT_A_AND_B:
        {
            str = "EVENT_A_AND_B";
            break;
        }
        case EVENT_A_AND_C:
        {
            str = "EVENT_A_AND_C";
            break;
        }
        case EVENT_B_TO_C:
        {
            str = "EVENT_B_TO_C";
            break;
        }
        case EVENT_C_TO_D:
        {
            str = "EVENT_C_TO_D";
            break;
        }
        case EVENT_D_TO_B:
        {
            str = "EVENT_D_TO_B";
            break;
        }
        default:
            str = "Undefined evt";
            break;
    }

    return str;
}
