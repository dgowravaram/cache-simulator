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
    Temporary local storage is available in /scratch.
  Note: Data stored locally will NOT be backed up.
---------------------------------------------------------

[divyag@csa2 ~]$ ls
210  210_midterm_practice  A1  bomb136  bomb136.tar  cachelab  cs210  mail  Mail  myfile.c  scratch  target14  target14.tar
[divyag@csa2 ~]$ cd cachelab
[divyag@csa2 cachelab]$ ls
cachelab.c  cachelab.pdf  csim.c    driver.py  Makefile  test-csim   test-trans.c  tracegen.c  trans.c  valgrind
cachelab.h  csim          csim-ref  make       README    test-trans  tracegen      traces      trans.o
[divyag@csa2 cachelab]$ emacs cachelab.c















File Edit Options Buffers Tools C Help                                                                                            
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
