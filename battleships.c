#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define N_SIZE (2)
#define BUFF_SIZE (5)
#define S_BUFF_SIZE (255)

char **r_str(char *str, uint8_t size, const char *separator) {
    char **res = malloc(sizeof(char *) * size);
    char *split = strtok(str, separator);
    uint8_t inx = 0;
    while(split) {
        res[inx] = strdup(split);
        split = strtok(NULL, separator);
        ++inx;
    }
    return res;
}

int main(void) {
	char buff[BUFF_SIZE];
	char s_buff[S_BUFF_SIZE];
	char ***matrix;
	uint8_t counter[N_SIZE];
	
	FILE *fp;
	fp = fopen("input.in", "r");

	uint8_t matrix_size = atoi(fgets(buff, BUFF_SIZE, fp));

	matrix = malloc(sizeof(char **) * N_SIZE);

	for(uint8_t i=0;i<N_SIZE;++i) {
		matrix[i] = malloc(sizeof(char *) * matrix_size);
		for(uint8_t j=0;j<matrix_size;++j) {
			matrix[i][j] = malloc(sizeof(char) * matrix_size);
			memset(matrix[i][j], '_', matrix_size);
		}
	}

	uint8_t n_ship = atoi(fgets(buff, BUFF_SIZE, fp));
	for(uint8_t i = 0; i < N_SIZE; ++i) {
		char *tmp = fgets(s_buff, S_BUFF_SIZE, fp);
		char **ships = r_str(tmp, n_ship, ":");
		for(int j = 0; j < n_ship; ++j) {
			char **pos = r_str(ships[j], 2, ",");
			uint8_t x = atoi(pos[0]), y = atoi(pos[1]);
			
            for(int i = 0; i < 2; ++i)
                free(pos[i]);
            free(pos);

            matrix[i][x][y] = 'B';
            
		}

        for(int i = 0; i < 5; ++i)
            free(ships[i]);
        free(ships);
	}
	
	uint8_t n_missile = atoi(fgets(buff, BUFF_SIZE, fp));
	
	for(uint8_t i = 0; i < N_SIZE; ++i) {
		counter[i] = 0;
		char *tmp = fgets(s_buff, S_BUFF_SIZE, fp);
		char **missiles = r_str(tmp, n_missile, ":");
		for(int j = 0; j < n_missile; ++j) {
			char **pos = r_str(missiles[j], 2, ",");
			uint8_t x = atoi(pos[0]), y = atoi(pos[1]);
			
            for(int i = 0; i < 2; ++i)
                free(pos[i]);
            free(pos);

			if(matrix[N_SIZE-1-i][x][y] == 'B') {
				matrix[N_SIZE-1-i][x][y] = 'X';
				++counter[i];
			}
			else
				matrix[N_SIZE-1-i][x][y] = 'O';
		}
		for(int i = 0; i < 5; ++i)
            free(missiles[i]);
        free(missiles);
	}

	for(uint8_t i=0;i<N_SIZE;++i) {
		printf("Player%d\n",i+1);
		for(uint8_t j=0;j<matrix_size;++j) {
			for(uint8_t k=0;k<matrix_size;++k)
				printf("%c ", matrix[i][j][k]);
			printf("\n");
		}
		printf("\n");
	}
	printf("P1:%d\nP2:%d\n", counter[0], counter[1]);
	
	if(counter[0] > counter[1])
		printf("Player 1 wins\n");
	else if(counter[0] < counter[1])
		printf("Player 2 wins\n");
	else
		printf("It is a draw\n");
	
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 5; ++j)
            free(matrix[i][j]);
        free(matrix[i]);
    }
	free(matrix);
	fclose(fp);
	return 0;
}
