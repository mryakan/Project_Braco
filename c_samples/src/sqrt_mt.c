//============================================================================
// Name        : sqrt_mt.c
// Author      : Medhat R. Yakan
// Version     : 1.0
//
// ****************************************************************************
// Copyright   : Copyright (c) 2017 "Medhat R. Yakan" - All Rights Reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
// ****************************************************************************
//
// Description : Multiuthreaded square root computation (non recursive)
//
//============================================================================

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define TUSEC_PER_SEC   1000000L

/*
 * Print Command help
 */
static bool
print_help(const char *cmd) {
    const char *arg_help =  "[-h] [-T <num_threads>] <Number>\n"
                            "    num_thread=1..8 (default=1)";
    const char *usage_ex = "-T 2 100";
    printf("  %s: %s\n", cmd, arg_help);
    printf("Example:\n  %s %s\n", cmd, usage_ex);
    return true;
}


/*
 * Parse the command line arguments
 * Returns: 0 if parse correctly
 *          N > 0 if too many arguments provided
 *          -1 if too few arguments specified or other parsing error occurs
 */
static int
parse_args(int argc, char **argv,
           unsigned int *num_threads, unsigned int *sqrtN, bool *help) {
    int nthreads=0, fnum=0;
    unsigned int rem_args = argc-1, i;

    if (help) {
        *help = false;
    }
    i = 1;
    /* parse each argument */
    while (rem_args) {
        rem_args--;
        if ((strcmp(argv[i], "-h") == 0) && help) {
            /* No need to continue if '-h' is specified */
            *help = true;
            return 0;
        } else if (strcmp(argv[i], "-T") == 0) {
            if (rem_args == 0) {
                return -1;
            }
            i++;
            rem_args--;
            nthreads = atoi(argv[i]);
        } else if (rem_args == 0) {
            /* last arg is sqrtN */
            fnum = atoi(argv[i]);
        } else {
            /* unrecognized arg */
            break;
        }
        i++;
    }
    /* verify argument values & assign is appropriate */
    if (nthreads < 0) {
        return -1;
    }
    if (num_threads) {
        *num_threads = (unsigned int)nthreads;
    }
    if (fnum < 0) {
        return -1;
    }
    if (sqrtN) {
        *sqrtN = (unsigned int)fnum;
    }
    return (int)rem_args;
}


/*
 * Calculate the square root sequence for values 'startN' to 'endN' and
 * return results in 'sqrt_seq'
 * (Single threaded)
 * Return: > 0 if success
 *         <= 0 if failed
 */
static int
calculate_sqrt(const unsigned int startN, const unsigned int endN,
              double *sqrt_seq) {
    unsigned int i, num;
    for (i=0, num=startN; num<=endN; i++, num++) {
        sqrt_seq[i] = sqrt((double)num);
    }
    return 1;
}

/*
 * Calculate the square root sequence for 'sqrtN' using 'num_threads' threads
 * and return results in 'sqrt_seq'
 * Return: > 0 if success
 *         <= 0 if failed
 */
static int
calculate_sqrt_mt(const unsigned int num_threads, const unsigned int sqrtN,
                  double *sqrt_seq) {
    if (sqrt_seq == NULL) {
        return 0;
    }
    if (num_threads == 1) {
        return calculate_sqrt(0, sqrtN, sqrt_seq);
    }
    return -1; // not implemented yet
}

/*
 * Print the square root sequence
 */
static bool
print_sqrt(const unsigned int sqrtN, const double *sqrt_seq) {
    unsigned int i;
    if (sqrt_seq == NULL && sqrtN) {
        return false;;
    }
    for (i=0; i < sqrtN; i++) {
        if (i && (i%8 == 0)) {
            printf("\n");
        }
        printf("%f ", sqrt_seq[i]);
    }
    printf("\n");
    return true;
}

/*
 * Print Elapsed time between 'startTval' and 'endTval'
 */
static bool
print_elapsed_time(const char *msg, const struct timeval startTval,
                   const struct timeval endTval) {
    long int elapsedTime = ((endTval.tv_sec - startTval.tv_sec)* TUSEC_PER_SEC +
                             endTval.tv_usec - startTval.tv_usec);
    struct timeval elapsedTval;
    elapsedTval.tv_sec = elapsedTime / TUSEC_PER_SEC;
    elapsedTval.tv_usec = elapsedTime % TUSEC_PER_SEC;
    printf("%s%ld seconds & %ld microseconds\n", (msg ? msg : ""),
           elapsedTval.tv_sec, elapsedTval.tv_usec);
    return true;
}

int
main(int argc, char **argv) {
    unsigned int num_threads = 0, sqrtN = 0;
    double *sqrt_seq = NULL;
    int ret=0;
    bool help = false;
    struct timeval startTval, endTval;
    if ((ret = parse_args(argc, argv, &num_threads, &sqrtN, &help)) !=0) {
        printf("ERROR: Invalid usage/argument (%d)!\n", ret);
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    if (help) {
        printf("HELP:\n");
        print_help(argv[0]);
        exit(EXIT_SUCCESS);
    }
    sqrt_seq = calloc(sqrtN, sizeof(double));
    if (sqrt_seq == NULL) {
        printf("ERROR: Failed to allocate memory! Aborting.\n");
        exit(EXIT_FAILURE);
    }
    printf("Computing square root sequence for N=%u...\n", sqrtN);
    gettimeofday(&startTval, NULL);
    ret = calculate_sqrt_mt(num_threads, sqrtN, sqrt_seq);
    gettimeofday(&endTval, NULL);
    if (ret <= 0) {
        printf("ERROR: Failed to compute square root sequence for N=%u (%d)!\n",
               sqrtN, ret);
        if (sqrt_seq) {
            free(sqrt_seq);
        }
        exit(EXIT_FAILURE);
    }
    //(void)print_sqrt(sqrtN, sqrt_seq);
    (void)print_elapsed_time("Computation time: ", startTval, endTval);
    if (sqrt_seq) {
        free(sqrt_seq);
    }
    exit(EXIT_SUCCESS);
}
