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
void registerUser()
{
    struct User user;
    FILE *userFile;
    userFile = fopen("users.dat", "ab");
    if(userFile == NULL)
    {
        printf("Unable to open file!\n");
        return;
    }
    printf("\n===== User Registration =====\n");
    printf("Enter Full Name: ");
    scanf(" %[^\n]", user.name);
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
    if(userFile == NULL)
    {
        printf("\nNo registered users found!\n");
        return;
    }
    printf("\n========== USER LOGIN ==========\n");

    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);

    while(fread(&user, sizeof(struct User), 1, userFile) == 1)
    {
        if(strcmp(email, user.email) == 0 &&
           strcmp(password, user.password) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(userFile);
    if(found)
    {
        printf("\n==================================\n");
        printf(" Login Successful!\n");
        printf(" Welcome %s\n", user.name);
        printf("==================================\n");
    }
    else
    {
        printf("\nInvalid Email or Password!\n");
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
            printf("Thank you!\n");
            exit(0);
        default:
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}
