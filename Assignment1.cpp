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

//vector<vector<int>> BruteForce(vector<vector<int>>, vector<vector<int>>);

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

int main()
{

    std::cout << "Hello World!\n";
    vector<vector<int>> input = ParseInput("");
    OutputToFile(input, "test.txt");
}




//Brute Force Algorithm
vector<vector<int>> BruteForce(vector<vector<int>> A, vector<vector<int>> B) { //need to fix array sizes
    int n = A.size();
    vector<vector<int>> C;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
                multiple_bf++;
                add_bf++;
            }
        }
    }

    return (C);
}

//Recursive Algorithm
vector<vector<int>> RecursiveAlgorithm(vector<vector<int>> A, vector<vector<int>> B) {//need to fix array sizes
    int n = sqrt(A.size());
    vector<vector<int>> C;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = 0;
        }
    }
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; //make function to multiply matrices
        multiple_recursive++;
    }
    else {
        vector<vector<int>> A_11;
        vector<vector<int>> A_12;
        vector<vector<int>> A_21;
        vector<vector<int>> A_22;
        vector<vector<int>> B_11;
        vector<vector<int>> B_12;
        vector<vector<int>> B_21;
        vector<vector<int>> B_22;
        vector<vector<int>> C_11;
        vector<vector<int>> C_12;
        vector<vector<int>> C_21;
        vector<vector<int>> C_22;


        RecursiveAlgorithm(A_11, B_11);

        C_11 = Add(RecursiveAlgorithm(A_11, B_11), RecursiveAlgorithm(A_12, B_21));
        C_12 = Add(RecursiveAlgorithm(A_11, B_12), RecursiveAlgorithm(A_12, B_22));
        C_21 = Add(RecursiveAlgorithm(A_21, B_11), RecursiveAlgorithm(A_22, B_21));
        C_22 = Add(RecursiveAlgorithm(A_21, B_12), RecursiveAlgorithm(A_22, B_22));
        add_recursive = add_recursive + (4 * (n / 2) ^ 2);

             /*
    C[1:(n / 2), 1:(n / 2)]             = C_11
    C[1:(n / 2), ((n / 2) + 1):n]       = C_12
    C[((n / 2) + 1):n, 1:(n / 2)]       = C_21
    C[((n / 2) + 1):n, ((n / 2) + 1):n] = C_22
            
            */
        return (C);

    }
}

//Strassen's Algorithm

vector<vector<int>> StrassensAlgorithm(vector<vector<int>> A, vector<vector<int>> B) {//need to fix array sizes
    int n = sqrt(A.size());
    vector<vector<int>> C;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            C[i][j] = 0;
        }
    }
    if (n == 1) {
        C = A * B;
        multiple_strassens++;
    }
    else {
        vector<vector<int>> A_11; // may need to make a function for the copies
        vector<vector<int>> A_12;
        vector<vector<int>> A_21;
        vector<vector<int>> A_22;
        vector<vector<int>> B_11;
        vector<vector<int>> B_12;
        vector<vector<int>> B_21;
        vector<vector<int>> B_22;
    
        //need to create functions to add and subtract matrixces
        
        vector<vector<int>> S_1 = Sub(B_12, B_22);
        vector<vector<int>> S_2 = Add(A_11, A_12);
        vector<vector<int>> S_2 = Add(A_11, A_12);
        vector<vector<int>> S_3 = Add(A_21, A_22);
        vector<vector<int>> S_4 = Sub(B_21, B_11);
        vector<vector<int>> S_5 = Add(A_11, A_22);
        vector<vector<int>> S_6 = Add(B_11, B_22);
        vector<vector<int>> S_7 = Sub(A_12, A_22);
        vector<vector<int>> S_8 = Add(B_21, B_22);
        vector<vector<int>> S_9 = Sub(A_11, A_21);
        vector<vector<int>> S_10 = Add(B_11, B_12);
        
        add_strassens = add_strassens + (10 * (n / 2) ^ 2);

        vector<vector<int>> P_1 = StrassensAlgorithm(A_11, S_1);
        vector<vector<int>> P_2 = StrassensAlgorithm(S_2, B_22);
        vector<vector<int>> P_3 = StrassensAlgorithm(S_3, B_11);
        vector<vector<int>> P_4 = StrassensAlgorithm(A_22, S_4);
        vector<vector<int>> P_5 = StrassensAlgorithm(S_5, S_6);
        vector<vector<int>> P_6 = StrassensAlgorithm(S_7, S_8);
        vector<vector<int>> P_7 = StrassensAlgorithm(S_9, S_10);

        
        vector<vector<int>> C_11 = Add(Sub(Add(P_5, P_4), P_2), P_6);
        vector<vector<int>> C_12 = Add(P_1, P_2);
        vector<vector<int>> C_21 = Add(P_3, P_4);
        vector<vector<int>> C_22 = Sub(Sub(Add(P_5, P_1), P_3), P_7);
        
        add_strassens = add_strassens + (8 * (n / 2) ^ 2);



        /*
C[1:(n / 2), 1:(n / 2)]             = C_11
C[1:(n / 2), ((n / 2) + 1):n]       = C_12
C[((n / 2) + 1):n, 1:(n / 2)]       = C_21
C[((n / 2) + 1):n, ((n / 2) + 1):n] = C_22

        */

        return(C);    
    }
}

//function to copy matrices






//function to add matrices
vector<vector<int>> Add(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = (A[i][j] + B[i][j]);
        }
    }
    return (C);
}



//function to subtract matrices
vector<vector<int>> Sub(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = (A[i][j] - B[i][j]);
        }
    }
    return (C);
}



