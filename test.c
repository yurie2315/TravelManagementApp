#include<stdio.h>
#include <string.h>
#include<conio.h>
#include<stdlib.h>


// Global Function
// Struct Similar to class

struct Destination{
    char short_name[11];
    char long_name[51];
    char country[21];
    char g_group[21];
    char to_do[101];
};


struct TravelGoal
{
	int nRank;
	char sRemarks[31];
	char sYorN[11];
	char sBuckDestiShort[11];
};

struct TravelPlan
{
	char travPlanDestiShort[11];
	char travStartDate[11];
	int travDays;
	char travMorningAct[10][31];
	char travAfternoonAct[10][31];
	char travEveningAct[10][31];
	float Rating;
	char comments;
	int totalDays;
};


struct Destination DestinationList[101];
struct TravelGoal BucketList[11];
struct TravelPlan TravelPlan[101];

int a; //Global Use for getting choices in main menu


// Use for counting
int i=0,j;
int count=0;
int countBuck=0;
int countItenerary=0;




// Program Flow start here
int main()
{
    int a;
    main_menu();

}


main_menu()
{

// For Showing Main menu
    system("Color 03");
    printf("Main Menu\n\n");
    printf("[1] Show Dashboard\n");
    printf("[2] Destination List Management\n");
    printf("[3] Bucket List Management\n");
    printf("[4] Trip Management\n");
    printf("[5] Exit\n\n");
    printf("Enter your choice: ");

//  scanning input using int a;
    scanf("%d", &a);

//  Conditional Statement for main menu
    if(a == 1) // If scan input = 1 it will go to dashboard
    {
        showDashboard();
    }

    else if(a == 2) // If scan input = 2 it will go to Destination List Management
    {
        destination();
    }

    else if(a == 3) // If scan input = 3 it will go to Bucket List Management
    {
      bucketListManagement();
    }

    else if(a == 4) // If scan input = 4 it will go to Trip Management
    {
        tripManagement();
    }

    else if(a == 5)
    {
        exit(0);
    }

    else
    {
        printf("Invalid Input\n");
        printf("Try again\n");
        main_menu();
    }
}

    // This section is for Show Dashboard


void showDashboard()
{
    printf("\n----------------------------------------\n");
    printf("\nWelcome to Dashboard\n");
    printf("\n[1] Top 3 Bucket List Destinations\n");
    printf("[2] Top 3 Destination\n");
    printf("[3] Bucket List Progress\n");
    printf("[4] Back\n");

    printf("Enter your choice: ");
    scanf("%d", &a);

    if(a == 1)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        top3buck(BucketList, countBuck);
    }

    else if(a == 2)
    {
        readTravelPlan(DestinationList, TravelPlan, &countItenerary, count);
        getTop3Prio(TravelPlan, countItenerary);
    }

    else if(a == 3)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        getProgress(BucketList, countBuck);
    }

    else if(a == 4)
    {
        main_menu();
    }
}

void readTravelGoalBuckList(struct TravelGoal BucketList[], int *countA)
	{
		int i; //for iteration
		char c[100]={}; //to initialize
		int length=0; // the total number of set of elements in the file.

		FILE *fp;
		fp=fopen("bucketlist.txt","r");//opens the file "bucketlist.txt" in read mode.

	   	if(fp == NULL)
		{
			printf("File not found.\n");// if the txt file is not found in the folder.
		}
		else
		{
			while (fgets(c,100,fp)!=NULL) // line from file, to c string // this condition counts total number of lines with the elements
	   		{
	    		if (c[0] != '\n')	// if line not equal to \n
	        	{
	        		length++; // add the length
				}
			}

			fclose(fp); //closes the file

			length=length/4; //the total number of lines with element divided by 4

			fp=fopen("bucketlist.txt","r");

			for(i=0;i<length; i++)	//this condition will loop if i is less than the total number of set and continues to scan each input to the variables
			{
				fscanf(fp,"%s",BucketList[i].sBuckDestiShort); //scanning two strings from the file using fscanf() and storing them into the arrays sDestiShor and sDestiLon respectively.
				fscanf(fp,"%d\n",&BucketList[i].nRank);
				fscanf(fp, " %[^\n]", BucketList[i].sRemarks); //	fgets(BucketList[i].sRemarks,31,fp); //gets the whole contents of the line.
				fscanf(fp,"%s",BucketList[i].sYorN);
			}

			fclose(fp);
		}
			*countA =length; //count is equal to the total number of set of elements in the file
	}

