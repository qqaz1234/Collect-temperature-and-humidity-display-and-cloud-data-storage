#include "reg52.h"
#include <intrins.h>
#include "delay.h"
#include "dht11.h"
#include "showtemperature.h"
uchar rec_dat[9];
void DHT11_start()
{
    Data=1;
    delay_us(2);
    Data=0;
    delay_ms(30);
    Data=1;
    delay_us(30);
}

uchar DHT11_rec_byte()
{
    uchar i,dat=0;
    for(i=0; i<8; i++)
    {
        while(!Data);
        delay_us(8);
        dat<<=1;
        if(Data==1)
            dat+=1;
        while(Data);
    }
    return dat;
}
void DHT11_receive()
{

    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise;
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);
        delay_us(40);
        R_H=DHT11_rec_byte();
        R_L=DHT11_rec_byte();
        T_H=DHT11_rec_byte();
        T_L=DHT11_rec_byte();
        revise=DHT11_rec_byte();
        delay_us(25);
        if((R_H+R_L+T_H+T_L)==revise)
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        }
        rec_dat[0]='0'+(RH/10);
        rec_dat[1]='0'+(RH%10);
        rec_dat[2]=' ';

        //�¶�
        rec_dat[4]='0'+(TH/10);
        rec_dat[5]='0'+(TH%10);
        rec_dat[6]=' ';
    }
}
void DHT11_temget(){
            DHT11_receive();
            for (i = 0; i < 7; i++)
            {
                if (i <= 2)
                {
                    shidu[i] = rec_dat[i]; //��ȡʪ��
                }
                else if (i > 3)
                {
                    wendu[i - 4] = rec_dat[i];
                }
            }
}
