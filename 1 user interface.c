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
struct Booking
{
    int bookingID;
    char guestName[50];
    int roomNumber;
    char checkIn[20];
    char checkOut[20];
    char status[20];
};
int bookingCounter = 1001;

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
        if (strcmp(user.email, "admin@gmail.com") == 0)
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
        printf("3. Cancel Booking\n");
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
            bookRoom();
            break;
        case 3:
            cancelBooking();
            break;
        case 4:
            viewBookings();
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
            printf("\nInvalid Choice...Please try again....\n");
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
void bookRoom()
{
    FILE *roomFile, *bookingFile;
    struct Room room;
    struct Booking booking;
    int roomNo;
    int found = 0;
    roomFile = fopen("rooms.dat", "rb+");
    bookingFile = fopen("booking.dat", "ab");

    if (roomFile == NULL || bookingFile == NULL)
    {
        printf("File Error!\n");
        return;
    }
    printf("\n===== ROOM BOOKING =====\n");

    printf("Enter Room Number: ");
    scanf("%d", &roomNo);
    while (fread(&room, sizeof(struct Room), 1, roomFile) == 1)
    {
        if (room.roomNumber == roomNo &&
            strcmp(room.status, "Available") == 0)
        {
            found = 1;

            booking.bookingID = bookingCounter++;

            getchar();
            printf("Enter Guest Name: ");
            gets(booking.guestName);
            booking.roomNumber = roomNo;

            printf("Check-In Date: ");
            scanf("%s", booking.checkIn);
            printf("Check-Out Date: ");
            scanf("%s", booking.checkOut);

            strcpy(booking.status, "Booked");

            fwrite(&booking, sizeof(struct Booking), 1, bookingFile);

            strcpy(room.status, "Occupied");

            fseek(roomFile, -sizeof(struct Room), SEEK_CUR);

            fwrite(&room, sizeof(struct Room), 1, roomFile);

            printf("\nBooking Successful!\n");
            printf("Booking ID : %d\n", booking.bookingID);

            break;
        }
    }

    if (!found)
    {
        printf("Room is not available!\n");
    }

    fclose(roomFile);
    fclose(bookingFile);
}
void viewBookings()
{
    FILE *fp;
    struct Booking booking;
    fp = fopen("booking.dat", "rb");
    if (fp == NULL)
    {
        printf("No Booking Found!\n");
        return;
    }
    printf("\n========== BOOKINGS ==========\n");
    while (fread(&booking, sizeof(struct Booking), 1, fp) == 1)
    {
        printf("\nBooking ID : %d", booking.bookingID);
        printf("\nGuest Name : %s", booking.guestName);
        printf("\nRoom No    : %d", booking.roomNumber);
        printf("\nCheck-In   : %s", booking.checkIn);
        printf("\nCheck-Out  : %s", booking.checkOut);
        printf("\nStatus     : %s", booking.status);
        printf("\n----------------------------");
    }
    fclose(fp);
}
void cancelBooking()
{
    FILE *bookingFile, *temp, *roomFile;
    struct Booking booking;
    struct Room room;
    int bookingID;
    int found = 0;
    bookingFile = fopen("booking.dat", "rb");
    temp = fopen("temp.dat", "wb");
    roomFile = fopen("rooms.dat", "rb+");
    if (bookingFile == NULL)
    {
        printf("No Booking Found!\n");
        return;
    }
    printf("\n===== CANCEL BOOKING =====\n");
    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);

    while (fread(&booking, sizeof(struct Booking), 1, bookingFile) == 1)
    {
        if (booking.bookingID == bookingID)
        {
            found = 1;

            rewind(roomFile);

            while (fread(&room, sizeof(struct Room), 1, roomFile) == 1)
            {
                if (room.roomNumber == booking.roomNumber)
                {
                    strcpy(room.status, "Available");
                    fseek(roomFile, -sizeof(struct Room), SEEK_CUR);
                    fwrite(&room, sizeof(struct Room), 1, roomFile);
                    break;
                }
            }
            printf("Booking Cancelled Successfully!\n");
        }
        else
        {
            fwrite(&booking, sizeof(struct Booking), 1, temp);
        }
    }
    fclose(bookingFile);
    fclose(roomFile);
    fclose(temp);

    remove("booking.dat");
    rename("temp.dat", "booking.dat");
    if (!found)
    {
        printf("Booking ID Not Found!\n");
    }
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
