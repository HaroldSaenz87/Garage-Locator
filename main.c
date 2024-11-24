/* COP 3502C Programming Assignment 4
This program is written by: Harold Saenz */


#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

typedef struct Coordinates
{
    int x;
    int y;

    int distance;

} Garages;

//---------------------------------PROTOTYPES-------------------------------------------------------------------------------//
Garages* ReadData(int* numGar, int* searchGar, int* threshold);
double Find_distance(int x, int y);
void MergeSort(Garages *array ,int left, int right, int threshold);
void merge(Garages* array, int left, int mid, int right);
int compareTo(Garages* L, Garages* R);
void wrapper_sort(Garages* array, int length, int thres);
void binarySearch(Garages* array,int searchNum, int numGar);

//---------------------------------PROTOTYPE-------------------------------------------------------------------------------//


//my global x and y coordinates 
int myX;
int myY;


int main()
{
    int numGarage;
    int searchGarage;
    int threshold;

    //read data
    Garages* coordinates = ReadData(&numGarage, &searchGarage, &threshold);
    
    wrapper_sort(coordinates, numGarage, threshold);

    binarySearch(coordinates, searchGarage, numGarage);
    
    free(coordinates);
    
    return 0;
}




//---------------------------------FUNCTIONS-------------------------------------------------------------------------------//



// just reading the input 
Garages* ReadData(int* numGar, int* searchGar, int* threshold)
{
    
    // receives my x&y, the amount of garages, the amount being searched, and the threshold
    scanf("%d %d %d %d %d", &myX, &myY, numGar, searchGar, threshold);

    // the array of garage coordinates
    Garages* coordinates = malloc((*numGar) * sizeof(Garages));

    for(int i = 0; i < *numGar; i++)
    {
        scanf("%d %d", &coordinates[i].x, &coordinates[i].y);

        coordinates[i].distance = Find_distance(coordinates[i].x , coordinates[i].y);

        //checking if its getting stored and the distance calculated
        //printf("%d %d\n", coordinates[i].x, coordinates[i].y);
        //printf("%.2f\n", coordinates[i].distance);
    }
    //printf("\n");

    return coordinates;
}

// for smaller array 
void Insertion(Garages* array, int left, int right)
{
    for(int i = left + 1; i <= right; i++)
    {
        Garages hand = array[i];        // the value to compare later

        int j;
        for(j = i - 1; j >= left; j--)
        {   
            if(array[j].distance > hand.distance)
            {
                array[j + 1] = array[j];
            }

                // if same distance check x coordinates
                // but if x is the same then check the y 
            else if(array[j].distance == hand.distance)
            {
                if(array[j].x > hand.x)
                {
                    array[j + 1] = array[j];
                }
                else if(array[j].x == hand.x)
                {
                    if(array[j].y > hand.y)
                    {
                        array[j + 1] = array[j];
                    }
                    else
                    {
                        break;      //correct position
                    }
                }
                else
                {
                    break;  // corect area
                }

            }
            else
            {
                break;
            }
        }



        array[j + 1] = hand;
    }

    return;
}


// if large array use mergesort/merge and if smaller (or equal threshold) use the insertion
void MergeSort(Garages *array ,int left, int right, int threshold)
{   
    // this would be for the insertion sort
    // will check if size falls below or at threshold
    if(right - left + 1 <= threshold)
    {
        //insertion
        Insertion(array, left, right);
        return;
    }

    if(right > left)
    {
        int mid = (left + right) / 2;

        MergeSort(array, left, mid, threshold);
        MergeSort(array , mid + 1, right, threshold);
        merge(array, left, mid, right);

    }
}



// for larger arrays
void merge(Garages* array, int left, int mid, int right)
{
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    Garages *L = malloc(sizeof(Garages) * sizeLeft);
    Garages *R = malloc(sizeRight * sizeof(Garages));

    for(int i = 0; i < sizeLeft; i++)
    {
        L[i] = array[left + i];
    }
    for(int i = 0; i < sizeRight; i++)
    {
        R[i] = array[mid + 1 + i];
    }


    // trackers
    int i = 0;      //left tracker
    int j = 0;      // right tracker
    int k = left;
    

    // comapre and copy
    while(i < sizeLeft && j < sizeRight)
    {
        // compare
        if(compareTo(&L[i], & R[j]) < 0)  
        {
            array[k] = L[i];
            i++;
            k++;
        }
        else
        {
            array[k] = R[j];
            j++;
            k++;
        }
    }

    // any left remains
    while(i < sizeLeft)
    {
        array[k] = L[i];
        i++;
        k++;
    }

    // any right remains
    while(j < sizeRight)
    {
        array[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);

}



// decide which point should come out first of the two points
int compareTo(Garages* L, Garages* R)
{
    if(L->distance < R->distance)
    {
        return -1; // L is closer
    }
    else if(L->distance > R->distance)
    {
        return 1;   // L is far
    }
    else        // if distance are the same checking X
    {
        if(L->x < R->x)
        {
            return -1;
        }
        else if(L->x > R->x)
        {
            return 1;
        }

        else // if X are the same then just check the Y
        {
            if(L->y < R->y)
            {
                return -1;
            }
            else if(L->y > R->y)
            {
                return 1;
            }
            else
            {
                return 0;       // equal
            }
        }
    }
    
}

// NOT recursive and should call necesary sorting functions
void wrapper_sort(Garages* array, int length, int thres)
{
    // check less than or threshold 
    if(length <= thres)
    {
        Insertion(array, 0, length - 1);
    }
    else
    {
        MergeSort(array, 0, length - 1 , thres);
    }
    
}


void binarySearch(Garages* array,int searchNum, int numGar)
{
    
    
    
    Garages arr[searchNum];

    for(int i = 0; i < searchNum; i++)
    {
        scanf("%d %d", &arr[i].x, &arr[i].y);
        arr[i].distance = Find_distance(arr[i].x, arr[i].y);
    }

    //printf("\n");       // DELETE THIS AFTER COMPLETE 

    for(int i = 0; i < numGar; i++)
    {
        printf("%d %d\n", array[i].x , array[i].y);
    }


    for(int i = 0; i < searchNum; i++)
    {
        int l = 0;
        int h = numGar-1;
        int mid;



        while(l <= h )
        {
            mid = (l + h) / 2;

            // using the compareTo function 
            int compareResult = compareTo(&array[mid], &arr[i]);
            
            // 0 if theres a match
            if(compareResult == 0)
            {
                printf("%d %d garage found at position %d in the order\n", arr[i].x, arr[i].y, mid + 1);        // mid + 1 because it was off by one 
                
                break;
            }
            else if(compareResult < 0)      // right search since everything before mid is far
            {
                l = mid + 1;
            }
            else        // left search since everything after mid is far
            {
                h = mid - 1;
            }

        }
        // no matches
        if(l > h)
        {
            printf("%d %d no garage found\n", arr[i].x, arr[i].y);
        }
    }
}

// distance for garages using square root( (x-x)^2 + (y-y)^2 )
double Find_distance(int x, int y)
{
    int dx = x - myX;
    int dy = y - myY;

    return (dx * dx) + (dy * dy);
}

//---------------------------------END OF FUNCTIONS-------------------------------------------------------------------------------//