#include <iostream>
// All necessary includes are in the Utility header file for avoiding multiple includes and conflicts
#include "Utility.h"
#include "main.h"
#include "List.h"

// Defining the clear screen, pause command for Windows and Unix based systems
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#define PAUSE_COMMAND "pause"
#else
#define CLEAR_SCREEN "clear"
#define PAUSE_COMMAND "read -p \"Press any key to continue...\" -n1 -s"
#endif


int main()
{
    cout << "Welcome to the search and sort program!\n"
         << "This program allows you to test different search and sort algorithms\n"
         << "Please choose from the following options:\n";
    int option;
    bool quit = false;
    Timer main_timer;

    while (!quit) {
        print_menu();
        cin >> option;
        switch (option)
        {
            case 1:			//manual seqSearch
                cout << "Manual Sequential Search\n";
                manualSearch(SEQUENTIAL);
                break;
            case 2:			//manual binSearch
                cout << "Manual Binary Search\n";
                manualSearch(BINARY);
                break;
            case 3:			//manual Quick Sort
                cout << "Manual Quick Sort\n";
                manualSort(QUICKSORT);
                break;
            case 4:			//manual Insertion Sort
                cout << "Manual Insertion Sort\n";
                manualSort(INSERTIONSORT);
                break;
            case 5:
                cout << "Search comparison test (manual) \n";
                searchTests(); // Search comparison test with user input
                break;
            case 6:
                cout << "Sorting comparison test (manual) \n";
                sortTests(); // Sorting comparison test with user input
                break;
            case 7: // Short automatic tests for search
                cout << "Short automatic tests for search\n";
                main_timer.reset();
                searchTests(3000, 10);
                searchTests(6000, 10);
                searchTests(12000, 10);
                searchTests(24000, 10);
                cout << "Time spent running search tests : " << main_timer.elapsed_time() << endl;
                break;
            case 8: // Long automatic tests for search
                cout << "Long automatic tests for search\n";
                main_timer.reset(); // Long automatic tests for search
                searchTests(10000, 20);
                searchTests(20000, 20);
                searchTests(40000, 20);
                searchTests(80000, 20);
                cout << "Time spent running search tests : " << main_timer.elapsed_time() << endl;
                break;
            case 9: // Short automatic tests for sort
                cout << "Short automatic tests for sort\n";
                main_timer.reset(); // Short automatic tests for sort
                sortTests(250, 10, 5);
                sortTests(500, 10, 5);
                sortTests(1000, 10, 5);
                cout << "Time spent running sort tests: " << main_timer.elapsed_time() << endl;
                break;
            case 10: // Long automatic tests for sort
                cout << "Long automatic tests for sort\n";
                main_timer.reset(); // Long automatic tests for sort
                sortTests(500, 10, 5);
                sortTests(1000, 10, 5);
                sortTests(1500, 10, 5);
                cout << "Time spent running sort tests: " << main_timer.elapsed_time() << endl;
                break;
            case 11: // Quit
                if (user_says_yes())
                {
                    quit = true;
                }
                break;
            default:
                break;
        }
        system(CLEAR_SCREEN);
    }
    return 0;
}

