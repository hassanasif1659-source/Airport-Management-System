//hassan bin asif
#include <stdio.h>

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
void showmenu(){
    printf("====MAIN MENU====\n");
    printf("1. Manage Flights\n2. Manage Passengers\n3. Book Ticket\n4. Cancel Booking\n5. Seat Allocation\n6. Search\n7. Report\n8. Packages & Categories\n0. Exit\ngy");
    }
int main(){
int choice ;

    printf("Welcome to Airport Management System\n");

    if (login() == 0)
        return 0;

    showmenu();
    printf("Enter choice: ");
     scanf("%d", &choice);
    switch(choice)
        {
            case 1: printf("Flights - coming soon\n"); break;
            case 2: printf("Passengers - coming soon\n"); break;
            case 3: printf("Book Ticket - coming soon\n"); break;
            case 4: printf("Cancel Booking - coming soon\n"); break;
            case 5: printf("Seat Allocation - coming soon\n"); break;
            case 6: printf("Search - coming soon\n"); break;
            case 7: printf("Report - coming soon\n"); break;
            case 8: printf("Packages - coming soon\n"); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Wrong choice!\n");
        }while(choice != 0);
    }
    //hassan bin asif