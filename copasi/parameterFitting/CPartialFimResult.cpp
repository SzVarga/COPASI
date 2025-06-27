// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/parameterFitting/CPartialFimResult.h"

#include "copasi/parameterFitting/CFitProblem.h"
#include "copasi/parameterFitting/CFitItem.h"
#include "copasi/parameterFitting/CFitTask.h"
#include "copasi/parameterFitting/CExperimentSet.h"
#include "copasi/parameterFitting/CExperiment.h"


CPartialFimResult::CPartialFimResult(CFitProblem * pProblem)
  : CDataContainer("Partial FIM Results")
  , mpProblem(pProblem)
  , mpExperimentSet(pProblem->getExperimentSet())
  , mpOptItems(pProblem->mpOptItems)
  , mNumParameters(pProblem->mSolutionVariables.size())
  , mNumExperiments(mpExperimentSet.getExperimentCount())
  , mDeltaResidualDeltaParameter(pProblem->mDeltaResidualDeltaParameter)
  , mDeltaResidualDeltaParameterScaled(pProblem->mDeltaResidualDeltaParameterScaled)
  , mFisherScaled(pProblem->mFisherScaled)
  , mParameterSD(pProblem->mParameterSD)
  , mParParameterSDContainer(0)
  , mParParameterSDXContainer(0)
  , mScaledParParameterSDContainer(0)
  , mScaledParParameterSDXContainer(0)
  , mParFIMContainer(0)
  , mParFIMXContainer(0)
  , mScaledParFIMContainer(0)
  , mScaledParFIMXContainer(0)
  , mParFIM(0, 0)
  , mpParFIMInterface(NULL)
  , mpParFIMatrix(NULL)
  , mParFIMX(0, 0)
  , mpParFIMXInterface(NULL)
  , mpParFIMXatrix(NULL)
  , mScaledParFIM(0, 0)
  , mpScaledParFIMInterface(NULL)
  , mpScaledParFIMatrix(NULL)
  , mScaledParFIMX(0, 0)
  , mpScaledParFIMXInterface(NULL)
  , mpScaledParFIMXatrix(NULL)
  , mRelFIM(0, 0)
  , mpRelFIMInterface(NULL)
  , mpRelFIMatrix(NULL)
  , mRelSD(0, 0)
  , mpRelSDInterface(NULL)
  , mpRelSDMatrix(NULL)
  , mParCovMContainer(0)
  , mParCovMXContainer(0)
  , mScaledParCovMContainer(0)
  , mScaledParCovMXContainer(0)
  , mParParameterSD(0, 0)
  , mpParParameterSDInterface(NULL)
  , mpParParameterSDMatrix(NULL)
  , mParParameterSDX(0, 0)
  , mpParParameterSDXInterface(NULL)
  , mpParParameterSDXMatrix(NULL)

{
  calculatePartialStatistics();
}


