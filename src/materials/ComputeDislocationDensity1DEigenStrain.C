#include "ComputeDislocationDensity1DEigenStrain.h"
#include "MooseMesh.h"
#include <math.h>

template <>
InputParameters
validParams<ComputeDislocationDensity1DEigenStrain>()
{
  InputParameters params = validParams<ComputeEigenstrainBase>();
  params.addClassDescription("Computes Eigenstrain based on gaussian dislocation density distribution");
  params.addParam<unsigned int>("n", 100, "Number of discrete dislocations on one bundle");
  params.addParam<MaterialPropertyName>("burgers_vector", 0.0001, "Burgers Vector");

  return params;
}

ComputeDislocationDensity1DEigenStrain::ComputeDislocationDensity1DEigenStrain(const InputParameters & parameters)
  : ComputeEigenstrainBase(parameters),
  _n(getParam<unsigned int>("n")),
  _b(getMaterialProperty<Real>("burgers_vector")),
  _s(declareProperty<Real>("plastic_slip_distribution")),
  _rho(declareProperty<Real>("dislocation_density")),

  _min_x_subdomain(std::numeric_limits<Real>::max()),
  _max_x_subdomain(std::numeric_limits<Real>::min())
  {
    if (_constant_option != 1)
      mooseError("Material will only work on constant option element");

    const SubdomainID & domain_id = _current_subdomain_id;
    ConstElemRange *active_local_elems = _mesh.getActiveLocalElementRange();

    for (const auto & elem : *active_local_elems)
    {
      if (elem->subdomain_id() == domain_id)
        {
          for (unsigned int n = 0; n < elem->n_nodes(); ++n)
          {
              Node *node = const_cast<Node *>(elem->node_ptr(n));
              for (unsigned int i = 0; i < 1; ++i)
              {
                if (node[i](0) < _min_x_subdomain)
                  _min_x_subdomain = node[i](0);
                if (node[i](0) > _max_x_subdomain)
                  _max_x_subdomain = node[i](0);
              }
          }
        }

      }
  }
void ComputeDislocationDensity1DEigenStrain::computeQpDislocationDensity()
{
  Real h = 1 ; // height of slip lamella
  Real std_dev = 0.1 ; // standard deviation of the gaussian distribution

  //Normalize range of local coordinate
  Real xi = (2*_q_point[_qp](0) -_min_x_subdomain)/(_max_x_subdomain - _min_x_subdomain)-1;

  //Dislocation density on each element of bundle
   _rho[_qp] = _n / (h * std_dev * sqrt(2)) * exp(-(xi * xi)/(sqrt(2) * std_dev));
}

void ComputeDislocationDensity1DEigenStrain::computeQpPlasticSlip()
{
    // Plastic Slip each element
    // why element due to we use constant_on ELEMENT not qp
     _s[_qp] = sign(_b[_qp]) * _b[_qp] * _rho[_qp] * _q_point[_qp](0) ;
}

void ComputeDislocationDensity1DEigenStrain::computeQpEigenstrain()
{
  RankTwoTensor M(0, 0, 0, 0, 1, 1); // shear_eigenstrain

  computeQpDislocationDensity();

  computeQpPlasticSlip();

  // eigenstrain on each element due to dislocation bundles
   _eigenstrain[_qp] = _s[_qp] * M;
}
