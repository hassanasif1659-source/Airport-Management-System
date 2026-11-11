// hassan bin asif
#include <stdio.h>
#include <string.h>
int login()
{
    int pin = 320;
    int pass;
    int attempt = 0;

    do
    {
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

// Hassan Zakai Day 1

int flightids[100];
char destinations[100][50];
char flightdates[100][20];
float flightfares[100];
int flighttypes[100];
int fcount = 0;
int nextflightid = 101;
int seats[100][10][4];

void addflight()
{
    printf("\n---Add New Flight---\n");
    flightids[fcount] = nextflightid;

    printf("Enter Destination: ");
    scanf(" %[^\n]", destinations[fcount]);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", flightdates[fcount]);

    do
    {
        printf("Enter Fare: ");
        scanf("%f", &flightfares[fcount]);
        if (flightfares[fcount] <= 0)
            printf("Fare must be positive. Please try again.\n");
    } while (flightfares[fcount] <= 0);

    do
    {
        printf("Enter Type (1 for Domestic / 2 for International): ");
        scanf("%d", &flighttypes[fcount]);
        if (flighttypes[fcount] != 1 && flighttypes[fcount] != 2)
            printf("Invalid type. Please enter 1 for Domestic or 2 for International.\n");
    } while (flighttypes[fcount] != 1 && flighttypes[fcount] != 2);
   
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 4; col++){
            seats[fcount][row][col] = 0;
        }
    }

    nextflightid++;
    fcount++;

    printf("\nFlight added successfully with ID: %d!\n", flightids[fcount - 1]);

}
void viewflights()
{
    printf("\n--- View Flights ---\n");
    if (fcount == 0)
    {
        printf("No flights available.\n");
        return;
    }
    printf("%-10s %-20s %-15s %-10s %-15s\n", "ID", "Destination", "Date", "Fare", "Type");


    for (int i = 0; i < fcount; i++)
    {
        char typestr[15];
        if (flighttypes[i] == 1)
            strcpy(typestr, "Domestic");
        else
            strcpy(typestr, "International");

        printf("%-10d %-20s %-15s %-10.2f %-15s\n", flightids[i], destinations[i], flightdates[i], flightfares[i], typestr);
    }
}
// Hassan Zakai Day 2 start
int findflight(int id)
{

    for (int i = 0; i < fcount; i++)
    {
        if (flightids[i] == id)
            return i;
    }
    return -1;
}

void updateflight()
{
    int id, i;
    printf("\n--- Update Flight Details ---\n");
    printf("Enter Flight ID to Update: ");
    scanf("%d", &id);
    i = findflight(id);
    if (i == -1)
    {
        printf("Flight with ID %d not found!\n", id);
        return;
    }
    printf("Enter New Destination: ");
    scanf(" %[^\n]", destinations[i]);

    printf("Enter New Date (DD-MM-YYYY): ");
    scanf(" %[^\n]", flightdates[i]);

    do
    {
        printf("Enter New Fare: ");
        scanf("%f", &flightfares[i]);
        if (flightfares[i] <= 0)
        {
            printf("Fare must be positive. Please try again.\n");
        }
    } while (flightfares[i] <= 0);

    do
    {
        printf("Enter New Type (1 = Domestic, 2 = International): ");
        scanf("%d", &flighttypes[i]);
        if (flighttypes[i] != 1 && flighttypes[i] != 2)
        {
            printf("Invalid type. Please enter 1 for Domestic or 2 for International.\n");
        }
    } while (flighttypes[i] != 1 && flighttypes[i] != 2);

    printf("\nFlight Updated Successfully!\n");
}

void deleteflight()
{
    int id, i, j;
    printf("\n--- Delete Flight ---\n");
    printf("Enter Flight ID to delete: ");
    scanf("%d", &id);
    i = findflight(id);
    if (i == -1)
    {
        printf("Flight Not Found!\n");
        return;
    }
    for (j = i; j < fcount - 1; j++)
    {
        flightids[j] = flightids[j + 1];
        strcpy(destinations[j], destinations[j + 1]);
        strcpy(flightdates[j], flightdates[j + 1]);
        flightfares[j] = flightfares[j + 1];
        flighttypes[j] = flighttypes[j + 1];
        // Shift the seat map structures down by one row index
        for(int row = 0; row < 10; row++){
            for(int col = 0; col < 4; col++){
                seats[j][row][col] = seats[j + 1][row][col];
            }
        }
    }
    fcount--;
    printf("Flight deleted successfully!\n");
}
// Hassan Zakai Day 2 End

// Hassan Zakai Day 3 Start
int countfreeseats(int f) //counts free seats
{
    int counter = 0;
    for(int row=0;row<10;row++){
        for(int col=0;col<4;col++){
            if(seats[f][row][col]==0){
                counter++;
            }
        }
    }
    return counter;
}

