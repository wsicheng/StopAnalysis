#ifndef EVENTTREE_H
#define EVENTTREE_H
 
#include <string>
#include <vector>
#include "Math/LorentzVector.h"
#include "Tools/badEventFilter.h"
 
// forward declarations
class TTree;
 
// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<std::string> vecs;
typedef std::vector<int> veci; 
typedef std::vector<bool> vecb;
 
class EventTree
{
public:
    // constructor/destructor
    EventTree ();
    EventTree (const std::string &prefix);
    virtual ~EventTree (){}
 
    void Reset ();
    void SetBranches (TTree* tree);
    void SetZllBranches (TTree* tree);
    void SetPhotonBranches (TTree* tree);
    void SetMETResBranches (TTree* tree);
    void SetMETFilterBranches (TTree* tree);
    void SetExtraVariablesBranches (TTree* tree);
    void SetSecondLepBranches (TTree* tree);
    void SetAliases (TTree* tree) const;
    void FillCommon (const std::string &root_file_name = "");
    void SetMetFilterEvents(); 
private:
    std::string prefix_;
    eventFilter metFilterTxt;
public:
    // branch objects
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    int nvtxs;

    int year;
    int sampver;

    int   firstGoodVtxIdx;

    unsigned int nEvents;
    unsigned int nEvents_goodvtx;
    unsigned int nEvents_MET30;
    unsigned int nEvents_1goodlep;
    unsigned int nEvents_2goodjets;

    int genlepsfromtop;
    int genLepsHardProcess;                                                                                               
    int genNusHardProcess;

    int is0lep;
    int is1lep;
    int is2lep;
    int isZtoNuNu;

    int is1lepFromW;
    int is1lepFromTop;

    int ngoodleps;
    int nlooseleps;  
    int nvetoleps;   
 
    float MT2W;
    float hadronic_top_chi2;
    float topness;
    float topnessMod;
    float MT2W_lep2;
    float topness_lep2;
    float topnessMod_lep2;
    float MT2_ll;

    float MT2W_rl;
    float topnessMod_rl;
    float MT2W_rl_jup;
    float topnessMod_rl_jup;
    float MT2W_rl_jdown;
    float topnessMod_rl_jdown;

    float topnessMod_resup;
    float topnessMod_resdown;
    float topnessMod_rl_resup;
    float topnessMod_rl_resdown;
    float topnessMod_genmet;
    float topnessMod_rl_genmet;

    float MT2W_jup;
    float topnessMod_jup;
    float MT2W_jdown;
    float topnessMod_jdown;
    float MT2_ll_jup;
    float MT2_ll_jdown;
    float MT2_ll_resup;
    float MT2_ll_resdown;
    float MT2_ll_genmet;

    float MT2_lb_b;
    float MT2_lb_b_lep2;
    float MT2_lb_b_mass;
    float MT2_lb_b_mass_lep2;
    float MT2_lb_bqq;
    float MT2_lb_bqq_lep2;
    float MT2_lb_bqq_mass;
    float MT2_lb_bqq_mass_lep2;

    float Mlb_closestb;
    float Mlb_lead_bdiscr;
    float Mlb_closestb_jup;
    float Mlb_lead_bdiscr_jup;
    float Mlb_closestb_jdown;
    float Mlb_lead_bdiscr_jdown;
    float Mlb_closestb_lep2;
    float Mlb_lead_bdiscr_lep2;
    float Mjjj;
    float Mjjj_lep2;

    float pfmet;
    float pfmet_phi;
    float pfmet_jup;
    float pfmet_phi_jup;
    float pfmet_jdown;
    float pfmet_phi_jdown;
    float pfmet_rl;
    float pfmet_phi_rl;
    float pfmet_rl_jup;
    float pfmet_phi_rl_jup;
    float pfmet_rl_jdown;
    float pfmet_phi_rl_jdown;
    float pfmet_egclean;
    float pfmet_egclean_phi;
    float pfmet_muegclean;
    float pfmet_muegclean_phi;
    float pfmet_muegcleanfix;
    float pfmet_muegcleanfix_phi;
    float pfmet_uncorr;
    float pfmet_uncorr_phi;
    float pfmet_uncorr_jup;
    float pfmet_uncorr_phi_jup;
    float pfmet_uncorr_jdown;
    float pfmet_uncorr_phi_jdown;
    float pfmet_original;
    float pfmet_original_phi;
    float pfmet_resup;
    float pfmet_phi_resup;
    float pfmet_resdown;
    float pfmet_phi_resdown;
    float pfmet_rl_resup;
    float pfmet_phi_rl_resup;
    float pfmet_rl_resdown;
    float pfmet_phi_rl_resdown;
   
