#include <DynamixelWorkbench.h>
#include <Arduino.h>
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
// #define DXL_ID    1
#define DXL_ID2    0
#define DXL_ID3    1
#define DXL_ID4    2

#define deg2dx  4095/360

DynamixelWorkbench dxl_wb;
int n = 3;

uint8_t dxl_id[3] = { DXL_ID2, DXL_ID3,DXL_ID4};//{DXL_ID, DXL_ID2, DXL_ID3,DXL_ID4};
const uint8_t handler_index = 0;
// int32_t pos[3] ={0*deg2dx,120*deg2dx,0*deg2dx};
int32_t pos[3] ={2048,2048,2048};
int32_t pos2[3] ={2048,1024,3072};
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
  //여기 부분을 지워면 동일한 속도로 움직임
  // case1 : 속도 프로파일 120으로 했을때 안맞음 : 왔다 갔다 하는 시간이 다른거 같음. => 증분값과 싱크가 안맞는듯
  // 증분으로 각도 주면 안되겠음.
  dxl_wb.writeRegister(dxl_id[0], "Profile_Velocity", 150, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Velocity", 150, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Velocity", 150, &log);
  // dxl_wb.writeRegister(dxl_id[3], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[0], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Acceleration", 12, &log);
  // dxl_wb.writeRegister(dxl_id[3], "Profile_Acceleration", 4, &log);

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



bool mode = true;
// bool result = false;
void loop() 
{
  const char *log;
  bool result = false;
  // if(mode){
  //   //초기값 각도에서 타겟각도로 움직임. 
  //   // x1 += inc1; 
  //   x2 += inc2;// x3 += inc3; //x4 += inc4;
  //   //pos[0] = x1;  
  //     pos[1] = x2;    pos[2] = 4095-x2; //pos[3] = x4;
  //   // if(pos[0] >= ang1t*deg2dx && pos[1] >= ang2t*deg2dx && pos[2] >= ang3t*deg2dx ){//&& pos[3] >= ang4t*deg2dx){
  //   //   mode =false;
  //   //   // Serial.print(" mode = ");Serial.println(mode);
  //   //   }
  //   if(pos[1]>4000)mode =false;
  // }
  // else{
  //   x2 -= inc2;
  //   pos[1] = x2;    pos[2] = 4095-x2;
  //   if(pos[1]<10)mode =true;
  // }
  
  // Serial.print(pos[1]);Serial.print(" ");Serial.println(mode);
  result = dxl_wb.syncWrite(handler_index,&pos[0], &log);
  delay(3000);
  swap(pos,pos2);
  // result = dxl_wb.syncWrite(handler_index,&pos[1], &log);
  // result = dxl_wb.syncWrite(handler_index,&pos[2], &log);
  // delay(10);
}
void swap(int32_t *p, int32_t *p2){
  int32_t temp = p[1];
  p[1] = p2[1];
  p2[1] = temp;
  int32_t temp2 = p[2];
  p[2] = p2[2];
  p2[2] = temp2;
}