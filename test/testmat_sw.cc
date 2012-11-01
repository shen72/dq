#include "matlab_util.h"

#include <vector>
#include <string>
#include <iostream>
#include <gflags/gflags.h>

using namespace std;

DEFINE_string(input_file, "", "input file");
DEFINE_string(input_mat, "", "input mat");
DEFINE_string(output_file, "", "output file");
DEFINE_string(output_mat, "", "output_mat");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  vector<vector<double> > M;
  size_t n, m;

  ReadMatOrDie(FLAGS_input_file, FLAGS_input_mat, &M, &n, &m);
  WriteMatOrDie(M, FLAGS_output_file, FLAGS_output_mat);
 
}
