#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define FEAR_RATE           1
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000
#define BOREDOM_MAX        99
#define MAX_ARR           128

#define TRUE                1
#define FALSE               0

// You may rename these types if you wish
typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

typedef struct room{
  char name[MAX_STR];
  struct roomList *rooms;
  struct EvidenceList* evidence;
  struct HunterList *hunters;
  struct Ghost *ghost;
  sem_t* mutex;
}RoomType;

typedef struct RoomNode{
  RoomType *room;
  struct RoomNode *next;
}RoomNodeType;

typedef struct roomList{
  RoomNodeType* head;
  RoomNodeType* tail;
}RoomListType;

typedef struct HunterNode{
  struct hunterTypeStruct *hunter;
  struct HunterNode *next;
}HunterNodeType;

typedef struct HunterList{
  HunterNodeType* head;
  HunterNodeType* tail;
}HunterListType;


typedef struct{
  EvidenceClassType class;
  float value;
}EvidenceType;

typedef struct EvidenceNode{
  EvidenceType *data;
  struct EvidenceNode *next;
}EvidenceNodeType;

typedef struct EvidenceList{
  EvidenceNodeType* head;
  EvidenceNodeType* tail;
}EvidenceListType;

typedef struct Ghost{
  GhostClassType* class;
  RoomType *room;
  int boredom_timer;
}GhostType;

typedef struct hunterTypeStruct{
  RoomType *room;
  EvidenceClassType evidence_type;
  EvidenceListType* evidence;
  char name[MAX_STR];
  int fear;
  int timer;
}HunterType;

typedef struct EvidenceArrayType{
    EvidenceType *elements[MAX_ARR];
    int size;
}EvidenceArrayType;

typedef struct Building{
  GhostType *ghost;
  HunterType *hunters[MAX_ARR];
  RoomListType *rooms;
}BuildingType;

int randInt(int, int);          // Generates a pseudorandom integer between the parameters
float randFloat(float, float);  // Generates a pseudorandom float between the parameters

void populateRooms(BuildingType*);   // Populates the building with sample data for rooms

void initRoom(RoomType*, char*);
void appendRoom(RoomListType*, RoomNodeType*);
//void connectRooms(RoomType*,RoomType*);
void initRoomList(RoomListType*);
void connectRooms(RoomListType*, RoomNodeType*, RoomListType*, RoomNodeType*);
void addRandom(RoomListType**,int, GhostType**,int);


void initBuilding(BuildingType**);

void initHunter(RoomType*, EvidenceClassType, char*, HunterType**);
void appendHunter(HunterListType*, HunterType*);
void initHunterList(HunterListType*);

void initEvidence(EvidenceClassType, float, EvidenceType*);
void evidenceArray(EvidenceArrayType*);
void initEvidenceList(EvidenceListType*);

void initGhost(GhostClassType*, RoomType*, GhostType**);
void* startThreadHunter(void*);
void* startThreadGhost(void*);
void check(HunterType*);

int collectEvidence(EvidenceListType*, EvidenceClassType, EvidenceListType*);
void changeHunterRoom(HunterType*);
void changeRooms(GhostType*);

void removeHunter(HunterListType*, HunterType*);

void appendEvidence(EvidenceNodeType*, EvidenceListType*);
void appendHunterEvidence(EvidenceNodeType*, EvidenceListType*);
EvidenceNodeType* leaveEvidence(GhostClassType);
int checkEvidence(HunterType*);

void cleanUpBuilding(BuildingType **b);
void cleanUpGhost(GhostType*);
void cleanUpHunters(HunterType*);
void cleanUpRooms(RoomListType*);

void cleanUpHunterData(EvidenceListType*);
void cleanUpHuntersList(EvidenceListType*);



void ShareEvidence(EvidenceListType*, EvidenceListType* RoomEvi);
void communicateEvidence(HunterType* hunter, EvidenceListType* evidence);
