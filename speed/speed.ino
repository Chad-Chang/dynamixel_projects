#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyUSB0" //Dynamixel on Serial3(USART3)  <-OpenCR

#define BAUDRATE  1000000
#define DXL_ID    11

DynamixelWorkbench dxl_wb;

void setup()
{int result;
  Serial.begin(57600);
  while(!Serial) Serial.println("Serial x"); // Open a Serial Monitor
  // const char *log;
  dxl_wb.begin(DXL_BUS_SERIAL4, BAUDRATE);
  dxl_wb.ping(DXL_ID);

  result = dxl_wb.wheelMode(DXL_ID);
  Serial.print("result : "); Serial.println(result);
}

void loop()
{Serial.println("loop on");
  dxl_wb.goalVelocity(DXL_ID, 200);
  Serial.println("this is 200");
  delay(3000);

  dxl_wb.goalVelocity(DXL_ID, -150);
  Serial.println("this is 150");
  delay(3000);
}