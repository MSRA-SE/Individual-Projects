/*
	ASE INDIVIDUAL PROJECT 
	CALCULATE THE FIRST N DIGITS OF PI
	UNIT TEST
	SHILIN LIU
	2014 - 09 - 09
	V-SHILIL
*/
#include<stdio.h>
#include<windows.h>
int main()
{
	char filename1[100], filename2[100];
	FILE *rf, *rf1, *rf2;
	char ch1, ch2;
	bool equal;
	int count;
	equal = true;
	rf = fopen("file.txt", "r");
	if (rf == NULL)
	{
		printf("file.txt not exist\n");
		system("pause");
		return 0;
	}
	fscanf(rf, "%s", filename1);
	fscanf(rf, "%s", filename2);
	fclose(rf);
	rf1 = fopen(filename1, "r");
	rf2 = fopen(filename2, "r");
	if (rf1 == NULL || rf2 == NULL)
	{
		printf("file not exist %s or %s\n",filename1,filename2);
		system("pause");
		return 0;
	}
	count = 0;
	while (fscanf(rf1,"%c", &ch1) != EOF)
	{
		if (fscanf(rf2, "%c", &ch2) == EOF)
		{
			equal = false;
			break;
		}
		count++;
		if (ch1 != ch2)
		{
			printf("\n===========================\n%d character:%c %c\n",count, ch1, ch2);
			equal = false;
			break;
		}
		else
		{
			printf("%c", ch1);
		}
			
	}
	if (equal && fscanf(rf2, "%c", &ch2) != EOF)
		equal = false;
	fclose(rf1);
	fclose(rf2);
	if (equal)
		printf("equal\n");
	else
		printf("not equal\n");
	system("pause");
	return 0;
}
