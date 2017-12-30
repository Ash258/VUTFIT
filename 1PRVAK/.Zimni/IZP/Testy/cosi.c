#include <stdio.h>

struct osoba{ int vek;double vaha;int vyska; };

typedef struct osoba CLOVEK;

typedef float  (*Pcena)(double, int);

typedef double (*PcenaB)(double, int);

unsigned long vypocet(unsigned long a, unsigned long b){
	if(a * b == 0) return 0;
	if(a < b){
		a ^= b;
		b ^= a;
		a ^= b;
	}
	return (a % b > 0) ? vypocet(b, a % b) : b;
}

void zobrazeni(unsigned long long cislo, unsigned short arg_bitu){
	if(arg_bitu > 2) zobrazeni(cislo >> 2, arg_bitu - 2);
	
	printf("%llu%llu ", cislo & 1, (cislo >> 1) & 1);
}

void myPrint(int n){
	printf("%d", n / 2);
	
	if(n > 0) myPrint(n - 1);
	
	printf("%d", n);
}

void myPrint2(int n){
	printf("%d", n % 2);
	
	if(n > 0) myPrint2(n - 1);
	
	printf("%d", n / 2);
}

void myPrint3(int n){
	printf("%d", n / 2);
	
	if(n > 0) myPrint3(n - 1);
	
	printf("%d", n);
}

void printAboveSideDiag(int n, int array[5][5]){
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - i - 1; j++){
			printf("%d ", array[i][j]);
			printf("\n");
		}
		return;
	}
}

int main(){
	//region Radny
	printf("********************\n\t\tRADNY\n********************\n");
	//2. priklad
	signed int z, x = 7, y = 22;
	z = x++ - y / 5; // x++ == x, ++x = 4, 22/5 = 4,4, 7-4,4 = 2,6 == 3
	printf("2A\n\tz = %i\n", z);
	
	int a[10] = {1, 2, 3, [8] = 8, 10};
	printf("2B\n\t%d\t\n", a[10]);
	for(int j = 0; j < 10; ++j){
		printf("\t\t%d", a[j]);
	}
	printf("\n");
	
	//3. priklad
	{
		CLOVEK c4 = {.vek = 30};
		CLOVEK c3 = {.vyska = 175};
		c4 = c3;
		printf("3A\n\t%d\n", c4.vek);
	}
	
	unsigned int aa = 1, b = 2, c;
	c = aa & b || aa && b;
	printf("3B\n\t%d\n", c);
	
	//4. priklad
	int     sum = 0;
	for(int i   = 0; i < 10; i++){
		switch(i){
			case 1:
			case 4:
			case 7: sum++;
			default:continue;
			case 5:break;
		}
		break;
	}
	printf("4A\n\t%d\n", sum);
	
	int     sumB = 1;
	for(int i    = 0; i < 10; i++){
		switch(i){
			case 1:
			case 4:
			case 7: sumB++;
			default:continue;
			case 5:break;
		}
		break;
	}
	printf("4B\n\t%d\n", sumB);
	
	//9. priklad
	unsigned long xx = 35;
	unsigned long yy = 10;
	printf("9A\n\t%lu\n", vypocet(xx, yy));
	
	//endregion
	
	//region Opravny
	printf("********************\n\t\tOpravny\n********************\n");
	printf("9A\n\t");
	unsigned short pom = 121;
	zobrazeni(pom, sizeof(pom) * 4);
	printf("\n9AA\n\t");
	int count = 4;
	myPrint(count);
	
	printf("\n9B\n\t");
	int cosi = 4;
	myPrint2(cosi);
	
	printf("\n9B\n\t");
	int cosi2 = 3;
	myPrint3(cosi2);
	//endregion
	
	printf("\n%d\n", 4 % 2);
}