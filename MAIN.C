#include "dos.h"
#include "stdio.h"
#include "stdlib.h"

unsigned short int code; // random number for random ASCII char
unsigned char ch; // random ASCII char
int ticks = 0; // counts ticks

void interrupt (*old_vect) (void); // define old_vect to contain taken IV in program

void interrupt new_vect(void) {
	// define new_vect to write custom IV in IVT
	// it replaces 0x1c (timer) IV and counts ticks
	// each 9th tick is approx. 0.5 seconds => print random ASCII char
	if (ticks % 9 == 0) {
		code = random(255);
		ch = code;
		printf("%c (%d)\n", ch, code);
	}
	++ticks;
}

int main() {
	clrscr();

	randomize();

	old_vect = _dos_getvect(0x1c); // get defalut IV to remember it

	_dos_setvect(0x1c, new_vect); // replace to custom IV in IVT and run it

	printf("Print random ASCII char each 0.5 seconds.\nPress any key to exit...\n");
	getch(); // wait 

	_dos_setvect(0x1c, old_vect); // after ending get default timer IV back in IVT

	return 0;
}