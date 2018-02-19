#include "DislocationDensityAux.h"
#include "ComputeDislocationDensity1DEigenStrain.h"

template<>
InputParameters
validParams<DislocationDensityAux>()
{
  InputParameters params = validParams<MaterialAuxBase<Real>>();
  params.addClassDescription("Exploit the dislocation density data in each element");
  return params;
}

DislocationDensityAux::DislocationDensityAux(const InputParameters & parameters)
: MaterialAuxBase<Real>(parameters)
  {
  }

Real
DislocationDensityAux::getRealValue(){
  return _prop[_qp];
}
