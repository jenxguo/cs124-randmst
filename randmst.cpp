#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string>

typedef struct
{
    int v;
    int u;
    float weight;
}
edge;

int main(int argc, char *argv[]){
    //checks that there are command line args
    if (argc != 5)
    {
        printf("Usage: ./randmst 0 numpoints numtrials dimension\n");
        return 1;
    }

    int flag = (int) strtol(argv[1], NULL, 10);
    int numpoints = (int) strtol(argv[2], NULL, 10);
    int numtrials = (int) strtol(argv[3], NULL, 10);
    int dimension = (int) strtol(argv[4], NULL, 10);

    printf("%i, %i, %i \n", numpoints, numtrials, dimension);

    return 0;
}