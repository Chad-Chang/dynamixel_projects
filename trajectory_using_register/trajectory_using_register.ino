#include <DynamixelWorkbench.h>
#include <Arduino.h>
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
// #define DXL_ID    1
#define DXL_ID2    2
#define DXL_ID3    11
#define DXL_ID4    15

#define deg2dx  4095/360

DynamixelWorkbench dxl_wb;
int n = 3;

uint8_t dxl_id[3] = { DXL_ID2, DXL_ID3,DXL_ID4};//{DXL_ID, DXL_ID2, DXL_ID3,DXL_ID4};
const uint8_t handler_index = 0;
// int32_t pos[3] ={0*deg2dx,120*deg2dx,0*deg2dx};
int32_t pos[3] ={0,0,0};
uint16_t model_number = 0;


void setup() 
{
  Serial.begin(1000000);
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
 
 for (int cnt = 0; cnt < n; cnt++)
  {
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
  }
  
  dxl_wb.writeRegister(dxl_id[0], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[0], "Profile_Acceleration", 4, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Acceleration", 4, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Acceleration", 4, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Acceleration", 4, &log);

  result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Position", &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync write handler");
  }
  
  result = dxl_wb.syncWrite(handler_index, &pos[0], &log);
  // pos[0] = 360*deg2dx; 
  // pos[1] = 240*deg2dx; 
  // pos[2] = 240*deg2dx;
  delay(3000);
}


int t1= 0; int t1s= 0; uint32_t t1f= 10000;
int t2= 0; int t2s= 0; uint32_t t2f= 10000;
int t3= 0; int t3s= 0; uint32_t t3f= 10000;
int t4= 0; int t4s= 0; uint32_t t4f= 10000;
int inc1 = 1; int inc2 = 1; int inc3 = 1;int inc4 = 1;

uint32_t ang1s = 0; uint32_t ang1t= 360;
uint32_t ang2s = 0; uint32_t ang2t= 360;
uint32_t ang3s = 0; uint32_t ang3t= 360;
uint32_t ang4s = 0; uint32_t ang4t= 360;
int32_t x1 = 0; int32_t x2 = 0; int32_t x3 = 0;int32_t x4 = 0;
bool mode = true;
// bool result = false;
void loop() 
{
  const char *log;
  bool result = false;
  if(mode){
    //초기값 각도에서 타겟각도로 움직임. 
    x1 += inc1; x2 += inc2; x3 += inc3; //x4 += inc4;
    pos[0] = x1;    pos[1] = x2;    pos[2] = x3; //pos[3] = x4;
    // Serial.print(" t1 = ");Serial.print(ang1t*deg2dx); Serial.print(" a1 = ");Serial.println(x1);
    // Serial.print(" t2 = ");Serial.print(ang2t*deg2dx);Serial.print(" a2 = ");Serial.println(x2);
    // Serial.print(" t3 = ");Serial.print(ang3t*deg2dx);Serial.print(" a3 = ");Serial.println(x3);
    if(pos[0] >= ang1t*deg2dx && pos[1] >= ang2t*deg2dx && pos[2] >= ang3t*deg2dx ){//&& pos[3] >= ang4t*deg2dx){
      mode =false;
      // Serial.print(" mode = ");Serial.println(mode);
      }
  }
  else{
    x1 -= inc1;    x2 -= inc2;    x3 -= inc3; //x4 += inc4;
    pos[0] = x1;    pos[1] = x2;    pos[2] = x3;  //pos[3] = x4;
    // Serial.print(" t1 = ");Serial.print(ang1s*deg2dx); Serial.print(" a1 = ");Serial.println(x1);
    // Serial.print(" t2 = ");Serial.print(ang2s*deg2dx);Serial.print(" a2 = ");Serial.println(x2);
    // Serial.print(" t3 = ");Serial.print(ang3s*deg2dx);Serial.print(" a3 = ");Serial.println(x3);
    if(pos[0] <= ang1s*deg2dx && pos[1] <= ang2s*deg2dx && pos[2] <= ang3s*deg2dx){//&& pos[3] <= ang4s*deg2dx){
      mode =true;
      // Serial.print(" mode = ");Serial.println(mode);
      }
  }
  
  // Serial.print(" x1= ");Serial.print(x1);Serial.print(" x2= ");Serial.print(x2); Serial.print(" x3= ");Serial.println(x3);
  // Serial.print(4096);
  // Serial.print(" , ");
  // Serial.println(0);
  result = dxl_wb.syncWrite(handler_index,&pos[0], &log);
  
  // result = dxl_wb.syncWrite(handler_index,&pos[1], &log);
  // result = dxl_wb.syncWrite(handler_index,&pos[2], &log);
  // delay(10);
}