void readTravelPlan(struct Destination DestinationList[], struct TravelPlan TravelPlan[], int *countB, int count)
{
	FILE *fp;

	int i,j; //for iteration
	int k=0; //counts valid files to store
	int length=0;
	char itenerayFILES[100][100];
	int totalDays=0;
	char c[100]={}; //to initialize
	char buffer[100]={};

	for(i=0; i<count; i++)
	{
		strcpy(itenerayFILES[i], DestinationList[i].short_name);
		strcat(itenerayFILES[i], "-itenerary.txt");
	}

	for(i=0; i<count; i++)
	{
		fp=fopen(itenerayFILES[i],"r");
	  	if(fp != NULL)
		{
		strcpy(TravelPlan[k].travPlanDestiShort, DestinationList[i].short_name);
		totalDays=0;
		while (fgets(c,100,fp)!=NULL) // line from file, to c string // this condition counts total number of lines with the elements
	   		{
	    		if (c[0] != '\n')	// if line not equal to \n
	        	{
					length++; // add the length
					if(length == 10 || (length > 10 && (length-10)%7==0)) //counts how many days and sets a condition (if length is equal to 11 totalDays +1
					{
						totalDays++;

					}
				}
			}
			fclose(fp);

			fp=fopen(itenerayFILES[i],"r");


 				fscanf(fp,"%s",TravelPlan[k].travStartDate);
				fscanf(fp,"%f\n",&TravelPlan[k].Rating);
				fscanf(fp,"%s",TravelPlan[k].comments);

				for(j=0;j<totalDays;j++)
				{
					fscanf(fp,"%s\n",buffer);
					fscanf(fp,"%s\n",buffer);
					fscanf(fp, " %[^\n]", TravelPlan[k].travMorningAct[j]);

					fscanf(fp,"%s\n",buffer);
					fscanf(fp, " %[^\n]", TravelPlan[k].travAfternoonAct[j]);

					fscanf(fp,"%s\n",buffer);
					fscanf(fp, " %[^\n]", TravelPlan[k].travEveningAct[j]);
				}

			fclose(fp);
			TravelPlan[k].totalDays=totalDays;//count is equal to the total number of set of elements in the file
			k++;
		}

	}
	*countB=k;
}

void top3buck(struct TravelGoal BucketList[], int countBuck)
{
   int i, j;
   int rank=0;
   char temp[10];

   for (i = 0; i < countBuck-1; i++)
   {
       for (j = 0; j < countBuck-i-1; j++)
       {
           if (BucketList[j].nRank < BucketList[j+1].nRank)
              {
			   rank = BucketList[j].nRank;
			   BucketList[j].nRank = BucketList[j+1].nRank;
			   BucketList[j+1].nRank = rank;
			   strcpy(temp, BucketList[j].sBuckDestiShort);
			   strcpy(BucketList[j].sBuckDestiShort, BucketList[j+1].sBuckDestiShort);
			   strcpy(BucketList[j+1].sBuckDestiShort, temp);
              }
       }
    }
    printf("\n\t\t\t\t             %s  %s  %s \n", BucketList[0].sBuckDestiShort, BucketList[1].sBuckDestiShort, BucketList[2].sBuckDestiShort);
}

void getTop3Prio(struct TravelPlan TravelPlan[], int countItenerary)
{
	int i, j;
   int rank=0;
   char temp[10];

   for (i = 0; i < countItenerary-1; i++)
   {
       for (j = 0; j < countItenerary-i-1; j++)
       {
           if (TravelPlan[j].Rating < TravelPlan[j+1].Rating)
              {
			   rank = TravelPlan[j].Rating;
			   TravelPlan[j].Rating = TravelPlan[j+1].Rating;
			   TravelPlan[j+1].Rating = rank;
			   strcpy(temp, TravelPlan[j].travPlanDestiShort);
			   strcpy(TravelPlan[j].travPlanDestiShort,  TravelPlan[j+1].travPlanDestiShort);
			   strcpy(TravelPlan[j+1].travPlanDestiShort, temp);
              }
       }
    }
    printf("\n%s  %s  %s \n", TravelPlan[0].travPlanDestiShort, TravelPlan[1].travPlanDestiShort, TravelPlan[2].travPlanDestiShort);
}

