#ifndef COMPUTEDISLOCATIONDENSITTY1DEIGENSTRAIN_H
#define COMPUTEDISLOCATIONDENSITTY1DEIGENSTRAIN_H

#include "ComputeEigenstrainBase.h"
#include "RankTwoTensor.h"

// Forward Declarations
class ComputeDislocationDensity1DEigenStrain;

template <>
InputParameters validParams<ComputeDislocationDensity1DEigenStrain>();

class ComputeDislocationDensity1DEigenStrain : public ComputeEigenstrainBase
{
public:
  ComputeDislocationDensity1DEigenStrain(const InputParameters & parameters);

protected:
  virtual void computeQpEigenstrain();

  virtual void computeQpDislocationDensity();

  virtual void computeQpPlasticSlip();

  const Real _n; // number of discrete dislocations

  const MaterialProperty<Real> & _b; // burgers vector in 1D

  MaterialProperty<Real> & _s; // plastic slip distribution

  MaterialProperty<Real> & _rho; // dislocation Density

  Real _min_x_subdomain; // min subdomain x coordinate

  Real _max_x_subdomain; // max subdomain x coordinate
};

inline Real
sign(Real x)
{
  return x >= 0.0 ? 1.0 : -1.0;
};

#endif
