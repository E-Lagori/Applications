//#include <TEC.h>
#include <ELi_MdM_4_00.h>
#include <ELi_McM_4_00.h>

struct MD3_6_4_00_Pinconfig p1 = {.IN1 = CtrlBUS_AE,.IN2 = CtrlBUS_AF,.VREF = 0};
MD3_6_4_00_DD test1(p1,100,0,MCPWM_UNIT_0,MCPWM_TIMER_0,100);

float set_speed;

void setup() {
  Serial.begin(115200);
  test1.startmotor();
  test1.setspeed_lin(0);
}

void loop() {
  if(Serial.available()>0){
    set_speed = Serial.parseFloat();
    Serial.println(set_speed);
    test1.setspeed_lin(-1*set_speed);
  }
}
