#define DEFAULT_PLAIN_SIZE 25
#define BIG_PLAIN_SIZE 50
#define DOUBLE_PLAIN_SIZE 100
#define HUGE_PLAIN_SIZE 200


#define MILLISECOND 1000
#define TIME_FAST 50*MILLISECOND
#define TIME_FASTER MILLISECOND
#define TIME_DEFAULT 150*MILLISECOND
#define TIME_SLOW 600*MILLISECOND
#define TIME_SLOWER 1000*MILLISECOND

#define ALIVE 1 
#define BORN 2
#define DEAD 0
#define DYING -1


typedef int **plain, **pattern; 

plain init_plain(int);
void clear_p(int, plain);

void load_pattern(int, int, int, pattern, int, plain);
void load_pattern_from_file(int, int, char*, int, plain);
int nb_neighbors(int, int, int, plain);
int isLife(int, int, int, plain);
int isDeath(int, int, int, plain);
int isBirth(int, int, int, plain);
int get_fate(int, int, int, plain);
void next_generation(int, plain);
void print_plain(int, plain);
void loop(int, int, plain);