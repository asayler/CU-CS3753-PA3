/*
 * File: rw.c
 * Author: Andy Sayler
 * Project: CSCI 3753 Programming Assignment 3
 * Create Date: 2012/03/19
 * Modify Date: 2012/03/19
 * Description:
 * 	
 *      
 */

/* Include Flags */
#define _GNU_SOURCE

/* Local Includes */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

    int inputD;
    int inputFlags;
    int outputD;

    /* Open Input File Descriptor in Read Only mode */
    inputFlags = O_RDONLY;
    if((inputD = open("rwinput", inputFlags)) < 0){
	perror("Failed to open input file");
	exit(EXIT_FAILURE);
    }
	
    /* Close Input File Descriptor */
    if(close(inputD)){
	perror("Failed to close input file");
	exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
