/*
Program Description: This program reads in pre-defined lists of student records from .csv files,
merges them together and then uses an algorithm to sort the merged lists by surname. It then offers
the user the option of searching for a specific student by surname (note that this is case sensitive). 
The Sorting algorithm used is a combination of Insertion and Merge Sort. The searching algorithm is a
combination of binary and linear searches. 


Author: Stephen Pearson /C17753589

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define MAX_DT265A 1		// PartTime (12)
#define MAX_DT265C 10		// PartTime (10)
#define MAX_DT265B 14		// FullTime (14)
#define MAX_DT8900  6  		// FullTime ( 6)

#define ALL_STUDENTS   MAX_DT265A+MAX_DT265C+MAX_DT265B+MAX_DT8900  // Max total = 24

struct student_record {
	char fName [20];
	char sName [20];
	char dob[12];
	char studentNum[12];
	char gender[12];
    char course[12];
};
typedef struct student_record RECORD;

// Function Prototypes
int merge_sort() ;
int merge(RECORD *[42], int, int, int) ;
int binarySearch(RECORD *[], int, int, char[]) ;
void insertionSort(RECORD *[]);

int main() {
	FILE * fp;
	int i,j;
    RECORD  A[ALL_STUDENTS] ;
    RECORD *A_ptr[ALL_STUDENTS];
    char course_code[12];
    char searchKey[20] = "";
    int resultIndex;
	
    for(i=0;i<(ALL_STUDENTS +1);i++)
    {
        A_ptr[i] = &A[i];
    }
    //============================================
    strcpy( course_code, "DT265A");
	fp = fopen("DT265A.csv", "r");
	for(i = 0; i < MAX_DT265A; i++)
	{
		fscanf(fp," %[^,], %[^,], %[^,], %[^,], %8s", A[i].fName, A[i].sName, A[i].dob, A[i].studentNum, A[i].gender );
        strcpy( A[i].course, course_code );
	}
	fclose(fp);
    //=============================================
    strcpy( course_code, "DT265C");
	fp = fopen("DT265C.csv", "r");
	for(i = 0; i < MAX_DT265C; i++)
	{
		// use "%[^,]" for comma delimitted items. Note use "%8s" for last item as it is not followed by a comma.
		fscanf(fp," %[^,], %[^,], %[^,], %[^,], %8s", A[MAX_DT265A+i].fName, A[MAX_DT265A+i].sName, A[MAX_DT265A+i].dob,
					A[MAX_DT265A+i].studentNum, A[MAX_DT265A+i].gender );
        strcpy( A[MAX_DT265A+i].course, course_code );
	}
	fclose(fp);
    //=============================================
   strcpy( course_code, "DT265B");
	fp = fopen("DT265B.csv", "r");
	for(i = 0; i < MAX_DT265B; i++)
	{
		fscanf(fp," %[^,], %[^,], %[^,], %[^,], %8s", A[MAX_DT265A+MAX_DT265C+i].fName, A[MAX_DT265A+MAX_DT265C+i].sName, A[MAX_DT265A+MAX_DT265C+i].dob,
					A[MAX_DT265A+MAX_DT265C+i].studentNum, A[MAX_DT265A+MAX_DT265C+i].gender );
        strcpy( A[MAX_DT265A+MAX_DT265C+i].course, course_code );
	}
	fclose(fp);
    //=============================================
    strcpy( course_code, "DT8900");
	fp = fopen("DT8900.csv", "r");
	for(i = 0; i < MAX_DT8900; i++)
	{
		fscanf(fp," %[^,], %[^,], %[^,], %[^,], %8s", A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].fName,
				A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].sName, A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].dob,
				A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].studentNum, A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].gender );
        strcpy( A[MAX_DT265A+MAX_DT265C+MAX_DT265B+i].course, course_code );
	}
	fclose(fp);
    //=============================================

	printf("\n\n Part 1 ========================= Combined UnSorted List of ALL Students ==============================\n");
	for(i = 0; i < MAX_DT265A+MAX_DT265C+MAX_DT265B+MAX_DT8900; i ++) {
	printf( "\t %-20s %-20s %-20s %-20s %-20s  %-20s \n", A[i].fName, A[i].sName, A[i].dob, A[i].studentNum, A[i].gender, A[i].course);
	}
	//  ==========================================================================================================================
	if ( ALL_STUDENTS >= 40)
	{
		merge_sort( A_ptr, 0,  ALL_STUDENTS-1);  // use merge_sort for large numbers i.e. >= 40. 
		printf("\n\n\tMerge Sort used as ALL_STUDENTS >= 40");
	}
	else
	{
		insertionSort( A_ptr );	 // use insertionSort for small numbers i.e. < 40.
		printf("\n\n\tInsertion Sort used as ALL_STUDENTS < 40");
	}
    	
	printf("\n\n Part 1 ===============  Combined List of ALL Students - SORTED  by  SURNAME (only) ======================\n");
	for(i = 0; i < ALL_STUDENTS; i ++) {
	printf( "\t %-20s %-20s %-20s %-20s %-20s  %-20s \n", A[i].fName, A[i].sName, A[i].dob, A[i].studentNum, A[i].gender, A[i].course);
	}
 	//====================End  of  Part 1 ==============================================
 	
 	//=======================Start of Part 2  ===========================================
	printf("\n\n Part 2 ================= List of FULL-TIME Students ======================\n");

	for(i = 0; i < ALL_STUDENTS; i ++) {
		if ( (strcmp( (A[i].course), "DT265B" ) == 0 ) || (strcmp( (A[i].course), "DT8900" ) == 0 ) ) {
			printf( "\t %-20s %-20s %-20s %-20s %-20s  %-20s \n", A[i].fName, A[i].sName, A[i].dob, A[i].studentNum, A[i].gender, A[i].course);
		} 	// End of if
	}		// End of for
	//========================End  of Part 2 ===========================================
	
	//=======================Start of Part 3  ===========================================
	printf("\n\nPart  3  ==============To Search for a Specific Student by Surname ======================\n");
	while(strcmp(searchKey, "exit")!=0)
	{
		printf("\n\tPlease enter the required surname or type 'exit' to quit\n\n");
		scanf("%s", searchKey);	
		resultIndex= binarySearch( A_ptr, 0, ALL_STUDENTS-1, searchKey ) ;
		if(resultIndex == -1)
		{
			if(strcmp(searchKey, "exit")!=0)
			{
			printf("\n\t '%s' is not present, Note this system is case sensitive\n", searchKey);
			}
		}
		else 
		{
		// To check if the required surname occurs more than once in the sorted list
			i=resultIndex;  // initialize i to resultIndex
			j=resultIndex;  // initialize j to resultIndex
			while(strcmp(searchKey, A[i].sName) ==0)
			{	
				i--; // To check if any surnames before searchKey = searchKey
			}
			i = i+1; // i is now index for the first occurence of the searchKey
			
			while(strcmp(searchKey, A[j].sName) ==0)
			{
				j++; // To check if any surnames after searchKey = searchKey
			}
			j=j-1;	// j is now index for the last occurence of the searchKey
			
			for(resultIndex=i; resultIndex <j+1; resultIndex++)
			{
				printf( "\t %-20s %-20s %-20s %-20s %-20s  %-20s \n", A[resultIndex].fName, A[resultIndex].sName, 
					A[resultIndex].dob, A[resultIndex].studentNum, A[resultIndex].gender, A[resultIndex].course);
			}
		}
	}
	printf("\nSearching complete/exit selected\n");
	//============================================================
	return 0;
}			// End of main
//================End of Part 3 =============================================================================

//====  START  of  FUNCTIONS   ==================================================


//=========================================================================
int merge_sort( RECORD *A[], int low, int high )
{
  int mid;
  if(low < high)
  {
    mid=(low+high)/2;   // Divide and Conquer

    merge_sort(A, low, mid); 	// recursive call to left half
    merge_sort(A, mid+1, high); // recursive call to right half

    merge(A, low, mid, high);  // Combine
  }
  return 0;
}	// end of merge_sort function
//=============================================================
int merge(RECORD *A[], int low, int mid, int high)
{
   	int leftIndex = low;
   	int rightIndex = mid+1;
   	int combinedIndex = low;  // or leftIndex
   	int i;
   	RECORD  tempA[ALL_STUDENTS];
    // STEP 1
  	while ( leftIndex <= mid  &&  rightIndex <= high )
  	{
  		if (strcmp( ( A[leftIndex]->sName), ( A[rightIndex]->sName) ) <= 0 ) {
			tempA[combinedIndex] = *(*(A+leftIndex));
		  	combinedIndex++;
		  	leftIndex++;
	  	}
    	else  {
			tempA[combinedIndex] = *(*(A+rightIndex));
			combinedIndex++;
			rightIndex++;
		}
  	}		// End of while
  	// STEP 2
	if( leftIndex == mid + 1 )	{
  		while( rightIndex <= high )  {
			tempA[combinedIndex] = *(*(A+rightIndex));
			combinedIndex++;
		  	rightIndex++;
  		}
	}
	else	{
   			while(  leftIndex <= mid )  {
   				tempA[combinedIndex] = *(*(A+leftIndex));
                combinedIndex++;
                leftIndex++;
   			}
		}

	// STEP  3
   	for( i = low; i <= high; i++ )
    {
		*(*(A+i)) = tempA[i];
    }
	return 0;
}	// end of merge function
//=======================================================
int binarySearch( RECORD *A[], int low, int high, char searchKey[] )  {
	int middle = ( low + high ) / 2;
	
	while(low<= high)
	{
		if ( strcmp( A[middle]->sName, searchKey) ==0 )
		{
			return middle;
		}
		else if ( strcmp( A[middle]->sName, searchKey) <= 0 )
		{
			return binarySearch( A, middle+1, high, searchKey );
		}
		else
		{
			return binarySearch( A, low, middle-1, searchKey );
		}
	}
	return -1;   // i.e. searchKey not found	
}	// end of Binary Search function
//=======================================================

/*This function sorts the supplied array of structures by Surname using the insertion sort algorithim*/
void insertionSort(RECORD *A[])	
{

	int i, j;

	RECORD  tempA;

	for(i=1; i<ALL_STUDENTS-1; i++)
	{
		j = i;
		while(j > 0 && 	(strcmp( ( A[j-1]->sName), ( A[j]->sName) ) > 0 ) )
		{
			tempA = *(*(A+j)) ;
			*(*(A+j)) = *(*(A+(j-1) ));
			*(*(A+(j-1) )) = tempA;
			j--;
		}//end while
	}//end for	
}// end of Insertion sort function
//=======================================================
