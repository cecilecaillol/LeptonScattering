// -*- C++ -*-
//
// Package:    MyAnalyzer/SSMMAnlzr
// Class:      SSMMAnlzr
//
/**\class SSMMAnlzr SSMMAnlzr.cc MyAnalyzer/SSMMAnlzr/plugins/SSMMAnlzr.cc

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
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

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


class SSMMAnlzr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit SSMMAnlzr(const edm::ParameterSet&);
      ~SSMMAnlzr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      EDGetTokenT<VertexCollection> vtxToken_;
      EDGetTokenT<pat::MuonCollection> muonToken_;
      EDGetTokenT<pat::PackedCandidateCollection> pfToken_;
      EDGetTokenT<GenParticleCollection> prunedGenToken_;
      EDGetTokenT<TriggerResults> triggerToken_;
      EDGetTokenT<BeamSpot> bsToken_;

      TTree *tr;
      TH1F *h_step;

      bool MC_;
      size_t n_mu, n_pv, pv_ntrk2, pv_ntrk3, hlt_mu17_mu8, hlt_mu17_mu8_mass3p8, pv_nmu,
	     hlt_tm_12_10_5, hlt_tm_10_5_5, hlt_tm_5_3_3_dca, hlt_tm_5_3_3_dz, ntrk_prompt, ntrk_nonprompt;
         //hlt_el23_el12, hlt_mu23_el12, hlt_mu8_el23;
      double mu_pt[10], mu_eta[10], mu_phi[10], mu_charge[10], mu_tight[10], mu_frompv[10], mu_trigger[10], mu_pfiso[10],
	     pv_d0, pv_dz, pv_ndof, pv_chi2,
         pt_2mu, pt_3mu_s, pt_3mu_v, mass_2mu, dphi_2mu, pv_charge, pt_vector, pt_scalar; // deta_trk; // pt2trk_1mm, pt2trk_3mm;

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
SSMMAnlzr::SSMMAnlzr(const edm::ParameterSet& iConfig)
 :
    vtxToken_(consumes<VertexCollection>(iConfig.getParameter<InputTag>("vertices"))),
    muonToken_(consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muons"))),
    pfToken_(consumes<pat::PackedCandidateCollection>(iConfig.getParameter<edm::InputTag>("pfCands"))),
    prunedGenToken_(consumes<GenParticleCollection>(iConfig.getParameter<InputTag>("pruned"))),
    triggerToken_(consumes<TriggerResults>(iConfig.getParameter<InputTag>("triggerBitsH"))),
    bsToken_(consumes<BeamSpot>(iConfig.getParameter<InputTag>("beamSpotHandle")))
{
   //now do what ever initialization is needed

   MC_ = iConfig.getParameter<bool>("MC");

   Service<TFileService> fs;
   h_step = fs->make<TH1F>("step", "", 7, 0, 7);
   tr = fs->make<TTree>("data", "");
   tr->Branch("n_mu", &n_mu, "n_mu/I");
   tr->Branch("mu_pt", mu_pt, "mu_pt[n_mu]/D");
   tr->Branch("mu_eta", mu_eta, "mu_eta[n_mu]/D");
   tr->Branch("mu_phi", mu_phi, "mu_phi[n_mu]/D");
   tr->Branch("mu_charge", mu_charge, "mu_charge[n_mu]/D");
   tr->Branch("mu_tight", mu_tight, "mu_tight[n_mu]/D");
   tr->Branch("mu_frompv", mu_frompv, "mu_frompv[n_mu]/D");
   tr->Branch("mu_trigger", mu_trigger, "mu_trigger[n_mu]/D");
   tr->Branch("mu_pfiso", mu_pfiso, "mu_pfiso[n_mu]/D");
   tr->Branch("pt_2mu", &pt_2mu, "pt_2mu/D");
   tr->Branch("pt_3mu_s", &pt_3mu_s, "pt_3mu_s/D");
   tr->Branch("pt_3mu_v", &pt_3mu_v, "pt_3mu_v/D");
   tr->Branch("dphi_2mu", &dphi_2mu, "dphi_2mu/D");
   tr->Branch("mass_2mu", &mass_2mu, "mass_2mu/D");
   tr->Branch("n_pv", &n_pv, "n_pv/I");
   tr->Branch("pv_ndof", &pv_ndof, "pv_ndof/D");
   tr->Branch("pv_chi2", &pv_chi2, "pv_chi2/D");
   tr->Branch("pv_d0", &pv_d0, "pv_d0/D");
   tr->Branch("pv_dz", &pv_dz, "pv_dz/D");
   tr->Branch("pv_ntrk2", &pv_ntrk2, "pv_ntrk2/I");
   tr->Branch("pv_ntrk3", &pv_ntrk3, "pv_ntrk3/I");
   tr->Branch("ntrk_prompt", &ntrk_prompt, "ntrk_prompt/I");
   tr->Branch("ntrk_nonprompt", &ntrk_nonprompt, "ntrk_nonprompt/I");
   tr->Branch("pv_nmu", &pv_nmu, "pv_nmu/I");
   tr->Branch("pv_charge", &pv_charge, "pv_charge/D");
   tr->Branch("pt_vector", &pt_vector, "pt_vector/D");
   tr->Branch("pt_scalar", &pt_scalar, "pt_scalar/D");
   tr->Branch("hlt_mu17_mu8", &hlt_mu17_mu8, "hlt_mu17_mu8/I");
   tr->Branch("hlt_mu17_mu8_mass3p8", &hlt_mu17_mu8_mass3p8, "hlt_mu17_mu8_mass3p8/I");
   tr->Branch("hlt_tm_10_5_5", &hlt_tm_10_5_5, "hlt_tm_10_5_5/I");
   tr->Branch("hlt_tm_12_10_5", &hlt_tm_12_10_5, "hlt_tm_12_10_5/I");
   tr->Branch("hlt_tm_5_3_3_dca", &hlt_tm_5_3_3_dca, "hlt_tm_5_3_3_dca/I");
   tr->Branch("hlt_tm_5_3_3_dz", &hlt_tm_5_3_3_dz, "hlt_tm_5_3_3_dz/I");
   //tr->Branch("hlt_el23_el12", &hlt_el23_el12, "hlt_el23_el12/I");
   //tr->Branch("hlt_mu23_el12", &hlt_mu23_el12, "hlt_mu23_el12/I");
   //tr->Branch("hlt_mu8_el23", &hlt_mu8_el23, "hlt_mu8_el23/I");


}


SSMMAnlzr::~SSMMAnlzr()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SSMMAnlzr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    h_step->Fill(0);

    //////////
    // HLT
    //////////
    hlt_mu17_mu8 = 0;
    hlt_mu17_mu8_mass3p8 = 0;
    hlt_tm_10_5_5 = 0;
    hlt_tm_12_10_5 = 0;
    hlt_tm_5_3_3_dca = 0;
    hlt_tm_5_3_3_dz = 0;
    //hlt_el23_el12 = 0;
    //hlt_mu8_el23 = 0;
    //hlt_mu23_el12 = 0;

    Handle<TriggerResults> triggerBitsH;
    iEvent.getByToken(triggerToken_, triggerBitsH);

    const TriggerNames &triggerNames = iEvent.triggerNames( *triggerBitsH );
    for (size_t i_hlt = 0; i_hlt != triggerBitsH->size(); ++i_hlt)
    {
      string hltName = triggerNames.triggerName(i_hlt);

      if(!(hltName.find("HLT_TripleMu_5_3_3_Mass3p8_DCA_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tm_5_3_3_dca = 1;
      }
      if(!(hltName.find("HLT_TripleMu_5_3_3_Mass3p8_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tm_5_3_3_dz = 1;
      }
      if(!(hltName.find("HLT_TripleMu_12_10_5_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tm_12_10_5 = 1;
      }
      if(!(hltName.find("HLT_TripleMu_10_5_5_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_tm_10_5_5 = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8 = 1;
      }
      if(!(hltName.find("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu17_mu8_mass3p8 = 1;
      }
      //if(!(hltName.find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_el23_el12 = 1;
      //}
      //if(!(hltName.find("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu23_el12 = 1;
      //}
      //if(!(hltName.find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v") == string::npos)){      if( triggerBitsH->wasrun(i_hlt) && !triggerBitsH->error(i_hlt) && triggerBitsH->accept(i_hlt )) hlt_mu8_el23 = 1;
      //}

    }

    if(!MC_ && hlt_mu17_mu8<0.5) return;
    h_step->Fill(1);


    //////////
    // PV
    //////////

    Handle<VertexCollection> vertices;
    iEvent.getByToken(vtxToken_, vertices);
    if (vertices->empty()) return; // skip the event if no PV found
    h_step->Fill(2);
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


    //////////
    // muons
    //////////

    TLorentzVector mu1, mu2, mu3;
    Handle<pat::MuonCollection> muons;
    iEvent.getByToken(muonToken_, muons);
    n_mu = 0;
    //double dz_mu1 = 999, dz_mu2 = 999;
    for (const pat::Muon &mu : *muons) {
        if( !mu.isMediumMuon() ) continue;
        if(fabs(mu.innerTrack()->dxy(PV.position()))>0.02) continue; //prompt
        if(fabs(mu.innerTrack()->dz(PV.position()))>0.1) continue;
        //if(!mu.passed(reco::Muon::PFIsoTight)) continue; // isolation
        mu_pt[n_mu] = mu.pt();
        mu_eta[n_mu] = mu.eta();
        mu_phi[n_mu] = mu.phi();
        mu_charge[n_mu] = mu.charge();
        mu_tight[n_mu] = mu.isTightMuon(PV);
        mu_trigger[n_mu] = mu.triggered("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v*");
        mu_pfiso[n_mu] = mu.passed(reco::Muon::PFIsoTight);
        //mu_frompv[n_mu] = mu.fromPV();
        
        if(n_mu==0) mu1.SetPtEtaPhiM(mu.pt(), mu.eta(), mu.phi(), mu.mass());
        if(n_mu==1) mu2.SetPtEtaPhiM(mu.pt(), mu.eta(), mu.phi(), mu.mass());
        if(n_mu==2) mu3.SetPtEtaPhiM(mu.pt(), mu.eta(), mu.phi(), mu.mass());

        n_mu ++;
        if(n_mu==10) break;
      
    }
     
    if(n_mu<2) return;
    h_step->Fill(3);

    if(mu_pfiso[0]<0.5 && mu_pfiso[1]<0.5) return; // at least 1 mu is isolated;
    h_step->Fill(4);

    //double dz_2mu = 0.5*(dz_mu1+dz_mu2);
    //cout<<endl<<dz_mu1<<"    "<<dz_mu2<<"    "<<dz_2mu;
    pt_2mu = (mu1+mu2).Pt();
    if(n_mu==2) {pt_3mu_v = pt_2mu; pt_3mu_s = mu1.Pt() + mu2.Pt();}
    else {pt_3mu_v = (mu1+mu2+mu3).Pt(); pt_3mu_s = mu1.Pt() + mu2.Pt() + mu3.Pt();}

    dphi_2mu = deltaPhi(mu1.Phi(), mu2.Phi());
    mass_2mu = (mu1+mu2).M();
    double r = gRandom->Rndm();
    if(!MC_ && mu_charge[0]!=mu_charge[1] && fabs(mass_2mu-90)<30 && r>0.1) return; // pre-scale by 10 Z->2mu events
    h_step->Fill(5);
    

    //////////
    // tracks
    //////////

    Handle<pat::PackedCandidateCollection> pfs;
    iEvent.getByToken(pfToken_, pfs);

    pv_ntrk3 = 0;
    pv_ntrk2 = 0;
    ntrk_prompt = 0;
    ntrk_nonprompt = 0;
    //pt2trk_3mm = 0;
    //deta_trk = 0;
    //double ptmax_trk = 0;
    for(size_t i = 0; i < pfs->size(); i++) {

       const pat::PackedCandidate & pf = (*pfs)[i];
       if(!pf.hasTrackDetails()) continue;
       if(pf.fromPV()==2) pv_ntrk2 ++;
       if(pf.fromPV()==3) pv_ntrk3 ++;
       if(fabs(pf.dz(PV.position()))<0.1 && fabs(pf.dxy(PV.position()))<0.02) ntrk_prompt++;
       if(fabs(pf.dz(PV.position()))<0.1 && fabs(pf.dxy(PV.position()))>0.02) ntrk_nonprompt++;
       //if(abs(pf.pdgId())==211 && pf.pt()>ptmax_trk) {
       //  ptmax_trk = pf.pt();
       //  deta_trk=fabs(pf.eta()-mu1.Eta());  
       //}
       //if(fabs(pf.dz()-dz_2mu)<0.1) pt2trk_1mm += pf.pt()*pf.pt();
       //if(fabs(pf.dz()-dz_2mu)<0.3) pt2trk_3mm += pf.pt()*pf.pt();

       for(size_t j = 0; j < n_mu; j++) {
          if(fabs(pf.pdgId())==13 && fabs(pf.pt()-mu_pt[j])/pf.pt()<0.1
            && deltaR(mu_eta[j], mu_phi[j], pf.eta(), pf.phi())<0.03) {
            mu_frompv[j] = pf.fromPV();
            //cout<<"    "<<pf.dz();
          }
       }

    }


    // build the vector sum pT, number of pv3 mu, and sum charge
    // not very useful
    pv_nmu = 0;
    pv_charge = 0;
    double pv_px = 0; double pv_py = 0;
    pt_scalar = 0;
    for(size_t j = 0; j < n_mu; j++) {
       if(mu_frompv[j] != 3) continue; 
       pv_nmu ++;
       pv_charge += mu_charge[j];
       pt_scalar += mu_pt[j];
       pv_px += mu_pt[j]*cos(mu_phi[j]);
       pv_py += mu_pt[j]*sin(mu_phi[j]);
    }
    pt_vector = sqrt(pv_px*pv_px + pv_py*pv_py);


    tr->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void
SSMMAnlzr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
SSMMAnlzr::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SSMMAnlzr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(SSMMAnlzr);
