#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int main() {
  // Create test_cases directory if it doesn't exist
  std::filesystem::create_directory("test_cases");

  // Define test case sizes
  std::vector<int> sizes = {3, 10, 100, 1000};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  for (int i = 0; i < sizes.size(); i++) {
    int N = sizes[i];

    std::string filename = "test_cases/test_" + std::to_string(i + 1) + ".txt";
    std::ofstream file(filename);

    // Write matrix size
    file << N << std::endl;

    // Generate and write matrix 1
    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        file << dis(gen);
        if (col < N - 1)
          file << " ";
      }
      file << std::endl;
    }

    // Generate and write matrix 2
    for (int row = 0; row < N; row++) {
      for (int col = 0; col < N; col++) {
        file << dis(gen);
        if (col < N - 1)
          file << " ";
      }
      file << std::endl;
    }

    file.close();
    std::cout << "Generated test case " << i + 1 << " with size " << N << "x"
              << N << std::endl;
  }

  return 0;
}