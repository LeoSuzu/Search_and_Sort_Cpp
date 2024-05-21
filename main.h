#ifndef SEARCH_AND_SORT_MAIN_H
#define SEARCH_AND_SORT_MAIN_H

#include "Utility.h"
#include "List.h"

//*****************ENUMS*****************//
// Enum to represent the search algorithm
enum SearchAlgorithm { SEQUENTIAL, BINARY };

// Enum to represent the sorting algorithm
enum SortAlgorithm { QUICKSORT, INSERTIONSORT };

//*****************RESULT STRUCTS*****************//
// Single run result struct
struct searchResult
{
    bool success;
    int position;
    int comparisons = 0;
    searchResult() : success(false), position(0), comparisons(0) {}
};

// Search result including time and algorithm used
struct runResultSearch
{
    searchResult result;
    double time;
    char algorithm;
};

// Results of search testing run
struct testRunResultsSearch {
    double timeSeqSuccess = 0, timeSeqFail = 0, timeBinSuccess = 0, timeBinFail = 0;
    int compSeqSuccess = 0, compSeqFail = 0, compBinSuccess = 0, compBinFail = 0;
    int runsSeqSuccess = 0, runsSeqFail = 0, runsBinSuccess = 0, runsBinFail = 0;
    int listSize, searchRuns, maxNumInList;
};

//Results for single sorting run
struct sortResult
{
    char algorithm;  // 'Q' for QuickSort, 'I' for InsertionSort
    unsigned int time;  // Time taken for sorting
    unsigned int comparisons;  // Number of comparisons performed
    unsigned int assignments;  // Number of assignments performed
    bool isSorted; // Indicates whether the list is sorted or not
};

//Results for multiple sorting runs
struct  testRunResultsSort
{
    unsigned int runsQuickSort = 0;
    double timeQuickSort = 0;
    unsigned long long compQuickSort = 0;
    unsigned long long assignmentsQuickSort = 0;
    unsigned int runsInsertionSort = 0;
    double timeInsertionSort = 0;
    unsigned long long compInsertionSort = 0;
    unsigned long long assignmentsInsertionSort = 0;
    unsigned int listSize = 0;
    unsigned int SortRuns = 0;
};


//*****************SEARCH*****************//
// Search test functions
void manualSearch(SearchAlgorithm algorithm);
void searchTests(int listSize = 0, int searchCycles = 0);

// List initialization functions for searching
void initLists(int length, List<unsigned int> &listOdd, List<unsigned int> &listEven);

// Search algorithm functions
searchResult seqSearch(const List<unsigned int>& list, unsigned int target);
searchResult binSearch(const List<unsigned int> &list, unsigned int key);

// Functions for printing results for search tests
void printSearchResult(searchResult &printThis);

//*****************SORT*****************//
//SortTest functions
void manualSort(SortAlgorithm sortingAlgorithm);
void sortTests(unsigned int listSize = 0, unsigned int printRange = 0, unsigned int sortCycles = 0);

// Initialization functions for sorting list
void initRandomList(int length, List<unsigned int> &list);

// Sorting algorithm functions
sortResult insertionSort(List<unsigned int> &list, Timer &timing, bool print);
sortResult quickSort(List<unsigned int> &list, sortResult &result, unsigned int length, unsigned int startingPos);

// Helper function for checking if list is sorted
bool isListSorted(List<unsigned int> &list);

// Functions for printing results for sort tests
void printTestRange(int position, List<unsigned int> &list, int size);

#endif //SEARCH_AND_SORT_MAIN_H
