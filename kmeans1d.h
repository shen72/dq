#ifndef KMEANS1D
#define KMEANS1D

#include <vector>
#include <algorithm>
#include <cmath>

#include "macros.h"

namespace dq {

using namespace std;

template<class T>
class kmeans1d {
 public:
  kmeans1d() {}
  void cluster(const vector<T>& samples,
               vector<T>* centers,
               int kcenter, T epsilon = 1e-10,
               int iteration_limit = 1000) {
    vector<T> sorted(samples);
    int n = samples.size();
    sort(sorted.begin(), sorted.end());
    vector<int> id(n);
    vector<int> counting(kcenter);
    vector<T> new_centers(kcenter);
 
    for (int it_no = 0; it_no < iteration_limit; it_no++) {
      fill(new_centers.begin(), new_centers.end(), static_cast<T>(0));
      fill(counting.begin(), counting.end(), 0);
      int j = 0;
      for (int i = 0; i < n; i++) {
        for (j++; j < kcenter && t_abs_((*centers)[j] - sorted[i]) < 
             t_abs_((*centers)[j - 1] - sorted[i]); j++);
        j--;
        id[i] = j;
        counting[j]++;
        new_centers[j] += sorted[i];
      }
      for (int i = 0; i < kcenter; i++) {
        if (counting[i] > 0) {
          new_centers[i] = new_centers[i] / counting[i];
        } else {
          new_centers[i] = (*centers)[i];
        }
      }
      sort(new_centers.begin(), new_centers.end());
      if (term_critria_(new_centers, *centers, epsilon)) { break; }
      *centers = new_centers;
    }
  }

 private:
  virtual void init_centers(const vector<T>& samples, 
                            vector<T>* centers,
                            int kcenter, bool issorted = false) {
    int n = samples.size();
    CHECK(n > 0 && kcenter > 0);

    centers->resize(kcenter);

    if (kcenter < 2) {
      (*centers)[0] = samples[0];
      return;
    }

    vector<T>* sorted = const_cast< vector<T>* > ( &samples );

    if (!issorted) {
      sorted = new vector<T>(samples);
      sort(sorted->begin(), sorted->end());
    }

    for (int i = 0; i < kcenter; i++) {
      (*centers)[i] = samples[n * i / kcenter];
    }
  }

  bool term_critria_(const vector<T>& center_a, const vector<T>& center_b,
                     const T& epsilon) {
    T sum = 0;
    for (int i = 0; i < center_a.size(); i++) {
      sum += t_abs_(center_a[i] - center_b[i]);
    }

    return sum < epsilon;
  }

  T t_abs_(const T& a) {
    return a >= 0 ? a : -a;
  }

  DISALLOW_COPY_AND_ASSIGN(kmeans1d);
};

}
#endif /* KMEANS1D */
