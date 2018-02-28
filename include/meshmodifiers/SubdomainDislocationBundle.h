//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef SUBDOMAINDISLOCATIONBUNDLE_H
#define SUBDOMAINDISLOCATIONBUNDLE_H

// MOOSE Includes
#include "MooseEnum.h"
#include "MeshModifier.h"

// Forward Declaration
class SubdomainDislocationBundle;

template <>
InputParameters validParams<SubdomainDislocationBundle>();

namespace LibMesh
{
class BoundingBox;
}

class SubdomainDislocationBundle : public MeshModifier
{
public:
  SubdomainDislocationBundle(const InputParameters & parameters);

  virtual void modify() override;

private:
  /// ID location (inside of outside of box)
  MooseEnum _location;

  /// Block ID to assign to the region
  SubdomainID _block_id;

  /// Bounding box for testing element centroids against
  BoundingBox _bounding_box;
};

#endif // end SUBDOMAINDISLOCATIONBUNDLE_H
