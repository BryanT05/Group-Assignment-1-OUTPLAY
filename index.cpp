#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int end = 0;
struct Node{
  char username[30];
  char password[30];
  Node *friends[100];
  int totalFriends;
  Node *inbox[100];
  int totalInbox;
  Node *request[100];
  int totalSentRequest;
  Node *next,*prev;
  char Note[260];
  char RecNote[260];
  char category[20];
  int val;
  int stats;
}*user_tail, *user_head,*curr;

// ================== Function Construct ==================================
void printFriends ();
void LoginScreen();
void AddFriend ();
void removeFriend();
void viewInbox();
void viewSentRequest();

// =================== Main Menu & Authentication =========================
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
  printf("\n======= User Registered Successfully ========\n\n");
  if(!user_head){
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

void login(){
  end = 1;
  int success = 0;
  while(!success){
    char username[30] = {0};
    char password[30] = {0};
    printf("Masukkan Username: ");
    getchar();
    scanf("%[^\n]",username);
    printf("Masukkan Password: ");
    getchar();
    scanf("%[^\n]",password);
    Node *temp = user_head;
    
    while(temp){
      if(strcmp(username,temp->username) == 0){
        if(strcmp(password,temp->password) == 0){
          success = 1;
          curr = temp;
          break;
        }
      }
      temp = temp->next;
    }
    if(!success)printf("Invalid Username or Password please try again!\n");
  }
  if(success == 1){
    printf("\n====== Login Successfull ======\n\n");
    LoginScreen();
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
    end = 1;
    return;
  }else if(input == 1){
    regis();
  }else if(input == 2){
    login();
  }else if(input == 3){
    end = 1;
    return;
  }
}

void LoginScreen(){
  printf("Oo=====================================oO\n");
  printf("Welcome, %s\n",curr->username);
  printf("Oo=====================================oO\n\n");
  time_t t;
  time(&t);
  printf("Logged in: %s\n", ctime(&t));
  printf("-----------------------------------------\n");
  printFriends();
  printf("-----------------------------------------\n");
  printf("             >>Menu<<\n");
  printf("-----------------------------------------\n");
  printf("[1] Add Friend\n");
  printf("[2] Remove Friend\n");
  printf("[3] View Inbox\n");
  printf("[4] View Sent Request\n");
  printf("[5] Add, Edit, Announce, Delete Note\n\n");
  printf("[6] Log out\n");
  printf("-----------------------------------------\n");
  printf(">>");
  int input = 0;
  scanf("%d",&input);

        if (input==1){
            getchar();
            AddFriend();
            LoginScreen();
        }
        else if (input==2){
            getchar();
            removeFriend();
            LoginScreen();
        }
        else if (input==3){
            getchar();
            viewInbox();
            LoginScreen();
        }
        else if (input==4){
            getchar();
            viewSentRequest();
            LoginScreen();
        }
        else if (input==5){
            printf("Bukan bagian gue\n");
        }
        else if (input==6){
            getchar();
            mainMenu();
        }

  printf("-----------------------------------------\n");
}

// ==================  Friend Management ===============

Node *createNode3 (const char name[]){
    Node *temp = (Node*) malloc (sizeof(Node));

    strcpy (temp ->username, name);
    temp -> totalFriends = 0;
    temp -> totalInbox = 0;
    temp -> totalSentRequest = 0;
    temp-> friends[0] = NULL;
    temp -> inbox[0]= NULL;
    temp ->request[0] =NULL;

    temp-> next = temp->prev = NULL;
    return temp;
}

void pushuser_head (const char name[]){
    Node *temp = createNode3 (name); 

    if (!user_head){ 
        user_head = user_tail = temp;
    }
    else { 
        temp->next =  user_head;
        user_head->prev = temp;
        user_head = temp;
    }
}

void pushuser_tail (const char name[]){
    Node *temp = createNode3 (name);

    if (!user_head){ 
        user_head= user_tail = temp;
    }
    else { 
        temp->prev = user_tail;
        user_tail->next = temp;
        user_tail =  temp;
    }
}

void printLinkedList (){
    printf("Linked List :\n");

    Node *curr = user_head; // curr adalah index yang akan berjalan

    while (curr){ // selama curr tidak sama dengan NULL
        printf("%s\n", curr->username);
        curr = curr->next; // Update curr nya ke next
    }
}

// FUNCTION UNTUK FRIENDS MANAGEMENT
void AddFriend (){
    Node *user = curr;

    Node *temp = user_head;
    int no = 1;
    int pass=1;
    printf ("\n[All User]\nNo. Username\n");
    while (temp){
        if (strcmp(temp->username, user->username)!=0){
            printf ("%d   %s\n", no, temp->username);
            no++;
            pass=0;
        }
        temp = temp->next;
    }
    puts ("");
    char newfriend [255];
    if (pass!=0){
        printf ("There is no User!\n");
    }else {
        printf("Which user do you want to add?\n>>");
        scanf ("%s", &newfriend);getchar ();
    }
    
    int flag=1;
    Node *curr = user_head;
    while (curr){
        if (strcmp (curr->username, newfriend)==0){
            printf("\n-- Your request has benn sent to %s --\n", newfriend);
            curr->inbox[curr->totalInbox] = user;
            curr->totalInbox++;
            user->request[user->totalSentRequest] = curr;
            user->totalSentRequest++;
            flag = 0;
            break;
        }
        curr= curr->next;
    }
    if (flag && pass == 0){
        printf ("\n--There is no %s in User List\n", newfriend);
    }
    printf("Press enter to continue!\n");
    getchar();
    getchar();
}

void viewInbox(){
    Node *user = curr;
    


    printf ("\n[All Friend Request of %s]\n", user->username);
    printf ("No. Userame\n");
    for (int i=0; i < user->totalInbox; i++){
        if (user->inbox[i]->username!= NULL) printf("%d   %s\n", i+1, user->inbox[i]->username);
    }
    char temp[255];
    if (user->totalInbox==0){
        printf ("Your Inbox is empty\n");
    }
    else {
        printf ("\nWhich user do you want to be accepted?\n>>");
        scanf("%[^\n]", &temp); getchar();
    }
    int flag =1;
    for (int i=0; i< user->totalInbox; i++){
        if (strcmp (temp, user->inbox[i]->username)==0){
            user->friends[user->totalFriends] = user->inbox[i];
            user->inbox[i]->friends[user->inbox[i]->totalFriends] = user;
            user->totalFriends++;
            user->inbox[i]->totalFriends++;
            printf ("\n--You accepted the request from %s--\n", user->inbox[i]->username);
            flag = 0;

            int index=0;
            for (int j=0; j<user->inbox[i]->totalSentRequest; j++){
                if (strcmp (user->username, user->inbox[i]->request[j]->username)==0){
                    index=j;
                }
            }
            user->inbox[i]->totalSentRequest--;
            for (int j=index; j<user->inbox[i]->totalSentRequest; j++){
                user->inbox[i]->request[j] = user->inbox[i]->request[j+1];
            }
            user->inbox[i]->request[user->inbox[i]->totalSentRequest]==NULL;

            user->totalInbox--;
            for (int j=i; j<user->totalInbox; j++){
                user->inbox[j]= user->inbox[j+1];
            }
            user->inbox[user->totalInbox]= NULL;
            break;
        }
    }
    if (flag){
        printf ("\n--There is no %s in your Friend Request\n", temp);
    }
    printf ("Press enter to continue!\n");
    getchar();
    getchar();
}

void viewSentRequest(){
    Node *user = curr;

    printf ("\n[%s's Sent Request]\n", user->username);
    if(user->totalSentRequest==0){
        printf ("Your Sent Request is empty\n");
    } 
    else {
        printf ("No. Username\n");
        for (int i=0; i< user->totalSentRequest; i++){
            printf ("%d   %s\n", i+1, user->request[i]->username);
        }
    }
    printf("Press enter to continue!\n");
    getchar();
    getchar();
}

void printFriends (){
    Node *user = curr;
    printf ("\n[All Friends of %s]\nNo. Username\n", user->username);
    if (user->totalFriends==0){
        printf ("You have no Friends yet\n");
    }
    else {
        for (int i=0; i<user->totalFriends; i++){
            printf ("%d   %s\n", i+1, user->friends[i]->username);
        }
    }
}

void removeFriend (){
    Node *user = curr;
    
    printFriends();
    char temp [255];
    int flag=1;
    if (user->totalFriends == 0){
        flag = -1;
    }else {
        printf ("\nWhich user do you want to remove?\n>>");
        scanf ("%[^\n]", &temp); getchar ();
    }

    for (int i=0; i<user->totalFriends; i++){
        if (strcmp(temp, user->friends[i]->username)==0){
            flag=0;
            for (int j=i; j<user->totalFriends-1; j++){
                user->friends[j]=user->friends[j+1];
            }
            user->friends[user->totalFriends-1]=NULL;
            user->totalFriends--;
            printf ("\n-- You are no longer friends with %s --\n", temp);
            break; 
        }
    }
    if (flag==0) printf ("\nThere is no %s in your Firend List\n", temp);
    printf("Press enter to continue!\n");
    getchar();
    getchar();
}


// ================== Main Caller Function =============
void caller(){
  while(!end){
    mainMenu();
  }
}

int main(){
  clock_t begin = time(NULL);
  caller();
  clock_t end = time(NULL);
  printf("You have allocated %ld seconds of your time for this program\n",end-begin);
}