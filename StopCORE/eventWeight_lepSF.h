#ifndef eventWeight_lepSF_H
#define eventWeight_lepSF_H

// ROOT
#include "Riostream.h"
#include "TFile.h"
#include "TH2.h"
#include "TGraphAsymmErrors.h"

// C
#include <string>
#include <vector>

#include "StopTree.h"

//
// CLASS
//
class eventWeight_lepSF{

 public:

  eventWeight_lepSF() {}
  ~eventWeight_lepSF();

  // Year of the sample
  int year;
  TString filepath;

  // Sample info 
  bool sampleIsFastsim;

  // Fullsim Electron file
  TFile *f_el_SF = nullptr;
  TFile *f_el_SF_tracking = nullptr;
  TFile *f_el_SF_trklowpt = nullptr;

  // Fullsim Muon files
  TFile *f_mu_SF_id = nullptr;
  TFile *f_mu_SF_iso = nullptr;
  TFile *f_mu_SF_ip = nullptr;
  TFile *f_mu_SF_tracking = nullptr;
  TFile *f_mu_SF_veto_id = nullptr;
  TFile *f_mu_SF_veto_iso = nullptr;
  TFile *f_mu_SF_veto_ip = nullptr;

  // Fullsim/Fastsim Electron files
  TFile *f_el_FS_ID = nullptr;
  TFile *f_el_FS_Iso = nullptr;
  TFile *f_el_veto_FS_ID = nullptr;
  TFile *f_el_veto_FS_Iso = nullptr;

  // Fullsim/Fastsim Muon files
  TFile *f_mu_FS_ID = nullptr;
  TFile *f_mu_FS_Iso = nullptr;
  TFile *f_mu_FS_Ip = nullptr;
  TFile *f_mu_veto_FS_ID = nullptr;
  TFile *f_mu_veto_FS_Iso = nullptr;
  TFile *f_mu_veto_FS_Ip = nullptr;

  // Lepton MC reco efficiency for veto lep IDs
  TFile *f_vetoLep_eff = nullptr;
 
  // Final scale factor histograms for selected leptons
  TH2F *h_el_SF = nullptr;
  TH2F *h_mu_SF = nullptr;
  
  // Final scale factor histograms for veto leptons
  TH2F *h_el_SF_veto = nullptr;
  TH2F *h_mu_SF_veto = nullptr;

  // Final scale factor histograms for tracking
  TH2F *h_el_SF_tracking = nullptr;
  TH2F *h_el_SF_trklowpt = nullptr;
  // TH1D *h_mu_SF_tracking = nullptr;

  // Final scale factor histograms for fastim/fullsim for selected leptons
  TH2F *h_el_FS = nullptr;
  TH2F *h_mu_FS = nullptr;

  // Final scale factor histograms for fastim/fullsim for veto leptons
  TH2F *h_el_veto_FS = nullptr;
  TH2F *h_mu_veto_FS = nullptr;

  // Final scale factor histograms for lost leptons
  TH2F *h_el_vetoLepEff = nullptr;
  TH2F *h_mu_vetoLepEff = nullptr;

  float xmin_h_el_SF;
  float xmax_h_el_SF;
  float ymin_h_el_SF;
  float ymax_h_el_SF;
  float xmin_h_el_SF_veto;
  float xmax_h_el_SF_veto;
  float ymin_h_el_SF_veto;
  float ymax_h_el_SF_veto;
  float xmin_h_el_SF_tracking;
  float xmax_h_el_SF_tracking;
  float ymin_h_el_SF_tracking;
  float ymax_h_el_SF_tracking;
  float ymin_h_el_SF_trklowpt;
  float ymax_h_el_SF_trklowpt;
  float xmin_h_mu_SF;
  float xmax_h_mu_SF;
  float ymin_h_mu_SF;
  float ymax_h_mu_SF;
  // float xmin_h_mu_SF_tracking;
  // float xmax_h_mu_SF_tracking;
  float xmin_h_mu_SF_veto;
  float xmax_h_mu_SF_veto;
  float ymin_h_mu_SF_veto;
  float ymax_h_mu_SF_veto;
  float xmin_h_el_FS;
  float xmax_h_el_FS;
  float ymin_h_el_FS;
  float ymax_h_el_FS;
  float xmin_h_el_veto_FS;
  float xmax_h_el_veto_FS;
  float ymin_h_el_veto_FS;
  float ymax_h_el_veto_FS;
  float xmin_h_mu_FS;
  float xmax_h_mu_FS;
  float ymin_h_mu_FS;
  float ymax_h_mu_FS;
  float xmin_h_mu_veto_FS;
  float xmax_h_mu_veto_FS;
  float ymin_h_mu_veto_FS;
  float ymax_h_mu_veto_FS;
  float xmin_h_el_vetoLepEff;
  float xmax_h_el_vetoLepEff;
  float ymin_h_el_vetoLepEff;
  float ymax_h_el_vetoLepEff;
  float xmin_h_mu_vetoLepEff;
  float xmax_h_mu_vetoLepEff;
  float ymin_h_mu_vetoLepEff;
  float ymax_h_mu_vetoLepEff;
  
  void setup( bool isFastsim, int inyear, TString fileloc );
  void getLepWeight( std::vector<float> recoLep_pt, std::vector<float> recoLep_eta, std::vector<int> recoLep_pdgid, std::vector<bool> recoLep_isSel, std::vector<float> genLostLep_pt, std::vector<float> genLostLep_eta, std::vector<int> genLostLep_pdgid, double &weight_lepSF, double &weight_lepSF_Up, double &weight_lepSF_Dn, double &weight_lepSF_FS, double &weight_lepSF_FS_Up, double &weight_lepSF_FS_Dn, double &weight_vetoLepSF, double &weight_vetoLepSF_Up, double &weight_vetoLepSF_Dn );

};

#endif
