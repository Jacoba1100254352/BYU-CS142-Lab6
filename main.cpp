#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

///   Global Variable Array Size Declaration   ///
const int ARRAY_SIZE = 10;

///   Array Functions Declarations   ///
void InitializeHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void InputHotPlate( double[][ARRAY_SIZE] );
void UpdateHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void UpdateTempHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void EqualizePlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE]);
void PrintHotPlate( double[][ARRAY_SIZE] );
void PrintToHotPlateCSV( double[][ARRAY_SIZE] );


/***********
*   Main   *
***********/

int main()
{
    ///   Array Declarations   ///
    double tempHotPlate[ARRAY_SIZE][ARRAY_SIZE];
    double hotPlate[ARRAY_SIZE][ARRAY_SIZE];

    ///   Start Program   ///
    cout << "Hotplate simulator" << "\n" << endl;

    cout << "Printing the initial plate values..." << endl;
    InitializeHotPlate(hotPlate, tempHotPlate);
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Printing plate after one iteration..." << endl;
    UpdateHotPlate(hotPlate, tempHotPlate);
    UpdateTempHotPlate(hotPlate, tempHotPlate);
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Printing final plate..." << endl;
    EqualizePlate( hotPlate, tempHotPlate );
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Writing final plate to \"Hotplate.csv\"..." << endl;
    PrintToHotPlateCSV(hotPlate);
    cout << endl;

    cout << "Printing input plate after 3 updates..." << endl;
    InputHotPlate( hotPlate );
    UpdateTempHotPlate(hotPlate, tempHotPlate);
    for (int i = 0; i < 3; i++)
    {
        UpdateHotPlate(hotPlate, tempHotPlate);
        UpdateTempHotPlate(hotPlate, tempHotPlate);
    }
    PrintHotPlate( hotPlate );

    return 0;
}


/**********************
*   Array Functions   *
**********************/

void InitializeHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] ) // Initialize Hotplate with 0's or 100's
{

    for (int col = 0; col < ARRAY_SIZE; col++)
    {
        for (int row = 0; row < ARRAY_SIZE; row++)
        {
            if ( ( col > 0 && col < 9 ) && (row == 0 || row == 9) )
            {
                tempHotPlate[row][col] = 100.000;
                hotPlate[row][col] = 100.000;
            }
            else
            {
                tempHotPlate[row][col] = 0.000;
                hotPlate[row][col] = 0.000;
            }
        }
    }
}

void InputHotPlate( double hotPlate[][ARRAY_SIZE] ) // Input from TXT file
{
    ifstream inFS;
    inFS.open("Inputplate.txt");
    if (!inFS.is_open())
    {
        throw logic_error("Could not open file Hotplate.csv.");
    }

    for (int col = 0; col < ARRAY_SIZE; col++)
    {
        for (int row = 0; row < ARRAY_SIZE; row++)
        {
            inFS >> hotPlate[col][row];
        }
    }

    inFS.close();
}

void UpdateHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] ) // Updates with the element averages
{
    for ( int col = 1; col < ARRAY_SIZE-1; col++ )
        for (int row = 1; row < ARRAY_SIZE - 1 ; row++)
            hotPlate[col][row] = (tempHotPlate[col-1][row] + tempHotPlate[col+1][row] + tempHotPlate[col][row-1] + tempHotPlate[col][row+1])/4;
}

void UpdateTempHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] ) // Assigns tempHotPlate to hotPlate
{
    for ( int col = 1; col < ARRAY_SIZE-1; col++ )
        for (int row = 1; row < ARRAY_SIZE - 1 ; row++)
            tempHotPlate[col][row] = hotPlate[col][row];
}

void EqualizePlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE]) // Run until there has not been a change of less than 0.1 for each element
{
    bool noChanges = true;

    while (noChanges)
    {
        int numCellsChanged = 0;
        UpdateHotPlate(hotPlate, tempHotPlate);
        for (int col = 1; col < ARRAY_SIZE - 1; col++)
        {
            for (int row = 1; row < ARRAY_SIZE - 1; row++)
            {
                if ( fabs(hotPlate[row][col] - tempHotPlate[row][col] ) < 0.1 )
                {
                    numCellsChanged++;
                }
                if (numCellsChanged == 64)
                {
                    noChanges = false;
                }
            }
        }
        UpdateTempHotPlate(hotPlate, tempHotPlate);
    }
}

void PrintHotPlate( double hotPlate[][ARRAY_SIZE]) // Outputs the hotPlate 2D array
{
    for ( int col = 0; col < ARRAY_SIZE; col++ )
    {
        for ( int row = 0; row < ARRAY_SIZE; row++ )
        {
            cout << fixed << setprecision(3) << right << setw(9) << hotPlate[col][row];
            cout << ((row != ARRAY_SIZE - 1) ? ',' : '\n');
        }
    }
}

void PrintToHotPlateCSV( double hotPlate[][ARRAY_SIZE]) // Print to CSV file
{
    ofstream outFS;

    outFS.open("Hotplate.csv");
    if (!outFS.is_open())
    {
        throw logic_error("Could not open file Hotplate.csv.");
    }

    for ( int col = 0; col < ARRAY_SIZE; col++ )
    {
        for ( int row = 0; row < ARRAY_SIZE; row++ )
        {
            outFS << fixed << setprecision(3) << right << setw(9) << hotPlate[col][row];
            if (row != ARRAY_SIZE - 1)
            {
                outFS << ",";
            }
            else
            {
                outFS << endl;
            }
        }
    }

    outFS.close();
}











