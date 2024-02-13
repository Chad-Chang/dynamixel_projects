#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyUSB0" //Dynamixel on Serial3(USART3)  <-OpenCR

#define BAUDRATE  1000000
#define DXL_ID    12
#define DXL_ID2    13

DynamixelWorkbench dxl_wb;

void setup()
{
  Serial.begin(57600);
  // while(!Serial); // Open a Serial Monitor
  // dxl_wb.scan(&scanned_id[0], &dxl_cnt, range); // scan 매서드를 써서 감지되면 dxl_cnt의 값을 1 추가시켜줌., scanned_id값도 바꿔줌. range는 id range를 뜻함.
  
  dxl_wb.begin(DXL_BUS_SERIAL4, BAUDRATE);
  dxl_wb.ping(DXL_ID);
  // dxl_wb.begin(DXL_BUS_SERIAL4, BAUDRATE);
  // dxl_wb.ping(DXL_ID2);
  dxl_wb.jointMode(DXL_ID);
  // dxl_wb.jointMode(DXL_ID2);
}

void loop()
{
  dxl_wb.goalPosition(DXL_ID, 0);
  // dxl_wb.goalPosition(DXL_ID2, 0);

  delay(2000);

  dxl_wb.goalPosition(DXL_ID, 1000);
  // dxl_wb.goalPosition(DXL_ID2, 1000);

  delay(2000);
}