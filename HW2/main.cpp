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
    char choose = 1;
    char run = 1;
    int frequency = 360;
    float T = 1000 / frequency;
    int j= 1;
    float i = 0.0f;
    float ADCdata[100];
    char store = 0;

    uLCD.printf("\nPlease Select the Frequency\n");
    uLCD.color(RED);
    uLCD.locate(0, 6);
    uLCD.printf("%5d Hz", frequency);

    while (1) {
        if (pin_up == 1) {
            frequency += 20;
            uLCD.locate(0, 6);
            uLCD.printf("%5d Hz", frequency);
        }
        if (pin_down == 1) {
            frequency -= 20;
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
        if (i > 20) sig = (100 - i) / 80.0f / 1.1f;
        if (i > 100) i = 0.0f;
        wait_us(T * 10 - 13);


        if (store == 1 ) {
            ADCdata[j - 1] = sig_fil;
            if (j == 100) {
                printf("%d\r\n", frequency);
                for(int k = 0; k < 100; k++) {
                    printf("%lf\r\n", ADCdata[k]);
                }
                j = 1;
                store = 0;
            }
            else j++;
        }
        i++;
    }
    
     


    
}
