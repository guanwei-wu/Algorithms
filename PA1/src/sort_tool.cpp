// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int j = 0;
    for(int i=1;i<data.size();i++){
        int key = data[i];
        j = i-1;
        while(j>=0 && data[j]>key){
            data[j+1] = data[j];
            j = j-1;
        }
        data[j+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if(low<high){
        int q = Partition(data, low, high);
        QuickSortSubVector(data, low, q-1);
        QuickSortSubVector(data, q+1, high);
    }
    // Hint : recursively call itself
    //        Partition function is needed
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector
    // TODO : Please complete the function

//    int temp_pivot = 0, temp = 0;
    int temp_pivot = 0;

    srand(time(NULL));
    temp_pivot = (rand()%(high-low+1)) + low;
//    temp = data[high];
//    data[high] = data[temp_pivot];
//    data[temp_pivot] = temp;
    swap(data[high], data[temp_pivot]);

    int pivot = data[high], left = low-1;
    for(int i=low;i<high;i++){
        if(data[i]<pivot){
            left++;
//            temp = data[i];
//            data[i] = data[left];
//            data[left] = temp;
            swap(data[i], data[left]);
        }
    }
//    temp = data[left+1];
//    data[left+1] = data[high];
//    data[high] = temp;
    swap(data[left+1], data[high]);
    return left+1;
    // Hint : Textbook page 171
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    if(low<high){
        int mid = low + (high-low)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function

    int n1 = middle2 - low, n2 = high - middle1;
    vector<int> left, right;
    for(int i=0;i<n1;i++) left.push_back(data[low+i]);
    left.push_back(INT_MAX);
    for(int i=0;i<n2;i++) right.push_back(data[middle2+i]);
    right.push_back(INT_MAX);
    int left_index = 0, right_index = 0;
    for(int i=low;i<=high;i++){
        if(left[left_index]<=right[right_index]){
            data[i] = left[left_index];
            left_index++;
        }
        else{
            data[i] = right[right_index];
            right_index++;
        }
    }

//    vector<int> temp(data.size());
//    int left = low, right = middle2, location = low;
//    while(!(left==middle1+1 || right==high+1)){
//        if(data[left]<=data[right]){
//            temp[location] = data[left];
//            left++;
//            location++;
//        }
//        else{
//            temp[location] = data[right];
//            right++;
//            location++;
//        }
//    }
//    if(left==middle1+1){
//        for(int i=right;i<=high;i++){
//            temp[location] = data[right];
//            right++;
//            location++;
//        }
//    }
//    else{
//        for(int i=left;i<=middle1;i++){
//            temp[location] = data[right];
//            left++;
//            location++;
//        }
//    }
//    for(int i=low;i<=high;i++){
//        data[i] = temp[i-low];
//    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int largest = 0;
    if(root*2+1<heapSize && data[root]<data[root*2+1]) largest = root*2+1;
    else largest = root;
    if(root*2+2<heapSize && data[largest]<data[root*2+2]) largest = root*2+2;
    if(largest!=root){
//        int temp = data[largest];
//        data[largest] = data[root];
//        data[root] = temp;
        swap(data[largest], data[root]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=data.size()/2-1;i>=0;i--){
        MaxHeapify(data, i);
    }
}
