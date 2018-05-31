#ifndef SLIPELEMENTERF_H
#define SLIPELEMENTERF_H

#include "AuxKernel.h"

// forward declarations

class SlipElementERF;

template <>
InputParameters validParams<SlipElementERF>();
/**
* This AuxKernel object is to generated slip distribution field for 1D gaussian distribution. It
*takes slip_element field of
* AuxVariables
*
* Later on, the slip_element field will be fed into materials object to calculate eigenstrain.
*
**/
class SlipElementERF : public AuxKernel
{
public:
  SlipElementERF(const InputParameters & parameters);

  virtual ~SlipElementERF() {}

protected:
  /// virtual real(double) function to calculate the variable field on each node/element
  virtual Real computeValue() override;

  /// Gaussian center coordinate-x
  Real _x_center;

  ///standard deviance or spread
  Real _sigma;

  /// number of dislocation of a bundle
  unsigned int _N;

  /// Burgers vector
  Real _b;

private:
  /// minimum local x coordinate of the bundle
  Real _x_min;

  /// maximum local x coordinate of the bundle
  Real _x_max;
};

/// signum function
inline Real
sign(Real x)
{
  return x >= 0.0 ? 1.0 : -1.0;
};

#endif // SLIPELEMENTERF_H
