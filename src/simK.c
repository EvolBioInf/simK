/***** simK.c ***************************************************************
 * Description: Simulate pair of related DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 13:27:39 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "interface.h"
#include "eprintf.h"
#include "gsl_rng.h"

char getNuc(float gc, gsl_rng *ran){
  char c;
  float r;
  r = gsl_rng_uniform(ran);
  if(r < gc){
    r = gsl_rng_uniform(ran);
    if(r < 0.5){
      c = 'G';
    }else{
      c = 'C';
    }
  }else{
    r = gsl_rng_uniform(ran);
    if(r < 0.5){
      c = 'A';
    }else{
      c = 'T';
    }
  }
  return c;
}

int main(int argc, char *argv[]){
  Args *args = getArgs(argc, argv);
  int n;
  char c, counter = 0;

  setprogname2(argv[0]);
  if(args->v)
    printSplash(args);
  if(args->h || args->err)
    printUsage();
  gsl_rng *ran = ini_gsl_rng(args);
  char **seq = (char **)emalloc(2*sizeof(char *));
  seq[0] = (char *)emalloc((args->l+1)*sizeof(char));
  seq[1] = (char *)emalloc((args->l+1)*sizeof(char));
  /* generate "ancestral sequence" */
  for(int i=0;i<args->l;i++){
    seq[0][i] = getNuc(args->g, ran);
    seq[1][i] = seq[0][i];
  }
  /* mutate sequence */
  n = (int)(-3.0/4.0*(1-log(4.0/3.0*args->D))*args->l+0.5);
  if(args->D < 0){
    n = (int)(args->l*args->k+0.5);
    for(int i=0;i<n;i++){
      int p = (int)(gsl_rng_uniform(ran)*args->l);
      c = seq[0][p];
      while((c = getNuc(args->g, ran)) == seq[0][p])
	;
      seq[0][p] = c;
    }
  }else{
    counter = 0;
    n = args->D * args->l + 0.5;
    while(counter < n){
      int p = (int)(gsl_rng_uniform(ran)*args->l);
      if(seq[0][p] == seq[1][p]){
	counter++;
	while((c = getNuc(args->g, ran)) == seq[0][p])
	  ;
	seq[0][p] = c;
      }
    }
  }
  /* output sequences */
  for(int i=0;i<2;i++){
    printf(">S%d\n",i+1);
    counter = 0;
    for(int j=0;j<args->l;j++){
      if(++counter < args->L)
	printf("%c",seq[i][j]);
      else{
	printf("%c\n",seq[i][j]);
	counter = 0;
      }
    }
    if(counter)
      printf("\n");
  }
  double d = 0;
  for(int i=0;i<args->l;i++)
    if(seq[0][i] != seq[1][i])
      d++;
  d /= args->l;
  double k = -3.0/4.0*log(1.0-4.0/3.0*d);
  if(args->d)
    printf("d: %f; K: %f\n",d,k);
  free(seq[0]);
  free(seq[1]);
  free(seq);
  gsl_rng_free(ran);
  return 0;
}

