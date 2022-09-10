#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
#include "custgraphics.h"

struct record
{
    char name[25];
    float accuracy;
    float WPM;
};

void countDown()
{
    printf("\t\t\t\t\t");
    for(int i=5;i>0;i--)
    {
        printf("....%d ",i);
            Sleep(1000);
    }
    printf("\t\t\t\t");
    printf("  GO!!!  \n");
}

void show_board(char level[])
{
    FILE *ptr;
    int i=1;
    struct record input;
    if (level=="Level_1.txt")
        ptr=fopen("Level_1_records.txt","r");
    else if (level=="Level_2.txt")
        ptr=fopen("Level_2_records.txt","r");
    else if (level=="Level_3.txt")
        ptr=fopen("Level_3_records.txt","r");
    while (fread(&input, sizeof(struct record), 1, ptr) == 1)
    {
        printf("\t\t\t\t\t");
        printf("%d\t\%s\t\t\t%.2f\t\t\t\t%.2f\n",i, input.name, input.accuracy, input.WPM);
        i++;
    }
    fclose(ptr);
}

void save_record(char Name[],float  Accuracy,float WPM,char level[])
{
    struct record input;
    FILE *ptr;
    char c;
    int data=0;

    if (level=="Level_1.txt")
        ptr=fopen("Level_1_records.txt","r");
    else if (level=="Level_2.txt")
        ptr=fopen("Level_2_records.txt","r");
    else if (level=="Level_3.txt")
        ptr=fopen("Level_3_records.txt","r");

    if (!feof(ptr))
    {
        while(!feof(ptr))
        {
            fread(&input, sizeof(struct record), 1, ptr);
            data = data + 1;
        }
    }
    else
        data=1;
    printf("\n%d\n",data);
    fseek(ptr, 0, SEEK_SET);
    struct record recs[data];
    if(!feof(ptr))
    {
        int i=1;
        while(!feof(ptr))
        {
         fread(&recs[i], sizeof(struct record), 1, ptr);
         i++;
        }
    }
    fclose(ptr);
    strcpy(recs[0].name,Name);
    recs[0].accuracy=Accuracy;
    recs[0].WPM=WPM;
    for (int i=0;i<data;i++)
    {
        for(int j=i;j<data;j++)
        {
            if(recs[i].WPM<recs[j].WPM)
            {
                struct record temp;
                temp=recs[i];
                recs[i]=recs[j];
                recs[j]=temp;
            }
        }
    }

    if (level=="Level_1.txt")
        ptr=fopen("Level_1_records.txt","w");
    else if (level=="Level_2.txt")
        ptr=fopen("Level_2_records.txt","w");
    else if (level=="Level_3.txt")
        ptr=fopen("Level_3_records.txt","w");

    for (int i=0 ; i<data ; i++)
    {
        fwrite (&recs[i], sizeof(struct record),1, ptr);
    }

    fclose(ptr);
}

void conduction(char level[],int file_words,int test_words)
{
    char name[25];
    int counter=-1;
    srand(time(0));
    char ch;
    char answer[500];
    char task[500]="\0";
    char test_string[file_words][15];
    float accuracy;
    FILE *ptr;
    clock_t t;
    ptr = fopen(level,"r");
    for(int i=0;i<file_words;i++)
    {
        int j=0;
        char te[15];

        do
        {
            ch=fgetc(ptr);
            if (ch == ' ' || ch == '\n')
                break;
            te[j]=ch;
            j++;
        } while(!feof(ptr));

        te[j]='\0';
        strcpy(test_string[i],te);
    }

    fclose(ptr);
    for (int i=0;i<test_words;i++)
    {
        int j=(rand() %(file_words))+0;
        strcat(task,test_string[j]);
        if (i!=test_words-1);
            strcat(task," ");
    }
    printf("\n\n\n");
    printf("\t\t\t\t\t");
    printf("Enter your name :");
    gets(name);
    fflush(stdin);
    countDown();

    if(level=="Level_1.txt")
    {
        printf("\n\t\t\t\t\t");
        pl();
        printf("\t\t\t\t\t");
    }
    else
    {
        p2();
    }
    puts(task);
    if(level=="Level_1.txt")
    {
        printf("\n\t\t\t\t\t");
        pl();
    }
    else
        p2();
    t = clock();
    if(level=="Level_1.txt")
        printf("\t\t\t\t\t");
    gets(answer);
    fflush(stdin);
    t = clock() - t;
    float time_taken = ((float)t)/CLOCKS_PER_SEC;
    printf("\n\n");
    for(int i=0;task[i]!='\0';i++)
    {
        if (task[i]!=answer[i])
            counter++;
    }
    printf("\t\t\t\t\t");
    printf("Mistakes made were :%d\n",counter);

    accuracy=(float)(((strlen(task)-counter)*100)/strlen(task));
    printf("\t\t\t\t\t");
    printf("Accuracy of this attempt is :%.2f\n",accuracy);
    printf("\t\t\t\t\t");
    printf("Time Taken to complete the attempt is :%.2f\n\n",time_taken);
    system("pause");
    save_record(name,accuracy,strlen(answer)/time_taken,level);
}


