// -*- C++ -*-
//
// Package:    MyAnalyzer/FRmuAnlzr
// Class:      FRmuAnlzr
//
/**\class FRmuAnlzr FRmuAnlzr.cc MyAnalyzer/FRmuAnlzr/plugins/FRmuAnlzr.cc

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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

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

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


class FRmuAnlzr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit FRmuAnlzr(const edm::ParameterSet&);
      ~FRmuAnlzr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      EDGetTokenT<VertexCollection> vtxToken_;
      EDGetTokenT<pat::MuonCollection> muonToken_;
      EDGetTokenT<edm::Association<GenParticleCollection>> mcmapmuonToken_;
      EDGetTokenT<reco::CandidateView> candmuonToken_;
      EDGetTokenT<pat::ElectronCollection> electronToken_;
      EDGetTokenT<edm::Association<GenParticleCollection>> mcmapelectronToken_;
      EDGetTokenT<reco::CandidateView> candelectronToken_;
      EDGetTokenT<pat::PackedCandidateCollection> pfToken_;
      EDGetTokenT<GenParticleCollection> prunedGenToken_;
      EDGetTokenT<TriggerResults> triggerToken_;
      EDGetTokenT<TriggerResults> metfilterToken_;
      EDGetTokenT<BeamSpot> bsToken_;
      EDGetTokenT<GenEventInfoProduct> generatorLabel_;
      EDGetTokenT<std::vector<PileupSummaryInfo>> pileupSummaryToken_;

      TTree *tr;
      TH1F *h_step;

      bool MC_;
      int n_mu, n_el, mu_charge[5], el_charge[5], ntrk_prompt, ntrk_nonprompt;
      float mu_pt[5], mu_eta[5], mu_phi[5], mu_dxy[5], mu_dz[5], mu_rawiso[5];
      int mu_pfiso[5], mu_trigger[5], mu_genPart[5];
      float el_pt[5], el_eta[5], el_phi[5], el_dxy[5], el_dz[5];
      int el_conversionveto[5], el_chargeconsistent[5], el_CBIDLoose[5],el_CBIDMedium[5], el_CBIDTight[5],el_CBIDVeto[5],el_MVAIDisoWP80[5],el_MVAIDisoWP90[5],el_MVAIDisoWPHZZ[5],el_MVAIDisoWPLoose[5],el_MVAIDnoisoWP80[5],el_MVAIDnoisoWP90[5],el_MVAIDnoisoWPLoose[5], el_genPart[5];
      float genWeight=1.0;

      float Pileup_trueNumInteractions = -1;
      int Pileup_puNumInteractions = -1;
      
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
FRmuAnlzr::FRmuAnlzr(const edm::ParameterSet& iConfig)
 :
    vtxToken_(consumes<VertexCollection>(iConfig.getParameter<InputTag>("vertices"))),
    muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
    mcmapmuonToken_(consumes<edm::Association<GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("mcmapmuons"))),
    candmuonToken_(consumes<reco::CandidateView>(iConfig.getParameter<edm::InputTag>("muons"))),
    electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
    mcmapelectronToken_(consumes<edm::Association<GenParticleCollection>>(iConfig.getParameter<edm::InputTag>("mcmapelectrons"))),
    candelectronToken_(consumes<reco::CandidateView>(iConfig.getParameter<edm::InputTag>("electrons"))),
    pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
    prunedGenToken_(consumes<GenParticleCollection>(iConfig.getParameter<InputTag>("pruned"))),
    triggerToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("triggerBitsH"))),
    metfilterToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("metfilterBitsH"))),
    bsToken_(consumes<BeamSpot>(iConfig.getParameter<InputTag>("beamSpotHandle"))),
    generatorLabel_(consumes<GenEventInfoProduct>(iConfig.getParameter<InputTag>("generatorLabel"))),
    pileupSummaryToken_(consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<InputTag>("pileupInfo")))
{
   //now do what ever initialization is needed

   MC_ = iConfig.getParameter<bool>("MC");

   Service<TFileService> fs;
   h_step = fs->make<TH1F>("step", "", 10, 0, 10);
   tr = fs->make<TTree>("data", "");
   tr->Branch("n_mu", &n_mu, "n_mu/I");
   tr->Branch("mu_pt", &mu_pt, "mu_pt[n_mu]/F");
   tr->Branch("mu_eta", &mu_eta, "mu_eta[n_mu]/F");
   tr->Branch("mu_phi", &mu_phi, "mu_phi[n_mu]/F");
   tr->Branch("mu_charge", &mu_charge, "mu_charge[n_mu]/I");
   tr->Branch("mu_genPart", &mu_genPart, "mu_genPart[n_mu]/I");
   tr->Branch("mu_pfiso", &mu_pfiso, "mu_pfiso[n_mu]/I");
   tr->Branch("mu_trigger", &mu_trigger, "mu_trigger[n_mu]/I");
   tr->Branch("mu_rawiso", &mu_rawiso, "mu_rawiso[n_mu]/F");
   tr->Branch("mu_dxy", &mu_dxy, "mu_dxy[n_mu]/F");
   tr->Branch("mu_dz", &mu_dz, "mu_dz[n_mu]/F");

   tr->Branch("n_el", &n_el, "n_el/I");
   tr->Branch("el_pt", &el_pt, "el_pt[n_el]/F");
   tr->Branch("el_dxy", &el_dxy, "el_dxy[n_el]/F");
   tr->Branch("el_dz", &el_dz, "el_dz[n_el]/F");
   tr->Branch("el_eta", &el_eta, "el_eta[n_el]/F");
   tr->Branch("el_phi", &el_phi, "el_phi[n_el]/F");
   tr->Branch("el_charge", &el_charge, "el_charge[n_el]/I");
   tr->Branch("el_genPart", &el_genPart, "el_genPart[n_el]/I");
   tr->Branch("el_conversionveto", &el_conversionveto, "el_conversionveto[n_el]/I");
   tr->Branch("el_CBIDLoose", &el_CBIDLoose, "el_CBIDLoose[n_el]/I");
   tr->Branch("el_CBIDMedium", &el_CBIDMedium, "el_CBIDMedium[n_el]/I");
   tr->Branch("el_CBIDTight", &el_CBIDTight, "el_CBIDTight[n_el]/I");
   tr->Branch("el_CBIDVeto", &el_CBIDVeto, "el_CBIDVeto[n_el]/I");
   tr->Branch("el_MVAIDisoWP80", &el_MVAIDisoWP80, "el_MVAIDisoWP80[n_el]/I");
   tr->Branch("el_MVAIDisoWP90", &el_MVAIDisoWP90, "el_MVAIDisoWP90[n_el]/I");
   tr->Branch("el_MVAIDisoWPHZZ", &el_MVAIDisoWPHZZ, "el_MVAIDisoWPHZZ[n_el]/I");
   tr->Branch("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose, "el_MVAIDisoWPLoose[n_el]/I");
   tr->Branch("el_MVAIDnoisoWP80", &el_MVAIDnoisoWP80, "el_MVAIDnoisoWP80[n_el]/I");
   tr->Branch("el_MVAIDnoisoWP90", &el_MVAIDnoisoWP90, "el_MVAIDnoisoWP90[n_el]/I");
   tr->Branch("el_MVAIDnoisoWPLoose", &el_MVAIDnoisoWPLoose, "el_MVAIDnoisoWPLoose[n_el]/I");
   tr->Branch("el_chargeconsistent", &el_chargeconsistent, "el_chargeconsistent[n_el]/I");

   tr->Branch("ntrk_prompt", &ntrk_prompt, "ntrk_prompt/I");
   tr->Branch("ntrk_nonprompt", &ntrk_nonprompt, "ntrk_nonprompt/I");
   tr->Branch("genWeight", &genWeight, "genWeight/F");

   tr->Branch("Pileup_trueNumInteractions", &Pileup_trueNumInteractions, "Pileup_trueNumInteractions/F");
   tr->Branch("Pileup_puNumInteractions", &Pileup_puNumInteractions, "Pileup_puNumInteractions/I");

}


FRmuAnlzr::~FRmuAnlzr()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
FRmuAnlzr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    h_step->Fill(0);

    if (MC_){
       edm::Handle<GenEventInfoProduct> genEventInfoHandle;
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
    bool Flag_ecalBadCalibFilter=0;

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

    if (!Flag_goodVertices or !Flag_globalSuperTightHalo2016Filter or !Flag_HBHENoiseFilter or !Flag_HBHENoiseIsoFilter or !Flag_EcalDeadCellTriggerPrimitiveFilter or !Flag_BadPFMuonFilter or !Flag_BadPFMuonDzFilter or !Flag_eeBadScFilter or !Flag_ecalBadCalibFilter) return;

    //FIXME in 2016 UL dont apply the last filter


    //////////
    // HLT
    //////////

    int hlt_el32 = 0;

    Handle<TriggerResults> triggerBitsH;
    iEvent.getByToken(triggerToken_, triggerBitsH);

    const TriggerNames &triggerNames = iEvent.triggerNames( *triggerBitsH );
    for (size_t i_hlt = 0; i_hlt != triggerBitsH->size(); ++i_hlt)
    {
      string hltName = triggerNames.triggerName(i_hlt);

      if(!(hltName.find("HLT_Ele32_WPTight_Gsf_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_el32 = 1;
      }
    }

    if(hlt_el32<0.5) return;
    h_step->Fill(2);


    //////////
    // PV
    //////////

    Handle<VertexCollection> vertices;
    iEvent.getByToken(vtxToken_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    const reco::Vertex &PV = vertices->front();

    BeamSpot bs;
    Handle<BeamSpot> beamSpotHandle;
    iEvent.getByToken(bsToken_, beamSpotHandle);
    bs = *beamSpotHandle;

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


    //////////
    // muons
    //////////

    Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);

    Handle<edm::Association<GenParticleCollection>> mcmapmuons;
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
	//std::cout<<mcmapmuons.isValid()<<" "<<i_mu<<" "<<candmuons->size()<<std::endl;
           //if (mcmapmuons.isValid()) {
              GenParticleRef match = (*mcmapmuons)[candmuons->ptrAt(i_mu)];
	      //std::cout<<"passed muon"<<std::endl;
	      if (match.isNonnull()){
                 if (match->isPromptFinalState()) mu_genPart[n_mu]=1;
                 else if (match->isDirectPromptTauDecayProductFinalState()) mu_genPart[n_mu]=15;
                 else mu_genPart[n_mu]=0;
	      }
              //std::cout<<"passed muon v2"<<std::endl;
	   //}
        }

        mu_dxy[n_mu] = fabs(mu.innerTrack()->dxy(PV.position()));
        mu_dz[n_mu] = mu.innerTrack()->dz(PV.position());
        mu_pt[n_mu] = mu.pt();
        mu_eta[n_mu] = mu.eta();
        mu_phi[n_mu] = mu.phi();
        mu_charge[n_mu] = mu.charge();
        mu_trigger[n_mu] = mu.triggered("HLT_IsoMu24_v*");
        mu_pfiso[n_mu] = mu.passed(reco::Muon::PFIsoTight);
        mu_rawiso[n_mu] = (mu.pfIsolationR04().sumChargedHadronPt + TMath::Max(mu.pfIsolationR04().sumNeutralHadronEt + mu.pfIsolationR04().sumPhotonEt - mu.pfIsolationR04().sumPUPt/2,float(0.0)))/mu.pt();

        n_mu ++;
        if(n_mu==5) break;
    }

    if(n_mu<1) return;

    /////////////
    // electrons
    /////////////

    Handle<pat::ElectronCollection> electrons;
    iEvent.getByToken(electronToken_, electrons);

    Handle<edm::Association<GenParticleCollection>> mcmapelectrons;
    iEvent.getByToken(mcmapelectronToken_, mcmapelectrons);

    Handle<reco::CandidateView> candelectrons;
    iEvent.getByToken(candelectronToken_, candelectrons);

    n_el = 0;
    int i_el=-1;

    for (const pat::Electron &el : *electrons) {
	i_el++;
	if (el.pt()<10) continue;
	if (!el.electronID("mvaEleID-Fall17-iso-V2-wpLoose")) continue;

        if (MC_){
        //std::cout<<"electrons "<<mcmapelectrons.isValid()<<" "<<i_el<<" "<<candelectrons->size()<<std::endl;
           //if (mcmapelectrons.isValid()) {
              GenParticleRef match = (*mcmapelectrons)[candelectrons->ptrAt(i_el)];
	      //std::cout<<"passed electrons"<<std::endl;
	      if (match.isNonnull()){
                 if (match->isPromptFinalState() and match->pdgId()==22) el_genPart[n_el]=22;
                 else if (match->isPromptFinalState()) el_genPart[n_el]=1;
                 else if (match->isDirectPromptTauDecayProductFinalState()) el_genPart[n_el]=15;
                 else el_genPart[n_el]=0;
	      }
	   //}
        }

	el_dxy[n_el]=fabs(el.gsfTrack()->dxy(PV.position()));
	el_dz[n_el]=el.gsfTrack()->dz(PV.position());
        el_pt[n_el] = el.pt();
        el_eta[n_el] = el.eta();
        el_phi[n_el] = el.phi();
        el_charge[n_el] = el.charge();
	el_conversionveto[n_el]=el.passConversionVeto();
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

        n_el ++;
        if(n_el==5) break;
    }
    if(n_el<2) return;

    int is_Z=false;

    for (int i=0; i<n_el; ++i){
       TLorentzVector el1;
       el1.SetPtEtaPhiM(el_pt[i],el_eta[i],el_phi[i],0.105);
       for (int j=i+1; j<n_el; ++j){
          TLorentzVector el2;
          el2.SetPtEtaPhiM(el_pt[j],el_eta[j],el_phi[j],0.105);
          if ((el_pt[j]>32 or el_pt[i]>32) and fabs((el1+el2).M()-90)<15 and el_charge[i]*el_charge[j]<0 and el_MVAIDisoWP80[i] and el_MVAIDisoWP80[j]) is_Z=true;
       }
    }
    if (!is_Z) return;

    //////////
    // tracks
    //////////

    Handle<pat::PackedCandidateCollection> pfs;
    iEvent.getByToken(pfToken_, pfs);

    ntrk_prompt = 0;
    ntrk_nonprompt = 0;

    for(size_t i = 0; i < pfs->size(); i++) {
       const pat::PackedCandidate & pf = (*pfs)[i];
       if(!pf.hasTrackDetails()) continue;
       if(fabs(pf.dz(PV.position()))<0.05 && fabs(pf.dxy(PV.position()))<0.02) ntrk_prompt++;
       if(fabs(pf.dz(PV.position()))<0.05 && fabs(pf.dxy(PV.position()))>0.02) ntrk_nonprompt++;
    }

    tr->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void
FRmuAnlzr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
FRmuAnlzr::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
FRmuAnlzr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(FRmuAnlzr);
