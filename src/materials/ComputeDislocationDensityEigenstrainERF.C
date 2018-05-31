#include "ComputeDislocationDensityEigenstrainERF.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<ComputeDislocationDensityEigenstrainERF>()
{
  InputParameters params = validParams<ComputeEigenstrainBase>();
  params.addClassDescription(
      "Computes Eigenstrain based on gaussian dislocation density distribution");
  params.addCoupledVar(
      "positive_dislocation_field", 0, "Slip distribution of positive dislocation");
  params.addCoupledVar(
      "negative_dislocation_field", 0, "Slip distribution of negative dislocation");
  return params;
}

ComputeDislocationDensityEigenstrainERF::ComputeDislocationDensityEigenstrainERF(
    const InputParameters & parameters)
  : ComputeEigenstrainBase(parameters),
    _s_var_pos(coupledValue("positive_dislocation_field")),
    _s_var_neg(coupledValue("negative_dislocation_field"))
{
}

void
ComputeDislocationDensityEigenstrainERF::computeQpEigenstrain()
{
  RankTwoTensor M(-1, 1, 0, 0, 0, 0); // shear_eigenstrain

  // eigenstrain on each element due to dislocation bundles
  _eigenstrain[_qp] = (_s_var_pos[_qp] - _s_var_neg[_qp]) * M;
}
