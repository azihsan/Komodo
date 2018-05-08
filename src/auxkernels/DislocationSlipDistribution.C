// #include "DislocationSlipDistribution.h"
//
//  // libMesh
// #include "libmesh/elem.h"
//
// template <>
// InputParameters
// validParams<DislocationSlipDistribution>()
// {
//   InputParameters params = validParams<AuxKernel>();
//   params.addClassDescription(
//       "Compute Slip distribution due to dislocation density of an element");
//   params.addRequiredCoupledVar("slip_element", "slip on each element due to dislocation");
//   return params;
// }
//
// DislocationSlipDistribution::DislocationSlipDistribution(const  InputParameters & parameters)
//   : AuxKernel(parameters),
//     _slip_i(coupledValue("slip_element"))
// {
// }
//
// Real
// DislocationSlipDistribution::LeftNeighborValue(const Elem * elem, unsigned int side)
// {
//   const Elem * neighbor = elem->neighbor_ptr(side);
//
// }
