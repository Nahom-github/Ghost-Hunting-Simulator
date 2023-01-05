#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"


/*
  Function:  initHunter
  Purpose:   initiilizes the hunter
       in:   the room the hunter will be in
       in:   the type of evidence the hunter can collect
       in:   the name
       in:   the hunter itself
   return:   no return value
*/
void initHunter(RoomType* room, EvidenceClassType class, char* name, HunterType **hunter){
  *hunter = (HunterType*)calloc(1,sizeof(HunterType));
  (*hunter)->room = room;
  (*hunter)->evidence_type = class;
  strcpy((*hunter)->name,name);
  (*hunter)->fear = 0;
  (*hunter)->timer = BOREDOM_MAX;
  EvidenceListType* evidence = (EvidenceListType*)calloc(1,sizeof(EvidenceListType));
  initEvidenceList(evidence);
  (*hunter)->evidence = evidence;
  appendHunter(room->hunters, (*hunter));
}

/*
  Function:  initHunterList
  Purpose:   initilzes the hunter
       in:   the list of hunters
   return:   no return value
*/
void initHunterList(HunterListType* list){
  list->head = NULL;
  list->tail = NULL;
}

/*
  Function: changeHunterRoom
  Purpose:  Allows the hunter to change their room
       in:   the hunter to change room
  return:  no return value
*/
void changeHunterRoom(HunterType* hunter){
  char pass = FALSE;
  if(hunter->room->rooms->head == NULL){
    return;
  }
  else{
    RoomNodeType* curr = hunter->room->rooms->head;
    do{
      if(curr->next != NULL){

        if(randInt(0,2) == 1){
          curr = curr->next;
        }else{
          removeHunter(hunter->room->hunters, hunter);
          hunter->room = curr->room;
          appendHunter(curr->room->hunters, hunter);
          //printf("\n%s has moved to the %s\n", hunter->name, hunter->room->name);
          break;
        }

      }
      else{
        removeHunter(hunter->room->hunters, hunter);
        hunter->room = curr->room;
        appendHunter(curr->room->hunters, hunter);
        //printf("%s has moved 2 the %s", hunter->name, hunter->room->name);
        break;
      }
    }while(!pass);
  }


}




/*
  Function: removeHunter()
  Purpose:  removes a hunter from a hunterlist
       in:  the hunterlist to be removes from
       in:  the hunter to be removed
*/
void removeHunter(HunterListType* list, HunterType* hunter){
  HunterNodeType* curr = list->head;
  HunterNodeType* prev = NULL;
  int count = 0;
  while(curr != NULL){
    if(curr->hunter != NULL){
      if(curr->hunter == hunter){
        break;
      }
    }

    prev = curr;
    curr = curr->next;
    if(count > 100000) printf("colect");
    count++;
  }
  if(curr==NULL){
    return;
  }

  if(prev==NULL){
    list->head = curr->next;
  }
  else{
    prev->next = curr->next;
  }

}




/*
  Function: appebdHunter()
  Purpose:  appends hunter to hunterlist
       in:  the hunter list to be appended too
       in:  the hunter to be appended
  return;   no return value
*/
void appendHunter(HunterListType* list, HunterType* hunter){
  HunterNodeType* hunterNode = calloc(1, sizeof(HunterNodeType));
  hunterNode->hunter = hunter;
  int count = 0;
  char pass = FALSE;
  if(list->head == NULL){
    list->head = hunterNode;
    list->head->next = NULL;
    list->tail = hunterNode;
  }
  else{
    HunterNodeType* curr = list->head;
    do{
      if(curr->next != NULL){
        curr = curr->next;
        if(count > 100000) printf("colect");
        count++;
      }
      else{
        hunterNode->next = NULL;
        curr->next = hunterNode;
        pass = TRUE;
      }
    }while(!pass);
  }
}

/*
  Function: cleanUpHunters()
  Purpose:  cleans up the hunters data
       in:   the hunters whos memory will be freed
*/
void cleanUpHunters(HunterType* hunters){
  cleanUpHunterData(hunters->evidence);
  cleanUpHuntersList(hunters->evidence);
  free(hunters);

}

/*
  Function: cleanUpHunterData()
  Purpose:  cleans up a hunters node
       in:   the ghostlist itself to be freed
 Citation: my implementation of this function is heavily influenced by the cleanup(NodeType* head)
               function from the code demo in week 9, lecture 13
*/
void cleanUpHunterData(EvidenceListType *list){
    EvidenceNodeType* curr = list->head;
    EvidenceNodeType* next = NULL;

    while(curr != NULL){
        next = curr->next;
        free(curr->data);
        curr = next;
    }

}
/*
  Function: cleanHuntersList()
  Purpose:  cleans up the hunters list
       in:   cleans up the hunters evidence list
    review: no return value
    Citation: my implementation of this function is heavily influenced by the cleanup(NodeType* head)
                  function from the code demo in week 9, lecture 13
*/
void cleanUpHuntersList(EvidenceListType *list){
    EvidenceNodeType* curr = list->head;
    EvidenceNodeType* next = NULL;

    while(curr != NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }

}
