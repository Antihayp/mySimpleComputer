#include "PrintAll.h"

static int bcint0 [2] = {1717992960, 8283750};
static int bcint1 [2] = {471341056, 3938328};
static int bcint2 [2] = {538983424, 3935292};
static int bcint3 [2] = {2120252928, 8282238};
static int bcint4 [2] = {2120640000, 6316158};
static int bcint5 [2] = {2114092544, 8273984};
static int bcint6 [2] = {33701376, 4071998};
static int bcint7 [2] = {811630080, 396312};
static int bcint8 [2] = {2120646144, 8283750};
static int bcint9 [2] = {2087074816, 3956832};
static int bcintA [2] = {2118269952, 4342338};
static int bcintB [2] = {1044528640, 4080194};
static int bcintC [2] = {37895168, 3949058};
static int bcintD [2] = {1111637504, 4080194};
static int bcintE [2] = {2114092544, 8258050};
static int bcintF [2] = {33717760, 131646};
static int bcintp [2] = {2115508224, 1579134};
static int bcintm [2] = {2113929216, 126};

int pa_ProgRun()
{
	enum keys key;

	pa_initComp();
	pa_printAllBox();

	pa_printAccumulator();
	pa_printInstructionCounter();
	
	pa_resetTerm();

	while (key != key_q) {
		rk_readkey(&key);

		switch (key)
		{
			case key_l:
				pa_keyLoad();
				break;
			case key_s:
				pa_keySave();
				break;
			case key_r:
				pa_keyRun();
				break;
			case key_tt:
				pa_keyStep();
				break;
			case key_i:
				pa_keyReset();
				break;
			case key_f5:
				pa_keyF5();
				break;
			case key_f6:
				pa_keyF6();
				break;
			case key_up:
				pa_moveUp();
				break;
			case key_down:
				pa_moveDown();
				break;
			case key_right:
				pa_moveRight();
				break;
			case key_left:
				pa_moveLeft();
				break;
			default:
				pa_keyNumber(key);
				break;
		}
	}

	return 0;
}

//////////////////////////////
int pa_resetTerm()
{
	pa_printMemory();
	pa_resetBGColor();
	pa_printOperation();
	pa_printFlags();
	pa_printCase();

	mt_gotoXY(24, 1);
	printf("Input\\Output: ");
	mt_gotoXY(24, 14);

	mt_gotoXY(25, 1);
	for (int i = 0; i < 8; i++) {
		for (int i = 0; i < 83; i++) {
			printf(" ");
		}
		printf("\n");
	}

	mt_gotoXY(33, 1);
	fflush(stdout);
	return 0;
}

int pa_initComp()
{
	sc_memoryInit();
	sc_regInit();
	accumulator = 0;
	coord = 0;
	coord = 0;
	return 0;
}

int pa_printAllBox()
{
	mt_setscreensize(83, 47);

	mt_clrscr();

	pa_printBoxMemory();
	pa_printBoxAccumulator();
	pa_printBoxInstructionCounter();
	pa_printBoxOperation();
	pa_printBoxFlags();
	pa_printBoxCase();
	pa_printKeys();
	return 0;
}

//////////////////////////////
void pa_getXY(int *x, int *y)
{
	*x = coord % 10;
	*y = coord / 10;
}

//////////////////////////////
void pa_keyLoad()
{
	char file[35] = { 0 };

	mt_gotoXY(25, 1);
	printf("Input name file for load: ");
	fflush(stdout);
	scanf("%s", file);
	
	if (read_file(file))
		return;
	
	int i = 0;
	while (file[i] != '.') i++;

	file[i + 1] = 'o';
	file[i + 2] = '\0';

	sc_memorySave(file);
	sc_memoryLoad(file);
	pa_resetTerm();
}

void pa_keySave()
{
	char file[35] = { 0 };
	
	mt_gotoXY(25, 1);
	printf("Input name file for save: ");
	scanf("%s", file);

	sc_memorySave(file);
	pa_resetTerm();
}

void pa_keyRun()
{
	sc_regSet(T, 1);

	coord = 0;

	while (!CU()) {
		coord = instructionCounter;
		pa_printAccumulator();
		pa_printInstructionCounter();
		
		pa_resetTerm();

		sleep(1);
	}

	pa_resetTerm();
}

