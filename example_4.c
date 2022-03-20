#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
uchar t = 0, cnt = 1, n;
sbit wave = P2^7;
bit flag;
uchar code DSY_CODE[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //0-9
uchar code LED_CODE[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00}; //依次点亮

void init_time0() {
	P1 = LED_CODE[cnt - 1];
	P0 = DSY_CODE[cnt];
	TMOD = 0x01; //设置T0为定时器模式，工作方式在1
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

void init_time1() {
	TMOD = 0x11;
	EA = 1;
	ET1 = 1;
	TR1 = 1;
	wave = 1;  //高电平
	flag = 1;
}

void time0() interrupt 1 {   //定时器0中断服务程序
	TH0=(65536-50000) / 256;
  TL0=(65536-50000) % 256;
	if(++t == 20) {  //1s
		t = 0;
		cnt++;
		P1 = LED_CODE[cnt - 1];
		P0 = DSY_CODE[cnt];
		if(cnt == 9) {
			P1 = 0xff;
			cnt = 0;
		}
	}
}

void timer1() interrupt 3 {
	TH1=(65536-40000) / 256;  //40ms高电平
  TL1=(65536-40000) % 256;
	if(flag) {
		wave = ~wave;   //变为低电平
		flag = 0;
	}
	n++;
	if(n == 10) {   //400ms时候，此时低电平已经持续360ms，翻转
		n = 0;
		wave = ~wave;
		flag = 1;
	}
}

void main() {
	init_time0();
	init_time1();
	while(1);
}