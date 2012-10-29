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

class DQMapper {
 public:
  DQMapper() {}
  explicit DQMapper(const QuantTable& table);
  void Load(const QuantTable& table);

  void Map(const vector<double>& old_v, vector<double>* new_v);
  
 private:
  vector<vector<double> > quant_table_;
  size_t dim_;

  DISALLOW_COPY_AND_ASSIGN(DQMapper);
};

}

#endif /* DQ_H */
