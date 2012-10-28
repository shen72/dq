#include "dq.h"
#include "macros.h"

#include <gflags/gflags.h>
#include "matlab_util.h"

using namespace std;
using namespace dq;

DEFINE_string(train, "", "Train File");
DEFINE_string(quant, "", "Quantization File");

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  CHECK(FLAGS_train != "" && FLAGS_quant != "");

  int n, m;
  
  CHECK(ReadFromMatlab(
  
}
