#ifndef STEVENSHEN_MACRO_H
#define STEVENSHEN_MACRO_H

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(ClassName) \
  ClassName(const ClassName&); \
  void operator = (const ClassName&); 
#endif

#ifndef CHECK
#define CHECK(Phrase) \
  { auto v__ = Phrase; \
    if (!v__) { exit(-1); } \
  }
#endif

#endif /* STEVENSHEN_MACRO_H */