void pa_keyStep()
{
	int x, y;

	sc_regSet(T, 1);

	pa_getXY(&x, &y);

	CU();
	coord = instructionCounter;
	pa_printAccumulator();
	pa_printInstructionCounter();

	pa_resetTerm();
}

void pa_keyReset()
{
	pa_initComp();
	pa_resetTerm();
}

void pa_keyF5()
{
	sc_memoryGet(coord, &accumulator);
	pa_printAccumulator();
	mt_gotoXY(33, 1);
	fflush(stdout);
}

void pa_keyF6()
{
	instructionCounter = coord;
	pa_printInstructionCounter();
	mt_gotoXY(33, 1);
	fflush(stdout);
}

void pa_keyNumber(enum keys key)
{
	int x, y;
	pa_getXY(&x, &y);
				
	if (key >= 0 && key <= 9) {
		int value;
		sc_memoryGet(y * 10 + x, &value);
		if (sc_memorySet(y * 10 + x, key + value) == 1)
			sc_regSet(P, 1);
		
		coord = y * 10 + x;
		pa_resetTerm();
	}
}

//////////////////////////////
void pa_moveUp()
{
	int x, y;
	pa_getXY(&x, &y);

	if (y != 0) {
		pa_setBGColor(0);
		y--;
		pa_setBGColor(1);
	}
	
	coord = y * 10 + x;
	pa_resetTerm();
}

void pa_moveDown()
{
	int x, y;
	pa_getXY(&x, &y);
				
	if (y != 9) {
		pa_setBGColor(0);
		y++;
		pa_setBGColor(1);
	}
	
	coord = y * 10 + x;
	pa_resetTerm();
}

void pa_moveRight()
{
	int x, y;
	pa_getXY(&x, &y);

	pa_setBGColor(0);
	if (x != 9) {
		x++;
	} else if (x == 9 && y != 9) {
		x = 0;
		y++;
	}
	pa_setBGColor(1);
	
	coord = y * 10 + x;
	pa_resetTerm();
}

void pa_moveLeft()
{
	int x, y;
	pa_getXY(&x, &y);

	pa_setBGColor(0);
	if (x != 0) {
		x--;
	} else if (x == 0 && y != 0) {
		x = 9;
		y--;
	}
	pa_setBGColor(1);
	
	coord = y * 10 + x;
	pa_resetTerm();
}

//////////////////////////////
int pa_resetBGColor()
{
	pa_setBGColor(0);
	pa_setBGColor(1);
	fflush(stdout);

	return 0;
}

int pa_setBGColor(int ind)
{
	int x, y;
	pa_getXY(&x, &y);
	if (ind == 1) {
		mt_ssetbgcolor(cyan);
		mt_gotoXY(y + 2, (6 + 6 * x) - 4);
		
		if (memory[coord] < 0) {
			printf("-%.4X", -memory[coord]);
		} else {
			printf("+%.4X", memory[coord]);
		}
		
		mt_stopcolor();
	} else if (ind == 0) {
		mt_stopcolor();
		mt_gotoXY(y + 2, (6 + 6 * x) - 4);
		
		if (memory[coord] < 0) {
			printf("-%.4X", -memory[coord]);
		} else {
			printf("+%.4X", memory[coord]);
		}
	} else {
		return 1;
	}
	return 0;
}

int pa_printMemory()
{
	for (int i = 0; i < 10; i++) {
		mt_gotoXY(2 + i, 2);
		for (int j = 0; j < 10; j++) {
			if (j != 0)
				printf(" ");
			if (memory[i * 10 + j] < 0) {
				printf("-%.4X", -memory[i * 10 + j]);
			} else {
				printf("+%.4X", memory[i * 10 + j]);
			}
		}
	}
	return 0;
}

int pa_printAccumulator()
{
	mt_gotoXY(2, 70);
	if (accumulator < 0) {
		printf("-%.4X", -accumulator);
	} else {
		printf("+%.4X", accumulator);
	}
	return 0;
}

int pa_printInstructionCounter()
{
	mt_gotoXY(5, 70);
	printf("+%.4X", coord);
	return 0;
}

int pa_printOperation()
{
	int value;
	int command;
	int operand;
	int x, y;

	pa_getXY(&x, &y);

	sc_memoryGet(y * 10 + x, &value);

	mt_gotoXY(8, 69);

	if (sc_commandDecode(value, &command, &operand)) {
		printf("+00 : 00");
		return 1;
	}

	printf("+%.2X : %.2X", command, operand);
	return 0;
}

