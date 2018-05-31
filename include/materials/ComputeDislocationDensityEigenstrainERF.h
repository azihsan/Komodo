#ifndef COMPUTEDISLOCATIONDENSITTYEIGENSTRAINERF_H
#define COMPUTEDISLOCATIONDENSITTYEIGENSTRAINERF_H

#include "ComputeEigenstrainBase.h"
#include "RankTwoTensor.h"

// Forward Declarations
class ComputeDislocationDensityEigenstrainERF;

template <>
InputParameters validParams<ComputeDislocationDensityEigenstrainERF>();

/**
* ComputeDislocationDensityEigenstrainERF  is class to calculate eigenstrain due to dislocation,
* slip
* element(_s_var) field is coupled into this object then
*
* _eigenstrain[_qp] = (_s_var_pos - _s_var_neg) * M .
*
* The eigenstrain itself will be fed into ComputeSmallStrain object so that we could get elastic
* strain(mechanical strain)
*/
class ComputeDislocationDensityEigenstrainERF : public ComputeEigenstrainBase
{
public:
  ComputeDislocationDensityEigenstrainERF(const InputParameters & parameters);

protected:
  /// virtual void function to calculate the eigenstrain on each quadrature point (Qp)
  virtual void computeQpEigenstrain();

  /// variable field value of positive slip distribution
  const VariableValue & _s_var_pos;

  /// variable field value of negative slip distribution
  const VariableValue & _s_var_neg;
};

#endif // COMPUTEDISLOCATIONDENSITTYEIGENSTRAIN_H
