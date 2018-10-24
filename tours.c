// take in number of tourists and number of cycles 
// store in an array of tourists + 1 element sub 0 is thread ID for indiana jones
// rest will be ID for tourists pthread create pthread join
// 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include "wrappers.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define MAXTOURISTS 50
void* indi(void *);
void* tourist(void *);
void* start_threads(pthread_t[], long);
void* join_threads(pthread_t[], long);

int trips
int shopping;
int tickets;
sem_t  *AvailSeats , *arrived, *busLoaded , *printing, *mutex;



void usage(char* cmd){
    printf("improper usage\n");
}

int main(int argc, char **argv){
    

    pthread_t thrd[MAXTOURISTS + 1];

    if(argc < 3){
        usage(argv[0]);
    }
    int semflg = O_CREAT;
    int semmode = S_IRUSR | S_IWUSR;
    
    AvailSeats = Sem_open("/AvailSeats1_lee3ac", semflg, semmode, 0);
    arrived = Sem_open("/arrived1_lee3ac", semflg, semmode, 0);
    busLoaded = Sem_open("/busLoaded1_lee3ac", semflg, semmode, 0);
    mutex = Sem_open("/mutex1_lee3ac", semflg, semmode, 0);
    
    printing = Sem_open("/printing1_lee3ac", semflg, semmode, 0);
   
  
    
    long numTourists = atol(argv[1]);
    trips = atol(argv[2]);
    if(numTourists > MAXTOURISTS){
        usage(argv[0]);
    }
    tickets = trips * numTourists;
    start_threads(thrd, numTourists);
    
    join_threads(thrd, numTourists);


    //cheack if numb tourisits is greater than max tourists

    

    //start threads helper that creates all threads pass thread array and number of tourists
    //CALLS PTHREAD CREATE MAKING driver passing number of tourists as the pointer
    // then loop from 1 to number of tourists creating thread i using tourists function 

    //jointhreads pass thread array and number of tourists loop for num tourist and join passing id

    // make thread function called indiana cast pointer to void param as long
    //printf started and number of passengers he will be carrying then goodbye then return void* null

    // make function called tourist case pointer to void param as long then printf his and exits return void* null 



    printf("OPERATOR DONE FOR NOW\n");

}



void* indi(void* i){
   


    long ID = (long) i;
    
    
    printf("Drier: hi just started with ID = %ld\n", ID);
    
    //wait for arrived semaphore
    Sem_wait(arrived);
    //if(all tourists leave town) how do we know that a toursits has completed. yes it will retrn but how does 
    //INDI know
    //avliableSeats = MAXSEATS
    //wait(busLoaded)
    //
     
    printf("Going to server %ld tourists\n", ID);
    
    return NULL;
}
void* tourist(void* i){
  

    long ID = (long) i;
    int myTrips = trips;
    printf("Tourists ID = %ld I just arrived in harrisonburg!\n", ID);
    //post to arrived semaphore
    Sem_post(arrived);
    while(myTrips > 0){
	

      myTrips--;
    }
    //while trips > 0  do we start off shopping or waiting for an avalible seat on the bus?
    //print going shoping sleep for random miliseconds
    //wait for availseats semaphore
    //shopping-- 
    //if avalible seats == MAXSEATS or shopping = 0 then post busLoaded
    
    
    
    
    printf("Leaving town!\n");
    
    return NULL;
}


void* join_threads(pthread_t thrd[], long numtourists){
    
    for(int i = 0; i < numtourists; i++){
        Pthread_join(thrd[i], NULL);
    }
    return NULL;

}


void* start_threads(pthread_t thrd[], long numtourists){
    
    
    
    
    Pthread_create(&thrd[0], NULL, indi, (void*) numtourists);
     
    for(long i = 1; i <= numtourists; i++){
        Pthread_create(&thrd[i], NULL, tourist, (void*) i);
    }
    
    return NULL;
}