void getProgress(struct TravelGoal BucketList[], int countBuck)
{
	int i;
	int countY=0, countN=0;
	float fProgress;
	for(i=0; i<countBuck; i++)
	{
	 if(strcmp(BucketList[i].sYorN, "yes")==0)
		{
			countY++;
		}
		fProgress=countY*100./countBuck;
	}
	printf("\nCurrent Progress: %.2f%%\n", fProgress);
}

      // This is the end of section is for Dashboard



   // This section is for Destination List Management

destination()
{

    printf("\nDestination List Management\n");
    printf("\n[1] Short Display List\n");
    printf("[2] Long Display List\n");
    printf("[3] Add Record\n");
    printf("[4] Delete Record\n");
    printf("[5] Edit Record\n");
    printf("[6] Back\n\n");
    printf("Enter your choice: ");

    scanf("%d", &a);

    if(a == 1)
    {
        printf("Short Display List\n");
        readFilesTravelDestination(DestinationList, &count);
        shortDisplayList(DestinationList, count);

    }

    else if(a == 2)
    {
        printf("\nLong Display List\n");
        readFilesTravelDestination(DestinationList, &count);
        longDisplayList(DestinationList, count);
    }

    else if(a == 3)
    {

        readFilesTravelDestination(DestinationList, &count);
        addRecord(DestinationList, &count);
    }

    else if(a == 4)
    {

        readFilesTravelDestination(DestinationList, &count);
        deleteRecord(DestinationList, &count);

    }

    else if(a == 5)
    {

        readFilesTravelDestination(DestinationList, &count);
        editRecord(DestinationList, &count);

    }

        else if(a == 6 )
    {
        system("cls");
        main_menu();
    }

}

void readFilesTravelDestination(struct Destination DestinationList[], int *count)
{
        int i; //for iteration
		char c[100]={}; //to initialize
		int length=0; // the total number of set of elements in the file.

		FILE *fp;
		fp=fopen("destination.txt","r");//opens the file "destination.txt" in read mode.

	   	if(fp == NULL)
		{
			printf("File not found.\n");// if the txt file is not found in the folder.
		}
		else
		{
			while (fgets(c,100,fp)!=NULL) // line from file, to c string // this condition counts total number of lines with the elements
	   		{
	    		if (c[0] != '\n')	// if line not equal to \n
	        	{
	        		length++; // add the length
				}
			}

			fclose(fp); //closes the file

			length=length/4; //the total number of lines with element divided by 4

			fp=fopen("destination.txt","r");

			for(i=0;i<length; i++)	//this condition will loop if i is less than the total number of set and continues to scan each input to the variables
			{
				fscanf(fp,"%s %s", DestinationList[i].short_name, DestinationList[i].long_name); //scanning two strings from the file using fscanf() and storing them into the arrays sDestiShor and sDestiLon respectively.
				fscanf(fp,"%s",DestinationList[i].country);
				fscanf(fp,"%s",DestinationList[i].g_group);
				fscanf(fp, " %[^\n]", DestinationList[i].to_do); //gets the whole contents of the line.
			}
			fclose(fp);
		}
			*count =length; //count is equal to the total number of set of elements in the file
}



void shortDisplayList(struct Destination DestinationList[], int count)
{
	int i;
	for(i=0; i<count; i++)
	{

		printf("\nShort name: %s, Long name: %s\n", DestinationList[i].short_name, DestinationList[i].long_name);
		printf("================================================================");
	}



    printf("\n\nPress [1] to back\n");
    printf("Press [0] to main menu\n\n");
    printf("Enter your Choice:");
    scanf("%d",&a);

        if(a == 1)
        {
            system("cls");
            destination(DestinationList, &count);

        }

        else if(a == 0)
        {
            main_menu();
        }


}

void longDisplayList(struct Destination DestinationList[], int count)
{
    int i;
	for(i=0; i<count; i++)
	{
	    printf("=======================================================");
		printf("\n\Short name: %s, Long name: %s\n", DestinationList[i].short_name, DestinationList[i].long_name);
		printf("\nCountry: %s\n", DestinationList[i].country);
		printf("\nGeo Group: %s\n", DestinationList[i].g_group);
		printf("\nTo do List: %s\n", DestinationList[i].to_do);
		printf("=======================================================");
	}

    printf("\n\nPress [1] to back\n");
    printf("Press [0] to main menu\n\n");
    printf("Enter your Choice:");
    scanf("%d",&a);

        if(a == 1)
        {
            system("cls");
            destination(DestinationList, &count);

        }

        else if(a == 0)
        {
            system("cls");
            main_menu();
        }


}



