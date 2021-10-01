#include <iostream>
#include <math.h>
#include <iomanip>
#include <array>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <algorithm>
#include <iterator>
//#include "Assignment1.h"

//Benjamin Davis
//Jonathan Lorray

using namespace std;

int multiple_bf;
int add_bf;
int multiple_recursive;
int add_recursive;
int multiple_strassens;
int add_strassens;




// Function Prototypes
vector<vector<int>> ParseInput(string fileName);
void OutputToFile(vector<vector<int>> matrixvector, string file_name);
void PrintMatrix(vector<vector<int>> A, ofstream& outfile);
bool CompareMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2);
bool CompareMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2, vector<vector<int>> matrix3);

vector<vector<int>> CreateMatrix(int n);

vector<vector<int>> BruteForce(vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> RecursiveAlgorithm(vector<vector<int>> A, vector<vector<int>> B);
vector<vector<int>> StrassensAlgorithm(vector<vector<int>> A, vector<vector<int>> B);




void Phase1Test(string matrix_file1_1, string matrix_file2_1, string expected_file_1, string matrix_file1_2, string matrix_file2_2, string expected_file_2, string matrix_file1_3, string matrix_file2_3, string expected_file_3, ofstream& outfile);
bool BruteForceCheck(string matrix_file1, string matrix_file2, string expected_file, ofstream& outfile);
void Phase2Test(ofstream& outfile);
void CompareAllAlgorithms(vector<vector<int>> input1, vector<vector<int>> input2, ofstream& outfile, int trial_index);


int main()
{
    ofstream outfile("output.txt"); //Create output file
    //Place paths to input files for phase 1 testing here
    string matrix_file1_1 = "input/Matrix3x3_1.txt";
    string matrix_file2_1 = "input/Matrix3x3_2.txt";
    string expected_file_1 = "input/Matrix3x3_expected.txt";
    string matrix_file1_2 = "input/Matrix5x5_1.txt";
    string matrix_file2_2 = "input/Matrix5x5_2.txt";
    string expected_file_2 = "input/Matrix5x5_expected.txt";
    string matrix_file1_3 = "input/Matrix7x7_1.txt";
    string matrix_file2_3 = "input/Matrix7x7_2.txt";
    string expected_file_3 = "input/Matrix7x7_expected.txt";
    
    Phase1Test(matrix_file1_1, matrix_file2_1, expected_file_1, matrix_file1_2, matrix_file2_2, expected_file_2, matrix_file1_3, matrix_file2_3, expected_file_3, outfile);
    Phase2Test(outfile);
    

}

//======================================================================================================================
//Utility Functions
//======================================================================================================================

//Utility function to parse input files
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
    return matrixvector;
}

//Deprecated Utility function to print a matrix to the output file
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

//Utility Function to print a matrix to the output file
void PrintMatrix(vector<vector<int>> A, ofstream& outfile) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << A[i][j] << " ";
        }
        outfile << endl;
    }
    outfile << endl;
    return;
}

//function to create a matrix partition
void Partition(vector<vector<int>>& C, vector<vector<int>> A, int startx, int starty, int endx, int endy) {
    int countx = 0;
    int county = 0;
    for (int i = startx; i <= endx; i++) {

        for (int j = starty; j <= endy; j++) {
            C[i][j] = A[countx][county];
            county++;
        }
        county = 0;
        countx++;
    }


    return;
}

//function to copy matrices
vector<vector<int>> Copy(vector<vector<int>> A, int startx, int starty, int endx, int endy) {
    vector<vector<int>> C;
    vector<int> temp;
    
    for (int i = startx; i <= endx; i++) {

        for (int j = starty; j <= endy; j++) {
            
            temp.push_back((A[i][j])); 
        }
        C.push_back(temp);
        temp.clear();
    }
    if (C.size() % 2 == 1 && C.size() != 1) {
        for (int i = 0; i < C[0].size(); i++) {
            temp.push_back(0);
            //cout << temp[i] << " ";
        }
        
        C.push_back(temp);
        for (int i = 0; i < C.size(); i++) {
            C[i].push_back(0);
            //cout << C[i][C.size()-1] << endl;
        }
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

//Utility Function for checking if matrices are equal
bool CompareMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
    bool all_match = true;
    if (!equal(matrix1.begin(), matrix1.end(), matrix2.begin())) {
        all_match = false;
    }
    return all_match;
}

//Utility Function for checking if matrices are equal(overloaded to 3 matrices for phase 2 of testing)
bool CompareMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2, vector<vector<int>> matrix3) {
    bool all_match = true;
    //Compare Brute Force to Recursive
    if (!equal(matrix1.begin(), matrix1.end(), matrix2.begin())) {
        all_match = false;
    }
    //Compare Brute Force to Strassens
    else if (!equal(matrix1.begin(), matrix1.end(), matrix3.begin())) {
        all_match = false;
    }
    //Compare Recursive to Strassens
    else if (!equal(matrix2.begin(), matrix2.end(), matrix3.begin())) {
        all_match = false;
    }
    return all_match;
}

