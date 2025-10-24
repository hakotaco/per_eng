#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int n = 16384;

struct SmallHot {
  double x0;  // Only x[0] needed for sorting
  int index;  // To track original position for later reconstruction
};

struct BigHot {
  int rank;   // Only rank needed for sorting
  int index;  // To track original position for later reconstruction
};

struct SmallCold {
  char flg1;
  double x[6];  // x[1] through x[6]
  char flg2;
};

struct BigCold {
  double x[n];
};

bool sortSmallHotByx0(const SmallHot &a, const SmallHot &b) { 
  return a.x0 < b.x0; 
}

bool sortBigHotByRank(const BigHot &a, const BigHot &b) { 
  return a.rank < b.rank; 
}

int main()
{
  // Split vectors for Small
  vector<SmallHot> vsmall_hot(n);
  vector<SmallCold> vsmall_cold(n);
  
  // Split vectors for Big
  vector<BigHot> vbig_hot(n);
  vector<BigCold> vbig_cold(n);

  // Initialize Small structures
  for (int i = 0; i < n; i++) {
    vsmall_hot[i].x0 = n - i;
    vsmall_hot[i].index = i;
    // vsmall_cold would be initialized here if needed
  }

  // Initialize Big structures
  for (int i = 0; i < n; i++) {
    vbig_hot[i].rank = n - i;
    vbig_hot[i].index = i;
    std::memset(vbig_cold[i].x, 0, sizeof(vbig_cold[i].x));
  }

  // Sort only the hot data (much smaller!)
  sort(vsmall_hot.begin(), vsmall_hot.end(), sortSmallHotByx0);

  sort(vbig_hot.begin(), vbig_hot.end(), sortBigHotByRank);


  return 0;
}
