/* Local Includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sched.h>

#define DEFAULT_ITERATIONS 1000000
#define RTPRIORITY 1
#define RADIUS (RAND_MAX / 2)

inline double dist(double x0, double y0, double x1, double y1){
    return sqrt(pow((x1-x0),2) + pow((y1-y0),2));
}

inline double zeroDist(double x, double y){
    return dist(0, 0, x, y);
}

int main(int argc, char* argv[]){

    long i;
    long iterations;
    struct sched_param param;
    int policy;
    double x, y;
    double inCircle = 0.0;
    double inSquare = 0.0;
    double pCircle = 0.0;
    double piCalc = 0.0;

    fprintf(stdout, "argc: %d\n", argc);

    if(argc < 2){
	iterations = DEFAULT_ITERATIONS;
    }
    if(argc < 3){
	policy = SCHED_OTHER;
	param.sched_priority = 0;
    }
    if(argc > 1){
	iterations = atol(argv[1]);
	if(iterations < 1){
	    fprintf(stderr, "Bad iterations value\n");
	    exit(EXIT_FAILURE);
	}
    }
    if(argc > 2){
	if(!strcmp(argv[2], "SCHED_OTHER")){
	    policy = SCHED_OTHER;
	    param.sched_priority = 0;
	}
	else if(!strcmp(argv[2], "SCHED_FIFO")){
	    fprintf(stdout, "SCHED_FIFO\n");
	    policy = SCHED_FIFO;
	    param.sched_priority = RTPRIORITY;
	}
	else if(!strcmp(argv[2], "SCHED_RR")){
	    policy = SCHED_RR;
	    param.sched_priority = RTPRIORITY;
	}
	else{
	    fprintf(stderr, "Unhandeled scheduling policy\n");
	    exit(EXIT_FAILURE);
	}
    }

    fprintf(stdout, "Current Scheduling Policy: %d\n", sched_getscheduler(0));
    fprintf(stdout, "Setting Scheduling Policy to: %d\n", policy);
    
    if(sched_setscheduler(0, policy, &param)){
	perror("Error setting scheduler policy");
	exit(EXIT_FAILURE);
    }

    fprintf(stdout, "Current Scheduling Policy: %d\n", sched_getscheduler(0));

    for(i=0; i<iterations; i++){
	x = (random() % (RADIUS * 2)) - RADIUS;
	y = (random() % (RADIUS * 2)) - RADIUS;
	if(zeroDist(x,y) < RADIUS){
	    inCircle++;
	}
	inSquare++;
    }

    pCircle = inCircle/inSquare;
    piCalc = pCircle * 4.0;

    fprintf(stdout, "pi = %f\n", piCalc);

    return 0;
}
