#include "korong.h"

korong* korong_lefoglal(int n) {  // korong strukt�r�t c�mz� mutat�
	korong* tomb = 0; // ez lesz a korongokat tarolo tomb kezdocime
	if (n == 2) {
		tomb = new korong[5]; // lefoglal egy korong t�pus� t�mb�t, 5 elemmel
	}
	else if (n == 3) {
		tomb = new korong[7];
	}
	else if (n == 4) {
		tomb = new korong[9];
	}
	return tomb;
};
