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

/* Local Defines */
#define INPUTBLOCKSIZE 1024*1024

int main(int argc, char* argv[]){

    (void) argc;
    (void) argv;

    int inputFD;
    int outputFD;
    char inputBuffer[INPUTBLOCKSIZE];
    ssize_t bytesRead = 0;
    ssize_t totalBytesRead = 0;
    int totalReads = 0;
    ssize_t bytesWritten = 0;
    ssize_t totalBytesWritten = 0;
    int totalWrites = 0;
    
    /* Open Input File Descriptor in Read Only mode */
    if((inputFD = open("rwinput", O_RDONLY | O_SYNC)) < 0){
	perror("Failed to open input file");
	exit(EXIT_FAILURE);
    }

    /* Open Output File Descriptor in Write  Only mode */
    if((outputFD =
	open("rwoutput",
	     O_WRONLY | O_CREAT | O_TRUNC | O_SYNC,
	     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0){
	perror("Failed to open output file");
	exit(EXIT_FAILURE);
    }

    /* Read Input File and write to output*/
    do{
	bytesRead = read(inputFD, inputBuffer, INPUTBLOCKSIZE);
	if(bytesRead < 0){
	    perror("Error reading input file");
	    exit(EXIT_FAILURE);
	}
	else{
	    totalBytesRead += bytesRead;
	    totalReads++;
	}

	bytesWritten = write(outputFD, inputBuffer, bytesRead);
	if(bytesWritten < 0){
	    perror("Error writing output file");
	    exit(EXIT_FAILURE);
	}
	else{
	    totalBytesWritten += bytesWritten;
	    totalWrites++;
	}
    }while(bytesRead > 0);

    fprintf(stdout, "Read:    %zd bytes in %d reads\n",
	    totalBytesRead, totalReads);
    fprintf(stdout, "Written: %zd bytes in %d writes\n",
	    totalBytesWritten, totalWrites);
	
    /* Close Output File Descriptor */
    if(close(outputFD)){
	perror("Failed to close output file");
	exit(EXIT_FAILURE);
    }

    /* Close Input File Descriptor */
    if(close(inputFD)){
	perror("Failed to close input file");
	exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
