#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct User
{
    char name[50];
    char email[50];
    char phone[20];
    char password[30];
};
struct Room
{
    int roomNumber;
    char roomType[20];
    float price;
    char status[20];
};
void registerUser()
{
    struct User user;
    FILE *userFile;
    userFile = fopen("users.dat", "ab");
    if (userFile == NULL)
    {
        printf("Unable to open file!\n");
        return;
    }
    printf("\n===== User Registration =====\n");
    printf("Enter Full Name: ");
    getchar();
    gets(user.name);
    printf("Enter Email: ");
    scanf("%s", user.email);
    printf("Enter Phone Number: ");
    scanf("%s", user.phone);
    printf("Enter Password: ");
    scanf("%s", user.password);

    fwrite(&user, sizeof(struct User), 1, userFile);
    fclose(userFile);

    printf("\nRegistration Successful!\n");
}
void loginUser()
{
    struct User user;
    char email[50];
    char password[30];
    int found = 0;
    FILE *userFile;
    userFile = fopen("users.dat", "rb");
    if (userFile == NULL)
    {
        printf("\nNo registered users found!\n");
        return;
    }
    printf("\n========== USER LOGIN ==========\n");

    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    while (fread(&user, sizeof(struct User), 1, userFile) == 1)
    {
        if (strcmp(email, user.email) == 0 &&
            strcmp(password, user.password) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(userFile);
    if (found)
    {
        printf("\n==================================\n");
        printf(" Login Successful!\n");
        printf(" Welcome %s\n", user.name);
        printf("==================================\n");
        if (strcmp(user.email, "admin@gmail.com")  == 0)
        {
            adminMenu();
        }
        else
        {
            guestMenu();
        }
    }
    else
    {
        printf("\nInvalid Email or Password!\n");
    }
}
void guestMenu()
{
    int choice;
    while (1)
    {
        printf("\n=====================================\n");
        printf("         GUEST DASHBOARD\n");
        printf("=====================================\n");
        printf("1. Search Available Rooms\n");
        printf("2. Book Room\n");
        printf("3. Cancel Reservation\n");
        printf("4. View My Bookings\n");
        printf("5. Logout\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            searchAvailableRooms();
            break;
        case 2:
            printf("\nRoom Booking Module Under Development...\n");
            break;
        case 3:
            printf("\nModify/Cancel Reservation Module Under Development...\n");
            break;
        case 4:
            printf("\nBooking History Module Under Development...\n");
            break;
        case 5:
            printf("\nLogging Out...\n");
            return;
        default:
            printf("\nInvalid Choice...Please try again\n");
        }
    }
}
void adminMenu()
{
    int choice;

    while (1)
    {
        printf("\n=====================================\n");
        printf("        ADMIN DASHBOARD\n");
        printf("=====================================\n");
        printf("1. Add Room\n");
        printf("2. View Rooms\n");
        printf("3. Update Room\n");
        printf("4. Delete Room\n");
        printf("5. Logout\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRoom();
            break;
        case 2:
            viewRooms();
            break;
        case 3:
            updateRoom();
            break;
        case 4:
            deleteRoom();
            break;
        case 5:
            printf("\nLogging Out...\n");
            return;
        default:
            printf("\nInvalid Choice...Please try again\n");
        }
    }
}
void addRoom()
{
    FILE *userFile;

    struct Room room;

    userFile = fopen("rooms.dat", "ab");

    if (userFile == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\n===== ADD ROOM =====\n");

    printf("Enter Room Number: ");
    scanf("%d", &room.roomNumber);
    printf("Enter Room Type (Single/Double/Suite): ");
    scanf("%s", room.roomType);
    printf("Enter Room Price: ");
    scanf("%f", &room.price);

    strcpy(room.status, "Available");

    fwrite(&room, sizeof(struct Room), 1, userFile);

    fclose(userFile);

    printf("\nRoom Added Successfully!\n");
}
void viewRooms()
{
    FILE *userFile;

    struct Room room;

    userFile = fopen("rooms.dat", "rb");

    if (userFile == NULL)
    {
        printf("No Room Found!\n");
        return;
    }

    printf("\n===============================\n");
    printf("         ROOM LIST\n");
    printf("===============================\n");

    while (fread(&room, sizeof(struct Room), 1, userFile) == 1)
    {
        printf("\nRoom Number : %d", room.roomNumber);
        printf("\nRoom Type   : %s", room.roomType);
        printf("\nPrice       : %.2f", room.price);
        printf("\nStatus      : %s", room.status);
        printf("\n----------------------------");
    }

    fclose(userFile);
}
void updateRoom()
{
    FILE *userFile;
    struct Room room;
    int number;
    int found = 0;

    userFile = fopen("rooms.dat", "rb+");
    if (userFile == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    printf("Enter Room Number: ");
    scanf("%d", &number);

    while (fread(&room, sizeof(struct Room), 1, userFile) == 1)
    {
        if (room.roomNumber == number)
        {
            found = 1;
            printf("New Price: ");
            scanf("%f", &room.price);
            printf("New Status: ");
            scanf("%s", room.status);

            fseek(userFile, -sizeof(struct Room), SEEK_CUR);

            fwrite(&room, sizeof(struct Room), 1, userFile);

            printf("Room Updated Successfully!\n");
            break;
        }
    }
    if (!found)
    {
        printf("Room Not Found!\n");
    }
    fclose(userFile);
}
void deleteRoom()
{
    FILE *userFile, *temp;
    struct Room room;
    int number;
    int found = 0;

    userFile = fopen("rooms.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (userFile == NULL)
    {
        printf("File Not Found!\n");
        return;
    }
    printf("Enter Room Number to Delete: ");
    scanf("%d", &number);

    while (fread(&room, sizeof(struct Room), 1, userFile) == 1)
    {
        if (room.roomNumber == number)
        {
            found = 1;
        }
        else
        {
            fwrite(&room, sizeof(struct Room), 1, temp);
        }
    }
    fclose(userFile);
    fclose(temp);
    remove("rooms.dat");
    rename("temp.dat", "rooms.dat");
    if (found)
        printf("Room Deleted Successfully!\n");
    else
        printf("Room Not Found!\n");
}
void searchAvailableRooms()
{
    FILE *userFile;
    struct Room room;

    userFile = fopen("rooms.dat", "rb");

    if (userFile == NULL)
    {
        printf("No Room Found!\n");
        return;
    }
    printf("\n======= AVAILABLE ROOMS =======\n");

    while (fread(&room, sizeof(struct Room), 1, userFile) == 1)
    {
        if (strcmp(room.status, "Available") == 0)
        {
            printf("\nRoom Number : %d", room.roomNumber);
            printf("\nType        : %s", room.roomType);
            printf("\nPrice       : %.2f", room.price);
            printf("\n--------------------------");
        }
    }
    fclose(userFile);
}
int main()
{
    int choice;
    while (1)
    {
        printf("\n==============================\n");
        printf(" HOTEL RESERVATION SYSTEM\n");
        printf("==============================\n");

        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            printf("Thank you for choosing us..abr dekha hobe\n");
            exit(0);
        default:
            printf("Invalid Choice...Please try again\n");
        }
    }
    return 0;
}