void addRecord(struct Destination DestinationList[], int *count)
{
	int recInput = *count;
	int i;

	printf("\n=======================================================\n");
	printf("\nAdd Record\n");
	printf("\nEnter Short name: ");
	scanf("%s", DestinationList[i].short_name);
	printf("\nEnter Long name: ");
	scanf("%s", DestinationList[i].long_name);
	printf("\nEnter Country: ");
	scanf("%s", DestinationList[i].country);
	printf("\nEnter Geo Group: ");
    scanf("%s", DestinationList [i].g_group);
	printf("\nEnter to do: ");
	scanf(" %[^\n]", DestinationList[i].to_do);

	FILE *fp;
    fp=fopen("destination.txt","w");
	for(i=0;i<*count;i++)
	{
		fprintf(fp,"%s %s\n", DestinationList[i].short_name, DestinationList[i].long_name);
		fprintf(fp,"%s\n", DestinationList[i].country);
		fprintf(fp,"%s\n", DestinationList [i].g_group);
		fprintf(fp,"%s\n\n", DestinationList[i].to_do);
	}
	fclose(fp);

    printf("\n\nPress [1] to back\n");
    printf("Press [0] to main menu\n\n");
    printf("Enter your Choice:");
    scanf("%d",&a);

        if(a == 1)
        {
            system("cls");
            destination(DestinationList, &count);

        }

        else if(a == 0)
        {
            system("cls");
            main_menu();
        }


}

void deleteRecord(struct Destination DestinationList[],int *count)
{
	int i,j;
	int index = *count;
	int ch;

    printf("\n=======================================================\n");
	printf("\nInput the Short Name you want to delete: \n\n");
	for(i=0; i < *count; i++)
	{
		printf("%d. Short Destination: %s\n", i + 1, DestinationList[i].short_name);
	}
	printf("\nEnter a number: ");
	scanf("%d", &ch);
	printf("\t\t\t\t\t\t ");
	ch = ch - 1;

	for(i=ch; i < index - 1; i++)
	{
		DestinationList[i] = DestinationList[i+1];
	}
	index--;

	FILE *fp;
    fp=fopen("destination.txt","w");//opens the file "destination.txt" in read mode.
	for(i=0;i<index;i++)
	{
		fprintf(fp,"%s %s\n", DestinationList[i].short_name ,DestinationList[i].long_name);
		fprintf(fp,"%s\n", DestinationList[i].country);
		fprintf(fp,"%s\n", DestinationList[i].g_group);
		fprintf(fp,"%s\n\n", DestinationList[i].to_do);
	}
	fclose(fp);
	printf("\nSuccessfully Deleted the Record. \n");

	*count = index;

    printf("\n\nPress [1] to back\n");
    printf("Press [0] to main menu\n\n");
    printf("Enter your Choice:");
    scanf("%d",&a);

        if(a == 1)
        {
            system("cls");
            destination(DestinationList, &count);

        }

        else if(a == 0)
        {
            system("cls");
            main_menu();
        }
}

void editRecord(struct Destination DestinationList[], int *count)
{

        int i,j, found;
        int index = *count;
        int ch1, ch2;
        FILE *fp, *fp1;
        fp = fopen("destination.txt","r");
        fp1 = fopen("temp.txt","w");

        printf("\nInput the Unique Short Name you want to change: \n");
        for(i=0; i<*count; i++)
        {
            printf("%d. Short Destination: %s\n", i + 1, DestinationList[i].short_name);
        }
        printf("\nEnter a number: ");
        scanf("%d", &ch1);



        while (!feof(fp))
        {
            if(fread(&DestinationList[i], sizeof(struct Destination),1,fp))
               {
                if (DestinationList[i].short_name == &ch1)
                found = 1;
                fflush(stdin);
                printf("\nEnter Short name: ");
                scanf("%s", DestinationList[i].short_name);
                printf("\nEnter Long name: ");
                scanf("%s", DestinationList[i].long_name);
                printf("\nEnter Country: ");
                scanf("%s", DestinationList[i].country);
                printf("\nEnter Geo Group: ");
                scanf("%s", DestinationList [i].g_group);
                printf("\nEnter to do: ");
                scanf(" %[^\n]", DestinationList[i].to_do);

                fp=fopen("destination.txt","r+");

                fprintf(fp,"%s %s\n", DestinationList[i].short_name, DestinationList[i].long_name);
                fprintf(fp,"%s\n", DestinationList[i].country);
                fprintf(fp,"%s\n", DestinationList [i].g_group);
                fprintf(fp,"%s\n\n", DestinationList[i].to_do);


                int pos=-1*sizeof(struct Destination);
                fwrite(&DestinationList[i], sizeof(struct Destination),1,fp1);
                printf("\n\n\t Contact Successfully Updated...");
                fclose(fp);
                fclose(fp1);

                printf("\n\nPress [1] to back\n");
                printf("Press [0] to main menu\n\n");
                printf("Enter your Choice:");
                scanf("%d",&a);

                    if(a == 1)
                    {
                        system("cls");
                        destination(DestinationList, &count);

                    }

                    else if(a == 0)
                    {
                        system("cls");
                        main_menu();
                    }
                }

            }
}

