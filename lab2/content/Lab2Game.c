#include <sys/alt_stdio.h>
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"


int slideLeft(int input){

	if(input &(1<<9)){
		return (0b0000000001);
	} else {
		return input << 1;
	}
}

int intToDisplay(int n){
	 if (n == 0){
			return 0b1000000;
	}if (n == 1){
			return 0b1111001;
	}if (n == 2){
			return 0b0100100;
	}if (n == 3){
			return 0b0110000;
	}if (n == 4){
			return 0b0011001;
	}if (n == 5){
			return 0b0010010;
	}if (n == 6){
			return 0b0000010;
	}if (n == 7){
			return 0b1111000;
	}if (n == 8){
			return 0b0000000;
	}if (n == 9){
			return 0b0011000;
	}if (n == 10){
			return 0b0001000;
	}if (n == 11){
			return 0b0000011;
	}if (n == 12){
			return 0b1000110;
	}if (n == 13){
			return 0b0100001;
	}if (n == 14){
			return 0b0000110;
	}if (n == 15){
			return 0b0001110;
	}
	return 0b1000000;
}


int main(){
	//Variables used
	int switch_datain;
	int led_display  = (0b0000000001);
	int value = (0b0000100000);
	int show = (0b0000100000);
	int rand = (0b0000100000);
	int speed = 500000;
	int count = 0;
	int hex_show;
	int no_show = 0b1111111;

	//Instructions
	alt_putstr("Hello from Nios II!\n");
	alt_putstr("When you press Push Button 0, you move aim to the left\n");
	alt_putstr("When you press Push Button 1, you shoot\n");
	alt_putstr("If your shot is succesfull, you move to the next, harder level");
	alt_putstr("Press both buttons to restart\n");



	//Set non-used LEDs to 0
	IOWR_ALTERA_AVALON_PIO_DATA(HEX1_BASE,no_show);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX2_BASE,no_show);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX3_BASE,no_show);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX4_BASE,no_show);
	IOWR_ALTERA_AVALON_PIO_DATA(HEX5_BASE,no_show);


	while (1)
	{
		rand = slideLeft(rand);
		switch_datain = ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
		switch_datain &= (0b0000000011);

		if (switch_datain != 0b0000000000){
			for (int c = 1; c <= (speed); c++){
						}
			if ((switch_datain == 0b0000000010)){
					alt_putstr("check\n");
					if (value == show){
						alt_putstr("true\n");
						value = rand;
						speed = speed - 75000;
						count += 1;
					}
			}if (switch_datain == 0b0000000001){
				led_display = slideLeft(led_display);
				alt_putstr("left\n");
			}if (switch_datain == 0b0000000011){
				alt_putstr("reset\n");
				speed = 500000;
				value = (0b0000100000);
				count = 0;
				led_display = 0b0000000001;
			}
		}

		hex_show = intToDisplay(count);
		show = value | led_display;

		IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,show);
		IOWR_ALTERA_AVALON_PIO_DATA(HEX0_BASE,hex_show);

	}
	return 0;
}
