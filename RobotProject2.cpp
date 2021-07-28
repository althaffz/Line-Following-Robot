unsigned int Left_Sensor;
unsigned int Right_Sensor;

float Right_B;
float Right_W;

float Left_B;
float Left_W;

unsigned short Left_PWM;
unsigned short Right_PWM;

void main() {
     //Initialize Timer0 for 100Hz Interrupt
     OPTION_REG = 0b10000101 ;
     TMR0       = 0b01100011;
     //Enable Interrupts
     INTCON = 0b11100000;

     TRISA = 0b00000011;
     TRISC = 0;

     PORTC = 0;

     PWM1_Init(5000);                                 // Initialize PWM1 module at 5KHz
     PWM2_Init(5000);                   // Initialize PWM2 module at 5KHz

     PWM1_Start();                       // start PWM1
     PWM2_Start();                   // start PWM2

     //PWM1_Set_Duty(0);        // Set current duty for PWM1
     //PWM2_Set_Duty(0);       // Set current duty for PWM2


while(1){





//void interrupt()
//{
          Left_Sensor  = ADC_Read(1);
          Right_Sensor  = ADC_Read(0);

          /////////////// Right Sensor Values //////////////

          if(Right_Sensor < 500){

                        Right_B=0;
                        Right_W=1;

          }else if(Right_Sensor > 500){

                        Right_B=1;
                        Right_W=0;

          }


          /////////////// Left Sensor Values //////////////

          if(Left_Sensor < 500){

               Left_B = 0;
               Left_W = 1;

          }else if(Left_Sensor > 500){

               Left_W = 0;
               Left_B = 1;

          }

          //////////////////////////////Map Final Output to PWM////////////////////////////////////////



          if((Left_W == 0 ) && ( Right_W ==0 )){

               Left_PWM = 255;
               Right_PWM = 255;

          } else if((Left_W == 1) && (Right_W ==0)){

               Left_PWM = 180;
               Right_PWM = 50;

          } else if((Left_W == 0) && (Right_W ==1)){

               Left_PWM = 50;
               Right_PWM = 180;

               } else if((Left_W == 1) && (Right_W ==1)){

               Left_PWM = 0;
               Right_PWM = 155;

          }

            PWM1_Set_Duty(Right_PWM);        // Set current duty for PWM1
                 // System.out.println(Right_PWM);   // Set current duty for PWM1
                  //System.out.println(Left_PWM);
          PWM2_Set_Duty(Left_PWM);       // Set current duty for PWM2



         //TMR0 = 0b01100011;
          //INTCON.TMR0IF = 0;
         Delay_ms(100);

}
}