#include <DynamixelWorkbench.h>
#include <Servo.h> 
#include <math.h>
int servoPin = 9;
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""     
#endif   
#define BAUDRATE  1000000
#define pi  3.14159265359
#define DXL_ID    1
#define DXL_ID2   2
#define DXL_ID3   3
#define DXL_ID4   4
#define DXL_ID5   5
#define DXL_ID6   6
uint8_t dxl_id[6]  = {DXL_ID,DXL_ID2,DXL_ID3,DXL_ID4,DXL_ID5,DXL_ID6};
const uint8_t handler_index = 0;
DynamixelWorkbench dxl_wb;

float ang[6];
float a[6];
int32_t goal_position[6] = {0,0,0,0,0,0};
String s1;
String s2;
int angle(float x){
  int angle2 = (int)((x/360)*4095);
  return angle2;
}

void serialEvent(){
  if (Serial.available() > 0) {
    for(int i =0; i<6;i++){
      a[i] = Serial.parseFloat();
      s1 = s1 + String(a[i]);
      goal_position[0] = angle(a[0]);
      goal_position[1] = angle(a[1]);
      goal_position[2] = angle(a[2]);
      goal_position[3] = angle(a[3]);
      goal_position[4] = angle(a[4]);
      goal_position[5] = angle(a[5]); 
      if(i != 5){s1 = s1 +',';}
    }
  // Serial.println(s1);
  s1 = "";
  }
}

void setup(){
  Serial.begin(115200);
  // Serial1.begin(115200);
  Serial.setTimeout(1);
  const char *log;
  uint16_t model_number  = 0;
  uint16_t model_number2 = 0;
  uint16_t model_number3 = 0;
  uint16_t model_number4 = 0;
  uint16_t model_number5 = 0;
  uint16_t model_number6 = 0;
  bool result = false;
  bool result2 = false;
  bool result3 = false;
  bool result4 = false;
  bool result5 = false;
  bool result6 = false;
  result  = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
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
  for (int cnt = 0; cnt < 6; cnt++)
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
  }
  Serial.println(result);
  result  = dxl_wb.jointMode(dxl_id[0], 60, 0, &log);
  Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[1], 60, 0, &log);
  Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[2], 60, 0, &log);
  Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[3], 40, 0, &log);
  Serial.println(result);
  // result = dxl_wb.torque(dxl_id[4],1, &log);
  // result = dxl_wb.torque(dxl_id[5],1, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[0], "Profile_Velocity", 120, &log);      
  dxl_wb.writeRegister(dxl_id[2], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[4], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[5], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[0], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[1], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[2], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[3], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[4], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[5], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[0], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[1], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[2], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[3], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[4], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[5], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[0], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[4], "Profile_Acceleration", 12, &log);
  dxl_wb.writeRegister(dxl_id[5], "Profile_Acceleration", 12, &log);
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
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync write handler");
  }

  result = dxl_wb.addSyncReadHandler(dxl_id[0], "Present_Position", &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to add sync read handler");
  }
    goal_position[0] = 0;// angle(0);
    goal_position[1] = 0;//angle(1.892950/pi*180);
    goal_position[2] = 0;//angle(0.515393/pi*180);
    goal_position[3] = 0;//angle(0);
    goal_position[4] = 0;//angle(0.192981/pi*180);
    goal_position[5] = 0;//angle(0);
  result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to sync write position");
  }
  delay(1000);
}

int32_t error[6] = {0,0,0,0,0,0};
unsigned long past = 0;
int32_t get_data[6];
int err_threshold = 30;

void loop(){
  const char *log;
  bool result = false;  
  unsigned long now = millis();
  for(int j =0; j<6;j++){
      a[j] = Serial.parseFloat();
      s2 = s2 + String(a[j]);
      if(j != 5){s2 = s2 +',';}
    }
  result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  result = dxl_wb.syncRead(handler_index, &log);
  if (result == false)
    {
      Serial.println(log);
      Serial.println("Failed to sync read position");
    }
  result = dxl_wb.getSyncReadData(handler_index, &get_data[0], &log);
  if (result == false)
    {
      Serial.println(log);
    }
    else
    {
      Serial.print("[ID ");
      Serial.print(dxl_id[0]);
      Serial.print(" ]");
      Serial.print(" Goal Position : ");
      Serial.print(goal_position[0]);
      Serial.print(" Present Position : ");
      Serial.print(get_data[0]);
      Serial.print(" [ID ");
      Serial.print(dxl_id[1]);
      Serial.print(" ]");
      Serial.print(" Goal Position : ");
      Serial.print(goal_position[1]);
      Serial.print(" Present Position : ");
      Serial.println(get_data[1]);
    }

    for(int i = 0; i<4;i++){
      error[i] = abs(goal_position[i]-get_data[i]);
      if(i<3){s2 = s2 + error[i]+ ",";}
    }

    // Serial.print("error");  Serial.print(error[0]);Serial.print(",");Serial.print(error[1]);Serial.print(",");Serial.print(error[2]);Serial.print(",");Serial.println(error[3]);

    // if(error[0]<err_threshold&&error[1]<err_threshold&&error[2]<err_threshold&&error[3]<err_threshold)Serial.println("transmit");
    // else Serial.println("no");
    s2 ="";
    // Serial.println(now - past);
    past = now;
   }