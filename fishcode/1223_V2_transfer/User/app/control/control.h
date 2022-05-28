#ifndef CONTROL_H
#define CONTROL_H

#include "bsp.h"

#define TailFinSwingSoftTimerID             1

#define PectoralFinQianHouSoftTimerID       2

#define PectoralFinUpSoftTimerID            3

#define PectoralFinDownSoftTimerID          4

#define PectoralFinRightSoftTimerID         5

#define PectoralFinLeftSoftTimerID          6

#define TailFinLeftSoftTimerID              7

#define TailFinRightSoftTimerID             8


void StartTailFinSwing(void);
uint8_t CheckTailFinSwingSoftTimerState(void);
void EndTailFinSwing(void);


void StartPectoralFinQianHouSwing(void);
uint8_t CheckPectoralFinQianHouSwingSoftTimerState(void);
void EndPectoralFinQianHouSwing(void);


void StartPectoralFinUp(void);
uint8_t CheckPectoralFinUpSoftTimerState(void);
void EndPectoralFinUp(void);


void StartPectoralFinDown(void);
uint8_t CheckPectoralFinDownSoftTimerState(void);
void EndPectoralFinDown(void);


void StartPectoralFinRight(void);
uint8_t CheckPectoralFinRightSoftTimerState(void);
void EndPectoralFinRight(void);

void StartPectoralFinLeft(void);
uint8_t CheckPectoralFinLeftSoftTimerState(void);
void EndPectoralFinLeft(void);

void StartTailFinLeft(void);
uint8_t CheckTailFinLeftSoftTimerState(void);
void EndTailFinLeft(void);

void StartTailFinRight(void);
uint8_t CheckTailFinRightSoftTimerState(void);
void EndTailFinRight(void);


#endif 
