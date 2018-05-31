#include "Slip3DGaussian.h"
#include "SlipElementERF.h"

template <>
InputParameters
validParams<Slip3DGaussian>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Compute 3D slip distribution due to dislocation density (positive "
                             "and negative) of an element");
  params.addRequiredParam<Real>("x_center",
                                "Center of gaussian dislocation density on local coordinate-x");
  params.addRequiredParam<Real>("y_center",
                                "Center of gaussian dislocation density on local coordinate-y");
  params.addRequiredParam<Real>("z_center",
                                "Center of gaussian dislocation density on local coordinate-z");
  params.addParam<Real>("sigma", 1.0, "Spread of the curve (sigma)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  params.addParam<Real>("burgers_vector", 0.0001, "Burgers Vector");
  return params;
}

/// Construction of the Slip3DGaussian object
Slip3DGaussian::Slip3DGaussian(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _y_center(getParam<Real>("y_center")),
    _z_center(getParam<Real>("z_center")),
    _sigma(getParam<Real>("sigma")),
    _N(getParam<unsigned int>("N")),
    _b(getParam<Real>("burgers_vector")),
    _x_min(_x_center - (3.0 * _sigma)),
    _x_max(_x_center + (3.0 * _sigma)),
    _y_min(_y_center - (3.0 * _sigma)),
    _y_max(_y_center + (3.0 * _sigma)),
    _z_min(_y_center - (3.0 * _sigma)),
    _z_max(_y_center + (3.0 * _sigma))
{
}

Real
Slip3DGaussian::computeValue()
{
  /// local x coordinate of bundle fed into cummulative distribution function equation
  Real x = _q_point[_qp](0);

  /// local y coordinate of bundle fed into cummulative distribution function equation
  Real y = _q_point[_qp](1);

  /// local z coordinate of bundle fed into cummulative distribution function equation
  Real z = _q_point[_qp](2);

  /// Amplitude of slip
  Real A =
      (_N * sign(_b) * _b) * (_sigma * _sigma * _sigma * std::sqrt(2 * 2 * 2 * M_PI * M_PI * M_PI));

  /// calculate the slip field
  if (x >= _x_min && x <= _x_max && y >= _y_min && y <= _y_max && z >= _z_min && y <= _z_max)
    return A * std::exp(-(((x - _x_center) * (x - _x_center)) / (2 * _sigma * _sigma) +
                          ((y - _y_center) * (y - _y_center)) / (2 * _sigma * _sigma) +
                          ((z - _z_center) * (z - _z_center)) / (2 * _sigma * _sigma)));
  else
    return 0;
}
