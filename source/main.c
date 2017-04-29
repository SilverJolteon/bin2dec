#include <3ds.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	// Initialize services
	gfxInitDefault();

	//Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
	consoleInit(GFX_BOTTOM, NULL);


	int kDownOld = 0, kHeldOld = 0, kUpOld = 0, version = 4, x, p = 7, dec = 0, width = 19, height = 4, max = 16, bit = 8, bin[max], comp = 0;
	char pnt[] = "^", spc[] = " ", sign[6] = "[]    ";
	printf("----------------------------------------\n");
	printf("    Binary to Decimal Converter v0.%d\n            by SilverJolteon\n", version);
	printf("----------------------------------------\n");
	printf(" %cUnsigned%c%cSigned (1's)%c%cSigned (2's)%c\n\n", sign[0], sign[1], sign[2], sign[3], sign[4], sign[5]);
	printf("\n");
	printf("\n      Bits:  0     Decimal Value: 0\n\n");
	//Prints out spaces according to width value set
	for(x = 0; x < (width); x++){
		printf(" ");
	}
	//Prints out 0's according to bit length
	for(x = 0; x < bit; x++){
		printf("0");
	}
	//Sets each bit in the binary number to 0
	for(x = 0; x < max; x++){
		bin[x] = 0;
	}
	printf("\n");
	//Prints out spaces according to width plus p values set
	for(x = 0; x < (width + p); x++){
		printf(" ");
	}
	printf("^");
	//Prints out new line breaks
	for(x = 0; x < height; x++){
		printf("\n");
	}
	printf("            Press X To Reset");
	//Main Loop
	while (aptMainLoop())
	{
		//Scans each input
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		//hidKeysHeld returns information about which buttons have are held down in this frame
		u32 kHeld = hidKeysHeld();
		//hidKeysUp returns information about which buttons have been just released
		u32 kUp = hidKeysUp();

		if(kDown & KEY_START) break; // Break in order to return to hbmenu

		//Runs scripts when certain keys are pressed
		if(kDown != kDownOld || kHeld != kHeldOld || kUp != kUpOld)
		{
			//Clears console
			consoleClear();

			//These lines must be rewritten because we cleared the whole console
			printf("----------------------------------------\n");
			printf("    Binary to Decimal Converter v0.%d\n            by SilverJolteon\n", version);
			printf("----------------------------------------\n");
			printf(" %cUnsigned%c%cSigned (1's)%c%cSigned (2's)%c\n\n", sign[0], sign[1], sign[2], sign[3], sign[4], sign[5]);
			printf("\n");
			//If bit is greater than 9, displays Bit and Decimal values
			if(bit > 9){
				printf("\n      Bits: %d     Decimal Value: %d", bit, dec);
			}
			else{
				printf("\n      Bits:  %d     Decimal Value: %d", bit, dec);
			}
			//If decimal value has more than 4 digits, prints only one line break
			if(dec < -9999){
				printf("\n");
			}
			else{
				printf("\n\n");
			}
			//Prints out spaces according to width value set
			for(x = 0; x < (width); x++){
				printf(" ");
			}
			//Prints out 0's according to bit length
			for(x = 0; x < bit; x++){
				printf("%d", bin[x]);
			}
			printf("\n");
			//Prints out spaces according to width value set
			for(x = 0; x < (width); x++){
				printf(" ");
			}
			//If value p is greater than 0, prints p-amount of spaces
			if(p > 0){
				for(x = 0; x < p; x++){
					printf("%s", spc);
				}
			}
			printf("%s", pnt);
			//Prints out new line breaks
			for(x = 0; x < height; x++){
				printf("\n");
			}
			printf("            Press X To Reset");
			
			dec = 0;
			
			//If Up on the D-Pad is pressed, and if binary number at index p is 0, increases to 1
			if(kDown & KEY_DUP && bin[p] == 0){
				bin[p]++;
			}
			//If Down on the D-Pad is pressed, and if binary number at index p is 1, decreases to 0
			else if(kDown & KEY_DDOWN && bin[p] == 1){
				bin[p]--;
			}
			//If Right on the D-Pad is pressed, and if value p is less than amount of bits minus 1, increases p
			if(kDown & KEY_DRIGHT && p < (bit-1)){
				p++;
			}
			//If Left on the D-Pad is pressed, and if value p is greater than 0, decreases p
			else if(kDown & KEY_DLEFT && p > 0){
				p--;
			}
			//If R button is pressed, and if bit length is greater than 1, decreases p value, increases width value, and shifts numbers to the left
			if(kDown & KEY_R && bit > 1){
				if(p > 0){
					p--;
				}
				width++;
				for(x = 0; x < bit; x++){
					if(x > 0){
						bin[x - 1] = bin[x];
						bin[x] = 0;
					}
				}
				bit--;
			}
			//If L button is pressed, and if bit length is less than max value, increases p value, decreases width value, and shifts numbers to the right
			else if(kDown & KEY_L && bit < max){
				bit++;
				width--;
				p++;
				for(x = bit - 1; x > 0; x--){
					if(x > 0){
						bin[x] = bin[x - 1];
						bin [x - 1] = 0;
					}
				}
			}
			//If X button is pressed, resets each value to what is initially set
			if(kDown & KEY_X){
				bit = 8;
				p = 7;
				width = 19;
				for(x = 0; x < max; x++){
					bin[x] = 0;
				}
				comp = 0;
			}
			//Converts binary number to decimal
			for(x = 0; x < bit; x++){
				dec = dec + (bin[x]) * ((int)pow(2, bit - 1 - x));
			}
			//If Y button is pressed, converts decimal number to 2's compliment
			if(kDown & KEY_Y){
				if(comp < 2){
					comp++;
				}
				else if(comp == 2){
					comp -= 2;
				}
			}
			//If comp is 0, highlights "Unsigned"
			if(comp == 0){
				strcpy(sign, "[]    ");
			}
			//If comp is 1, changes value to 1's compliment and highlights it
			else if(comp == 1){
				strcpy(sign, "  []  ");
				if(bin[0] == 1){
					dec = dec + 1 - (int)pow(2, bit - 1) * 2;
				}
			}
			//If comp is 2, changes value to 2's compliment and highlights it
			else if(comp == 2){
				strcpy(sign, "    []");
				if(bin[0] == 1){
					dec = dec - (int)pow(2, bit - 1) * 2;
				}
			}
		}

		//Set keys old values for the next frame
		kDownOld = kDown;
		kHeldOld = kHeld;
		kUpOld = kUp;

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}