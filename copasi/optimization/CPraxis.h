// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include <limits>
#include "copasi/core/CMatrix.h"

class CRandom;

class FPraxis
{
public:
  virtual ~FPraxis() {};

  virtual const C_FLOAT64 & operator()(C_FLOAT64 * C_UNUSED(value), C_INT * C_UNUSED(n))
  {
    static C_FLOAT64 NaN = std::numeric_limits<C_FLOAT64>::quiet_NaN();
    return NaN;
  }
};

template <class CType> class FPraxisTemplate : public FPraxis
{
private:
  const C_FLOAT64 &(CType::*mMethod)(C_FLOAT64 *, C_INT *);  // pointer to member function
  CType * mpType;                                            // pointer to object

public:

  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  FPraxisTemplate(CType * pType,
                  const C_FLOAT64 & (CType::*method)(C_FLOAT64 *, C_INT*))
  {
    mpType = pType;
    mMethod = method;
  };

  virtual ~FPraxisTemplate() {};

  // override operator "()"
  virtual const C_FLOAT64 & operator()(C_FLOAT64 *value, C_INT *n)
  {return (*mpType.*mMethod)(value, n);}    ;              // execute member function
};

class CPraxis
{
public:

  struct Global
  {
    C_FLOAT64 fx, ldt, dmin__;
    C_INT nf, nl;
  };

  struct Q
  {
    CVector< C_FLOAT64 > v; // [__dim__ * __dim__] /* was [100][100] */,
    CVector< C_FLOAT64 > q0; // [__dim__],
    CVector< C_FLOAT64 > q1; // [__dim__],
    C_FLOAT64 qa, qb, qc, qd0, qd1, qf1;
  };

  CPraxis();
  ~CPraxis();

private:
  CRandom * mpRandom;

  Global global_1;
  Q q_1;

public:

  C_FLOAT64 praxis_(C_FLOAT64 *t0,
                    C_FLOAT64 *machep,
                    C_FLOAT64 *h0,
                    C_INT *n,
                    C_INT *prin,
                    C_FLOAT64 *x,
                    FPraxis *f, // Functor for function under investigation
                    C_FLOAT64 *fmin);

  int min_(C_INT *, C_INT *, C_INT *,
           C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, bool *, FPraxis *f,
           C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
  C_FLOAT64 flin_(C_INT *, C_INT *, C_FLOAT64 *, FPraxis *, C_FLOAT64 *, C_INT *);
  int quad_(C_INT *, FPraxis *f, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
  int print_(C_INT *n, C_FLOAT64 *x, C_INT *prin, C_FLOAT64 *fmin);
  int minfit_(C_INT *, C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
};

#endif // COPASI_CPraxis
