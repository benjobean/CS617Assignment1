// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <iomanip>
#include <array>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Assignment1.h"


using namespace std;

int multiple_bf;
int add_bf;
int multiple_recursive;
int add_recursive;
int multiple_strassens;
int add_strassens;

//int** BruteForce(int**, int**);

vector<vector<int>> ParseInput(string fileName) {
    ifstream inFile(fileName);
    vector<vector<int>> matrixvector;
    if (inFile.is_open())
    {
        string line;
        vector<int> temp;
        int count = 0;
        while (getline(inFile, line))
        {
            stringstream linestream(line);
            string value;
            while (getline(linestream, value, ',')) {
                temp.push_back(stoi(value));   
            }
            matrixvector.push_back(temp);
            temp.clear();
        }
    }

    /*for (auto row_obj : matrixvector)
    {
        for (auto elem : row_obj)
        {
            cout << elem << " ";
        }
        cout << endl;
    }*/
    return matrixvector;
}

void OutputToFile(vector<vector<int>> matrixvector, string file_name) {
    ofstream outfile(file_name);
    for (auto row_obj : matrixvector)
    {
        for (auto elem : row_obj)
        {
            outfile << elem << "\t";
        }
        outfile << endl;
    }
    outfile.close();
}


// Testing ---------------------

//Brute Force Test
bool BruteForceCorrect() {
    int n = 6;
    int** C;
    C = new int* [n];
    int count = 0;
    for (int z = 0; z < n; z++) {//need to fix array size and initialize to 0
        C[z] = new int[n];
        for (int i = 0; i < n; i++) {
            C[z][i] = z;
            count++;
        }
    }
    cout << count << endl;
    cout << *(&C + 1) - C << endl;
    cout << *(&C + 1) - C << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
    return false;
}



int main()
{

    std::cout << "Hello World!\n";
    //vector<vector<int>> input = ParseInput("");
    //OutputToFile(input, "test.txt");
    BruteForceCorrect();
}



