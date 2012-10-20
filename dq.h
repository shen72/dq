#ifndef DQ_H
#define DQ_H

#include "dq_quant.pb.h"
#include "macros.h"

#include <vector>

namespace dq {

using std::vector;

class DQTrainer {
 public:
  DQTrainer() {}
  void Train(const vector<vector<double> >& samples, QuantTable* table, int nbins);

 private:
  void train_dim(const vector<double>& sample_dim,
                 QuantDim* dim_table, int nbins);

  DISALLOW_COPY_AND_ASSIGN(DQTrainer); 
};
}

#endif /* DQ_H */
