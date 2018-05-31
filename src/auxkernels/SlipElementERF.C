#include "SlipElementERF.h"

template <>
InputParameters
validParams<SlipElementERF>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription(
      "Compute slip distribution due to dislocation density (positive and negative) of an element");
  params.addRequiredParam<Real>("x_center",
                                "Center of gaussian dislocation density on local coordinate-x");
  params.addParam<Real>("sigma", 1.0, "Spread of the curve (sigma)");
  params.addParam<unsigned int>("N", 100, "Number of discrete dislocations on one bundle");
  params.addParam<Real>("burgers_vector", 0.0001, "Burgers Vector");
  return params;
}

/// Construction of the SlipElemenERF object
SlipElementERF::SlipElementERF(const InputParameters & parameters)
  : AuxKernel(parameters),
    _x_center(getParam<Real>("x_center")),
    _sigma(getParam<Real>("sigma")),
    _N(getParam<unsigned int>("N")),
    _b(getParam<Real>("burgers_vector")),
    _x_min(_x_center - (3.0 * _sigma)),
    _x_max(_x_center + (3.0 * _sigma))
{
}

Real
SlipElementERF::computeValue()
{
  ///height of lamella
  Real h = _sigma;

  /// local x coordinate of bundle fed into cummulative distribution function equation
  Real x = _q_point[_qp](0);

  /// cummulative distribution function
  if (x >= _x_min && x <= _x_max)
    return _N * (sign(_b) * _b / (h * 2)) *
           (1 + std::erf(-(x - _x_center) / (std::sqrt(2) * _sigma)));

  else
    return 0;
}
