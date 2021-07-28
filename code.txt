unsigned int Left_Sensor;
unsigned int Right_Sensor;
unsigned int Temp;

float Right_B;
float Right_G;
float Right_W;

float Left_B;
float Left_G;
float Left_W;

float Output        = 0;
float Output_Devide = 0;

float Output_Final  = 0;

unsigned short Left_PWM;
unsigned short Right_PWM;


void main() {

     //Initialize Timer0 for 100Hz Interrupt
     OPTION_REG = 0b10000101 ;
     TMR0       = 0b01100011;

     //Enable Interrupts
     INTCON = 0b11100000;

     TRISA = 0b00000011;
     TRISB = 0;
     TRISC = 0;
     TRISD = 0;

     PORTB = 0;
     PORTC = 0;

     //Left_Sensor_Max    = 1023;
     //Right_Sensor_Max   = 1023;

     PWM1_Init(4000);                                 // Initialize PWM1 module at 5KHz
     PWM2_Init(4000);                   // Initialize PWM2 module at 5KHz

     PWM1_Start();                       // start PWM1
     PWM2_Start();	           // start PWM2

     //PWM1_Set_Duty(0);        // Set current duty for PWM1
     //PWM2_Set_Duty(0);       // Set current duty for PWM2

     PORTD = 0b00001010;


     while(1)
{
}


}




void interrupt()
{


          Left_Sensor  = ADC_Read(1);

          Right_Sensor  = ADC_Read(0);


          /////////////// Right Sensor Values //////////////

          if(Right_Sensor < 116){

               Right_B = 1;
               Right_G = 0;
               Right_W = 0;

          }else if(Right_Sensor < 552){

               Right_G = (Right_Sensor - 116)/436;

               Right_B = 1-Right_G;

               Right_W = 0;

          }else if(Right_Sensor < 988){

               Right_W = (Right_Sensor - 552)/436;

               Right_G = 1-Right_W;

               Right_B = 0;

          }else{

               Right_B = 0;
               Right_G = 0;
               Right_W = 1;

          }


          /////////////// Left Sensor Values //////////////

          if(Left_Sensor < 116){

               Left_B = 1;
               Left_G = 0;
               Left_W = 0;

          }else if(Left_Sensor < 552){

               Left_G = (Left_Sensor - 116)/436;

               Left_B = 1-Left_G;

               Left_W = 0;

          }else if(Left_Sensor < 988){

               Left_W = (Left_Sensor - 552)/436;

               Left_G = 1-Left_W;

               Left_B = 0;

          }else{

               Left_B = 0;
               Left_G = 0;
               Left_W = 1;

          }

          Output = 0;
          Output_Devide = 0;






          ///////////////////////Fire 9 Rules///////////////////////////////

          if(Left_B < Right_B){

               Output_Devide = Left_B;
               Output = Left_B*0;

          }else{

               Output_Devide =  Right_B;
               Output = Left_B*0;

          }
          /////////////////////////////////////////////
          if(Left_B < Right_G){

               Output_Devide =  Output_Devide + Left_B;
               Output =  Output + Left_B*(-10);

          }else{

               Output_Devide =  Output_Devide + Right_G;
               Output =  Output + Right_G*(-10);

          }
          /////////////////////////////////////////////
          if(Left_B < Right_W){

               Output_Devide =  Output_Devide + Left_B;
               Output =  Output + Left_B*(-20);

          }else{

               Output_Devide =  Output_Devide + Right_W;
               Output =  Output + Right_W*(-20);

          }
          /////////////////////////////////////////////
          if(Left_G < Right_B){

               Output_Devide =  Output_Devide + Left_G;
               Output =  Output + Left_G*(10);

          }else{

               Output_Devide =  Output_Devide + Right_B;
               Output =  Output + Right_B*(10);

          }
          /////////////////////////////////////////////
          if(Left_G < Right_W){

               Output_Devide =  Output_Devide + Left_G;
               Output =  Output + Left_G*(-20);

          }else{

               Output_Devide =  Output_Devide + Right_W;
               Output =  Output + Right_W*(-20);

          }
          /////////////////////////////////////////////
          if(Left_W < Right_B){

               Output_Devide =  Output_Devide + Left_W;
               Output =  Output + Left_W*(20);

          }else{

               Output_Devide =  Output_Devide + Right_B;
               Output =  Output + Right_B*(20);

          }
          /////////////////////////////////////////////
          if(Left_W < Right_G){

               Output_Devide =  Output_Devide + Left_W;
               Output =  Output + Left_W*(20);

          }else{

               Output_Devide =  Output_Devide + Right_G;
               Output =  Output + Right_G*(20);

          }
          /////////////////////////////////////////////
          if(Left_W < Right_W){

               Output_Devide =  Output_Devide + Left_W;
               Output =  Output + Left_W*(0);

          }else{

               Output_Devide =  Output_Devide + Right_W;
               Output =  Output + Right_W*(0);

          }

          //////////////////////////////Map Final Output to PWM////////////////////////////////////////

          Output_Final =  Output/Output_Devide;

          if(Output_Final < 0){

               Left_PWM = (Output_Final*(-1) + 20)*6;
               Right_PWM = 250 - Left_PWM;

          } else {

               Right_PWM = (Output_Final + 20)*6;
               Left_PWM = 250 - Right_PWM;

          }

          PWM1_Set_Duty(Right_PWM);        // Set current duty for PWM1
          PWM2_Set_Duty(Left_PWM);       // Set current duty for PWM2



          TMR0 = 0b01100011;
          INTCON.TMR0IF = 0;

     }