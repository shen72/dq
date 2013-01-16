#include "dq.h"
#include "macros.h"
#include "matlab_util.h"

#include <google/gflags.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace dq;

DEFINE_string(quant, "", "Quantization File");
DEFINE_string(input_file, "", "Input filename");
DEFINE_string(input_mat, "", "Input Matname");
DEFINE_string(output_file, "", "Output filename");
DEFINE_string(output_mat, "", "Output Matname");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  CHECK(FLAGS_input_file != "" && FLAGS_input_mat != "" &&
        FLAGS_output_file != "" && FLAGS_output_mat != "" &&
        FLAGS_quant != "");

  QuantTable table;
  ifstream quant_s(FLAGS_quant.c_str(), ios::in | ios::binary);
  table.ParseFromIstream(&quant_s);

  vector<vector<double> > input_samples;

  DQMapper mapper(table);

  size_t rows, cols;
  ReadMatOrDie(FLAGS_input_file, FLAGS_input_mat,
               &input_samples, &rows, &cols);

  vector<vector<double> > output_samples(rows);
  for (size_t i = 0; i < rows; i++) {
    mapper.Map(input_samples[i], &output_samples[i]);
  }

  WriteMatOrDie(output_samples, FLAGS_output_file,
                FLAGS_output_mat);
}
