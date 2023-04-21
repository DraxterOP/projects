#include <stdio.h>
#include <string.h>

//Structure to hold courier details
struct Courier {
    char name[50];
    char address[100];
    char phone[15];
    char tracking_id[20];
};

//Insert module
void insert() {
    struct Courier c;
    FILE *fp;
    fp = fopen("courier.txt","a");
    printf("\nEnter Name: ");
    fflush(stdin);
    gets(c.name);
    printf("\nEnter Address: ");
    fflush(stdin);
    gets(c.address);
    printf("\nEnter Phone Number: ");
    fflush(stdin);
    gets(c.phone);
    printf("\nEnter Tracking ID: ");
    fflush(stdin);
    gets(c.tracking_id);
    fwrite(&c,sizeof(c),1,fp);
    fclose(fp);
    printf("\nCourier inserted successfully!");
}

//Display module
void display() {
    struct Courier c;
    FILE *fp;
    fp = fopen("courier.txt","r");
    printf("\nName\tAddress\tPhone\tTracking ID");
    while(fread(&c,sizeof(c),1,fp)) {
        printf("\n%s\t%s\t%s\t%s",c.name,c.address,c.phone,c.tracking_id);
    }
    fclose(fp);
}

//Search module
void search() {
    struct Courier c;
    FILE *fp;
    char id[20];
    printf("\nEnter Tracking ID to search: ");
    fflush(stdin);
    gets(id);
    fp = fopen("courier.txt","r");
    while(fread(&c,sizeof(c),1,fp)) {
        if(strcmp(c.tracking_id,id)==0) {
            printf("\nCourier found:");
            printf("\nName: %s\nAddress: %s\nPhone Number: %s\nTracking ID: %s",c.name,c.address,c.phone,c.tracking_id);
            fclose(fp);
            return;
        }
    }
    printf("\nCourier not found!");
    fclose(fp);
}

//Delete/Update module
void delete_update() {
    struct Courier c;
    FILE *fp1,*fp2;
    char id[20];
    int choice;
    printf("\nEnter Tracking ID to delete/update: ");
    fflush(stdin);
    gets(id);
    fp1 = fopen("courier.txt","r");
    fp2 = fopen("temp.txt","w");
    while(fread(&c,sizeof(c),1,fp1)) {
        if(strcmp(c.tracking_id,id)==0) {
            printf("\nCourier found:");
            printf("\nName: %s\n\tAddress: \t%s\n\tPhone Number:\t %s\n\tTracking ID: %s",c.name,c.address,c.phone,c.tracking_id);
            printf("\nDo you want to delete or update this courier? (1 for delete, 2 for update): ");
            scanf("%d",&choice);
            if(choice==1) {
                printf("\nCourier deleted successfully!");
            } else if(choice==2) {
                printf("\nEnter new Name: ");
                fflush(stdin);
                gets(c.name);
                printf("\nEnter new Address: ");
                fflush(stdin);
                gets(c.address);
                printf("\nEnter new Phone Number: ");
                fflush(stdin);
                gets(c.phone);
                printf("\nEnter new Tracking ID: ");
                fflush(stdin);
                gets(c.tracking_id);
                printf("\nCourier updated successfully!");
            }
        } else {
            fwrite(&c,sizeof(c),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove("courier.txt");
    rename("temp.txt","courier.txt");
}

//Sorting module
void sort() {
    struct Courier c1, c2;
    FILE *fp;
    int choice;
    printf("\nSort by:\n1. Name\n2. Tracking ID\nEnter your choice: ");
    scanf("%d", &choice);
    fp = fopen("courier.txt", "r");
    if(fp == NULL) {
        printf("\nError opening file!");
        return;
    }
    if(choice == 1) {
        while(fread(&c1, sizeof(c1), 1, fp)) {
            while(fread(&c2, sizeof(c2), 1, fp)) {
                if(strcmp(c1.name, c2.name) > 0) {
                    fseek(fp, -2*sizeof(c2), SEEK_CUR);
                    fwrite(&c2, sizeof(c2), 1, fp);
                    fwrite(&c1, sizeof(c1), 1, fp);
                    fseek(fp, -sizeof(c2), SEEK_CUR);
                    c1 = c2;
                }
            }
            fseek(fp, -sizeof(c2), SEEK_CUR);
        }
    } else if(choice == 2) {
        while(fread(&c1, sizeof(c1), 1, fp)) {
            while(fread(&c2, sizeof(c2), 1, fp)) {
                if(strcmp(c1.tracking_id, c2.tracking_id) > 0) {
                    fseek(fp, -2*sizeof(c2), SEEK_CUR);
                    fwrite(&c2, sizeof(c2), 1, fp);
                    fwrite(&c1, sizeof(c1), 1, fp);
                    fseek(fp, -sizeof(c2), SEEK_CUR);
                    c1 = c2;
                }
            }
            fseek(fp, -sizeof(c2), SEEK_CUR);
        }
    } else {
        printf("\nInvalid choice!");
        fclose(fp);
        return;
    }
    fclose(fp);
    printf("\nCouriers sorted successfully!");
}
	
int main()
{
	int choice;
	while(1)
	{
		printf("\n courier management system \n1. insert \n2.display \n3. search \n4. delete \n5.sort \n");
		scanf("%d", &choice);
		switch(choice)
		
	{
		case 1:
        insert();
        break;
        case 2:
        display();
        break;
        case 3:
        search();
        break; 
        case 4:
        delete_update();
         
         break;
         case 5:
         	sort();
         	break;
        case 6:
          printf("\nExiting...");
        return 0;
        default:
         printf("\nInvalid choice!");
        } 
    }
return 0;
   }
