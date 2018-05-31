#include "Slip2DGaussian.h"
#include "SlipElementERF.h"

template <>
InputParameters
validParams<Slip2DGaussian>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Compute 2D slip distribution due to dislocation density (positive "
                             "and negative) of an element");
  params.addRequiredParam<Real>("x_center",
                                "Center of gaussian dislocation density on local coordinate-x");
  params.addRequiredParam<Real>("y_center",
                                "Center of gaussian dislocation density on local coordinate-y");
  params.addParam<Real>("sigma", 1.0, "Spread of the curve (sigma)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  params.addParam<Real>("burgers_vector", 0.0001, "Burgers Vector");
  return params;
}

/// Construction of the Slip2DGaussian object
Slip2DGaussian::Slip2DGaussian(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _y_center(getParam<Real>("y_center")),
    _sigma(getParam<Real>("sigma")),
    _N(getParam<unsigned int>("N")),
    _b(getParam<Real>("burgers_vector")),
    _x_min(_x_center - (3.0 * _sigma)),
    _x_max(_x_center + (3.0 * _sigma)),
    _y_min(_y_center - (3.0 * _sigma)),
    _y_max(_y_center + (3.0 * _sigma))
{
}

Real
Slip2DGaussian::computeValue()
{
  /// local x coordinate of bundle fed into cummulative distribution function equation
  Real x = _q_point[_qp](0);

  /// local y coordinate of bundle fed into cummulative distribution function equation
  Real y = _q_point[_qp](1);

  /// Amplitude of slip
  Real A = (_N * sign(_b) * _b) * (2 * M_PI * _sigma * _sigma);

  /// calculate the slip field
  if (x >= _x_min && x <= _x_max && y >= _y_min && y <= _y_max)
    return A *
           std::exp(-(((x - _x_center) * (x - _x_center)) + ((y - _y_center) * (y - _y_center))) /
                    (2 * _sigma * _sigma));

  else
    return 0;
}
