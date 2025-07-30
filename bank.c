#include<stdio.h>
#include<string.h>
#include<conio.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void fix_fgets(char *string);


typedef struct {
    char name[30];
    int acc_no;
    float balance;
}account;
int main() {
    int choice;
    while(1) {
    printf("\n\n*** Bank Management system ***\n");
    printf("1. Create account\n2. Deposit money\n3. Withdraw money\n4. Check Balance\n5. Exit\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
        create_account();
        break;
        case 2:
        deposit_money();
        break;
        case 3:
        withdraw_money();
        break;
        case 4:
        check_balance();
        break;
        case 5:
        printf("Closing the bank, Thanks for your visit.\n\n");
        return 0;
        break;
        default:
        printf("Invalid choice!");
        break;
    }
    }
    return 0;
}

void fix_fgets(char *string) {
    int index = strcspn(string, "\n");
    string[index] = '\0';
}
void create_account() {
    account acc;
    FILE *file = fopen("account.dat", "ab+");
    if(file == NULL) {
        printf("Unable to open file!!\n");
        return;
    }

    char c;
    do {
        c = getchar();
    }while (c != '\n'  && c != EOF);
    printf("Enter your name : ");
    fgets(acc.name, 30, stdin);
    fix_fgets(acc.name);
    printf("Enter your account number : ");
    scanf("%d", &acc.acc_no);
    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);
    printf("Account created successfully.\n");

}

void deposit_money() {
    FILE *file = fopen("account.dat", "rb+");
    if(file == NULL) {
        printf("Unable to open file!!\n");
        return;
    }
    account acc_read;
    int acc_no;
    float money;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter the amount you want to deposit : ");
    scanf("%f", &money);
    while(fread(&acc_read, sizeof(acc_read), 1, file)) {
        if(acc_read.acc_no == acc_no) {
            fseek(file, -sizeof(acc_read), SEEK_CUR);
            acc_read.balance += money;
            fwrite(&acc_read, sizeof(acc_read), 1, file);
            fclose(file);
            printf("Successfully deposited Rs.%.2f\nNew balance is Rs.%.2f", money, acc_read.balance);
            return;
        }
    }
    fclose(file);
    printf("Money could not be deposited as your account was not found.\n", acc_no);
}

void withdraw_money() {
    FILE *file = fopen("account.dat", "r+b");
    if(file == NULL) {
        printf("Unable to open file!!\n");
        return;
    }
    account acc_read;
    int acc_no;
    float money;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    printf("Enter the amount you want to withdraw : ");
    scanf("%f", &money);
    while(fread(&acc_read, sizeof(acc_read), 1, file)) {
        if(acc_read.acc_no == acc_no) {
            if(acc_read.balance>=money) {
                acc_read.balance -= money;
                fseek(file, -sizeof(acc_read), SEEK_CUR);
                fwrite(&acc_read, sizeof(acc_read), 1, file);
                printf("Succesfuly withdrawn Rs.%.2f\nRemaining balance is Rs.%.2f", money, acc_read.balance);
            }
            else {
                printf("Insufficient balance!");
            }
        fclose(file);
        return;
        }
    }
    fclose(file);
    printf("Money could not be withdrawn as your account was not found.\n", acc_no);
}

void check_balance() {
    int acc_no;
    FILE *file = fopen("account.dat", "rb");
    if(file == NULL) {
        printf("Unable to open file!!\n");
        return;
    }
    account acc_read;
    printf("Enter your account number : ");
    scanf("%d", &acc_no);
    while(fread(&acc_read, sizeof(acc_read), 1, file)) {
        if(acc_read.acc_no == acc_no) {
            printf("Your current balance is Rs.%.2f", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account no : %d was not found.\n", acc_no);
}