#include "dq.h"
#include "macros.h"

#include <gflags/gflags.h>
#include "matlab_util.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace dq;

DEFINE_string(train, "", "Train File");
DEFINE_string(mat, "", "Mat name");
DEFINE_string(quant, "", "Quantization File");
DEFINE_int32(nbins, 32, "Number of bins per dimension");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  CHECK(FLAGS_train != "" && FLAGS_quant != "");
  CHECK(FLAGS_nbins > 0);

  size_t n, m;

  vector<vector<double> > train_repo;
  
  ReadMatOrDie(FLAGS_train, FLAGS_mat, &train_repo, &n, &m);

  DLOG(INFO) << "Done reading mat into library" << endl;
  DQTrainer trainer;
  QuantTable table;
  trainer.Train(train_repo, &table, FLAGS_nbins);

  ofstream out_s(FLAGS_quant, ios::out | ios::binary);
  CHECK(table.SerializeToOstream(&out_s));
  out_s.close();
}
