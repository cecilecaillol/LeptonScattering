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
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
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

class ChargeMisidAnlzr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ChargeMisidAnlzr(const edm::ParameterSet&);
      ~ChargeMisidAnlzr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      EDGetTokenT<VertexCollection> vtxToken_;
      EDGetTokenT<pat::ElectronCollection> electronToken_;
      EDGetTokenT<TriggerResults> triggerToken_;
      EDGetTokenT<TriggerResults> metfilterToken_;
      EDGetTokenT<GenEventInfoProduct> generatorLabel_;
      EDGetTokenT<std::vector<PileupSummaryInfo>> pileupSummaryToken_;

      TTree *tr;

      bool MC_;
      int year_;
      int el_charge[2];
      float el_pt[2], el_eta[2], el_sceta[2], el_phi[2], el_dxy[2], el_dz[2], el_sip2d[2], el_sieie[2], el_hoe[2], el_eInvMinusPInv[2];
      int el_conversionveto[2], el_chargeconsistent[2], el_MVAIDisoWP80[2],el_MVAIDisoWP90[2],el_MVAIDisoWPHZZ[2],el_MVAIDisoWPLoose[2],el_MVAIDnoisoWP80[2],el_MVAIDnoisoWP90[2],el_MVAIDnoisoWPLoose[2], el_genPart[2], el_losthits[2];
      float genWeight=1.0;

      float Pileup_trueNumInteractions = -1;
      int Pileup_puNumInteractions = -1;
      
};

ChargeMisidAnlzr::ChargeMisidAnlzr(const edm::ParameterSet& iConfig)
 :
    vtxToken_(consumes<VertexCollection>(iConfig.getParameter<InputTag>("vertices"))),
    electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
    triggerToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("triggerBitsH"))),
    metfilterToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("metfilterBitsH"))),
    generatorLabel_(consumes<GenEventInfoProduct>(iConfig.getParameter<InputTag>("generatorLabel"))),
    pileupSummaryToken_(consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<InputTag>("pileupInfo")))
{

   MC_ = iConfig.getParameter<bool>("MC");
   year_ = iConfig.getParameter<int>("year");

   Service<TFileService> fs;
   tr = fs->make<TTree>("tree_misid", "");
   tr->Branch("el_pt", &el_pt, "el_pt[2]/F");
   tr->Branch("el_dxy", &el_dxy, "el_dxy[2]/F");
   tr->Branch("el_dz", &el_dz, "el_dz[2]/F");
   tr->Branch("el_eta", &el_eta, "el_eta[2]/F");
   tr->Branch("el_sceta", &el_sceta, "el_sceta[2]/F");
   tr->Branch("el_phi", &el_phi, "el_phi[2]/F");
   tr->Branch("el_charge", &el_charge, "el_charge[2]/I");
   tr->Branch("el_genPart", &el_genPart, "el_genPart[2]/I");
   tr->Branch("el_conversionveto", &el_conversionveto, "el_conversionveto[2]/I");
   tr->Branch("el_MVAIDisoWP80", &el_MVAIDisoWP80, "el_MVAIDisoWP80[2]/I");
   tr->Branch("el_MVAIDisoWP90", &el_MVAIDisoWP90, "el_MVAIDisoWP90[2]/I");
   tr->Branch("el_MVAIDisoWPHZZ", &el_MVAIDisoWPHZZ, "el_MVAIDisoWPHZZ[2]/I");
   tr->Branch("el_MVAIDisoWPLoose", &el_MVAIDisoWPLoose, "el_MVAIDisoWPLoose[2]/I");
   tr->Branch("el_MVAIDnoisoWP80", &el_MVAIDnoisoWP80, "el_MVAIDnoisoWP80[2]/I");
   tr->Branch("el_MVAIDnoisoWP90", &el_MVAIDnoisoWP90, "el_MVAIDnoisoWP90[2]/I");
   tr->Branch("el_MVAIDnoisoWPLoose", &el_MVAIDnoisoWPLoose, "el_MVAIDnoisoWPLoose[2]/I");
   tr->Branch("el_chargeconsistent", &el_chargeconsistent, "el_chargeconsistent[2]/I");
   tr->Branch("el_losthits", el_losthits, "el_losthits[2]/I");
   tr->Branch("el_sip2d", el_sip2d, "el_sip2d[2]/D");
   tr->Branch("el_hoe", el_hoe, "el_hoe[2]/D");
   tr->Branch("el_sieie", el_sieie, "el_sieie[2]/D");
   tr->Branch("el_eInvMinusPInv", el_eInvMinusPInv, "el_eInvMinusPInv[2]/D");

   tr->Branch("genWeight", &genWeight, "genWeight/F");

   tr->Branch("Pileup_trueNumInteractions", &Pileup_trueNumInteractions, "Pileup_trueNumInteractions/F");
   tr->Branch("Pileup_puNumInteractions", &Pileup_puNumInteractions, "Pileup_puNumInteractions/I");

}


