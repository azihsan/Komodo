//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SubdomainDislocationBundle.h"
#include "Conversion.h"
#include "MooseMesh.h"

template <>
InputParameters
validParams<SubdomainDislocationBundle>()
{
  MooseEnum location("INSIDE OUTSIDE", "INSIDE");

  InputParameters params = validParams<MeshModifier>();
  params.addClassDescription("Changes the subdomain ID of elements either (XOR) inside or outside "
                             "the specified box to the specified ID.");
  params.addRequiredParam<RealVectorValue>("left",
                                           "The left point (in x,y with spaces in-between).");
  params.addRequiredParam<RealVectorValue>("right",
                                           "The right point (in x,y with spaces in-between).");
  params.addRequiredParam<SubdomainID>("block_id",
                                       "Subdomain id to set for inside/outside the bounding box");
  params.addParam<SubdomainName>(
      "block_name", "Subdomain name to set for inside/outside the bounding box (optional)");
  params.addParam<MooseEnum>(
      "location", location, "Control of where the subdomain id is to be set");

  return params;
}

SubdomainDislocationBundle::SubdomainDislocationBundle(const InputParameters & parameters)
  : MeshModifier(parameters),
    _location(getParam<MooseEnum>("location")),
    _block_id(getParam<SubdomainID>("block_id")),
    _bounding_box(getParam<RealVectorValue>("left"), getParam<RealVectorValue>("right"))
{
  // RealVectorValue left_y = getParam<RealVectorValue>("left");
  // RealVectorValue right_y = getParam<RealVectorValue>("right");
  //
  // if (left_y(1) != right_y(1))
  //   mooseError("left y component must equal to right y component");
}

void
SubdomainDislocationBundle::modify()
{
  // Check that we have access to the mesh
  if (!_mesh_ptr)
    mooseError("_mesh_ptr must be initialized before calling SubdomainDislocationBundle::modify()");

  MeshBase & mesh = _mesh_ptr->getMesh();

  // Loop over the elements
  for (const auto & elem : mesh.active_element_ptr_range())
  {
    bool contains = _bounding_box.contains_point(elem->centroid());
    if (contains && _location == "INSIDE")
      elem->subdomain_id() = _block_id;
    else if (!contains && _location == "OUTSIDE")
      elem->subdomain_id() = _block_id;
  }

  // Assign block name, if provided
  if (isParamValid("block_name"))
    mesh.subdomain_name(_block_id) = getParam<SubdomainName>("block_name");
}
