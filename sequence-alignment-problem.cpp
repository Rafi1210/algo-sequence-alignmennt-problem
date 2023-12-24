#include<bits/stdc++.h>
using namespace std;

const int MAX_ROWS = 50;
const int MAX_COLS = 50;

int penaltyMatrix[MAX_ROWS][MAX_COLS], gapPenalty, mismatchPenalty, minimumPenalty;
int tracebackMatrix[MAX_ROWS][MAX_COLS];

int minPenalty(int a, int b, int c)
{
    return min(min(a, b), c);
}

int getPenalty(char a, char b, int c)
{
    return (a == b) ? 0 : c;
}

void printAlignmentSeq1(string sequence1, int i, int j)
{
    if (i > 0 && j > 0 && tracebackMatrix[i][j] == 0)
    {
        printAlignmentSeq1(sequence1, i - 1, j - 1);
        cout << sequence1[j - 1];
    }
    else if (i > 0 && tracebackMatrix[i][j] == 1)
    {
        printAlignmentSeq1(sequence1, i - 1, j);
        cout << '_';
    }
    else if (j > 0 && tracebackMatrix[i][j] == 2)
    {
        printAlignmentSeq1(sequence1, i, j - 1);
        cout << sequence1[j - 1];
    }
}

void printAlignmentSeq2(string sequence2, int i, int j)
{
    if (i > 0 && j > 0 && tracebackMatrix[i][j] == 0)
    {
        printAlignmentSeq2(sequence2, i - 1, j - 1);
        cout << sequence2[i - 1];
    }
    else if (i > 0 && tracebackMatrix[i][j] == 1)
    {
        printAlignmentSeq2(sequence2, i - 1, j);
        cout << sequence2[i - 1];
    }
    else if (j > 0 && tracebackMatrix[i][j] == 2)
    {
        printAlignmentSeq1(sequence2, i, j - 1);
        cout << '_';
    }
}

void calculateAlignment(string sequence1, string sequence2, int gapPenalty, int mismatchPenalty)
{
    for (int i = 0; i <= sequence2.length(); i++)
    {
        for (int j = 0; j <= sequence1.length(); j++)
        {
            if (i == 0 && j == 0)
            {
                penaltyMatrix[i][j] = 0;
            }
            else if (i == 0)
            {
                penaltyMatrix[i][j] = penaltyMatrix[i][j - 1] + gapPenalty;
                tracebackMatrix[i][j] = 2;
            }
            else if (j == 0)
            {
                penaltyMatrix[i][j] = penaltyMatrix[i - 1][j] + gapPenalty;
                tracebackMatrix[i][j] = 1;
            }
            else
            {
                int diagonalPenalty = penaltyMatrix[i - 1][j - 1] + getPenalty(sequence2[i - 1], sequence1[j - 1], mismatchPenalty);
                int verticalPenalty = penaltyMatrix[i - 1][j] + gapPenalty;
                int horizontalPenalty = penaltyMatrix[i][j - 1] + gapPenalty;

                penaltyMatrix[i][j] = minPenalty(diagonalPenalty, verticalPenalty, horizontalPenalty);

                if (penaltyMatrix[i][j] == diagonalPenalty)
                {
                    tracebackMatrix[i][j] = 0;
                }
                else if (penaltyMatrix[i][j] == verticalPenalty)
                {
                    tracebackMatrix[i][j] = 1;
                }
                else
                {
                    tracebackMatrix[i][j] = 2;
                }
            }
        }
    }
}
int main()
{
    cout << "\t\t _________________________________________________________________\n";
    cout << "\t\t|\t\t\t\t\t\t\t\t  |\n";
    cout << "\t\t|\t\t Welcome to Sequence Alignment Problem    \t  |\n";
    cout << "\t\t|_________________________________________________________________|\n\n";

    string sequence1, sequence2;

    cout << "Enter Sequence X : ";
    cin >> sequence1;
    cout << "Enter Sequence Y : ";
    cin >> sequence2;
    cout << "Enter Gap Penalty , P(gap) : ";
    cin >> gapPenalty;
    cout << "Enter Mismatch Penalty, P(xy) : ";
    cin >> mismatchPenalty;

    calculateAlignment(sequence1, sequence2, gapPenalty, mismatchPenalty);

    cout << endl;
        cout << "+-------------------+\n";
    cout << "|Total Penalty : " << penaltyMatrix[sequence2.length()][sequence1.length()] << "  |\n";
        cout << "+-------------------+\n";

    cout << "_____________________________________________\n";

            cout << "+--------------------------------------------+\n";
    cout << "|Alignment for Sequence X: ";
    printAlignmentSeq1(sequence1, sequence2.length(), sequence1.length());
    cout << "\n";
            cout << "+--------------------------------------------+\n";
            cout << "+--------------------------------------------+\n";

    cout << "|Alignment for Sequence Y: ";
    printAlignmentSeq2(sequence2, sequence2.length(), sequence1.length());
   cout << "\n";
            cout << "+--------------------------------------------+\n";
    return 0;
}
