#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
  char username[30];
  char password[30];
  Node *friends[100];
  int totalFriends;
  Node *inbox[100];
  Node *request[100];
  int totalSentRequest;
  int totalInbox;
  int priv;
  int numpriv;
  char privFriends[2][100];
  Node *next;
  char Note[260];
  char RecNote[260];
  char category[20];
  int val;
  int stats;
}*tail, *head;

Node *createNode (const char name[]){
    Node *newNode = (Node*) malloc (sizeof(Node));
    strcpy (newNode ->username, name);
    strcpy(newNode->Note, '\0');
    strcpy(newNode->RecNote, '\0');
    strcpy(newNode->category, '\0');
    newNode->stats = 0;
    newNode->priv = 0; // 1 artinya private, 0 artinya public
    newNode->numpriv=0;
    newNode -> totalFriends = 0;
    newNode -> totalInbox = 0;
    newNode -> totalSentRequest = 0;
    newNode-> next = newNode-> friends[0] = NULL;
    newNode->request[0] = newNode->inbox[0] = NULL;
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
  if(strcmp(curr->category, "\0") == 0){
    printf("There is no announcement.\n");
  } else {
    printf("Status: %s\n", curr->category);
  }
  puts("====================================");
  printf("Notes:\n");
  int i=1;
  Node *curr2 = head;
  printf("Announced:\n");
  puts("------------------------------------"); 
  while(curr2) {
    if(curr2->stats == 1) {
      if(curr2->priv == 0) {
      printf("%d. %s : %s\n", i, curr2->username, curr2->Note);
      i++;
      }else {
        int flag = 0;
        for(int i=0; i<curr2->numpriv; i++) {
          if(strcpy(curr2->privFriends[i], username) == 0){
            flag = 1;
            break;
          }
        }
        if(flag == 1) {
          printf("%d. %s : %s(private)\n", i, curr2->username, curr2->Note);
          i++;
        } else {
          continue;
        }
      }
    }
    curr2 = curr2->next;
  }
  puts("------------------------------------");
  Node *curr3 = head;
  int j = 1;
  while(curr3) {
    if(curr3->stats == 0) {
      if(curr2->priv == 0) {
      printf("%d. %s : %s\n", j, curr3->username, curr3->Note);
      j++;
      }else {
        int flag = 0;
        for(int i=0; i<=curr3->numpriv; i++) {
          if(strcpy(curr3->privFriends[i], username) == 0){
            flag = 1;
            break;
          }
        }
        if(flag == 1) {
          printf("%d. %s : %s(private)\n", i, curr3->username, curr3->Note);
          j++;
        } else {
          continue;
        }
      }      
    }
    curr3 = curr3->next;
  }
  puts("====================================");
}

void addNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  int flag = 0;
  if(strcmp(curr->Note, "\0") == 0) {
    flag = 1;
  }
  if(flag == 0) {
    tempdashboard(username);
    printf("Please input your new note:");
  } else {
    tempdashboard(username);
    printf("Please input the note you want to replace:");
  }
  char note[255];
  scanf("%[^\n]", note);
  strcpy(curr->Note, note);
  strcpy(curr->RecNote,note);
  
}

void editNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username )== 0) break;
    curr = curr->next;
  }
  if(strcmp(curr->Note, "\0") == 0) {
    printf("No notes to edit\n");
    dashboard(username);
  }

  char note[260];
  printf("Current Note:%s\n", curr->Note);
  printf("Input New Note:");
  scanf("%[^\n]", &note);
  strcpy(curr->Note, note);
  strcpy(curr->RecNote, note);
  return;
} 

void deleteNote(char const *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  if(strcmp(curr->Note, "\0") == 0) {
    printf("No Notes to be Deleted.\n");
    dashboard(username);
    return;
  }
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) {
      break;
    }
    curr = curr->next;
  }
  strcpy(curr->Note, '\0');
}

void recoverNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) {
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
    strcpy(curr->category, "Backlog");
  }else if(scan ==2) {
    strcpy(curr->category, "In Progress");
  }else if(scan == 3){
    strcpy(curr->category, "Peer Review");
  }else if(scan == 4) {
    strcpy(curr->category, "In Test");
  }else if(scan == 5) {
    strcpy(curr->category, "Done");
  }else if(scan == 6) {
    strcpy(curr->category, "Blocked");
  }else {
    printf("Invalid input, please try again.\n");
    printf("Please press enter to continue");
    char enter[3];
    scanf("%[^\n]", enter);
    category(username);
  }
  return;
}

void announceNote(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0)break;
    curr = curr->next;
  }
  printf("Do you want to announce your note?\n");
  printf("[1] Announce\n[2] Cancel\n");
  printf("Choose your option:");
  int n;
  scanf("%d", &n);
  if(n == 1) {
    curr->stats = 1;
    printf("Your note has been announced\n");
  }else if(n == 2) {
    dashboard(username);
  }else {
    puts("Invalid username, please try again.");
    announceNote(username);
  }
}

void privateAccount(const char *username) {
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0) {
      break;
    }
    curr = curr-> next;
  }
  curr->priv = 1;
  if(curr->numpriv < 2) {
    printf("Please input the unique username you want your note avaialble to:");
    char name[260];
    int flag = 0;
    scanf("%[^\n]", name);
    for(int i = 0; i<curr->numpriv; i++) {
      if(strcmp(curr->privFriends[i], name) == 0){
        puts("This username has already been on your private list.\n");
        flag = 1;
        break;
      }
    }
    if(flag == 1) {
      strcpy(curr->privFriends[curr->numpriv], name);
      curr->numpriv++;
    }
  } else {
    puts("The lists of private friends are full, please click enter to continue");
    char enter[3];
    scanf("%[^\n]", enter);
    dashboard(username);
  }
  return;
}


void dashboard(const char *username) {
  tempdashboard(username);
  Node *curr = head;
  while(curr) {
    if(strcmp(curr->username, username) == 0 )break;
    curr = curr->next;
  }
  printf("[1] Add\n[2] Edit\n[3] Announce\n[4] Delete Note\n[5] Recover Note\n [6]Update Category\n[7] Private Your Account\n[8] Return\n");
  printf("Choose Noting Option :");  
  int choice = 0;
  scanf("%d", &choice);
  if(choice == 1) {
    addNote(username);
  } else if(choice == 2) {
    editNote(username);
  } else if(choice == 3) {
    announceNote(username); // belum dikerjain
  } else if(choice == 4) {
    deleteNote(username);
  } else if(choice == 5) {
    recoverNote(username);
  } else if(choice == 6) {
    category(username);
  } else if(choice == 7) {
    privateAccount(username);
  
  }else if(choice == 8){
    //panggil function main beserta username;
    mainMenu(username);
  } else {
    printf("Invalid input, please try again.\n");
    dashboard(username);
  }
  return;
}


int main() {
  dashboard(username);
}
