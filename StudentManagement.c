#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    int id;
    char name[50];
    char branch[4];
    float marks;
};

int count = 0;
struct student * s;

int choice_entry()
{
    int choice;
    do {
        printf("\n1.Add New Student\n");
        printf("2.View Students\n");
        printf("3.Search Student\n");
        printf("4.Update Student\n");
        printf("5.Delete Student\n");
        printf("6.Exit\n");
        printf("--------------------------------------\n");
        printf("Enter Your Choice: ");
        scanf("%d", & choice);
    } while (choice < 1 || choice > 6);
    return choice;
}

void add_new_std()
{
    int dup=0;
    printf("Choice Chosen 1.Add New Student\n");
    if (count >= 100)
        printf("NO MORE STUDENTS CAN BE ADDED\n");
    else
    {
        int i = count++;
        printf("ENTER ID: ");
        scanf("%d", & s[i].id);
        
        getchar();
        printf("ENTER NAME: ");
        fgets(s[i].name, 50, stdin);
        s[i].name[strcspn(s[i].name, "\n")] = '\0';
        printf("ENTER BRANCH: ");
        fgets(s[i].branch, 4, stdin);
        if (strchr(s[i].branch, '\n') == NULL)
        {
            while (getchar() != '\n');
        }
        s[i].branch[strcspn(s[i].branch, "\n")] = '\0';
        printf("ENTER MARKS: ");
        scanf("%f", & s[i].marks);
        printf("*STUDENT CREATED SUCCESSFULLY*\n");
    }
}

void view_std(struct student s[])
{
    int i = 0, j = 0;
    printf("Choice Chosen 2.View Students\n");
    for (i = 0; i < count; i++)
    {
        printf("ID    NAME   BRANCH   MARKS\n");
        printf("%d      ", s[i].id);
        for (j = 0; s[i].name[j] != '\0'; j++)
            printf("%c", s[i].name[j]);
        printf("%s", s[i].branch);
        printf("%f      ", s[i].marks);
    }
}

int search_std()
{
    int search = 0, k, search_id, flag = 0;
    char search_name[50];
    printf("Search Student:\n");
    printf("SEARCH BY :\n");
    printf("1.NAME.\n");
    printf("2.ID.\n");
    printf("ENTER TYPE OF SEARCH: ");
    scanf("%d", & search);
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
        scanf("%d", & search_id);
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
        printf("STUDENT FOUND");
        return k;
    }
    else
    {
        printf("STUDENT NOT FOUND");
        return -1;
    }
}

void update_std()
{
    int update_choice = 0, index;
    char update_branch[4];
    float update_marks;
    printf("Choice Chosen 4.Update Student\n");
    index = search_std();
    if (index == -1)
        return;
    printf("WHAT DO YOU WANT TO UPDATE?\n");
    do {
        printf("1.BRANCH\n");
        printf("2.MARKS\n");
        scanf("%d", & update_choice);
    } while (update_choice < 1 || update_choice > 2);
    if (update_choice == 1)
    {
        printf("ENTER NEW BRANCH: ");
        getchar();
        fgets(update_branch, 4, stdin);
        if (strchr(update_branch, '\n') == NULL)
        {
            while (getchar() != '\n');
        }
        update_branch[strcspn(update_branch, "\n")] = '\0';
        strcpy(s[index].branch, update_branch);
    }
    else if (update_choice == 2)
    {
        printf("ENTER NEW MARKS: ");
        scanf("%f", & update_marks);
        s[index].marks = update_marks;
    }
}

void delete_std()
{
    int delete_std_id = 0, i, index = -1;
    printf("Choice Chosen 5.Delete Student\n");
    printf("REMEMBER DATA IS IRRECOVERABLE\n");
    printf("ENTER ID: ");
    scanf("%d", & delete_std_id);
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
        printf("STUDENT FOUND!!\n");
        for (i = index; i < count - 1; i++)
            s[i] = s[i + 1];
        count--;
        printf("DELETED SUCCESSFULLY!\n");
    }
    else
        printf("STUDENT NOT FOUND!\n");
}

int main()
{
    int choice;
    printf("===================================\n");
    printf("     STUDENT MANAGEMENT SYSTEM\n");
    printf("===================================\n");
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
    } while (choice != 6);
    free(s);
    s = NULL;
    return 0;
}