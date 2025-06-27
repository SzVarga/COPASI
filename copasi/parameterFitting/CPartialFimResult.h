// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CPartialFimResult
#define COPASI_CPartialFimResult

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/core/CDataArray.h"
#include "copasi/core/CDataContainer.h"

#include "copasi/parameterFitting/CExperimentSet.h"


template < class CMatrixType >
class CMatrixInterface;
class CFitProblem;
class COptItem;

class CPartialFimResult : public CDataContainer
{
public:
  /**
   * constructor, with problem on which summary statistics are calculated
   */
  CPartialFimResult(CFitProblem* pProblem);

  /**
   * Destructor
   */
  ~CPartialFimResult();

  void print(std::ostream * ostream) const override;

private:

  CPartialFimResult(const CPartialFimResult& source);


  #pragma region // Methods

  /**
   * calculate the summary fisher information matrix for the experiments
   * @param vector of partial FIMs
   * @return Matrix containing the diagonal elements of the input matrices as rows
   */
  bool calcSummaryFIM(const std::vector< CMatrix< C_FLOAT64 > * > & iMatVec, CMatrix< C_FLOAT64 > & oMat);

  /**
   * calculate the summary sd Matrix for the experiments
   * @param Vector of SD-Vectors of the parameters
   * @return Matrix containing the SD-Vectors as rows
   */
  bool calcSummarySD(const std::vector< CVector< C_FLOAT64 > * > & iSDVec, CMatrix< C_FLOAT64 > & oMat);

  /**
   * calculate matrices containing relative values
   * @param  summary partial Matrix (FIM or CovM) and complete FIM or CovM
   * @return matrix containing relative entries
   */
  bool calcRelFIM(const CMatrix< C_FLOAT64 > & partial, const CMatrix< C_FLOAT64 > & complete, CMatrix< C_FLOAT64 > & relMat);

  /**
   * calculate matrix of relative standard deviation of parameters
   * @param  summary partial sd matrix and complete parameter sd vector
   * @return matrix containing change of parameter sd uppon discarding single experiment
   */
  bool calcRelSD(const CMatrix< C_FLOAT64 > & partial, const CVector< C_FLOAT64 > & complete, CMatrix< C_FLOAT64 > & relMat);

  /**
   * Calculate advanced statistics for the problem
   * All partial fisher information and covariance matrices are calculated
   * based on experiments used for parameter estimation
   */
  bool calculatePartialStatistics();

  /**
   * Retrieve the Relative Fisher Information content matrix of experiments.
   * @return CArrayAnnotation & relFIMatrix
   */
  CDataArray & getRelFisherInformation() const;

  /**
   * Retrieve the relative Standard Deviation change matrix of experiments.
   * @return CArrayAnnotation & relSDMatrix
   */
  CDataArray & getRelSDMatrix() const;

  #pragma endregion

  #pragma region // Attributes

  CExperimentSet& mpExperimentSet; ///< The experiment set to which the model is fitted.
  CFitProblem * mpProblem;          ///< The problem for which the partial statistics are calculated
  std::vector< COptItem * > * mpOptItems; ///< The vector of optimization items used for parameter estimation

  size_t mNumParameters; ///< The number of parameters in the problem
  size_t mNumExperiments; ///< The number of experiments in the problem

  const CMatrix< C_FLOAT64 > & mDeltaResidualDeltaParameter; ///< The Jacobian of the parameter estimation
  const CMatrix< C_FLOAT64 > & mDeltaResidualDeltaParameterScaled; ///< The scaled version of the Jacobian
  const CMatrix< C_FLOAT64 > & mFisherScaled; ///< The scaled Fisher information matrix
  const CVector< C_FLOAT64 > & mParameterSD;                       ///< The standard deviation of the parameters

  #pragma endregion

  #pragma region // Previous Attributes

  /**
   * The vectors of standard deviations of parameters
   * using subset of experiments selected for parameter estimation
   * Calculated for both a single experiment and all experiments
   * except one (excluded - X in the attribute name)
   */
  std::vector< CVector< C_FLOAT64 > * > mParParameterSDContainer;
  std::vector< CVector< C_FLOAT64 > * > mParParameterSDXContainer;
  std::vector< CVector< C_FLOAT64 > * > mScaledParParameterSDContainer;
  std::vector< CVector< C_FLOAT64 > * > mScaledParParameterSDXContainer;
  /**
   * Partial Fisher Information and Covariance matrices
   * based on a subset of experiments selected for parameter estimation
   * Matrices are calculated either based on a single experiment
   * or all experiments except one (excluded - X in the attribute name)
   */
  std::vector< CMatrix< C_FLOAT64 > * > mParFIMContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mParFIMXContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mScaledParFIMContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mScaledParFIMXContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mParCovMContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mParCovMXContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mScaledParCovMContainer;
  std::vector< CMatrix< C_FLOAT64 > * > mScaledParCovMXContainer;

  /**
   * Summary Partial Fisher Information and Standard deviations
   * of experiments selected for parameter estimation
   * Matrices are calculated either based on a single experiment
   * or all experiments except one (excluded - X in the attribute name)
   */
  CMatrix< C_FLOAT64 > mParFIM;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpParFIMInterface;
  CDataArray * mpParFIMatrix;
  CMatrix< C_FLOAT64 > mParFIMX;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpParFIMXInterface;
  CDataArray * mpParFIMXatrix;
  CMatrix< C_FLOAT64 > mScaledParFIM;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpScaledParFIMInterface;
  CDataArray * mpScaledParFIMatrix;
  CMatrix< C_FLOAT64 > mScaledParFIMX;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpScaledParFIMXInterface;
  CDataArray * mpScaledParFIMXatrix;
  CMatrix< C_FLOAT64 > mParParameterSD;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpParParameterSDInterface;
  CDataArray * mpParParameterSDMatrix;
  CMatrix< C_FLOAT64 > mParParameterSDX;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpParParameterSDXInterface;
  CDataArray * mpParParameterSDXMatrix;

  /**
   * The Relative Fisher Information matrix,
   * containing relative information content of single experiments on parameters
   */
  CMatrix< C_FLOAT64 > mRelFIM;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpRelFIMInterface;
  CDataArray * mpRelFIMatrix;

  /**
   * The Relative sd matrix, containing the relative
   * change of parameter sd, when a single experiment is neglected
   */
  CMatrix< C_FLOAT64 > mRelSD;
  CMatrixInterface< CMatrix< C_FLOAT64 > > * mpRelSDInterface;
  CDataArray * mpRelSDMatrix;

  #pragma endregion
};

#endif // COPASI_CPartialFimResult
