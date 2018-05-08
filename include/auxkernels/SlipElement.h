#ifndef SLIPELEMENT_H
#define SLIPELEMENT_H

#include "AuxKernel.h"

// forward declarations

class SlipElement;

template <>
InputParameters validParams<SlipElement>();

class SlipElement : public AuxKernel
{
public:
  SlipElement(const InputParameters & parameters);

  virtual ~SlipElement() {}

protected:
  virtual Real computeValue() override;

  const VariableValue & _rho_positive;

  const VariableValue & _rho_negative;

private:
  Real _delta_x;
};

#endif // SLIPELEMENT_H
