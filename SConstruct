import os

env = Environment(
  ENV = {'PATH' : os.environ['PATH']}
)
env.Replace(CC = 'clang++')
env.Replace(CXX = 'clang++')

env.Program('dq_train',
  [ 'dq_train.cc',
    'dq.cc',
    'dq_quant.pb.cc',
    'matlab_util.cc'
  ],
  LIBS = ['matio', 'gflags', 'glog', 'protobuf'],
  LIBPATH = ['/usr/local/lib'],
  CCFLAGS = '-std=c++0x')

env.Program('dq_mapping',
  [ 'dq_mapping.cc',
    'dq.cc',
    'dq_quant.pb.cc',
    'matlab_util.cc'
  ],
  LIBS = ['matio', 'gflags', 'glog', 'protobuf'],
  LIBPATH = ['/usr/local/lib'],
  CCFLAGS = '-std=c++0x')

env.Program('table_view',
  [ 'table_view.cc',
    'dq_quant.pb.cc',
  ],
  LIBS = ['gflags', 'glog', 'protobuf'],
  LIBPATH = ['/usr/local/lib'],
  CCFLAGS = '-std=c++0x')

