#!/bin/bash
voms-proxy-init -voms cms -valid 240:00
condor_submit configs_V00-00-05/condor_V00-00-05_TTZToLLNuNu_M-10_amcnlo_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT100To200_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT1200To2500_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT200To400_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT2500ToInf_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT400To600_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT600To800_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT600ToInf_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_HT800To1200_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_WJetsToLNu_madgraph_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_eg_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_eg_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_eg_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_mu_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_mu_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_double_mu_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_met_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_met_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_met_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_muon_eg_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_muon_eg_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_muon_eg_2015D_05Oct2015_v2_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_muon_eg_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_electron_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_electron_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_electron_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_muon_2015C_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_muon_2015D_05Oct2015_v1_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_data_single_muon_2015D_promptRecoV4_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_t_sch_4f_amcnlo_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_t_tW_5f_powheg_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_t_tbarW_5f_powheg_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_t_tch_4f_powheg_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_tbar_tch_4f_powheg_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_ttbar_powheg_pythia8_25ns.cmd
condor_submit configs_V00-00-05/condor_V00-00-05_ttbar_powheg_pythia8_ext3_25ns.cmd
