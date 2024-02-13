#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "3" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID    11


DynamixelWorkbench dxl_wb;

void setup() 
{
  Serial.begin(57600);
  // while(!Serial); // Wait for Opening Serial Monitor

  const char *log;
  bool result = false;

  uint8_t dxl_id = DXL_ID;
  uint16_t model_number = 0;

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

  result = dxl_wb.ping(dxl_id, &model_number, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.jointMode(dxl_id, 0, 0, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to change joint mode");
  }
  else
  {
    Serial.println("Succeed to change joint mode");
    Serial.println("Dynamixel is moving...");

  dxl_wb.goalPosition(dxl_id, (int32_t)0);
    for (int count = 0; count < 180; count++)
    {// {
      dxl_wb.goalPosition(dxl_id, (float)radians(count*3));
      delay(10);
      Serial.println(count);
    }
    for(int count = 180; count>-1; count--)
    {// {
      dxl_wb.goalPosition(dxl_id, (float)radians(count*3));
      delay(10);
      Serial.println(count);
    }
  }
}

void loop() 
{

}