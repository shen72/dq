#include <fstream>
#include <iostream>
#include <gflags/gflags.h>

#include "macros.h"
#include "dq_quant.pb.h"

using namespace std;
using namespace dq;

DEFINE_string(quant, "", "Quant Filename");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  CHECK(FLAGS_quant != "");
  ifstream fin(FLAGS_quant.c_str(), ios::in | ios::binary);

  QuantTable table;
  table.ParseFromIstream(&fin);
  fin.close();

  for (size_t i = 0; i < table.dim_num(); i++) {
    cout << "Dim #" << i << ":";
    const QuantDim& local = table.dims(i);
    for (size_t j = 0; j < local.size(); j++) {
      cout << " " << local.data(j);
    }
    cout << endl;
  }
}