CPartialFimResult::CPartialFimResult(const CPartialFimResult& src)
  : CDataContainer(src, NO_PARENT)
  , mpProblem(src.mpProblem)
  , mpExperimentSet(src.mpExperimentSet)
  , mpOptItems(src.mpOptItems)
  , mNumParameters(src.mNumParameters)
  , mNumExperiments(src.mNumExperiments)
  , mDeltaResidualDeltaParameter(src.mDeltaResidualDeltaParameter)
  , mDeltaResidualDeltaParameterScaled(src.mDeltaResidualDeltaParameterScaled)
  , mFisherScaled(src.mFisherScaled)
  , mParameterSD(src.mParameterSD)
  , mParParameterSDContainer(src.mParParameterSDContainer.begin(), src.mParParameterSDContainer.end())
  , mParParameterSDXContainer(src.mParParameterSDXContainer.begin(), src.mParParameterSDXContainer.end())
  , mScaledParParameterSDContainer(src.mScaledParParameterSDContainer.begin(), src.mScaledParParameterSDContainer.end())
  , mScaledParParameterSDXContainer(src.mScaledParParameterSDXContainer.begin(), src.mScaledParParameterSDXContainer.end())
  , mParFIMContainer(src.mParFIMContainer.begin(), src.mParFIMContainer.end())
  , mParFIMXContainer(src.mParFIMXContainer.begin(), src.mParFIMXContainer.end())
  , mScaledParFIMContainer(src.mScaledParFIMContainer.begin(), src.mScaledParFIMContainer.end())
  , mScaledParFIMXContainer(src.mScaledParFIMXContainer.begin(), src.mScaledParFIMXContainer.end())
  , mParFIM(src.mParFIM)
  , mpParFIMInterface(src.mpParFIMInterface)
  , mpParFIMatrix(src.mpParFIMatrix)
  , mParFIMX(src.mParFIMX)
  , mpParFIMXInterface(src.mpParFIMXInterface)
  , mpParFIMXatrix(src.mpParFIMXatrix)
  , mScaledParFIM(src.mScaledParFIM)
  , mpScaledParFIMInterface(src.mpScaledParFIMInterface)
  , mpScaledParFIMatrix(src.mpScaledParFIMatrix)
  , mScaledParFIMX(src.mScaledParFIMX)
  , mpScaledParFIMXInterface(src.mpScaledParFIMXInterface)
  , mpScaledParFIMXatrix(src.mpScaledParFIMXatrix)
  , mRelFIM(src.mRelFIM)
  , mpRelFIMInterface(src.mpRelFIMInterface)
  , mpRelFIMatrix(src.mpRelFIMatrix)
  , mRelSD(src.mRelSD)
  , mpRelSDInterface(src.mpRelSDInterface)
  , mpRelSDMatrix(src.mpRelSDMatrix)
  , mParCovMContainer(src.mParCovMContainer.begin(), src.mParCovMContainer.end())
  , mParCovMXContainer(src.mParCovMXContainer.begin(), src.mParCovMXContainer.end())
  , mScaledParCovMContainer(src.mScaledParCovMContainer.begin(), src.mScaledParCovMContainer.end())
  , mScaledParCovMXContainer(src.mScaledParCovMXContainer.begin(), src.mScaledParCovMXContainer.end())
  , mParParameterSD(src.mParParameterSD)
  , mpParParameterSDInterface(src.mpParParameterSDInterface)
  , mpParParameterSDMatrix(src.mpParParameterSDMatrix)
  , mParParameterSDX(src.mParParameterSDX)
  , mpParParameterSDXInterface(src.mpParParameterSDXInterface)
  , mpParParameterSDXMatrix(src.mpParParameterSDXMatrix)

{
  // Add copy logic here when needed
}


CPartialFimResult::~CPartialFimResult()
{
  // Delete all partial matrices and sd vectors
  for (size_t i{}; i < mParFIMContainer.size(); ++i)
    {
      pdelete(mParFIMContainer.at(i));
      pdelete(mParFIMXContainer.at(i));
      pdelete(mScaledParFIMContainer.at(i));
      pdelete(mScaledParFIMXContainer.at(i));

      pdelete(mParCovMContainer.at(i));
      pdelete(mParCovMXContainer.at(i));
      pdelete(mScaledParCovMContainer.at(i));
      pdelete(mScaledParCovMXContainer.at(i));

      pdelete(mParParameterSDContainer.at(i));
      pdelete(mParParameterSDXContainer.at(i));
      pdelete(mScaledParParameterSDContainer.at(i));
      pdelete(mScaledParParameterSDXContainer.at(i));
    }

  // Delete all summary partial matrices
  pdelete(mpParFIMInterface);
  pdelete(mpParFIMatrix);
  pdelete(mpParFIMXInterface);
  pdelete(mpParFIMXatrix);
  pdelete(mpScaledParFIMInterface);
  pdelete(mpScaledParFIMatrix);
  pdelete(mpScaledParFIMXInterface);
  pdelete(mpScaledParFIMXatrix);
  pdelete(mpParParameterSDInterface);
  pdelete(mpParParameterSDMatrix);
  pdelete(mpParParameterSDXInterface);
  pdelete(mpParParameterSDXMatrix);
  pdelete(mpRelFIMInterface);
  pdelete(mpRelFIMatrix);
  pdelete(mpRelSDInterface);
  pdelete(mpRelSDMatrix);
}