//
////Brute Force Algorithm
//int** BruteForce(int **A, int **B) { //need to fix array sizes
//    int n = sizeof(A) / sizeof(A[0]);
//    int **C;
//    for (int z = 0; z < n; z++)//need to fix array size and initialize to 0
//        C[z] = new int[n];
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            C[i, j] = 0;
//            for (int k = 1; k <= n; k++) {
//                C[i, j] = C[i, j] + (A[i][k] * B[k][j]);
//                multiple_bf++;
//                add_bf++;
//            }
//        }
//    }
//
//    return (C);
//}
//
////Recursive Algorithm
//int** RecursiveAlgorithm(int** A, int** B) {//need to fix array sizes
//    int n = sqrt((sizeof(A) / sizeof(A[0])));
//    int **C;
//    C = new int*[n];
//    for (int z = 0; z < n; z++)//need to fix array size and initialize to 0
//        C[z] = new int[n];
//    if (n == 1) {
//        C = A * B; //make function to multiply matrices
//        multiple_recursive++;
//    }
//    else {
//        int** A_11;
//        int** A_12;
//        int** A_21;
//        int** A_22;
//        int** B_11;
//        int** B_12;
//        int** B_21;
//        int** B_22;
//        int** C_11;
//        int** C_12;
//        int** C_21;
//        int** C_22;
//        A_11 = new int*[n];
//        A_12 = new int*[n];
//        A_21 = new int*[n];
//        A_22 = new int*[n];
//        B_11 = new int*[n];
//        B_12 = new int*[n];
//        B_21 = new int*[n];
//        B_22 = new int*[n];
//        C_11 = new int*[n];
//        C_12 = new int*[n];
//        C_21 = new int*[n];
//        C_22 = new int*[n];
//        for (int z = 0; z < n; z++) {//need to fix array size and initialize to 0
//            A_11[z] = new int[n];
//            A_12[z] = new int[n];
//            A_21[z] = new int[n];
//            A_22[z] = new int[n];
//            B_11[z] = new int[n];
//            B_12[z] = new int[n];
//            B_21[z] = new int[n];
//            B_22[z] = new int[n];
//            C_11[z] = new int[n];
//            C_12[z] = new int[n];
//            C_21[z] = new int[n];
//            C_22[z] = new int[n];
//        }
//
//        RecursiveAlgorithm(A_11, B_11);
//
//        C_11 = RecursiveAlgorithm(A_11, B_11) + RecursiveAlgorithm(A_12, B_21);
//        C_12 = RecursiveAlgorithm(A_11, B_12) + RecursiveAlgorithm(A_12, B_22);
//        C_21 = RecursiveAlgorithm(A_21, B_11) + RecursiveAlgorithm(A_22, B_21);
//        C_22 = RecursiveAlgorithm(A_21, B_12) + RecursiveAlgorithm(A_22, B_22);
//        add_recursive = add_recursive + (4 * (n / 2) ^ 2);
//
//             /*
//    C[1:(n / 2), 1:(n / 2)]             <- C.11
//    C[1:(n / 2), ((n / 2) + 1):n]       <- C.12
//    C[((n / 2) + 1):n, 1:(n / 2)]       <- C.21
//    C[((n / 2) + 1):n, ((n / 2) + 1):n] <- C.22
//            
//            */
//        return (C);
//
//    }
//}
//
////Strassen's Algorithm
//
//int StrassensAlgorithm(int A[], int B[]) {//need to fix array sizes
//    int n = sqrt(A.length());
//    int C[] = { 0 }; //need to fix array size and initialize to 0
//    if (n == 1) {
//        C = A * B;
//        multiple_strassens++;
//    }
//    else {
//        int A_11[]; // may need to make a function for the copies
//        int A_12[];
//        int A_21[];
//        int A_22[];
//        int B_11[];
//        int B_12[];
//        int B_21[];
//        int B_22[];
//    
//        //need to create functions to add and subtract matrixces
//        /*
//    S.1  <- B.12 - B.22
//    S.2  <- A.11 + A.12
//    S.3  <- A.21 + A.22
//    S.4  <- B.21 - B.11
//    S.5  <- A.11 + A.22
//    S.6  <- B.11 + B.22
//    S.7  <- A.12 - A.22
//    S.8  <- B.21 + B.22
//    S.9  <- A.11 - A.21
//    S.10 <- B.11 + B.12
//        */
//        add_strassens = add_strassens + (10 * (n / 2) ^ 2);
//
//        int P_1[] = StrassensAlgorithm(A_11, S_1);
//        int P_2[] = StrassensAlgorithm(S_2, B_22);
//        int P_3[] = StrassensAlgorithm(S_3, B_11);
//        int P_4[] = StrassensAlgorithm(A_22, S_4);
//        int P_5[] = StrassensAlgorithm(S_5, S_6);
//        int P_6[] = StrassensAlgorithm(S_7, S_8);
//        int P_7[] = StrassensAlgorithm(S_9, S_10);
//
//        /*
//    C.11 <- P.5 + P.4 - P.2 + P.6
//    C.12 <- P.1 + P.2
//    C.21 <- P.3 + P.4
//    C.22 <- P.5 + P.1 - P.3 - P.7
//        */
//        add_strassens = add_strassens + (8 * (n / 2) ^ 2);
//
//
//
//        /*
//C[1:(n / 2), 1:(n / 2)]             <- C.11
//C[1:(n / 2), ((n / 2) + 1):n]       <- C.12
//C[((n / 2) + 1):n, 1:(n / 2)]       <- C.21
//C[((n / 2) + 1):n, ((n / 2) + 1):n] <- C.22
//
//        */
//
//        return(C);    
//    }
//}

//function to copy matrices

//function to add matrices

//function to subtract matrices


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
