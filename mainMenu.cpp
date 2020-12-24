#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct Node{
  char username[30];
  char password[30];
  Node *friends[100];
  int totalFriends;
  int totalSentRequest;
  int totalInbox;
  Node *next,*prev;
  char Note[260];
  char RecNote[260];
  char category[20];
  int stats;
}*tail, *head,*user_head,*user_tail;

Node *createNode(const char *username,const char *password){
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->next = temp->prev = NULL;
  strcpy(temp->password,password);
  strcpy(temp->username,username);
  return temp;
}

//autentikasi
int authen(const char *username){
  Node *curr = user_head;
  int flag = 0;

    /* cek apakah memenuhi syarat nama username dan password*/
    int check = strlen(username);
    if(check>24){
      return 1;
    }
    else{
      while(curr){
        if(strcmp(username, curr->username) == 0){
          flag=1;
          break;
        }
        curr = curr->next;
      }
      for(int i = 0;i<check;i++){
          if(!(username[i] >= 'a' && username[i] <= 'z')){
            flag=1;
            break;
          }
        }
    }
  return flag;
}


int autenPassword(const char *password){
  int flag = 0;
  int len = strlen(password);
  for(int i = 0;i<len;i++){
    if(!(password[i] >= 'a' && password[i] <= 'z')){
      flag = 1;
      break;
    }
  }
  return flag;
}


void regis(){
  char pengguna[255]={0};
  int status = 1;
  while(status){
    printf("Please type in your username [lowercase || 1..24]: ");
    getchar();
    scanf("%[^\n]",pengguna);
    status = authen(pengguna);
    if(status == 1)printf("Invalid username please try again!\n");
  }

  int statuspass = 1;
  char password[255]={0};
  while(statuspass){
    printf("Please type in your password [lowercase || 1..24]: ");
    getchar();
    scanf("%[^\n]",password);
    statuspass = autenPassword(password);
    if(statuspass == 1)printf("Invalid password please try again!\n");
  }
  

  Node *regis= createNode(pengguna, password);
  if(!head){
    /*cek apakah usernamenya memenuhi ketentuan*/
    if(status==0){
      user_head = user_tail = regis;
    }
  }
  else{
    user_tail->next= regis;
    regis->prev = user_tail;
    regis->next = NULL;
    user_tail = regis;
  }
}

void mainMenu(){
  printf("Oo=====================================oO\n");
  printf("              STUDY NETWORK\n");
  printf("Oo=====================================oO\n\n");
  printf("[All User]\n");
  printf("No. Username\n");
  Node *curr = user_head;
  int num = 1;
  while(curr){
    printf("%d   %s\n",num,user_head->username);
    num++;
    curr = curr->next;
  }
  printf("-----------------------------------------\n");
  printf("[1] Register\n");
  printf("[2] Login\n");
  printf("[3] Exit\n");
  printf("-----------------------------------------\n");
  printf("Press 0 and enter to abort an operation\n");
  printf("-----------------------------------------\n");
  printf(">> ");
  int input = 0;
  scanf("%d",&input);
  if(input == 0){
    return;
  }else if(input == 1){
    regis();
  }else if(input == 2){
    // login();
  }else if(input == 3){
    return;
  }
}



int main(){
  clock_t begin = time(NULL);
  mainMenu();
  clock_t end = time(NULL);
  printf("You have allocated %ld seconds of your time for this program\n",end-begin);
}