// This is the end of section is for Destination List Management

// This section is for BucketListManagement


void bucketListManagement()
{
    printf("\n----------------------------------------\n");
    printf("Bucket List Management\n");
    printf("1. Display List\n");
    printf("2. Add Record\n");
    printf("3. Delete Record\n");
    printf("4. Edit Record\n");
    printf("5. Mark as Achieve\n");
    printf("6. Unmark as Achievement\n");
    printf("7. Back\n");
    printf("-----------------------------------------------\n");
    printf("Enter the number: ");

    printf("Enter your choice: ");
    scanf("%d", &a);

    if(a == 1)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        displayBucketList(BucketList, countBuck);
    }

    if(a == 2)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        addBucketList(BucketList, &countBuck);
    }

    if(a == 3)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        deleteBuckutList(BucketList, &countBuck);
    }

    if(a == 4)
    {
        readTravelGoalBuckList(BucketList, &countBuck);
        editRecordBucketList(BucketList, &countBuck);
    }

    if(a == 5)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                bucketListManagement();
            }
    }

    if(a == 6)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                bucketListManagement();
            }
    }

    else if(a == 7)
    {
        main_menu();
    }

}

void displayBucketList(struct TravelGoal BucketList[], int countBuck)
{
	int i;
	for(i=0; i<countBuck; i++)
	{
		printf("\nShort name: %s\n", BucketList[i].sBuckDestiShort);
		printf("\nRank: %d\n", BucketList[i].nRank);
		printf("\nRemarks: %s\n", BucketList[i].sRemarks);
		printf("\nAchieved: %s\n", BucketList[i].sYorN);
	}
}

void addBucketList(struct TravelGoal BucketList[], int *countBuck)
{
	int recInput = *countBuck;
	int i;
	printf("\nEnter Short name: ");
	scanf("%s", BucketList[i].sBuckDestiShort);
	printf("\nEnter Rank: ");
	scanf("%d", &BucketList[i].nRank);
	printf("\nEnter Remarks: ");
    scanf("%s", BucketList[i].sRemarks);
	printf("\n\Enter Achievement (yes or no): ");
	scanf(" %[^\n]", BucketList[i].sYorN);

	FILE *fp;
    fp=fopen("bucketlist.txt","w");//opens the file "destination.txt" in read mode.
	for(i=0; i<*countBuck; i++)
	{
		fprintf(fp,"%s\n", BucketList[i].sBuckDestiShort);
		fprintf(fp,"%d\n", BucketList[i].nRank);
		fprintf(fp,"%s\n", BucketList[i].sRemarks);
		fprintf(fp,"%s\n\n", BucketList[i].sYorN);
	}
	fclose(fp);
}

void deleteBuckutList(struct TravelGoal BucketList[], int *countBuck)
{
	int i,j;
	int index = *countBuck;
	int choiceDelete;
	printf("\t\t\t\t\t\t  Input the Short Name you want to delete: \n\n");
	for(i=0; i<*countBuck; i++)
	{
		printf("\t\t\t\t\t\t\t  %d. Short Destination: %s\n", i + 1, BucketList[i].sBuckDestiShort);
	}
	printf("\n\t\t\t\t\t\t\t Enter a number: ");
	scanf("%d", &choiceDelete);
	printf("\t\t\t\t\t\t ");
	choiceDelete = choiceDelete - 1;

	for(i=choiceDelete; i < index - 1; i++)
	{
		BucketList[i] = BucketList[i+1];
	}
	index--;

	FILE *fp;
    fp=fopen("bucketlist.txt","w");//opens the file "destination.txt" in read mode.
	for(i=0;i<index;i++)
	{
		fprintf(fp,"%s\n", BucketList[i].sBuckDestiShort);
		fprintf(fp,"%d\n", BucketList[i].nRank);
		fprintf(fp,"%s\n", BucketList[i].sRemarks);
		fprintf(fp,"%s\n\n", BucketList[i].sYorN);
	}
	fclose(fp);
	printf("\n\t\t\t\t\t\t  Successfully Deleted the Bucketlist Record. \n");

	*countBuck = index;
}

