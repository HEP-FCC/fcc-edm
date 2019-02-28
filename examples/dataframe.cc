
#include <ROOT/RDataFrame.hxx>
#include <TSystem.h>
#include <TLorentzVector.h>

// FCC event datamodel includes
#include "datamodel/ParticleData.h"
// pt lambda defined here
#include "utilities/FCCLambdas.h"


#include <algorithm>


std::vector<float> particle_eta(std::vector<fcc::ParticleData> in){
 std::vector<float> result;
   TLorentzVector lv;
	 for (size_t i = 0; i < in.size(); ++i) {
     lv.SetXYZM(in[i].core.p4.px, in[i].core.p4.py, in[i].core.p4.pz, in[i].core.p4.mass);
		 result.push_back(lv.Eta());
	 }
	 return result;
}

  bool eta_filter (std::vector<float> in) { return (*std::max_element(in.begin(),
  in.end()) > 3); }

int main(){

   // fcc edm libraries
   gSystem->Load("libutilities.so");
   gSystem->Load("libdatamodel.so");
   

   std::cout << "Read file.. ";

   
   std::cout << "Creating TDataFrame ..." << std::endl;
   ROOT::RDataFrame df("events", "example.root");



   auto dff =  df
                      .Define("GenParticle_eta", particle_eta, {"GenParticle"})
                    ;
  auto nentries = dff.Count();
  std::cout << "Count events: " <<  *nentries << std::endl;


  auto dff_filtered = dff.Filter(eta_filter, {"GenParticle_eta"});
  auto nentries_filtered = dff_filtered.Count();
  std::cout << " ... events with at least one particle with eta > 3: " <<  *nentries_filtered << std::endl;

  std::cout << "Writing snapshot  ..." << std::endl;
  dff.Snapshot("events", "example_snapshot.root",
    { 
      "GenParticle_eta",

      }
    );

   return 0;
}
