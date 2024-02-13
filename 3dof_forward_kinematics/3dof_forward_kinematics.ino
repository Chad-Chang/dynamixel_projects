#include <DynamixelWorkbench.h>
#include <Arduino.h>
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID    1
#define DXL_ID2    11
#define DXL_ID3    15
#define deg2dx  4096/360

DynamixelWorkbench dxl_wb;
int n = 3;

uint8_t dxl_id[3] = {DXL_ID, DXL_ID2, DXL_ID3};
const uint8_t handler_index = 0;
int32_t pos[3] ={80*deg2dx,90*deg2dx,201*deg2dx};
uint16_t model_number = 0;


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
result = dxl_wb.addSyncWriteHandler(dxl_id[0], "Goal_Position", &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync write handler");
  }
  
  result = dxl_wb.syncWrite(handler_index, &pos[0], &log);
  pos[0] = 180*deg2dx; 
  pos[1] = 77.7*deg2dx; 
  pos[2] = 180*deg2dx;
  delay(3000);
}


int t1= 0; int t1s= 0; uint32_t t1f= 10000;
int t2= 0; int t2s= 0; uint32_t t2f= 10000;
int t3= 0; int t3s= 0; uint32_t t3f= 10000;
uint32_t ang1s= 180; uint32_t ang1t= 85;
uint32_t ang2s= 77.7; uint32_t ang2t= 180;
uint32_t ang3s= 180; uint32_t ang3t= 90;
int32_t x1 = 0; int32_t x2 = 0; int32_t x3 = 0;
int mode = 1;
// bool result = false;
void loop() 
{
  const char *log;
  bool result = false;
  if(mode == 1){
      if(t1>t1f && t2>t2f && t3>t3f){
      mode = -1;
    }
    t1+=1;t2+=1;t3+=1;
    x1 = deg2dx *((ang1t+ang1s)/2-(ang1t-ang1s)/2*cos(PI*t1/(t1f-t1s)));
    x2 = deg2dx *((ang2t+ang2s)/2-(ang2t-ang2s)/2*cos(PI*t2/(t2f-t2s)));
    x3 = deg2dx *((ang3t+ang3s)/2-(ang3t-ang3s)/2*cos(PI*t3/(t3f-t3s)));
    pos[0] = x1;
    pos[1] = x2;
    pos[2] = x3;
    // Serial.print(" x1 ");Serial.println(x1);Serial.print(" x2 ");Serial.println(x2); Serial.print(" x3 ");Serial.println(x3);
    // Serial.print(4096);
    // Serial.print(" , ");
    // Serial.println(0);
  }
  else{
    if(t1<0 && t1<0 && t1<0){
      mode =1; 
    }
    t1-=1;t2-=1;t3-=1;
    x1 = deg2dx *((ang1t+ang1s)/2-(ang1t-ang1s)/2*cos(PI*t1/(t1f-t1s)));
    x2 = deg2dx *((ang2t+ang2s)/2-(ang2t-ang2s)/2*cos(PI*t2/(t2f-t2s)));
    x3 = deg2dx *((ang3t+ang3s)/2-(ang3t-ang3s)/2*cos(PI*t3/(t3f-t3s)));
    pos[0] = x1;
    pos[1] = x2;
    pos[2] = x3;

    
  }
  Serial.print(" x1 ");Serial.println(x1);Serial.print(" x2 ");Serial.println(x2); Serial.print(" x3 ");Serial.println(x3);
  Serial.print(4096);
  Serial.print(" , ");
  Serial.println(0);
  result = dxl_wb.syncWrite(handler_index,&pos[0], &log);
  // delay(10);
}