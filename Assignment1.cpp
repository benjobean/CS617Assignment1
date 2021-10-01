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
bool BruteForceCheck(string matrix_file1, string matrix_file2, string expected_file, ofstream& outfile);
vector<vector<int>> CreateMatrix(int n);
void PrintMatrix(vector<vector<int>> A, ofstream& outfile);
void TestAlgorithms(ofstream& outfile);
void Phase1Test(string matrix_file1_1, string matrix_file2_1, string expected_file_1, string matrix_file1_2, string matrix_file2_2, string expected_file_2, string matrix_file1_3, string matrix_file2_3, string expected_file_3, ofstream& outfile);
void CompareAllAlgorithms(vector<vector<int>> input1, vector<vector<int>> input2, ofstream& outfile, int trial_index);

int main()
{
    ofstream outfile("output.txt");
   //Place paths to input files here
    string matrix_file1_1 = "input/Matrix3x3_1.txt";
    string matrix_file2_1 = "input/Matrix3x3_2.txt";
    string expected_file_1 = "input/Matrix3x3_expected.txt";
    string matrix_file1_2 = "input/Matrix5x5_1.txt";
    string matrix_file2_2 = "input/Matrix5x5_2.txt";
    string expected_file_2 = "input/Matrix5x5_expected.txt";
    string matrix_file1_3 = "input/Matrix7x7_1.txt";
    string matrix_file2_3 = "input/Matrix7x7_2.txt";
    string expected_file_3 = "input/Matrix7x7_expected.txt";
    std::cout << "Hello World!\n";
    Phase1Test(matrix_file1_1, matrix_file2_1, expected_file_1, matrix_file1_2, matrix_file2_2, expected_file_2, matrix_file1_3, matrix_file2_3, expected_file_3, outfile);
    vector<vector<int>> input = ParseInput("Book1.csv");
    cout << "Parse Successful\n";
    //vector<vector<int>> BF = BruteForce(input, input);
    //vector<vector<int>> RE = RecursiveAlgorithm(input, input);
    //vector<vector<int>> SA = StrassensAlgorithm(input, input);
    //OutputToFile(SA, "test.txt");
    //BruteForceCheck();
    vector<vector<int>> temp = CreateMatrix(8);
    //OutputToFile(temp, "MatrixCreation.txt");

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
        county = 0;
        countx++;
    }


    return;
}

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
    cout << "n =" << n << endl;
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

//Testing
// =================================================================================================
//TODO: Change BruteForceCheck() to have the expected matrices be read in from a text file
//==================================================================================================
void Phase1Test(string matrix_file1_1, string matrix_file2_1, string expected_file_1, string matrix_file1_2, string matrix_file2_2, string expected_file_2, string matrix_file1_3, string matrix_file2_3, string expected_file_3, ofstream& outfile) {
    BruteForceCheck(matrix_file1_1, matrix_file2_1, expected_file_1, outfile);
    BruteForceCheck(matrix_file1_2, matrix_file2_2, expected_file_2, outfile);
    BruteForceCheck(matrix_file1_3, matrix_file2_3, expected_file_3, outfile);
}

