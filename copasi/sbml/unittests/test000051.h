// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef TEST_000051_H__
#define TEST_000051_H__

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/extensions/HelperMacros.h>

class CDataModel;

class test000051 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(test000051);
  CPPUNIT_TEST(test_bug988);
  CPPUNIT_TEST_SUITE_END();

protected:
  static const char* MODEL_STRING;
  static CDataModel* pCOPASIDATAMODEL;

public:
  void setUp();

  void tearDown();

  void test_bug988();
};

#endif /* TEST000051_H__ */