    float calomet;
    float calomet_phi;

    bool filt_cscbeamhalo;
    bool filt_cscbeamhalo2015;
    bool filt_globaltighthalo2016;
    bool filt_globalsupertighthalo2016;
    bool filt_ecalbadcalib;
    bool filt_ecallaser;
    bool filt_ecaltp;
    bool filt_eebadsc;
    bool filt_goodvtx;
    bool filt_badevents;
    bool filt_hbhenoise;
    bool filt_hbheisonoise;
    bool filt_hcallaser;
    bool filt_met;
    bool filt_badChargedCandidateFilter;
    bool filt_badMuonFilter;
    bool filt_trkfail;
    bool filt_trkPOG;
    bool filt_trkPOG_logerr_tmc;
    bool filt_trkPOG_tmc;
    bool filt_trkPOG_tms;
    bool filt_fastsimjets;
    bool filt_fastsimjets_jup;
    bool filt_fastsimjets_jdown;
    bool filt_jetWithBadMuon;
    bool filt_jetWithBadMuon_jup;
    bool filt_jetWithBadMuon_jdown;
    bool filt_pfovercalomet;
    bool filt_badmuons;
    bool filt_duplicatemuons;
    bool filt_nobadmuons;
    
    float dR_lep_leadb;
    float dR_lep2_leadb;    
    float mindphi_met_j1_j2;
    float mindphi_met_j1_j2_rl;
    float mindphi_met_j1_j2_rl_jup;
    float mindphi_met_j1_j2_rl_jdown;
    float mindphi_met_j1_j2_jup;
    float mindphi_met_j1_j2_jdown;
    float mindphi_met_j1_j2_rl_resup;
    float mindphi_met_j1_j2_rl_resdown;
    float mindphi_met_j1_j2_resup;
    float mindphi_met_j1_j2_resdown;
    float mindphi_genmet_j1_j2;
    float mindphi_genmet_j1_j2_rl;
    float mt_met_lep;
    float mt_met_lep2;
    float mt_met_lep_rl;
    float mt_met_lep_rl_jup;
    float mt_met_lep_rl_jdown;
    float mt_met_lep_jup;
    float mt_met_lep_jdown;
    float mt_met_lep_rl_resup;
    float mt_met_lep_rl_resdown;
    float mt_met_lep_resup;
    float mt_met_lep_resdown;
    float mt_genmet_lep;
    float mt_genmet_lep_rl;

    float dphi_Wlep;
    float MET_over_sqrtHT;
    float ak4pfjets_rho;
 
    bool is_data;
 
    std::string dataset;
    std::string filename;    
    std::string cms3tag;

    //gen info//
    float scale1fb;
    float xsec;
    float xsec_uncert;//fill it for signal
    float kfactor;
    float pu_ntrue;
    int   pu_nvtxs;
    float pdf_up_weight;
    float pdf_down_weight;
    vecd  genweights;
    int   ngenweights;
    vecs  genweightsID;
    float weight_Q2_up;
    float weight_Q2_down;
    float weight_muF_up;
    float weight_muF_down;
    float weight_muR_up;
    float weight_muR_down;
    float weight_alphas_up;
    float weight_alphas_down;
    float weight_btagsf;
    float weight_btagsf_heavy_UP;
    float weight_btagsf_light_UP;
    float weight_btagsf_heavy_DN;
    float weight_btagsf_light_DN;
    float weight_btagsf_fastsim_UP;
    float weight_btagsf_fastsim_DN;
    float weight_lepSF;
    float weight_lepSF_up;
    float weight_lepSF_down;
    float weight_vetoLepSF;
    float weight_vetoLepSF_up;
    float weight_vetoLepSF_down;
    float weight_lepSF_fastSim;
    float weight_lepSF_fastSim_up;
    float weight_lepSF_fastSim_down;
    float weight_ISR;
    float weight_ISRup;
    float weight_ISRdown;
    float weight_PU;
    float weight_PUup;
    float weight_PUdown;
    float weight_ISRnjets;
    float weight_ISRnjets_UP;
    float weight_ISRnjets_DN;
    float weight_L1prefire;
    float weight_L1prefire_UP;
    float weight_L1prefire_DN;
    float weight_analysisbtagsf;//medium if Mlb<175, tight if Mlb>175
    float weight_analysisbtagsf_heavy_UP;
    float weight_analysisbtagsf_light_UP;
    float weight_analysisbtagsf_heavy_DN;
    float weight_analysisbtagsf_light_DN;
    float weight_analysisbtagsf_fastsim_UP;
    float weight_analysisbtagsf_fastsim_DN;
    float weight_tightbtagsf;
    float weight_tightbtagsf_heavy_UP;
    float weight_tightbtagsf_light_UP;
    float weight_tightbtagsf_heavy_DN;
    float weight_tightbtagsf_light_DN;
    float weight_tightbtagsf_fastsim_UP;
    float weight_tightbtagsf_fastsim_DN;
    float weight_loosebtagsf;
    float weight_loosebtagsf_heavy_UP;
    float weight_loosebtagsf_light_UP;
    float weight_loosebtagsf_heavy_DN;
    float weight_loosebtagsf_light_DN;
    float weight_loosebtagsf_fastsim_UP;
    float weight_loosebtagsf_fastsim_DN;
    int   NISRjets;
    int   NnonISRjets;
    float hardgenpt;
    //sparms
    // vecs  sparms_comment;
    vecs  sparms_names;
    vecd  sparms_values;
    int   sparms_subProcessId;
    float mass_lsp;
    float mass_chargino;
    float mass_stop;
    float mass_gluino;       
 