int pa_printFlags()
{
	int reg_p, reg_o, reg_m, reg_t, reg_e;

	sc_regGet(P, &reg_p);
	sc_regGet(O, &reg_o);
	sc_regGet(M, &reg_m);
	sc_regGet(T, &reg_t);
	sc_regGet(E, &reg_e);

	mt_gotoXY(11, 64);
	printf("P-%d O-%d M-%d T-%d E-%d", reg_p, reg_o, reg_m, reg_t, reg_e);

	return 0;
}

int pa_printCase()
{
	int value;
	int rank[4];
	int x, y;
	
	pa_getXY(&x, &y);
	
	sc_memoryGet(y * 10 + x, &value);

	if (value < 0) {
		bc_printbigchar(bcintm, BOX_ROW_MEMORY + 2, 2, purple, cyan);
		value *= -1;
	} else {
		bc_printbigchar(bcintp, BOX_ROW_MEMORY + 2, 2, purple, cyan);
	}

	for (int i = 0; i < 4; ++i) {
		rank[i] = value % 16;
		value /= 16;
	}

	for (int i = 38, j = 0; i >= 11; i -= 9, j++)
		pa_printCaseBigChar(rank[j], i);

	return 0;
}

int pa_printCaseBigChar(int value, int coord_y)
{
	switch (value) {
		case 0:
			bc_printbigchar(bcint0, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 1:
			bc_printbigchar(bcint1, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;		
		case 2:
			bc_printbigchar(bcint2, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 3:
			bc_printbigchar(bcint3, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 4:
			bc_printbigchar(bcint4, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 5:
			bc_printbigchar(bcint5, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 6:
			bc_printbigchar(bcint6, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 7:
			bc_printbigchar(bcint7, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 8:
			bc_printbigchar(bcint8, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 9:
			bc_printbigchar(bcint9, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 10:
			bc_printbigchar(bcintA, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 11:
			bc_printbigchar(bcintB, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 12:
			bc_printbigchar(bcintC, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 13:
			bc_printbigchar(bcintD, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 14:
			bc_printbigchar(bcintE, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
		case 15:
			bc_printbigchar(bcintF, BOX_ROW_MEMORY + 2, coord_y, purple, cyan);
			break;
	}
	return 0;
}

//////////////////////////////
int pa_printBoxMemory()
{
	bc_box(1, 1, BOX_ROW_MEMORY, BOX_COLUMN_MEMORY);
	mt_gotoXY(1, 28);
	printf(" Memory ");
	return 0;
}

int pa_printBoxAccumulator()
{
	bc_box(1, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(1, 67);
	printf(" accumulator ");
	return 0;
}

int pa_printBoxInstructionCounter()
{
	bc_box(4, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(4, 63);
	printf(" instructionCounter ");
	return 0;
}

int pa_printBoxOperation()
{
	bc_box(7, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(7, 68);
	printf(" Operation ");
	return 0;
}

int pa_printBoxFlags()
{
	bc_box(10, BOX_COLUMN_MEMORY + 1, MINI_BOX_ROW, MINI_BOX_COLUMN);
	mt_gotoXY(10, 69);
	printf(" Flags ");
	return 0;
}

int pa_printBoxCase()
{
	int column = 46;
	int row = 10;
	bc_box(BOX_ROW_MEMORY + 1, 1, row, column);
	return 0;
}

int pa_printKeys()
{
	int column = 37;
	int row = 10;

	bc_box(13, 47, row, column);
	mt_gotoXY(13, 48);
	printf(" Keys: ");
	mt_gotoXY(14, 48);
	printf("l   - load");
	mt_gotoXY(15, 48);
	printf("s   - save");
	mt_gotoXY(16, 48);
	printf("r   - run");
	mt_gotoXY(17, 48);
	printf("t   - step");
	mt_gotoXY(18, 48);
	printf("i   - reset");
	mt_gotoXY(19, 48);
	printf("F5  - accumulator");
	mt_gotoXY(20, 48);
	printf("F6  - instructionCounter");
	mt_gotoXY(21, 48);
	printf("q   - exit");
	return 0;
}
