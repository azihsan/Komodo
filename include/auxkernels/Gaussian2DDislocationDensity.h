#ifndef GAUSSIAN2DDISLOCATIONDENSITY_H
#define GAUSSIAN2DDISLOCATIONDENSITY_H

#include "AuxKernel.h"

// forward declarations
class Gaussian2DDislocationDensity;

template <>
InputParameters validParams<Gaussian2DDislocationDensity>();

/**
* This AuxKernel object is used to generate a dislocation bundle based on 2D Gaussian Distribution.
* later on this object will generate dislocation field either positive or negative dislocation.
* Note :
*
*   1. Continuum dilocation dynamic model for edge dislocations.
*
*   2. Since this is AuxKernel, an AuxVariable object(_rho_negative & _rho_positive)
*   need to be declared first then coupled with this object.
*
*   3. AuxVariable is set so that we have two dislocations,
*    there are positive dislocation and negative dislocation.
*
*/

class Gaussian2DDislocationDensity : public AuxKernel
{
public:
  Gaussian2DDislocationDensity(const InputParameters & parameters);

  virtual ~Gaussian2DDislocationDensity() {}

protected:
  /// virtual real(double) function to calculate the variable field on each node/element
  virtual Real computeValue() override;

  /// Gaussian center coordinate-x
  const Real _x_center;

  /// Gaussian center coordinate-y
  const Real _y_center;

  /// sigma x or spread x
  const Real _sigma_x;

  /// sigma y or spread y
  const Real _sigma_y;

  /// number of dislocation of a bundle
  const unsigned int _N;

private:
  /// minimum local x coordinate of the bundle
  Real _x_min;

  /// maximum local x coordinate of the bundle
  Real _x_max;

  /// minimum local y coordinate of the bundle
  Real _y_min;

  /// maximum local y coordinate of the bundle
  Real _y_max;
};

#endif // GAUSSIAN2DDISLOCATIONDENSITY_H
