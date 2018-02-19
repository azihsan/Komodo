[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 7
  ny = 2
  nz = 0
[]

[MeshModifiers]
  [./subdomain_id]
    type = AssignElementSubdomainID
    subdomain_ids = '0 1 1 1 1 1 0
                    0 0 0 0 0 0 0'
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
    block = '0 1'
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

  [./small_strain1]
    type=ComputeSmallStrain
    block= 1
    eigenstrain_names = 'eigenstrain1'
  [../]

  [./small_strain3]
    type=ComputeSmallStrain
    block= 0
    [../]

  [./stress]
    type = ComputeLinearElasticStress
    block= '0 1'
  [../]
[]

[Kernels]
    [./TensorMechanics]
      displacements = 'disp_x disp_y'
      use_displaced_mesh = false
      block='0 1'
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
