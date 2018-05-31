#ifndef GAUSSIANDISLOCATIONDENSITY_H
#define GAUSSIANDISLOCATIONDENSITY_H

#include "AuxKernel.h"

// forward declarations
class GaussianDislocationDensity;

template <>
InputParameters validParams<GaussianDislocationDensity>();

/**
* This AuxKernel object is used to generate a dislocation bundle based on 1D Gaussian Distribution.
* Later on this object will generate dislocation field either positive or negative dislocation.
* Note :
*
*   1. Continuum dilocation dynamic model for edge dislocations.
*
*   2. Since this is AuxKernel, an AuxVariable object(_rho_negative & _rho_positive)
*   need to be declared first then coupled with this object.
*
*   3. AuxVariable is set so that we have two dislocations,
*    there are positive dislocation and negative dislocation.
*/
class GaussianDislocationDensity : public AuxKernel
{
public:
  GaussianDislocationDensity(const InputParameters & parameters);

  virtual ~GaussianDislocationDensity() {}

protected:
  /// virtual real(double) function to calculate the variable field on each node/element
  virtual Real computeValue() override;

  /// Gaussian center coordinate-x
  const Real _x_center;

  /// sigma or spread
  const Real _sigma;

  /// number of dislocations of a bundle
  const unsigned int _N;

private:
  /// minimum local x coordinate of the bundle
  Real _x_min;

  /// maximum local x coordinate of the bundle
  Real _x_max;
};

#endif // GAUSSIANDISLOCATIONDENSITY_H
