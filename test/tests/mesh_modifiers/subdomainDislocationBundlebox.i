[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 10
  xmax = 1
  ymax = 1
[]

[MeshModifiers]
  [./subdomain_dislocation_bundle1]
    type = SubdomainDislocationBundle
    left = '0.1 0.0 0'
    right = '0.9 0.1 0'
    block_id = 1
  [../]
  [./subdomain_dislocation_bundle2]
    type = SubdomainDislocationBundle
    left = '0.1 0.3 0'
    right = '0.9 0.4 0'
    block_id = 2
  [../]

  [./subdomain_dislocation_bundle3]
    type = SubdomainDislocationBundle
    left = '0.1 0.6 0'
    right = '0.9 0.7 0'
    block_id = 3
  [../]

[]

[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
[]

[AuxVariables]

  [./strain_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./strain_xx]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./strain_zz]
    order = CONSTANT
    family = MONOMIAL
  [../]

  [./dislocation_density]
    order = CONSTANT
    family = MONOMIAL
  [../]

[]


[AuxKernels]
  [./strain_xx]
    type = RankTwoAux
    rank_two_tensor = total_strain
    variable = strain_xx
    index_i = 0
    index_j = 0
  [../]
  [./strain_yy]
    type = RankTwoAux
    rank_two_tensor = total_strain
    variable = strain_yy
    index_i = 1
    index_j = 1
  [../]
  [./strain_zz]
    type = RankTwoAux
    rank_two_tensor = total_strain
    variable = strain_zz
    index_i = 2
    index_j = 2
  [../]

  [./dislocation_density]
    type = DislocationDensityAux
    variable = dislocation_density
    property = dislocation_density
  [../]

[]

[BCs]
  [./left]
    type = DirichletBC
    variable = disp_x
    boundary = left
    value = 0.0
  [../]
  [./bottom]
    type = DirichletBC
    variable = disp_y
    boundary = bottom
    value = 0.0
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    block = '0 1 2 3'
    youngs_modulus = 2.1e5
    poissons_ratio = 0.3
  [../]

  [./eigen_strain1]
    type=ComputeDislocationDensity1DEigenStrain
    block = 1
    n=100
    burgers_vector =  0.0001
    eigenstrain_name = eigenstrain1
    constant_on = ELEMENT
  [../]

  [./eigen_strain2]
    type=ComputeDislocationDensity1DEigenStrain
    block = 2
    n=100
    burgers_vector =  0.0001
    eigenstrain_name = eigenstrain2
    constant_on = ELEMENT
  [../]

  [./eigen_strain3]
    type=ComputeDislocationDensity1DEigenStrain
    block = 3
    n=100
    burgers_vector =  0.0001
    eigenstrain_name = eigenstrain3
    constant_on = ELEMENT
  [../]

  [./eigen_strain0]
    type=ComputeDislocationDensity1DEigenStrain
    block = 0
    n = 0
    burgers_vector = 0.0001
    eigenstrain_name = eigenstrain0
    constant_on = ELEMENT
  [../]

  [./small_strain1]
    type=ComputeSmallStrain
    block= 1
    eigenstrain_names = 'eigenstrain1'
  [../]

  [./small_strain2]
    type=ComputeSmallStrain
    block= 2
    eigenstrain_names = 'eigenstrain2'
  [../]

  [./small_strain3]
    type=ComputeSmallStrain
    block= 3
    eigenstrain_names = 'eigenstrain3'
  [../]

  [./small_strain0]
    type=ComputeSmallStrain
    block= 0
    [../]

  [./stress]
    type = ComputeLinearElasticStress
    block= '0 1 2 3'
  [../]
[]

[Kernels]
    [./TensorMechanics]
      displacements = 'disp_x disp_y'
      use_displaced_mesh = false
      block='0 1 2 3'
    [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]
[Executioner]
  type = Steady

  solve_type = 'NEWTON'

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-pc_type -sub_pc_type -pc_asm_overlap -ksp_gmres_restart'
  petsc_options_value = 'asm lu 1 101'
[]

[Outputs]
  exodus = true
  csv = true
  print_perf_log = true
[]

[Postprocessors]
  [./strain_xx]
    type = ElementAverageValue
    variable = strain_xx
    block = 1
  [../]
  [./strain_yy]
    type = ElementAverageValue
    variable = strain_yy
    block = 1
  [../]
  [./strain_zz]
    type = ElementAverageValue
    variable = strain_zz
    block = 1
  [../]
[]
