#define	max2(a, b)	a > b ? a : b
#define	max3(a, b, c)	a > b ? max2(a, c) : max2(b, c)
#define max4(a, b, c, d)	a > b ? max3(a, c, d) : max3(b, c, d)
#define max5(a, b, c, d, e)	a > b ? max4(a, c, d, e) : max4(b, c, d, e)

void SystemInit() {
}

int main(void) {
	int a = 5;
	int b = 7;
	int c = 1;
	int d = 2;
	int e = 11;
	
	int max2 = 0;
	int max3 = 0;
	int max4 = 0;
	int max5 = 0;
	
	max2 = max2(a, b);
	max3 = max3(a, b, c);
	max4 = max4(a, b, c, d);
	max5 = max5(a, b, c, d, e);
	
	return 0;
}