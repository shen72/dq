#ifndef MATLAB_UTIL_H
#define MATLAB_UTIL_H 

#include <string>
#include <vector>

using std::string;
using std::vector;

void ReadMatOrDie(const string& mat_file_name,
                  const string& mat_name,
                  vector<vector<double> >* contents,
                  int* row_n = 0,
                  int* col_n = 0);


#endif /* MATLAB_UTIL_H */
