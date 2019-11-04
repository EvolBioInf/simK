/***** interface.c **********************************************************
 * Description: Simulate pair of related DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 13:27:39 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "interface.h"
#include "eprintf.h"

Args *newArgs() {
  Args *args = (Args *)emalloc(sizeof(Args));
  args->h   = 0;
  args->v   = 0;
  args->err = 0;
  args->d   = 0;
  args->l   = DEFAULT_L;
  args->k   = DEFAULT_K;
  args->D   = -1.0;
  args->g   = DEFAULT_G;
  args->s   = 0;
  args->L   = DEFAULT_LL;
  return args;
}

void freeArgs(Args *args) {
  free(args);
}

Args *getArgs(int argc, char *argv[]) {
  int c;
  char *optString = "hvdl:k:D:g:s:L:";
  Args *args = newArgs();

  while ((c = getopt(argc, argv, optString)) != -1) {
    switch(c) {
    case 'l': /* iterations */
      args->l = atoi(optarg);
      break;
    case 'k': /* substitutions */
      args->k = atof(optarg);
      break;
    case 'D': /* divergence */
      args->D = atof(optarg);
      break;
    case 'g': /* GC content */
      args->g = atof(optarg);
      break;
    case 's': /* random number seed */
      args->s = atoi(optarg);
      break;
    case 'L': /* line length */
      args->L = atoi(optarg);
      break;
    case 'h': /* help       */
      args->h = 1;
      break;
    case 'v': /* version    */
      args->v = 1;
      break;
    case '?':
      args->err = 1;
      if(optopt == 'i')
	fprintf(stderr, "Error: Option `%c` requires an argument.\n", optopt);
      else if(isprint(optopt))
	fprintf(stderr, "Error: Unknown option `%c`.\n", optopt);
      else
	fprintf(stderr, "Error: Unknown option character `\\x%x`.\n", optopt);
    default:
      args->err = 1;
      return args;
    }
  }
  args->fi = argv + optind;
  args->nf = argc - optind;

  return args;
}

void printUsage() {
  printf("Usage: %s [options] [inputFiles]\n", progname());
  printf("Simulate a pair of related DNA sequences\n");
  printf("Example: %s\n", progname()); 
  printf("Options:\n");
  printf("\t[-l <INTEGER> generate sequences of length INTEGER; default: %d]\n", DEFAULT_L);
  printf("\t[-k <FLOAT> introduce FLOAT substitutions / site; default: %.2f]\n", DEFAULT_K);
  printf("\t[-D <FLOAT> create divergence of FLOAT (replaces -k)]\n");
  printf("\t[-g <FLOAT> sequences have FLOAT gc content; default: %.2f]\n", DEFAULT_G);
  printf("\t[-s <INTEGER> use INTEGER as seed for random number; default: system]\n");
  printf("\t[-L <INTEGER> print lines of length INTEGER; default: %d]\n", DEFAULT_LL);
  printf("\t[-d print divergence values; default: sequence only]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print version & program information and exit]\n");
  exit(0);
}

void printSplash(Args *args) {
  printf("%s ", progname());
  int l = strlen(VERSION);
  for(int i = 0; i < l - 1; i++)
    printf("%c", VERSION[i]);
  printf(", %s\n", DATE);
  printf("Author: Bernhard Haubold\n");
  printf("License: GNU General Public License, https://www.gnu.org/licenses/gpl.html\n");
  printf("Bugs: haubold@evolbio.mpg.de\n");
  exit(0);
}
