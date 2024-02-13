#include <DynamixelWorkbench.h>
#include <Servo.h> 
#include <math.h>
#include <string.h> 
int servoPin = 9;
#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""     
#endif   
#define BAUDRATE  1000000
#define pi  3.14159265359
#define DXL_ID    0
#define DXL_ID2   1
#define DXL_ID3   2
#define DXL_ID4   3
#define DXL_ID5   4
#define DXL_ID6   5
#define DXL_ID7   6
//[187.2,75,260,180.26,270.1,0]
uint8_t dxl_id[7]  = {DXL_ID,DXL_ID2,DXL_ID3,DXL_ID4,DXL_ID5,DXL_ID6,DXL_ID7};
const uint8_t handler_index = 0;
DynamixelWorkbench dxl_wb;
uint32_t angle(float x){
uint32_t angle2 = (uint32_t)((x/360)*4095);
return angle2;
}
float a[7] = {angle(187.2),angle(75),angle(75),angle(260),angle(180.26),angle(270.1),0}; // 초기 각도 
int32_t goal_position[7]; 
String s1;
String s2;

bool packet = false;
void serialEvent(){
  int index[5];
  if (Serial.available() > 0) {
    String temp = Serial.readStringUntil('\n');
    int len = temp.length();
    if(temp[0]=='['&&temp[len-1]==']'){
      index[0] = temp.indexOf(',');
      index[1] = temp.indexOf(',',index[0]+1);
      index[2] = temp.indexOf(',',index[1]+1);
      index[3] = temp.indexOf(',',index[2]+1);
      index[4] = temp.indexOf(',',index[3]+1);
      if(index[0]>0&&index[1]>0&&index[2]>0&&index[3]>0&&index[4]>0){
        String inString1 = temp.substring(1, index[0]);
        String inString2 = temp.substring(index[0]+1, index[1]);
        String inString3 = temp.substring(index[1]+1, index[2]);
        String inString4 = temp.substring(index[2]+1, index[3]);
        String inString5 = temp.substring(index[3]+1, index[4]);
        String inString6 = temp.substring(index[4]+1, len-1);    
        a[0] = inString1.toFloat() + 187.2;// + 187.2;
        a[1] = inString2.toFloat() +172;//+ 171.91;
        a[2] = inString2.toFloat() +172;//+ 172;
        a[3] = inString3.toFloat() +180;//+ 180 ;
        a[4] = inString4.toFloat()+180.2; //+ 180.2;
        a[5] = inString5.toFloat()+270.18; //+ 270.18;
        a[6] = inString6.toFloat(); //+ 0 ;
        packet =true;
        Serial.print("0)="); Serial.print(index[0]); Serial.print(',');Serial.print(index[1]);Serial.print(',');Serial.print(index[2]);Serial.print(',');Serial.print(index[3]);Serial.print(',');Serial.println(index[4]);
        Serial.print("1)="); Serial.print(inString1); Serial.print(',');Serial.print(inString2);Serial.print(',');Serial.print(inString3);Serial.print(',');Serial.print(inString4);Serial.print(',');Serial.print(inString5);Serial.print(',');Serial.println(inString6);
        Serial.print("2)="); Serial.print(a[0]); Serial.print(',');Serial.print(a[1]);Serial.print(',');Serial.print(a[2]);Serial.print(',');Serial.print(a[3]);Serial.print(',');Serial.print(a[4]);Serial.print(',');Serial.print(a[5]);Serial.print(',');Serial.println(a[6]);
        }
        else {Serial.println("packet1 is not succeed"); packet =false;Serial.print("10)="); Serial.print(index[0]); Serial.print(',');Serial.print(index[1]);Serial.print(',');Serial.print(index[2]);Serial.print(',');Serial.print(index[3]);Serial.print(',');Serial.println(index[4]);     }
      }
      else {Serial.println("packet2 is not succeed"); packet =false;}
      temp= "";
    }
}

