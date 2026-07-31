////////////////////////////////////////////////////////////////////////
// Class:       SCEDLVertexAnalyzer
// Plugin Type: analyzer (Unknown Unknown)
// File:        SCEDLVertexAnalyzer_module.cc
//
// Generated at Mon May 11 04:57:24 2026 by Alexandra Moor using cetskelgen
// from cetlib version 3.18.02.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include <TTree.h>

#include "lardataalg/DetectorInfo/DetectorPropertiesData.h"
#include "lardataalg/DetectorInfo/DetectorPropertiesStandard.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "larsim/MCCheater/BackTrackerService.h"
#include "larsim/MCCheater/ParticleInventoryService.h"
#include "larsim/Utils/TruthMatchUtils.h"
#include "larsim/MCCheater/BackTrackerService.h"

#include "art_root_io/TFileService.h"
#include "canvas/Persistency/Common/Ptr.h"
#include "art/Framework/Core/FileBlock.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Common/FindOneP.h"

#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/GTruth.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCNeutrino.h"

#include "sbnobj/Common/Reco/OpT0FinderResult.h"
#include "lardataobj/RecoBase/Slice.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "lardataobj/RecoBase/PFParticleMetadata.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Shower.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/AnalysisBase/ParticleID.h"

constexpr Int_t DEFAULT_INT     = -9999;
constexpr Int_t TRUTH_MATCHING_FAILED = -8888;
constexpr Int_t OBJECT_NOT_AVAILABLE = -7777;
constexpr Float_t DEFAULT_FLOAT = -9999.0;
constexpr Int_t NO_ERR = 0;
constexpr Int_t ERR_PANDORA_NOT_AVAILABLE = -10000;
constexpr Int_t ERR_NO_SLICES_FOUND = -20000;


namespace ana {
  class SCEDLVertexAnalyzer;
}


