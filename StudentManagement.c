#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int id;
    char name[50];
    char branch[20];
    float marks;
};

int count = 0;
struct student * s;
void banner()
{
    printf("===================================\n");
    printf("   STUDENT MANAGEMENT SYSTEM\n");
    printf("===================================\n");
}
int choice_entry()
{
    int choice;
    do {
        printf("Note: This Is A Inpersistent Student Management System \n");
        printf("\n1.Add New Student\n");
        printf("2.View Students\n");
        printf("3.Search Student\n");
        printf("4.Update Student\n");
        printf("5.Delete Student\n");
        printf("6.Exit\n");
        printf("--------------------------------------\n");
        printf("Enter Your Choice: ");
        if (scanf("%d", & choice) != 1)
        {
            while (getchar() != '\n');
            choice = 0;
        }
    } while (choice < 1 || choice > 6);
    return choice;
}

void add_new_std()
{
    int i, j, dup;
    printf("Choice Chosen 1.Add New Student\n");
    if (count >= 100)
        printf("NO MORE STUDENTS CAN BE ADDED\n");
    else
    {
        printf("ENTER ID: ");
        while (scanf("%d", & i) != 1)
        {
            while (getchar() != '\n');
            printf("INVALID INPUT , ID IS NUMERIC: ");
        }
        dup = 0;
        for (j = 0; j < count; j++)
        {
            if (i == s[j].id)
            {
                dup = 1;
                break;
            }
        }
        if (dup == 1)
            printf("ID ALREADY EXISTS! PLEASE ENTER A DIFFERENT ID.\n");
        else
        {
            s[count].id = i;
            getchar();
            printf("ENTER NAME: ");
            fgets(s[count].name, 50, stdin);
            s[count].name[strcspn(s[count].name, "\n")] = '\0';
            printf("ENTER BRANCH: ");
            fgets(s[count].branch, 20, stdin);
            if (strchr(s[count].branch, '\n') == NULL)
            {
                while (getchar() != '\n');
            }
            s[count].branch[strcspn(s[count].branch, "\n")] = '\0';
            printf("ENTER MARKS: ");
            while (scanf("%f", & s[count].marks) != 1)
            {
                while (getchar() != '\n');
                printf("INVALID INPUT, MARKS BE NUMERIC: ");
            }
            count++;
            system("cls");
            banner();
            printf("*STUDENT CREATED SUCCESSFULLY*\n");
        }
    }
}

void view_std(struct student s[])
{
    int i = 0, j = 0;
    system("cls");
    banner();
    printf("Choice Chosen 2.View Students\n");
    if (count == 0)
    {
        printf("NO STUDENTS ADDED TO VIEW\n");
    }
    else
    {
        printf("\n");
        printf("----------------------------\n");
        for (i = 0; i < count; i++)
        {
            printf("ID: %d\n", s[i].id);
            printf("NAME: ");
            for (j = 0; s[i].name[j] != '\0'; j++)
                printf("%c", s[i].name[j]);
            printf("\nBRANCH: %s\n", s[i].branch);
            printf("MARKS: %f", s[i].marks);
            printf("\n");
            printf("----------------------------\n");
            printf("\n");
        }
    }
}