ChargeMisidAnlzr::~ChargeMisidAnlzr()
{

}

void
ChargeMisidAnlzr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    if (MC_){
       edm::Handle<GenEventInfoProduct> genEventInfoHandle;
       iEvent.getByToken(generatorLabel_, genEventInfoHandle);
       if (genEventInfoHandle.isValid()) {
         if (genEventInfoHandle->hasBinningValues())
         genWeight = genEventInfoHandle->weight();
       }
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

    int hlt_2018 = 0;
    int hlt_2017 = 0;
    int hlt_2016 = 0;

    Handle<TriggerResults> triggerBitsH;
    iEvent.getByToken(triggerToken_, triggerBitsH);

    const TriggerNames &triggerNames = iEvent.triggerNames( *triggerBitsH );
    for (size_t i_hlt = 0; i_hlt != triggerBitsH->size(); ++i_hlt)
    {
      string hltName = triggerNames.triggerName(i_hlt);

      if(!(hltName.find("HLT_Ele32_WPTight_Gsf_v") == string::npos)){ if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_2018 = 1;}
      if(!(hltName.find("HLT_Ele32_WPTight_Gsf_v") == string::npos)){ if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_2017 = 1;}
      if(!(hltName.find("HLT_Ele25_eta2p1_WPTight_Gsf_v") == string::npos)){ if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_2016 = 1;}
    }

    if (year_==2018 and hlt_2018<0.5) return;
    if (year_==2017 and hlt_2017<0.5) return;
    if (year_==2016 and hlt_2016<0.5) return;

    //////////
    // PV
    //////////

    Handle<VertexCollection> vertices;
    iEvent.getByToken(vtxToken_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    const reco::Vertex &PV = vertices->front();

    /////////////
    // electrons
    /////////////

    Handle<pat::ElectronCollection> electrons;
    iEvent.getByToken(electronToken_, electrons);

    int n_el = 0;
    int i_el=-1;
    TLorentzVector tmp_el;
    for (const pat::Electron &el : *electrons) {
	i_el++;

        if (el.pt()<7) continue;
        if (!el.electronID("mvaEleID-Fall17-iso-V2-wpLoose")) continue;
        if (fabs(el.eta())>1.442 and fabs(el.eta())<1.556) continue;
        if (el.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS)>1) continue; //at most one missing hit 

        el_dxy[n_el]=fabs(el.gsfTrack()->dxy(PV.position()));
        el_dz[n_el]=el.gsfTrack()->dz(PV.position());
        el_sip2d[n_el]=fabs(el.dB(pat::Electron::BS2D)/el.edB(pat::Electron::BS2D));
        el_pt[n_el] = el.pt();
        el_eta[n_el] = el.eta();
        el_sceta[n_el] = el.superCluster()->eta();
        el_phi[n_el] = el.phi();
        el_charge[n_el] = el.charge();
        el_conversionveto[n_el]=el.passConversionVeto();
        el_losthits[n_el]=el.gsfTrack()->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS);
        el_chargeconsistent[n_el]=el.isGsfCtfScPixChargeConsistent();
        el_MVAIDisoWP80[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wp80");
        el_MVAIDisoWP90[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wp90");
        el_MVAIDisoWPHZZ[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wpHZZ");
        el_MVAIDisoWPLoose[n_el]=el.electronID("mvaEleID-Fall17-iso-V2-wpLoose");
        el_MVAIDnoisoWP80[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wp80");
        el_MVAIDnoisoWP90[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wp90");
        el_MVAIDnoisoWPLoose[n_el]=el.electronID("mvaEleID-Fall17-noIso-V2-wpLoose");
        el_sieie[n_el]=el.full5x5_sigmaIetaIeta();
        el_eInvMinusPInv[n_el] = (1-el.eSuperClusterOverP())/el.ecalEnergy();
        el_hoe[n_el] = el.hadronicOverEm();

        n_el ++;
        if(n_el==2) break;
    }

    if(n_el!=2) return;

    TLorentzVector ele1;
    ele1.SetPtEtaPhiM(el_pt[0], el_eta[0], el_phi[0], 0.);
    TLorentzVector ele2;
    ele2.SetPtEtaPhiM(el_pt[1], el_eta[1], el_phi[1], 0.);
    if ((ele1+ele2).M()<50 or (ele1+ele2).M()>150) return;

    tr->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void
ChargeMisidAnlzr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
ChargeMisidAnlzr::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ChargeMisidAnlzr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(ChargeMisidAnlzr);