// ********************SEARCHING********************
// Function to perform a manual search
void manualSearch(SearchAlgorithm algorithm) {
    unsigned int searchFor;
    int listSize;
    searchResult resEven, resOdd;
    Timer testTimer;

    cout << "Size for searchable list? ";
    cin >> listSize;
    cout << "What number would you like to search for? ";
    cin >> searchFor;

    // Initialize lists for odd and even numbers for search
    cout << "Initializing list with odd and even numbers...\n";
    testTimer.reset();
    List<unsigned int> odd_list;
    List<unsigned int> even_list;
    initLists(listSize, odd_list, even_list);  // Ensure this function initializes lists correctly
    cout << "Lists done. Time to initialize: " << testTimer.elapsed_time() << endl;

    // Search for the number in the lists
    cout << "Starting search with algorithm << " << (algorithm == SEQUENTIAL ? "Sequential" : "Binary") << " >>\n";

    // Even list search
    testTimer.reset();
    if (algorithm == SEQUENTIAL) {
        resEven = seqSearch(even_list, searchFor);
    } else if (algorithm == BINARY) {
        resEven = binSearch(even_list, searchFor);
    }
    cout << "Search from even list results:\n";
    printSearchResult(resEven);
    cout << "Time to run (Even): " << testTimer.elapsed_time() << endl;

    // Odd list search
    testTimer.reset();
    if (algorithm == SEQUENTIAL) {
        resOdd = seqSearch(odd_list, searchFor);
    } else if (algorithm == BINARY) {
        resOdd = binSearch(odd_list, searchFor);
    }
    cout << "Search from odd list results:\n";
    printSearchResult(resOdd);
    cout << "Time to run (Odd): " << testTimer.elapsed_time() << endl;

    system(PAUSE_COMMAND);
    system(CLEAR_SCREEN);
}
// Search tests comparison function
void searchTests(int listSize, int searchRuns)
{
    Timer testTimer;
    int maxNumInList;
    unsigned int x[5000]; // Array to hold random numbers for searching
    List<unsigned int> odd_list;
    List<unsigned int> even_list;
    bool preset = true;

    // Determine list size if not provided
    if (listSize == 0 || listSize < 0) {
        cout << "Size of list: ";
        cin >> listSize;
        // Set preset to false stop test in the end
        preset = false;
    }
    maxNumInList = 2 * listSize; // Maximum number in the list is twice the list size

    // Initialize lists with odd and even numbers
    cout << "Initializing lists" << endl;
    testTimer.reset();
    initLists(listSize, odd_list, even_list); // Initialize odd_list and even_list
    cout << "Time to init lists for Even and Odd: " << testTimer.elapsed_time() << endl;

    // Determine number of search runs if not provided
    if (searchRuns == 0) {
        cout << "How many runs / algorithm: ";
        cin >> searchRuns;
        if (searchRuns == 0) {
            searchRuns++;
        }
    }

    vector<runResultSearch> results; // Vector to store results of each search run
    if (searchRuns > 100) {
        cout << "Too many runs, setting to 100" << endl;
        searchRuns = 100;
    }

    // Generate random numbers to search for
    for (auto i = 0; i < searchRuns; i++) {
        x[i] = rand() % maxNumInList;
    }

    // SEQUENTIAL SEARCH PART
    cout << "Searching with sequential search\n";
    // Sequential search for even numbers
    for (auto i = 0; i < searchRuns; i++) {
        if (!preset){
            cout << "Sequential search even cycle: " << i + 1 << endl; // Print cycle number if not preset
        }
        runResultSearch temp;
        List<unsigned int> even_list_copy = even_list; // Create a copy of even_list
        testTimer.reset();
        temp.result = seqSearch(even_list_copy, x[i]); // Perform sequential search
        temp.time = testTimer.elapsed_time();
        temp.algorithm = 'S';
        results.push_back(temp);
    }

    // Sequential search for odd numbers
    for (auto i = 0; i < searchRuns; i++) {
        if (!preset){
            cout << "Sequential search odd cycle: " << i + 1 << endl; // Print cycle number if not preset
        }
        runResultSearch temp;
        List<unsigned int> odd_list_copy = odd_list; // Create a copy of odd_list
        testTimer.reset();
        temp.result = seqSearch(odd_list_copy, x[i]); // Perform sequential search
        temp.time = testTimer.elapsed_time();
        temp.algorithm = 'S';
        results.push_back(temp);
    }

    // BINARY SEARCH PART
    cout << "Searching with binary search\n";
    // Binary search for even numbers
    for (auto i = 0; i < searchRuns; i++) {
        if (!preset){
            cout << "Binary search even cycle: " << i + 1 << endl; // Print cycle number if not preset
        }
        runResultSearch temp;
        List<unsigned int> even_list_copy = even_list; // Create a copy of even_list
        testTimer.reset();
        temp.result = binSearch(even_list_copy, x[i]); // Perform binary search
        temp.time = testTimer.elapsed_time();
        temp.algorithm = 'B';
        results.push_back(temp);
    }

    // Binary search for odd numbers
    for (auto i = 0; i < searchRuns; i++) {
        if (!preset){
            cout << "Binary search odd cycle: " << i + 1 << endl; // Print cycle number if not preset
        }
        runResultSearch temp;
        List<unsigned int> odd_list_copy = odd_list; // Create a copy of odd_list
        testTimer.reset();
        temp.result = binSearch(odd_list_copy, x[i]); // Perform binary search
        temp.time = testTimer.elapsed_time();
        temp.algorithm = 'B';
        results.push_back(temp);
    }

    // RESULTS PRINTING

    testRunResultsSearch runResults;
    runResults.searchRuns = searchRuns;
    runResults.listSize = listSize;
    runResults.maxNumInList = maxNumInList;
    runResultSearch tempRun;

    // Calculate results and summarize statistics
    for (auto i = 0; i < results.size(); i++) {
        tempRun = results[i];
        if (tempRun.algorithm == 'S') {
            if (tempRun.result.success) {
                runResults.timeSeqSuccess += tempRun.time;
                runResults.compSeqSuccess += tempRun.result.comparisons;
                runResults.runsSeqSuccess++;
            } else {
                runResults.timeSeqFail += tempRun.time;
                runResults.compSeqFail += tempRun.result.comparisons;
                runResults.runsSeqFail++;
            }
        } else {
            if (tempRun.result.success) {
                runResults.timeBinSuccess += tempRun.time;
                runResults.compBinSuccess += tempRun.result.comparisons;
                runResults.runsBinSuccess++;
            } else {
                runResults.timeBinFail += tempRun.time;
                runResults.compBinFail += tempRun.result.comparisons;
                runResults.runsBinFail++;
            }
        }
    }

    system(CLEAR_SCREEN);
    // Print search settings
    cout << "Search done\n"
         << "Searching setting:\n\n"
         << "***********************\n"
         << "Searches per algorithm: " << runResults.searchRuns
         << "\nLength of lists: " << runResults.listSize
         << "\nLargest possible number in list: " << runResults.maxNumInList
         << "\nTotal time: " << runResults.timeBinFail + runResults.timeBinSuccess + runResults.timeSeqFail + runResults.timeSeqSuccess
         << "\n\n";
    // Print search results for sequential search
    cout << "Sequential Search:\n"
         << "***********************\n"
         << "Status: Successful\n"
         << "Avg time per run: " << (float)(runResults.timeSeqSuccess / (float)runResults.searchRuns)
         << "\nAvg comparisons per search: " << runResults.compSeqSuccess / runResults.runsSeqSuccess
         << "\nSearches: " << runResults.runsSeqSuccess
         << "\n\n"
         << "Status: Unsuccessful\n"
         << "Avg time per run: " << (float)(runResults.timeSeqFail / (float)runResults.searchRuns)
         << "\nAvg comparisons per search: " << runResults.compSeqFail / runResults.runsSeqFail
         << "\nSearches: " << runResults.runsSeqFail
         << "\n\n";

    // Print search results for binary search
    cout << "Binary Search:\n"
         << "***********************\n"
         << "Status: Successful\n"
         << "Avg time per run: " << (float)(runResults.timeBinSuccess / (float)runResults.searchRuns)
         << "\nAvg comparisons per search: " << runResults.compBinSuccess / runResults.runsBinSuccess
         << "\nSearches: " << runResults.runsBinSuccess
         << "\n\n"
         << "Status: Unsuccessful\n"
         << "Avg time per run: " << (float)(runResults.timeBinFail / (float)runResults.searchRuns)
         << "\nAvg comparisons per search: " << runResults.compBinFail / runResults.runsBinFail
         << "\nSearches: " << runResults.runsBinFail
         << "\n\n";
    if (!preset) {
        system(PAUSE_COMMAND);
    }
}
// Function to perform a sequential search on a list for a given key
searchResult seqSearch(const List<unsigned int> &list, unsigned int key) {
    // Create an instance of searchResult to store the search results
    searchResult res;

    // Temporary variable to store the current element from the list
    unsigned int temp;

    // Loop through each element in the list
    for (unsigned int i = 0; i < list.size(); i++) {
        // Retrieve the element at the current index and store it in temp
        list.retrieve(i, temp);

        // Increment the comparison count
        res.comparisons++;

        // Check if the retrieved element matches the key
        if (temp == key) {
            // If a match is found, set the success flag to true
            res.success = true;

            // Store the position where the key was found
            res.position = i;

            // Exit the loop as the key has been found
            break;
        }
    }

    // Return the search result containing success flag, position, and comparisons count
    return res;
}
// Function to perform a binary search on a sorted list for a given key
searchResult binSearch(const List<unsigned int> &list, unsigned int key) {
    // Create an instance of searchResult to store the search results
    searchResult res;
    res.success = false; // Initialize the success flag to false

    // Initialize the bottom and top indices for the binary search
    int bottom = 0;
    int top = list.size() - 1;
    unsigned int x; // Temporary variable to store the current element from the list

    // Loop to perform binary search
    while (bottom <= top) {
        // Calculate the middle index
        int mid = (bottom + top) / 2;

        // Retrieve the element at the middle index and store it in x
        list.retrieve(mid, x);

        // Increment the comparison count
        res.comparisons++;

        // Check if the retrieved element matches the key
        if (x == key) {
            // If a match is found, set the success flag to true
            res.success = true;

            // Store the position where the key was found
            res.position = mid;

            // Return the search result immediately
            return res;
        }
            // If the retrieved element is greater than the key, adjust the top index
        else if (x > key) {
            top = mid - 1;
        }
            // If the retrieved element is less than the key, adjust the bottom index
        else {
            bottom = mid + 1;
        }
    }

    // Return the search result containing the success flag, position, and comparisons count
    return res;
}
// Initialize lists for search testing
void initLists(int length, List<unsigned int> &odd_list, List<unsigned int> &even_list) {
    for (int i = 0; i < length; i++) {
        odd_list.insert(i, ((i + 1) * 2) - 1);  // Inserting odd numbers: 1, 3, 5, ..., (2*length - 1)
        even_list.insert(i, (i + 1) * 2);       // Inserting even numbers: 2, 4, 6, ..., (2*length)
    }
}
// Print search result
void printSearchResult(searchResult &printThis)
{
    if (printThis.success)
    {
        cout << "Number found in position: " << printThis.position << "\n";
    }
    else
    {
        cout << "Number was not found\n";
    }
}

