#include <pump.h>
#include "main.h"
#include <stdint.h>  
#include <stdbool.h> 

typedef enum
{
    INIT,
    RUN
} irrigation_state_t;

typedef struct
{
    irrigation_state_t state;
    uint32_t on_pump_start_time;
    uint32_t off_pump_start_time;
    bool on_pump;
} irrigation_t;

irrigation_t irrigation_pump[MAX_PUMPS];

// Function Prototypes

void irrigation_init(void)
{
    for (int i = 0; i < MAX_PUMPS; i++)
    {
        irrigation_pump[i].state = INIT;
        irrigation_pump[i].on_pump_start_time = 0;
        irrigation_pump[i].off_pump_start_time = 0;
        irrigation_pump[i].on_pump = false;

        // Ensure the pump is off initially
        HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin,PUMP_RELAY_OFF);
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET); 
    }
}

void irrigation_run(void)
{
    for (int i = 0; i < MAX_PUMPS; i++)
    {

        switch (irrigation_pump[i].state)
        {
        case INIT:
            // Turn on the pump
            HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, PUMP_RELAY_ON);
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); 
            irrigation_pump[i].on_pump = true;
            irrigation_pump[i].on_pump_start_time = HAL_GetTick();
            irrigation_pump[i].state = RUN;
            break;

        case RUN:
            if (irrigation_pump[i].on_pump)
            {
                // Check if ON duration has elapsed (seconds)
                if ((HAL_GetTick() - irrigation_pump[i].on_pump_start_time) >= PUMP_ON_DELAY)
                {
                    HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, PUMP_RELAY_OFF);
                    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
                    irrigation_pump[i].on_pump = false;
                    irrigation_pump[i].off_pump_start_time = HAL_GetTick();
                }
            }
            else
            {
                // Check if OFF duration has elapsed (seconds)
                if ((HAL_GetTick() - irrigation_pump[i].off_pump_start_time) >= PUMP_OFF_DELAY)
                {
                    HAL_GPIO_WritePin(pump_GPIO_Port, pump_Pin, PUMP_RELAY_ON);
                    HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin, GPIO_PIN_SET);
                    irrigation_pump[i].on_pump = true;
                    irrigation_pump[i].on_pump_start_time = HAL_GetTick();
                }
            }
            break;
        }
    }
}
