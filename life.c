#include "life.h"
#include<stdlib.h>
#include<stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


plain init_plain(int plain_size) {
    //allocate memory for the plain and innitialize it to an empty one
    plain p = (plain)malloc(plain_size*sizeof(int*));
    for(int i=0; i<plain_size; i++) {
        *(p+i) = (int*)malloc(plain_size*sizeof(int));
        for(int j=0; j<plain_size; j++)
            p[i][j] = 0; 
    }

    return p;
}



void clear_p(int plain_size, plain p){
    //basic garbage collector
    for(int i=0; i<plain_size; i++) {
        free(*(p+i));
    }
    free(p);
}


void load_pattern(int x, int y, int pattern_size, pattern ptrn, int plain_size, plain p) {
    /**
     * Loads a pattern into a plain at a specified position (x, y).
     * */

    //if the pattern can't be placed at that position due to overflow 
    //stop and print error message
    if( x + pattern_size > plain_size || y + pattern_size > plain_size ){
        puts("Unable to load pattern at those coordinates.");
        exit(EXIT_FAILURE);
    }

    //go to the specified position in the plain
    //and copy the values from the pattern
    for(int i=0; i<plain_size;i++){ 
        for(int j=0; j<plain_size; j++) {
            if(i==y && j==x) {
                for(int k=0; k<pattern_size; k++)
                    for(int l=0; l<pattern_size; l++)
                        p[i+k][j+l] = ptrn[k][l];
                return;
            }
        }
    }
}

void load_pattern_from_file(int x, int y, char* filename, int plain_size, plain p){
    //reads from file and creates an equivalent pattern then calls load_pattern

    //open file
    FILE * f = fopen(filename, "r");
    if(f==NULL) {
        printf("Error: Unable to read file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }
    
    //read first line: pattern size
    int pattern_size;
    fscanf(f, "%d", &pattern_size);


    //initialize new plain used as a pattern (same underlying structure)
    pattern pttr = (pattern)init_plain(pattern_size);
    
    char tmp; //holds temporary value to be tested against bad input

    int j;
    for(int i=0; i<pattern_size; i++)
        for(j=0; j<pattern_size; j++){
            
            fscanf(f, "%c", &tmp);
            if(feof(f)) break; //checks if file had ended
            if(tmp != '\n' || tmp == '0' || tmp == '1'){
                pttr[i][j] = tmp-48;

            }
            else j--;
        }

    //if file ends before reading all values needed (pattern_size*pattern_size)
    //error
    if(j!=pattern_size) {
        printf("%s has an invalid format\n", filename);
        exit(EXIT_FAILURE);
    }


    fclose(f); //close file
    load_pattern(x, y, pattern_size, pttr, plain_size, p); 
    //free up memory taken by the pattern.
    clear_p(pattern_size, (plain)pttr);

}

int nb_neighbors(int x, int y, int plain_size, plain p){
    int counter = 0;
    for(int i = -1; i<2 && y+i<plain_size; i++){
            if(i+x<0) continue;
        for(int j = -1; j<2 && x+j<plain_size; j++){
            if(i+y<0 || j+x<0) continue;
            if(i==0 && j==0) continue;

            counter += p[i+y][j+x]==ALIVE || p[i+y][j+x]==DYING ? 1 : 0; 
        }
    }

    return counter;
}

int isLife(int x, int y, int plain_size, plain p){

    return p[y][x]==ALIVE && (nb_neighbors(x, y, plain_size, p) == 2 || nb_neighbors(x, y, plain_size, p) == 3);
}

int isDeath(int x, int y, int plain_size, plain p) {
    return p[y][x]==ALIVE && (nb_neighbors(x, y, plain_size, p) > 3 || nb_neighbors(x, y, plain_size, p) < 2);
}

int isBirth(int x, int y, int plain_size, plain p){
    return p[y][x]== DEAD && nb_neighbors(x, y, plain_size, p) == 3;
}

int get_fate(int x, int y, int plain_size, plain p){
    
    
    if(isDeath(x, y, plain_size, p))
        return DEAD;
    return -1;
}

void next_generation(int plain_size, plain p){
    
     for(int i=0; i<plain_size; i++){
        for(int j=0; j<plain_size; j++){
            if(isBirth(j, i, plain_size, p))
                p[i][j] = BORN;
            if(isDeath(j, i, plain_size, p))
                p[i][j] = DYING;
        }
     }
    

    for(int i=0; i<plain_size; i++){
        for(int j=0; j<plain_size; j++){
            if(p[i][j] == BORN)
                p[i][j] = ALIVE;

            if(p[i][j] == DYING)
                p[i][j] = DEAD;
        }
     }
     

    
}

void print_plain(int plain_size, plain p) {
    system("clear");
    for(int i=0; i<plain_size; i++){
        for(int j=0; j<plain_size; j++){
            printf("%s", (p[i][j]==1?"# ":"_ " ));
        }
        printf("\n");
    }
}

void loop(int time, int plain_size, plain p){
    while(1){
        print_plain(plain_size, p);
        next_generation(plain_size, p);

        usleep(time);
    }
}