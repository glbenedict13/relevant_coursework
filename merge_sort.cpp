#include <iostream>

using namespace std;

int temp[100];

void merge(int arr[], int low, int mid, int high)
{
    int firstIndex = low;
    int tempIndex = low;
    int secondIndex = mid + 1;

    while((firstIndex <= mid) && (secondIndex <= high))
    {
        //element in 1st array < element in 2nd array
        if(arr[firstIndex] < arr[secondIndex])
        {
            temp[tempIndex] = arr[firstIndex];
            firstIndex++;
            tempIndex++;
        }
        //element in 2nd array < element in 1st array
        else
        {
            temp[tempIndex] = arr[secondIndex];
            secondIndex++;
            tempIndex++;
        }
    }
    //remaining elements in first array added
    while(firstIndex <= mid)
    {
        temp[tempIndex] = arr[firstIndex];
        firstIndex++;
        tempIndex++;
    }
    //remaining elements in second array added
    while(secondIndex <= high)
    {
        temp[tempIndex] = arr[secondIndex];
        secondIndex++;
        tempIndex++;
    }
    //apply sorted temp array to original array
    for(int i = 0; i <= high; i++)
    {
        arr[i] = temp[i];
    }
}//end merge

//recursive
void mergesort(int arr[], int low, int high)
{
    int mid = 0;
    //runs until low = mid or mid + 1 = high
    if(low < high)
    {
        mid = (low + high)/2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}//end mergesort

int main(int argc, char *argv[])
{
    int arr[10] = {56,12,1,99,38,24,123,876,2,49};

    mergesort(arr, 0, 9);

    cout << "merge sort:" << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}