void CPartialFimResult::print(std::ostream * ostream) const
{
  if (!ostream)
    return;

  for (size_t i = 0; i < mScaledParFIMContainer.size(); ++i)
    {
      std::cout << "Scaled Fisher M for Exp: " << i << std::endl;
      std::cout << *(mScaledParFIMContainer.at(i)) << std::endl;
      std::cout << std::endl;
    }
}

bool CPartialFimResult::calcSummaryFIM(const std::vector< CMatrix< double > * > & iMatVec, CMatrix< double > & oMat)
{
  if (!(iMatVec.size() > 0))
    return false;

  size_t imax, jmax;
  imax = iMatVec.size();           //number of experiments
  jmax = iMatVec.at(0)->numRows(); //number of parameters
  oMat.resize(imax, jmax);

  for (size_t i{}; i < imax; ++i)
    {
      const CMatrix< C_FLOAT64 > & iMat = *(iMatVec.at(i));
      for (size_t j{}; j < jmax; ++j)
        {
          oMat(i, j) = iMat(j, j);
        }
    }
  return true;
}

bool CPartialFimResult::calcSummarySD(const std::vector< CVector< double > * > & iSDVec, CMatrix< double > & oMat)
{
  if (!(iSDVec.size() > 0))
    return false;

  size_t imax, jmax;
  imax = iSDVec.size();        //number of experiments
  jmax = iSDVec.at(0)->size(); //number of parameters
  oMat.resize(imax, jmax);

  for (size_t i{}; i < imax; ++i)
    {
      const CVector< C_FLOAT64 > & SDVec = *(iSDVec.at(i));
      for (size_t j{}; j < jmax; ++j)
        {
          oMat(i, j) = SDVec[j];
        }
    }
  return true;
}

bool CPartialFimResult::calcRelFIM(const CMatrix< double > & partial, const CMatrix< double > & complete, CMatrix< double > & relMat)
{
  size_t imax{partial.numRows()};
  size_t jmax{partial.numCols()};

  for (size_t i{}; i < imax; ++i)
    {
      for (size_t j{}; j < jmax; ++j)
        {
          relMat(i, j) = partial(i, j) / complete(j, j);
        }
    }
  return true;
}

bool CPartialFimResult::calcRelSD(const CMatrix< C_FLOAT64 > & partial, const CVector< C_FLOAT64 > & complete, CMatrix< C_FLOAT64 > & relMat)
{
  size_t imax{partial.numRows()};
  size_t jmax{partial.numCols()};

  relMat.resize(imax, jmax);

  //calculate entries of relSD matrix
  for (size_t i{}; i < imax; ++i)
    {
      for (size_t j{}; j < jmax; ++j)
        {
          relMat(i, j) = (partial(i, j) / complete[j]) - 1;
        }
    }
  return (true);
}


