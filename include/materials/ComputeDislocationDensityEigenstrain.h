#ifndef COMPUTEDISLOCATIONDENSITTYEIGENSTRAIN_H
#define COMPUTEDISLOCATIONDENSITTYEIGENSTRAIN_H

#include "ComputeEigenstrainBase.h"
#include "RankTwoTensor.h"

// Forward Declarations
class ComputeDislocationDensityEigenstrain;

template <>
InputParameters validParams<ComputeDislocationDensityEigenstrain>();

/**
* ComputeDislocationDensityEigenstrain  is class to calculate eigenstrain due to dislocation, slip element(_s_var) field is coupled into this object then
*
* _eigenstrain[_qp] = sign(b) * b * _s_var.
*
* The eigenstrain itself will be fed into ComputeSmallStrain object so that we could get elastic strain(mechanical strain)
*/
class ComputeDislocationDensityEigenstrain : public ComputeEigenstrainBase
{
public:
  ComputeDislocationDensityEigenstrain(const InputParameters & parameters);

protected:
  /// virtual void function to calculate the eigenstrain on each quadrature point (Qp)
  virtual void computeQpEigenstrain();

  /// burgers vector in 1D
  const Real _b;

  /// variable field value of slip distribution
  const VariableValue & _s_var;

  /// plastic slip
  MaterialProperty<Real> & _s;
};

inline Real
sign(Real x)
{
  return x >= 0.0 ? 1.0 : -1.0;
};

#endif
