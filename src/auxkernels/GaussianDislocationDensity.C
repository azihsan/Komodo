#include "GaussianDislocationDensity.h"
#include "MooseEnum.h"

template <>
InputParameters
validParams<GaussianDislocationDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Generate a bundle of dislocation density based on 1D Gaussian scalar field");
  params.addRequiredParam<Real>("x_center", "Center of gaussian dislocation density on local coordinate-x");
  params.addParam<Real>("sigma_x", 1.0, "Spread of the curve in the x direction (sigma_x)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  return params;
}

GaussianDislocationDensity::GaussianDislocationDensity(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _sigma_x(getParam<Real>("sigma_x")),
    _N(getParam<unsigned int>("N")),
    _x_min(_x_center - (3.0 * _sigma_x)),
    _x_max(_x_center + (3.0 * _sigma_x))
{
}

Real
GaussianDislocationDensity::computeValue()
{
  /// height of slip lamella
  Real h = 1;

  /// local x coordinate of bundle fed into 1D gaussian distribution equation
  Real x = _q_point[_qp](0);

  /// Amplitude of dislocation bundle
  Real A = _N / (h * _sigma_x * std::sqrt(2));


  /// Calculate the dislocation density field
  if (x >= _x_min && x <= _x_max)
    return A * std::exp(-(((x - _x_center) * (x - _x_center)) / (std::sqrt(2) * _sigma_x)));

  else
    return 0;
}