int main()
{
    system("color f0");
    displayTitle();
    int choice_1;
    printf("\t\t\t\t\t");
    printf("1. Practice on Typing Tutor\n");
    printf("\t\t\t\t\t");
    printf("2. View Leader Board\n");
    printf("\t\t\t\t\t");
    printf("3. Exit\n");
    printf("\t\t\t\t\t");
    printf("Select an option :");
    scanf("%d",&choice_1);
    fflush(stdin);
    while(choice_1!=3)
    {

    int choice_2;
    switch (choice_1)
    {
    case 1:
        practiceMode();
        printf("\t\t\t\t\t");
        printf("1. Level-1\n");
        printf("\t\t\t\t\t");
        printf("2. Level-2\n");
        printf("\t\t\t\t\t");
        printf("3. Level-3\n");
        printf("\t\t\t\t\t");
        printf("4. To go back\n");
        printf("\t\t\t\t\t");
        printf("Select difficulty level :");
        scanf("%d",&choice_2);
        fflush(stdin);
        fflush(stdin);
            switch (choice_2)
            {
            case 1:
                Level_1_test();
                printf("\t\t\t\t\t");
                conduction("Level_1.txt",138,20);
                break;
            case 2:
                Level_2_test();
                printf("\t\t\t\t\t");
                conduction("Level_2.txt",99,35);
                break;
            case 3:
                Level_3_test();
                printf("\t\t\t\t\t");
                conduction("Level_3.txt",166,50);
                break;
            case 4:
                printf("Move to previous \"Option Window\" ");
                break;
            default:
                printf("Choice does not exist....");
                break;
            }
        break;
    case 2:
        printf("\t\t\t\t\t");
        printf("Select a category...\n");
        printf("\t\t\t\t\t");
        printf("1. Level-1\n");
        printf("\t\t\t\t\t");
        printf("2. Level-2\n");
        printf("\t\t\t\t\t");
        printf("3. Level-3\n");
        printf("\t\t\t\t\t");
        printf("Select a choice :");
        scanf("%d",&choice_2);
        fflush(stdin);

        switch(choice_2)
        {
        case 1:
            Level_1_rec();
            printf("\t\t\t\t\t");
            printf("Rank\tName\t\t\tAccuracy\t\t\tSpeed(LPS)\n");
            printf("\t\t\t\t\t");
            line();
            show_board("Level_1.txt");
            system("pause");
            break;
        case 2:
            Level_2_rec();
            printf("\t\t\t\t\t");
            printf("Rank\tName\t\t\tAccuracy\t\t\tSpeed(LPS)\n");
            printf("\t\t\t\t\t");
            line();
            show_board("Level_2.txt");
            system("pause");
            break;
        case 3:
            Level_3_rec();
            printf("\t\t\t\t\t");
            printf("Rank\tName\t\t\tAccuracy\t\t\tSpeed(LPS)\n");
            printf("\t\t\t\t\t");
            line();
            show_board("Level_3.txt");
            system("pause");
            break;
        default:
            printf("\t\t\t\t\t");
            printf("Choice does not exist....");
            printf("\n\t\t\t\t\tResetting menu");
            dots();
            Sleep(1000);
            system("cls");
            break;
        }

    case 3:
        break;
    default:
        printf("\t\t\t\t\t");
        printf("Choice does not exist\n");
        printf("\t\t\t\t\t");
        printf("Resetting Menu");
        dots();
        break;
    }

    displayTitle();
    printf("\t\t\t\t\t");
    printf("1. Practice on Typing Tutor\n");
    printf("\t\t\t\t\t");
    printf("2. View Leader Board\n");
    printf("\t\t\t\t\t");
    printf("3. Exit\n");
    printf("\t\t\t\t\t");
    printf("Select an option :");
    scanf("%d",&choice_1);
    }

    exiting();
}
