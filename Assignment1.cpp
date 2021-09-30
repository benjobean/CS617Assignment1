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

// Function Prototypes
vector<vector<int>> BruteForce(vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> RecursiveAlgorithm(vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> StrassensAlgorithm(vector<vector<int>> A, vector<vector<int>> B);

int main()
{

    std::cout << "Hello World!\n";
    vector<vector<int>> input = ParseInput("Book1.csv");
    cout << "Parse Successful\n";
    vector<vector<int>> BF = BruteForce(input, input);
    //vector<vector<int>> RE = RecursiveAlgorithm(input, input);
    OutputToFile(BF, "test.txt");

}

//function to copy matrices
void Partition(vector<vector<int>>& C, vector<vector<int>> A, int startx, int starty, int endx, int endy) {
    int countx = 0;
    int county = 0;
    for (int i = startx; i <= endx; i++) {

        for (int j = starty; j <= endy; j++) {
            C[i][j] = A[countx][county];
            county++;
        }
        countx++;
    }


    return;
}

vector<vector<int>> Copy(vector<vector<int>> A, int startx, int starty, int endx, int endy) {
    int n = (endx - startx); //A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    int countx = 0;
    int county = 0;
    for (int i = startx; i <= endx; i++) {

        for (int j = starty; j <= endy; j++) {
            C[countx][county] = A[i][j];
            county++;
        }
        countx++;
    }
    return(C);
}

//function to add matrices
vector<vector<int>> Add(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
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
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = (A[i][j] - B[i][j]);
        }
    }
    return (C);
}

//Brute Force Algorithm
vector<vector<int>> BruteForce(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    //cout << "n =" << n << endl;
    vector<vector<int>> C(n, vector<int>(n, 0)); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j]=0;
            for (int k = 0; k < n; k++) {
                C[i][j] = C[i][j] + (A[i][k] * B[k][j]);
                multiple_bf++;
                add_bf++;
            }
        }
    }

    return (C);
}

//Recursive Algorithm
vector<vector<int>> RecursiveAlgorithm(vector<vector<int>> A, vector<vector<int>> B) {
    int n = sqrt(A.size());
    cout << "n is = " << n << endl;
    vector<vector<int>> C(n, vector<int>(n, 0));
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; // base case for recursion
        multiple_recursive++;  // add multiplications for counters
    }
    else {
        vector<vector<int>> A_11 = Copy(A, 0, 0, (n / 2), (n / 2)); // initializing vectors
        vector<vector<int>> A_12 = Copy(A, 0, (n / 2 + 1), (n / 2), n);
        vector<vector<int>> A_21 = Copy(A, ((n / 2) + 1), 0, n, (n / 2));
        vector<vector<int>> A_22 = Copy(A, ((n / 2) + 1), ((n / 2) + 1), n, n);
        vector<vector<int>> B_11 = Copy(B, 0, 0, (n / 2), (n / 2));
        vector<vector<int>> B_12 = Copy(B, 0, (n / 2 + 1), (n / 2), n);
        vector<vector<int>> B_21 = Copy(B, ((n / 2) + 1), 0, n, (n / 2));
        vector<vector<int>> B_22 = Copy(B, ((n / 2) + 1), ((n / 2) + 1), n, n);
        vector<vector<int>> C_11;
        vector<vector<int>> C_12;
        vector<vector<int>> C_21;
        vector<vector<int>> C_22;

        C_11 = Add(RecursiveAlgorithm(A_11, B_11), RecursiveAlgorithm(A_12, B_21)); // recursion into sub matrices and combining sub matrices into total
        C_12 = Add(RecursiveAlgorithm(A_11, B_12), RecursiveAlgorithm(A_12, B_22));
        C_21 = Add(RecursiveAlgorithm(A_21, B_11), RecursiveAlgorithm(A_22, B_21));
        C_22 = Add(RecursiveAlgorithm(A_21, B_12), RecursiveAlgorithm(A_22, B_22));
        add_recursive = add_recursive + (4 * (n / 2) ^ 2);  // additions for counters


        Partition(C, C_11, 0, 0, (n / 2), (n / 2)); // Combining of sub matrices
        Partition(C, C_12, 0, (n / 2 + 1), (n / 2), n);
        Partition(C, C_21, ((n / 2) + 1), 0, n, (n / 2));
        Partition(C, C_22, ((n / 2) + 1), ((n / 2) + 1), n, n);



    }
    return (C);
}

