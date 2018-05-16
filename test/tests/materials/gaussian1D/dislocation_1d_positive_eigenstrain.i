[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Mesh]
  type = GeneratedMesh
  dim  = 2
  xmax = 40
  xmin = 0
  ymax = 40
  ymin = 0
  nx   = 100
  ny   = 100
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
  [./stress_xx]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_yy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./stress_xy]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./rho_positive]
    order = CONSTANT
    family = MONOMIAL
  [../]
  #instead of value is zero we still have to declare positive density due to slip element needs the variable
  [./rho_negative]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./slip_element]
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
  [./stress_xx]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_xx
    index_i = 0
    index_j = 0
  [../]
  [./stress_yy]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_yy
    index_i = 1
    index_j = 1
  [../]
  [./stress_xy]
    type = RankTwoAux
    rank_two_tensor = stress
    variable = stress_xy
    index_i = 0
    index_j = 1
  [../]

  [./rho_positive]
    type = GaussianDislocationDensity
    x_center = 10
    sigma_x  = 5
    variable = rho_positive
    execute_on = INITIAL
  [../]
  [./slip_element]
    type = SlipElement
    positive_dislocation = rho_positive
    negative_dislocation = rho_negative
    variable = slip_element
    execute_on = INITIAL
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
    youngs_modulus = 2.1e5
    poissons_ratio = 0.3
  [../]

  [./eigen_strain]
    type = ComputeDislocationDensityEigenstrain
    burgers_vector =  0.001
    slip_distribution = slip_element
    eigenstrain_name = dislocation_eigenstrain
  [../]


  [./small_strain]
    type=ComputeSmallStrain
    eigenstrain_names = 'dislocation_eigenstrain'
  [../]


  [./stress]
    type = ComputeLinearElasticStress
  [../]
[]

[Kernels]
    [./TensorMechanics]
      displacements = 'disp_x disp_y'
      use_displaced_mesh = false
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
  [../]
  [./strain_yy]
    type = ElementAverageValue
    variable = strain_yy
  [../]
  [./strain_zz]
    type = ElementAverageValue
    variable = strain_zz
  [../]
[]
