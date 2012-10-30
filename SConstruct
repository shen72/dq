Program('dq_train',
  [ 'dq_train.cc',
    'dq.cc',
    'dq_quant.pb.cc',
    'matlab_util.cc'
  ],
  LIBS = ['matio', 'gflags', 'glog', 'protobuf'],
  LIBPATH = ['/usr/local/lib'],
  CCFLAGS = '-std=c++0x')

Program('dq_mapping',
  [ 'dq_mapping.cc',
    'dq.cc',
    'dq_quant.pb.cc',
    'matlab_util.cc'
  ],
  LIBS = ['matio', 'gflags', 'glog', 'protobuf'],
  LIBPATH = ['/usr/local/lib'],
  CCFLAGS = '-std=c++0x')