void seatmap(int f){
    printf("--- Seat Map for Flight ID: %d ---\n", flightids[f]);
    printf("    A   B   C   D\n");

    for(int row = 0; row < 10; row++){
        printf("Row %d: ", row + 1);
        for(int col = 0; col < 4; col++){
            if(seats[f][row][col] == 0){
                printf("[ ] "); //free
            } else {
                printf("[X] "); //booked
            }
        }
        printf("\n");
    }
    printf("Total Free Seats: %d / 40\n", countfreeseats(f));
}

void allocateseat(int f, int *row, int *col){

    int r;
    char c;
    seatmap(f);

    while(1){
        printf("\nEnter Row (1-10): ");
        scanf("%d", &r);
        printf("\nEnter Seats (A-D): ");
        scanf(" %c", &c);

        if(c >= 'a' && c <= 'z'){
            c = c - 32; //converts lowercase to uppercase
        }
        if(r < 1 || r > 10 || c < 'A' || c > 'D') {
            printf("Seat Does not Exist. Please select between Row (1 - 10) And Seat (A - D).\n");
            continue;
        }
        if(seats[f][r-1][c-'A'] == 1){
            printf("Seat Already Booked. Please select another seat.\n");
            continue;
        }
        break;
    }  
    seats[f][r-1][c-'A'] = 1;

    *row = r-1;
    *col = c-'A';

    printf("Seat %d%c allocated successfully!\n",r,c);
}

void seatmenu(){
    int choice;
    do{
        printf("\n--- Seat Management Menu ---\n");
        printf("1. View Seat Map\n");
        printf("2. Book a Seat (Test Mode)\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            case 2: {
                int id, f;
                printf("Enter Flight ID: ");
                scanf("%d", &id);
                f = findflight(id);
                if(f == -1){
                    printf("Flight Not Found!\n");
                    break;
                }
                if(choice == 1){
                    seatmap(f);
                }
                else{
                    int assignedrow, assignedcol;
                    allocateseat(f,&assignedrow,&assignedcol);
                }
                break;
            }
            case 0:
                printf("Returning to Main Menu...\n");
                break;
                default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 0);
    }
