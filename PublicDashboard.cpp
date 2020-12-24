#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
  char username[30];
  char password[30];
  Node *friends[100];
  int totalFriends;
  int totalSentRequest;
  int totalInbox;
  Node *next;
  char Note[260];
  char RecNote[260];
  char category[20];
  int val;
}*tail, *head;

Node *createNode (const char name[]){
    Node *newNode = (Node*) malloc (sizeof(Node));
    strcpy (newNode ->username, name);
    strcpy(newNode->Note, '\0');
    strcpy(newNode->RecNote, '\0');
    strcpy(newNode->category, '\0');
    
    newNode -> totalfriends = 0;
    newNode -> totalInbox = 0;
    newNode -> totalSentRequest = 0;
    newNode-> next = newNode-> friends[0] = NULL;
    return newNode;
}

void tempdashboard(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username)==0)break;
    curr = curr->next;
  }
  printf("Oo================================oO\n");
  printf("           STUDY NETWORK\n");
  printf("Oo================================oO\n");
  if(strcmp(curr->category, '\0') = 0){
    printf("There is no announcement.\n");
  } else {
    printf("Status: %s\n", curr->category);
  }
  printf("Notes:\n");
  int i=1;
  Node *curr2 = head;
  while(curr2) {
      printf("%d. %s : %s", i, curr2->username, curr2->Note);
    curr = curr->next;
  }
}

void addNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->name, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  char note[255];
  scanf("%[^\n]", note);
  strcpy(curr->Note, &note);
  strcpy(curr->RecNote,note);
}

void editNote(const char *username) {
  if(strcmp(curr->note, '\0') == 0) {
    printf("No Notes\n");
    dashboard();
    return;
  }
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->name, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  char note[260];
  printf("Current Note:%s\n", curr->note);
  printf("Input New Note:");
  scanf("%[^\n]", &note);
  strcpy(curr->Note, note);
  strcpy(curr->RecNote, note);
} 

void deleteNote(char const *username) {
  if(strcmp(curr->note, '\0') == 0) {
    printf("No Notes to be Deleted.\n");
    dashboard();
    return;
  }
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->name, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  strcpy(curr->Note, '\0');
}

void recoverNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->name, username) == 0) {
      break;
    }
    curr = curr->next;
  }  
  strcpy(curr->Note, curr->RecNote);
  printf("Your note has been recovered.\n");
  printf("Your note: %s\n", curr->Note);
}

void category(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) break;
    curr = curr->next;
  }

  printf("[1] Backlog\n[2] In Progress\n[3] Peer Review\n[4]In Test\n[5] Done\n[6] Blocked\n");
  printf("Choose your category:\n");
  int scan;
  scanf("%d", &scan);
  if(scan == 1) {
    strcpy(curr->category, 'Backlog');
  }else if(scan ==2) {
    strcpy(curr->category, 'In Progress');
  }else if(scan == 3){
    strcpy(curr->category, 'Peer Review');
  }else if(scan == 4) {
    strcpy(curr->category, 'In Test');
  }else if(scan == 5) {
    strcpy(curr->category, 'Done');
  }else if(scan == 6) {
    strcpy(curr->category, 'Blocked');
  }else {
    printf("Invalid input, please try again.\n");
    category();
  }
  return;
}
void dashboard() {
  tempdashboard();
  
  printf("[1] Add\n[2] Edit\n[3] Announce\n[4] Delete Note\n[5] Recover Note\n [6]Update Category\n");
  printf("Choose Noting Option :");  
  int choice = 0;
  scanf("%d", &choice);
  if(choice == 1) {
    addNote(username);
  } else if(choice == 2) {
    editNote(username);
  } else if(choice == 3) {
    announceNote(username);
  } else if(choice == 4) {
    deleteNote(username);
  } else if(choice == 5) {
    recoverNote(username);
  } else if(choice == 6) {
    category();
  } else {
    printf("Invalid input, please try again.\n");
    dashboard();
  }
  return;
}
int main() {
  dashboard();
}
