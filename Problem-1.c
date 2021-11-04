#include <stdbool.h> /*Define boolean data type*/
#include <pthread.h>/*for all thread functions (create,join,exit,runner)*/
#include <stdio.h> /* input/output capabilities of the C language*/
#include <unistd.h>/* process,fork */
#include <sys/wait.h>/* for wait function */
#include <sys/types.h> /*Define data types*/
#include <threads.h>// include thread local
/*  shared by the threads -global variables- */
int flag=0;
thread_local bool B [] = {false,false,false,false,false};//global but local for every thread
int A[5][5]= {
	     {1,2,3,4,5},
             {2,1,4,5,3},
             {4,3,5,1,2},
             {3,5,1,2,4},
             {5,4,2,3,1}};
    
/* runs as a separate thread that check rows */
void *runner1(void *p){

    int f =(int*) p;		//casting to int
        for(int j = 0; j<5; j++){
            if (B[A[f][j] % 5]){//is the global array in that nom. true? means it has duplicate then make flag
        printf("element %d in row %d and coloumn %d \n"
         ,A[f][j],f,j);
                flag=1;
                 pthread_exit(0);/*to terminate thread*/
             }
             else{
                B[A[f][j] % 5] = true;	//true means unique
                
               }
        }
}

/* runs as a separate thread that check columns */
void *runner2(void *p) {

    int f =(int*) p;		//casting to int
    
    for(int j = 0; j<5; j++){
        if (B[A[j][f] % 5]){	//is the global array in that nom. true? means it has duplicate then make flag
     printf("element %d in row %d and coloumn %d  [column checker] \n",A[j][f],j,f);
            flag=1;		
            pthread_exit(0);
        }
        else
            B[A[j][f] % 5] = true;
    }
  
    
}


int main() {
    
    /* thread identifier */
    pthread_t th1[5];
    pthread_t th2[5];
    
    for(int i = 0; i<5; i++)
      {
        /* create thread */	//rows checker
        pthread_create(&th1[i],NULL,runner1,i);
        pthread_join(th1[i],NULL);
        if(flag==1)
          {printf("INVALID\n");
          exit(0);
                   }
      }
    
    if(flag!=1)	//is it still valid?
    {			//col. checker
      for(int i = 0; i<5; i++)
       {
         pthread_create(&th2[i],NULL,runner2,i);
         pthread_join(th2[i],NULL);
         if(flag==1)
         { printf("INVALID\n");
           exit(0);
          }
       }
    }
        printf("VALID\n");    /*if it's still not
         				tremenited, obviously 
         				it's valid */            
       
}
        

    

