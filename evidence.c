#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
/*
  Function:  initEvidenceList
  Purpose:   Initializes an evidence list type
       in:   the list to be Initialized
   return:   no return value
*/
void initEvidenceList(EvidenceListType *list){
  list->head = NULL;
  list->tail = NULL;
}
/*
  Function:  initEvidenceArray
  Purpose:   initiilizes an evidence array
       in:   the evidence array to be initilized
   return:   no return value
*/
void evidenceArray(EvidenceArrayType *arr){
  arr->size = 0;
}

/*
  Function:  initEvidence
  Purpose:   initilzes the evidence
       in:   the evidence class
       in:   the float value
       in:   the evidence itself
   return:   no return value
*/
void initEvidence(EvidenceClassType class , float val, EvidenceType *evidence){
  evidence->class = class;
  evidence->value = val;

}
/*
  Function:  appendEvidence
  Purpose:   appends evidence to the end of a linked list
       in:   the evidence node
       in:   the evidence list
   return:   no return value
*/
void appendEvidence(EvidenceNodeType* evidence,EvidenceListType* list){
  char pass = FALSE;
  if(list->head == NULL){
    list->head = evidence;
    list->head->next = NULL;
    list->tail = evidence;
  }
  else{
    EvidenceNodeType* curr = list->head;
    do{
      if(curr->next != NULL){
        curr = curr->next;
      }
      else{
        evidence->next = NULL;
        curr->next = evidence;
        pass = TRUE;
      }
    }while(!pass);
  }


}

/*
  Function:  appendHunterEvidence
  Purpose:   appends evidence the end of a hunters evidence list
       in:   the evidence node
       in:   the evidence list
   return:   no return value
*/
void appendHunterEvidence(EvidenceNodeType* evidence,EvidenceListType* list){
  char pass = FALSE;
  if(list->head == NULL){
    list->head = evidence;
    list->tail = evidence;
  }
  else{
    EvidenceNodeType* curr = list->head;
    do{
      if(curr->next != NULL){
        curr = curr->next;
      }
      else{
        curr->next = evidence;
        pass = TRUE;
      }
    }while(!pass);
  }
}