void editRecordBucketList(struct TravelGoal BucketList[], int *countBuck)
{
	int i,j;
	int index = *countBuck;
	int choice1;
	int choice2;
	printf("\t\t\t\t  Input the Short Name you want to change: \n\n");
	for(i=0; i<*countBuck; i++)
	{
		printf("\t\t\t\t  %d. Short Destination: %s\n", i + 1, BucketList[i].sBuckDestiShort);
	}
	printf("\n\t\t\t\t    Enter a number: ");
	scanf("%d", &choice1);

	printf("\nInput the entry you want to change");
	printf("\n1. Rank, 2. Reamrks, 3. Achievement (yes or no): ");
	scanf("%d", &choice2);
	FILE *fp;
    fp=fopen("bucketlist.txt","w");
	for(j=0; j<*countBuck; j++)
	{
    if(choice2 == 1)
    {
	printf("\n\t\t\t\t  Enter Rank: ");
	scanf("%s", BucketList[i].nRank);
	fprintf(fp,"%d\n", BucketList[i].nRank);
	}
	else if(choice2 == 2)
	{
	printf("\n\t\t\t\t  Enter Remarks: ");
	scanf("%s", BucketList[i].sRemarks);
	fprintf(fp,"%s\n", BucketList[i].sRemarks);
	}
	else if(choice2 == 3)
	{
	printf("\n\t\t\t\t  Enter Achievement: ");
	scanf("%s", BucketList[i].sRemarks);
	fprintf(fp,"%s\n", BucketList[i].sYorN);
	}
    }
    fclose(fp);

}

// This is the end of section for Dashboard Bucket List Management


// This section is for Trip Management
void tripManagement()
{
    printf("\n----------------------------------------\n");
    printf("Trip Management\n");
    printf("1. Display List\n");
    printf("2. View Itenerary\n");
    printf("3. Add Record\n");
    printf("4. Delete Record\n");
    printf("5. Edit Record\n");
    printf("6. Rate Trip\n");
    printf("7. Back\n");
    printf("-----------------------------------------------\n");
    printf("Enter the number: ");

    printf("Enter your choice: ");
    scanf("%d", &a);

    if(a == 1)
    {
        readFilesTravelDestination(DestinationList, &count);
        readTravelGoalBuckList(BucketList, &countBuck);
        readTravelPlan(DestinationList, TravelPlan, &countItenerary, count);
        displayTravel(DestinationList, BucketList, TravelPlan, countItenerary, count);
    }

    if(a == 2)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {

                tripManagement();
            }
    }

    if(a == 3)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                tripManagement();
            }
    }

    if(a == 4)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                tripManagement();
            }
    }

    if(a == 5)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                tripManagement();
            }
    }

    if(a == 6)
    {
        printf("\nThis Section is in Progress\n");
        printf("\n\nPress [1] to back\n");
        printf("Enter your Choice:");
        scanf("%d",&a);

            if(a == 1)
            {
                tripManagement();;
            }
    }

    else if(a == 7)
    {
        main_menu();
    }
}


void displayTravel(struct Destination DestinationList[], struct TravelGoal BucketList[], struct TravelPlan TravelPlan[], int countItenerary, int count)
{
	int i, j, n;
	char itenerary[100][100];

	for(n=0; n<count; n++)
	{
		strcpy(itenerary[n], TravelPlan[n].travPlanDestiShort);
		strcat(itenerary[n], "-itenerary.txt");
	}

	for(i=0; i<countItenerary; i++)
	{
		printf("%s\n",DestinationList[i].short_name);
		printf("%s\n",TravelPlan[i].travStartDate);
		printf("%f\n",TravelPlan[i].Rating);
		printf("%s\n",TravelPlan[i].comments);

		for(j=0;j<TravelPlan[i].totalDays;j++)
		{
			printf("Day %d\n",j+1);
			printf("Morning Activities:\n");
			printf("%s\n",TravelPlan[i].travMorningAct[j]);
			printf("Afternoon Activities:\n");
			printf("%s\n",TravelPlan[i].travAfternoonAct[j]);
			printf("Evening Activities:\n",TravelPlan[i].travEveningAct[j]);
		}
	}
}