class ana::SCEDLVertexAnalyzer : public art::EDAnalyzer {
public:
  explicit SCEDLVertexAnalyzer(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  SCEDLVertexAnalyzer(SCEDLVertexAnalyzer const&) = delete;
  SCEDLVertexAnalyzer(SCEDLVertexAnalyzer&&) = delete;
  SCEDLVertexAnalyzer& operator=(SCEDLVertexAnalyzer const&) = delete;
  SCEDLVertexAnalyzer& operator=(SCEDLVertexAnalyzer&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  void get_GENIE_info(art::Ptr<simb::MCTruth> const& MCGenInteraction, size_t i);
  void get_pfp_vertices(const art::FindManyP<recob::Vertex>& findManyVerticesFromPFParticle, const art::Ptr<recob::PFParticle>& pfparticle);
  void get_PANDORA_info(art::Event const & e);

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

  void clear_truth_data();
  void clear_reco_data();

private:

  art::ServiceHandle<cheat::BackTrackerService> backTracker;
  art::ServiceHandle<cheat::ParticleInventoryService> particleInv;

  std::string filepath;
  Int_t event_error_code;

  // Run, SubRun and Event IDs.
  unsigned int run_ID;
  unsigned int subrun_ID;
  unsigned int event_ID;
  unsigned int full_event_ID;

  TTree* GENIE_MCTree;
  //TTree* MCTree;
  TTree* RecoTree;

  int mcgen_interaction_ID;
  Float_t mcgen_int_vtx_x;
  Float_t mcgen_int_vtx_y;
  Float_t mcgen_int_vtx_z;

  std::string fMCPOTSummaryLabel;
  std::string fMCParticleLabel;
  std::string fMCTruthLabel;
  std::string fRecoOpT0FinderLabel;
  std::string fRecoCaloLabel;
  std::string fMCRecoTruthMatchingLabel;
  std::string fRecoAllHits;
  std::string fRecoSlicesLabel;
  std::string fRecoTrackLabel;
  std::string fRecoTrackHitsLabel;
  std::string fRecoShowerLabel;
  std::string fRecoClusterLabel;
  std::string fRecoPFParticleLabel;
  std::string fRecoPFParticleMetadataLabel;
  std::string fRecoPIDLabel;
  std::string fRecoVertexLabel;

  Float_t true_vtx_x;
  Float_t true_vtx_y;
  Float_t true_vtx_z;

  Int_t reco_slice_num_slices;
  Int_t reco_slice_num_vertices;

  Int_t reco_slice_vertex_key;
  Int_t reco_slice_vertex_idx;
  Int_t reco_slice_vertex_ID;
  Float_t reco_slice_vertex_x;
  Float_t reco_slice_vertex_y;
  Float_t reco_slice_vertex_z;

  Float_t dx_vertex_x;
  Float_t dy_vertex_y;
  Float_t dz_vertex_z;

  std::vector<Int_t> reco_pfp_vertex_key;
  std::vector<Int_t> reco_pfp_vertex_idx;
  std::vector<Int_t> reco_pfp_vertex_ID;
  std::vector<Float_t> reco_pfp_vertex_x;
  std::vector<Float_t> reco_pfp_vertex_y;
  std::vector<Float_t> reco_pfp_vertex_z;

  std::vector<Int_t> reco_pfp_num_vertices;

};


ana::SCEDLVertexAnalyzer::SCEDLVertexAnalyzer(fhicl::ParameterSet const& p)
  : EDAnalyzer{p},

  fMCPOTSummaryLabel(p.get<std::string>("POTSummaryLabel")),
  fMCParticleLabel(p.get<std::string>("MCParticleLabel")),
  fMCTruthLabel(p.get<std::string>("MCTruthLabel")),
  fRecoOpT0FinderLabel(p.get<std::string>("RecoOpT0FinderLabel")),
  fRecoCaloLabel(p.get<std::string>("RecoCaloLabel")),
  fMCRecoTruthMatchingLabel(p.get<std::string>("MCTruthMatchingLabel")),
  fRecoAllHits(p.get<std::string>("RecoAllHits")),
  fRecoSlicesLabel(p.get<std::string>("RecoSlicesLabel")),
  fRecoTrackLabel(p.get<std::string>("RecoTrackLabel")),
  fRecoTrackHitsLabel(p.get<std::string>("RecoTrackHitsLabel")),
  fRecoShowerLabel(p.get<std::string>("RecoShowerLabel")),
  fRecoClusterLabel(p.get<std::string>("RecoClusterLabel")),
  fRecoPFParticleLabel(p.get<std::string>("RecoPFParticleLabel")),
  fRecoPFParticleMetadataLabel(p.get<std::string>("RecoPFParticleMetadataLabel")),
  fRecoPIDLabel(p.get<std::string>("RecoPIDLabel")),
  fRecoVertexLabel(p.get<std::string>("RecoVertexLabel"))
  // More initializers here.
{
  // Call appropriate consumes<>() for any products to be retrieved by this module.
}

void ana::SCEDLVertexAnalyzer::clear_truth_data() {

  mcgen_interaction_ID = -1;

}

void ana::SCEDLVertexAnalyzer::clear_reco_data() {

  true_vtx_x = DEFAULT_FLOAT;
  true_vtx_y = DEFAULT_FLOAT;
  true_vtx_z = DEFAULT_FLOAT;

  reco_slice_num_slices = DEFAULT_INT;

  reco_slice_vertex_key = DEFAULT_INT;
  reco_slice_vertex_idx = DEFAULT_INT;
  reco_slice_vertex_ID = DEFAULT_INT;
  reco_slice_vertex_x = DEFAULT_FLOAT;
  reco_slice_vertex_y = DEFAULT_FLOAT;
  reco_slice_vertex_z = DEFAULT_FLOAT;

  dx_vertex_x = DEFAULT_FLOAT;
  dy_vertex_y = DEFAULT_FLOAT;
  dz_vertex_z = DEFAULT_FLOAT;

  reco_slice_num_vertices = DEFAULT_INT;

  reco_pfp_num_vertices.clear();

  reco_pfp_vertex_key.clear();
  reco_pfp_vertex_idx.clear();
  reco_pfp_vertex_ID.clear();
  reco_pfp_vertex_x.clear();
  reco_pfp_vertex_y.clear();
  reco_pfp_vertex_z.clear();

}

void ana::SCEDLVertexAnalyzer::analyze(art::Event const& e)
{
  run_ID = e.run();
  subrun_ID = e.subRun();
  event_ID = e.id().event();
  full_event_ID = std::stoi(std::to_string(run_ID) + std::to_string(subrun_ID) + std::to_string(event_ID));

    std::cout << "\n\n============================================================================================================================================================================================================================================================" << std::endl;
    std::cout << "::::::::::::::::::::::::::::::::::::::::::::::::" << " ANALYZING RUN " << run_ID << " SUBRUN " << subrun_ID << " EVENT " << event_ID << " (" << full_event_ID << ") ... ::::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
    std::cout << "============================================================================================================================================================================================================================================================\n" << std::endl;


  // MCTruth handle.
  art::Handle<std::vector<simb::MCTruth>> MCGenListHandle;
  std::vector<art::Ptr<simb::MCTruth>> MCGenList;
  std::cout << "Before getByLabel" << std::endl;
  if (e.getByLabel(fMCTruthLabel, MCGenListHandle)) {
    art::fill_ptr_vector(MCGenList, MCGenListHandle);
  }
  std::cout << "Got by label" << std::endl;
  std::cout << "MCGenListHandle = " << MCGenListHandle << std::endl;
  // Associate Geant 4 information to the GENIE objects.
  art::FindManyP<simb::MCParticle, sim::GeneratedParticleInfo> findManyMCParticle(MCGenListHandle, e, fMCParticleLabel);

  std::cout << "MCGenList size = " << MCGenList.size() << std::endl;

  // Interaction generated.
  if (!MCGenList.empty()) { 
    std::cout << "Number of interactions in this event: " << MCGenList.size() << std::endl;
    for (size_t i = 0; i < MCGenList.size(); i++) { 
      clear_truth_data();
      art::Ptr<simb::MCTruth> MCGenInteraction = MCGenList[i];

      // If it is a neutrino interaction it gets MCNeutrino information.
      if (MCGenInteraction->NeutrinoSet()) {

        get_GENIE_info(MCGenInteraction, i);
        GENIE_MCTree->Fill();

      } else {
        std::cout << "Not a neutrino interaction." << std::endl;
      }
    }
  }
  get_PANDORA_info(e);
}

void ana::SCEDLVertexAnalyzer::get_GENIE_info(art::Ptr<simb::MCTruth> const& MCGenInteraction, size_t i) {
  simb::MCNeutrino nu_interaction = MCGenInteraction->GetNeutrino();

  // Incoming neutrino.
  simb::MCParticle nu = nu_interaction.Nu();
  TVector3 in(nu.Px(), nu.Py(), nu.Pz());

  mcgen_interaction_ID = i;                                         // Interaction ID for this event.
  mcgen_int_vtx_x = nu.Vx();                                        // X coordinate of the interaction vertex (cm).
  mcgen_int_vtx_y = nu.Vy();                                        // Y coordinate of the interaction vertex (cm).
  mcgen_int_vtx_z = nu.Vz();                                        // Z coordinate of the interaction vertex (cm).
  size_t num_int_particles = MCGenInteraction->NParticles();        // Number of particles generated for this interaction.

    std::cout << "\n==================== INTERACTION " << i << " ====================" << std::endl;
    std::cout << "\n---------- GENERATOR INFO ---------- " << std::endl;
    std::cout
 
        << "\nVertex interaction: (" << mcgen_int_vtx_x << ", " << mcgen_int_vtx_y << ", " << mcgen_int_vtx_z << ") cm."
        << std::endl;
    std::cout << "Number of particles from GENIE:  " << num_int_particles << std::endl;
    std::cout << "- Final state particles at GENIE: " << std::endl;


}

void ana::SCEDLVertexAnalyzer::get_PANDORA_info(art::Event const & e) {

  bool pandora_available = true;


  std::cout << "\n------------- RECO INFO -------------- " << std::endl;

  // Accesses slices from PANDORA
  art::Handle<std::vector<recob::Slice>> MCRecoSlicesHandle = e.getHandle<std::vector<recob::Slice>>(fRecoSlicesLabel);
  std::vector<art::Ptr<recob::Slice>> MCRecoSlicesList;
  if (MCRecoSlicesHandle.isValid()) {
    art::fill_ptr_vector(MCRecoSlicesList, MCRecoSlicesHandle);
  } else {
    pandora_available = false;
    std::cout << "No valid handle for PANDORA slices." << std::endl;
  }

  // Accesses PFParticles from PANDORA.
  art::Handle<std::vector<recob::PFParticle>> MCRecoPFParticlesHandle = e.getHandle<std::vector<recob::PFParticle>>(fRecoPFParticleLabel);
  std::vector<art::Ptr<recob::PFParticle>> MCRecoPFParticleList;
  if (MCRecoPFParticlesHandle.isValid()) {
    art::fill_ptr_vector(MCRecoPFParticleList, MCRecoPFParticlesHandle);
  } else {
    pandora_available = false;
    std::cout << "No valid handle for PANDORA PFParticles." << std::endl;
  }

  // Accesses Tracks from PANDORA.
    art::Handle<std::vector<recob::Track>> MCRecoTracksHandle = e.getHandle<std::vector<recob::Track>>(fRecoTrackLabel);
  std::vector<art::Ptr<recob::Track>> MCRecoTrackList;
  if (MCRecoTracksHandle.isValid()) {
    art::fill_ptr_vector(MCRecoTrackList, MCRecoTracksHandle);
  } else {
    std::cout << "No valid handle for PANDORA tracks found in this event." << std::endl;
  }

  // Checks opT0finder availability
    art::Handle<art::Assns<recob::Slice, sbn::OpT0Finder>> opT0AssnsHandle;
  bool opT0_available = e.getByLabel(fRecoOpT0FinderLabel, opT0AssnsHandle);
  if (!opT0_available) {
    std::cout << "OpT0Finder associations not found for label '" << fRecoOpT0FinderLabel << "'. Skipping OpT0 extraction." << std::endl;
  }

  if (pandora_available) {
    // Pandora associations.
    art::FindManyP<recob::PFParticle> findManyPFParticleFromSlice(MCRecoSlicesHandle, e, fRecoPFParticleLabel);
    art::FindManyP<larpandoraobj::PFParticleMetadata> findManyPFParticleMetadatafromPFParticle(MCRecoPFParticlesHandle, e, fRecoPFParticleMetadataLabel);
    art::FindManyP<recob::Track> findManyTracksFromPFParticle(MCRecoPFParticlesHandle, e, fRecoTrackLabel);
    art::FindManyP<anab::Calorimetry> findManyCaloFromTrack(MCRecoTracksHandle, e, fRecoCaloLabel);
    art::FindManyP<recob::Hit> findManyHitsFromTrack(MCRecoTracksHandle, e, fRecoTrackHitsLabel);
    art::FindManyP<anab::ParticleID> findManyPidFromTrack(MCRecoTracksHandle, e, fRecoPIDLabel);
    art::FindManyP<recob::Shower> findManyShowersFromPFParticle(MCRecoPFParticlesHandle, e, fRecoShowerLabel);
    art::FindManyP<recob::Vertex> findManyVerticesFromPFParticle(MCRecoPFParticlesHandle, e, fRecoVertexLabel);

    // Truth matching associations.
    art::FindManyP<recob::Hit> slice_hit_assns(MCRecoSlicesHandle, e, fRecoPFParticleLabel);

    size_t num_slices = MCRecoSlicesList.size();

    if (num_slices == 0) {
      clear_reco_data();

      true_vtx_x = mcgen_int_vtx_x;
      true_vtx_y = mcgen_int_vtx_y;
      true_vtx_z = mcgen_int_vtx_z;

      event_error_code = ERR_NO_SLICES_FOUND;
      reco_slice_num_slices = num_slices; // 0
      RecoTree->Fill();
      //RecoFailedTree->Fill();
    }

    for (size_t s = 0; s < num_slices; s++) {
      clear_reco_data();


      /// True information for this slice ////
      true_vtx_x = mcgen_int_vtx_x;
      true_vtx_y = mcgen_int_vtx_y;
      true_vtx_z = mcgen_int_vtx_z;

      const art::Ptr<recob::Slice> slice = MCRecoSlicesList[s];

      std::vector<art::Ptr<recob::PFParticle>> slice_particles(findManyPFParticleFromSlice.at(slice.key()));

      for (size_t p = 0; p < slice_particles.size(); p++) {
        const art::Ptr<recob::PFParticle> pfparticle = slice_particles[p];
        get_pfp_vertices(findManyVerticesFromPFParticle, pfparticle);

      } // End PFParticles loop.

      

      RecoTree->Fill();
     }
  }
}

void ana::SCEDLVertexAnalyzer::beginJob()
{
  // Implementation of optional member function here.
   art::ServiceHandle<art::TFileService> tfs;

  GENIE_MCTree = tfs->make<TTree> ("GENIE_MCTree", "[GENIE] Output MC TTree of the GENIE Muon Kaon Analyzer");

  GENIE_MCTree->Branch("run_ID", &run_ID);
  GENIE_MCTree->Branch("subrun_ID", &subrun_ID);
  GENIE_MCTree->Branch("event_ID", &event_ID);
  GENIE_MCTree->Branch("full_event_ID", &full_event_ID);
  GENIE_MCTree->Branch("filepath", &filepath);

  GENIE_MCTree->Branch("mcgen_int_vtx_x", &mcgen_int_vtx_x);
  GENIE_MCTree->Branch("mcgen_int_vtx_y", &mcgen_int_vtx_y);
  GENIE_MCTree->Branch("mcgen_int_vtx_z", &mcgen_int_vtx_z);

  //MCTree = tfs->make<TTree>("MCTree", "[G4] Output MC TTree of the GENIE Muon Kaon Analyzer");
  //MCTree->Branch("run_ID", &run_ID);
  //MCTree->Branch("subrun_ID", &subrun_ID);
  //MCTree->Branch("event_ID", &event_ID);
  //MCTree->Branch("full_event_ID", &full_event_ID);
  //MCTree->Branch("filepath", &filepath);

  //MCTree->Branch("mcgen_int_vtx_x", &mcgen_int_vtx_x);
  //MCTree->Branch("mcgen_int_vtx_y", &mcgen_int_vtx_y);
  //MCTree->Branch("mcgen_int_vtx_z", &mcgen_int_vtx_z);

  RecoTree = tfs->make<TTree>("RecoTree", "[PANDORA] Output MC TTree of the GENIE Muon Kaon Analyzer");


  RecoTree->Branch("run_ID", &run_ID);
  RecoTree->Branch("subrun_ID", &subrun_ID);
  RecoTree->Branch("event_ID", &event_ID);
  RecoTree->Branch("full_event_ID", &full_event_ID);
  RecoTree->Branch("filepath", &filepath);

  RecoTree->Branch("true_vtx_x", &true_vtx_x);
  RecoTree->Branch("true_vtx_y", &true_vtx_y);
  RecoTree->Branch("true_vtx_z", &true_vtx_z);

  RecoTree->Branch("slice_vertex_x", &reco_slice_vertex_x);
  RecoTree->Branch("slice_vertex_y", &reco_slice_vertex_y);
  RecoTree->Branch("slice_vertex_z", &reco_slice_vertex_z);

  RecoTree->Branch("dx_vertex_x", &dx_vertex_x);
  RecoTree->Branch("dy_vertex_y", &dy_vertex_y);
  RecoTree->Branch("dz_vertex_z", &dz_vertex_z);

  RecoTree->Branch("pfp_vertex_key", &reco_pfp_vertex_key);
  RecoTree->Branch("pfp_vertex_idx", &reco_pfp_vertex_idx);
  RecoTree->Branch("pfp_vertex_ID", &reco_pfp_vertex_ID);
  RecoTree->Branch("pfp_vertex_x", &reco_pfp_vertex_x);
  RecoTree->Branch("pfp_vertex_y", &reco_pfp_vertex_y);
  RecoTree->Branch("pfp_vertex_z", &reco_pfp_vertex_z);
}

void ana::SCEDLVertexAnalyzer::endJob()
{
  // Implementation of optional member function here.
  std::cout << "Ending job..." << std::endl;
}

void ana::SCEDLVertexAnalyzer::get_pfp_vertices(const art::FindManyP<recob::Vertex>& findManyVerticesFromPFParticle, const art::Ptr<recob::PFParticle>& pfparticle) {
  // Get Vertex data.
  std::vector<art::Ptr<recob::Vertex>> pfp_vertices(findManyVerticesFromPFParticle.at(pfparticle.key()));
  const Int_t pfp_num_vertices = pfp_vertices.size();
  reco_slice_num_vertices += pfp_num_vertices;
  std::cout << "\t\tNumber of vertices: " << pfp_num_vertices << "." << std::endl;

  Int_t vertex_key = DEFAULT_INT;
  Int_t vertex_idx = DEFAULT_INT;
  Int_t vertex_ID = DEFAULT_INT;
  Float_t vertex_x = DEFAULT_FLOAT;
  Float_t vertex_y = DEFAULT_FLOAT;
  Float_t vertex_z = DEFAULT_FLOAT;


  for (size_t v = 0; v < pfp_vertices.size(); v++) {
    const art::Ptr<recob::Vertex> vertex = pfp_vertices.at(v);

    vertex_key = DEFAULT_INT;
    vertex_idx = DEFAULT_INT;
    vertex_ID = DEFAULT_INT;
    vertex_x = DEFAULT_FLOAT;
    vertex_y = DEFAULT_FLOAT;
    vertex_z = DEFAULT_FLOAT;

    if (vertex.isAvailable()) {
      vertex_key = vertex.key();
      vertex_idx = v + 1;
      vertex_ID = vertex->ID();
      vertex_x = vertex->position().X();
      vertex_y = vertex->position().Y();
      vertex_z = vertex->position().Z();

        std::cout << "\t\t- Vertex " << v << " (key " << vertex_key << ", ID " << vertex_ID << ")" << std::endl;
        std::cout << "\t\t\tPosition: (" << vertex_x << ", " << vertex_y << ", " << vertex_z << ") cm." << std::endl;
        std::cout << "\t\t\t True Position: (" << true_vtx_x << ", " << true_vtx_y << ", " << true_vtx_z << ") cm." << std::endl;


      if (pfparticle->IsPrimary()) {
        reco_slice_vertex_key = vertex_key;
        reco_slice_vertex_idx = vertex_idx;
        reco_slice_vertex_ID = vertex_ID;
        reco_slice_vertex_x = vertex_x;
        reco_slice_vertex_y = vertex_y;
        reco_slice_vertex_z = vertex_z;
        dx_vertex_x = vertex_x - true_vtx_x;
        dy_vertex_y = vertex_y - true_vtx_y;
        dz_vertex_z = vertex_z - true_vtx_z;
        std::cout << "\t\t\t pfpparticle is primary" << std::endl;
      }

    } else {
      std::cout << "Invalid pointer to a recob::Vertex (key: " << vertex.key() << "). Skipping this vertex..." << std::endl;
    }
  }

  reco_pfp_num_vertices.push_back(pfp_num_vertices);

  reco_pfp_vertex_key.push_back(vertex_key);
  reco_pfp_vertex_idx.push_back(vertex_idx);
  reco_pfp_vertex_ID.push_back(vertex_ID);
  reco_pfp_vertex_x.push_back(vertex_x);
  reco_pfp_vertex_y.push_back(vertex_y);
  reco_pfp_vertex_z.push_back(vertex_z);
}

DEFINE_ART_MODULE(ana::SCEDLVertexAnalyzer)
