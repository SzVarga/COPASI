// Copyright (C) 2021 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "catch.hpp"

extern std::string getTestFile(const std::string & fileName);

#include <copasi/CopasiTypes.h>

TEST_CASE("create a reaction with numerically named species", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != nullptr);

  REQUIRE(dm->newModel(NULL, true));

  auto * model = dm->getModel();
  REQUIRE(model != nullptr);

  auto * reaction = model->createReaction("r1");
  REQUIRE(reaction != nullptr);

  REQUIRE(reaction->setReactionScheme("2 \"2\" -> 3 \"3\""));

  const auto& chem = reaction->getChemEq();
  REQUIRE(chem.getSubstrates().size() == 1);
  REQUIRE(chem.getSubstrates()[0].getMetabolite() != nullptr);
  REQUIRE(chem.getSubstrates()[0].getMultiplicity() == 2);
  REQUIRE(chem.getSubstrates()[0].getMetabolite()->getObjectName() == "2");
  REQUIRE(chem.getProducts().size() == 1);
  REQUIRE(chem.getProducts()[0].getMetabolite() != nullptr);
  REQUIRE(chem.getProducts()[0].getMultiplicity() == 3);
  REQUIRE(chem.getProducts()[0].getMetabolite()->getObjectName() == "3");

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("create a new model with invalid value", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->newModel(NULL, true));

  auto * model = dm->getModel();
  REQUIRE(model != nullptr);

  auto* exp = new CExpression("expr", dm);
  exp->setInfix("1,1");
  exp->compile();
  auto val = exp->calcValue();
  pdelete(exp);

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("create a model with inhibited reaciton", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->newModel(NULL, true));

  auto * m = dm->getModel();

  auto * pFunc = new CKinFunction("test");
  REQUIRE(pFunc->setInfix("(1-a*I)*k*A*B") == true);

  auto & vars = pFunc->getVariables();

  for (auto & var : vars)
    {
      if (var.getObjectName() == "A" || var.getObjectName() == "B")
        var.setUsage(CFunctionParameter::Role::SUBSTRATE);

      else if (var.getObjectName() == "I")
        var.setUsage(CFunctionParameter::Role::MODIFIER);

      else
        var.setUsage(CFunctionParameter::Role::PARAMETER);
    }

  auto * db = CRootContainer::getFunctionList();
  REQUIRE(db->add(pFunc, true));

  auto * r = m->createReaction("R1");
  REQUIRE(r->setReactionScheme("S1 + S2 -> S3") == true);

  auto * info = new CReactionInterface();
  info->init(*r);
  info->setFunctionAndDoMapping("test");

  // does not work because of the modifier
  REQUIRE(info->isValid() == false);

  // create modifier
  REQUIRE(r->setReactionScheme("S1 + S2 -> S3; I") == true);
  info->init(*r);
  info->setFunctionAndDoMapping("test");

  // now it should work
  REQUIRE(info->isValid() == true);
  REQUIRE(info->writeBackToReaction(r));

  REQUIRE(r->compile() == true);
  REQUIRE(r->getFunction()->getObjectName() == "test");

  CRootContainer::removeDatamodel(dm);
}

TEST_CASE("changing from global to local variable", "[copasi,creation]")
{
  auto * dm = CRootContainer::addDatamodel();
  REQUIRE(dm != NULL);

  REQUIRE(dm->newModel(NULL, true));

  auto * m = dm->getModel();

  auto * p = m->createModelValue("k_global");
  auto * r = m->createReaction("R");
  r->setReactionScheme("A -> B");

  {
    CReactionInterface info;
    info.init(*r);
    REQUIRE(info.isLocalValue(0) == true);
    REQUIRE(r->isLocalParameter(0));
    REQUIRE(info.writeBackToReaction(r, true) == true);
    info.setMapping(0, "k_global");
    REQUIRE(info.writeBackToReaction(r, true) == true);
    REQUIRE(info.isLocalValue(0) == false);
    REQUIRE(r->isLocalParameter(0) == false);
  }

  {
    CReactionInterface info;
    info.init(*r);
    REQUIRE(info.isLocalValue(0) == false);
    info.setLocalValue(0, 2.0);
    REQUIRE(info.isLocalValue(0) == true);
    REQUIRE(info.writeBackToReaction(r, true) == true);
    REQUIRE(r->isLocalParameter(0) == true);
  }

  CRootContainer::removeDatamodel(dm);
}
