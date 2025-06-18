/*void saveToFile() 
{
    FILE *fp = fopen("employees.txt", "w");
    if (fp == NULL) 
    {
        printf("Error saving to file.\n");
        return;
    }

    for (int i = 0; i < empcount; i++) 
    {
        fprintf(fp, "%d %s %s %s %d %d %d %d\n",
            employee[i].id,
            employee[i].name,
            employee[i].pass,
            employee[i].month,
            employee[i].leavetaken,
            employee[i].leaveremain,
            employee[i].requestleave,
            employee[i].d
        );
    }

    fclose(fp);
}
void loadFromFile() 
{
    FILE *fp = fopen("employees.txt", "r");
    if (fp == NULL) 
    {
        return;
    }

    while (fscanf(fp, "%d %s %s %s %d %d %d %d",
            &employee[empcount].id,
            employee[empcount].name,
            employee[empcount].pass,
            employee[empcount].month,
            &employee[empcount].leavetaken,
            &employee[empcount].leaveremain,
            &employee[empcount].requestleave,
            &employee[empcount].d
        ) != EOF) {
        empcount++;
    }

    fclose(fp);
}
int main()
{
    int choice;

    loadFromFile();  

    printf("Welcome to the Leave Management System\n********************************************\n");

    while (1) 
    {
        printf("\nPress 1 to add employee\nPress 2 to request leave\n");
        printf("Press 3 to view employee details\nPress 4 for login into manager account\nPress 5 to exit\n");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addemployee();
                break;
            case 2:
                request();
                break;
            case 3:
                details();
                break;
            case 4:
                manager();
                break;
            case 5:
                saveToFile(); 
                printf("Data saved. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct emp 
{
    int id;
    int d;
    char name[20];
    char pass[20];
    char month[20];
    int leavetaken;
    int leaveremain;
    int requestleave;
} emp;

emp employee[100];
int empcount = 0;

void addemployee()
{
    printf("Enter name: ");
    scanf("%s", employee[empcount].name);
    printf("Enter ID: ");
    scanf("%d", &employee[empcount].id);
    printf("Enter password: ");
    scanf("%s", employee[empcount].pass);
    employee[empcount].leavetaken = 0;
    employee[empcount].leaveremain = 30;
    employee[empcount].requestleave = 0;
    empcount++;
}

void request() 
{
    int id, i, found = 0;
    char pass[20];
    int date, date1, d, d1;

    printf("Enter ID: ");
    scanf("%d", &id);
    printf("Enter password: ");
    scanf("%s", pass);

    for (i = 0; i < empcount; i++)
    {
        if (employee[i].id == id && strcmp(employee[i].pass, pass) == 0) 
        {
            found = 1;
            printf("Your total leave for this year is %d\n", employee[i].leaveremain);
            printf("Enter month of leave: ");
            scanf("%s", employee[i].month);
            printf("Enter first day of leave: ");
            scanf("%d", &date);
            printf("Enter last day of leave: ");
            scanf("%d", &date1);
            
             int days = (date1 - date) + 1;
            employee[i].leavetaken += days;
            employee[i].leaveremain -= days;
            
             if (employee[i].leaveremain < 0)
           {
            printf("not enough leave\n");
            printf("Press 4 for leave without pay\nPress 5 to cancel leave request\n");
            scanf("%d", &employee[i].d);
            if(employee[i].d==4)
            {
             printf("leave without pay requested sucessfully\n");
             employee[i].requestleave = 1;
            }
            else if(employee[i].d==5)
            {
                printf("leave cancelled\n");
                employee[i].requestleave = 0;
            }
            else
            {
                printf("invalid option leave cancelled\n");
            }
           }
            
            else
            {
            printf("Your leave is for %d days\n", days);
            printf("Your remaining leave is %d\n", employee[i].leaveremain);
            employee[i].requestleave = 1;
            }
        }
    }

    if (found!=1) 
    {
        printf("Incorrect ID or password\n");
    }
}

void manager()
{
     char magpass[11] = "@manager10";
    char magpass1[20];
    int i=0, d, d1;
   
    printf("Hey manager, enter your password: ");
    scanf("%s", magpass1);

    if (strcmp(magpass, magpass1) != 0) 
    {
        printf("Incorrect manager password.\n");
        return;
    }
    printf("******requested leaves are as follows******\n");
    for(i=0;i<empcount;i++)
    {
      if(employee[i].requestleave==1)
      {
            printf("Employee Name: %s\n", employee[i].name);
            printf("(ID: %d)\n",employee[i].id);
            printf("Leave Requested for Month: %s\n", employee[i].month);
            printf("Leave Taken: %d\n", employee[i].leavetaken);
            printf("Leave Remaining: %d\n", employee[i].leaveremain);
            
        if (employee[i].leaveremain < 0)
         {
            if (employee[i].d == 4) 
            {
                printf("Enter 1 to grant leave without pay \nEnter 2 to reject leave\n");
                scanf("%d", &d1);
                if (d1 == 1) {
                    printf("Leave granted (without pay)\n");
                } else {
                    printf("Leave not granted\n");
                }
            } else 
            {
                printf("Leave not granted\n");
            }
         }
         else 
          {
            printf("Enter 1 to grant leave\nEnter 2 to reject leave\n");
            scanf("%d", &d1);
            if (d1 == 1) {
                printf("Leave granted\n");
            } else {
                printf("Leave not granted\n");
            }
          }
    } 
  }   
}



void details()
{
    int i;
    for (i = 0; i < empcount; i++)
    {
        printf("\nEmployee %d:\n", i + 1);
        printf("Employee Name: %s\n", employee[i].name);
        printf("Leave Taken: %d\n", employee[i].leavetaken);
        printf("Leave Remaining: %d\n", employee[i].leaveremain);
        printf("month of leave: %s\n", employee[i].month);
    }
}



int main()
{
    int choice;
    printf("Welcome to the Leave Management System\n********************************************\n");

    while (1) 
    {
        printf("\nPress 1 to add employee\nPress 2 to request leave\n");
        printf("Press 3 to view employee details\nPress 4 for login into manager account\nPress 5 to exit\n");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                addemployee();
                break;
            case 2:
                request();
                break;
            case 3:
                details();
                break;
            case 4:
                manager();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}