int search_std()
{
    int search = 0, k, search_id, flag = 0;
    char search_name[50];
    if (count == 0)
    {
        printf("NO STUDENTS ADDED\n");
        return -1;
    }
    printf("Search Student:\n");
    printf("SEARCH BY :\n");
    printf("1.NAME.\n");
    printf("2.ID.\n");
    printf("ENTER TYPE OF SEARCH: ");
    while (scanf("%d", & search) != 1 || (search < 1 || search > 2))
    {
        while (getchar() != '\n');
        printf("INVALID SEARCH TYPE! ENTER 1 OR 2: ");
    }
    getchar();
    if (search == 1)
    {
        printf("NOTE: NAME IS CASE SENSITIVE\n");
        printf("ENTER NAME: ");
        fgets(search_name, 50, stdin);
        search_name[strcspn(search_name, "\n")] = '\0';
        for (k = 0; k < count; k++)
        {
            if (strcmp(search_name, s[k].name) == 0)
            {
                flag = 1;
                break;
            }
        }
    }
    else if (search == 2)
    {
        printf("ENTER ID: ");
        while (scanf("%d", & search_id) != 1)
        {
            while (getchar() != '\n');
            printf("INVALID INPUT, IDs ARE NUMERIC: ");
        }
        for (k = 0; k < count; k++)
        {
            if (search_id == s[k].id)
            {
                flag = 1;
                break;
            }
        }
    }
    if (flag == 1)
    {
        system("cls");
        banner();
        printf("STUDENT FOUND");
        printf("\n");
        return k;
    }
    else
    {
        system("cls");
        banner();
        printf("STUDENT NOT FOUND");
        printf("\n");
        return -1;
    }
}

void update_std()
{
    int update_choice = 0, index;
    char update_branch[20];
    float update_marks;
    printf("Choice Chosen 4.Update Student\n");
    if (count == 0)
    {
        printf("NO STUDENTS ADDED\n");
    }
    else
    {
        index = search_std();
        if (index == -1)
            return;
        printf("WHAT DO YOU WANT TO UPDATE?\n");
        do {
            printf("1.BRANCH\n");
            printf("2.MARKS\n");
            printf("ENTER CHOICE: ");
            if (scanf("%d", & update_choice) != 1)
            {
                while (getchar() != '\n');
                update_choice = 0;
                printf("INVALID INPUT, ENTER 1 OR 2: ");
            }
        } while (update_choice < 1 || update_choice > 2);
        if (update_choice == 1)
        {
            printf("ENTER NEW BRANCH: ");
            getchar();
            fgets(update_branch, 20, stdin);
            if (strchr(update_branch, '\n') == NULL)
            {
                while (getchar() != '\n');
            }
            update_branch[strcspn(update_branch, "\n")] = '\0';
            strcpy(s[index].branch, update_branch);
            printf("UPDATED SUCCESSFULLY!!\n");
        }
        else if (update_choice == 2)
        {
            printf("ENTER NEW MARKS: ");
            while (scanf("%f", & update_marks) != 1)
            {
                while (getchar() != '\n');
                printf("INVALID INPUT, MARKS BE NUMERIC: ");
            }
            s[index].marks = update_marks;
            printf("UPDATED SUCCESSFULLY!!\n");
        }
    }
}

void delete_std()
{
    int delete_std_id = 0, i, index = -1;
    printf("Choice Chosen 5.Delete Student\n");
    if (count == 0)
    {
        printf("NO NEW STUDENT ADDED\n");
    }
    else
    {
        printf("REMEMBER DATA IS IRRECOVERABLE\n");
        printf("ENTER ID: ");
        while (scanf("%d", & delete_std_id) != 1)
        {
            while (getchar() != '\n');
            printf("INVALID INPUT, IDs ARE NUMERIC: ");
        }
        for (i = 0; i < count; i++)
        {
            if (s[i].id == delete_std_id)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            system("cls");
            banner();
            printf("STUDENT FOUND!!\n");
            for (i = index; i < count - 1; i++)
                s[i] = s[i + 1];
            count--;
            printf("DELETED SUCCESSFULLY!\n");
        }
        else
        {
            system("cls");
            banner();
            printf("STUDENT NOT FOUND!\n");
        }
    }
}

int main()
{
    banner();
    int choice;
    s = calloc(100, sizeof(struct student));
    if (s == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        return 1;
    }
    do {
        choice = choice_entry();
        if (choice == 1)
            add_new_std();
        else if (choice == 2)
            view_std(s);
        else if (choice == 3)
            search_std();
        else if (choice == 4)
            update_std();
        else if (choice == 5)
            delete_std();
    }
    while (choice != 6);
    printf("THANK YOU.BYE BYE!!\n");
    printf("MADE BY GIRIDHAR\n");
    free(s);
    s = NULL;
    return 0;
}