//Strassen's Algorithm

vector<vector<int>> StrassensAlgorithm(vector<vector<int>> A, vector<vector<int>> B) {//need to fix array sizes
    int n = sqrt(A.size());
    vector<vector<int>> C(n, vector<int>(n, 0)); 
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; //base case for recursion
        multiple_strassens++;
    }
    else {
        vector<vector<int>> A_11 = Copy(A, 0, 0, (n / 2), (n / 2)); // initializing vectors
        vector<vector<int>> A_12 = Copy(A, 0, (n / 2 + 1), (n / 2), n);
        vector<vector<int>> A_21 = Copy(A, ((n / 2) + 1), 0, n, (n / 2));
        vector<vector<int>> A_22 = Copy(A, ((n / 2) + 1), ((n / 2) + 1), n, n);
        vector<vector<int>> B_11 = Copy(B, 0, 0, (n / 2), (n / 2));
        vector<vector<int>> B_12 = Copy(B, 0, (n / 2 + 1), (n / 2), n);
        vector<vector<int>> B_21 = Copy(B, ((n / 2) + 1), 0, n, (n / 2));
        vector<vector<int>> B_22 = Copy(B, ((n / 2) + 1), ((n / 2) + 1), n, n);


        vector<vector<int>> S_1 = Sub(B_12, B_22); //Strassions algorithm performing additions and subtractions of sub matrices
        vector<vector<int>> S_2 = Add(A_11, A_12);
        vector<vector<int>> S_3 = Add(A_21, A_22);
        vector<vector<int>> S_4 = Sub(B_21, B_11);
        vector<vector<int>> S_5 = Add(A_11, A_22);
        vector<vector<int>> S_6 = Add(B_11, B_22);
        vector<vector<int>> S_7 = Sub(A_12, A_22);
        vector<vector<int>> S_8 = Add(B_21, B_22);
        vector<vector<int>> S_9 = Sub(A_11, A_21);
        vector<vector<int>> S_10 = Add(B_11, B_12);

        add_strassens = add_strassens + (10 * (n / 2) ^ 2); //add to total of additions

        vector<vector<int>> P_1 = StrassensAlgorithm(A_11, S_1); //Recursion of sub matrices
        vector<vector<int>> P_2 = StrassensAlgorithm(S_2, B_22);
        vector<vector<int>> P_3 = StrassensAlgorithm(S_3, B_11);
        vector<vector<int>> P_4 = StrassensAlgorithm(A_22, S_4);
        vector<vector<int>> P_5 = StrassensAlgorithm(S_5, S_6);
        vector<vector<int>> P_6 = StrassensAlgorithm(S_7, S_8);
        vector<vector<int>> P_7 = StrassensAlgorithm(S_9, S_10);


        vector<vector<int>> C_11 = Add(Sub(Add(P_5, P_4), P_2), P_6); //Combining of sub matrices
        vector<vector<int>> C_12 = Add(P_1, P_2);
        vector<vector<int>> C_21 = Add(P_3, P_4);
        vector<vector<int>> C_22 = Sub(Sub(Add(P_5, P_1), P_3), P_7);

        add_strassens = add_strassens + (8 * (n / 2) ^ 2);




        Partition(C, C_11, 0, 0, (n / 2), (n / 2));  // combining of sub matrices
        Partition(C, C_12, 0, (n / 2 + 1), (n / 2), n);
        Partition(C, C_21, ((n / 2) + 1), 0, n, (n / 2));
        Partition(C, C_22, ((n / 2) + 1), ((n / 2) + 1), n, n);
    }
    return(C);
}






