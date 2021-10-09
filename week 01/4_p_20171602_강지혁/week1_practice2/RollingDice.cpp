#include "pch.h"
#include "tipsware.h"
#include "time.h"
#define _USE_MATH_DEFINES
#include "math.h"

NOT_USE_MESSAGE

#define MAX_TRY 100

int main()
{
	SelectPenObject(RGB(0, 0, 0));

	float hit = 0;
	float miss = 0;
	float relProb = 5.0 / 36.0;
	float prob = 0;
	
	// TODO 

	int leftDice, rightDice;

	for (int i = 0; i < MAX_TRY; i++) {
		leftDice = rand() % 6 + 1;
		rightDice = rand() % 6 + 1;

		if (leftDice + rightDice == 8) {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d (hit!)", 0 + i, leftDice, rightDice);
			hit += 1;
		}
		else {
			TextOut(120 * (i / 20), 20 * (i % 20), "try %d: %d,%d", 0 + i, leftDice, rightDice);
			miss += 1;
		}
	}

	prob = float(hit / (hit + miss));
	
	//

	SetTextColor(RGB(128, 0, 0));
	// 실제 주사위 값
	TextOut(0, 420, "실제 값: %.6f", relProb);
	// 계산된 값
	TextOut(0, 440, "계산된 값: %.6f", prob);

	ShowDisplay();

	return 0;
}
