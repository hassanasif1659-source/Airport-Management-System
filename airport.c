//hassan bin asif
#include<stdio.h>
#include<string.h>
int login()
{
    int pin = 320;
    int pass;
    int attempt = 0;

    do {
        printf("Enter PIN: ");
        scanf("%d", &pass);
        attempt++;

        if (pass != pin)
            printf("Wrong PIN! Attempts left: %d\n", 3 - attempt);

    } while (pin != pass && attempt < 3);

    if (pin == pass)
    {
        printf("Login successful!\n");
        return 1;
    }

    printf("Limit reached! Access denied.\n");
    return 0;
}

//Hassan Zakai in

int flightids[100];
char destinations[100][50];
char flightdates[100][20];
float flightfares[100];
int flighttypes[100];
int fcount=0;
int nextflightid=101;
void addflight(){
    printf("\n---Add New Flight---\n");
    flightids[fcount]= nextflightid;

    printf("Enter Destination: ");
    scanf("%s", destinations[fcount]);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", flightdates[fcount]);

    do {
        printf("Enter Fare: ");
        scanf("%f", &flightfares[fcount]);
        if(flightfares[fcount] <= 0)
            printf("Fare must be positive. Please try again.\n");
} while (flightfares[fcount] <= 0);


    do{
        printf("Enter Type (1 for Domestic / 2 for International): ");
        scanf("%d",&flighttypes[fcount]);
        if(flighttypes[fcount] != 1 && flighttypes[fcount] != 2)
            printf("Invalid type. Please enter 1 for Domestic or 2 for International.\n");
    } while (flighttypes[fcount] != 1 && flighttypes[fcount] != 2);
    nextflightid++;
    fcount++;

    printf("\nFlight added successfully with ID: %d!\n", flightids[fcount - 1]);

}
void viewflights(){
    printf("\n--- View Flights ---\n");
    if(fcount == 0) {
        printf("No flights available.\n");
        return;
     }
     printf("-------------------------------------------------------------------\n");
    printf("%-10s %-20s %-15s %-10s %-15s\n", "ID", "Destination", "Date", "Fare", "Type");
    printf("-------------------------------------------------------------------\n");

    for(int i=0; i<fcount; i++){
        char typestr[15];
        if(flighttypes[i] == 1)
            strcpy(typestr, "Domestic");
        else
            strcpy(typestr, "International");

            printf("%-10d %-20s %-15s %-10.2f %-15s\n", flightids[i], destinations[i], flightdates[i], flightfares[i], typestr);
    }
    printf("-------------------------------------------------------------------\n");
}

void flightmenu(){
    int choice;
    do{
        printf("\n--- Flight Management Menu ---\n");
        printf("1. Add Flight\n2. View Flights\n0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: addflight(); break;
            case 2: viewflights(); break;
            case 0: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
}
//Hassan Zakai out

// Ahmed Day 1 start
int paxID[100];
char paxName[100][50];
int paxAge[100];
char paxCnic[100][20];
int pCount = 0, nextPaxId = 1001;

void addPassenger()
{
    if (pCount >= 100)
    {
        printf("Passenger limit reached!\n");
        return;
    }

    printf("\n--- Add Passenger ---\n");

    paxID[pCount] = nextPaxId;

    printf("Enter Name: ");
    scanf(" %49[^\n]", paxName[pCount]);

    printf("Enter CNIC: ");
    scanf("%19s", paxCnic[pCount]);

    do
    {
        printf("Enter Age: ");
        scanf("%d", &paxAge[pCount]);

        if (paxAge[pCount] < 1 || paxAge[pCount] > 120)
            printf("Invalid age! Please enter age between 1 and 120.\n");

    } while (paxAge[pCount] < 1 || paxAge[pCount] > 120);

    printf("\nPassenger added successfully! ID: %d\n", paxID[pCount]);

    pCount = pCount + 1;
    nextPaxId = nextPaxId + 1;
}

void viewPassengers()
{
    printf("\n--- View Passengers ---\n");

    if (pCount == 0)
    {
        printf("No passengers yet.\n");
        return  ;
    }

    printf("---------------------------------------------------------------\n");
    printf("%-10s %-25s %-20s %-10s\n", "ID", "Name", "CNIC", "Age");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < pCount; i++)
    {
        printf("%-10d %-25s %-20s %-10d\n",
               paxID[i], paxName[i], paxCnic[i], paxAge[i]);
    }

    printf("---------------------------------------------------------------\n");
}

void passengerMenu()
{
    int choice;

    do
    {
        printf("\n--- Passenger Management Menu ---\n");
        printf("1. Add Passenger\n");
        printf("2. View Passengers\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPassenger();
                break;
            case 2:
                viewPassengers();
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}
// Ahmed Day 1 end


//Hassan Asif Day 2 start
void saveCounters(){
    FILE *fp;
    fp = fopen("counters.txt", "w");
    if(fp==NULL){
        printf("Error Saving File ! \n");
        return ; 
    }
    fprintf(fp, "%d %d", nextflightid, nextPaxId);
    fclose(fp);
}
void loadcounters(){
    FILE *fp ;
    fp = fopen("counters.txt", "r");
    if(fp==NULL){
        return ; 
    }
    fscanf(fp , "%d %d" ,&nextflightid , &nextPaxId);
    fclose(fp);
}
//Hassan Asif Day 2 completed

void showmenu(){
    printf("====MAIN MENU====\n");
    printf("1. Manage Flights\n2. Manage Passengers\n3. Book Ticket\n4. Cancel Booking\n5. Seat Allocation\n6. Search\n7. Report\n8. Packages & Categories\n0. Exit\n");
    }
int main(){
int choice ;

    printf("Welcome to Airport Management System\n");

    if (login() == 0)
        return 0;
            loadcounters();
    do{

        showmenu();
        printf("Enter choice: ");
         scanf("%d", &choice);
        switch(choice)
            {
                case 1: flightmenu(); saveCounters(); break; //Hassan Zakai
                case 2: passengerMenu(); saveCounters(); break; // Ahmed Day 1
                case 3: printf("Book Ticket - coming soon\n"); break;
                case 4: printf("Cancel Booking - coming soon\n"); break;
                case 5: printf("Seat Allocation - coming soon\n"); break;
                case 6: printf("Search - coming soon\n"); break;
                case 7: printf("Report - coming soon\n"); break;
                case 8: printf("Packages - coming soon\n"); break;
                case 0: saveCounters(); printf("Goodbye!\n"); break;
                default: printf("Wrong choice!\n");
    }
        } while(choice != 0);
        
        return 0;
    }
    //hassan bin asif