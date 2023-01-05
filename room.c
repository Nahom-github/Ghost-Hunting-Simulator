#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"


/*
  Function:  initRoom
  Purpose:   initilzes the room
       in:   the room itself
       in:   the room name
   return:   no return value
*/
void initRoom(RoomType* room, char *name){
  strcpy(room->name, name);
  room->ghost = NULL;
  RoomListType* newRoomList = (RoomListType*)calloc(1,sizeof(RoomListType));
  initRoomList(newRoomList);
   room->rooms = newRoomList;
  EvidenceListType* newEvidenceList = (EvidenceListType*)calloc(1,sizeof(EvidenceListType));
  room->evidence = newEvidenceList;
  HunterListType* newHunterList = (HunterListType*)calloc(1,sizeof(HunterListType));
  initHunterList(newHunterList);
  room->hunters = newHunterList;
  sem_t mutex;
  sem_init(&mutex,0,1);
  room->mutex = &mutex;
}

/*
  Function:  initRoomList
  Purpose:   initilizes the room list
       in:   the room list
   return:   no return value
*/
void initRoomList(RoomListType* list){
  list->head = NULL;
  list->tail = NULL;
}

/*
  Function:  appendRoom
  Purpose:   appends a room to the end of a linked list
       in:   the room list
       in:   the roomnode
   return:   no return value
*/
void appendRoom(RoomListType *list, RoomNodeType *roomNode){
  char pass = FALSE;
  if(list->head == NULL){
    list->head = roomNode;
    list->head->next = NULL;
    list->tail = roomNode;
  }
  else{
    RoomNodeType* curr = list->head;
    do{
      if(curr->next != NULL){
        curr = curr->next;
      }
      else{
        roomNode->next = NULL;
        curr->next = roomNode;
        pass = TRUE;
      }
    }while(!pass);
  }
}


/*
  Function:  changeRooms
  Purpose:   lets a ghost change their room
       in:   the ghost itself
   return:   no return value
*/
void changeRooms(GhostType* ghost){

  char pass = FALSE;
  if(ghost->room->rooms->head == NULL){
    return;
  }
  else{
    RoomNodeType* curr = ghost->room->rooms->head;
    do{
      if(curr->next != NULL){

        if(randInt(0,2) == 1){
          curr = curr->next;
        }else{
          ghost->room->ghost = NULL;
          ghost->room = curr->room;
          curr->room->ghost = ghost;
          return;
        }
      }
      else{
        ghost->room->ghost = NULL;
        ghost->room = curr->room;
        curr->room->ghost = ghost;
        return;
      }
    }while(!pass);
  }
}

/*
  Function:  addRandom
  Purpose:   adds a ghost to a random room
       in:   the room list
       in:   how many rooms in the linked list to skip
       in:   the ghost
       in:   the class for the ghost
   return:   no return value
*/
void addRandom(RoomListType** list, int num, GhostType** ghost, int class){
  if(num == 0){
    return;
  }
  RoomNodeType* curr = (*list)->head;

  int i=0;
  while(curr!=NULL){
    if(i==num){
      break;
    }
    i++;
    curr=curr->next;
  }

  GhostClassType classtype;
  if(class == 0) classtype = POLTERGEIST;
  else if(class == 1) classtype = BANSHEE;
  else if(class == 2) classtype = BULLIES;
  else if(class == 3) classtype = PHANTOM;
  initGhost(&classtype,curr->room, ghost);
  curr->room->ghost = (*ghost);
}

/*
  Function: cleanUpRooms()
  Purpose:  the room to be cleaned up
       in:   the roomlist to be cleaned
    return:  no return value
*/
//Citation: my implementation of this function is heavily influenced by the cleanup(NodeType* head) function from the code demo in week 9, lecture 13
void cleanUpRooms(RoomListType* rooms){
  RoomNodeType* curr = rooms->head;
  RoomNodeType* next = NULL;

    while(curr != NULL){
        next = curr->next;
        curr = next;
   }

        curr = rooms->head;
        next = NULL;

    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }



  free(rooms);
}
