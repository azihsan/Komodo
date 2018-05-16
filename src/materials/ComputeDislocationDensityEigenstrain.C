#include "ComputeDislocationDensityEigenstrain.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<ComputeDislocationDensityEigenstrain>()
{
  InputParameters params = validParams<ComputeEigenstrainBase>();
  params.addClassDescription(
      "Computes Eigenstrain based on gaussian dislocation density distribution");
  params.addParam<Real>("burgers_vector", 0.0001, "Burgers Vector");
  params.addRequiredCoupledVar("slip_distribution", "Slip distribution");
  return params;
}

ComputeDislocationDensityEigenstrain::ComputeDislocationDensityEigenstrain(
    const InputParameters & parameters)
  : ComputeEigenstrainBase(parameters),
    _b(getParam<Real>("burgers_vector")),
    _s_var(coupledValue("slip_distribution")),
    _s(declareProperty<Real>("plastic_slip"))
{
}

void
ComputeDislocationDensityEigenstrain::computeQpEigenstrain()
{
  RankTwoTensor M(1, 1, 1, 0, 0, 0); // shear_eigenstrain

  _s[_qp] = _s_var[_qp]; // passing value from aux variable to material slip property

  Real slip = sign(_b) * _b * _s[_qp];

  // eigenstrain on each element due to dislocation bundles
  _eigenstrain[_qp] = slip * M;
}
