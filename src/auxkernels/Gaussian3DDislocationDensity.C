#include "Gaussian3DDislocationDensity.h"

template <>
InputParameters
validParams<Gaussian3DDislocationDensity>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription(
      "Generate a bundle of dislocation density based on 3D Gaussian scalar field");
  params.addRequiredParam<Real>("x_center",
                                "Center of gaussian dislocation density on local coordinate-x");
  params.addRequiredParam<Real>("y_center",
                                "Center of gaussian dislocation density on local coordiante-y");
  params.addRequiredParam<Real>("z_center",
                                "Center of gaussian dislocation density on local coordiante-z");
  params.addParam<Real>("sigma_x", 1.0, "Spread of the curve in the x direction (sigma_x)");
  params.addParam<Real>("sigma_y", 1.0, "Spread of the curve in the y direction (sigma_x)");
  params.addParam<Real>("sigma_z", 1.0, "Spread of the curve in the y direction (sigma_z)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  return params;
}

Gaussian3DDislocationDensity::Gaussian3DDislocationDensity(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _y_center(getParam<Real>("y_center")),
    _z_center(getParam<Real>("z_center")),
    _sigma_x(getParam<Real>("sigma_x")),
    _sigma_y(getParam<Real>("sigma_y")),
    _sigma_z(getParam<Real>("sigma_z")),
    _N(getParam<unsigned int>("N")),
    _x_min(_x_center - (3.0 * _sigma_x)),
    _x_max(_x_center + (3.0 * _sigma_x)),
    _y_min(_y_center - (3.0 * _sigma_y)),
    _y_max(_y_center + (3.0 * _sigma_y)),
    _z_min(_z_center - (3.0 * _sigma_z)),
    _z_max(_z_center + (3.0 * _sigma_z))
{
}

Real
Gaussian3DDislocationDensity::computeValue()
{
  /// height of slip lamella
  Real h = 1;

  /// local x coordinate of bundle fed into 3D gaussian distribution equation
  Real x = _q_point[_qp](0);

  /// local y coordinate of bundle fed into 3D gaussian distribution equation
  Real y = _q_point[_qp](1);

  /// local z coordinate of bundle fed into 3D gaussian distribution equation
  Real z = _q_point[_qp](2);

  /// Amplitude of dislocation bundle
  Real A = _N / (h * _sigma_x * std::sqrt(2));

  /// calculate the dislocation density field
  if (x >= _x_min && x <= _x_max && y >= _y_min && y <= _y_max && z >= _z_min && y <= _z_max)
    return A * std::exp(-(((x - _x_center) * (x - _x_center)) / (std::sqrt(2) * _sigma_x) +
                          ((y - _y_center) * (y - _y_center)) / (std::sqrt(2) * _sigma_y) +
                          ((z - _z_center) * (z - _z_center)) / (std::sqrt(2) * _sigma_z)));

  else
    return 0;
}
