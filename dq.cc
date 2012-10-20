#include "dq.h"
#include "kmeans1d.h"

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
    for (int j = 0; j < n; j++) {
      perdim[j] = sample[i][j];
    }

    QuantDim dim_table;
    train_dim(perdim, &dim_table, nbins);
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
}
