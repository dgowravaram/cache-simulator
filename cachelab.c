Last login: Mon Jun 29 05:32:33 on ttys000
(base) Divyas-MacBook-Pro:~ divyagowravaram$ ssh divyag@csa2.bu.edu
divyag@csa2.bu.edu's password: 
Permission denied, please try again.
divyag@csa2.bu.edu's password: 
       Last failed login: Mon Jun 29 12:46:38 EDT 2020 from c-73-194-112-252.hsd1.nj.comcast.net on ssh:notty
There was 1 failed login attempt since the last successful login.
       Last login: Mon Jun 29 05:32:55 2020 from c-73-194-112-252.hsd1.nj.comcast.net
---------------------------------------------------------
       For all support issues related to this machine,
        please send e-mail to support@cs.bu.edu.
---------------------------------------------------------
    Temporary local storage is a





  // cachelab.c - Cache Lab helper functions

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cachelab.h"
#include <time.h>


trans_func_t func_list[MAX_TRANS_FUNCS];
int func_counter = 0;

/*                                                                                                                                
 * printSummary - Summarize the cache simulation statistics.
 */

void printSummary(int hits, int misses, int evictions)
{
  printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
  FILE* output_fp = fopen(".csim_results", "w");
  assert(output_fp);
  fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
  fclose(output_fp);
}


/*                                                                                                                                
 * initMatrix - Initialize the given matrix                                                                                       
 */
void initMatrix(int M, int N, int A[N][M], int B[M][N])
{
  int i, j;
  srand(time(NULL));
  for (i = 0; i < N; i++){
    for (j = 0; j < M; j++){
      // A[i][j] = i+j;  /* The matrix created this way is symmetric */                                                     
      A[i][j]=rand();
      B[j][i]=rand();
    }
  }
}

void randMatrix(int M, int N, int A[N][M]) {
  int i, j;
  srand(time(NULL));
  for (i = 0; i < N; i++){
    for (j = 0; j < M; j++){
      // A[i][j] = i+j;  /* The matrix created this way is symmetric */                                                     
      A[i][j]=rand();
    }
  }
}


/*                                                                                                                                * correctTrans - baseline transpose function used to evaluate correctness                                                      
 */ 
void correctTrans(int M, int N, int A[N][M], int B[M][N])
{
  int i, j, tmp;
  for (i = 0; i < N; i++){
    for (j = 0; j < M; j++){
      tmp = A[i][j];
      B[j][i] = tmp;
    }
  }
}



/*                                                                                                                               
 * registerTransFunction - Add the given trans function into your list                                                           
 *     of functions to be tested                                                                                               
 */
void registerTransFunction(void (*trans)(int M, int N, int[N][M], int[M][N]),
                           char* desc)
{
  func_list[func_counter].func_ptr = trans;
  func_list[func_counter].description = desc;
  func_list[func_counter].correct = 0;
  func_list[func_counter].num_hits = 0;
  func_list[func_counter].num_misses = 0;
  func_list[func_counter].num_evictions =0;
  func_counter++;
}