bool BruteForceCheck(string matrix_file1, string matrix_file2, string expected_file, ofstream& outfile) {
    bool result;
    bool check5x5;
    bool check7x7;
    bool incorrect_check;
    ///3x3 Matrix
    /*vector<vector<int>> first_vect3x3{
        {-16, -15, -12},
        {-20, -9, 2},
        {9, 17, 18}
    };

    vector<vector<int>> second_vect3x3{
        { 7, 8, 12 },
        { -6, 3, 16 },
        { -14, -11, -5 }
    };
    
    vector<vector<int>> expect_vect3x3{
        { 146, -41, -372 },
        { -114, -209, -394 },
        { -291, -75, 290 }
    };*/
    vector<vector<int>> first_vect = ParseInput(matrix_file1);
    outfile << "Matrix size " << first_vect.size() << " Input Matix 1:" << endl;
    PrintMatrix(first_vect, outfile);

    vector<vector<int>> second_vect = ParseInput(matrix_file2);
    outfile << "Matrix size " << second_vect.size() << " Input Matix 2:" << endl;
    PrintMatrix(second_vect, outfile);

    vector<vector<int>> expect_vect = ParseInput(expected_file);
    outfile << "Matrix size " << expect_vect.size() << " Expected Result Matix:" << endl;
    PrintMatrix(expect_vect, outfile);

    vector<vector<int>> BruteForceResult = BruteForce(first_vect, second_vect);
    outfile << "Matrix size " << BruteForceResult.size() << " Brute Force Result Matix:" << endl;
    PrintMatrix(BruteForceResult, outfile);
    result = equal(expect_vect.begin(), expect_vect.end(), BruteForceResult.begin());
    cout << "Bruteforce Check: " << result << endl;

    if (result) {
        outfile << "Comparison OK\n" << endl;
        return true;
    }
    else {
        outfile << "Comparison Error\n" << endl;
        return false;
    }

    ////5x5 Matrix
    //vector<vector<int>> first_vect5x5{
    //    {-10, -9, 12, 16, 17},
    //    {-15, -9, -6, 0, 16},
    //    {-14, -2, -1, 3, 9},
    //    {-6, -1, 0, 12, 13},
    //    { -17, -12, 1, 2, 20 }
    //};

    //vector<vector<int>> second_vect5x5{
    //    {-8, 9, 10, 13, 16},
    //    {-14, -12, -2, 16, 19},
    //    {-18, 6, 10, 14, 16},
    //    {-14, -8, 2, 13, 14},
    //    {-15, -10, -2, 11, 18}
    //};

    //vector<vector<int>> expect_vect5x5{
    //    {-489, -208, 36, 289, 391},
    //    {114,-223,-224,-247,-219},
    //    {-19,-222,-158,-90,-74},
    //    {-301,-268,-60,205,287},
    //    {-42,-219,-172,-153,-96}
    //};

    //vector<vector<int>> BruteForceResult5x5 = BruteForce(first_vect5x5, second_vect5x5);
    //check5x5 = equal(expect_vect5x5.begin(), expect_vect5x5.end(), BruteForceResult5x5.begin());
    //cout << "Bruteforce 5x5 Check: " << check5x5 << endl;

    ////7x7 Matrix
    //vector<vector<int>> first_vect7x7{
    //    {-19, -16, -7, 0, 1, 10, 11},
    //    {-17, -15, -12, 1, 7, 12, 19},
    //    {-15, -10, -6, -5, -3, -1, 14},
    //    {-18, -3, -2, 3, 4, 15, 19},
    //    {-19, -16, -14, -12, -3, -1, 14},
    //    {-18, -17, -9, 0, 10, 11, 13},
    //    {-17, -15, -10, -7, 0, 13, 18}
    //};

    //vector<vector<int>> second_vect7x7{
    //    {10, 3, -3, 1, 18, 8, -13},
    //    {-14, 19, -10, -5, -18, -4, 9},
    //    {-13, 16, -1, -15, 9, 11, -17},
    //    {-5, -7, -18, -14, 18, 15, 10},
    //    {-2, -3, -4, -18, 5, -10, -14},
    //    {1, -16, 11, 9, -18, 7, -14},
    //    {11, -19, 4, 15, 17, -8, 19}
    //};

    //vector<vector<int>> expect_vect7x7{
    //    {254, -845, 374, 403, -105, -193, 277},
    //    {398, -1109, 375, 491, 16, -331, 395},
    //    {252, -537, 298, 450, 7, -310, 479},
    //    {89, -777, 257, 333, -161, -196, 366},
    //    {435, -742, 504, 694, -155, -511, 543},
    //    {309, -974, 366, 316, -26, -302, 187},
    //    {416, -997, 552, 693, -180, -344, 346}
    //};

    //vector<vector<int>> BruteForceResult7x7 = BruteForce(first_vect7x7, second_vect7x7);
    //check7x7 = equal(expect_vect7x7.begin(), expect_vect7x7.end(), BruteForceResult7x7.begin());
    //cout << "Bruteforce 7x7 Check: " << check7x7 << endl;

    ////Check to make sure it can see that something is wrong
    //vector<vector<int>> BruteForceResultIncorrect = BruteForce(first_vect7x7, first_vect7x7);
    //incorrect_check = equal(expect_vect7x7.begin(), expect_vect7x7.end(), BruteForceResultIncorrect.begin());
    //cout << "Bruteforce Inc Check: " << incorrect_check << endl;
    //if (incorrect_check) {
    //    cout << "Comparison Error" << endl;
    //    return false;
    //}

    //if (check3x3 && check5x5 && check7x7) {
    //    cout << "Comparison OK" << endl;
    //    return true;
    //}
    //else {
    //    cout << "Comparison Error" << endl;
    //    return false;
    //}
    /*OutputToFile(BruteForceResult3x3, "test.txt");
    OutputToFile(expect_vect3x3, "test2.txt");*/

}

//Utility Function to generate matrices
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

void TestAlgorithms(ofstream& outfile) {
    //ofstream outfile(file_name);
    vector<int> n_values{ 1, 2, 4, 8, 16, 32, 64, 128, 256 };
    for (int i : n_values) {
        for (int j = 0; j < 100; j++) {
            vector<vector<int>> input_matrix_1 = CreateMatrix(i);
            vector<vector<int>> input_matrix_2 = CreateMatrix(i);
            CompareAllAlgorithms(input_matrix_1, input_matrix_2, outfile, j);
        }
    }
}

//Function to Compare all 3 Algorithms and return any matrices that error out
void CompareAllAlgorithms(vector<vector<int>> input1, vector<vector<int>> input2, ofstream& outfile, int trial_index) {
    vector<vector<int>> BruteForce_result = BruteForce(input1, input2);
    outfile << "Brute Force" << endl;
    vector<vector<int>> Recursive_result = RecursiveAlgorithm(input1, input2);
    outfile << "Recursive" << endl;
    vector<vector<int>> Strassens_result = StrassensAlgorithm(input1, input2);
    outfile << "Strassen" << endl;
    bool all_match = equal(BruteForce_result.begin(), BruteForce_result.end(), Recursive_result.begin()) && equal(BruteForce_result.begin(), BruteForce_result.end(), Strassens_result.begin());
    outfile << "n: " << input1.size() << "  |   " << "trial: " << trial_index + 1 << "  |   " << "result: " << all_match << endl;
    if (!all_match) {
        outfile << "Input Matrix 1" << endl;
        for (auto row_obj : input1)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }
        outfile << "Input Matrix 2" << endl;
        for (auto row_obj : input2)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }

        outfile << "Brute Force Result" << endl;
        for (auto row_obj : BruteForce_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }

        outfile << "Recursive Result" << endl;
        for (auto row_obj : Recursive_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }

        outfile << "Strassens Result" << endl;
        for (auto row_obj : Strassens_result)
        {
            for (auto elem : row_obj)
            {
                outfile << elem << "\t";
            }
            outfile << endl;
        }

    }
}


