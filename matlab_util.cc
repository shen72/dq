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
                  size_t* row_n, size_t* col_n) {
  mat_t* matfp;
  CHECK(matfp = Mat_Open(mat_file_name.c_str(), MAT_ACC_RDONLY));

  matvar_t* matp;
  CHECK(matp = Mat_VarRead(matfp, mat_name.c_str()));

  CHECK(matp->rank == 2);
  size_t rows = matp->dims[0];
  size_t cols = matp->dims[1];

  if (row_n) {
    *row_n = rows;
  }

  if (col_n) {
    *col_n = cols;
  }

  CHECK(matp->class_type == MAT_C_DOUBLE);

  *contents = vector<vector<double> > (rows, vector<double>(cols));
  double* data_p = static_cast<double*>(matp->data);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      (*contents)[i][j] = *(data_p + j * rows + i);
    }
  }

  Mat_VarFree(matp);
  Mat_Close(matfp);
}

void WriteMatOrDie(const vector<vector<double> >& contents,
                   const string& mat_file_name,
                   const string& mat_name) {
  size_t n = contents.size();
  CHECK(n > 0);
  size_t dim = contents[0].size();
  double* data_p = new double[n * dim];  // TODO: should use scope_ptr here.
  CHECK(data_p);

  for (size_t j = 0, p = 0; j < dim; j++) {
    for (size_t i = 0; i < n; i++, p++) {
      data_p[p] = contents[i][j];
    }
  }
  size_t dims[2] = {n, dim}; 

  matvar_t* matp = Mat_VarCreate(mat_name.c_str(), MAT_C_DOUBLE,
                                 MAT_T_DOUBLE, 2, dims, data_p, 0);
  
  mat_t * matfp = Mat_Create(mat_file_name.c_str(), 0);
  CHECK(matp && matfp);

  Mat_VarWrite(matfp, matp, MAT_COMPRESSION_ZLIB);
  Mat_Close(matfp);
  Mat_VarFree(matp);
  delete [] data_p;
}
