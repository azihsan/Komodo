//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "KomodoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// New Material in Tensor Mechanics
#include "ComputeDislocationDensity1DEigenStrain.h"
// New Aux kernel for exploit data from Dislocation density
#include "DislocationDensityAux.h"

// New MeshModifier for defining 1D dislocation bundle
#include "SubdomainDislocationBundle.h"

template <>
InputParameters
validParams<KomodoApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

KomodoApp::KomodoApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  KomodoApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  KomodoApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  KomodoApp::registerExecFlags(_factory);
}

KomodoApp::~KomodoApp() {}

void
KomodoApp::registerApps()
{
  registerApp(KomodoApp);
}

void
KomodoApp::registerObjects(Factory & factory)
{
  /* Uncomment Factory parameter and register your new production objects here! */

  // Register  dislocation density 1D eigenstrain
  registerMaterial(ComputeDislocationDensity1DEigenStrain);

  // new register dislocation density aux
  registerAux(DislocationDensityAux);

  // new register subdomain dislocation bundle
  registerMeshModifier(SubdomainDislocationBundle);
}

void
KomodoApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new production objects here! */
}

void
KomodoApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
KomodoApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
KomodoApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
KomodoApp__registerApps()
{
  KomodoApp::registerApps();
}

extern "C" void
KomodoApp__registerObjects(Factory & factory)
{
  KomodoApp::registerObjects(factory);
}

extern "C" void
KomodoApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  KomodoApp::associateSyntax(syntax, action_factory);
}

extern "C" void
KomodoApp__registerExecFlags(Factory & factory)
{
  KomodoApp::registerExecFlags(factory);
}
