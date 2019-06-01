/***** interface.h **********************************************************
 * Description: Simulate pair of related DNA sequences
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Sat Jun  1 13:27:39 2019
 ****************************************************************************/
#ifndef INTERFACE
#define INTERFACE

#define DEFAULT_L  100000
#define DEFAULT_K  0.01
#define DEFAULT_G  0.5
#define DEFAULT_LL 70

/* define argument container */
typedef struct args{
  char    h; /* help message?         */
  char    v; /* version message?      */
  char    d; /* print divergence val. */
  char  err; /* error                 */
  int     l; /* sequence length       */
  int     s; /* seed for random num.  */
  int     L; /* line length           */
  float   k; /* substitutions         */
  float   D; /* divergence            */
  float   g; /* GC content            */
  char **fi; /* input files           */
  int    nf; /* number of input files */
} Args;

Args *getArgs(int argc, char *argv[]);
Args *newArgs();
void freeArgs(Args *args);
void printUsage();
void printSplash(Args *args);

#endif
