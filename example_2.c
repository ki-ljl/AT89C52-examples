#include<reg52.h>
#include <intrins.h>    

//LED
sbit D1 = P1^0;
sbit D2 = P1^1;
sbit D3 = P1^2;
sbit D4 = P1^3;
sbit D5 = P1^4;
sbit D6 = P1^5;
sbit D7 = P1^6;
sbit D8 = P1^7;

//switch
sbit K1 = P0^0;
sbit K2 = P0^1;
sbit K3 = P0^2;
sbit K4 = P0^3;

//延时
void delay(int m, int n) {
	unsigned int i, j;
	for(i = m; i > 0; i--) {
		for(j = n; j >0; j--);
	}
}

void main() {
	unsigned char led, i, j; //设置变量
  led = 0xfe; //初值为11111110
	while(1) {
		//按下K1，八个灯按照同一频率同时闪烁
		P1 = 0xff;
		if(K1 == 0) {
			while(K1 == 0) {
				P1 = 0x00;
				delay(50, 20);
				P1 = 0xff;
				delay(50, 20);
			}
		}
		P1 = 0xff;
		//按下K2，从D1到D8闪烁10次后转到下个灯
		if(K2 == 0) {
			while(K2 == 0) {
				//右移
				for(i = 0; i < 7; i++) {
					//闪烁10次
					for(j = 0; j < 10; j++) {
						delay(100, 50);
						P1 = led;
						delay(100, 50);
						P1 = 0xff;  //全灭
						delay(100, 50);
					}
					led = _crol_(led, 1);
				}
				//左移
				for(i = 0; i < 7; i++) {
					//闪烁10次
					for(j = 0; j < 10; j++) {
						delay(100, 50);
						P1 = led;
						delay(100, 50);
						P1 = 0xff;  //全灭
						delay(100, 50);
					}
					led = _cror_(led, 1);
				}
			}
			P1 = 0xff;
		}
		if(K3 == 0) {
			while(K3 == 0) {
				delay(50, 50);
				P1 = 0xf0;   //左边四个灯亮
				delay(50, 50);
				P1 = 0x0f;  //右边四个灯亮
			}
		}
		if(K4 == 0) {
			while(K4 == 0) {
				P1 = 0xff;
				//从右往左依次点亮
				delay(150, 150);
				D8 = 0;
				delay(150, 150);
				D7 = 0;
				delay(150, 150);
				D6 = 0;
				delay(150, 150);
				D5 = 0;
				delay(150, 150);
				D4 = 0;
				delay(150, 150);
				D3 = 0;
				delay(150, 150);
				D2 = 0;
				delay(150, 150);
				D1 = 0;
				delay(150, 150);
				P1 = 0xff;  //全灭
				delay(150, 150);
				//从右往左依次点亮
				D8 = 0;
				delay(150, 150);
				D7 = 0;
				delay(150, 150);
				D6 = 0;
				delay(150, 150);
				D5 = 0;
				delay(150, 150);
				D4 = 0;
				delay(150, 150);
				D3 = 0;
				delay(150, 150);
				D2 = 0;
				delay(150, 150);
				D1 = 0;
				delay(150, 150);
			}
		}
	}
}
