#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_USERS 10

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char account_number[20];
    char name[50];
    double balance;
} Account;

// Function prototypes
void displayMenu();
int authenticateUser();
void createUser();
void createAccount();
void displayAccount();
void deposit();
void withdraw();
void transferMoney();
void listAccounts();
void deleteAccount();

int main() {
     if (!authenticateUser()) {
        printf("Authentication failed. Exiting the program.\n");
        printf("\nPress any key to return to the dashboard...");
        getchar(); // Consume the newline character from the previous input
        getchar(); 
        system("cls");
       int i;
       printf("1.create user\n2.Login\n0.Exit\n");
       printf("Enter your choice:");
       scanf("%d",&i);
       
       if(i==1){
       	createUser();
	   }
	   if(i==2){
	   	authenticateUser();
	   }
	   if(i==0){
	   	return 1;
	   }
		}
   system("cls");
	

    int choice;

    do {
    	printf("Welcome");
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createAccount();
                
                break;
            case 2:
                displayAccount();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                transferMoney();
                break;
            case 6:
                listAccounts();
                break;
            case 7:
                deleteAccount();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            	
            default:
                printf("Invalid choice. Please try again.\n");
        }
         printf("\nPress any key to return to the dashboard...");
        getchar(); // Consume the newline character from the previous input
        getchar(); 
        system("cls");
    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n=== Banking Application ===\n");
    printf("1. Create Account\n");
    printf("2. Display Account Information\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Transfer Money\n");
    printf("6. List All Accounts\n");
    printf("7. Delete Account\n");
    printf("0. Exit\n");
}

int authenticateUser() {
    char username[50];
    char password[50];

    printf("=== User Authentication ===\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
        printf("Error opening user file.\n");
         printf("\nPress any key to return to the dashboard...");
        getchar(); // Consume the newline character from the previous input
        getchar(); 
        system("cls");
       int i;
       printf("Welcome Habibi\n");
       printf("1.create user\n0.Exit\n");
       printf("Enter your choice:");
       scanf("%d",&i);
       system("cls");
       
       if(i==1){
       	createUser();
	   }
	   if(i==0){
	   	return 1;
	   }
        
    }

    User user;
    int authenticated = 0;

    while (fscanf(userFile, "%s %s", user.username, user.password) == 2) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            authenticated = 1;
            break;
        }
    }

    fclose(userFile);

    return authenticated;
}

void createUser() {
    char username[50];
    char password[50];

    printf("=== Create User ===\n");
    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new password: ");
    scanf("%s", password);

    FILE *userFile = fopen("users.txt", "a");
    if (userFile == NULL) {
        printf("Error opening user file.\n");
        exit(1);
    }

    fprintf(userFile, "%s %s\n", username, password);

    fclose(userFile);

    printf("User created successfully!\n");
    printf("\nPress any key to return to the dashboard...");
        getchar(); // Consume the newline character from the previous input
        getchar(); 
        system("cls");
    
    
}

void createAccount() {
   Account newAccount;

    printf("Enter account number: ");
    scanf("%s", newAccount.account_number);
    printf("Enter account holder name: ");
    scanf("%s", newAccount.name);
    printf("Enter initial balance: ");
    scanf("%lf", &newAccount.balance);

    FILE *file = fopen("accounts.dat", "ab");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fwrite(&newAccount, sizeof(Account), 1, file);

    fclose(file);

    printf("Account created successfully!\n");
}

void displayAccount() {
     char accountNumber[20];

    printf("Enter account number: ");
    scanf("%s", accountNumber);

    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (strcmp(account.account_number, accountNumber) == 0) {
            printf("\n=== Account Information ===\n");
            printf("Account Number: %s\n", account.account_number);
            printf("Account Holder: %s\n", account.name);
            printf("Balance: %.2lf\n", account.balance);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    }
}

void deposit() {
    char accountNumber[20];
    double amount;

    
    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter deposit amount: ");
    scanf("%lf", &amount);

    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (strcmp(account.account_number, accountNumber) == 0) {
            account.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    } else {
        printf("Deposit successful.\n");
    }
}

void withdraw() {
   char accountNumber[20];
    double amount;

    printf("Enter account number: ");
    scanf("%s", accountNumber);
    printf("Enter withdrawal amount: ");
    scanf("%lf", &amount);

    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (strcmp(account.account_number, accountNumber) == 0) {
            if (account.balance >= amount) {
                account.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&account, sizeof(Account), 1, file);
                found = 1;
                printf("Withdrawal successful.\n");
            } else {
                printf("Insufficient funds.\n");
            }
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Account not found.\n");
    }
}

void listAccounts() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Account account;

    printf("\n=== List of All Accounts ===\n");

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        printf("Account Number: %s, Account Holder: %s, Balance: %.2lf\n",
               account.account_number, account.name, account.balance);
    }

    fclose(file);
}
void deleteAccount() {
    char accountNumber[20];

    printf("Enter account number to delete: ");
    scanf("%s", accountNumber);

    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        exit(1);
    }

    Account account;
    int found = 0;

    while (fread(&account, sizeof(Account), 1, file) == 1) {
        if (strcmp(account.account_number, accountNumber) == 0) {
            found = 1;
            printf("\n=== Deleting Account ===\n");
            printf("Account Number: %s\n", account.account_number);
            printf("Account Holder: %s\n", account.name);
            printf("Balance: %.2lf\n", account.balance);
            printf("Account deleted successfully!\n");
        } else {
            fwrite(&account, sizeof(Account), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Account not found.\n");
    }

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
}
void transferMoney() {
    char senderAccountNumber[20];
    char receiverAccountNumber[20];
    double amount;

    printf("Enter sender's account number: ");
    scanf("%s", senderAccountNumber);
    printf("Enter receiver's account number: ");
    scanf("%s", receiverAccountNumber);
    printf("Enter transfer amount: ");
    scanf("%lf", &amount);

    FILE *file = fopen("accounts.dat", "rb+");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    Account senderAccount, receiverAccount;
    int senderFound = 0, receiverFound = 0;

    while (fread(&senderAccount, sizeof(Account), 1, file) == 1) {
        if (strcmp(senderAccount.account_number, senderAccountNumber) == 0) {
            senderFound = 1;
            if (senderAccount.balance >= amount) {
                senderAccount.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&senderAccount, sizeof(Account), 1, file);
            } else {
                printf("Insufficient funds in the sender's account.\n");
                fclose(file);
                return;
            }
            break;
        }
    }

    fseek(file, 0, SEEK_SET);

    while (fread(&receiverAccount, sizeof(Account), 1, file) == 1) {
        if (strcmp(receiverAccount.account_number, receiverAccountNumber) == 0) {
            receiverFound = 1;
            receiverAccount.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&receiverAccount, sizeof(Account), 1, file);
            break;
        }
    }

    fclose(file);

    if (!senderFound) {
        printf("Sender's account not found.\n");
    }

    if (!receiverFound) {
        printf("Receiver's account not found.\n");
    }

    if (senderFound && receiverFound) {
        printf("Money transferred successfully.\n");
    }
}
