#include "Gaussian2DDislocationDensity.h"

template <>
InputParameters
validParams<Gaussian2DDislocationDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription(
      "Generate a bundle of dislocation density based on 2D Gaussian scalar field");
  params.addRequiredParam<Real>("x_center",
                                "Center of gaussian dislocation density on local coordinate-x");
  params.addRequiredParam<Real>("y_center",
                                "Center of gaussian dislocation density on local coordiante-y");
  params.addParam<Real>("sigma_x", 1.0, "Spread of the curve in the x direction (sigma_x)");
  params.addParam<Real>("sigma_y", 1.0, "Spread of the curve in the y direction (sigma_x)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  return params;
}

Gaussian2DDislocationDensity::Gaussian2DDislocationDensity(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _y_center(getParam<Real>("y_center")),
    _sigma_x(getParam<Real>("sigma_x")),
    _sigma_y(getParam<Real>("sigma_y")),
    _N(getParam<unsigned int>("N")),
    _x_min(_x_center - (3.0 * _sigma_x)),
    _x_max(_x_center + (3.0 * _sigma_x)),
    _y_min(_y_center - (3.0 * _sigma_y)),
    _y_max(_y_center + (3.0 * _sigma_y))
{
}

Real
Gaussian2DDislocationDensity::computeValue()
{
  /// height of slip lamella
  Real h = 1;

  /// local x coordinate of bundle fed into 2D gaussian distribution equation
  Real x = _q_point[_qp](0);

  /// local y coordinate of bundle fed into 2D gaussian distribution equation
  Real y = _q_point[_qp](1);

  /// Amplitude of dislocation bundle
  Real A = _N / (h * _sigma_x * std::sqrt(2));

  /// calculate the dislocation density field
  if (x >= _x_min && x <= _x_max && y >= _y_min && y <= _y_max)
    return A * std::exp(-(((x - _x_center) * (x - _x_center)) / (std::sqrt(2) * _sigma_x) +
                          ((y - _y_center) * (y - _y_center)) / (std::sqrt(2) * _sigma_y)));

  else
    return 0;
}
