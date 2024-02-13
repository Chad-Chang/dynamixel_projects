#include <DynamixelWorkbench.h>
#include <Arduino.h>
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID    2
#define DXL_ID2    1
#define deg2dx  4096/360

DynamixelWorkbench dxl_wb;

uint8_t dxl_id[2] = {DXL_ID,DXL_ID2};
uint16_t model_number = 0;
int32_t goal_position[2] ={0,0};
const uint8_t handler_index = 0;

void setup() 
{
  Serial.begin(57600);
  // while(!Serial); // Wait for Opening Serial Monitor

  const char *log;
  bool result = false;


  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }
for(int cnt = 0; cnt<2; cnt++){
  result = dxl_wb.ping(dxl_id[cnt], &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id[cnt]);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.jointMode(dxl_id[cnt], 0, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else
  {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is moving...");
}
  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Position", &log);
  
  result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  delay(1000);
    // for (int count = 0; count < 3; count++)
    // {
    //   dxl_wb.goalPosition(dxl_id, (int32_t)0);

    //   // dxl_wb.goalPosition(dxl_id, (int32_t)deg2dx*360);
    // }
  }
}
int t= 0;
int ts= 0;
int tf= 300;
int32_t x = 0;
int mode = 1;

void loop() 
{const char *log;
  if(mode == 1){
    if(t>tf){
      mode = -1;
    }
    t+=1;
    x =deg2dx *(180-180*cos(PI*t/(tf-ts)));
    goal_position[0] =x;
    goal_position[1] =x;
    Serial.println(x);
    Serial.print(4096);
    Serial.print(" , ");
    Serial.println(0);
  }
  else{
    if(t<0){
      mode =1; 
    }
    t-=1;
    x =deg2dx *(180-180*cos(PI*t/(tf-ts)));
    goal_position[0] =x;
    goal_position[1] =x;
    Serial.println(x);
    Serial.print(4096);
    Serial.print(" , ");
    Serial.println(0);
  }
  dxl_wb.goalPosition(dxl_id[1], x);
  dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  delay(10);
}