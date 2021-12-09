#include <mbed.h>
#include <math.h>
#include "TS_DISCO_F429ZI.h"
#include "FlashIAPBlockDevice.h"
#include "flash_data.h"
#include "TDBStore.h"
#include "movement.h"
#include "myUI.h"

#define My_LEG_LENGTH 80
#define INTERVAL 0.5
#define RECORD_TIME 20
#define SAMPLE_COUNT (int)(RECORD_TIME / INTERVAL)
#define FIRST_DB_BLOCK (ADDR_FLASH_SECTOR_5) // Sector 5, 128 Kbytes
#define SCREEN_MAX_Y 320

typedef enum
{
  MenuState,
  RecordState,
  ResultState,
} ProState;

void Init();
void Update();
void Control();
void PageMenu();
void PageRecord();
void PageResult();

void record();
void exportData();
bool extractData();
float displayDistant();
void wait(float s);

FlashIAPBlockDevice bd(FIRST_DB_BLOCK, 256 * 1024); //2 sectors
TDBStore nvStore(&bd);

//for exportData and extractData
float data[SAMPLE_COUNT][AXIS] = {};

TS_DISCO_F429ZI ts;
TS_StateTypeDef TS_State;
LCDUI lcd;
Movement m(My_LEG_LENGTH);
ProState state = MenuState;
Ticker tick;

int main()
{
  //faster update rate for control method
  tick.attach(&Control, 0.1f);
  Init();
  while (1)
  {
    Update();
    wait(0.5f);
  }
}

void Init()
{
  lcd.Init();
  bd.init();
  nvStore.init();
}
void Update()
{
  switch (state)
  {
  case MenuState:
    PageMenu();
    break;
  case RecordState:
    PageRecord();
    break;
  case ResultState:
    PageResult();
    break;
  }
}
void Control()
{
  ts.GetState(&TS_State);
  switch (state)
  {
  case MenuState:
    //record button
    if (TS_State.TouchDetected && TS_State.X > 10 && TS_State.X < 230 && TS_State.Y < SCREEN_MAX_Y - 65 && TS_State.Y > SCREEN_MAX_Y - 115)
    {
      state = RecordState;
    } //result button
    else if (TS_State.TouchDetected && TS_State.X > 10 && TS_State.X < 230 && TS_State.Y < SCREEN_MAX_Y - 185 && TS_State.Y > SCREEN_MAX_Y - 235)
    {
      state = ResultState;
    }

    break;
  case RecordState:
    break;
  case ResultState:
    break;
  }
}

//Menu
void PageMenu()
{
  lcd.PageMenu();
  state = MenuState;
}

//Record for 20 sec data
void PageRecord()
{
  lcd.PageCountDown(3);
  lcd.PageRecord();
  record();
  exportData();
  lcd.Display("Done!");
  wait(3.0f);
  lcd.Init();
  state = MenuState;
}

//display the data on the LCD
void PageResult()
{
  lcd.PageResult();
  if (extractData())
  {
    lcd.Display("No data!");
  }
  else
  {
    displayDistant();
  }
  wait(3.0f);
  lcd.Init();
  state = MenuState;
}

void record()
{
  for (int i = 0; i < SAMPLE_COUNT; i++)
  {
    float *angVel = m.GetAngVel();
    float *vel = m.GetVel(angVel);
    lcd.DisplayVel(vel);

    for (int axis = 0; axis < AXIS; axis++)
    {
      data[i][axis] = vel[axis];
    }
    //wait for 0.5sec
    wait(INTERVAL);
  }
}

/**
* @brief  Extract Data from the flash memory.
* @param  None.
* @retval If there's no data then true. Otherwise false.
*/
bool extractData()
{
  if (nvStore.get("_0000", &data, sizeof(data)))
  {
    return true;
  }
  for (int i = 0; i < SAMPLE_COUNT; i++)
  {
    lcd.DisplayVel(data[i]);
    wait(0.05);
  }
  return false;
}


// Store in the flash memory
void exportData()
{
  nvStore.set("_0000", &data, sizeof(data), 0);
}

//display total distance(cm)
float displayDistant()
{
  char str[32];
  float distance = 0;

  for (int i = 0; i < SAMPLE_COUNT; i++)
  {
    //distance per second
    distance += m.GetDistance(data[i]) * INTERVAL;
  }
  //not interest in the floating point of cm, round it to the nearest int
  sprintf(str, "Total Distance: %dcm", (int)round(distance));
  lcd.Display("");
  lcd.Display(str);
  return distance;
}

/**
* @brief  wait for seconds.
* @param  s: second.
* @retval None
*/
void wait(float s)
{
  wait_us((int)(1000 * 1000 * s));
}