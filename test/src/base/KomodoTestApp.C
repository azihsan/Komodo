//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "KomodoTestApp.h"
#include "KomodoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<KomodoTestApp>()
{
  InputParameters params = validParams<KomodoApp>();
  return params;
}

KomodoTestApp::KomodoTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  KomodoApp::registerObjectDepends(_factory);
  KomodoApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  KomodoApp::associateSyntaxDepends(_syntax, _action_factory);
  KomodoApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  KomodoApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    KomodoTestApp::registerObjects(_factory);
    KomodoTestApp::associateSyntax(_syntax, _action_factory);
    KomodoTestApp::registerExecFlags(_factory);
  }
}

KomodoTestApp::~KomodoTestApp() {}

void
KomodoTestApp::registerApps()
{
  registerApp(KomodoApp);
  registerApp(KomodoTestApp);
}

void
KomodoTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
KomodoTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
KomodoTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
KomodoTestApp__registerApps()
{
  KomodoTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
KomodoTestApp__registerObjects(Factory & factory)
{
  KomodoTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
KomodoTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  KomodoTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
KomodoTestApp__registerExecFlags(Factory & factory)
{
  KomodoTestApp::registerExecFlags(factory);
}
