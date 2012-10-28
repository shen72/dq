#include "matlab_util.h"

#include "macros.h"

#include <memory.h>
#include <vector>
#include <string>
#include <matio.h>

using namespace std;

void ReadMatOrDie(const string& mat_file_name,
                  const string& mat_name,
                  vector<vector<double> >* contents,
                  size_t* row_n = 0, size_t* col_n = 0) {
  mat_t* matfp;
  CHECK(matfp = Mat_Open(mat_file_name.c_str(), MAT_ACC_RDONLY));

  matvar_t* matp;
  CHECK(matp = Mat_VarRead(matfp, mat_name.c_str()));

  CHECK(matp->rank == 2);
  if (row_n) {
    *row_n = matp->dims[0];
  }

  if (col_n) {
    *col_n = matp->dims[1];
  }

  CHECK(matp->class_type == MAT_C_DOUBLE);

  *contents = vector<vector<double> > (*row_n, vector<double>(*col_n));
  for (size_t i = 0; i < *row_n; i++) {
    memcpy(&(*contents)[i][0], static_cast<double*>(matp->data) + i * *col_n,
           sizeof(double) * *col_n);
  }  
}
