#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int n = 16384;

struct Small {
  char flg1;
  double x[7];
  char flg2;
};

struct Big {
  int rank;
  double x[n];
};

bool sortSmallByx0(const Small &a, const Small &b) { 
  return a.x[0] < b.x[0]; 
}

bool sortBigByRank(const Big &a, const Big &b) { 
  return a.rank < b.rank; 
}

int main()
{
  vector<Small> vsmall(n);
  vector<Big> vbig(n);

  for (int i = 0; i < n; i++)
    vsmall[i].x[0] = n - i;

  for (int i = 0; i < n; i++) {
    vbig[i].rank = n - i;
    std::memset(vbig[i].x, 0, sizeof(vbig[i].x));
  }

  sort(vsmall.begin(), vsmall.end(), sortSmallByx0);

  sort(vbig.begin(), vbig.end(), sortBigByRank);

  return 0;
}