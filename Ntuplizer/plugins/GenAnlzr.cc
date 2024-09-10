// -*- C++ -*-
//
// Package:    MyAnalyzer/GenAnlzr
// Class:      GenAnlzr
//
/**\class GenAnlzr GenAnlzr.cc MyAnalyzer/GenAnlzr/plugins/GenAnlzr.cc

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
#include "DataFormats/Candidate/interface/Candidate.h"

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


class GenAnlzr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GenAnlzr(const edm::ParameterSet&);
      ~GenAnlzr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      EDGetTokenT<GenParticleCollection> prunedGenToken_;

      bool MC_;

      TH1F *h_step;

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
GenAnlzr::GenAnlzr(const edm::ParameterSet& iConfig)
 :
    prunedGenToken_(consumes<GenParticleCollection>(iConfig.getParameter<InputTag>("pruned")))
{
   //now do what ever initialization is needed

   MC_ = iConfig.getParameter<bool>("MC");

   Service<TFileService> fs;
   h_step = fs->make<TH1F>("step", "", 10, 0, 10);


}


GenAnlzr::~GenAnlzr()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenAnlzr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

    TLorentzVector lep1; lep1.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector lep2; lep2.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector lep3; lep3.SetPtEtaPhiM(0,0,0,0);
    TLorentzVector lep4; lep4.SetPtEtaPhiM(0,0,0,0);

    int pdg1=0; int pdg2=0; int pdg3=0; int pdg4=0;

    Handle<GenParticleCollection> pruned;
    iEvent.getByToken(prunedGenToken_,pruned);
    for (size_t i = 0; i < pruned->size(); ++i) {
        const GenParticle &p = (*pruned)[i];
        const Candidate * mom = p.mother();
        //if(fabs(p.pdgId())==24 && p.numberOfDaughters()>1 ) 
        if (p.status()==1 and (fabs(p.pdgId())==11 or fabs(p.pdgId())==13)) cout<<p.pdgId()<<"    "<<p.pt()<<"    "<<p.eta()<<" "<<p.phi()<<" "<<mom->pdgId()<<endl;
	if (fabs(p.pdgId())==11 or fabs(p.pdgId())==13){
	   if (lep1.Pt()==0){ lep1.SetPtEtaPhiM(p.pt(),p.eta(),p.phi(),p.mass()); pdg1=p.pdgId();}
	   else if (lep2.Pt()==0){ lep2.SetPtEtaPhiM(p.pt(),p.eta(),p.phi(),p.mass()); pdg2=p.pdgId();}
           else if (lep3.Pt()==0){ lep3.SetPtEtaPhiM(p.pt(),p.eta(),p.phi(),p.mass()); pdg3=p.pdgId();}
           else if (lep4.Pt()==0){ lep4.SetPtEtaPhiM(p.pt(),p.eta(),p.phi(),p.mass()); pdg4=p.pdgId();}
        }
    }
    cout<<endl;

    h_step->Fill(0.5);
    if (fabs(pdg1)==11 and fabs(pdg2)==11)  h_step->Fill(1.5);
    else if (fabs(pdg1)==13 and fabs(pdg2)==13) h_step->Fill(2.5);
    else if (fabs(pdg1)+fabs(pdg2)==24) h_step->Fill(3.5);
    if (fabs(pdg1+pdg2)==24) h_step->Fill(4.5);
    if (fabs(pdg1+pdg2)==24 and ((fabs(pdg1)==11 and fabs(pdg2)==13 and lep1.Pt()>13 and lep2.Pt()>9 and (lep1.Pt()>24 or lep2.Pt()>24) and fabs(lep1.Eta())<2.5 and fabs(lep1.Eta())<2.4) or 
        (fabs(pdg1)==13 and fabs(pdg2)==11 and lep1.Pt()>9 and lep2.Pt()>13 and (lep1.Pt()>24 or lep2.Pt()>24) and fabs(lep1.Eta())<2.4 and fabs(lep1.Eta())<2.5)))
        h_step->Fill(5.5);
    if ((fabs(pdg1)==11 and fabs(pdg2)==11 and fabs(pdg3)==13 and fabs(pdg4)==13) or (fabs(pdg1)==11 and fabs(pdg2)==13 and fabs(pdg3)==11 and fabs(pdg4)==13) or (fabs(pdg1)==11 and fabs(pdg2)==13 and fabs(pdg3)==13 and fabs(pdg4)==11) or (fabs(pdg1)==13 and fabs(pdg2)==13 and fabs(pdg3)==11 and fabs(pdg4)==11) or (fabs(pdg1)==13 and fabs(pdg2)==11 and fabs(pdg3)==13 and fabs(pdg4)==11) or (fabs(pdg1)==13 and fabs(pdg2)==11 and fabs(pdg3)==11 and fabs(pdg4)==13)) h_step->Fill(6.5);
    if (pdg3==1000 or pdg4==1000) h_step->Fill(10.5);

   
}


// ------------ method called once each job just before starting event loop  ------------
void
GenAnlzr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
GenAnlzr::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenAnlzr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(GenAnlzr);
