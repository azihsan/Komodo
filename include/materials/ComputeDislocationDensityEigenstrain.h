#ifndef COMPUTEDISLOCATIONDENSITTYEIGENSTRAIN_H
#define COMPUTEDISLOCATIONDENSITTYEIGENSTRAIN_H

#include "ComputeEigenstrainBase.h"
#include "RankTwoTensor.h"

// Forward Declarations
class ComputeDislocationDensityEigenstrain;

template <>
InputParameters validParams<ComputeDislocationDensityEigenstrain>();

class ComputeDislocationDensityEigenstrain : public ComputeEigenstrainBase
{
public:
  ComputeDislocationDensityEigenstrain(const InputParameters & parameters);

protected:
  virtual void computeQpEigenstrain();

  const Real _b; // burgers vector in 1D

  const VariableValue & _s_var; //variable field value of slip distribution  

  MaterialProperty<Real> & _s; // plastic slip

};

inline Real
sign(Real x)
{
  return x >= 0.0 ? 1.0 : -1.0;
};

#endif
