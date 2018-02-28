//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "DislocationDensityAux.h"
#include "ComputeDislocationDensity1DEigenStrain.h"

template <>
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
DislocationDensityAux::getRealValue()
{
  return _prop[_qp];
}