//Utility Function to generate random matrices
vector<vector<int>> CreateMatrix(int n) {
    random_device rnd_device;
    mt19937 mersenne_engine{ rnd_device() };
    uniform_int_distribution<int> dist{ 1, 52 };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };


    vector<vector<int>> newMatrix;
    for (int i = 0; i < n; i++) {
        vector<int> temp(n);
        generate(begin(temp), end(temp), gen);
        newMatrix.push_back(temp);
    }
    return newMatrix;
}


//======================================================================================================================
//Algorithms
//======================================================================================================================

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
    int n = A.size();
    //PrintMatrix(A);
    //cout << "n is = " << n << endl;
    vector<vector<int>> C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; // base case for recursion

        multiple_recursive++;  // add multiplications for counters
    }
    else {
        vector<vector<int>> A_11 = Copy(A, 0, 0, (n / 2) - 1, (n / 2) - 1); // initializing vectors
        vector<vector<int>> A_12 = Copy(A, 0, ((n / 2)), (n / 2)-1, n-1);
        vector<vector<int>> A_21 = Copy(A, ((n / 2)), 0, n - 1, (n / 2) - 1);
        vector<vector<int>> A_22 = Copy(A, ((n / 2)), ((n / 2)), n-1, n-1);
        vector<vector<int>> B_11 = Copy(B, 0, 0, (n / 2)-1, (n / 2) - 1);
        vector<vector<int>> B_12 = Copy(B, 0, (n / 2), (n / 2)-1, n - 1);
        vector<vector<int>> B_21 = Copy(B, ((n / 2)), 0, n - 1, (n / 2) - 1);
        vector<vector<int>> B_22 = Copy(B, ((n / 2)), ((n / 2)), n - 1, n - 1);
        vector<vector<int>> C_11;
        vector<vector<int>> C_12;
        vector<vector<int>> C_21;
        vector<vector<int>> C_22;

        C_11 = Add(RecursiveAlgorithm(A_11, B_11), RecursiveAlgorithm(A_12, B_21)); // recursion into sub matrices and combining sub matrices into total
        C_12 = Add(RecursiveAlgorithm(A_11, B_12), RecursiveAlgorithm(A_12, B_22));
        C_21 = Add(RecursiveAlgorithm(A_21, B_11), RecursiveAlgorithm(A_22, B_21));
        C_22 = Add(RecursiveAlgorithm(A_21, B_12), RecursiveAlgorithm(A_22, B_22));
        add_recursive = add_recursive + (4 * (n / 2) ^ 2);  // additions for counters


        Partition(C, C_11, 0, 0, ((n / 2)-1), ((n / 2)-1)); // Combining of sub matrices
        Partition(C, C_12, 0, (n / 2), (n / 2)-1, n-1);
        Partition(C, C_21, (n / 2), 0, n-1, ((n / 2)-1));
        Partition(C, C_22, (n / 2), (n / 2), n-1, n-1);



    }
    return (C);
}

//Strassen's Algorithm
vector<vector<int>> StrassensAlgorithm(vector<vector<int>> A, vector<vector<int>> B) {//need to fix array sizes
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); 
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0]; //base case for recursion
        multiple_strassens++;
    }
    else {
        vector<vector<int>> A_11 = Copy(A, 0, 0, (n / 2) - 1, (n / 2) - 1); // initializing vectors
        vector<vector<int>> A_12 = Copy(A, 0, ((n / 2)), (n / 2) - 1, n - 1);
        vector<vector<int>> A_21 = Copy(A, ((n / 2)), 0, n - 1, (n / 2) - 1);
        vector<vector<int>> A_22 = Copy(A, ((n / 2)), ((n / 2)), n - 1, n - 1);
        vector<vector<int>> B_11 = Copy(B, 0, 0, (n / 2) - 1, (n / 2) - 1);
        vector<vector<int>> B_12 = Copy(B, 0, (n / 2), (n / 2) - 1, n - 1);
        vector<vector<int>> B_21 = Copy(B, ((n / 2)), 0, n - 1, (n / 2) - 1);
        vector<vector<int>> B_22 = Copy(B, ((n / 2)), ((n / 2)), n - 1, n - 1);


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




        Partition(C, C_11, 0, 0, ((n / 2) - 1), ((n / 2) - 1)); // Combining of sub matrices
        Partition(C, C_12, 0, (n / 2), (n / 2) - 1, n - 1);
        Partition(C, C_21, (n / 2), 0, n - 1, ((n / 2) - 1));
        Partition(C, C_22, (n / 2), (n / 2), n - 1, n - 1);
    }
    return(C);
}

//======================================================================================================================
//Testing
//======================================================================================================================

