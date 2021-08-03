#include <stdio.h>
#include <stdlib.h>

typedef struct INFO {
	char	name[20];
	int		age;
	float	height;
} INFO;

#define DATA_SIZE	5

int main(int argc, char * argv[]){
	FILE *fp;
	int i;
	INFO data;
	
	if((fp = fopen(argv[1], "r")) == NULL){
		perror("fopen");
		exit(1);
	}
	
	while(1) {
		fread(&data, sizeof(INFO), 1, fp);
		if(feof(fp)){
			break;
		}
		printf("name:%s, age:%d, height:%.1f\n", data.name, data.age, data.height);
	}
	
	fclose(fp);
	return 0;
					
}
