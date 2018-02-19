#ifndef DISLOCATIONDENSITYAUX
#define DISLOCATIONDENSITYAUX

#include "MaterialAuxBase.h"

//forward declarations

class DislocationDensityAux;

template<>
InputParameters validParams<DislocationDensityAux>();

class DislocationDensityAux:public MaterialAuxBase<Real>
{
  public:
     DislocationDensityAux(const InputParameters & parameters);
     virtual ~DislocationDensityAux(){}

  protected:
    virtual Real getRealValue();

};

#endif //DISLOCATIONDENSITYAUX
