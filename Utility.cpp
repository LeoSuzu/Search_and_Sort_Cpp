//
// Created by Leo Suzuki on 7.5.2024.
//

// All necessary includes are in the Utility header file for avoiding multiple includes and conflicts
#include "Utility.h"

bool user_says_yes() {
    int c;
    bool initial_response = true;

    do { // Loop until an appropriate input is received.
        cout << "Are you sure?" << endl;
        if (initial_response)
            cout << " (y,n)? " << flush;
        else
            cout << "Respond with either y or n: " << flush;

        do { // Ignore white space.
            c = cin.get();
        } while (c == '\n' || c == ' ' || c == '\t');

        initial_response = false;
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');

    return (c == 'y' || c == 'Y');
}

void print_menu()
{
    cout << "1. Manual Sequential Search\n"
         << "2. Manual Binary Search\n"
         << "3. Quick Sort\n"
         << "4. Insertion sort\n"
         << "5. Search comparison test\n"
         << "6. Sorting comparison test\n"
         << "7. Multiple searching tests (short version)\n"
         << "8. Multiple searching tests (long version)\n"
         << "9. Multiple sorting tests (short version) \n"
         << "10. Multiple sorting tests (long version)\n"
         << "11. Quit\n"
         << "Please choose number: ";
}


