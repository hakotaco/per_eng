#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>

/**
 * Prints usage information
 */
void printUsage(const char *programName) {
  std::cout << "Usage: " << programName << " -f <input_file>" << std::endl;
  std::cout << "Example: " << programName << " -f example.txt" << std::endl;
}

/**
 * Reads filename from command line arguments.
 */
std::string readFilename(int argc, char **argv) {
  if (argc != 3) {
    return std::string();
  }

  if (strcmp(argv[1], "-f") != 0) {
    return std::string();
  }

  std::string filename = argv[2];

  return filename;
}

/**
 * Reads a square matrix of size N from istream is
 */
std::vector<std::vector<double>> readMatrix(int N, std::ifstream &inputStream) {
  std::vector<std::vector<double>> matrix(N, std::vector<double>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      inputStream >> matrix[i][j];
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
  int N;
  std::string filename = readFilename(argc, argv);

  if (filename.empty()) {
    printUsage(argv[0]);
    return 1;
  }

  std::ifstream inputStream(filename);

  if (!inputStream) {
    std::cout << "Could not open file " << filename << std::endl;
    inputStream.close();
    return 1;
  }


  inputStream >> N;

  std::cout << "Matrix size: " << N << "x" << N << std::endl;

  std::cout << "Enter matrix A (" << N << "x" << N << "):" << std::endl;
  std::vector<std::vector<double>> A = readMatrix(N, inputStream);

  std::cout << "Enter matrix B (" << N << "x" << N << "):" << std::endl;
  std::vector<std::vector<double>> B = readMatrix(N, inputStream);

  std::vector<std::vector<double>> C = multiplyMatrices(A, B, N);

  std::cout << "\nResult matrix C = A * B:" << std::endl;
  printMatrix(C, N);

  inputStream.close();
  return 0;
}
