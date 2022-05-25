
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


int main (int argc, char *argv[]) {
	FILE *fptr;
	fptr = fopen("res.bin","w");
	char *data;
	time_t t;
	long theSize = pow(10,6) * 100; // its must be pow(10,9) * 4 for fill 10^9 int_32  into file but i haven't nerves to wait so long
	long memSize = pow(10,6);

	srand((unsigned) time(&t));
	// srand(time(NULL));
	data = (char *) malloc(memSize);

	for (long uh1 = 0 ; uh1 < theSize; uh1++) {
		if (uh1 > 0 && uh1 % memSize == 0) {
			fwrite(data, theSize, 1, fptr); 
			printf("Write %d from %d chunk \n", uh1/memSize, theSize/memSize);
		}
		*(data + uh1 % memSize) = (char)(rand()%255);

	}
	fwrite(data, theSize, 1, fptr); 
	printf("Write %d from %d chunk \n", theSize/memSize, theSize/memSize);
	fclose(fptr);
	free(data);
	printf ("I'ts done \n");
	return 0;
} 


// 69 000 000
