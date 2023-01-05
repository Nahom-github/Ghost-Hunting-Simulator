#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include <pthread.h>
#include <semaphore.h>


int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    char hunter_name[MAX_STR];
    int i =0;
    HunterType* hunter;


    BuildingType *building;
    initBuilding(&building);

    while(i<4){
      printf("Enter Hunter Name\n");
      fgetc(stdin);
      fgets(hunter_name, MAX_STR, stdin);
      hunter_name[strlen(hunter_name)-1] = 0;
      initHunter(building->rooms->head->room, i,hunter_name, &hunter);
      building->hunters[i] = hunter;
      i++;
    }

    addRandom(&building->rooms, randInt(1,12), &building->ghost,randInt(POLTERGEIST, PHANTOM+1));
    printf("The ghost is in the %s\n", building->ghost->room->name);
    pthread_t hunter1;
    pthread_t hunter2;
    pthread_t hunter3;
    pthread_t hunter4;
    pthread_t ghostThread;

    pthread_create(&hunter1,NULL,startThreadHunter,building->hunters[0]);
    pthread_create(&hunter2,NULL,startThreadHunter,building->hunters[1]);
    pthread_create(&hunter3,NULL,startThreadHunter,building->hunters[2]);
    pthread_create(&hunter4,NULL,startThreadHunter,building->hunters[3]);
    pthread_create(&ghostThread,NULL,startThreadGhost,building->ghost);

    pthread_join(hunter1, (void**)(building->hunters[0]));
    pthread_join(hunter2,(void**)(building->hunters[1]));
    pthread_join(hunter3,(void**)(building->hunters[2]));
    pthread_join(hunter4,(void**)(building->hunters[3]));
    pthread_join(ghostThread,(void**)(building->ghost));

    i = 0;
    int size = 0;
    while(i < 4){
      if(building->hunters[i]->fear >= 100){
        printf("Hunter %s has a fear over 100\n",building->hunters[i]->name );
        size++;
      }
      i++;

    }
    if(size == 4){
      printf("the ghost has won");
    }else{
      printf("the hunters have won");
    }
    //cleanUpBuilding(&building);
    return 0;
}

void* startThreadHunter(void* hunter){
  HunterType* usehunt = hunter;

 while(usehunt->timer > 0 && usehunt->fear < 100){
   if(usehunt->room->ghost != NULL){
     usehunt->fear += 1;
     usehunt->timer = BOREDOM_MAX;
   }
   usehunt->timer -= 1;
   int rand = randInt(0,3);
   if(rand == 0){
     int result = collectEvidence(usehunt->evidence, usehunt->evidence_type,usehunt->room->evidence );
     if(result == 2) usehunt->timer = BOREDOM_MAX;
   }else if(rand == 1){
     changeHunterRoom(usehunt);
   }else{
     if(usehunt->room->hunters->head->next != NULL){
       communicateEvidence(usehunt, usehunt->evidence);
   }else{
     rand = randInt(0,2);
     if(rand == 1){
       int result = collectEvidence(usehunt->evidence, usehunt->evidence_type,usehunt->room->evidence );
       if(result == 2) usehunt->timer = BOREDOM_MAX;
     }
     else{
       changeHunterRoom(usehunt);
     }
   }
 }
 usehunt->timer -= 1;

}
 removeHunter(usehunt->room->hunters, usehunt);
 printf(" %s has left the room: \n", usehunt->name);
 return (void*) usehunt;
}

void* startThreadGhost(void* ghost){
  GhostType* useGhost = ghost;
  while(useGhost->boredom_timer > 0){
     if(useGhost->room->hunters->head != NULL){
       useGhost->boredom_timer = BOREDOM_MAX;
       if(randInt(0,2) == 0){
           EvidenceNodeType* check = leaveEvidence(*(useGhost->class));
           appendEvidence(check, useGhost->room->evidence);
           changeRooms(useGhost);
       }
     }else{
       useGhost->boredom_timer -= 1;
       int rand = randInt(0,3);
       if(rand == 0){
        changeRooms(useGhost);
       }else if(rand == 1){
           EvidenceNodeType* check = leaveEvidence(*(useGhost->class));
           appendEvidence(check, useGhost->room->evidence);
       }
     }
  }
  printf("Ghost has left the building \n");
  return (void*) useGhost;

}








/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}
