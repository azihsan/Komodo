#include "SlipElement.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<SlipElement>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription(
      "Compute slip distribution due to dislocation density (positive and negative) of an element");
  params.addRequiredCoupledVar("positive_dislocation", "positive dislocation");
  params.addRequiredCoupledVar("negative_dislocation", "negative dislocation");
  return params;
}

SlipElement::SlipElement(const InputParameters & parameters)
  : AuxKernel(parameters),
    _rho_positive(coupledValue("positive_dislocation")),
    _rho_negative(coupledValue("negative_dislocation"))
{
}
Real
SlipElement::computeDeltaX()
{
  Real x_min = std::numeric_limits<Real>::max();
  Real x_max = std::numeric_limits<Real>::min();

  /// Calculate delta x in one element
  for (unsigned int n = 0; n < _current_elem->n_nodes(); ++n)
  {
    const Node * node = _current_elem->node_ptr(n);
    if (node[0](0) < x_min)
      x_min = node[0](0);
    if (node[0](0) > x_max)
      x_max = node[0](0);
  }
  return std::abs(x_max - x_min);
}

Real
SlipElement::computeValue()
{
  /// calculate excess density
  Real K = _rho_positive[_qp] - _rho_negative[_qp];

  /// Slip element
  return K * computeDeltaX();
}