// ********************SORTING********************
// Function to perform a manual sort
void manualSort(SortAlgorithm sortingAlgorithm) {
    List<unsigned int> sortable;
    unsigned int listSize;
    int resultPrintRange;
    sortResult res;
    Timer testTimer;

    // Get the size of the list to be sorted from the user
    cout << "Size for sortable list? ";
    cin >> listSize;

    // Get the range for printing the test slice of the list
    cout << "Size for test print? (max sortable list size, default 200): ";
    cin >> resultPrintRange;

    // Check if the input is within the valid range; otherwise, set it to 200
    if (resultPrintRange <= 0 || resultPrintRange > listSize) {
        resultPrintRange = 200;
    }

    // Initialize the list with random values
    cout << "Initializing list...\n";
    testTimer.reset();
    initRandomList(listSize, sortable);  // Generate random list
    cout << "List initialized. Initialization time: " << testTimer.elapsed_time() << endl;

    // Print the initial part of the list for verification
    cout << "Initial list slice:\n";
    printTestRange(0, sortable, resultPrintRange);

    // Sort the list using the specified sorting algorithm
    if (sortingAlgorithm == QUICKSORT) {
        cout << "Sorting with QuickSort...\n";
        testTimer.reset();
        res = quickSort(sortable, res, 0, listSize - 1);
        res.time = testTimer.elapsed_time();
        cout << "List is sorted properly (QuickSort)\n";
    } else if (sortingAlgorithm == INSERTIONSORT) {
        cout << "Sorting with InsertionSort...\n";
        testTimer.reset();
        res = insertionSort(sortable, testTimer, false);
        res.time = testTimer.elapsed_time();
        cout << "List is sorted properly (InsertionSort)\n";
    } else {
        cout << "Invalid sorting algorithm!\n";
        return;
    }

    // Print the sorted part of the list for verification
    cout << "Sorted list slice:\n";
    printTestRange(0, sortable, resultPrintRange);

    // Print performance metrics
    cout << "Operations: " << res.assignments + res.comparisons
         << "\nAssignments: " << res.assignments
         << "\nComparisons: " << res.comparisons
         << "\nTime: " << res.time << " ms\n";

    // Pause the system and clear the screen for a clean exit
    system(PAUSE_COMMAND);
    system(CLEAR_SCREEN);
}
// Sort test comparison function
void sortTests(unsigned int listSize, unsigned int printRange, unsigned int sortCycles) {
    testRunResultsSort TotalResult;  // Structure to hold total results
    vector<sortResult> results;  // Vector to store individual sorting results
    Timer testTimer;
    bool preset = (listSize != 0);

    // Handle user input if not preset
    if (!preset) {
        // Get input from the user
        cout << "The sortable list size: ";
        cin >> listSize;
        cout << "Print range? max sortable list size : ";
        cin >> printRange;
        cout << "How many cycles: ";
        cin >> sortCycles;

        // Check if print range is larger than the list size and set default value
        if (listSize < printRange) {
            printRange = listSize;
        } else if (printRange == 0 || printRange > listSize) {
            printRange = 200;
        }
    }

    // Perform sorting cycles
    for (unsigned int i = 0; i < sortCycles; ++i) {
        List<unsigned int> unsorted;
        cout << "Init list for sorting" << endl;
        initRandomList(listSize, unsorted);

        // Create a copy of the unsorted list for quick sort that
        // both algorithms can be tested with the same list
        List<unsigned int> unsorted_quick(unsorted);

        // Insertion Sort
        cout << "Performing Insertion Sort" << endl;
        printTestRange(printRange, unsorted, printRange);
        sortResult insertionSortResult = insertionSort(unsorted, testTimer, preset);
        insertionSortResult.isSorted = isListSorted(unsorted); // Set isSorted based on the result
        results.push_back(insertionSortResult);
        printTestRange(printRange, unsorted, printRange);
        if (insertionSortResult.isSorted) {
            cout << "List is sorted properly (InsertionSort)\n";
        } else {
            cout << "List is not sorted, something went wrong (InsertionSort)\n";
            system(PAUSE_COMMAND);
        }

        // Quick Sort
        sortResult temp = {};
        cout << "Performing Quick Sort" << endl;
        printTestRange(printRange, unsorted_quick, printRange);
        testTimer.reset();
        quickSort(unsorted_quick, temp, 0, unsorted_quick.size() - 1);
        temp.time = testTimer.elapsed_time();
        temp.algorithm = 'Q';
        temp.isSorted = isListSorted(unsorted_quick); // Set isSorted based on the result
        results.push_back(temp);
        printTestRange(printRange, unsorted_quick, printRange);
        if (temp.isSorted) {
            cout << "List is sorted properly (QuickSort)\n";
        } else {
            cout << "List is not sorted, something went wrong (QuickSort)\n";
            system(PAUSE_COMMAND);
        }
    }

    // Aggregate results
    for (const auto &result : results) {
        if (result.algorithm == 'I') {
            TotalResult.runsInsertionSort++;
            TotalResult.timeInsertionSort += result.time;
            TotalResult.compInsertionSort += result.comparisons;
            TotalResult.assignmentsInsertionSort += result.assignments;
        } else if (result.algorithm == 'Q') {
            TotalResult.runsQuickSort++;
            TotalResult.timeQuickSort += result.time;
            TotalResult.compQuickSort += result.comparisons;
            TotalResult.assignmentsQuickSort += result.assignments;
        }
    }

    TotalResult.listSize = listSize;
    TotalResult.SortRuns = sortCycles;


    // Print aggregated results
    cout << "Sorting done\n"
         << "Sorting settings:\n"
         << "***********************\n"
         << "Sorts per algorithm: " << TotalResult.SortRuns
         << "\nLength of lists: " << TotalResult.listSize
         << "\nTotal time: " << TotalResult.timeInsertionSort + TotalResult.timeQuickSort
         << "\n\n";
    cout << "Quick Sort:\n"
         << "***********************\n"
         << "Sorting successful: " << TotalResult.runsQuickSort << " times\n"
         << "Sorting unsuccessful: " << TotalResult.SortRuns - TotalResult.runsQuickSort << " times\n"
         << "Avg time per run: " << (TotalResult.timeQuickSort / (float)TotalResult.SortRuns)
         << "\nAvg operations per sort: " << (TotalResult.assignmentsQuickSort + TotalResult.compQuickSort) / TotalResult.SortRuns
         << "\nAvg comparisons per sort: " << TotalResult.compQuickSort / TotalResult.SortRuns
         << "\nAvg assignments per sort: " << TotalResult.assignmentsQuickSort / TotalResult.SortRuns
         << "\n\n";
    cout << "Insertion Sort:\n"
         << "***********************\n"
         << "Sorting successful: " << TotalResult.runsInsertionSort << " times\n"
         << "Sorting unsuccessful: " << TotalResult.SortRuns - TotalResult.runsInsertionSort << " times\n"
         << "Avg time per run: " << (TotalResult.timeInsertionSort / (float)TotalResult.SortRuns)
         << "\nAvg operations per sort: " << (TotalResult.assignmentsInsertionSort + TotalResult.compInsertionSort) / TotalResult.SortRuns
         << "\nAvg comparisons per sort: " << TotalResult.compInsertionSort / TotalResult.SortRuns
         << "\nAvg assignments per sort: " << TotalResult.assignmentsInsertionSort / TotalResult.SortRuns
         << "\n\n";
    if (!preset) {
        system(PAUSE_COMMAND); // Pause the system if not preset
    }
}
// Function to perform quick sort on a list
sortResult quickSort(List<unsigned int> &list, sortResult &result, unsigned int startingPos, unsigned int endingPos) {
    // Base case: if the starting position is greater than or equal to the ending position, return the result
    if (startingPos >= endingPos) {
        return result;
    }

    // Choose the starting element as the pivot
    unsigned int pivotIndex = startingPos;
    unsigned int pivot;
    list.retrieve(pivotIndex, pivot);  // Retrieve the pivot element

    // Initialize pointers for the partitioning process
    unsigned int i = startingPos + 1;
    unsigned int j = endingPos;

    // Partition the list around the pivot
    while (i <= j) {
        unsigned int listToSort, listToCompare;
        list.retrieve(i, listToSort);
        list.retrieve(j, listToCompare);
        result.comparisons++;

        // Move the pointers i and j towards each other
        if (listToSort <= pivot) {
            i++;
        } else if (listToCompare >= pivot) {
            j--;
        } else {
            // Swap elements at positions i and j
            list.remove(i, listToSort);
            list.insert(i, listToCompare);
            list.remove(j, listToCompare);
            list.insert(j, listToSort);
            i++;
            j--;
            result.assignments += 2;  // Increment the assignment count
        }
    }

    // Move the pivot to its correct position
    list.remove(startingPos, pivot);
    list.insert(j, pivot);
    result.assignments++;  // Increment the assignment count

    // Recursively sort the left and right sublists
    if (j > startingPos) result = quickSort(list, result, startingPos, j - 1);  // Sort the left sublist
    if (j < endingPos) result = quickSort(list, result, j + 1, endingPos);  // Sort the right sublist

    // Return the sorting result containing the algorithm type, comparison count, and elapsed time
    return result;
}
// Function to perform insertion sort on a list
sortResult insertionSort(List<unsigned int> &list, Timer &timing, bool print) {
    // Create an instance of sortResult to store the sorting results
    sortResult res;
    unsigned int listToSort, listToCompare;

    // Reset the timer to start measuring the sorting time
    timing.reset();

    // Set the algorithm type to 'I' for Insertion Sort
    res.algorithm = 'I';

    // Start the insertion sort algorithm
    for (auto i = 1; i < list.size(); i++) {
        // Retrieve the element at position i to be sorted
        list.retrieve(i, listToSort);

        // Initialize j to the position before i
        int j = i - 1;

        // Inner loop to compare and shift elements
        while (j >= 0) {
            // Retrieve the element at position j to compare
            list.retrieve(j, listToCompare);

            // Increment the comparison count
            res.comparisons++;

            // Optionally print the comparison count every 100000 comparisons
            if (res.comparisons % 100000 == 0 && print) {
                // Uncomment the following line to print the number of comparisons
                // cout << "Comparisons done: " << res.comparisons << endl;
            }

            // If the current element is greater than or equal to the element to sort, break the loop
            if (listToSort >= listToCompare) {
                break;
            }

            // Move the current element one position forward to make space for the element to sort
            list.remove(j, listToCompare);
            list.insert(j + 1, listToCompare);

            // Decrement j to continue shifting elements
            j--;
        }

        // Insert the element to sort at its correct position
        list.remove(j + 1, listToCompare);  // Use a dummy variable for the remove operation
        list.insert(j + 1, listToSort);
    }

    // Record the elapsed time for the sorting process
    res.time = timing.elapsed_time();

    // Return the sorting result containing the algorithm type, comparison count, and elapsed time
    return res;
}
// Initialize a random list for sorting
void initRandomList(int length, List<unsigned int> &list) {
    for (int i = 0; i < length; i++) {
        list.insert(i, rand() % (length * 10)); // Random values between 0 and 10 times the length
    }
}
// Boolean function to check if list is sorted
bool isListSorted(List<unsigned int> &list) {
    unsigned int temp1, temp2;
    for (size_t i = 0; i < list.size() - 1; ++i) {
        list.retrieve(i, temp1);
        list.retrieve(i + 1, temp2);
        if (temp2 < temp1) {
            return false;  // If any element is greater than the next, list is not sorted
        }
    }
    return true;  // List is sorted
}
// Print a range of the list
void printTestRange(int position, List<unsigned int> &list, int size) {
    if (size <= 0) return;

    unsigned int x;
    int j = 0;
    cout << setw(80) << setfill('=') << "=" << endl;

    int list_size = list.size();
    int end = (list_size > size) ? position + size : list_size;

    for (int i = position; i < end; ++i) {
        if (j == 10) {
            cout << endl;
            j = 0;
        }
        j++;
        list.retrieve(i, x);
        cout << setw(8) << left << setfill(' ') << x;
    }
    cout << endl;
}