bool CPartialFimResult::calculatePartialStatistics()
{
  /* Only calculate if regular statistics is also calculated */
  //if(!(*mpParmCalculateStatistics) || !(*mpParmCalculatePartialStatistics))
  //  return false;

  /* Calculation of partial matrices */
  std::vector< size_t > ExperimentStartInResiduals = {0};
  CExperiment * pExperiment;
  size_t i{}, imax{mNumExperiments};
  size_t jmax{mNumParameters}; /* Number of parameters */
  size_t expStart{};

  // Resize partial matrices and partial sd vectors
  mParFIMContainer.resize(imax);
  mParFIMXContainer.resize(imax);
  mScaledParFIMContainer.resize(imax);
  mScaledParFIMXContainer.resize(imax);

  mParCovMContainer.resize(imax);
  mParCovMXContainer.resize(imax);
  mScaledParCovMContainer.resize(imax);
  mScaledParCovMXContainer.resize(imax);

  mParParameterSDContainer.resize(imax);
  mParParameterSDXContainer.resize(imax);
  mScaledParParameterSDContainer.resize(imax);
  mScaledParParameterSDXContainer.resize(imax);

  // Iterate through all experiments
  for (i = 0; i < imax; ++i)
    {
      // Get starting residual for next experiment
      pExperiment = mpExperimentSet.getExperiment(i);
      expStart += pExperiment->getNumDataRows() * pExperiment->getDependentObjectsMap().size();
      ExperimentStartInResiduals.push_back(expStart);

      // Initiate partial fisher matrices
      mParFIMContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mParFIMXContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mScaledParFIMContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mScaledParFIMXContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);

      // Initiate covariance matrices
      mParCovMContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mParCovMXContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mScaledParCovMContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);
      mScaledParCovMXContainer.at(i) = new CMatrix< C_FLOAT64 >(0, 0);

      // Initiate partial parameter sd vectors
      mParParameterSDContainer.at(i) = new CVector< C_FLOAT64 >(0);
      mParParameterSDXContainer.at(i) = new CVector< C_FLOAT64 >(0);
      mScaledParParameterSDContainer.at(i) = new CVector< C_FLOAT64 >(0);
      mScaledParParameterSDXContainer.at(i) = new CVector< C_FLOAT64 >(0);

      // Calculate unscaled partial fisher information matrices
      // Single experiment only
      mpProblem->calcPartialFIM(mDeltaResidualDeltaParameter, *(mParFIMContainer.at(i)),
                     ExperimentStartInResiduals[i], ExperimentStartInResiduals[i + 1], false);
      // Single experiment excluded
      mpProblem->calcPartialFIM(mDeltaResidualDeltaParameter, *(mParFIMXContainer.at(i)),
                     ExperimentStartInResiduals[i], ExperimentStartInResiduals[i + 1], true);

      // Calculate scaled partial fisher information matrices
      // Single experiment only
      mpProblem->calcPartialFIM(mDeltaResidualDeltaParameterScaled, *(mScaledParFIMContainer.at(i)),
                     ExperimentStartInResiduals[i], ExperimentStartInResiduals[i + 1], false);
      // Single experiment excluded
      mpProblem->calcPartialFIM(mDeltaResidualDeltaParameterScaled, *(mScaledParFIMXContainer.at(i)),
                     ExperimentStartInResiduals[i], ExperimentStartInResiduals[i + 1], true);

      // Calculate covariance matrices and parameter sd based on unscaled FIM
      // Single experiment only
      mpProblem->calcCov(*(mParFIMContainer.at(i)), *(mParCovMContainer.at(i)), *(mParParameterSDContainer.at(i)), true);
      // Single experiment excluded
      mpProblem->CFitProblem::calcCov(*(mParFIMXContainer.at(i)), *(mParCovMXContainer.at(i)), *(mParParameterSDXContainer.at(i)), true);

      // Calculate covariance matrices and parameter based on scaled FIM
      // Single experiment only
      mpProblem->calcCov(*(mScaledParFIMContainer.at(i)), *(mScaledParCovMContainer.at(i)), *(mScaledParParameterSDContainer.at(i)), true);
      // Single experiment excluded
      mpProblem->calcCov(*(mScaledParFIMXContainer.at(i)), *(mScaledParCovMXContainer.at(i)), *(mScaledParParameterSDXContainer.at(i)), true);
    }

  /* Calculation of summary matrices */
  // Initiate summary matrices
  mpParFIMInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mParFIM);
  mpParFIMatrix = new CDataArray("Summary unscaled Fisher Information", this, mpParFIMInterface, false);
  mpParFIMatrix->setDescription("Individual experiment considered only");
  mpParFIMatrix->setDimensionDescription(0, "Experiments");
  mpParFIMatrix->setDimensionDescription(1, "Parameters");
  mpParFIMatrix->setMode(CDataArray::Mode::Strings);
  mpParFIMXInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mParFIMX);
  mpParFIMXatrix = new CDataArray("Summary unscaled Fisher Information", this, mpParFIMXInterface, false);
  mpParFIMXatrix->setDescription("Individual experiment excluded");
  mpParFIMXatrix->setDimensionDescription(0, "Experiments");
  mpParFIMXatrix->setDimensionDescription(1, "Parameters");
  mpParFIMXatrix->setMode(CDataArray::Mode::Strings);
  mpScaledParFIMInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mScaledParFIM);
  mpScaledParFIMatrix = new CDataArray("Summary scaled Fisher Information", this, mpScaledParFIMInterface, false);
  mpScaledParFIMatrix->setDescription("Individual experiment considered only");
  mpScaledParFIMatrix->setDimensionDescription(0, "Experiments");
  mpScaledParFIMatrix->setDimensionDescription(1, "Parameters");
  mpScaledParFIMatrix->setMode(CDataArray::Mode::Strings);
  mpScaledParFIMXInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mScaledParFIMX);
  mpScaledParFIMXatrix = new CDataArray("Summary scaled Fisher Information", this, mpScaledParFIMXInterface, false);
  mpScaledParFIMXatrix->setDescription("Individual experiment excluded");
  mpScaledParFIMXatrix->setDimensionDescription(0, "Experiments");
  mpScaledParFIMXatrix->setDimensionDescription(1, "Parameters");
  mpScaledParFIMXatrix->setMode(CDataArray::Mode::Strings);
  mpParParameterSDInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mParParameterSD);
  mpParParameterSDMatrix = new CDataArray("Summary sd matrix", this, mpParParameterSDInterface, false);
  mpParParameterSDMatrix->setDescription("Individual experiment considered only");
  mpParParameterSDMatrix->setDimensionDescription(0, "Experiments");
  mpParParameterSDMatrix->setDimensionDescription(1, "Parameters");
  mpParParameterSDMatrix->setMode(CDataArray::Mode::Strings);
  mpParParameterSDXInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mParParameterSDX);
  mpParParameterSDXMatrix = new CDataArray("Summary sd matrix", this, mpParParameterSDXInterface, false);
  mpParParameterSDXMatrix->setDescription("Individual experiment excluded");
  mpParParameterSDXMatrix->setDimensionDescription(0, "Experiments");
  mpParParameterSDXMatrix->setDimensionDescription(1, "Parameters");
  mpParParameterSDXMatrix->setMode(CDataArray::Mode::Strings);

  mpRelFIMInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mRelFIM);
  mpRelFIMatrix = new CDataArray("Relative Fisher Information content", this, mpRelFIMInterface, false);
  mpRelFIMatrix->setDescription("Scaled Fisher Information of single experiment on parameter");
  mpRelFIMatrix->setDimensionDescription(0, "Experiments");
  mpRelFIMatrix->setDimensionDescription(1, "Parameters");
  mpRelFIMatrix->setMode(CDataArray::Mode::Strings);
  mpRelSDInterface = new CMatrixInterface< CMatrix< C_FLOAT64 > >(&mRelSD);
  mpRelSDMatrix = new CDataArray("Relative Change in parameter sd", this, mpRelSDInterface, false);
  mpRelSDMatrix->setDescription("Change in parameter standard deviation when single experiment is excluded");
  mpRelSDMatrix->setDimensionDescription(0, "Experiments");
  mpRelSDMatrix->setDimensionDescription(1, "Parameters");
  mpRelSDMatrix->setMode(CDataArray::Mode::Strings);

  // Resize summary matrices
  mParFIM.resize(imax, jmax);
  mpParFIMatrix->resize();
  mParFIMX.resize(imax, jmax);
  mpParFIMXatrix->resize();
  mScaledParFIM.resize(imax, jmax);
  mpScaledParFIMatrix->resize();
  mScaledParFIMX.resize(imax, jmax);
  mpScaledParFIMXatrix->resize();
  mParParameterSD.resize(imax, jmax);
  mpParParameterSDMatrix->resize();
  mParParameterSDX.resize(imax, jmax);
  mpParParameterSDXMatrix->resize();

  mRelFIM.resize(imax, jmax);
  mpRelFIMatrix->resize();
  mRelSD.resize(imax, jmax);
  mpRelSDMatrix->resize();

  // Calculate matrices
  calcSummaryFIM(mParFIMContainer, mParFIM);
  calcSummaryFIM(mParFIMXContainer, mParFIMX);
  calcSummaryFIM(mScaledParFIMContainer, mScaledParFIM);
  calcSummaryFIM(mScaledParFIMXContainer, mScaledParFIMX);
  calcSummarySD(mParParameterSDContainer, mParParameterSD);
  calcSummarySD(mParParameterSDXContainer, mParParameterSDX);

  calcRelFIM(mScaledParFIM, mFisherScaled, mRelFIM);
  calcRelSD(mParParameterSDX, mParameterSD, mRelSD);

  /* Annotations */
  std::vector< COptItem * >::iterator it = mpOptItems->begin();
  std::vector< COptItem * >::iterator end = mpOptItems->end();
  CFitItem * pItem;

  // Annotation on experiments
  for (i = 0; i < imax; ++i)
    {
      CExperiment * pExperiment = mpExperimentSet.getExperiment(i);

      std::string Annotation{pExperiment->getObjectName()};
      mpParFIMatrix->setAnnotationString(0, i, Annotation);
      mpParFIMXatrix->setAnnotationString(0, i, Annotation);
      mpScaledParFIMatrix->setAnnotationString(0, i, Annotation);
      mpScaledParFIMXatrix->setAnnotationString(0, i, Annotation);
      mpParParameterSDMatrix->setAnnotationString(0, i, Annotation);
      mpParParameterSDXMatrix->setAnnotationString(0, i, Annotation);

      mpRelFIMatrix->setAnnotationString(0, i, Annotation);
      mpRelSDMatrix->setAnnotationString(0, i, Annotation);
    }

  // Annotations on parameters
  for (size_t k{0}; it != end; ++it, k++)
    {
      pItem = dynamic_cast< CFitItem * >(*it);

      if (pItem == NULL)
        return false;

      std::string Annotation{pItem->getObjectDisplayName()};
      mpParFIMatrix->setAnnotationString(1, k, Annotation);
      mpParFIMXatrix->setAnnotationString(1, k, Annotation);
      mpScaledParFIMatrix->setAnnotationString(1, k, Annotation);
      mpScaledParFIMXatrix->setAnnotationString(1, k, Annotation);
      mpParParameterSDMatrix->setAnnotationString(1, k, Annotation);
      mpParParameterSDXMatrix->setAnnotationString(1, k, Annotation);

      mpRelFIMatrix->setAnnotationString(1, k, Annotation);
      mpRelSDMatrix->setAnnotationString(1, k, Annotation);
    }

  // Code testing
  /*
  std::cout << *mpParFIMatrix << std::endl;
  std::cout << "Testing of code:" << std::endl;
  std::cout << "Experiments: " << imax << " Parameters: " << jmax << std::endl;
  std::cout << mParParameterSDX << std::endl;
  std::cout << mParameterSD << std::endl;
  std::cout << mRelSD << std::endl;
  */
  
  print(&std::cout);

  // Clean up
  //pdelete(pExperiment);
  //pdelete(pItem);

  // Everything went well
  return true;
}

CDataArray & CPartialFimResult::getRelFisherInformation() const
{
  return *mpRelFIMatrix;
}

CDataArray & CPartialFimResult::getRelSDMatrix() const
{
  return *mpRelSDMatrix;
}