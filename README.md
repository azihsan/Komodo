Komodo (Kontinuum Dislocation on Moose Framework)
=====

As shown in [Wu R., Sandfeld S. (2016) Some Steps towards Modelling of Dislocation Assisted Rafting: A Coupled 2D Phase Field — Continuum Dislocation Dynamics Approach. In: The Minerals, Metals & Materials Society (eds) TMS 2016 145th Annual Meeting & Exhibition. Springer, Cham](https://link.springer.com/chapter/10.1007/978-3-319-48254-5_77#citeas) and [Schmitt, R., Kuhn, C., Müller, R., & Bhattacharya, K. (2014). Crystal plasticity and martensitic transformations—a phase field approach. Technische Mechanik, 34(1), 23-38.](http://www.uni-magdeburg.de/ifme/zeitschrift_tm/2014_Heft1/03_Schmitt.pdf) the initial dislocation and initial eigenstrain has to be generated in order to couple with Phase Field Method.

Initial dislocation will be generated by the gaussian distribution(1D or 2D scalar field) within the system, then will be calculated the slip distribution on the system. Finally, we ought to calculate initial Eigenstrain due to the dislocation.

Various objects handling this work such as
  - AuxKernels/GaussianDislocationDensity (generate 1D dislocation density)
  - AuxKernels/Slip2DGaussian (generate 2D gaussian slip field)
  - AuxKernels/Slip3DGaussian (generate 3D gaussian slip field)
  - AuxKernels/SlipElementERF (calculate Slip distribution element)
  - Materials/ComputeDislocationDensityEigenstrain (Materials object to calculate eigenstrain)

Example of using Komodo
  - 1D Gaussian Positive Dislocation, 2D Gaussian negative dislocation, Slip 2D, Slip 3D in test/tests/materials

For more information see: [http://mooseframework.org/create-an-app/](http://mooseframework.org/create-an-app/)
