#include "dq.h"

#include "kmeans1d.h"

#include <algorithm>

namespace dq {

using namespace std;

void DQTrainer::Train(const vector<vector<double> >& sample,
                      QuantTable* table, int nbins) {
  int n = sample.size();
  CHECK(n > 0);

  int dim = sample[0].size();

  table->Clear();
  table->set_dim_num(dim);
  vector<double> perdim(n);
  for (int i = 0; i < dim; i++) {
    DLOG(INFO) << "Start training Dim #" << i << "\t";
    for (int j = 0; j < n; j++) {
      perdim[j] = sample[i][j];
    }

    QuantDim dim_table;
    train_dim(perdim, &dim_table, nbins);
    DLOG(INFO) << "Done" << endl;
    table->add_dims()->CopyFrom(dim_table);
  }
}


void DQTrainer::train_dim(const vector<double>& sample_dim,
                          QuantDim* dim_table, int nbins) {
  dim_table->Clear();

  kmeans1d<double> trainer;
  vector<double> centers;
  trainer.cluster(sample_dim, &centers, nbins); 

  dim_table->set_size(centers.size());
  for (int i = 0; i < centers.size(); i++) {
    dim_table->add_data(centers[i]);
  }
}


//=============DQMapper==============

DQMapper::DQMapper(const QuantTable& table) {
  Load(table);
}

void DQMapper::Load(const QuantTable& table) {
  dim_ = table.dim_num();
  quant_table_ = vector<vector<double> > (dim_);
  for (size_t i = 0; i < dim_; i++) {
    const QuantDim& curr_dim = table.dims(i);
    size_t len = curr_dim.size();
     for (size_t j = 0; j < len; j++) {
      quant_table_[i].push_back(curr_dim.data(j));
    }
  } 
}

void DQMapper::Map(const vector<double>& old_v,
                   vector<double>* new_v) {
  CHECK(old_v.size() == dim_);
  new_v->resize(dim_);

  for (size_t i = 0; i < dim_; i++) {
    const vector<double>& curr_table = quant_table_[i];
    vector<double>::const_iterator it = lower_bound(
        curr_table.begin(), curr_table.end(), old_v[i]);
    if (it == curr_table.end()) {
      (*new_v)[i] = *(it-1);
    } else if (it == curr_table.begin() ||
               *it - old_v[i] < old_v[i] - *(it - 1)) {
      (*new_v)[i] = *it;
    } else {
      (*new_v)[i] = *(it - 1);
    }
  }
}

} // namespace dq
