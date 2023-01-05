#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  Function:  initGhost
  Purpose:   initilzes a ghost
       in:   the ghost class type
       in:   the room the ghost will be in
       in:   the ghost itself
   return:   no return value
*/
void initGhost(GhostClassType* gtype, RoomType* room, GhostType** ghost){
  *ghost = calloc(1,sizeof(GhostType));
  GhostClassType* newclass = (GhostClassType*)calloc(1,sizeof(GhostClassType));
  newclass = gtype;
  (*ghost)->class = newclass;
  (*ghost)->boredom_timer = BOREDOM_MAX;
  (*ghost)->room = room;
}
/*
  Function:  cleanUpGhost
  Purpose:   frees a ghosts memory
       in:   the ghost to be freed
   return:   no return value
*/
void cleanUpGhost(GhostType *ghost){
    free(ghost->class);
    free(ghost);
}
