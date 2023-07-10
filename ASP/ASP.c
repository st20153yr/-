# include <stdlib.h>
# include <stdio.h>
# include "Activity.h"

extern unsigned num;
extern ACT activity[];

int main() {
	sortActivity(activity, num);

	unsigned time = 0;
	int i;
	
	while (1) {
		for(i=0; i<num; i++) {
			if(activity[i].start >= time) break;
		}
		if ( time < 16 ) {
			time = activity[i].finish;
			printf("%s\n", activity[i].name);
		}
		else {
			break;
		}
	}
	return 0;
}

void sortActivity(ACT act[], unsigned n) {
	ACT tmp;
	for(int i=0; i<n-1; i++) {
		for(int j=n-1; j>i; j--) {
			if(activity[j].finish < activity[j-1].finish) {
                tmp = activity[j];
                activity[j] = activity[j-1];
                activity[j-1] = tmp;
            }
		}
	}
}
