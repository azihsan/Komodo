#include "SlipElement.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<SlipElement>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addClassDescription("Compute Slip due to dislocation density of an element");
  params.addRequiredCoupledVar("positive_dislocation", "positive dislocation");
  params.addRequiredCoupledVar("negative_dislocation", "negative dislocation");
  return params;
}

SlipElement::SlipElement(const InputParameters & parameters)
  : AuxKernel(parameters),
    _rho_positive(coupledValue("positive_dislocation")),
    _rho_negative(coupledValue("negative_dislocation")),
    _delta_x(0)
{
}

Real
SlipElement::computeValue()
{

  Real x_min = std::numeric_limits<Real>::max();
  Real x_max = std::numeric_limits<Real>::min();

  // Calculate delta x in one element
  for (unsigned int n = 0; n < _current_elem->n_nodes(); ++n)
  {
    const Node * node = _current_elem->node_ptr(n);
    if (node[0](0) < x_min)
      x_min = node[0](0);
    if (node[0](0) > x_max)
      x_max = node[0](0);
  }
  _delta_x = std::abs(x_max - x_min);

  Real K = _rho_positive[_qp] - _rho_negative[_qp]; // calculate excess density

  return K * _delta_x; // yields slip element
}
