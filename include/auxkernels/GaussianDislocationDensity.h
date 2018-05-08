#ifndef GAUSSIANDISLOCATIONDENSITY_H
#define GAUSSIANDISLOCATIONDENSITY_H

#include "AuxKernel.h"


class GaussianDislocationDensity;

template <>
InputParameters validParams<GaussianDislocationDensity>();
/**
* This AuxKernel object is used to generate dislocation based on 1D Gaussian Distribution.
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

// forward declarations

class GaussianDislocationDensity : public AuxKernel
{
public:
  GaussianDislocationDensity(const InputParameters & parameters);

  virtual ~GaussianDislocationDensity() {}

protected:
  virtual Real computeValue() override;

  const Real _x_center; // Gaussian center coordinate-x

  const Real _sigma_x; // sigma x or spread x

  const unsigned int _N; // number of dislocation of a bundle


private:
    Real _x_min;

    Real _x_max;

};

#endif // GAUSSIANDISLOCATIONDENSITY_H
