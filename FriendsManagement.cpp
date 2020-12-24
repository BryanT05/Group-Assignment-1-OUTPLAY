#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char username [255];
    Node *next;
    Node *prev;

    int totalfriends;
    Node *friends[100];

    int totalInbox;
    Node *inbox[100];

    int totalSentRequest;
    Node *request[100];
} *head, *tail; 

Node *createNode (const char name[]){
    Node *temp = (Node*) malloc (sizeof(Node));

    strcpy (temp ->username, name);
    temp -> totalfriends = 0;
    temp -> totalInbox = 0;
    temp -> totalSentRequest = 0;
    temp-> friends[0] = NULL;
    temp -> inbox[0]= NULL;
    temp ->request[0] =NULL;

    temp-> next = temp->prev = NULL;
    return temp;
}

void pushHead (const char name[]){
    Node *temp = createNode (name); 

    if (!head){ 
        head = tail = temp;
    }
    else { 
        temp->next =  head;
        head->prev = temp;
        head = temp;
    }
}

void pushTail (const char name[]){
    Node *temp = createNode (name);

    if (!head){ 
        head= tail = temp;
    }
    else { 
        temp->prev = tail;
        tail->next = temp;
        tail =  temp;
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
void AddFriend (const char temp2[]){
    Node *user = head;
    while (user){
        if (strcmp (temp2, user->username)==0){
            break;
        }
        user= user->next;
    }

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

void viewInbox (const char temp2[]){
    Node *user = head;
    while (user){
        if (strcmp (temp2, user->username)==0){
            break;
        }
        user= user->next;
    }


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
            user->inbox[i]->totalfriends++;
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
}

void viewSentRequest (const char temp2[]){
    Node *user = head;
    while (user){
        if (strcmp (temp2, user->username)==0){
            break;
        }
        user= user->next;
    }

    printf ("\n[%s's Sent Request]\n", user->username);
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

void printFriends (const char temp2[]){
    Node *user = head;
    while (user){
        if (strcmp (temp2, user->username)==0){
            break;
        }
        user= user->next;
    }
    printf ("\n[All Friends of %s]\nNo. Username\n", user->username);
    if (user->totalfriends==0){
        printf ("None\n");
    }
    else {
        for (int i=0; i<user->totalfriends; i++){
            printf ("%d   %s\n", i+1, user->friends[i]->username);
        }
    }
}

void removeFriend (const char temp2[]){
    Node *user = head;
    while (user){
        if (strcmp (temp2, user->username)==0){
            break;
        }
        user= user->next;
    }
    printFriends(user->username);
    printf ("\nWhich user do you want to remove?\n>>");
    char temp [255];
    int flag=1;
    scanf ("%[^\n]", &temp); getchar ();
    for (int i=0; i<user->totalfriends; i++){
        if (strcmp(temp, user->friends[i]->username)==0){
            flag=0;
            for (int j=i; j<user->totalfriends-1; j++){
                user->friends[j]=user->friends[j+1];
            }
            user->friends[user->totalfriends-1]=NULL;
            user->totalfriends--;
            printf ("\n-- You are no longer friends with %s --\n", temp);
            break; 
        }
    }
    if (flag) printf ("\nThere is no %s in your Firend List\n", temp);
    printf("Press enter to continue!\n");
}


int main (){
    // cuma bikin data nya aja
    pushTail ("romario");
    pushTail ("roland");
    pushTail ("lucky");
    pushTail ("codewiz");
    printLinkedList ();

//  ABAIKAN INI!!!!!!!!!!!!!!!!
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
    // disini, user sebagai yang sedang Log In, PASSING PARAMETER nya adalah const char dari username yang lagi log in (user1->username)
    AddFriend (user->username);
    AddFriend (user->username);
    AddFriend (user->username);
    viewSentRequest (user->username);

//  ABAIKAN INI!!!!!!!!!!!!!!!!!!!!!
    printf ("\nlog in as : ");
    scanf("%s", &temp);  getchar ();
    Node *user2 = head;
    while (user2){
        if (strcmp (temp, user2->username)==0){
            break;
        }
        user2= user2->next;
    }
    //  untuk cek inbox nya user 2, PASSING PARAMETER nya adalah const char dari username yang lagi log in (user2->username)
    viewInbox (user2->username);
    viewSentRequest (user->username);
    AddFriend (user2->username);

    // ABAIKAN INI!!!!!!!!!!!!!!
    printf ("\nlog in as : ");
    scanf("%s", &temp);  getchar ();
    Node *user3 = head;
    while (user3){
        if (strcmp (temp, user3->username)==0){
            break;
        }
        user3= user3->next;
    }

    viewInbox (user3->username);
    viewSentRequest (user->username);
    viewInbox (user3->username);
    viewSentRequest (user2->username);
    
    

//  coba ngetes print friendlist 3 sebelum remove
    printFriends (user3->username);

    removeFriend (user3->username);
//  coba ngetes print friendlist 3 setelah remove friend
    printf ("Setelah remvoe Friend:\n");
    printFriends (user3->username);
    
    return 0;
}