#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
DigitalIn pin_up(D3);
DigitalIn pin_down(D6);
DigitalIn pin_sel(D5);
AnalogOut sig(PA_4);
AnalogIn sig_fil(A0);

int main()
{
    int frequency = 50;
    float T = 1000 / frequency;
    int j= 1;
    float i = 0.0f;
    float ADCdata[500];
    char store = 0;
    int l = 0;
   

    uLCD.printf("\nPlease Select the Frequency\n");
    uLCD.color(RED);
    uLCD.locate(0, 6);
    uLCD.printf("%5d Hz", frequency);

    while (1) {
        if (pin_up == 1) {
            frequency += 2;
            uLCD.locate(0, 6);
            uLCD.printf("%5d Hz", frequency);
        }
        if (pin_down == 1) {
            frequency -= 2;
            uLCD.locate(0, 6);
            uLCD.printf("%5d Hz", frequency);
        }
        if (pin_sel == 1) {
            uLCD.locate(0, 6);
            uLCD.printf("\nconfirm your frequency is %5d Hz", frequency);
            T = 1000.0 / frequency;
            store = 1;

        }
        if (i <= 20) sig = i / 20.0f / 1.1f;
        if (i > 20 && i <= 100) sig = (100 - i) / 80.0f / 1.1f;
        if (i > 100) i = 0.0f;
        if (T * 10 <= 13) T = 1.3;
        wait_us(T * 10 - 13);

        if (j == 500) {
            j = 0;
            l = 0;
        } else if (l % (100 * frequency / 500) == 0) { 
                ADCdata[j] = sig_fil;
                j++;       
        }
        if (store == 1 ) {          
                //printf("%d\r\n", frequency);
                for(int k = 0; k < 500; k++) {
                    printf("%lf\r\n", ADCdata[k]);
                }
                store = 0;
            
        }
        i++;
        l++;
       
    }
    
     


    
}
