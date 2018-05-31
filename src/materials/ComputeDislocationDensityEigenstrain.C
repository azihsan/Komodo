#include "ComputeDislocationDensityEigenstrain.h"

template <>
InputParameters
validParams<ComputeDislocationDensityEigenstrain>()
{
  InputParameters params = validParams<ComputeEigenstrainBase>();
  params.addClassDescription(
      "Computes Eigenstrain based on gaussian dislocation density distribution");
  params.addRequiredCoupledVar("slip_distribution", "Slip distribution");
  return params;
}

ComputeDislocationDensityEigenstrain::ComputeDislocationDensityEigenstrain(
    const InputParameters & parameters)
  : ComputeEigenstrainBase(parameters), _s_var(coupledValue("slip_distribution"))
{
}

void
ComputeDislocationDensityEigenstrain::computeQpEigenstrain()
{
  RankTwoTensor M(0, 0, 0, 0, 0, 1); // shear_eigenstrain

  // eigenstrain on each element due to dislocation bundles
  _eigenstrain[_qp] = _s_var[_qp] * M;
}
