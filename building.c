#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

/*
  Function:  populateRooms
  Purpose:   populates the rooms in the building
       in:   the building that will be populates
   return:   no return value
*/
void populateRooms(BuildingType* building) {
    // First, create each room. Perhaps you want to include more data
    // in the init parameters?
    RoomType* van = calloc(1, sizeof(RoomType));
    initRoom(van, "Van");
    RoomType* hallway = calloc(1, sizeof(RoomType));
    initRoom(hallway, "Hallway");
    RoomType* master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(master_bedroom, "Master Bedroom");
    RoomType* boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(boys_bedroom, "Boy's Bedroom");
    RoomType* bathroom = calloc(1, sizeof(RoomType));
    initRoom(bathroom, "Bathroom");
    RoomType* basement = calloc(1, sizeof(RoomType));
    initRoom(basement, "Basement");
    RoomType* basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(basement_hallway, "Basement Hallway");
    RoomType* right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(right_storage_room, "Right Storage Room");
    RoomType* left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(left_storage_room, "Left Storage Room");
    RoomType* kitchen = calloc(1, sizeof(RoomType));
    initRoom(kitchen, "Kitchen");
    RoomType* living_room = calloc(1, sizeof(RoomType));
    initRoom(living_room, "Living Room");
    RoomType* garage = calloc(1, sizeof(RoomType));
    initRoom(garage, "Garage");
    RoomType* utility_room = calloc(1, sizeof(RoomType));
    initRoom(utility_room, "Utility Room");

    // Now create a linked list of rooms using RoomNodeType in the Building
    RoomNodeType* van_node = calloc(1, sizeof(RoomNodeType));
    van_node->room = van;
    RoomNodeType* hallway_node = calloc(1, sizeof(RoomNodeType));
    hallway_node->room = hallway;
    RoomNodeType* master_bedroom_node = calloc(1, sizeof(RoomNodeType));
    master_bedroom_node->room = master_bedroom;
    RoomNodeType* boys_bedroom_node = calloc(1, sizeof(RoomNodeType));
    boys_bedroom_node->room = boys_bedroom;
    RoomNodeType* bathroom_node = calloc(1, sizeof(RoomNodeType));
    bathroom_node->room = bathroom;
    RoomNodeType* basement_node = calloc(1, sizeof(RoomNodeType));
    basement_node->room = basement;
    RoomNodeType* basement_hallway_node = calloc(1, sizeof(RoomNodeType));
    basement_hallway_node->room = basement_hallway;
    RoomNodeType* right_storage_room_node = calloc(1, sizeof(RoomNodeType));
    right_storage_room_node->room = right_storage_room;
    RoomNodeType* left_storage_room_node = calloc(1, sizeof(RoomNodeType));
    left_storage_room_node->room = left_storage_room;
    RoomNodeType* kitchen_node = calloc(1, sizeof(RoomNodeType));
    kitchen_node->room = kitchen;
    RoomNodeType* living_room_node = calloc(1, sizeof(RoomNodeType));
    living_room_node->room = living_room;
    RoomNodeType* garage_node = calloc(1, sizeof(RoomNodeType));
    garage_node->room = garage;
    RoomNodeType* utility_room_node = calloc(1, sizeof(RoomNodeType));
    utility_room_node->room = utility_room;

    // Building->rooms might be a linked list structre, or maybe just a node.
    initRoomList(building->rooms);
    appendRoom(building->rooms, van_node);
    appendRoom(building->rooms, hallway_node);
    appendRoom(building->rooms, master_bedroom_node);
    appendRoom(building->rooms, boys_bedroom_node);
    appendRoom(building->rooms, bathroom_node);
    appendRoom(building->rooms, basement_node);
    appendRoom(building->rooms, basement_hallway_node);
    appendRoom(building->rooms, right_storage_room_node);
    appendRoom(building->rooms, left_storage_room_node);
    appendRoom(building->rooms, kitchen_node);
    appendRoom(building->rooms, living_room_node);
    appendRoom(building->rooms, garage_node);
    appendRoom(building->rooms, utility_room_node);

    // Now connect the rooms. It is possible you do not need a separate
    // function for this, but it is provided to give you a starting point.
    connectRooms(van->rooms, hallway_node, hallway->rooms, van_node);
    connectRooms(hallway->rooms, master_bedroom_node, master_bedroom->rooms, hallway_node);
    connectRooms(hallway->rooms, boys_bedroom_node, boys_bedroom->rooms, hallway_node);
    connectRooms(hallway->rooms, bathroom_node, bathroom->rooms, hallway_node);
    connectRooms(hallway->rooms, kitchen_node, kitchen->rooms, hallway_node);
    connectRooms(hallway->rooms, basement_node, basement->rooms, hallway_node);
    connectRooms(basement->rooms, basement_hallway_node, basement->rooms, basement_node);
    connectRooms(basement_hallway->rooms, right_storage_room_node, right_storage_room->rooms, basement_hallway_node);
    connectRooms(basement_hallway->rooms, left_storage_room_node, left_storage_room->rooms, basement_hallway_node);
    connectRooms(kitchen->rooms, living_room_node, living_room->rooms, kitchen_node);
    connectRooms(kitchen->rooms, garage_node, garage->rooms, kitchen_node);
    connectRooms(garage->rooms, utility_room_node, utility_room->rooms, garage_node);
}

/*
  Function:  connectRooms
  Purpose:   connects two rooms adjacent rooms together
       in:   the first rooms roomlist
       in:   the second rooms roomnode
       in:   the second rooms roomlist
       in:   the first rooms roomnode
   return:   no return value
*/
void connectRooms(RoomListType *list, RoomNodeType *roomNode, RoomListType *list2, RoomNodeType *roomNode2){
  RoomNodeType* roomList = calloc(1, sizeof(RoomNodeType));
  roomList->room = roomNode->room;
  char pass = FALSE;
  if(list->head == NULL){
    list->head = roomList;
    list->tail = roomList;
  }
  else{
    RoomNodeType* curr = list->head;
    do{
      if(curr->next != NULL){
        curr = curr->next;
      }
      else{
        roomList->next = NULL;
        curr->next = roomList;
        curr->next->next = NULL;
        pass = TRUE;
      }
    }while(!pass);
  }

  RoomNodeType* roomList2 = calloc(1, sizeof(RoomNodeType));
  roomList2->room = roomNode2->room;
  pass = FALSE;
  if(list2->head == NULL){
    list2->head = roomList2;
    list2->tail = roomList2;
  }
  else{
    RoomNodeType* curr2 = list2->head;
    do{
      if(curr2->next != NULL){
        curr2 = curr2->next;
      }
      else{
        roomList2->next = NULL;
        curr2->next = roomList2;
        curr2->next->next = NULL;
        pass = TRUE;
      }
    }while(!pass);
  }
}
/*
  Function:  initBuilding
  Purpose:   Initializes the building
       in:   the building to be Initialized
   return:   no return value
*/
void initBuilding(BuildingType **b){
  (*b) = calloc(1, sizeof(BuildingType));
  (*b)->ghost = calloc(1,sizeof(GhostType));
  (*b)->rooms = calloc(1,sizeof(RoomListType));
  populateRooms((*b));
}
/*
  Function: cleanupBuilding()
  Purpose:  cleans up the building memory
       in:   the building to be freed
*/
void cleanUpBuilding(BuildingType **b){
  cleanUpGhost((*b)->ghost);
  int i = 0;
  while(i < 5){
  cleanUpHunters((*b)->hunters[i]);
  i++;
  }
  cleanUpRooms((*b)->rooms);


  free(*b);
}
