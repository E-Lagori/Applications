#include<ELi_McM_4_00.h>
int y,i;
uint8_t x[8]= {I_B,I_D,I_F,I_H,I_J,I_L,I_N,I_P}; // Input mux selections
float val,val1,val2,val3,val4,val5,diff_voltage,V_P,sensorResis,temp,a,b,c,det,calib_temp[8];
float Voffset=2.632,Vref=5.252,r=1000,A=0.0039083,B= -0.0000005775; //Vref -> USB supply voltage value, Voffset -> USB supply Voltage/2
float R[8]={994.207,994.207,991.161,995.733,992.683,994.207,994.97,992.683}; //Resistance of Bridge for all 8 channels as given in bridge testing document
// float bias[8]={183.16,137.99,59.59,77.6,66.03,59.7,59.62,59.91}; // Resistance Calibration bias
// float factor[8]={0.8258,0.8763,0.9549,0.9368,0.9391,0.949,0.9513,0.9474}; // Resistance Calibration slope
float m[8] = {1.0673,1.0667,1.0752,1.0671,1.073,1.0602,1.0565,1.0674}; // Temperature Calibration slope
float C[8] = {-5.7137,-5.8692,-6.0613,-5.7444,-6.3924,-6.9003,-7.1829,-6.3264}; // Temperature Calibration bias

void setup() {
    Serial.begin(115200);
    pinMode(CtrlBUS_AF,OUTPUT); // Switch ON/OFF the bridge
    digitalWrite(CtrlBUS_AF, HIGH); // Switch on the bridge
    McM_ESP32D_4_00_Setmux(I_B,1);  // Initialise the MUX to I_B
}
 
void loop() {
//   if(Serial.available()>0){
//    int h = Serial.parseInt();
//    if (h == 0)
//      return;
//    Serial.print("Noted Reading at temperature,");
//    Serial.println(h);
// }
    for (y=0;y<8;y++){
        McM_ESP32D_4_00_Setmux(x[y]);
        val1=0;
        for(i=0;i<1000;i++){
         val = analogRead(McM_ESP32D_4_00_CH_ADC_DAC);
         val1+=val; 
        }
        val2 = val1/1000;
        val3 = (val2/4096)*Vref;
        val4 = ((val3-Voffset)/3)+Voffset;
        val5 = (R[y]*val4)/(Vref-val4);
        sensorResis = val5;//*factor[y] + bias[y];
        a = r*B;
        b = r*A;
        c = r-sensorResis;
        det = sqrt((b*b)-(4*a*c));
        temp = (-b+det)/(2*a);
        calib_temp[y] = ((temp/m[y]) - (C[y]/m[y]));
//       Serial.print(y+1);
//       Serial.print(',');
//       Serial.print(val4,4);
//       Serial.print(',');        
//       Serial.print(sensorResis);
//       Serial.print(',');
//       Serial.print(temp);
//       Serial.print(' ');
       Serial.println(calib_temp[y]);
//       Serial.println(' ');
    }
    Serial.println();
    // delay(1000);
//  }
}
