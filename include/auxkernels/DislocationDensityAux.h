//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef DISLOCATIONDENSITYAUX
#define DISLOCATIONDENSITYAUX

#include "MaterialAuxBase.h"

// forward declarations

class DislocationDensityAux;

template <>
InputParameters validParams<DislocationDensityAux>();

class DislocationDensityAux : public MaterialAuxBase<Real>
{
public:
  DislocationDensityAux(const InputParameters & parameters);
  virtual ~DislocationDensityAux() {}

protected:
  virtual Real getRealValue();
};

#endif // DISLOCATIONDENSITYAUX