//Hassan Zakai Day 3 End
void flightmenu()
{
    int choice;
    do
    {
        printf("\n--- Flight Management Menu ---\n");
        printf("1. Add Flight\n2. View Flights\n3. Update Flight\n4. Delete Flight\n0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addflight();
            break;
        case 2:
            viewflights();
            break;
        case 3:
            updateflight();
            break;
        case 4:
            deleteflight();
            break;
        case 0:
            printf("Returning to Main Menu...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);
}
// Hassan Zakai Day 1 end

// Ahmed Day 1 start
int paxID[100];
char paxName[100][50];
int paxAge[100];
char paxCnic[100][20];
int pCount = 0, nextPaxId = 1001;

char catName[4][20] = {"Child", "Student", "Adult", "Senior Citizen"}; // Day 2 variables
int getCategory(int age); // Day 2 variables

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

    // printf("\nPassenger added successfully! ID: %d\n", paxID[pCount]);
    printf("\nPassenger added successfully! ID: %d | Category: %s\n",paxID[pCount], catName[getCategory(paxAge[pCount])]); // Modified the above line on day 2
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

    printf("-----------------------------------------------------------------------------------\n");
    // printf("%-10s %-25s %-20s %-10s\n", "ID", "Name", "CNIC", "Age");
    printf("%-10s %-25s %-20s %-10s %-20s\n", "ID", "Name", "CNIC", "Age", "Category"); // Modified the above line on day 2
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < pCount; i++)
    {
        // printf("%-10d %-25s %-20s %-10d\n",paxID[i], paxName[i], paxCnic[i], paxAge[i]);
        printf("%-10d %-25s %-20s %-10d %-20s\n", 
       paxID[i], paxName[i], paxCnic[i], paxAge[i],
       catName[getCategory(paxAge[i])]); // Modified the above printf line on day 2
    }

    printf("-----------------------------------------------------------------------------------\n");
}
// Ahmed Day 2 Start
int getCategory(int age)
{
    if (age < 12)
        return 0;
    else if (age <= 25)
        return 1;
    else if (age <= 59)
        return 2;
    else
        return 3;
}

int findPassenger(int id)
{
    for (int i = 0; i < pCount; i++)
    {
        if (paxID[i] == id)
            return i;
    }

    return -1;
}

void updatePassenger()
{
    int id, i;

    printf("\n--- Update Passenger ---\n");
    printf("Enter Passenger ID: ");
    scanf("%d", &id);

    i = findPassenger(id);

    if (i == -1)
    {
        printf("Passenger not found!\n");
        return;
    }

    printf("Enter New Name: ");
    scanf(" %49[^\n]", paxName[i]);

    printf("Enter New CNIC: ");
    scanf("%19s", paxCnic[i]);

    do
    {
        printf("Enter New Age: ");
        scanf("%d", &paxAge[i]);

        if (paxAge[i] < 1 || paxAge[i] > 120)
            printf("Invalid age! Please enter age between 1 and 120.\n");

    } while (paxAge[i] < 1 || paxAge[i] > 120);

    printf("\nPassenger updated successfully!\n");
    printf("New Category: %s\n", catName[getCategory(paxAge[i])]);
}
// Ahmed Day 2 End

// Ahmed Day 3 Start
char pkgName[4][15] = {"", "Economy", "Business", "First Class"};
int pkgMulti[4] = {0, 1, 2, 3};
int pkgBaggage[4] = {0, 0, 10, 20};
int catDiscount[4] = {50, 10, 0, 15};

int choosePackage()
{
    int pkg;

    printf("\n--- Available Packages ---\n");

    for (int i = 1; i <= 3; i++)
    {
        printf("%d. %s | Fare x%d | Baggage: %d kg\n",
               i, pkgName[i], pkgMulti[i], 20 + pkgBaggage[i]);
    }

    do
    {
        printf("Enter package (1-3): ");
        scanf("%d", &pkg);

        if (pkg < 1 || pkg > 3)
            printf("Invalid package!\n");

    } while (pkg < 1 || pkg > 3);

    return pkg;
}

void calculateFare(float base, int pkg, int age, float *discount, float *finalFare)
{
    float packageFare;
    int category;

    packageFare = base * pkgMulti[pkg];

    category = getCategory(age);

    *discount = packageFare * catDiscount[category] / 100;

    *finalFare = packageFare - *discount;
}

void showPackages()
{
    printf("\n========== TRAVEL PACKAGES ==========\n");

    for (int i = 1; i <= 3; i++)
    {
        printf("%d. %s | Fare x%d | Baggage Limit: %d kg\n",
               i, pkgName[i], pkgMulti[i], 20 + pkgBaggage[i]);
    }

    printf("\n========== AGE CATEGORIES ==========\n");

    for (int i = 0; i < 4; i++)
    {
        printf("%s | Discount: %d%%\n", catName[i], catDiscount[i]);
    }

    printf("\nExcess baggage: Rs 500/kg Domestic, Rs 1000/kg International\n");

    // Temporary Fare Test

    float base, discount, finalFare;
    int age, pkg;

    printf("\n========== FARE CALCULATOR ==========\n");

    printf("Enter Base Fare: ");
    scanf("%f", &base);

    printf("Enter Age: ");
    scanf("%d", &age);

    pkg = choosePackage();

    calculateFare(base, pkg, age, &discount, &finalFare);

    printf("\nDiscount: Rs %.2f\n", discount);
    printf("Final Fare: Rs %.2f\n", finalFare);
}
// Ahmed Day 3 End
void passengerMenu()
{
    int choice;

    do
    {
        printf("\n--- Passenger Management Menu ---\n");
        printf("1. Add Passenger\n");
        printf("2. View Passengers\n");
        printf("3. Update Passenger\n");
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
            case 3:
                updatePassenger();
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
//I add two functions savecounters and loadcounters which save the ids in file .

int nextbookingID = 5001 ;


void saveCounters(){
    FILE *fp;
    fp = fopen("counters.txt", "w");
    if(fp==NULL){
        printf("Error Saving File ! \n");
        return ; 
    }
    fprintf(fp, "%d %d %d", nextflightid, nextPaxId,nextbookingID);
    fclose(fp);
}
void loadcounters(){
    FILE *fp ;
    fp = fopen("counters.txt", "r");
    if(fp==NULL){
        return ; 
    }
    fscanf(fp , "%d %d %d" ,&nextflightid , &nextPaxId,&nextbookingID);
    fclose(fp);
}
//I add two functions savecounters and loadcounters which save the ids in file .
//Hassan Asif Day 2 completed

//Hassan Asif Day 3 start
int bookingId[200];
int bookingpax[200];
int bookingflight[200];
float bookingfare[200];
int bookingstatus[200];
int bcount = 0;

//Hassan Asif Day 4 start
int bookingpkg[200];
int bookingrow[200];
int bookingcol[200];
float bookingdiscount[200];
float bookingweight[200];
float bookingfee[200];
float bookingtotal[200];

void printReceipt(int b)
{
    int p = findPassenger(bookingpax[b]);
    int f = findflight(bookingflight[b]);

    printf("\n========== TICKET RECEIPT ==========\n");
    printf("Booking ID   : %d\n", bookingId[b]);
    printf("Passenger    : %s\n", paxName[p]);
    printf("Category     : %s\n", catName[getCategory(paxAge[p])]);
    printf("Flight       : %d to %s\n", bookingflight[b], destinations[f]);
    printf("Date         : %s\n", flightdates[f]);
    printf("Package      : %s\n", pkgName[bookingpkg[b]]);
    printf("Seat         : %d%c\n", bookingrow[b] + 1, 'A' + bookingcol[b]);
    printf("Discount     : Rs %.2f\n", bookingdiscount[b]);
    printf("Ticket Price : Rs %.2f\n", bookingfare[b]);
    printf("Baggage      : %.1f kg (Limit %d kg)\n", bookingweight[b], 20 + pkgBaggage[bookingpkg[b]]);
    printf("Excess Fee   : Rs %.2f\n", bookingfee[b]);
    printf("TOTAL        : Rs %.2f\n", bookingtotal[b]);
    printf("Status       : %s\n", bookingstatus[b] == 1 ? "Confirmed" : "Cancelled");
    printf("--------------------------\n");
}

void bookticket(){
    int pid ;
    int fid ;
    int p;
    int f ;
    int pkg;                                      // Day 4
    float discount, fare, weight, limit, excess, fee;   // Day 4

printf("\n****Book Ticket****\n");
if(pCount==0 || fcount==0){
    printf("Add a flight & Passenger \n");
    return ;
}
printf("Enter Passenger ID: ");
scanf("%d" , &pid);
p  = findPassenger(pid);
if(p==-1){
    printf("Passenger not found!\n");
    return ;
}
printf("Passenger: %s | Age: %d | Category: %s\n", paxName[p], paxAge[p], catName[getCategory(paxAge[p])]);
// flight input
    printf("Enter Flight ID: ");
    scanf("%d" , &fid);
    f = findflight(fid);
    if(f==-1){
        printf("Flight not found!\n");
        return ;
    }
    printf("Flight: %s | Date: %s | Fare: Rs %.2f\n", destinations[f], flightdates[f], flightfares[f]);

    // Day 4: flight full check
    if(countfreeseats(f) == 0){
        printf("Flight is full!\n");
        return ;
    }

    // Day 4: package (Ahmed)
    pkg = choosePackage();

    // Day 4: fare with age discount (Ahmed) - pointers
    calculateFare(flightfares[f], pkg, paxAge[p], &discount, &fare);

    // Day 4: seat (Zakai) - pointers
    allocateseat(f, &bookingrow[bcount], &bookingcol[bcount]);

    // Day 4: baggage
    do{
        printf("Enter baggage weight (kg): ");
        scanf("%f", &weight);
        if(weight < 0)
            printf("Weight cannot be negative!\n");
    } while(weight < 0);

    limit = 20 + pkgBaggage[pkg];
    excess = (weight > limit) ? weight - limit : 0;
    fee = excess * ((flighttypes[f] == 1) ? 500 : 1000);
    printf("Limit %.0f kg | Excess %.1f kg | Fee Rs %.2f\n", limit, excess, fee);

    // booking save karo
    bookingId[bcount] = nextbookingID;
    bookingpax[bcount] = pid;
    bookingflight[bcount] = fid;
    bookingfare[bcount] = fare;
    bookingstatus[bcount] = 1;
    bookingpkg[bcount] = pkg;
    bookingdiscount[bcount] = discount;
    bookingweight[bcount] = weight;
    bookingfee[bcount] = fee;
    bookingtotal[bcount] = fare + fee;

    // receipt print karo
    printReceipt(bcount);

    nextbookingID++;
    bcount++;
}
//Hassan Asif Day 4 end

//Hassan Asif Day 3 end

void showmenu()
{
    printf("====MAIN MENU====\n");
    printf("1. Manage Flights\n2. Manage Passengers\n3. Book Ticket\n4. Cancel Booking\n5. Seat Allocation\n6. Search\n7. Report\n8. Packages & Categories\n0. Exit\n");
}
int main()
{
    int choice;

    printf("Welcome to Airport Management System\n");

    if (login() == 0)
        return 0;
    loadcounters();
    do
    {

        showmenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            flightmenu();
            saveCounters();
            break; // Hassan Zakai Day 1
        case 2:
            passengerMenu();
            saveCounters();
            break; // Ahmed Day 1
        case 3:
            bookticket();
            saveCounters();
            break; // Hassan Asif Day 3
        case 4:
            printf("Cancel Booking - coming soon\n");
            break;
        case 5:
            seatmenu();
            break; // Hassan Zakai Day 3
        case 6:
            printf("Search - coming soon\n");
            break;
        case 7:
            printf("Report - coming soon\n");
            break;
        case 8:
            showPackages();
            break; // Ahmed Day 3
        case 0:
            saveCounters();
            printf("Goodbye!\n");
            break;
        default:
            printf("Wrong choice!\n");
        }
    } while (choice != 0);

    return 0;
}
// hassan bin asif