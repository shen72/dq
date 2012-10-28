#include "matlab_util.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  string filename = argv[1];
  string matname = argv[2];
  
  vector<vector<double> > M;
  size_t n, m;

  ReadMatOrDie(filename, matname, &M, &n, &m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }
  
}
