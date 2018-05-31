#ifndef SLIP2DGAUSSIAN_H
#define SLIP2DGAUSSIAN_H

#include "AuxKernel.h"

// forward declarations

class Slip2DGaussian;

template <>
InputParameters validParams<Slip2DGaussian>();
/**
* This AuxKernel object is to generated slip distribution field for 2D gaussian distribution. It
*takes slip_element field of
* AuxVariables
*
* Later on, the slip_element field will be fed into materials object to calculate eigenstrain.
*
**/
class Slip2DGaussian : public AuxKernel
{
public:
  Slip2DGaussian(const InputParameters & parameters);

  virtual ~Slip2DGaussian() {}

protected:
  /// virtual real(double) function to calculate the variable field on each node/element
  virtual Real computeValue() override;

  /// Gaussian center coordinate-x
  Real _x_center;

  /// Gaussian center coordinate-y
  Real _y_center;

  ///standard deviance or spread
  Real _sigma;

  /// number of dislocation on each bundle
  unsigned int _N;

  ///Burgers vector
  Real _b;

private:
  /// minimum local x coordinate of the bundle
  Real _x_min;

  /// maximum local y coordinate of the bundle
  Real _x_max;

  /// minimum local y coordinate of the bundle
  Real _y_min;

  /// maximum local y coordinate of the bundle
  Real _y_max;
};

#endif // SLIP2DGAUSSIAN_H
