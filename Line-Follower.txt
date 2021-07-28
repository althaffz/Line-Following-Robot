void right() ;
int count=0 ,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,thr=500;//thr=thrasold;
 unsigned short high=255, low=255;


void right(){
   PWM1_Set_Duty(high);//right PWM EN
  // PORTC.RC2=1; //RIGHT EN
    PORTC.RC5=1; //RIGHT FORWARD
    PORTC.RC6=0; //RIGHT REVERCE
    PWM2_Set_Duty(low);
    PORTC.RC4=1; //LEFT FORWARD
    PORTC.RC3=0;  //LEFT REVERCE
   // PORTC.RC1=0; //LEFT EN
    PORTC.RC0=1;   //LED
    Delay_ms(10);
}

void left(){
   PWM1_Set_Duty(low);//right PWM EN
   //PORTC.RC2=1; //RIGHT EN
    PORTC.RC5=1; //RIGHT FORWARD
    PORTC.RC6=0; //RIGHT REVERCE
    PWM2_Set_Duty(High);
    PORTC.RC4=1; //LEFT FORWARD
    PORTC.RC3=0;  //LEFT REVERCE
    //PORTC.RC1=1; //LEFT EN
    PORTC.RC0=1;   //LED
    Delay_ms(10);
}
void forward(){
    PORTC.RC2=1; //RIGHT EN
    PORTC.RC5=1; //RIGHT FORWARD
    PORTC.RC6=0; //RIGHT REVERCE

    PORTC.RC4=1; //LEFT FORWARD
    PORTC.RC3=0;  //LEFT REVERCE
    PORTC.RC1=1; //LEFT EN
    PORTC.RC0=1;   //LED
    Delay_ms(100);
    //PORTC=0X00;
   // Delay_ms(10);

}
void stop(){
    if(count<1){
    PORTC=0X00;
    PORTC.RC2=1; //RIGHT EN
    PORTC.RC5=0; //RIGHT FORWARD
    PORTC.RC6=1; //RIGHT REVERCE

    PORTC.RC4=0; //LEFT FORWARD
    PORTC.RC3=1;  //LEFT REVERCE
    PORTC.RC1=1; //LEFT EN
    PORTC.RC0=1;   //LED
    Delay_ms(50);
    PORTC=0X00;
    Delay_ms(50);
    }
    count++;
    //use count=0; after calling this function.
}

  void main() {
  PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
  PWM2_Init(5000);                    // Initialize PWM2 module at 5KHz
  PWM1_Start();                       // start PWM1
  PWM2_Start();                       // start PWM2
  PWM1_Set_Duty(0);        // Set current duty for PWM1
  PWM2_Set_Duty(0);       // Set current duty for PWM2
   TRISB=0;
   TRISC=0;
   TRISD=0;
   //TRISA=1;
    PORTC=0X00;
   while(1){
   temp1 = ADC_Read(0);
   temp2 = ADC_Read(1);
   temp3 = ADC_Read(2);
   temp4 = ADC_Read(3);
   temp5 = ADC_Read(4);
        PORTC.RC0=1;   //LED
        delay_ms(10);
         PORTC.RC0=0;   //LED
      if(temp1<thr && temp2<thr && temp3>thr && temp4<thr && temp5<thr){       //00100
      PORTB=0B00100000 ;
     //forward();
    }else if(temp1<thr && temp2>thr && temp3<thr && temp4<thr && temp5<thr){   //01000      value<<<< when white ||  1023 >---blak
      //left();
        PORTB=0B01000000 ;
    }else if(temp1<thr && temp2<thr && temp3<thr && temp4>thr && temp5<thr){   //00010
    //  right();
        PORTB=0B00010000 ;
    }else if(temp1>thr && temp2<thr && temp3<thr && temp4<thr && temp5<thr){   //10000
     //  left();
      PORTB=0B10000000 ;
    }else if(temp1<thr && temp2<thr && temp3<thr && temp4<thr && temp5>thr){   //00001
      // right();
         PORTB=0B00001000 ;
    }else if(temp1<thr && temp2>thr && temp3>thr && temp4<thr && temp5<thr){   //01100
     PORTB=0B01100000 ;
      // left();
    }else if(temp1<thr && temp2<thr && temp3>thr && temp4>thr && temp5<thr){   //00110
      //right();
         PORTB=0B00110000 ;
    }else if(temp1>thr && temp2>thr && temp3<thr && temp4<thr && temp5<thr){   //11000
    //left();
     PORTB=0B11000000 ;
    }else if(temp1<thr && temp2<thr && temp3<thr && temp4>thr && temp5>thr){   //00011
    //right();
     PORTB=0B00011000 ;
    }else{
     PORTB=0B1010100 ;
   // stop();
   // right();
   // delay_ms(1000);
    //stop();
  //  forward();
  //  delay_ms(1000);
    //stop();
  //  left();
  //  delay_ms(1000);
    //stop();

   //forward();
    }


}   
}