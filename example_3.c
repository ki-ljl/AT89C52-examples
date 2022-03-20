#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int

uchar code DSY_CODE[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; 

//延时函数
void delay(uint m, uint n) {
	uint i, j;
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++);
	}
}

void open_interrupt() {
	EA = 1;   //CPU开中断
	EX0 = 1;  //允许外部中断0产生中断
	IT0 = 1;  //外中断0为边沿触发方式
	EX1 = 1;  //允许外部中断1产生中断
	IT1 = 1;  //外中断1为边沿触发方式
	PX1 = 1;  //外中断1为高级中断
}

//外部中断0
void inter0() interrupt 0 {
	uint i = 0;
	for(i = 0; i < 10; i++) {
		P2 = DSY_CODE[i];
		delay(880, 110);
	}
}

//外部中断1
void inter1() interrupt 2 {
	uint i = 0;
	for(i = 0; i < 10; i++) {
		P1 = DSY_CODE[i];
		delay(880, 110);
	}
}

void main() {
	uint i = 0;
	open_interrupt();  //开中断
	while(1) {
		P0 = DSY_CODE[i];
		i = (i + 1) % 10;
		delay(880, 110);
	}
}