    //gen met
    float genmet;
    float genmet_phi;
    float genmet_rl;
    float genmet_phi_rl;
    float genht;
    float nupt;
    //veto
    bool PassTrackVeto;
    bool PassTauVeto;

    //trigger
    //int  HLT_HT900;
    int HLT_SingleMu; 
    int HLT_SingleEl;
    int HLT_MET;
    int HLT_MET_MHT;
    int HLT_MET100_MHT100;
    int HLT_MET110_MHT110;
    int HLT_MET120_MHT120;
    int HLT_MET130_MHT130;
    int HLT_DiEl;
    int HLT_DiMu;
    int HLT_MuE;

    int HLT_PFHT_unprescaled;
    int HLT_PFHT_prescaled;
    int HLT_AK8Jet_unprescaled;
    int HLT_AK8Jet_prescaled;
    int HLT_Photon22_R9Id90_HE10_IsoM;
    int HLT_Photon30_R9Id90_HE10_IsoM;
    int HLT_Photon36_R9Id90_HE10_IsoM;
    int HLT_Photon50_R9Id90_HE10_IsoM;
    int HLT_Photon75_R9Id90_HE10_IsoM; 
    int HLT_Photon90_R9Id90_HE10_IsoM; 
    int HLT_Photon120_R9Id90_HE10_IsoM;
    int HLT_Photon165_R9Id90_HE10_IsoM;
    int HLT_Photon175;
    int HLT_Photon165_HE10;
    int HLT_Photon120;//from MT2
    int HLT_Photon200;
    int HLT_Photon250_NoHE;//from MT2
    int HLT_Photon300_NoHE;
    int HLT_CaloJet500_NoJetID;//from Vince's code

    float EA_fixgridfastjet_all_rho;//to do photon EA on the fly

    //float pu_weight;
    float lep_sf;
    float btag_sf;

    //photon addition
    int nPhotons;
    int ph_selectedidx;//not necessarily first photon
    int ph_ngoodjets;
    int ph_ngoodbtags;
    float ph_met;
    float ph_met_phi;
    float ph_HT;
    float ph_htssm;
    float ph_htosm;
    float ph_htratiom;
    float ph_mt_met_lep;
    float ph_dphi_Wlep;
    float ph_MT2W;
    float ph_topness;
    float ph_topnessMod;
    float ph_MT2_lb_b_mass;
    float ph_MT2_lb_b;
    float ph_MT2_ll;
    float ph_MT2_lb_bqq_mass;
    float ph_MT2_lb_bqq;
    float ph_hadronic_top_chi2;
    float ph_mindphi_met_j1_j2;
    float ph_Mlb_lead_bdiscr;
    float ph_dR_lep_leadb;
    float ph_Mlb_closestb;
    float ph_Mjjj;

    int   Zll_idl1;
    int   Zll_idl2;
    LorentzVector  Zll_p4l1;
    LorentzVector  Zll_p4l2;
    bool  Zll_OS;
    bool  Zll_SF;
    bool  Zll_isZmass;
    float Zll_M;
    LorentzVector  Zll_p4;
    int   Zll_selLep;
    float Zll_met;
    float Zll_met_phi;
    float Zll_mindphi_met_j1_j2;
    float Zll_mt_met_lep;
    float Zll_dphi_Wlep;
    float Zll_MT2W;
    float Zll_topness;
    float Zll_topnessMod;
    float Zll_MT2_lb_b_mass;
    float Zll_MT2_lb_b;
    float Zll_MT2_ll;
    float Zll_MT2_lb_bqq_mass;
    float Zll_MT2_lb_bqq;

    
};
 
#endif
