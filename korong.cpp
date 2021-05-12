#include "korong.h"

korong* korong_lefoglal(int n) {  // korong struktúrát címzõ mutató
	korong* tomb = 0; // ez lesz a korongokat tarolo tomb kezdocime
	if (n == 2) {
		tomb = new korong[5]; // lefoglal egy korong típusú tömböt, 5 elemmel
	}
	else if (n == 3) {
		tomb = new korong[7];
	}
	else if (n == 4) {
		tomb = new korong[9];
	}
	return tomb;
};
