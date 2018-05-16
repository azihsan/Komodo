#ifndef SLIPELEMENT_H
#define SLIPELEMENT_H

#include "AuxKernel.h"

// forward declarations

class SlipElement;

template <>
InputParameters validParams<SlipElement>();
/**
* This AuxKernel object is to geneated slip distribution field. It takes slip_element field of
*AuxVariables
* Two variables need to couple into this object, they are positive dislocation and negative
*dislocation.
*
* Later on, the slip_element field will be fed into materials object to calculate eigenstrain.
*
**/
class SlipElement : public AuxKernel
{
public:
  SlipElement(const InputParameters & parameters);

  virtual ~SlipElement() {}

protected:
  virtual Real computeValue() override;

  Real computeDeltaX();

  /// coupled variable hold the positive dislocation density
  const VariableValue & _rho_positive;

  /// coupled variable hold the negative dislocation density
  const VariableValue & _rho_negative;
};

#endif // SLIPELEMENT_H
