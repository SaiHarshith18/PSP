#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
};

int main() {
    int choice,  i;
    long count = 0;
    char name[50];
    struct Contact contact;
    FILE *fp;

    fp = fopen("phonebook.dat", "r+");

    if (fp == NULL) {
        fp = fopen("phonebook.dat", "a+");
        if (fp == NULL) {
            printf("Cannot open file");
            exit(1);
        }
    }

    // Read existing contacts and update count
    fseek(fp, 0, SEEK_END);
    count = ftell(fp) / sizeof(struct Contact);
    rewind(fp);

    while (1) {
        printf("\nPhone Book\n");
        printf("1. Add a contact\n");
        printf("2. List all contacts\n");
        printf("3. Edit a contact\n");
        printf("4. Delete a contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter name: ");
                scanf("%s", contact.name);
                printf("Enter phone number: ");
                scanf("%s", contact.phone);
                fseek(fp, 0, SEEK_END);
                fwrite(&contact, sizeof(struct Contact), 1, fp);
                count++;
                break;
            case 2:
                printf("\nList of contacts\n");
                rewind(fp);
                for (i = 0; i < count; i++) {
                    fread(&contact, sizeof(struct Contact), 1, fp);
                    printf("%s\t%s\n", contact.name, contact.phone);
                }
                break;
            case 3:
                printf("\nEnter the name of the contact to edit: ");
                scanf("%s", name);
                rewind(fp);
                for (i = 0; i < count; i++) {
                    fread(&contact, sizeof(struct Contact), 1, fp);
                    if (strcmp(contact.name, name) == 0) 
					{
                        printf("Enter new phone number: ");
                        scanf("%s", contact.phone);
                        fseek(fp,-sizeof(struct Contact), SEEK_CUR);
                        fwrite(&contact, sizeof(struct Contact), 1, fp);
                        break;
                    }
                }
                break;
            case 4:
    			printf("\nEnter the name of the contact to delete: ");
    			scanf("%s", name);
    			rewind(fp);
    			FILE *temp = fopen("temp.dat", "w");
    			if (temp == NULL) 
				{
        			printf("Cannot open temporary file");
        			exit(1);
   				 }
    			int deleted = 0;
    			for (i = 0; i < count; i++) 
				{
        			fread(&contact, sizeof(struct Contact), 1, fp);
        			if (strcmp(contact.name, name) == 0) 
					{
           				printf("%s\t%s\n", contact.name, contact.phone);
            			printf("Are you sure you want to delete this contact? (Y/N): ");
            			scanf(" %c", &choice);
            			if (choice == 'Y' || choice == 'y') 
						{
                			deleted = 1;
                			continue;
            			}
        			}
        			fwrite(&contact, sizeof(struct Contact), 1, temp);
    			}
    			fclose(fp);
    			fclose(temp);
    			if (deleted) 
				{
        			remove("phonebook.dat");
        			rename("temp.dat", "phonebook.dat");
        			printf("Contact deleted successfully.");
        			count--;
    			} 
				else 
				{
        			remove("temp.dat");
        			printf("Contact not found.");
    			}
    			fp = fopen("phonebook.dat", "r+");
    			if (fp == NULL) {
        		printf("Cannot open file");
        		exit(1);
    			}
    			break;
            case 5:
                fclose(fp);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