/*
  Function:  collectEvidence
  Purpose:   alllows hunter to collect evidence in room
       in:   the hunters evidence list
       in:   the evidence class type
       in:   the evidence list of the room
   return:   returns 1 if the evidence is ghostly and 0 if there is no evidence and 2 if the evidence is standard
*/
int collectEvidence(EvidenceListType* hunterEvi, EvidenceClassType class, EvidenceListType* RoomEvi){

  EvidenceNodeType* curr = RoomEvi->head;
  EvidenceNodeType* prev = NULL;
  int result = 0;

  while(curr != NULL){
    if(curr->data != NULL){
      if(curr->data->class == class){
        appendHunterEvidence(curr, hunterEvi);
        if(curr->data->class == EMF){
            if(curr->data->value >= 4.91) result = 1;
        }else if(curr->data->class == TEMPERATURE){
            if(curr->data->value >= -10.0 && curr->data->value < 0.0 ) result = 1;
        }else if(curr->data->class == FINGERPRINTS){
            if(curr->data->value == 1) result = 1;
        }else if(curr->data->class == SOUND){
            if(curr->data->value > 70) result = 1;
        }else result = 2;
        break;
      }
    }
    prev = curr;
    curr = curr->next;

  }
  if(result == 0){
    return 0;
  }
  if(curr==NULL){
    return 0;
  }

  if(result == 1){
    if(curr->data->class == EMF){
        printf("hunter has collected some ghostly RANDOM EMF evidence");
    }else if(curr->data->class == TEMPERATURE){
        printf(" hunter has collected some gostly RANDOM TEMPERATURE evidence");
    }else if(curr->data->class == FINGERPRINTS){
        printf(" hunter has collected some gostly RANDOM FINGERPRINTS evidence");
    }else if(curr->data->class == SOUND){
        printf(" hunter has collected some gostly RANDOM SOUND evidence");
  }}else if(result == 2){
    if(curr->data->class == EMF){
        printf(" hunter has collected some RANDOM EMF evidence");
    }else if(curr->data->class == TEMPERATURE){
        printf(" hunter has collected some RANDOM TEMPERATURE evidence");
    }else if(curr->data->class == FINGERPRINTS){
        printf(" hunter has collected some RANDOM FINGERPRINTS evidence");
    }else if(curr->data->class == SOUND){
        printf(" hunter has collected some RANDOM SOUND evidence");
    }

  }

  if(prev==NULL){
    RoomEvi->head = curr->next;
  }
  else{
    prev->next = curr->next;
  }
  return result;
}
/*
  Function:  leaveEvidence
  Purpose:   lets the ghost leave evidence
       in:   the ghost class type
   return:   returns the created evidence by the ghost
*/
EvidenceNodeType* leaveEvidence(GhostClassType class){//could work without pointer for evidence and no need to calloc maybe
  EvidenceNodeType* newEvidence = (EvidenceNodeType*)calloc(1,sizeof(EvidenceNodeType));
  EvidenceType* evi = (EvidenceType*)calloc(1,sizeof(EvidenceType));
  int rand = randInt(0,3);
  if(class == POLTERGEIST){
    if(rand == 0){
      float generatedValue = randFloat(4.7,5);
      evi->class = EMF;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else if(rand == 1){
      float generatedValue = randFloat(-10,1);
      evi->class = TEMPERATURE;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else{
      float generatedValue = 1;
      evi->class = FINGERPRINTS;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }

  }else if(class == BANSHEE){
    if(rand == 0){
      float generatedValue = randFloat(4.7,5);
      evi->class = EMF;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else if(rand == 1){
      float generatedValue = randFloat(-10,1);
      evi->class = TEMPERATURE;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else{
      float generatedValue = randFloat(65,75);
      evi->class = SOUND;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }

  }else if(class == BULLIES){
    if(rand == 0){
      float generatedValue = randFloat(4.7,5);
      evi->class = EMF;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else if(rand == 1){
      float generatedValue = 1;
      evi->class = FINGERPRINTS;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else{
      float generatedValue = randFloat(65,75);
      evi->class = SOUND;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }

  }else{
    if(rand == 0){
      float generatedValue = 1;
      evi->class = FINGERPRINTS;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else if(rand == 1){
      float generatedValue = randFloat(-10,1);
      evi->class = TEMPERATURE;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }else{
      float generatedValue = randFloat(65,75);
      evi->class = SOUND;
      evi->value = generatedValue;
      newEvidence->data = evi;
      newEvidence->next = NULL;
    }

  }
  if(newEvidence->data->class == EMF){
      printf("ghost has left some ghostly RANDOM EMF evidence\n");
  }else if(newEvidence->data->class == TEMPERATURE){
      printf("ghost has left some gostly RANDOM TEMPERATURE evidence\n");
  }else if(newEvidence->data->class == FINGERPRINTS){
      printf("ghost has left some gostly RANDOM FINGERPRINTS evidence\n");
  }else if(newEvidence->data->class == SOUND){
      printf("ghost has left some gostly RANDOM SOUND evidence\n");
}
  return newEvidence;

}



/*
  Function:  ShareEvidence
  Purpose:   shares evidence between hunters
       in:   the hunters evidence list that will be added too
       in:   the evidence list of the hunter that is sharing their evidence
   return:   no return value
*/
void ShareEvidence(EvidenceListType* hunterEvi, EvidenceListType* RoomEvi){

  EvidenceNodeType* curr = RoomEvi->head;
  while(curr != NULL){
    if(curr->data != NULL){
        appendHunterEvidence(curr, hunterEvi);
    }
    curr = curr->next;
  }
}

/*
  Function:  communicateEvidence
  Purpose:   allows hunters to share evidence between themselves
       in:   the hunter who is sharing their evidence
       in:   the evidence list of the hunter
   return:   no return value
*/
void communicateEvidence(HunterType* hunter, EvidenceListType* evidence){

  char pass = FALSE;
  if(hunter->room->hunters->head->next == NULL){
    return;
  }
  else{
    HunterNodeType* curr = hunter->room->hunters->head;
    do{
      if(curr->next != NULL){

        if(randInt(0,2) == 1){
          curr = curr->next;
        }else{
          ShareEvidence(curr->hunter->evidence,hunter->evidence);
          return;
        }
      }
      else{
        ShareEvidence(curr->hunter->evidence,hunter->evidence);
        return;
      }
    }while(!pass);
  }

}


/*
  Function:  checkEvidence
  Purpose:   checks the hunters evidence to see if they have 3 different types of evidence to identify the ghost
       in:   the hunter  itself
   return:   returns 1 if they have enough information and 0 if they do not
*/
int checkEvidence(HunterType* hunter){
  int evidence[3];
  int size = 0;

  char pass = FALSE;
  if(hunter->evidence->head == NULL){
    return 0;
  }
  else{
    EvidenceNodeType* curr = hunter->evidence->head;
    do{
      if(curr->next != NULL){
          if(evidence[0] != 0 && curr->data->class == EMF){
            evidence[0] = 0;
            size++;
          }else if(evidence[1] != 1 && curr->data->class == TEMPERATURE){
            evidence[1] = 1;
            size++;
          }else if(evidence[2] != 2 && curr->data->class == FINGERPRINTS){
            evidence[2] = 2;
            size++;
          }else if(evidence[3] != 3 && curr->data->class == SOUND){
            evidence[3] = 3;
            size++;
          }

          curr = curr->next;
      }
      else{
        if(evidence[0] != 0 && curr->data->class == EMF){
          evidence[0] = 0;
          size++;
        }else if(evidence[1] != 1 && curr->data->class == TEMPERATURE){
          evidence[1] = 1;
          size++;
        }else if(evidence[2] != 2 && curr->data->class == FINGERPRINTS){
          evidence[2] = 2;
          size++;
        }else if(evidence[3] != 3 && curr->data->class == SOUND){
          evidence[3] = 3;
          size++;
        }
        if(size >= 3) return 1;
      }
    }while(!pass);
  }
  if(size >= 3) return 1;
  else return 0;
}
