// -*- C++ -*-
//
// Package:    MyAnalyzer/SSEMAnlzr
// Class:      SSEMAnlzr
//
/**\class SSEMAnlzr SSEMAnlzr.cc MyAnalyzer/SSEMAnlzr/plugins/SSEMAnlzr.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jian Wang
//         Created:  Wed, 28 Jun 2023 09:01:56 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/transform.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "TLorentzVector.h"
#include "TRandom.h"
#include <TTree.h>

using namespace edm;
using namespace reco;
using namespace std;

#include <vector>
#include <unordered_map>
#include <iostream>
#include <regex>


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


class SSEMAnlzr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit SSEMAnlzr(const edm::ParameterSet&);
      ~SSEMAnlzr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      EDGetTokenT<VertexCollection> vtxToken_;
      EDGetTokenT<pat::MuonCollection> muonToken_;
      EDGetTokenT<edm::Association<reco::GenParticleCollection>> mcmapmuonToken_;
      EDGetTokenT<reco::CandidateView> candmuonToken_;
      EDGetTokenT<pat::ElectronCollection> electronToken_;
      EDGetTokenT<edm::Association<reco::GenParticleCollection>> mcmapelectronToken_;
      EDGetTokenT<reco::CandidateView> candelectronToken_;
      EDGetTokenT<pat::PackedCandidateCollection> pfToken_;
      EDGetTokenT<edm::View<pat::PackedGenParticle>> packedgenToken_;
      EDGetTokenT<GenParticleCollection> prunedGenToken_;
      EDGetTokenT<TriggerResults> triggerToken_;
      EDGetTokenT<TriggerResults> metfilterToken_;
      EDGetTokenT<BeamSpot> bsToken_;
      EDGetTokenT<GenEventInfoProduct> generatorLabel_;
      EDGetTokenT<std::vector<PileupSummaryInfo>> pileupSummaryToken_;
      EDGetTokenT<std::vector<pat::MET>> metToken_;
      std::vector<edm::InputTag> lheLabel_;
      std::vector<edm::EDGetTokenT<LHEEventProduct>> lheTag_;



      TTree *tr;
      TH1F *h_step;

      bool MC_;
      int year_;
      size_t n_mu, n_el, n_pv, pv_ntrk2, pv_ntrk3, pv_nmu,
	     ntrk_prompt, ntrk_nonprompt, ntrk_HS, ntrk_PU, ntrk_all, ntrk_signal, is_DYtauetaumu, is_ZG;
      size_t hlt_mu23_el12, hlt_mu23_el12_DZ, hlt_mu8_el23, hlt_mu8_el23_DZ, hlt_isomu24, hlt_isotkmu24, hlt_isomu27, hlt_mu17_mu8, hlt_mu17_mu8_DZ, hlt_mu17_tkmu8, hlt_mu17_tkmu8_DZ, hlt_tkmu17_tkmu8, hlt_tkmu17_tkmu8_DZ, hlt_mu17_mu8_DZ_mass3p8, hlt_mu17_mu8_DZ_mass8 = 0;

      int el_conversionveto[5], el_losthits[5], mu_trigger8[5], mu_trigger23[5], mu_triggerIsoMu24[5], mu_frompv[5], mu_charge[5], mu_tight[5],el_charge[5], el_frompv[5], el_trigger[5], el_chargeconsistent[5];
      int el_CBIDLoose[5],el_CBIDMedium[5],el_CBIDTight[5],el_CBIDVeto[5],el_MVAIDisoWP80[5],el_MVAIDisoWP90[5],el_MVAIDisoWPHZZ[5],el_MVAIDisoWPLoose[5],el_MVAIDnoisoWP80[5],el_MVAIDnoisoWP90[5],el_MVAIDnoisoWPLoose[5], mu_pfiso[5], el_genPart[5], mu_genPart[5];
      double mu_pt[5], mu_eta[5], mu_phi[5], mu_dxy[5], mu_dz[5], mu_rawiso[5], 
             el_pt[5], el_eta[5], el_phi[5], el_dxy[5], el_dz[5], 
	     pv_d0, pv_dz, pv_ndof, pv_chi2,
         pt_2mu, pt_3mu_s, pt_3mu_v, mass_2mu, dphi_2mu, pv_charge, pt_vector, pt_scalar; // deta_trk; // pt2trk_1mm, pt2trk_3mm;
      float genWeight=1.0;
      float gentop_pt, genantitop_pt, gentop_eta, genantitop_eta, gentop_phi, genantitop_phi;
      float Pileup_trueNumInteractions = -1;
      int Pileup_puNumInteractions = -1;
      float PuppiMET_pt, PuppiMET_phi;
      float taug2weight=1.0;
      int Flag_ecalBadCalibFilter=0;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SSEMAnlzr::SSEMAnlzr(const edm::ParameterSet& iConfig)
 :
    vtxToken_(consumes<VertexCollection>(iConfig.getParameter<InputTag>("vertices"))),
    muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
    mcmapmuonToken_(consumes<edm::Association<reco::GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("mcmapmuons"))),
    candmuonToken_(consumes<reco::CandidateView>(iConfig.getParameter<edm::InputTag>("muons"))),
    electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
    mcmapelectronToken_(consumes<edm::Association<reco::GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("mcmapelectrons"))),
    candelectronToken_(consumes<reco::CandidateView>(iConfig.getParameter<edm::InputTag>("electrons"))),
    pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
    packedgenToken_(consumes<edm::View<pat::PackedGenParticle>>(iConfig.getParameter<edm::InputTag>("packedgens"))),
    prunedGenToken_(consumes<GenParticleCollection>(iConfig.getParameter<InputTag>("pruned"))),
    triggerToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("triggerBitsH"))),
    metfilterToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("metfilterBitsH"))),
    bsToken_(consumes<BeamSpot>(iConfig.getParameter<InputTag>("beamSpotHandle"))),
    generatorLabel_(consumes<GenEventInfoProduct>(iConfig.getParameter<InputTag>("generatorLabel"))),
    pileupSummaryToken_(consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<InputTag>("pileupInfo"))),
    metToken_(consumes<std::vector<pat::MET>>(iConfig.getParameter<InputTag>("mets"))),
    lheLabel_(iConfig.getParameter<std::vector<edm::InputTag>>("lheInfo")),
    lheTag_(edm::vector_transform(lheLabel_,
                                      [this](const edm::InputTag& tag) { return mayConsume<LHEEventProduct>(tag); }))

{
   //now do what ever initialization is needed

   MC_ = iConfig.getParameter<bool>("MC");
   year_ = iConfig.getParameter<int>("year");

   Service<TFileService> fs;
   h_step = fs->make<TH1F>("step", "", 10, 0, 10);
   tr = fs->make<TTree>("tree_em", "");
   tr->Branch("n_mu", &n_mu, "n_mu/I");
   tr->Branch("mu_pt", mu_pt, "mu_pt[n_mu]/D");
   tr->Branch("mu_eta", mu_eta, "mu_eta[n_mu]/D");
   tr->Branch("mu_phi", mu_phi, "mu_phi[n_mu]/D");
   tr->Branch("mu_charge", mu_charge, "mu_charge[n_mu]/I");
   tr->Branch("mu_genPart", mu_genPart, "mu_genPart[n_mu]/I");
   tr->Branch("mu_tight", mu_tight, "mu_tight[n_mu]/I");
   tr->Branch("mu_frompv", mu_frompv, "mu_frompv[n_mu]/I");
   tr->Branch("mu_trigger23", mu_trigger23, "mu_trigger23[n_mu]/I");
   tr->Branch("mu_trigger8", mu_trigger8, "mu_trigger8[n_mu]/I");
   tr->Branch("mu_triggerIsoMu24", mu_triggerIsoMu24, "mu_triggerIsoMu24[n_mu]/I");
   tr->Branch("mu_pfiso", mu_pfiso, "mu_pfiso[n_mu]/I");
   tr->Branch("mu_rawiso", mu_rawiso, "mu_rawiso[n_mu]/D");
   tr->Branch("mu_dxy", mu_dxy, "mu_dxy[n_mu]/D");
   tr->Branch("mu_dz", mu_dz, "mu_dz[n_mu]/D");

   tr->Branch("n_el", &n_el, "n_el/I");
   tr->Branch("el_pt", el_pt, "el_pt[n_el]/D");
   tr->Branch("el_dxy", el_dxy, "el_dxy[n_el]/D");
   tr->Branch("el_dz", el_dz, "el_dz[n_el]/D");
   tr->Branch("el_eta", el_eta, "el_eta[n_el]/D");
   tr->Branch("el_phi", el_phi, "el_phi[n_el]/D");
   tr->Branch("el_charge", el_charge, "el_charge[n_el]/I");
   tr->Branch("el_genPart", el_genPart, "el_genPart[n_el]/I");
   tr->Branch("el_frompv", el_frompv, "el_frompv[n_el]/I");
   tr->Branch("el_trigger", el_trigger, "el_trigger[n_el]/I");
   tr->Branch("el_conversionveto", el_conversionveto, "el_conversionveto[n_el]/I");
   tr->Branch("el_losthits", el_losthits, "el_losthits[n_el]/I");
   //tr->Branch("el_CBIDLoose", el_CBIDLoose, "el_CBIDLoose[n_el]/I");
   //tr->Branch("el_CBIDMedium", el_CBIDMedium, "el_CBIDMedium[n_el]/I");
   //tr->Branch("el_CBIDTight", el_CBIDTight, "el_CBIDTight[n_el]/I");
   //tr->Branch("el_CBIDVeto", el_CBIDVeto, "el_CBIDVeto[n_el]/I");
   tr->Branch("el_MVAIDisoWP80", el_MVAIDisoWP80, "el_MVAIDisoWP80[n_el]/I");
   tr->Branch("el_MVAIDisoWP90", el_MVAIDisoWP90, "el_MVAIDisoWP90[n_el]/I");
   tr->Branch("el_MVAIDisoWPHZZ", el_MVAIDisoWPHZZ, "el_MVAIDisoWPHZZ[n_el]/I");
   tr->Branch("el_MVAIDisoWPLoose", el_MVAIDisoWPLoose, "el_MVAIDisoWPLoose[n_el]/I");
   //tr->Branch("el_MVAIDnoisoWP80", el_MVAIDnoisoWP80, "el_MVAIDnoisoWP80[n_el]/I");
   //tr->Branch("el_MVAIDnoisoWP90", el_MVAIDnoisoWP90, "el_MVAIDnoisoWP90[n_el]/I");
   //tr->Branch("el_MVAIDnoisoWPLoose", el_MVAIDnoisoWPLoose, "el_MVAIDnoisoWPLoose[n_el]/I");
   tr->Branch("el_chargeconsistent", el_chargeconsistent, "el_chargeconsistent[n_el]/I");

   //tr->Branch("n_pv", &n_pv, "n_pv/I");
   //tr->Branch("pv_ndof", &pv_ndof, "pv_ndof/D");
   //tr->Branch("pv_chi2", &pv_chi2, "pv_chi2/D");
   //tr->Branch("pv_d0", &pv_d0, "pv_d0/D");
   tr->Branch("pv_dz", &pv_dz, "pv_dz/D");
   //tr->Branch("pv_ntrk2", &pv_ntrk2, "pv_ntrk2/I");
   //tr->Branch("pv_ntrk3", &pv_ntrk3, "pv_ntrk3/I");
   tr->Branch("ntrk_prompt", &ntrk_prompt, "ntrk_prompt/I");
   tr->Branch("ntrk_nonprompt", &ntrk_nonprompt, "ntrk_nonprompt/I");
   tr->Branch("ntrk_HS", &ntrk_HS, "ntrk_HS/I");
   tr->Branch("ntrk_signal", &ntrk_signal, "ntrk_signal/I");
   tr->Branch("ntrk_all", &ntrk_all, "ntrk_all/I");
   tr->Branch("ntrk_PU", &ntrk_PU, "ntrk_PU/I");
   //tr->Branch("pv_nmu", &pv_nmu, "pv_nmu/I");
   //tr->Branch("pv_charge", &pv_charge, "pv_charge/D");
   //tr->Branch("pt_vector", &pt_vector, "pt_vector/D");
   //tr->Branch("pt_scalar", &pt_scalar, "pt_scalar/D");
   //
   //

   tr->Branch("hlt_mu23_el12", &hlt_mu23_el12, "hlt_mu23_el12/I");
   tr->Branch("hlt_mu23_el12_DZ", &hlt_mu23_el12_DZ, "hlt_mu23_el12_DZ/I");
   tr->Branch("hlt_mu8_el23", &hlt_mu8_el23, "hlt_mu8_el23/I");
   tr->Branch("hlt_mu8_el23_DZ", &hlt_mu8_el23_DZ, "hlt_mu8_el23_DZ/I");
   tr->Branch("hlt_isomu24", &hlt_isomu24, "hlt_isomu24/I");
   tr->Branch("hlt_isotkmu24", &hlt_isotkmu24, "hlt_isotkmu24/I");
   tr->Branch("hlt_isomu27", &hlt_isomu27, "hlt_isomu27/I");
   tr->Branch("hlt_mu17_mu8", &hlt_mu17_mu8, "hlt_mu17_mu8/I");
   tr->Branch("hlt_mu17_mu8_DZ", &hlt_mu17_mu8_DZ, "hlt_mu17_mu8_DZ/I");
   tr->Branch("hlt_mu17_tkmu8", &hlt_mu17_tkmu8, "hlt_mu17_tkmu8/I");
   tr->Branch("hlt_mu17_tkmu8_DZ", &hlt_mu17_tkmu8_DZ, "hlt_mu17_tkmu8_DZ/I");
   tr->Branch("hlt_tkmu17_tkmu8", &hlt_tkmu17_tkmu8, "hlt_tkmu17_tkmu8/I");
   tr->Branch("hlt_tkmu17_tkmu8_DZ", &hlt_tkmu17_tkmu8_DZ, "hlt_tkmu17_tkmu8_DZ/I");
   tr->Branch("hlt_mu17_mu8_DZ_mass3p8", &hlt_mu17_mu8_DZ_mass3p8, "hlt_mu17_mu8_DZ_mass3p8/I");
   tr->Branch("hlt_mu17_mu8_DZ_mass8", &hlt_mu17_mu8_DZ_mass8, "hlt_mu17_mu8_DZ_mass8/I");

   tr->Branch("is_DYtauetaumu", &is_DYtauetaumu, "is_DYtauetaumu/I");
   tr->Branch("is_ZG", &is_ZG, "is_ZG/I");
   tr->Branch("genWeight", &genWeight, "genWeight/F");
   tr->Branch("gentop_pt", &gentop_pt, "gentop_pt/F");
   tr->Branch("genantitop_pt", &genantitop_pt, "genantitop_pt/F");
   tr->Branch("gentop_eta", &gentop_eta, "gentop_eta/F");
   tr->Branch("genantitop_eta", &genantitop_eta, "genantitop_eta/F");
   tr->Branch("gentop_phi", &gentop_phi, "gentop_phi/F");
   tr->Branch("genantitop_phi", &genantitop_phi, "genantitop_phi/F");

   tr->Branch("PuppiMET_pt", &PuppiMET_pt, "PuppiMET_pt/F");
   tr->Branch("PuppiMET_phi", &PuppiMET_phi, "PuppiMET_phi/F");

   tr->Branch("Pileup_trueNumInteractions", &Pileup_trueNumInteractions, "Pileup_trueNumInteractions/F");
   tr->Branch("Pileup_puNumInteractions", &Pileup_puNumInteractions, "Pileup_puNumInteractions/I");

   tr->Branch("taug2weight", &taug2weight, "taug2weight/F");

   tr->Branch("Flag_ecalBadCalibFilter", &Flag_ecalBadCalibFilter, "Flag_ecalBadCalibFilter/I");

}


SSEMAnlzr::~SSEMAnlzr()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SSEMAnlzr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    h_step->Fill(0);

    if (MC_){
       Handle<GenEventInfoProduct> genEventInfoHandle;
       iEvent.getByToken(generatorLabel_, genEventInfoHandle);
       if (genEventInfoHandle.isValid()) { 
         if (genEventInfoHandle->hasBinningValues())
         genWeight = genEventInfoHandle->weight();
       }

       h_step->Fill(1,genWeight);
    }

    float trueNumInteractions = -1;
    int puNumInteractions = -1;
    if (MC_) {
       Handle<std::vector<PileupSummaryInfo>> PupInfo;
       iEvent.getByToken(pileupSummaryToken_, PupInfo);

       for (auto PVI : *PupInfo) {
          int BX = PVI.getBunchCrossing();
          if (BX == 0) {
             trueNumInteractions = PVI.getTrueNumInteractions();
             puNumInteractions = PVI.getPU_NumInteractions();
             continue;
          }
       }
    }

    Pileup_trueNumInteractions = trueNumInteractions;
    Pileup_puNumInteractions = puNumInteractions;

    ///////////////////
    // tau g2 weight //
    // ////////////////
    edm::Handle<LHEEventProduct> lheInfo;
    for (const auto& lheTag : lheTag_) {
      iEvent.getByToken(lheTag, lheInfo);
      if (lheInfo.isValid()) {
        break;
      }
    }
    if (lheInfo.isValid()) {

       double normWeight = lheInfo->originalXWGTUP();
       std::vector<gen::WeightsInfo> weights = lheInfo->weights();
       for (const auto& weight: weights)
       {
          std::size_t found = weight.id.find("ceBRe_0p0");
          if (found!=std::string::npos) taug2weight=weight.wgt/normWeight;
       }
    }



    ///////////////
    // MET filters
    //////////////

    bool Flag_goodVertices=0;
    bool Flag_globalSuperTightHalo2016Filter=0;
    bool Flag_HBHENoiseFilter=0;
    bool Flag_HBHENoiseIsoFilter=0;
    bool Flag_EcalDeadCellTriggerPrimitiveFilter=0;
    bool Flag_BadPFMuonFilter=0;
    bool Flag_BadPFMuonDzFilter=0;
    bool Flag_eeBadScFilter=0;
    //bool Flag_ecalBadCalibFilter=0;

    Handle<TriggerResults> metfilterBitsH;
    iEvent.getByToken(metfilterToken_, metfilterBitsH);

    const TriggerNames &metfilterNames = iEvent.triggerNames( *metfilterBitsH );
    for (size_t i_met = 0; i_met != metfilterBitsH->size(); ++i_met)
    {
      string metName = metfilterNames.triggerName(i_met);

      if(!(metName.find("Flag_goodVertices") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_goodVertices = 1;}
      if(!(metName.find("Flag_globalSuperTightHalo2016Filter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_globalSuperTightHalo2016Filter = 1;}
      if(!(metName.find("Flag_HBHENoiseFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_HBHENoiseFilter = 1;}
      if(!(metName.find("Flag_HBHENoiseIsoFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_HBHENoiseIsoFilter = 1;}
      if(!(metName.find("Flag_EcalDeadCellTriggerPrimitiveFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_EcalDeadCellTriggerPrimitiveFilter = 1;}
      if(!(metName.find("Flag_BadPFMuonFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_BadPFMuonFilter = 1;}
      if(!(metName.find("Flag_BadPFMuonDzFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_BadPFMuonDzFilter = 1;}
      if(!(metName.find("Flag_eeBadScFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_eeBadScFilter = 1;}
      if(!(metName.find("Flag_ecalBadCalibFilter") == string::npos)){      if( metfilterBitsH->wasrun(i_met) && !metfilterBitsH->error(i_met) && metfilterBitsH->accept(i_met )) Flag_ecalBadCalibFilter = 1;}

    }

    if (!Flag_goodVertices or !Flag_globalSuperTightHalo2016Filter or !Flag_HBHENoiseFilter or !Flag_HBHENoiseIsoFilter or !Flag_EcalDeadCellTriggerPrimitiveFilter or !Flag_BadPFMuonFilter or !Flag_BadPFMuonDzFilter or !Flag_eeBadScFilter) return;

    //FIXME in 2016 UL dont apply the last filter


    Handle<std::vector<pat::MET>> mets;
    iEvent.getByToken(metToken_, mets);
    const pat::MET &met = mets->front();
    PuppiMET_pt=met.pt();
    PuppiMET_phi=met.phi();

    //////////
    // HLT
    //////////

    hlt_mu23_el12 = 0;
    hlt_mu23_el12_DZ = 0;
    hlt_mu8_el23 = 0;
    hlt_mu8_el23_DZ = 0;

    hlt_isomu24 = 0;
    hlt_isotkmu24 = 0;
    hlt_isomu27 = 0;

    hlt_mu17_mu8 = 0;
    hlt_mu17_mu8_DZ = 0;
    hlt_mu17_tkmu8 = 0;
    hlt_mu17_tkmu8_DZ = 0;
    hlt_tkmu17_tkmu8 = 0;
    hlt_tkmu17_tkmu8_DZ = 0;
    hlt_mu17_mu8_DZ_mass3p8 = 0;
    hlt_mu17_mu8_DZ_mass8 = 0;

    Handle<TriggerResults> triggerBitsH;
    iEvent.getByToken(triggerToken_, triggerBitsH);

    const TriggerNames &triggerNames = iEvent.triggerNames( *triggerBitsH );
    for (size_t i_hlt = 0; i_hlt != triggerBitsH->size(); ++i_hlt)
    {
      string hltName = triggerNames.triggerName(i_hlt);

      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8_DZ_mass3p8 = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8_DZ_mass8 = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8_DZ = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8 = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_tkmu8_DZ = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_tkmu8 = 1;
      }
      if(!(hltName.find("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tkmu17_tkmu8_DZ = 1;
      }
      if(!(hltName.find("HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tkmu17_tkmu8 = 1;
      }


      if(!(hltName.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu23_el12_DZ = 1;
      }
      if(!(hltName.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu23_el12 = 1;
      }
      if(!(hltName.find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu8_el23_DZ = 1;
      }
      if(!(hltName.find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu8_el23 = 1;
      }


      if(!(hltName.find("HLT_IsoMu24_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_isomu24 = 1;
      }
      if(!(hltName.find("HLT_IsoTkMu24_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_isotkmu24 = 1;
      }
      if(!(hltName.find("HLT_IsoMu27_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_isomu27 = 1;
      }

    }

    //if(hlt_mu23_el12<0.5 && hlt_mu8_el23<0.5 && hlt_isomu24<0.5 && hlt_el23_el12<0.5 and hlt_el25_el25<0.5 and hlt_mu17_mu8<0.5 and hlt_mu12_el23<0.5 and hlt_el32<0.5 and hlt_mu9_mu9_el9<0.5) return;
    if (year_==2016 and !hlt_isomu24 and !hlt_isotkmu24 and !hlt_mu23_el12_DZ and !hlt_mu23_el12 and !hlt_mu8_el23_DZ and !hlt_mu8_el23 and !hlt_mu17_mu8_DZ and !hlt_mu17_mu8 and !hlt_mu17_tkmu8_DZ and !hlt_mu17_tkmu8 and !hlt_tkmu17_tkmu8_DZ and !hlt_tkmu17_tkmu8) return;
    if (year_==2017 and !hlt_isomu27 and !hlt_mu23_el12_DZ and !hlt_mu8_el23_DZ and !hlt_mu17_mu8_DZ_mass3p8 and !hlt_mu17_mu8_DZ_mass8) return;
    if (year_==2018 and !hlt_isomu24 and !hlt_mu23_el12 and !hlt_mu8_el23 and !hlt_mu17_mu8) return;
    h_step->Fill(2);


    //////////
    // PV
    //////////

    Handle<VertexCollection> vertices;
    iEvent.getByToken(vtxToken_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    h_step->Fill(3);
    n_pv = vertices->size();
    const reco::Vertex &PV = vertices->front();
    pv_ndof = PV.ndof();
    pv_chi2 = PV.chi2();

    BeamSpot bs;
    Handle<BeamSpot> beamSpotHandle;
    iEvent.getByToken(bsToken_, beamSpotHandle);
    bs = *beamSpotHandle;

    double pv_dx = PV.position().X() - bs.x0();
    double pv_dy = PV.position().Y() - bs.y0();
    pv_d0 = sqrt(pv_dx*pv_dx+pv_dy*pv_dy);
    pv_dz = PV.position().Z() - bs.z0();

   /*
    Handle<GenParticleCollection> pruned;
    iEvent.getByToken(prunedGenToken_,pruned);
    for (size_t i = 0; i < pruned->size(); ++i) {
        const GenParticle &p = (*pruned)[i];
        // const Candidate * mom = p.mother();
        //if(fabs(p.pdgId())==24 && p.numberOfDaughters()>1 ) 
        cout<<p.pdgId()<<"    "<<p.pt()<<"    "<<p.eta()<<endl;
    }
    cout<<endl;
   */
    gentop_pt=-1;
    genantitop_pt=-1;
    gentop_eta=99;
    genantitop_eta=99;
    gentop_phi=99;
    genantitop_phi=99;
    is_DYtauetaumu=0;
    is_ZG=0;
    bool is_taue=false;
    bool is_taumu=false;
    bool is_22fromq=false;
    bool is_23fromq=false;
    if (MC_){
       Handle<GenParticleCollection> pruned;
       iEvent.getByToken(prunedGenToken_,pruned);
       for (size_t i = 0; i < pruned->size(); ++i) {
           const GenParticle &p = (*pruned)[i];
           const Candidate * mom = p.mother();
	   //if (fabs(p.pdgId())<2000) std::cout<<p.pdgId()<<" "<<mom->pdgId()<<" "<<p.pt()<<std::endl;
	   if (fabs(p.pdgId())==22 and fabs(mom->pdgId())==23) is_ZG=1;
           if (fabs(p.pdgId())==22 and (fabs(mom->pdgId())<6 or fabs(mom->pdgId())==21)) is_22fromq=true;
           if (fabs(p.pdgId())==23 and (fabs(mom->pdgId())<6 or fabs(mom->pdgId())==21)) is_23fromq=true;
           if (gentop_pt<0 and p.pdgId()==6) gentop_pt=p.pt();
           if (genantitop_pt<0 and p.pdgId()==-6) genantitop_pt=p.pt();
           if (gentop_pt<0 and p.pdgId()==15){ 
	      gentop_pt=p.pt();
              gentop_eta=p.eta();
              gentop_phi=p.phi();
	   }
           if (genantitop_pt<0 and p.pdgId()==-15){ 
	      genantitop_pt=p.pt();
              genantitop_eta=p.eta();
              genantitop_phi=p.phi();
	   }
	   if (fabs(p.pdgId())==11 and fabs(mom->pdgId())==15) is_taue=true;
           if (fabs(p.pdgId())==13 and fabs(mom->pdgId())==15) is_taumu=true;
       }
    }
    if (is_22fromq && is_23fromq) is_ZG=1;
    //std::cout<<is_ZG<<std::endl<<std::endl;
    if (is_taue && is_taumu) is_DYtauetaumu=1;

    //////////
    // muons
    //////////

    Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);

    Handle<edm::Association<reco::GenParticleCollection>> mcmapmuons;
    iEvent.getByToken(mcmapmuonToken_, mcmapmuons);

    Handle<reco::CandidateView> candmuons;
    iEvent.getByToken(candmuonToken_, candmuons);

    n_mu = 0;
    int i_mu=-1;
    for (const pat::Muon &mu : *muons) {
	i_mu++;
        if( !mu.isMediumMuon() ) continue;
	if (mu.pt()<5) continue;

	if (MC_){
           reco::GenParticleRef match = (*mcmapmuons)[candmuons->ptrAt(i_mu)];
           mu_genPart[n_mu]=-1;
	   if (match.isNonnull()){
              if (match->isPromptFinalState()) mu_genPart[n_mu]=1;
              else if (match->isDirectPromptTauDecayProductFinalState()) mu_genPart[n_mu]=15;
              else mu_genPart[n_mu]=0;
	   }
        }

        //if(fabs(mu.innerTrack()->dxy(PV.position()))>0.02) continue; //prompt
        //if(fabs(mu.innerTrack()->dz(PV.position()))>0.1) continue;
        mu_dxy[n_mu] = fabs(mu.innerTrack()->dxy(PV.position()));
	mu_dz[n_mu] = mu.innerTrack()->dz(PV.position());
        //if(!mu.passed(reco::Muon::PFIsoTight)) continue; // isolation
        mu_pt[n_mu] = mu.pt();
        mu_eta[n_mu] = mu.eta();
        mu_phi[n_mu] = mu.phi();
        mu_charge[n_mu] = mu.charge();
        mu_tight[n_mu] = mu.isTightMuon(PV);
        mu_trigger23[n_mu] = mu.triggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*");
        mu_trigger8[n_mu] = mu.triggered("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*");
        mu_triggerIsoMu24[n_mu] = mu.triggered("HLT_IsoMu24_v*");
        mu_pfiso[n_mu] = mu.passed(reco::Muon::PFIsoTight);
        mu_rawiso[n_mu] = (mu.pfIsolationR04().sumChargedHadronPt + TMath::Max(mu.pfIsolationR04().sumNeutralHadronEt + mu.pfIsolationR04().sumPhotonEt - mu.pfIsolationR04().sumPUPt/2,float(0.0)))/mu.pt();
        
        n_mu ++;
        if(n_mu==5) break;
    }

    if(n_mu<1) return;
    h_step->Fill(4);

    vector<TLorentzVector> selected_muons;
    for (unsigned int k=0; k<n_mu; ++k){
	TLorentzVector tmp_mu;
        tmp_mu.SetPtEtaPhiM(mu_pt[k],mu_eta[k],mu_phi[k],0.105);
        selected_muons.push_back(tmp_mu);
    }

    //if(mu_pfiso[0]<0.5) return; // at least 1 mu is isolated;
    //h_step->Fill(4);

    /////////////
    // electrons
    /////////////

    Handle<pat::ElectronCollection> electrons;
    iEvent.getByToken(electronToken_, electrons);

    Handle<edm::Association<reco::GenParticleCollection>> mcmapelectrons;
    iEvent.getByToken(mcmapelectronToken_, mcmapelectrons);

    Handle<reco::CandidateView> candelectrons;
    iEvent.getByToken(candelectronToken_, candelectrons);

    n_el = 0;
    int i_el=-1;
    TLorentzVector tmp_el;
    bool has_overlap=false;
    for (const pat::Electron &el : *electrons) {
        i_el++;
	if (el.pt()<10) continue;
        if (!el.electronID("mvaEleID-Fall17-iso-V2-wpLoose")) continue;
	if (fabs(el.eta())>1.442 and fabs(el.eta())<1.556) continue;
	tmp_el.SetPtEtaPhiM(el.pt(),el.eta(),el.phi(),0.0);

	has_overlap=false;
	for (unsigned int k=0; k<n_mu; ++k){
	   if (tmp_el.DeltaR(selected_muons[k])<0.3) has_overlap=true;
	}
	if (has_overlap) continue;

	
	el_genPart[n_el]=-1;
	if (MC_){
           reco::GenParticleRef match = (*mcmapelectrons)[candelectrons->ptrAt(i_el)];
	   if (match.isNonnull()){
	      if (match->isPromptFinalState() and match->pdgId()==22) el_genPart[n_el]=22;
	      else if (match->isPromptFinalState()) el_genPart[n_el]=1;
	      else if (match->isDirectPromptTauDecayProductFinalState()) el_genPart[n_el]=15;
              else el_genPart[n_el]=0;
	   }
	}

	el_dxy[n_el]=fabs(el.gsfTrack()->dxy(PV.position()));
	el_dz[n_el]=el.gsfTrack()->dz(PV.position());
        el_pt[n_el] = el.pt();
        el_eta[n_el] = el.eta();
        el_phi[n_el] = el.phi();
        el_charge[n_el] = el.charge();
	el_conversionveto[n_el]=el.passConversionVeto();
        el_losthits[n_el]=el.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
	el_chargeconsistent[n_el]=el.isGsfCtfScPixChargeConsistent();
	el_CBIDLoose[n_el]=el.electronID("cutBasedElectronID-Fall17-94X-V2-loose");
        el_CBIDMedium[n_el]=el.electronID("cutBasedElectronID-Fall17-94X-V2-medium");
        el_CBIDTight[n_el]=el.electronID("cutBasedElectronID-Fall17-94X-V2-tight");
        el_CBIDVeto[n_el]=el.electronID("cutBasedElectronID-Fall17-94X-V2-veto");
        el_MVAIDisoWP80[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wp80");
        el_MVAIDisoWP90[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wp90");
        el_MVAIDisoWPHZZ[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wpHZZ");
        el_MVAIDisoWPLoose[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wpLoose");
        el_MVAIDnoisoWP80[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wp80");
        el_MVAIDnoisoWP90[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wp90");
        el_MVAIDnoisoWPLoose[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wpLoose");

        //el_trigger[n_el] = el.triggered("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v*") or el.triggered("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v*");

        n_el ++;
        if(n_el==5) break;
    }

    if(n_el<1) return;
    h_step->Fill(5);

    h_step->Fill(6);

    //if (el_charge[0]*mu_charge[0]<0) return; // SS emu
    h_step->Fill(7);

    //////////
    // tracks
    //////////

    Handle<pat::PackedCandidateCollection> pfs;
    iEvent.getByToken(pfToken_, pfs);

    // packedGenParticles collection
    Handle<edm::View<pat::PackedGenParticle>> gp_handle;
    iEvent.getByToken( packedgenToken_, gp_handle );

    Handle<GenParticleCollection> pruned;
    iEvent.getByToken(prunedGenToken_,pruned);

    ntrk_prompt = 0;
    ntrk_nonprompt = 0;
    ntrk_all = 0;
    ntrk_HS = 0;
    ntrk_PU = 0;
    ntrk_signal=0;
    float emu_dz=(mu_dz[0]+el_dz[0])/2;
    TLorentzVector my_el; my_el.SetPtEtaPhiM(el_pt[0],el_eta[0],el_phi[0],0.);
    TLorentzVector my_mu; my_mu.SetPtEtaPhiM(mu_pt[0],mu_eta[0],mu_phi[0],0.);
    for(size_t i = 0; i < pfs->size(); i++) {

       const pat::PackedCandidate & pf = (*pfs)[i];

       bool isMatchedToGen=false;
       bool isMatchedToEM=false;
       bool isMatchedTo4L=false;

       if (pf.charge()!=0){
          TLorentzVector recotk; recotk.SetPtEtaPhiM(pf.pt(),pf.eta(),pf.phi(),0);
	  if (gp_handle.isValid()){
             for (unsigned int j = 0; j<gp_handle->size(); ++j){
                pat::PackedGenParticle const& pk = gp_handle->at(j);
                TLorentzVector genp; 
                genp.SetPtEtaPhiM(pk.pt(),pk.eta(),pk.phi(),0);
                if (recotk.DeltaR(genp)<0.1 and (fabs(recotk.Pt()-genp.Pt())/recotk.Pt())<0.5){
                   isMatchedToGen=true;
                }
             }
          }
          if (pruned.isValid()){
             for (size_t k = 0; k < pruned->size(); ++k) {
                const GenParticle &p = (*pruned)[k];
                TLorentzVector genp;
                genp.SetPtEtaPhiM(p.pt(),p.eta(),p.phi(),0);
                if (p.status()==1 and (fabs(p.pdgId())==11 or fabs(p.pdgId())==13) and recotk.DeltaR(genp)<0.1 and (fabs(recotk.Pt()-genp.Pt())/recotk.Pt())<0.5){
                   isMatchedTo4L=true;
                }
             }
          }

          if (fabs(pf.pt()-my_mu.Pt())/my_mu.Pt()<0.1 and my_mu.DeltaR(recotk)<0.002) {isMatchedToEM=true;}
          if (fabs(pf.pt()-my_el.Pt())/my_el.Pt()<0.1 and my_el.DeltaR(recotk)<0.002) {isMatchedToEM=true;}
	  //if (fabs(pf.dz(PV.position())-emu_dz)<0.05 and pf.pt()>0.5 and fabs(pf.eta())<2.5) std::cout<<isMatchedToEM<<std::endl;

          if(!pf.hasTrackDetails()) continue;
	  if (!isMatchedToEM and fabs(pf.dz(PV.position())-emu_dz)<0.05 and pf.pt()>0.5 and fabs(pf.eta())<2.5){
             if(fabs(pf.dz(PV.position())-emu_dz)<0.05 && fabs(pf.dxy(PV.position()))<0.02) ntrk_prompt++;
             if(fabs(pf.dz(PV.position())-emu_dz)<0.05 && fabs(pf.dxy(PV.position()))>0.02) ntrk_nonprompt++;
	     if (fabs(pf.dz(PV.position())-emu_dz)<0.05) ntrk_all++;
             if (fabs(pf.dz(PV.position())-emu_dz)<0.05 and isMatchedToGen) ntrk_HS++;
             if (fabs(pf.dz(PV.position())-emu_dz)<0.05 and !isMatchedToGen) ntrk_PU++;
             if (fabs(pf.dz(PV.position())-emu_dz)<0.05 and isMatchedTo4L) ntrk_signal++;
	  }
       }
    }
    //std::cout<<std::endl;

    tr->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void
SSEMAnlzr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
SSEMAnlzr::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SSEMAnlzr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SSEMAnlzr);
