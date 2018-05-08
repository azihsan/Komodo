// #ifndef DISLOCATIONSLIPDISTRIBUTION_H
// #define DISLOCATIONSLIPDISTRIBUTION_H
//
// #include "AuxKernel.h"
//
// // forward declarations
//
// class DislocationSlipDistribution;
//
// template <>
// InputParameters validParams<DislocationSlipDistribution>();
//
// class DislocationSlipDistribution : public AuxKernel
// {
// public:
//   DislocationSlipDistribution(const InputParameters & parameters);
//
//   virtual ~DislocationSlipDistribution() {}
//
// protected:
//
//   Real LeftNeighborValue(const Elem * elem);
//
//   virtual Real computeValue() override;
//
//   VariableValue &  _slip_i ;// coupled
//
// };
//
// #endif // GAUSSIANDISLOCATIONSLIPDISTRIBUTION_H
