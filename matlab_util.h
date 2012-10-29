#ifndef MATLAB_UTIL_H
#define MATLAB_UTIL_H 

#include <string>
#include <vector>

using std::string;
using std::vector;

void ReadMatOrDie(const string& mat_file_name,
                  const string& mat_name,
                  vector<vector<double> >* contents,
                  size_t* row_n = 0,
                  size_t* col_n = 0);

void WriteMatOrDie(const vector<vector<double> >& contents,
                   const string& mat_file_name, 
                   const string& mat_name);

#endif /* MATLAB_UTIL_H */
