#ifndef GAUSSIAN2DDISLOCATIONDENSITY_H
#define GAUSSIAN2DDISLOCATIONDENSITY_H

#include "AuxKernel.h"

// forward declarations

class Gaussian2DDislocationDensity;

template <>
InputParameters validParams<Gaussian2DDislocationDensity>();

/**
* This AuxKernel object is used to generate dislocation based on 2D Gaussian Distribution.
* To be exact later on this object will generate dislocation field.
* Note :
*
*   1. Dislocation will act continuum-like dislocation dynamics.
*
*   2. Since this is AuxKernel, an AuxVariable object(_rho_negative & _rho_positive)
*   need to be declared first then coupled with this object.
*
*   3. AuxVariable is set so that we have two dislocations,
*    there are positive dislocation and negative dislocation.
*
**/

class Gaussian2DDislocationDensity : public AuxKernel
{
public:
  Gaussian2DDislocationDensity(const InputParameters & parameters);

  virtual ~Gaussian2DDislocationDensity() {}

protected:
  virtual Real computeValue() override;

  const Real _x_center; // Gaussian center coordinate-x

  const Real _y_center; // Gaussian center coordinate-y

  const Real _sigma_x; // sigma x or spread x

  const Real _sigma_y; // sigma y or spread y

  const unsigned int _N; // number of dislocation of a bundle


private:
    Real _x_min;

    Real _x_max;

    Real _y_min;

    Real _y_max;

};

#endif // GAUSSIAN2DDISLOCATIONDENSITY_H
