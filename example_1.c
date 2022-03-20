#include<reg52.h>

sbit light = P1^0;

// delay 0.2s
void delay(void) {
	unsigned int i, j, k;
	for(i = 20; i > 0; i--) {
		for(j = 20; j >0; j--) {
			for(k = 248; k > 0; k--);
		}
	}
}

void main() {
	while(1) {
		light = 0;
		delay();
		light = 1;
		delay();
	}
}