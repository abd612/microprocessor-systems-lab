void SystemInit() {
}

int add(int a, int b) {
	return (a + b);
}

int main() {
	int val1 = 10;
	int val2 = 15;
	int temp;
	
	int c = 0;
	c = add(val1, val2);
	
	temp = val1;
	val1 = val2;
	val2 = temp;

	return 0;
}