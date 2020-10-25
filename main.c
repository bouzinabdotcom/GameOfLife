#include "life.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>




int strtoint(char * str) {
    int n = 0;
    for(int i=0; str[i]!='\0'; i++){
        if(!isdigit(str[i])){
            puts("Syntax Error!");
            exit(EXIT_FAILURE);
        }
        n += str[i] - 48;
        if(str[i+1]!='\0') n*=10;
    }

    return n;
}

void paramters_man(int argc, char* argv[], int *plain_size, int *x, int *y, int *time, int *file) {
    if(argc < 2 || argc > 11 || argc%2 == 0) {
        puts("Syntax Error!");
        exit(EXIT_FAILURE);
    }

    for(int i=1; i<argc; i+=2) {
        if(strcmp(argv[i], "-s") == 0) {
            if(strcmp(argv[i+1], "b") == 0){
                *plain_size = BIG_PLAIN_SIZE;
            }
            else if(strcmp(argv[i+1], "d") == 0){
                *plain_size = DOUBLE_PLAIN_SIZE;
            }
            else if(strcmp(argv[i+1], "h") == 0){
                *plain_size = HUGE_PLAIN_SIZE;
            }
            else{
                printf("-s option can\'t take %s as a value\n", argv[i+1]);
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(argv[i], "-x") == 0)
            *x = strtoint(argv[i+1]);
        else if(strcmp(argv[i], "-y") == 0)
            *y = strtoint(argv[i+1]);
        else if(strcmp(argv[i], "-t") == 0){
            if(strcmp(argv[i+1], "f") == 0)
                *time = TIME_FAST;
            else if(strcmp(argv[i+1], "fr") == 0)
                *time = TIME_FASTER;
            else if(strcmp(argv[i+1], "s") == 0)
                *time = TIME_SLOW;
            else if(strcmp(argv[i+1], "sr") == 0)
                *time = TIME_SLOWER;
            else {
                printf("-t option can\'t take \"%s\" as a value\n", argv[i+1]);
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(argv[i], "-f") == 0) {
            FILE *f = fopen(argv[i+1], "r");
            if(f==NULL){
                printf("Cannot open file \"%s\"\n", argv[i+1]);
                exit(EXIT_FAILURE);
            }

            *file = i+1;
            fclose(f);
        }
        else{
            printf("%s is not a supported option.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char* argv[]){

    int plain_size = DEFAULT_PLAIN_SIZE;
    int x=0, y=0;
    int time = TIME_DEFAULT;
    int file;


    paramters_man(argc, argv, &plain_size, &x, &y, &time, &file);
    plain p = init_plain(plain_size);

    
    load_pattern_from_file(x, y, argv[file], plain_size, p);

    loop(time, plain_size, p);




    return 0;

}
