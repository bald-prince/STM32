

#ifndef _SCHEDULER_H
#define _SCHEDULER_H

/* exact-width signed integer types */
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;

/* exact-width unsigned integer types */
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;

typedef void (*MyTaskFunction_t)(void);


// ------ Public data type declarations ----------------------------

// User-defined type to store required data for each task
typedef struct
{
   // Pointer to the task
   // (must be a 'uint32_t (void)' function)
   uint32_t (*pTask)(void);
   //  void (*pTask) (void);

   // Delay (ticks) until the task will (next) be run
   uint32_t Delay;

   // Interval (ticks) between subsequent runs.
   uint32_t Period;
} sTask_t;


// ------ Public constants -------------------------------------------------------------
// The maximum number of tasks required at any one time
// during the execution of the program

// MUST BE CHECKED FOR EACH PROJECT (*not* dynamic)
#define SCH_MAX_TASKS (5)

// Usually set to 1, unless 'Long Tasks' are employed
#define SCH_TICK_COUNT_LIMIT (1)

// Default value for pTask (no task at this location)
#define SCH_NULL_PTR ((uint32_t(*)(void))0)


// ------ Public function prototypes (declarations) --------------------------
void SCH_Start(void);
void SCH_Dispatch_Tasks(void);

void SCH_Add_Task(uint32_t (*pTask)(),
                  const uint32_t DELAY,   // Ticks
                  const uint32_t PERIOD); // Ticks

void SCH_change_Task(uint32_t (*pTask)(),
                     const uint32_t DELAY,
                     const uint32_t PERIOD);

void SCH_delete_Task(uint32_t (*pTask)());
void delay_sch_ms(unsigned int ms);
unsigned int get_tick_counter(void);
void TIMX_IRQHandler_user(void);

#endif