/*
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int ARRAY_SIZE = 10;

///   Array Functions   ///
void InitializeHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void InputHotPlate( double[][ARRAY_SIZE] );
void UpdateHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void UpdateTempHotPlate( double[][ARRAY_SIZE], double[][ARRAY_SIZE] );
void PrintHotPlate( double[][ARRAY_SIZE] );
void PrintToHotPlateCSV( double[][ARRAY_SIZE] );

***********
*   Main   *
***********

int main()
{
    bool tempVariation = true;
    bool noPreviousMinorChanges = true;
    double tempHotPlate[ARRAY_SIZE][ARRAY_SIZE];
    double hotPlate[ARRAY_SIZE][ARRAY_SIZE];

    cout << "Hotplate simulator" << "\n" << endl;

    cout << "Printing the initial plate values..." << endl;
    InitializeHotPlate(hotPlate, tempHotPlate);
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Printing plate after one iteration..." << endl;
    UpdateHotPlate(hotPlate, tempHotPlate);
    UpdateTempHotPlate(hotPlate, tempHotPlate);
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Printing final plate..." << endl;
    while (tempVariation)
    {
        noPreviousMinorChanges = true; // Determines iteration if any variation was detected
        for (int col = 1; col < ARRAY_SIZE - 1; col++)
        {
            for (int row = 1; row < ARRAY_SIZE - 1; row++)
            {
                double averageValue = (tempHotPlate[col - 1][row] + tempHotPlate[col][row - 1] + tempHotPlate[col + 1][row] + tempHotPlate[col][row + 1]) / 4;
                if (noPreviousMinorChanges && abs(hotPlate[col][row] - averageValue) > 0.1) //if minor change, then
                {
                    noPreviousMinorChanges = false;
                }
                hotPlate[col][row] = averageValue; //updating hotplate in realtime
            }
        }
        if (noPreviousMinorChanges)
        {
            tempVariation = false;
        }

        UpdateTempHotPlate(hotPlate, tempHotPlate);
    }
    PrintHotPlate(hotPlate);
    cout << endl;

    cout << "Writing final plate to \"Hotplate.csv\"..." << endl;
    PrintToHotPlateCSV(hotPlate);
    cout << endl;

    cout << "Printing input plate after 3 updates..." << endl;
    InputHotPlate( hotPlate );
    UpdateTempHotPlate(hotPlate, tempHotPlate);
    for (int i = 0; i < 3; i++)
    {
        UpdateHotPlate(hotPlate, tempHotPlate);
        UpdateTempHotPlate(hotPlate, tempHotPlate);
    }
    PrintHotPlate( hotPlate );

    return 0;
}


**********************
*   Array Functions   *
**********************

void InitializeHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] )
{

    for (int col = 0; col < ARRAY_SIZE; col++)
    {
        for (int row = 0; row < ARRAY_SIZE; row++)
        {
            if ( ( col > 0 && col < 9 ) && (row == 0 || row == 9) )
            {
                tempHotPlate[row][col] = 100.000;
                hotPlate[row][col] = 100.000;
            }
            else
            {
                tempHotPlate[row][col] = 0.000;
                hotPlate[row][col] = 0.000;
            }
        }
    }
}

void InputHotPlate( double hotPlate[][ARRAY_SIZE] )
{
    ifstream inFS;
    inFS.open("Inputplate.txt");
    if (!inFS.is_open())
    {
        throw logic_error("Could not open file Hotplate.csv.");
    }

    for (int col = 0; col < ARRAY_SIZE; col++)
    {
        for (int row = 0; row < ARRAY_SIZE; row++)
        {
            inFS >> hotPlate[col][row];
        }
    }

    inFS.close();
}

void UpdateHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] )
{
    for ( int col = 1; col < ARRAY_SIZE - 1; col++ )
    {
        for (int row = 1; row < ARRAY_SIZE - 1; row++)
        {
            hotPlate[col][row] = (tempHotPlate[col-1][row] + tempHotPlate[col+1][row] + tempHotPlate[col][row-1] + tempHotPlate[col][row+1])/4.000;
        }
    }
}

void UpdateTempHotPlate( double hotPlate[][ARRAY_SIZE], double tempHotPlate[][ARRAY_SIZE] )
{
    for ( int col = 1; col < ARRAY_SIZE - 1; col++ )
    {
        for (int row = 1; row < ARRAY_SIZE - 1; row++)
        {
            tempHotPlate[col][row] = hotPlate[col][row];
        }
    }
}

void PrintHotPlate( double hotPlate[][ARRAY_SIZE])
{
    for ( int col = 0; col < ARRAY_SIZE; col++ )
    {
        for ( int row = 0; row < ARRAY_SIZE; row++ )
        {
            cout << fixed << setprecision(3) << right << setw(9) << hotPlate[col][row];
            if (row != ARRAY_SIZE - 1)
            {
                cout << ",";
            }
            else
            {
                cout << endl;
            }
        }
    }
}

void PrintToHotPlateCSV( double hotPlate[][ARRAY_SIZE])
{
    ofstream outFS;

    outFS.open("Hotplate.csv");
    if (!outFS.is_open())
    {
        throw logic_error("Could not open file Hotplate.csv.");
    }

    for ( int col = 0; col < ARRAY_SIZE; col++ )
    {
        for ( int row = 0; row < ARRAY_SIZE; row++ )
        {
            outFS << fixed << setprecision(3) << right << setw(9) << hotPlate[col][row];
            if (row != ARRAY_SIZE - 1)
            {
                outFS << ",";
            }
            else
            {
                outFS << endl;
            }
        }
    }

    outFS.close();
}
*/
