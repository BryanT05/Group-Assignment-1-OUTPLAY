#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char username [255];
    Node *next;

    int totalfriends;
    Node *friends[100];

    int totalInbox;
    Node *inbox[100];

    int totalSentRequest;
    Node *request[100];
} *head, *tail; 

Node *createNode (const char name[]){
    Node *newNode = (Node*) malloc (sizeof(Node));
    strcpy (newNode ->username, name);
    newNode -> totalfriends = 0;
    newNode -> totalInbox = 0;
    newNode -> totalSentRequest = 0;
    newNode-> next = newNode-> friends[0] = NULL;
    return newNode;
}

void pushHead (const char name[]){
    Node *temp = createNode (name); 

    if (!head){ 
        head = tail = temp;
    }
    else { 
        temp->next =  head;
        head = temp;
    }
}

void pushTail (const char name[]){
    Node *temp = createNode (name);

    if (!head){ 
        head= tail = temp;
    }
    else { 
        tail->next = temp;
        tail =  temp;
    }
}

void popHead (){
    if (!head){
        return;
    } else if (head==tail) {
        free(head);
        head = tail = NULL;
    }
    else {
        Node *temp = head;
        head = temp->next; 
        free(temp);
        temp->next = NULL;
    }
}

void popTail (){
    if (!head){
        return;
    }
    else if (head==tail){
        head = tail = NULL;
        free(head);
    }
    else {
        Node *temp = head; 
        while (temp->next != tail){
            temp = temp->next;
        }              
        temp->next = NULL;
        free(tail); 
        tail = temp; 
    }
}

void printLinkedList (){
    printf("Linked List :\n");

    Node *curr = head; // curr adalah index yang akan berjalan

    while (curr){ // selama curr tidak sama dengan NULL
        printf("%s\n", curr->username);
        curr = curr->next; // Update curr nya ke next
    }
}

// FUNCTION UNTUK FRIENDS MANAGEMENT
void AddFriend (Node *user){
    Node *temp = head;
    int no = 1;
    printf ("\n[All User]\nNo. Username\n");
    while (temp){
        if (strcmp(temp->username, user->username)!=0){
            printf ("%d   %s\n", no, temp->username);
            no++;
        }
        temp = temp->next;
    }
    puts ("");
    char newfriend [255];
    printf("Which user do you want to add?\n>>");
    scanf ("%s", &newfriend);getchar ();
    
    int flag=1;
    Node *curr = head;
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
    if (flag){
        printf ("\n--There is no %s in User List\n", newfriend);
    }
    printf("Press enter to continue!\n");
}

void viewInbox (Node *user){
    
    printf ("\n[All Friend Request of %s]\n", user->username);
    printf ("No. Userame\n");
    for (int i=0; i < user->totalInbox; i++){
        if (user->inbox[i]->username!= NULL) printf("%d   %s\n", i+1, user->inbox[i]->username);
    }
    printf ("\nWhich user do you want to be accepted?\n>>");
    char temp[255];
    scanf("%[^\n]", &temp); getchar();
    int flag =1;
    for (int i=0; i< user->totalInbox; i++){
        if (strcmp (temp, user->inbox[i]->username)==0){
            user->friends[user->totalfriends] = user->inbox[i];
            user->inbox[i]->friends[user->inbox[i]->totalfriends] = user;
            user->totalfriends++;
            printf ("\n--You accepted the request from %s--\n", user->inbox[i]->username);
            flag = 0;
            user->inbox[i]->totalfriends++;user->inbox[i] = NULL;
            user->inbox[i] = NULL;
            break;
        }
    }
    if (flag){
        printf ("\n--There is no %s in your Friend Request\n", temp);
    }
    printf ("Press enter to continue!\n");
}

void viewSentRequest (Node *user){

    printf ("\n[Your Sent Request]\n");
    if(user->totalSentRequest==0){
        printf ("No Name\n");
    } 
    else {
        printf ("No. Username\n");
        for (int i=0; i< user->totalSentRequest; i++){
            printf ("%d   %s\n", i+1, user->request[i]->username);
        }
    }
}

int main (){
    // cuma bikin data nya aja
    pushTail ("romario");
    pushTail ("roland");
    pushTail ("lucky");
    pushTail ("codewiz");
    printLinkedList ();

//  cuma untuk tau log in as ... (Contoh doang)
    printf ("log in as : ");
    char temp[100];
    scanf("%s", &temp);  getchar ();
    Node *user = head;
    while (user){
        if (strcmp (temp, user->username)==0){
            break;
        }
        user= user->next;
    }

//  cuma ngetes functionnya
    AddFriend (user);
    AddFriend (user);
    AddFriend (user);
    viewSentRequest (user);

//  cuma coba log in as ... user 2
    printf ("\nlog in as : ");
    scanf("%s", &temp);  getchar ();
    Node *user2 = head;
    while (user2){
        if (strcmp (temp, user2->username)==0){
            break;
        }
        user2= user2->next;
    }

//  coba cek inbox nya user 2
    viewInbox (user2);


//  coba ngetes print friendlist 1 ama 2
    for (int i=0; i<user2->totalfriends; i++){
        printf ("temen %s : %s\n", user2->username, user2->friends[i]->username);
    }

    for (int i=0; i<user->totalfriends; i++){
        printf ("temen %s : %s\n",user->username, user->friends[i]->username);
    }
    return 0;
}