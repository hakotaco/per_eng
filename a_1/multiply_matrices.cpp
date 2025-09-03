#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

/**
 * Prints usage information
 */
void printUsage(const char *programName) {
  std::cout << "Usage: " << programName << " -n <matrix_size>" << std::endl;
  std::cout << "Example: " << programName << " -n 3" << std::endl;
}

/**
 * Parses command line arguments to get matrix size
 */
int parseArguments(int argc, char *argv[]) {
  if (argc != 3) {
    return -1;
  }

  if (strcmp(argv[1], "-n") != 0) {
    return -1;
  }

  int N = atoi(argv[2]);
  if (N <= 0) {
    return -1;
  }

  return N;
}

/**
 * Reads a square matrix of size N from standard input
 */
std::vector<std::vector<double>> readMatrix(int N) {
  std::vector<std::vector<double>> matrix(N, std::vector<double>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cin >> matrix[i][j];
    }
  }
  return matrix;
}

/**
 * Multiplies two square matrices A and B, returns result matrix C
 * Implements C = A * B
 */
std::vector<std::vector<double>>
multiplyMatrices(const std::vector<std::vector<double>> &A,
                 const std::vector<std::vector<double>> &B, int N) {

  std::vector<std::vector<double>> C(N, std::vector<double>(N, 0.0));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

/**
 * Prints a square matrix with proper formatting
 */
void printMatrix(const std::vector<std::vector<double>> &matrix, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << std::setw(8) << std::setprecision(2) << std::fixed
                << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[]) {
  int N = parseArguments(argc, argv);

  if (N == -1) {
    printUsage(argv[0]);
    return 1;
  }

  std::cout << "Matrix size: " << N << "x" << N << std::endl;

  std::cout << "Enter matrix A (" << N << "x" << N << "):" << std::endl;
  std::vector<std::vector<double>> A = readMatrix(N);

  std::cout << "Enter matrix B (" << N << "x" << N << "):" << std::endl;
  std::vector<std::vector<double>> B = readMatrix(N);

  std::vector<std::vector<double>> C = multiplyMatrices(A, B, N);

  std::cout << "\nResult matrix C = A * B:" << std::endl;
  printMatrix(C, N);

  return 0;
}