void setup(){
  Serial.begin(115200);
  Serial.setTimeout(0.1);

  const char *log;
  uint16_t model_number0  = 0;
  uint16_t model_number1 = 0;
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
  for (int cnt = 0; cnt < 7; cnt++)
  {
    result = dxl_wb.ping(dxl_id[cnt], &model_number0, &log);
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
      Serial.println(model_number0);
    }
  }
  Serial.print("JointMode(0)");Serial.println(result);
  result  = dxl_wb.jointMode(dxl_id[0], 60, 0, &log);
  Serial.print("JointMode(1)");Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[1], 60, 0, &log);
  Serial.print("JointMode(2)");Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[2], 60, 0, &log);
  Serial.print("JointMode(3)");Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[3], 40, 0, &log);
  Serial.print("JointMode(4)");Serial.println(result);
  result = dxl_wb.jointMode(dxl_id[4], 40, 0, &log);
  Serial.print("JointMode(5)");Serial.println(result);
  result = dxl_wb.torque(dxl_id[5],1, &log);
  Serial.print("JointMode(6)");Serial.println(result);
  result = dxl_wb.torque(dxl_id[6],1, &log);
  Serial.print("JointMode(7)");Serial.println(result);
  dxl_wb.writeRegister(dxl_id[0], "Profile_Velocity", 200, &log);      
  dxl_wb.writeRegister(dxl_id[1], "Profile_Velocity", 80, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Velocity", 80, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Velocity", 80, &log);
  dxl_wb.writeRegister(dxl_id[4], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[5], "Profile_Velocity", 120, &log);
  dxl_wb.writeRegister(dxl_id[6], "Profile_Velocity", 120, &log);

  dxl_wb.writeRegister(dxl_id[0], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[1], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[2], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[3], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[4], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[5], "Position_I_Gain", 400, &log);
  dxl_wb.writeRegister(dxl_id[6], "Position_I_Gain", 400, &log);

  dxl_wb.writeRegister(dxl_id[0], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[1], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[2], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[3], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[4], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[5], "Position_D_Gain", 30, &log);
  dxl_wb.writeRegister(dxl_id[6], "Position_D_Gain", 30, &log);

  dxl_wb.writeRegister(dxl_id[0], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[1], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[2], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[3], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[4], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[5], "Profile_Acceleration", 20, &log);
  dxl_wb.writeRegister(dxl_id[6], "Profile_Acceleration", 20, &log);
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
    goal_position[0] = angle(187.2);// angle(0);
    goal_position[1] = angle(58);//angle(1.892950/pi*180);
    goal_position[2] = angle(58);//angle(0.515393/pi*180);
    goal_position[3] = angle(260.42);//angle(0);
    goal_position[4] = angle(180.);//angle(0.192981/pi*180);
    goal_position[5] = angle(270.09);//angle(0);
    goal_position[6] = angle(0);//angle(0);
  result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to sync write position");
  }
  delay(1000);
}

int32_t error[7] = {0,0,0,0,0,0,0};
unsigned long past = 0;
int32_t get_data[7];
int err_threshold = 15;
bool transmit = true;

void loop(){
  const char *log;
  bool result = false;  
  unsigned long now = millis();

  for(int j= 0; j<7;j++){goal_position[j] = angle(a[j]);
  goal_position[1] = goal_position[2];}
  // result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);

  if(packet){packet = false; 
  Serial.print("3)="); Serial.print(goal_position[0]); Serial.print(',');Serial.print(goal_position[1]);Serial.print(',');Serial.print(goal_position[2]);Serial.print(',');Serial.print(goal_position[3]);Serial.print(',');Serial.print(goal_position[4]);Serial.print(',');Serial.print(goal_position[5]);Serial.print(',');Serial.println(goal_position[6]);
  result = dxl_wb.syncWrite(handler_index, &goal_position[0], &log);
  }
  
  // if (result == false)
  // {
  //   Serial.println(log);
  //   Serial.println("Failed to sync write position");
  // }
  // result = dxl_wb.syncRead(handler_index, &log);
  // if (result == false)
  //   {
  //     Serial.println(log);
      // Serial.println("Failed to sync read position");
    
  // result = dxl_wb.getSyncReadData(handler_index, &get_data[0], &log);
  // if (result == false)
  //   {
  //     Serial.println(log);
  //   }
  //   else
  //   {
  //     Serial.print("[ID ");Serial.print(dxl_id[0]);Serial.print(" ]");Serial.print(" Goal Position : ");Serial.print(goal_position[0]);      Serial.print(" Present Position : ");      Serial.print(get_data[0]);      Serial.print(" [ID ");      Serial.print(dxl_id[1]);      Serial.print(" ]");      Serial.print(" Goal Position : ");      Serial.print(goal_position[1]);      Serial.print(" Present Position : ");      Serial.println(get_data[1]);
  //   }
    // for(int i = 0; i<7;i++){
    //   error[i] = abs(goal_position[i]-get_data[i]);
    //   // if(i<3){s2 = s2 + error[i]+ ",";}
    // }
    // if(error[0]<err_threshold && error[1]<err_threshold && error[2]<err_threshold && error[3]<err_threshold){transmit = true;}
    // else transmit = false;
    // Serial.println(transmit);
    // Serial.print("error");  Serial.print(error[0]);Serial.print(",");Serial.print(error[1]);Serial.print(",");Serial.print(error[2]);Serial.print(",");Serial.println(error[3]);

    // if(error[0]<err_threshold&&error[1]<err_threshold&&error[2]<err_threshold&&error[3]<err_threshold)Serial.println("transmit");
    // else Serial.println("no");
    // s2 ="";
    // Serial.println(now - past);
    past = now;
   }