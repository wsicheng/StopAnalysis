#include "StopRegions.h"

const float fInf = std::numeric_limits<float>::max();
const float wpResTop = 0.95;
const float wpDeepTop = 0.40;


std::vector<SR> getStopControlRegionsNoBTags(std::vector<SR>&& SRvec) {

  std::vector<SR> CRvec;
  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr0b"));
    cr.SetAllowDummyVars(1);
    if (cr.VarExists("nbjet")) cr.RemoveVar("nbjet");
    if (cr.VarExists("ntbtag")) cr.RemoveVar("ntbtag");
    if (cr.GetName().find("base") != std::string::npos || cr.GetName().find("cr0bI") == 0) {
      cr.SetVar("nbjet", 0, 1);
    } else {
      cr.SetVar("nbtag", 0, 1);
    }
    if (cr.GetLowerBound("tmod") < 10)
      cr.SetVar("nbjet", 0, 1);
    cr.SetVar("mlb_0b", cr.GetLowerBound("mlb"), cr.GetUpperBound("mlb"));
    cr.RemoveVar("mlb");
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopControlRegionsDilepton(std::vector<SR>&& SRvec) {

  std::vector<SR> CRvec;

  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr2l"));
    cr.SetAllowDummyVars(1);
    for (std::string var : {"met", "mt", "dphijmet", "nlep", "tmod", "dphilmet"}) {
      if (!cr.VarExists(var)) continue;
      cr.SetVar(var+"_rl", cr.GetLowerBound(var), cr.GetUpperBound(var));
      cr.RemoveVar(var);
    }
    cr.RemoveVar("passvetos");
    cr.SetVar("nvlep", 2, fInf);
    cr.SetVar("nlep_rl", 2, fInf);
    cr.SetVar("mt2_ll", 0, 100);  // to avoid overlap with the stop-2l SR
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopSignalRegionsTopological() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar("mt", 150, fInf);
  srbase.SetVar("met", 250, fInf);
  srbase.SetVar("nlep", 1, 2);
  srbase.SetVar("nvlep", 1, 2);
  srbase.SetVar("passvetos", 1, 2);
  srbase.SetVar("njet", 2, fInf);
  srbase.SetVar("nbjet", 1, fInf);
  srbase.SetVar("ntbtag", 0, fInf);
  // srbase.SetVar("nbtag", 1, fInf);
  srbase.SetVar("mlb", 0, fInf);
  srbase.SetVar("tmod", -fInf, fInf);
  srbase.SetVar("dphijmet", 0.8, 3.14159);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // SR 2-3j

  sr = srbase;
  sr.SetName("srA");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("ntbtag", 0, fInf);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srB");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetMETBins({250, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("ntbtag", 0, fInf);
  sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE");
  sr.SetDetailName("geq4j_tmod0to10_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("ntbtag", 0, fInf);
  sr.SetMETBins({250, 350, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srF");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG");
  sr.SetDetailName("geq4j_tmod10toInf_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("ntbtag", 0, fInf);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srH");
  sr.SetDetailName("geq4j_tmod10toInf_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  // Compressed regions
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("geq5j_lpt0to150_j1notb");
  sr.SetVar("mt", 150, fInf);
  sr.SetVar("njet", 5, fInf);
  sr.SetVar("nbjet", 1, fInf);
  sr.SetVar("lep1pt", 0, 150);
  sr.SetVar("dphilmet", 0, 2.0);
  sr.SetVar("dphijmet", 0.5, 3.1416);
  sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsTopological() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsTopological() );
}

std::vector<SR> getStopControlRegionsDileptonTopological() {
  return getStopControlRegionsDilepton( getStopSignalRegionsTopological() );
}

std::vector<SR> getStopCrosscheckRegionsEMu() {
  std::vector<SR> CRvec;

  SR crbase;

  crbase.SetName("cremu_base");
  crbase.SetVar("nvlep", 1, 3);
  crbase.SetVar("met", 50, fInf);
  crbase.SetVar("njet", 2, fInf);
  crbase.SetMETBins({50, 100, 150, 200, 250, 350, 450, 600, 800, 1500});
  crbase.SetAllowDummyVars(1);

  // The strict lepton selections are in the looper

  SR cr = crbase;

  cr.SetName("cremuA0");
  cr.SetDetailName("ge2j_ge0b_met50toInf");
  cr.SetVar("nbjet", 0, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuA1");
  cr.SetDetailName("ge2j_ge1b_met50toInf");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuA2");
  cr.SetDetailName("ge2j_ge2b_met50toInf");
  cr.SetVar("nbjet", 2, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("mt", 0, 150);
  cr.SetName("cremuB0");
  cr.SetDetailName("ge2j_ge0b_met50toInf_mt0to150");
  cr.SetVar("nbjet", 0, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuB1");
  cr.SetDetailName("ge2j_ge1b_met50toInf_mt0to150");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("mt", 150, fInf);
  cr.SetName("cremuC0");
  cr.SetDetailName("ge2j_0b_met50toInf_mt150toInf");
  cr.SetVar("nbjet", 0, 1);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC1");
  cr.SetDetailName("ge2j_1b_met50toInf_mt150toInf");
  cr.SetVar("nbjet", 1, 2);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC2");
  cr.SetDetailName("ge2j_ge2b_met50toInf_mt150toInf");
  cr.SetVar("nbjet", 2, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("mt", 0, fInf);
  cr.SetVar("tmod", 0, 10);

  cr.SetName("cremuD0");
  cr.SetDetailName("ge2j_0b_met50toInf_tmod0to10");
  cr.SetVar("nbjet", 0, 1);
  CRvec.emplace_back(cr);

  cr.SetName("cremuD1");
  cr.SetDetailName("ge2j_ge1b_met50toInf_tmod0to10");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("tmod", 10, fInf);

  cr.SetName("cremuE0");
  cr.SetDetailName("ge2j_0b_met50toInf_tmod10toInf");
  cr.SetVar("nbjet", 0, 1);
  CRvec.emplace_back(cr);

  cr.SetName("cremuE1");
  cr.SetDetailName("ge2j_ge1b_met50toInf_tmod10toInf");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("tmod", -fInf, fInf);
  cr.SetVar("met", 50, 250);

  cr.SetVar("nbjet", 0, 1);
  cr.SetName("cremuF0");
  cr.SetDetailName("ge2j_0b_met50to250");
  cr.SetVar("nbjet", 0, 1);
  CRvec.emplace_back(cr);

  cr.SetName("cremuF1");
  cr.SetDetailName("ge2j_ge1b_met50to250");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetVar("met", 250, fInf);

  cr.SetVar("nbjet", 0, 1);
  cr.SetName("cremuG0");
  cr.SetDetailName("ge2j_0b_met250to500");
  cr.SetVar("nbjet", 0, 1);
  CRvec.emplace_back(cr);

  cr.SetName("cremuG1");
  cr.SetDetailName("ge2j_ge1b_met250to500");
  cr.SetVar("nbjet", 1, fInf);
  CRvec.emplace_back(cr);


  return CRvec;
}

std::vector<SR> getStopCrosscheckRegionsEMuRun2() {
  std::vector<SR> CRvec;

  SR crbase;

  crbase.SetName("cremu_base");
  crbase.SetVar(nvlep, 1, 3);
  crbase.SetVar(met, 50, fInf);
  crbase.SetVar(njet, 2, fInf);
  crbase.SetMETBins({50, 100, 150, 200, 250, 350, 450, 600, 800, 1500});
  crbase.SetAllowDummyVars(1);

  // The strict lepton selections are in the looper

  SR cr = crbase;

  cr.SetName("cremuA0");
  cr.SetDetailName("emu_ge2j_ge0b_met50toInf");
  cr.SetVar(nbjet, 0, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuA1");
  cr.SetDetailName("emu_ge2j_ge1b_met50toInf");
  cr.SetVar(nbjet, 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuA2");
  cr.SetDetailName("emu_ge2j_ge2b_met50toInf");
  cr.SetVar(nbjet, 2, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuA3");
  cr.SetDetailName("emu_ge2j_2b_met50toInf");
  cr.SetVar(nbjet, 2, 3);
  CRvec.emplace_back(cr);

  cr.SetName("cremuB1");
  cr.SetDetailName("emu_ge1j_1b_met50toInf");
  cr.SetVar(njet, 1, fInf);
  cr.SetVar(nbjet, 1, 2);
  CRvec.emplace_back(cr);

  cr.SetName("cremuB2");
  cr.SetDetailName("emu_1j_1b_met50toInf");
  cr.SetVar(njet, 1, 2);
  cr.SetVar(nbjet, 1, 2);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC2");
  cr.SetDetailName("emu_2to3j_ge1b_met50toInf");
  cr.SetVar(njet, 2, 4);
  cr.SetVar(nbjet, 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC3");
  cr.SetDetailName("emu_ge3j_ge1b_met50toInf");
  cr.SetVar(njet, 3, fInf);
  cr.SetVar(nbjet, 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC4");
  cr.SetDetailName("emu_ge4j_ge1b_met50toInf");
  cr.SetVar(njet, 4, fInf);
  cr.SetVar(nbjet, 1, fInf);
  CRvec.emplace_back(cr);

  cr.SetName("cremuC5");
  cr.SetDetailName("emu_ge5j_ge1b_met50toInf");
  cr.SetVar(njet, 5, fInf);
  cr.SetVar(nbjet, 1, fInf);
  CRvec.emplace_back(cr);

  // cr = crbase;
  // cr.SetName("cremuM1");
  // cr.SetDetailName("ge2j_ge1b_met50to100");
  // cr.SetVar(met, 50, 100);
  // cr.SetVar(njet, 2, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuM2");
  // cr.SetDetailName("ge2j_ge1b_met150toInf");
  // cr.SetVar(met, 150, 250);
  // cr.SetVar(njet, 2, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuM3");
  // cr.SetDetailName("ge2j_ge1b_met150toInf");
  // cr.SetVar(met, 250, fInf);
  // cr.SetVar(njet, 2, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // CRvec.emplace_back(cr);


  // // SRs
  // cr.SetName("cremuA");
  // cr.SetDetailName("2to3j_ge1b_met50toInf_tmod10toInf_mlb0to175");
  // cr.SetVar(njet, 2, 4);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 0, 175);
  // cr.SetVar(tmod, 10, fInf);
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 600, 750, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuB");
  // cr.SetDetailName("2to3j_ge1b_met50toInf_tmod10toInf_mlb175toInf");
  // cr.SetVar(njet, 2, 4);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 175, fInf);
  // cr.SetVar(tmod, 10, fInf);
  // cr.SetMETBins({50, 100, 150, 200, 250, 450, 700, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuC");
  // cr.SetDetailName("ge4j_ge1b_met50toInf_tmodInfto0_mlb0to175");
  // cr.SetVar(njet, 4, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 0, 175);
  // cr.SetVar(tmod, -fInf, 0);
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 550, 650, 800, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuE");
  // cr.SetDetailName("ge4j_ge1b_met50toInf_tmod0to10_mlb0to175");
  // cr.SetVar(njet, 4, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 0, 175);
  // cr.SetVar(tmod, 0, 10);
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 600, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuG");
  // cr.SetDetailName("ge4j_ge1b_met50toInf_tmod10toInf_mlb0to175");
  // cr.SetVar(njet, 4, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 0, 175);
  // cr.SetVar(tmod, 0, 10);
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 550, 750, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuH");
  // cr.SetDetailName("ge4j_ge1b_met50toInf_tmod10toInf_mlb175toInf");
  // cr.SetVar(njet, 4, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.SetVar(mlb, 0, 175);
  // cr.SetVar(tmod, 0, 10);
  // cr.SetMETBins({50, 100, 150, 200, 250, 500, 800, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuI");
  // cr.SetDetailName("ge5j_ge1b_met50toInf");
  // cr.SetVar(njet, 5, fInf);
  // cr.SetVar(nbjet, 1, fInf);
  // cr.RemoveVar(mlb);
  // cr.RemoveVar(tmod);
  // cr.SetVar(passlmetcor, 1, 2);
  // cr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 550, 750, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuJ");
  // cr.SetDetailName("ge5j_ge1b_met50toInf");
  // cr.SetVar(njet, 5, fInf);
  // cr.SetVar(nbjet, 0, fInf);
  // cr.SetVar(nsbtag, 1, fInf);
  // cr.SetMETBins({50, 100, 150, 200, 250, 350, 450, 550, 800, 1500});
  // CRvec.emplace_back(cr);

  // cr.SetVar(mt, 150, fInf);
  // cr.SetName("cremuC0");
  // cr.SetDetailName("ge2j_0b_met50toInf_mt150toInf");
  // cr.SetVar(nbjet, 0, 1);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuC1");
  // cr.SetDetailName("ge2j_1b_met50toInf_mt150toInf");
  // cr.SetVar(nbjet, 1, 2);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuC2");
  // cr.SetDetailName("ge2j_ge2b_met50toInf_mt150toInf");
  // cr.SetVar(nbjet, 2, fInf);
  // CRvec.emplace_back(cr);

  // cr.SetVar(mt, 0, fInf);
  // cr.SetVar(tmod, 0, 10);

  // cr.SetName("cremuD0");
  // cr.SetDetailName("ge2j_0b_met50toInf_tmod0to10");
  // cr.SetVar(nbjet, 0, 1);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuD1");
  // cr.SetDetailName("ge2j_ge1b_met50toInf_tmod0to10");
  // cr.SetVar(nbjet, 1, fInf);
  // CRvec.emplace_back(cr);

  // cr.SetVar(tmod, 10, fInf);

  // cr.SetName("cremuE0");
  // cr.SetDetailName("ge2j_0b_met50toInf_tmod10toInf");
  // cr.SetVar(nbjet, 0, 1);
  // CRvec.emplace_back(cr);

  // cr.SetName("cremuE1");
  // cr.SetDetailName("ge2j_ge1b_met50toInf_tmod10toInf");
  // cr.SetVar(nbjet, 1, fInf);
  // CRvec.emplace_back(cr);


  return CRvec;
}

std::vector<SR> getStopInclusiveRegionsTopological() {
  std::vector<SR> SRvec;

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar("mt", 150, fInf);
  srbase.SetVar("met", 250, fInf);
  srbase.SetVar("nlep", 1, 2);
  srbase.SetVar("nvlep", 1, 2);
  srbase.SetVar("passvetos", 1, 2);
  srbase.SetVar("njet", 2, fInf);
  srbase.SetVar("nbtag", 1, fInf);
  srbase.SetVar("mlb", 0, fInf);
  srbase.SetVar("tmod", -fInf, fInf);
  srbase.SetVar("dphijmet", 0.8, 3.1416);
  srbase.SetMETBins({250, 350, 450, 550, 650, 800, 1500});
  SRvec.emplace_back(srbase);

  SR sr;

  sr = srbase;
  sr.SetName("srsbmet");  // MET sideband
  sr.SetVar("met", 150, 250);
  sr.SetVar("passlep1pt", 1, 2);
  sr.SetMETBins({150, 200, 250});
  SRvec.emplace_back(sr);

  // Test regions
  sr.Clear();
  sr.SetAllowDummyVars(1);
  sr.SetName("srtest0");         // test for zpeak lumi
  sr.SetVar("mt", 0, fInf);
  sr.SetVar("met", 50, fInf);
  sr.SetVar("nlep", 1, 2);
  sr.SetVar("nvlep", 1, 2);
  sr.SetVar("passvetos", 1, 2);
  sr.SetVar("njet", 2, fInf);
  sr.SetVar("nbtag", 1, fInf);
  sr.SetVar("mlb", -fInf, fInf);
  sr.SetVar("tmod", -fInf, fInf);
  sr.SetVar("dphijmet", 0.8, 3.1416);
  sr.SetMETBins({100, 1500});
  SRvec.emplace_back(sr);

  return SRvec;

  sr.SetName("srtestMT");
  sr.SetVar("met", 250, fInf);
  SRvec.emplace_back(sr);

  sr.SetName("srtestMET");
  sr.SetVar("met", 50, fInf);
  sr.SetVar("mt", 150, fInf);
  SRvec.emplace_back(sr);

  sr.SetName("srtest2");
  sr.SetVar("met", 250, fInf);
  sr.SetVar("dphijmet", 0.0, 3.1416);
  SRvec.emplace_back(sr);

  sr.SetName("srtest3");
  sr.SetVar("mt", 0, fInf);
  sr.SetVar("nbtag", 0, fInf);
  SRvec.emplace_back(sr);

  sr.SetName("srtest4");
  sr.SetDetailName("geq4j_inclusive");
  sr.SetVar("mt", 150, fInf);
  sr.SetVar("dphijmet", 0.0, 3.1416);
  sr.SetVar("njet", 4, fInf);
  SRvec.emplace_back(sr);

  // SRvec.clear();

  sr.SetName("srtest5");         // test
  sr.SetVar("met", 150, fInf);
  sr.SetVar("dphijmet", 0, 0.5);
  sr.SetVar("nlep", 0, fInf);
  sr.SetVar("nvlep", 0, fInf);
  sr.SetVar("njet", 2, fInf);
  sr.SetVar("nbtag", 0, fInf);
  SRvec.emplace_back(sr);

  // return SRvec;

  // // Top tag regions at baseline
  // sr = srbase;
  // sr.SetName("srbase2");
  // sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 350, 500, 700, 1500});
  // SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srbase3");
  // sr.SetVar("deepttag", -1, wpDeepTop);
  // sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 500, 700, 1500});
  // SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModTTagA2");
  sr.SetDetailName("2to3j_tmod10toInf_deepttag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, fInf);
  sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 600, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModTTagC2");
  sr.SetDetailName("geq4j_tmodlt0_deepttag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 0, fInf);
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetTModTTagC3");
  sr.SetDetailName("geq4j_tmodlt0_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModTTagE2");
  sr.SetDetailName("geq4j_tmod0to10_deepttag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 0, fInf);
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetTModTTagE3");
  sr.SetDetailName("geq4j_tmod0to10_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModTTagG2");
  sr.SetDetailName("geq4j_tmod10toInf_deepttag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, fInf);
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetTModTTagG3");
  sr.SetDetailName("geq4j_tmod10toInf_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetMlbTTagC2");
  sr.SetDetailName("geq4j_mlb0to175_deepttag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetMlbTTagC3");
  sr.SetDetailName("geq4j_mlb0to175_deepttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetMlbTTagD2");
  sr.SetDetailName("geq4j_mlb175toInf_resttag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetMlbTTagD3");
  sr.SetDetailName("geq4j_mlb175toInf_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  // Inclusive regions
  sr = srbase;
  sr.SetName("srNJet1");
  sr.SetDetailName("2to3j");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", -fInf, fInf);
  sr.SetVar("nbtag", 1, fInf);
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetMET1");
  sr.SetDetailName("2to3j_met400");
  sr.SetVar("met", 450, fInf);
  SRvec.emplace_back(sr);

  SRvec.clear();

  sr = srbase;
  sr.SetName("srNJet2");
  sr.SetDetailName("ge4j");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, fInf);
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srNJetMET2");
  sr.SetDetailName("ge4j_met400");
  sr.SetVar("met", 450, fInf);
  SRvec.emplace_back(sr);

  return SRvec;

  sr = srbase;
  sr.SetName("srNJetTMod1");
  sr.SetDetailName("2to3j_tmod10toInf");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTMod2");
  sr.SetDetailName("ge4j_tmodlt0");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTMod3");
  sr.SetDetailName("ge4j_tmod0to10");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTMod4");
  sr.SetDetailName("ge4j_tmod10toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModMet1");
  sr.SetDetailName("2to3j_tmod10toInf");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetMETBins({150, 250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModMet2");
  sr.SetDetailName("ge4j_tmodlt0");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetMETBins({150, 250, 350, 450, 550, 650, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModMet3");
  sr.SetDetailName("ge4j_tmod0to10");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetMETBins({150, 250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srNJetTModMet4");
  sr.SetDetailName("ge4j_tmod10toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetMETBins({150, 250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  // Compressed regions
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("geq5j_lpt0to150_j1notb");
  sr.RemoveVar("nbtag");
  sr.SetVar("mt", 150, fInf);
  sr.SetVar("njet", 5, fInf);
  sr.SetVar("nbjet", 1, fInf);
  sr.SetVar("lep1pt", 0, 150);
  sr.SetVar("dphilmet", 0, 2.0);
  sr.SetVar("dphijmet", 0.5, 3.1416);
  sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopInclusiveControlRegionsNoBTags() {
  return getStopControlRegionsNoBTags( getStopInclusiveRegionsTopological() );
}

std::vector<SR> getStopInclusiveControlRegionsDilepton() {
  return getStopControlRegionsDilepton( getStopInclusiveRegionsTopological() );
}

std::vector<SR> getStopSignalRegionsAddResTagBin() {

  std::vector<SR> orgSRvec = getStopSignalRegionsTopological();
  std::vector<SR> SRvec;

  for (SR sr : orgSRvec) {
    if (sr.GetLowerBound("njet") < 4) {
      SRvec.emplace_back(sr);
    } else {
      std::string srname = sr.GetName();

      sr.SetName(srname+"wrt");
      sr.SetAllowDummyVars(1);
      sr.SetVar("resttag", 0.9, 1);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"nrt");
      sr.SetAllowDummyVars(1);
      sr.SetVar("resttag", -2, 0.9);
      SRvec.emplace_back(sr);
    }
  }

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsAddResTagBin() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsAddResTagBin() );
}

std::vector<SR> getStopControlRegionsDileptonAddResTagBin() {
  return getStopControlRegionsDilepton( getStopSignalRegionsAddResTagBin() );
}


std::vector<SR> getStopSignalRegionsNewMETBinning1() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar("mt", 150, fInf);
  srbase.SetVar("met", 250, fInf);
  srbase.SetVar("nlep", 1, 2);
  srbase.SetVar("nvlep", 1, 2);
  srbase.SetVar("passvetos", 1, 2);
  srbase.SetVar("njet", 2, fInf);
  srbase.SetVar("nbtag", 1, fInf);
  srbase.SetVar("mlb", 0, fInf);
  srbase.SetVar("tmod", -fInf, fInf);
  srbase.SetVar("dphijmet", 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // SR 2-3j

  sr = srbase;
  sr.SetName("srA1");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -1, wpDeepTop);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 350, 450, 600, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srA2");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srB1");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_nottag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -1, wpDeepTop);
  // sr.SetMETBins({250, 450, 600, 1500});
  sr.SetMETBins({250, 450, 700, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srB2");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 450, 600, 1500});
  sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC1");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  sr.SetMETBins({250, 350, 450, 550, 650, 800, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC2");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC3");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD1");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 450, 550, 1500});
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD2");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 550, 1500});
  sr.SetMETBins({250, 350, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD3");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 450, 550, 1500});
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE1");
  sr.SetDetailName("geq4j_tmod0to10_mlb0to175_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 550, 1500});
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE2");
  sr.SetDetailName("geq4j_tmod0to10_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 550, 1500});
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE3");
  sr.SetDetailName("geq4j_tmod0to10_mlb0to175_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 550, 1500});
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srF1");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 450, 1500});
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srF2");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 450, 1500});
  // sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srF3");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 450, 1500});
  // sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG1");
  sr.SetDetailName("geq4j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG2");
  sr.SetDetailName("geq4j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG3");
  sr.SetDetailName("geq4j_tmod10toInf_mlb0to175_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 350, 500, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srH1");
  sr.SetDetailName("geq4j_tmod10toInf_mlb175toInf_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 450, 1500});
  sr.SetMETBins({250, 500, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srH2");
  sr.SetDetailName("geq4j_tmod10toInf_mlb175toInf_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 450, 1500});
  // sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srH3");
  sr.SetDetailName("geq4j_tmod10toInf_mlb175toInf_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  sr.SetMETBins({250, 450, 1500});
  // sr.SetMETBins({250, 1500});
  SRvec.emplace_back(sr);

  // Compressed regions
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("geq5j_lpt0to150_j1notb");
  sr.RemoveVar("nbtag");
  sr.SetVar("mt", 150, fInf);
  sr.SetVar("njet", 5, fInf);
  sr.SetVar("nbjet", 1, fInf);
  sr.SetVar("lep1pt", 0, 150);
  sr.SetVar("dphilmet", 0, 2.0);
  sr.SetVar("dphijmet", 0.5, 3.1416);
  sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 1500});
  sr.SetMETBins({250, 350, 450, 550, 700, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsNewMETBinning1() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsNewMETBinning() );
}

std::vector<SR> getStopControlRegionsDileptonNewMETBinning1() {
  return getStopControlRegionsDilepton( getStopSignalRegionsNewMETBinning() );
}

std::vector<SR> getStopSignalRegionsNewMETBinning() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar("mt", 150, fInf);
  srbase.SetVar("met", 250, fInf);
  srbase.SetVar("nlep", 1, 2);
  srbase.SetVar("nvlep", 1, 2);
  srbase.SetVar("passvetos", 1, 2);
  srbase.SetVar("njet", 2, fInf);
  srbase.SetVar("nbjet", 1, fInf);
  srbase.SetVar("mlb", 0, fInf);
  srbase.SetVar("tmod", -fInf, fInf);
  srbase.SetVar("dphijmet", 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // Test region at MET sideband for top taggers
  sr = srbase;
  sr.SetName("srsbmet");  // MET sideband
  sr.SetVar("met", 150, 250);
  sr.SetVar("passlep1pt", 1, 2);
  sr.SetMETBins({150, 200, 250});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetVar("nbtag", 1, fInf);
  sr.RemoveVar("nbjet");

  // SR 2-3j

  sr.SetName("srA0");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  // sr.SetMETBins({250, 350, 450, 600, 750, 1500});
  sr.SetMETBins({600, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srA1");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -1, wpDeepTop);
  // sr.SetMETBins({250, 350, 450, 600, 750, 1500});
  // sr.SetMETBins({350, 450, 600, 750, 1500});
  sr.SetMETBins({350, 450, 600});
  SRvec.emplace_back(sr);

  sr.SetName("srA2");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 600, 1500});
  sr.SetMETBins({250, 600});
  SRvec.emplace_back(sr);


  sr.SetName("srB0");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_nottag");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -1, 1);
  sr.SetMETBins({250, 450, 700, 1500});
  SRvec.emplace_back(sr);

  // sr.SetName("srB1");
  // sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_nottag");
  // sr.SetVar("njet", 2, 4);
  // sr.SetVar("tmod", 10, fInf);
  // sr.SetVar("mlb", 175, fInf);
  // sr.SetVar("deepttag", -1, wpDeepTop);
  // sr.SetMETBins({250, 450, 700, 1500});
  // SRvec.emplace_back(sr);

  // sr.SetName("srB2");
  // sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_deepttag");
  // sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetMETBins({250, 1500});
  // SRvec.emplace_back(sr);


  // SR ge4j

  sr.SetName("srC0");
  sr.SetDetailName("ge4j_tmodlt0_mlb0to175_met550");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  // sr.SetMETBins({250, 350, 450, 550, 650, 800, 1500});
  // sr.SetMETBins({450, 550, 650, 800, 1500});
  sr.SetMETBins({350, 450, 550, 650, 800, 1500});
  SRvec.emplace_back(sr);

  // sr.SetName("srC1");
  // sr.SetDetailName("ge4j_tmodlt0_mlb0to175_nottag");
  // sr.SetVar("njet", 4, fInf);
  // sr.SetVar("tmod", -fInf, 0);
  // sr.SetVar("mlb", 0, 175);
  // sr.SetVar("deepttag", -2, wpDeepTop);
  // sr.SetVar("resttag", -2, wpResTop);
  // // sr.SetMETBins({250, 350, 450, 550, 650, 800, 1500});
  // // sr.SetMETBins({250, 350, 450});
  // sr.SetMETBins({350, 450});
  // SRvec.emplace_back(sr);

  // sr.SetName("srC2");
  // sr.SetDetailName("ge4j_tmodlt0_mlb0to175_deepttag");
  // sr.SetVar("deepttag", wpDeepTop, 1);
  // sr.SetVar("resttag", -2, 1);
  // // sr.SetMETBins({250, 350, 450, 600, 1500});
  // sr.SetMETBins({350, 450});
  // SRvec.emplace_back(sr);

  // sr.SetName("srC3");
  // sr.SetDetailName("ge4j_tmodlt0_mlb0to175_resttag");
  // sr.SetVar("deepttag", -2, wpDeepTop);
  // sr.SetVar("resttag", wpResTop, 1);
  // // sr.SetMETBins({250, 350, 500, 1500});
  // // sr.SetMETBins({250, 350, 450});
  // sr.SetMETBins({350, 450});
  // SRvec.emplace_back(sr);


  sr.SetName("srD0");
  sr.SetDetailName("ge4j_tmodlt0_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);


  sr.SetName("srE0");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE1");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 450, 600, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE2");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 350, 450, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE3");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 450, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);


  sr.SetName("srF0");
  sr.SetDetailName("ge4j_tmod0to10_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);


  sr.SetName("srG0");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG1");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", -2, wpResTop);
  // sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG2");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar("deepttag", wpDeepTop, 1);
  sr.SetVar("resttag", -2, 1);
  // sr.SetMETBins({250, 450, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG3");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_resttag");
  sr.SetVar("deepttag", -2, wpDeepTop);
  sr.SetVar("resttag", wpResTop, 1);
  // sr.SetMETBins({250, 350, 500, 1500});
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);


  sr.SetName("srH0");
  sr.SetDetailName("ge4j_tmod10toInf_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("deepttag", -2, 1);
  sr.SetVar("resttag", -2, 1);
  sr.SetMETBins({250, 500, 1500});
  SRvec.emplace_back(sr);

  // SRvec.clear();  // TEMPORARY!!

  // Compressed regions
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("ge5j_lpt0to150_j1notb");
  // sr.RemoveVar("nbtag");
  sr.SetVar("mt", 150, fInf);
  sr.SetVar("njet", 5, fInf);
  sr.SetVar("nbjet", 1, fInf);
  sr.SetVar("lep1pt", 0, 150);
  sr.SetVar("dphilmet", 0, 2.0);
  sr.SetVar("dphijmet", 0.5, 3.1416);
  sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 1500});
  sr.SetMETBins({250, 350, 450, 550, 700, 1500});
  SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srI2");
  // sr.SetDetailName("ge2j_lpt0to150_j1notb");
  // sr.RemoveVar("nbtag");
  // sr.SetVar("mt", 100, fInf);
  // sr.SetVar("njet", 4, fInf);
  // sr.SetVar("nbjet", 1, fInf);
  // sr.SetVar("lep1pt", 0, 100);
  // sr.SetVar("j1pt", 200, fInf);
  // // sr.SetVar("j2pt", 20, 150);
  // // sr.SetVar("dphilmet", 0, 2.0);
  // sr.SetVar("dphijmet", 2, 3.1416);
  // sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 700, 1500});
  // SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srI3");
  // sr.SetDetailName("ge2j_lpt0to150_j1notb");
  // sr.RemoveVar("nbtag");
  // sr.SetVar("mt", 100, fInf);
  // sr.SetVar("njet", 4, fInf);
  // sr.SetVar("nbjet", 1, fInf);
  // sr.SetVar("lep1pt", 0, 100);
  // sr.SetVar("j1pt", 400, fInf);
  // // sr.SetVar("j2pt", 20, 150);
  // // sr.SetVar("dphilmet", 0, 2.0);
  // sr.SetVar("dphijmet", 2, 3.1416);
  // sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 700, 1500});
  // SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srI4");
  // sr.SetDetailName("ge2j_lpt0to150_j1notb");
  // sr.RemoveVar("nbtag");
  // sr.SetVar("mt", 100, fInf);
  // sr.SetVar("njet", 4, fInf);
  // sr.SetVar("nbjet", 1, fInf);
  // sr.SetVar("lep1pt", 0, 100);
  // sr.SetVar("j1pt", 600, fInf);
  // // sr.SetVar("j2pt", 20, 150);
  // // sr.SetVar("dphilmet", 0, 2.0);
  // sr.SetVar("dphijmet", 2, 3.1416);
  // sr.SetVar("j1passbtag", 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 700, 1500});
  // SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsNewMETBinning() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsNewMETBinning() );
}

std::vector<SR> getStopControlRegionsDileptonNewMETBinning() {
  return getStopControlRegionsDilepton( getStopSignalRegionsNewMETBinning() );
}

std::vector<SR> getStopSignalRegionsRun2() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar(mt, 150, fInf);
  srbase.SetVar(met, 250, fInf);
  srbase.SetVar(nlep, 1, 2);
  srbase.SetVar(nvlep, 1, 2);
  srbase.SetVar(passvetos, 1, 2);
  srbase.SetVar(njet, 2, fInf);
  srbase.SetVar(nbjet, 1, fInf);
  srbase.SetVar(mlb, 0, fInf);
  srbase.SetVar(tmod, -fInf, fInf);
  srbase.SetVar(dphijmet, 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // Start of nominal signal regions
  sr = srbase;
  sr.ReplaceVar(nbjet, nbtag);

  // SR 2-3j

  sr.SetName("srA0");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(met, 600, fInf);
  sr.SetMETBins({600, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srA1");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -1, wpDeepTop);
  sr.SetVar(met, 350, 600);
  sr.SetMETBins({350, 450, 600});
  SRvec.emplace_back(sr);

  sr.SetName("srA2");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(met, 250, 600);
  sr.SetMETBins({250, 600});
  SRvec.emplace_back(sr);


  sr.SetName("srB");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf_nottag");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetVar(deepttag, -1, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 450, 700, 1500});
  SRvec.emplace_back(sr);

  // SR ge4j

  sr.SetName("srC");
  sr.SetDetailName("ge4j_tmodlt0_mlb0to175_met550");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, -fInf, 0);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 350, fInf);
  sr.SetMETBins({350, 450, 550, 650, 800, 1500});
  SRvec.emplace_back(sr);


  sr.SetName("srD");
  sr.SetDetailName("ge4j_tmodlt0_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, -fInf, 0);
  sr.SetVar(mlb, 175, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);


  sr.SetName("srE0");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 450, fInf);
  sr.SetMETBins({450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE1");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_nottag");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, -2, wpResTop);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE2");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE3");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_tfttag");
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, wpResTop, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);


  sr.SetName("srF");
  sr.SetDetailName("ge4j_tmod0to10_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 175, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 350, 450, 1500});
  SRvec.emplace_back(sr);


  sr.SetName("srG0");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 450, fInf);
  sr.SetMETBins({450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG1");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, -2, wpResTop);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG2");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG3");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_tfttag");
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, wpResTop, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);


  sr.SetName("srH");
  sr.SetDetailName("ge4j_tmod10toInf_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 500, 1500});
  SRvec.emplace_back(sr);

  // SRvec.clear();  // TEMPORARY!!

  // Compressed (corridor) region
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("ge5j_lpt0to150_j1notb");
  sr.SetVar(njet, 5, fInf);
  sr.SetVar(nbjet, 1, fInf);
  // sr.SetVar(lep1pt, 0, 150);
  // sr.SetVar(dphilmet, 0, 2.0);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.RemoveVar(tmod);
  sr.RemoveVar(mlb);
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  // sr = srbase;
  sr.SetName("srJ");
  sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  sr.SetVar(njet, 3, fInf);
  sr.SetVar(nbjet, 0, fInf);
  sr.SetVar(nsbtag, 1, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}


std::vector<SR> getStopSignalRegionsTest2() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar(mt, 150, fInf);
  srbase.SetVar(met, 250, fInf);
  srbase.SetVar(nlep, 1, 2);
  srbase.SetVar(nvlep, 1, 2);
  srbase.SetVar(passvetos, 1, 2);
  srbase.SetVar(njet, 2, fInf);
  srbase.SetVar(nbjet, 1, fInf);
  srbase.SetVar(mlb, 0, fInf);
  srbase.SetVar(tmod, -fInf, fInf);
  srbase.SetVar(dphijmet, 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // Start of nominal signal regions
  sr = srbase;
  sr.ReplaceVar(nbjet, nbtag);

  // SR 2-3j

  sr = srbase;
  sr.SetName("srA");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srB");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetMETBins({250, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, -fInf, 0);
  sr.SetVar(mlb, 0, 175);
  sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, -fInf, 0);
  sr.SetVar(mlb, 175, fInf);
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE");
  sr.SetDetailName("geq4j_tmod0to10_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 0, 175);
  sr.SetMETBins({250, 350, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srF");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 175, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG");
  sr.SetDetailName("geq4j_tmod10toInf_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetMETBins({250, 350, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srH");
  sr.SetDetailName("geq4j_tmod10toInf_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  // Compressed regions
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("geq5j_lpt0to150_j1notb");
  sr.SetVar(mt, 150, fInf);
  sr.SetVar(njet, 5, fInf);
  sr.SetVar(nbjet, 1, fInf);
  sr.SetVar(lep1pt, 0, 150);
  sr.SetVar(dphilmet, 0, 2.0);
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  // SRvec.clear();  // TEMPORARY!!

  return SRvec;
}

std::vector<SR> getStopSignalRegionsTestRun2() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar(mt, 150, fInf);
  srbase.SetVar(met, 250, fInf);
  srbase.SetVar(nlep, 1, 2);
  srbase.SetVar(nvlep, 1, 2);
  srbase.SetVar(passvetos, 1, 2);
  srbase.SetVar(njet, 2, fInf);
  srbase.SetVar(nbjet, 1, fInf);
  srbase.SetVar(mlb, 0, fInf);
  srbase.SetVar(tmod, -fInf, fInf);
  srbase.SetVar(dphijmet, 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // Start of nominal signal regions
  sr = srbase;
  sr.ReplaceVar(nbjet, nbtag);

  // SR 2-3j

  sr.SetName("srA0");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(met, 600, fInf);
  sr.SetMETBins({600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srA1");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -1, wpDeepTop);
  sr.SetVar(met, 350, 600);
  sr.SetMETBins({350, 450, 600});
  SRvec.emplace_back(sr);

  sr.SetName("srA2");
  sr.SetDetailName("2to3j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(met, 250, 600);
  sr.SetMETBins({250, 600});
  SRvec.emplace_back(sr);


  sr.SetVar(met, 250, fInf);

  sr.SetName("srB");
  sr.SetDetailName("2to3j_tmod10toInf_mlb175toInf");
  sr.SetVar("njet", 2, 4);
  sr.SetVar("tmod", 10, fInf);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetMETBins({250, 450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srC");
  sr.SetDetailName("geq4j_tmodlt0_mlb0to175");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 0, 175);
  sr.SetVar("ntbtag", 0, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetMETBins({250, 350, 450, 550, 650, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srD");
  sr.SetDetailName("geq4j_tmodlt0_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", -fInf, 0);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE0");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 450, fInf);
  sr.SetMETBins({450, 550, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srE1");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_nottag");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 0, 10);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, -2, wpResTop);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE2");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srE3");
  sr.SetDetailName("ge4j_tmod0to10_mlb0to175_tfttag");
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, wpResTop, 1);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srF");
  sr.SetDetailName("geq4j_tmod0to10_mlb175toInf");
  sr.SetVar("njet", 4, fInf);
  sr.SetVar("tmod", 0, 10);
  sr.SetVar("mlb", 175, fInf);
  sr.SetVar("ntbtag", 1, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG0");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 450, fInf);
  sr.SetMETBins({450, 600, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srG1");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_nottag");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, -2, wpResTop);
  sr.SetVar(met, 250, 450);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG2");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_deepttag");
  sr.SetVar(deepttag, wpDeepTop, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);

  sr.SetName("srG3");
  sr.SetDetailName("ge4j_tmod10toInf_mlb0to175_tfttag");
  sr.SetVar(deepttag, -2, wpDeepTop);
  sr.SetVar(tfttag, wpResTop, 1);
  sr.SetMETBins({250, 350, 450});
  SRvec.emplace_back(sr);


  sr.SetName("srH");
  sr.SetDetailName("ge4j_tmod10toInf_mlb175toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetVar(deepttag, -2, 1);
  sr.SetVar(tfttag, -2, 1);
  sr.SetVar(met, 250, fInf);
  sr.SetMETBins({250, 450, 1500});
  SRvec.emplace_back(sr);

  // SRvec.clear();  // TEMPORARY!!

  // Compressed (corridor) region
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("ge5j_lpt0to150_j1notb");
  sr.SetVar(njet, 5, fInf);
  sr.SetVar(nbjet, 1, fInf);
  // sr.SetVar(lep1pt, 0, 150);
  // sr.SetVar(dphilmet, 0, 2.0);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.RemoveVar(tmod);
  sr.RemoveVar(mlb);
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  // sr = srbase;
  sr.SetName("srJ");
  sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  sr.SetVar(njet, 3, fInf);
  sr.SetVar(nbjet, 0, fInf);
  sr.SetVar(nsbtag, 1, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsRun2(const std::vector<SR>& SRvec = getStopSignalRegionsRun2()) {
  std::vector<SR> CRvec;

  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr0b"));
    cr.SetAllowDummyVars(1);
    if (cr.VarExists(ntbtag)) cr.RemoveVar(ntbtag);
    if (cr.VarExists(nbjet)) {
      cr.SetVar(nbjet, 0, 1);
    } else if (cr.VarExists(nbtag)) {
      cr.SetVar(nbtag, 0, 1);
    }
    if (cr.VarExists(tmod) && cr.GetLowerBound(tmod) < 10)
      cr.SetVar(nbjet, 0, 1);

    if (cr.VarExists(tfttag))   cr.RemoveVar(tfttag);
    if (cr.VarExists(deepttag)) cr.RemoveVar(deepttag);

    if (cr.VarExists(nsbtag)) cr.SetVar(nsbtag, 0, 1);
    if (cr.VarExists(mlb)) cr.ReplaceVar(mlb, mlb_0b);
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopControlRegionsDileptonRun2(const std::vector<SR>& SRvec = getStopSignalRegionsRun2()) {
  std::vector<SR> CRvec;

  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr2l"));
    cr.SetAllowDummyVars(1);
    cr.ReplaceVar(met, met_rl);
    cr.ReplaceVar(mt, mt_rl);
    cr.ReplaceVar(dphijmet, dphijmet_rl);
    cr.ReplaceVar(nlep, nlep_rl);
    cr.RemoveVar(passvetos);
    if (cr.VarExists(tmod)) cr.ReplaceVar(tmod, tmod_rl);
    if (cr.VarExists(dphilmet)) cr.ReplaceVar(dphilmet, dphilmet_rl);
    if (cr.VarExists(passlmetcor)) cr.ReplaceVar(passlmetcor, passlmet_rl);
    cr.SetVar(nvlep, 2, fInf);
    cr.SetVar(nlep_rl, 2, fInf);
    cr.SetVar(mt2_ll, 0, 100);  // to avoid overlap with the stop-2l SR
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopInclusiveRegionsRun2() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbase");
  srbase.SetVar(mt, 150, fInf);
  srbase.SetVar(met, 250, fInf);
  srbase.SetVar(nlep, 1, 2);
  srbase.SetVar(nvlep, 1, 2);
  srbase.SetVar(passvetos, 1, 2);
  srbase.SetVar(njet, 2, fInf);
  srbase.SetVar(nbjet, 1, fInf);
  srbase.SetVar(mlb, 0, fInf);
  srbase.SetVar(tmod, -fInf, fInf);
  srbase.SetVar(dphijmet, 0.8, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  SR sr;
  std::vector<SR> SRvec;

  SRvec.emplace_back(srbase);

  // The actual base region that is the sum of all SRs
  sr = srbase;
  sr.SetName("srincl0");
  sr.SetVar(njettmod, 1, 2);
  sr.ReplaceVar(nbjet, nbtag);
  SRvec.emplace_back(sr);

  // Inclusive for A+B
  sr.SetName("srincl1");
  sr.SetVar(njet, 2, 4);
  SRvec.emplace_back(sr);

  // Inclusive for C+D
  sr.SetName("srincl2");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tmod, -fInf, 0);
  SRvec.emplace_back(sr);

  // Inclusive for E+F
  sr.SetName("srincl3");
  sr.SetVar(tmod, 0, 10);
  SRvec.emplace_back(sr);

  // Inclusive for G+H
  sr.SetName("srincl4");
  sr.SetVar(tmod, 10, fInf);
  SRvec.emplace_back(sr);

  // Inclusive for C-H (geq 4j )
  sr.SetName("srincl4J");
  sr.SetVar(tmod, -fInf, fInf);
  sr.SetVar(njet, 4, fInf);
  SRvec.emplace_back(sr);

  // Inclusive for E+G
  sr.SetName("srincl5");
  sr.SetVar(tmod, 0, fInf);
  sr.SetVar(mlb, 0, 175);
  SRvec.emplace_back(sr);

  // Inclusive for E+G, low MET
  sr.SetName("srincl5L");
  sr.SetVar(met, 250, 450);
  SRvec.emplace_back(sr);
  sr.SetVar(met, 250, fInf);

  // Inclusive for E+G, low MET + not merge tagged
  sr.SetName("srincl5LR");
  sr.SetVar(met, 250, 450);
  sr.SetVar(deepttag, -2, wpDeepTop);
  SRvec.emplace_back(sr);
  sr.SetVar(met, 250, fInf);
  sr.RemoveVar(deepttag);

  // Inclusive for F+H
  sr.SetName("srincl6");
  sr.SetVar(mlb, 175, fInf);
  SRvec.emplace_back(sr);

  // Inclusive for A+E+G, low MET, (deepAK8 tags)
  sr.SetName("srincl7L");
  sr.SetVar(njettmod, 1, 2);
  sr.SetVar(njet, 2, fInf);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(tmod, 0, fInf);
  sr.SetVar(met, 250, 450);
  SRvec.emplace_back(sr);

  // Inclusive for A, low MET, (deepAK8 tags)
  sr.SetName("srinclA");
  sr.SetVar(njet, 2, 4);
  sr.SetVar(mlb, 0, 175);
  sr.SetVar(tmod, 10, fInf);
  sr.SetVar(met, 250, 600);
  SRvec.emplace_back(sr);

  sr.SetName("srinclM");
  sr.SetDetailName("ge2j_met250to450_mtag");
  sr.SetVar(met, 250, 450);
  sr.SetVar(njet, 2, fInf);
  sr.SetVar(mlb, 0, fInf);
  sr.SetVar(tmod, -fInf, fInf);
  sr.SetVar(deepttag, wpDeepTop, 1.1);
  SRvec.emplace_back(sr);
  sr.SetName("srinclMI");
  sr.SetDetailName("ge2j_met250to450_invmtag");
  sr.SetVar(deepttag, -2, wpDeepTop);
  SRvec.emplace_back(sr);
  sr.SetVar(met, 250, fInf);
  sr.RemoveVar(deepttag);

  sr.SetName("srinclR");
  sr.SetDetailName("ge2j_met250to450_rtag");
  sr.SetVar(met, 250, 450);
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(tfttag, wpResTop, 1.1);
  SRvec.emplace_back(sr);
  sr.SetName("srinclRI");
  sr.SetDetailName("ge2j_met250to450_invrtag");
  sr.SetVar(deepttag, -2, wpResTop);
  SRvec.emplace_back(sr);
  sr.SetVar(met, 250, fInf);
  sr.RemoveVar(tfttag);

  // Test region at MET sideband for top taggers
  sr = srbase;
  sr.SetName("srsbmet");  // MET sideband
  sr.SetDetailName("ge2j_met150to250");
  sr.SetVar(met, 150, 250);
  sr.SetVar(passlep1pt, 1, 2);
  sr.SetMETBins({150, 200, 250});
  SRvec.emplace_back(sr);

  sr.SetName("srsbmet2");  // MET sideband
  sr.SetDetailName("ge4j_met150to250_mt0toInf");
  sr.SetVar(met, 150, 250);
  sr.SetVar(mt, 0, fInf);
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(passlep1pt, 1, 2);
  sr.SetMETBins({150, 200, 250});
  SRvec.emplace_back(sr);

  sr.SetName("srsbmet3");  // MET sideband
  sr.SetDetailName("ge3j_met150to250_mt0toInf");
  sr.SetVar(njet, 3, fInf);
  sr.SetVar(mt, 100, 250);
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srsbfmet4");  // MET sideband
  sr.SetDetailName("ge2j_met125toInf_mt50toInf_dphijmet0toPi");
  sr.SetVar(met, 125, fInf);
  sr.SetVar(mt, 50, fInf);
  sr.SetVar(dphijmet, 0, 3.1416);
  sr.SetVar(passlep1pt, 1, 2);
  sr.SetMETBins({125, 200, 250});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srsbmt");  // MT sideband
  sr.SetDetailName("ge2j_met250toInf_mt0to150");
  sr.SetVar(mt, 0, 150);
  sr.SetVar(njet, 2, fInf);
  sr.SetVar(passlep1pt, 1, 2);
  sr.SetMETBins({150, 200, 250, 300, 400, 500, 800, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srsbmt2");  // MT sideband
  sr.SetDetailName("ge2j_met150toInf_mt0to150");
  sr.SetVar(met, 150, fInf);
  sr.SetMETBins({250, 300, 400, 500, 800, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srsbmlb");  // MT sideband
  sr.SetDetailName("ge4j_met150toInf_mt0to150");
  sr.SetVar(mt, 0, fInf);
  sr.SetVar(mlb, 175, fInf);
  sr.SetMETBins({250, 300, 400, 500, 800, 1500});
  SRvec.emplace_back(sr);
  sr.SetVar(mlb, 0, fInf);

  sr = srbase;
  sr.SetName("srsbfull");  // fullband
  sr.SetDetailName("ge2j_met150toInf_mt0toInf");
  sr.SetVar(met, 150, fInf);
  sr.SetVar(mt, 0, fInf);
  sr.SetVar(njet, 2, fInf);
  sr.SetVar(passlep1pt, 1, 2);
  sr.SetMETBins({150, 200, 250, 300, 400, 500, 800, 1500});
  SRvec.emplace_back(sr);

  sr.SetName("srsbfmt");
  sr.SetDetailName("ge2j_met250toInf_mt0toInf");
  sr.SetVar(njet, 2, fInf);
  sr.SetVar(met, 250, fInf);
  sr.SetVar(mt, 0, fInf);
  SRvec.emplace_back(sr);

  sr.SetName("srsbfmt2");
  sr.SetDetailName("ge2j_met250toInf_mt0toInf");
  sr.RemoveVar(passvetos);
  SRvec.emplace_back(sr);

  sr.SetName("srsbfmt4");
  sr.SetDetailName("ge4j_met250toInf_mt0toInf");
  sr.SetVar(njet, 4, fInf);
  sr.SetVar(passvetos, 1, 2);
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srsbfdphi");
  sr.SetDetailName("ge2j_met250toInf_dphi0topi");
  sr.SetVar(dphijmet, 0, 3.1416);
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srsbjfsb");
  sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  sr.SetVar(njet, 3, fInf);
  sr.SetVar(nbjet, 0, fInf);
  // sr.tVar(nsbtag, 0, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopSignalRegionsCorridorRun2() {

  SR srbase;
  srbase.SetAllowDummyVars(1);
  srbase.SetName("srbasecor");
  srbase.SetVar(mt, 150, fInf);
  srbase.SetVar(met, 250, fInf);
  srbase.SetVar(nlep, 1, 2);
  srbase.SetVar(nvlep, 1, 2);
  srbase.SetVar(passvetos, 1, 2);
  srbase.SetVar(njet, 5, fInf);
  // srbase.SetVar(nbjet, 0, fInf);
  srbase.SetVar(dphijmet, 0.5, 3.1416);
  srbase.SetMETBins({0, 250, 350, 450, 550, 650, 800, 1500});

  std::vector<SR> SRvec;
  // SRvec.emplace_back(srbase);

  SR sr;
  sr = srbase;
  sr.SetName("srI");
  sr.SetDetailName("ge5j_lpt0to150_j1notb");
  sr.SetVar(njet, 5, fInf);
  sr.SetVar(nbjet, 1, fInf);
  // sr.SetVar(nsbtag, 1, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srJ0");
  sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  sr.SetVar(njet, 5, fInf);
  sr.SetVar(nbjet, 0, fInf);
  sr.SetVar(nsbtag, 1, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 1500});
  SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srJ1");
  // sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  // sr.SetVar(njet, 4, fInf);
  // sr.SetVar(nbjet, 0, fInf);
  // sr.SetVar(nsbtag, 1, fInf);
  // sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  // sr.SetVar(dphijmet, 0.5, 3.1416);
  // sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  // SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srJ2");
  // sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  // sr.SetVar(njet, 3, 4);
  // sr.SetVar(nbjet, 0, fInf);
  // sr.SetVar(nsbtag, 1, fInf);
  // sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  // sr.SetVar(dphijmet, 0.5, 3.1416);
  // sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  // SRvec.emplace_back(sr);

  sr = srbase;
  sr.SetName("srJ3");
  sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  sr.SetVar(njet, 3, fInf);
  sr.SetVar(nbjet, 0, fInf);
  sr.SetVar(nsbtag, 1, fInf);
  sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  sr.SetVar(dphijmet, 0.5, 3.1416);
  sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srJ4");
  // sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  // sr.SetVar(njet, 3, fInf);
  // sr.SetVar(nbjet, 1, fInf);
  // sr.SetVar(nsbtag, 1, fInf);
  // sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  // sr.SetVar(dphijmet, 0.5, 3.1416);
  // sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({250, 350, 450, 550, 750, 1500});
  // SRvec.emplace_back(sr);

  // sr = srbase;
  // sr.SetName("srJ5");
  // sr.SetDetailName("ge5j_ge1sb_passlmetcor_j1notb");
  // sr.SetVar(njet, 3, fInf);
  // sr.SetVar(nbjet, 0, fInf);
  // sr.SetVar(nsbtag, 1, fInf);
  // sr.SetVar(passlmetcor, 1, 2); // shape cut on lep1pt & dphilmet
  // sr.SetVar(dphijmet, 0.5, 3.1416);
  // sr.SetVar(j1passbtag, 0, 1);  // Require j1 not b-tagged
  // sr.SetMETBins({350, 450, 550, 750, 1500});
  // SRvec.emplace_back(sr);

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsCorridorRun2() {
  std::vector<SR> CRvec;
  std::vector<SR> SRvec = getStopSignalRegionsCorridorRun2();

  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr0b"));
    cr.SetAllowDummyVars(1);
    if (cr.VarExists(nbjet))  cr.RemoveVar(nbjet);
    if (cr.VarExists(ntbtag)) cr.RemoveVar(ntbtag);
    if (cr.VarExists(nsbtag)) cr.SetVar(nsbtag, 0, 1);
    cr.SetVar(nbjet, 0, 1);
    if (cr.VarExists(mlb)) cr.ReplaceVar(mlb, mlb_0b);
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopControlRegionsDileptonCorridorRun2() {
  std::vector<SR> CRvec;
  std::vector<SR> SRvec = getStopSignalRegionsCorridorRun2();

  for (SR cr : SRvec) {
    cr.SetName(cr.GetName().replace(0, 2, "cr2l"));
    cr.SetAllowDummyVars(1);
    cr.ReplaceVar(met, met_rl);
    cr.ReplaceVar(mt, mt_rl);
    cr.ReplaceVar(dphijmet, dphijmet_rl);
    cr.ReplaceVar(nlep, nlep_rl);
    // cr.ReplaceVar(tmod, tmod_rl);
    cr.RemoveVar(passvetos);
    if (cr.VarExists(dphilmet)) cr.ReplaceVar(dphilmet, dphilmet_rl);
    if (cr.VarExists(passlmetcor)) cr.ReplaceVar(passlmetcor, passlmet_rl);
    cr.SetVar(nvlep, 2, fInf);
    cr.SetVar(nlep_rl, 2, fInf);
    cr.SetVar(mt2_ll, 0, 100);  // to avoid overlap with the stop-2l SR
    CRvec.emplace_back(cr);
  }

  return CRvec;
}

std::vector<SR> getStopSignalRegionsAddTopTagBins() {

  const float wpResTop = 0.8;
  const float wpDeepTop = 0.4;
  // const float wpDeepW = 0.3;

  std::vector<SR> orgSRvec = getStopSignalRegionsTopological();
  std::vector<SR> SRvec;

  for (SR sr : orgSRvec) {
    if (sr.GetName() == "srbase") {
      SRvec.emplace_back(sr);
    }
    else if (sr.GetLowerBound("njet") < 4) {
      std::string srname = sr.GetName();
      sr.SetAllowDummyVars(1);

      sr.SetName(srname+"1");
      sr.SetVar("deepttag", -2, wpDeepTop);
      // sr.SetVar("deepWtag", -2, wpDeepW);
      SRvec.emplace_back(sr);

      // sr.SetName(srname+"_wwt");
      // sr.SetVar("deepttag", -2, wpDeepTop);
      // sr.SetVar("deepWtag", wpDeepW, 1);
      // SRvec.emplace_back(sr);

      sr.SetName(srname+"2");
      sr.SetVar("deepttag", wpDeepTop, 1);
      // sr.SetVar("deepWtag", -2, 1);
      SRvec.emplace_back(sr);
    }
    else if (sr.GetLowerBound("njet") == 4) {
      std::string srname = sr.GetName();

      sr.SetName(srname+"1");
      sr.SetVar("deepttag", -2, wpDeepTop);
      // sr.SetVar("deepWtag", -2, wpDeepW);
      sr.SetVar("resttag", -2, wpResTop);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"2");
      sr.SetVar("deepttag", wpDeepTop, 1);
      // sr.SetVar("deepWtag", -2, 1);
      sr.SetVar("resttag", -2, 1);
      // sr.SetVar("resttag", -2, wpResTop);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"3");
      // sr.SetVar("deepttag", -2, 1);
      sr.SetVar("deepttag", -2, wpDeepTop);
      // sr.SetVar("deepWtag", -2, 1);
      sr.SetVar("resttag", wpResTop, 1);
      SRvec.emplace_back(sr);

      // sr.SetName(srname+"_wwt");
      // // sr.SetVar("deepttag", -2, 1);
      // sr.SetVar("deepttag", -2, wpDeepTop);
      // sr.SetVar("deepWtag", -2, 1);
      // sr.SetVar("resttag", -2, wpResTop);
      // SRvec.emplace_back(sr);

      // sr.SetName(srname+"_wrdt");
      // sr.SetVar("deepttag", wpDeepTop, 1);
      // sr.SetVar("resttag", wpResTop, 1);
      // // sr.SetMETBins({250, 500, 1500});
      // SRvec.emplace_back(sr);
    }
    else {
      SRvec.emplace_back(sr);
    }
  }

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsAddTopTagBins() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsAddTopTagBins() );
}

std::vector<SR> getStopControlRegionsDileptonAddTopTagBins() {
  return getStopControlRegionsDilepton( getStopSignalRegionsAddTopTagBins() );
}

std::vector<SR> getStopSignalRegionsBinInResolvedTag() {
  // Replace the tmod bin with the top tagger bin

  std::vector<SR> orgSRvec = getStopSignalRegionsTopological();
  std::vector<SR> SRvec;

  for (SR sr : orgSRvec) {
    if (sr.GetName() == "srbase") {
      SRvec.emplace_back(sr);
      continue;
    }

    sr.SetAllowDummyVars(1);
    if (sr.GetLowerBound("njet") == 4) {
      std::string name = sr.GetDetailName();
      if (sr.GetUpperBound("tmod") == 0) {
        sr.SetVar("resttag", -2, -1.05);
        name.replace(name.find("tmodlt0"), 7, "norestag");
      }
      else if (sr.GetLowerBound("tmod") == 0) {
        sr.SetVar("resttag", -1.05, wpResTop);
        name.replace(name.find("tmod0to10"), 9, "restaglt0p9");
      }
      else if (sr.GetLowerBound("tmod") == 10) {
        sr.SetVar("resttag", wpResTop, 1);
        name.replace(name.find("tmod10toInf"), 11, "restaggt0p9");
      }
      sr.SetDetailName(name);
      // sr.SetVar("tmod", -fInf, fInf);
      sr.RemoveVar("tmod");
    }

    std::string srname = sr.GetName();
    sr.SetName(srname+"_ndt");
    sr.SetVar("deepttag", -2, wpDeepTop);
    SRvec.emplace_back(sr);

    sr.SetName(srname+"_wdt");
    sr.SetVar("deepttag", wpDeepTop, 1);
    // sr.SetMETBins({250, 500, 1500});
    SRvec.emplace_back(sr);

  }

  // printf("%s:%d: printf here!\n", __FILE__, __LINE__);
  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsBinInResolvedTag() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsBinInResolvedTag() );
}

std::vector<SR> getStopControlRegionsDileptonBinInResolvedTag() {
  return getStopControlRegionsDilepton( getStopSignalRegionsBinInResolvedTag() );
}

std::vector<SR> getStopSignalRegionsBinInMergedTag() {
  // Replace the tmod bin with the top tagger bin

  std::vector<SR> orgSRvec = getStopSignalRegionsTopological();
  std::vector<SR> SRvec;

  for (SR sr : orgSRvec) {
    if (sr.GetName() == "srbase") {
      SRvec.emplace_back(sr);
      continue;
    }
    sr.SetAllowDummyVars(1);
    std::string srname = sr.GetName();
    std::string dname = sr.GetDetailName();

    if (sr.GetUpperBound("tmod") == 0) {
      sr.SetVar("deepttag", -2, 0.02);
      // sr.SetVar("binttag", -2, 0.02);
      dname.replace(dname.find("tmodlt0"), 8, "nomergetag");
    }
    else if (sr.GetLowerBound("tmod") == 0) {
      sr.SetVar("deepttag", 0.02, wpDeepTop);
      // sr.SetVar("binttag", 0.02, wpDeepTop);
      dname.replace(dname.find("tmod0to10"), 9, "mergetaglt0p6");
    }
    else if (sr.GetLowerBound("tmod") == 10) {
      sr.SetVar("deepttag", wpDeepTop, 1);
      // sr.SetVar("binttag", wpDeepTop, 1);
      dname.replace(dname.find("tmod10toInf"), 11, "mergetaggt0p6");
    }
    sr.SetDetailName(dname);
    sr.SetVar("tmod", -fInf, fInf);

    // sr.SetName(srname+"_ndt");
    // sr.SetVar("resttag", -2, wpResTop);
    // SRvec.emplace_back(sr);

    // sr.SetName(srname+"_wdt");
    // sr.SetVar("resttag", wpResTop, 1);
    // sr.SetMETBins({250, 500, 1500});
    SRvec.emplace_back(sr);

  }

  // printf("%s:%d: printf here!\n", __FILE__, __LINE__);
  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsBinInMergedTag() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsBinInMergedTag() );
}

std::vector<SR> getStopControlRegionsDileptonBinInMergedTag() {
  return getStopControlRegionsDilepton( getStopSignalRegionsBinInMergedTag() );
}

std::vector<SR> getStopSignalRegionsBooleanTopTags() {

  std::vector<SR> orgSRvec = getStopSignalRegionsTopological();
  std::vector<SR> SRvec;

  for (SR sr : orgSRvec) {
    if (sr.GetName() == "srbase") {
      SRvec.emplace_back(sr);
    }
    else if (sr.GetLowerBound("njet") < 4) {
      std::string srname = sr.GetName();
      sr.SetAllowDummyVars(1);

      sr.SetName(srname+"_ntt");
      sr.SetVar("passdeepttag", 0, 1);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"_wdt");
      sr.SetVar("passdeepttag", 1, 2);
      SRvec.emplace_back(sr);
    }
    else if (sr.GetLowerBound("njet") == 4) {
      std::string srname = sr.GetName();

      sr.SetName(srname+"_ntt");
      sr.SetVar("passdeepttag", 0, 1);
      sr.SetVar("passresttag", 0, 1);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"_wdt");
      sr.SetVar("passdeepttag", 1, 2);
      sr.SetVar("passresttag", 0, 2);
      SRvec.emplace_back(sr);

      sr.SetName(srname+"_wrt");
      sr.SetVar("passdeepttag", 0, 1);
      sr.SetVar("passresttag", 1, 2);
      SRvec.emplace_back(sr);

    }
    else {
      SRvec.emplace_back(sr);
    }
  }

  return SRvec;
}

std::vector<SR> getStopControlRegionsNoBTagsBooleanTopTags() {
  return getStopControlRegionsNoBTags( getStopSignalRegionsBooleanTopTags() );
}

std::vector<SR> getStopControlRegionsDileptonBooleanTopTags() {
  return getStopControlRegionsDilepton( getStopSignalRegionsBooleanTopTags() );
}
