#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Method Declaration

void enter_name();
void find_name();
void find_room();
void checkout_guest();
void view_bookings();

//Instance Field Declaration
FILE* view;
FILE *fp;
FILE* enter;
char admin_entry[20] = {'y'};
char user_entry[20] = {'y'};

//structure defined to store name, room, rent service and payment system required
struct hotel
{
    char name[20];
    char room[20];
    char payment[5];
    char rent[4];
}h;

//main method
int main(){

    int a,b,c;

     //Welcome screen

system("COLOR  70");

	printf(" \t\t  ******************************************\t\n");
	printf(" \t\t\t  Welcome To Our Hotel \t\t\n");
	printf(" \t\t\t Thanks For Choosing  Our Hotel    \n");
	printf(" \t\t  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\t\n");
	printf(" \t\t   \n");

	printf("\t\t\t\n\n           Login page               \n\n");


    printf("\n\t\t\t Enter -1 For ADMIN access -  \t");
    printf("\n\t\t\t Enter -2 For USER access  -  \t");
     scanf("%d",&a);


        switch(a){
            case 1:{
                char pass[10];
                char filepass[10];
                int i;

                FILE *passw;
                passw = fopen("pass.txt","r");

                //admins password prompt
                printf("\nPlease enter the password to continue - ");



                for(i=0; i<6; i++){
                    scanf("%s",pass);
                    fscanf(passw,"%s",filepass);
                    if (strcmp(filepass,pass) == 0) {
                        printf("\n\nAccess granted!\n");
                        fclose(passw);
                        break;

                    }
                    else{
                     printf("\nIncorrect password, please try again.");
                     printf("\nYou have %d trys left ",5-i-1);
                     printf("\n\nEnter password >> ");
                    }
                    if(i==4){
                        fclose(passw);
                        return 0;
                    }
                }

                 //re-entry if
                while(admin_entry[0] =='y'){
                printf("\n\t Enter -1 To ENTER new guest - \t\n");
                 printf("\n\t Enter -2 To VIEW booked guests details - \n");
   	            printf("\n\t Enter -3 To FIND room number of existing guest - \n");
                printf("\n\t Enter -4 To FIND guest of occupied room - \n");
                printf("\n\t Enter -5 To Edit - \n");
                printf("\n\t Enter -6 To Delete  - \n");
                printf("\n\t Enter -7 Exit  - \n");
                printf(">> ");
                scanf("%d",&b);

                switch(b){

                    case 1:{
                        enter_name();
                         break;
                    }
                    {
                case 2:
                        view_bookings();
                        break;
                     }
                    case 3:{
                        find_name();
                        break;
                    }
                    case 4:{
                        find_room();
                        break;
                    }
                    case 5:{
                        edit();
                        break;
                    }
                    case 6:{
                        delete();
                        break;
                        }
                    case 7:{
                        exit(0);
                    }
                    default:{
                        printf("\n Wrong entry!");
                    }
                }
                //enter again?
                printf("Would you like to continue? (y/n)\n");
                scanf("%s",admin_entry);

                }
                if(strcmp(admin_entry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\n >Exited<\n\n");

                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting...\n");
                    return 0;
                }
                break;
            }

            case 2:{
                while(user_entry[0] =='y'){
                printf("\n\t Enter - 1 View available rooms -  \n");
   	            printf("\n\t Enter - 2  Booking of room -  \n");
                printf("\n\t Enter - 3  Special event service -  \n");
   	            printf("\n\t Enter - 4 About us  -  \n");
   	            printf("\n\t Enter - 5 Exit  -  \n");
                scanf("%d",&c);
                switch(c){
                    case 1:{
                        FILE* view;
                        view = fopen("rooms.txt","r");
                        printf("Available rooms are:\n");
                        while(fscanf(view,"%s",h.room) != -1){
                        printf("%s \n",h.room);
                        }
                        fclose(view);
                        break;
                    }

                    case 2:{
                        enter_name();
                        break;
                    }
                    case 3:{
                        printf("Special Events:\n");

                        FILE * fp = fopen("special_events.txt", "r");
                        char ch;

                        while(fscanf(fp, "%c", &ch) != -1)
                            printf("%c", ch);

                        printf("\n");

                        fclose(fp);

                        break;
                    }
                    case 4:{
                        printf("About Hotel:\n");

                        FILE * fp = fopen("about_hotel.txt", "r");
                        char ch;

                        while(fscanf(fp, "%c", &ch) != -1)
                            printf("%c", ch);

                        printf("\n");

                        fclose(fp);

                        break;
                    }
                    case 5:{
                        exit(0);
                    }
                }

                printf("Would you like to continue? (y/n)\n");
                scanf("%s",user_entry);

                }
                if(strcmp(user_entry,"n") == 0){
                    printf("Exiting\n");
                    printf("\n >Exited<\n\n");

                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting\n");
                    return 0;
                }
                break;
            }
        }
}

void delete(){
    FILE * fp = fopen("hotelnew.txt", "r");
    int i, j, sl_no;

    if(!fp){
        printf("Something went wrong!\n");
        printf("Press any key to go back... ");
        getch();
        return;
    }

    struct hotel ara[1000];

    i = 0;
    while(fscanf(fp, "%s %s %s %s", ara[i].name, ara[i].room, ara[i].rent, ara[i].payment) != -1)
        ++i;

    printf("SL No and details:\n");
    for(int j = 0; j < i; ++j)
        printf("%d\t%s %s %s %s\n", j+1, ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    printf("\nEnter serial no to delete: ");
    scanf("%d", &sl_no);

    fclose(fp);

    fp = fopen("hotelnew.txt", "w");

    for(j = 0; j < sl_no-1; ++j)
        fprintf(fp, "%s %s %s %s\n", ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    for(j = sl_no; j < i; ++j)
        fprintf(fp, "%s %s %s %s\n", ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    fclose(fp);

    printf("Successfully deleted!\n");

    return;


}


void edit(){
    FILE * fp = fopen("hotelnew.txt", "r");
    int i, j, sl_no;

    if(!fp){
        printf("Something went wrong!\n");
        printf("Press any key to go back... ");
        getch();
        return;
    }

    struct hotel ara[1000];

    i = 0;
    while(fscanf(fp, "%s %s %s %s", ara[i].name, ara[i].room, ara[i].rent, ara[i].payment) != -1)
        ++i;

    printf("SL No and details:\n");
    for(int j = 0; j < i; ++j)
        printf("%d\t%s %s %s %s\n", j+1, ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    printf("\nEnter serial no to edit: ");
    scanf("%d", &sl_no);

    printf("Enter new name: ");
    scanf("%s", h.name);
    printf("Enter new room no: ");
    scanf("%s", h.room);
    printf("Enter new rent servces: ");
    scanf("%s", h.rent);
    printf("Payment method : ");
    scanf("%s", h.payment);

    printf("\nNew details are:\n");
    printf("%s %s %s %s\n", h.name, h.room, h.rent, h.payment);

    fclose(fp);

    fp = fopen("hotelnew.txt", "w");

    for(j = 0; j < sl_no-1; ++j)
        fprintf(fp, "%s %s %s %s\n", ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    fprintf(fp, "%s %s %s %s\n", h.name, h.room, h.rent, h.payment);

    for(j = sl_no; j < i; ++j)
        fprintf(fp, "%s %s %s %s\n", ara[j].name, ara[j].room, ara[j].rent, ara[j].payment);

    fclose(fp);

    printf("Successfully edited!\n");

    return;
}

//method declare to enter name
void enter_name(){

    FILE *tmp1;
    FILE *tmp2;

    printf("\nEnter guest name - ");
    scanf("%s",h.name);
    printf("\nEnter their room number - ");
    scanf("%s",h.room);
    printf("\nRent service (yes/no) - ");
    scanf("%s",h.rent);
    printf("\nPayment sytem (Cash/Card) - ");
    scanf("%s",h.payment);

    printf("Name: %s\tRoom: %s\tRent: %s\tPayment: %s\n", h.name, h.room, h.rent, h.payment);

    //entering guests
    fp = fopen("hotelnew.txt","a");

    if( fp == NULL){
        printf("\nFile not found");
        exit(1);
    }
    else{
        fprintf(fp,"%s %s %s %s\n",h.name,h.room,h.rent,h.payment);
        printf("\nDone\n");
    }


    fclose(fp);
}

//method defined to find quest name
void find_name(){
    char buffer[20];
    char entered_name[20];
    int guestFound =0;

    printf("\nEnter guest name to find -");
    scanf("%s",entered_name);

    fp = fopen("hotelnew.txt","r");
    while(fscanf(fp,"%s %s %s %s",h.name,h.room,h.rent, h.payment) != -1){
    if(strcmp(h.name,entered_name) == 0){
                     guestFound = 1;
                    printf("\n Guest found!");
                    printf("\n Name  is %s",h.name);
                    printf("\n Room number is %s",h.room);
                    printf("\n Rent service: %s",h.rent);
                    printf("\n Payment system: %s\n",h.payment);
      }
   }
   if(guestFound == 0){
         printf("\nGuest %s not found!\n", entered_name);
      }
   fclose(fp);
}

//method definition for guest checkout
void checkout_guest(){
    char buffer2[20];
    char checkout_name[20];
    char add_room[20];

    FILE *tmp;

    printf("Enter guest too checkout ");
    scanf("%s",checkout_name);

    fp = fopen("hotelnew.txt","r");
    tmp = fopen("tmp.txt","w");

    if(fp == NULL){
    printf("File not found");
    exit(1);
    }
	else{
        while(fscanf(fp,"%s %s %s",h.name,h.room,h.rent) != -1){
            fgetc(fp);
		    fgets(h.payment, 20, (FILE*)fp);
			    if(strcmp(h.name,checkout_name) != 0){
                    fprintf(tmp,"%s %s %s %s",h.name,h.room,h.rent,h.payment);
                }
                else{
                   strcpy(add_room,h.room);
                }
        }
        printf("Room checked out!");
    }

    fclose(fp);
    fclose(tmp);
    remove("hotelnew.txt");
    rename("tmp.txt","hotelnew.txt");

    //enter room back into available rooms list
    view = fopen("rooms.txt","a");
    printf(" add is %s",add_room);
    fprintf(view,"%s",add_room);
    fclose(view);

}

//method definition for finding rooms avalaible
void find_room(){
    char buffer[20];
    char entered_room[20];
    int roomFound =0;
    FILE *fp;
    printf("\nEnter room number to find -");
    scanf("%s",entered_room);

    fp = fopen("hotelnew.txt","r");
    while(fscanf(fp,"%s %s %s %s",h.name,h.room,h.rent, h.payment) != -1){
    if(strcmp(h.room,entered_room) == 0){
                     roomFound = 1;
                    printf("\n Room found!");
                    printf("\n Name  is %s",h.name);
                    printf("\n Room number is %s",h.room);
                    printf("\n Rent service: %s",h.rent);
                    printf("\n Payment system: %s\n",h.payment);
      }
    }
    if(roomFound == 0){
         printf("\nRoom %s not found!\n", entered_room);
      }
   fclose(fp);
}

//method defined to view bookings
void view_bookings(){

    enter = fopen("hotelnew.txt","r");

    while(fscanf(enter,"%s %s %s %s",h.name,h.room,h.rent,h.payment) != -1){
        printf("%s %s %s %s\n",h.name,h.room,h.rent,h.payment);
    }
}