//Driver Function for Phase 1 of testing
void Phase1Test(string matrix_file1_1, string matrix_file2_1, string expected_file_1, string matrix_file1_2, string matrix_file2_2, string expected_file_2, string matrix_file1_3, string matrix_file2_3, string expected_file_3, ofstream& outfile) {
    bool bf_check1 = BruteForceCheck(matrix_file1_1, matrix_file2_1, expected_file_1, outfile);
    bool bf_check2 = BruteForceCheck(matrix_file1_2, matrix_file2_2, expected_file_2, outfile);
    bool bf_check3 = BruteForceCheck(matrix_file1_3, matrix_file2_3, expected_file_3, outfile);
    if (bf_check1 && bf_check2 && bf_check3) {
        outfile << "Brute Force Algorithm Validated\n" << endl;
        cout << "Brute Force Algorithm Validated\n" << endl;
    }
}

//Main Brute Force algorithm validation function
bool BruteForceCheck(string matrix_file1, string matrix_file2, string expected_file, ofstream& outfile) {
           
    vector<vector<int>> first_matrix = ParseInput(matrix_file1);
    outfile << "Matrix size " << first_matrix.size() << " Input Matix 1:" << endl;
    PrintMatrix(first_matrix, outfile);

    vector<vector<int>> second_matrix = ParseInput(matrix_file2);
    outfile << "Matrix size " << second_matrix.size() << " Input Matix 2:" << endl;
    PrintMatrix(second_matrix, outfile);

    vector<vector<int>> expect_matrix = ParseInput(expected_file);
    outfile << "Matrix size " << expect_matrix.size() << " Expected Result Matix:" << endl;
    PrintMatrix(expect_matrix, outfile);

    vector<vector<int>> BruteForceResult = BruteForce(first_matrix, second_matrix);
    outfile << "Matrix size " << BruteForceResult.size() << " Brute Force Result Matix:" << endl;
    PrintMatrix(BruteForceResult, outfile);
    //bool result = equal(expect_vect.begin(), expect_vect.end(), BruteForceResult.begin());
    bool result = CompareMatrices(expect_matrix, BruteForceResult);
    cout << "Bruteforce Check: " << result << endl;

    if (result) {
        outfile << "Comparison OK\n" << endl;
        return true;
    }
    else {
        outfile << "Comparison Error\n" << endl;
        return false;
    }

}

//Driver function for Phase 2 of testing
void Phase2Test(ofstream& outfile) {
    //ofstream outfile(file_name);
    outfile << "NOTE: result: 1 if the matrices are equal, 0 if there is a discrepency" << endl;
    vector<int> n_values{ 1, 2, 4, 8, 16, 24, 32, 48, 64 };
    for (int i : n_values) {
        for (int j = 0; j < 100; j++) {
            cout << "n = " << i << "\t|\ttrial: " << j << endl;
            vector<vector<int>> input_matrix_1 = CreateMatrix(i);
            vector<vector<int>> input_matrix_2 = CreateMatrix(i);
            CompareAllAlgorithms(input_matrix_1, input_matrix_2, outfile, j);
        }
    }
}

//Main Phase 2 testing Function to Compare all 3 Algorithms and output any matrices that error out
void CompareAllAlgorithms(vector<vector<int>> input1, vector<vector<int>> input2, ofstream& outfile, int trial_index) {
    cout << "Brute Force: Start" << endl;
    vector<vector<int>> BruteForce_result = BruteForce(input1, input2);
    cout << "Brute Force: Done" << endl; //Program progress notification

    cout << "Recursive: Start" << endl;
    vector<vector<int>> Recursive_result = RecursiveAlgorithm(input1, input2);
    cout << "Recursive: Done" << endl;  //Program progress notification

    cout << "Strassen: Start" << endl;
    vector<vector<int>> Strassens_result = StrassensAlgorithm(input1, input2);
    cout << "Strassen: Done" << endl;  //Program progress notification
    
    bool all_match = CompareMatrices(BruteForce_result, Recursive_result, Strassens_result);
    outfile << "n: " << input1.size() << "\t|\t" << "trial: " << trial_index + 1 << "\t|\t" << "result: " << all_match << endl;
    if (!all_match) {
        cout << "n: " << input1.size() << "\t|\t" << "trial: " << trial_index + 1 << "\t|\t" << "result: " << all_match << endl;//Debug and Notification for mid program run
        outfile << "Input Matrix 1" << endl;
        PrintMatrix(input1, outfile);
        /*for (auto row_obj : input1)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }*/

        outfile << "Input Matrix 2" << endl;
        PrintMatrix(input2, outfile);
        /*for (auto row_obj : input2)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }*/

        outfile << "Brute Force Result Matrix" << endl;
        PrintMatrix(BruteForce_result, outfile);
        /*for (auto row_obj : BruteForce_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }*/

        outfile << "Recursive Result Matrix" << endl;
        PrintMatrix(Recursive_result, outfile);
        /*for (auto row_obj : Recursive_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }*/

        outfile << "Strassens Result Matrix" << endl;
        PrintMatrix(Strassens_result, outfile);
        /*for (auto row_obj : Strassens_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }*/

    }
    cout << "Trial " << trial_index+1 << " Done" << endl; //Program progress notification
}


