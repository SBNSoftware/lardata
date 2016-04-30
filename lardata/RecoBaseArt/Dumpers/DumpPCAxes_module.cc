/**
 * @file   DumpPCAxes_module.cc
 * @brief  Dumps on screen the content of Principal Component Axis objects
 * @author Gianluca Petrillo (petrillo@fnal.gov)
 * @date   December 18th, 2015
 */

// LArSoft includes

// art libraries
#include "art/Utilities/InputTag.h"
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Principal/Event.h"

// support libraries
#include "fhiclcpp/ParameterSet.h"

// C//C++ standard libraries
#include <string>

// ... and more in the implementation part

namespace recob {
  
  /**
   * @brief Prints the content of all the PCA axis object on screen
   *
   * This analyser prints the content of all the principal component axis object
   * into the LogInfo/LogVerbatim stream.
   * 
   * Configuration parameters
   * =========================
   * 
   * - *PCAxisModuleLabel* (art::InputTag, mandatory): label of the
   *   producer used to create the recob::PCAxis collection to be dumped
   * - *OutputCategory* (string, default: "DumpPCAxes"): the category used
   *   for the output (useful for filtering)
   *
   */
  class DumpPCAxes: public art::EDAnalyzer {
      public:
    
    /// Configuration parameters
    struct Config {
      using Name = fhicl::Name;
      using Comment = fhicl::Comment;
      
      fhicl::Atom<art::InputTag> PCAxisModuleLabel {
        Name   ("PCAxisModuleLabel"),
        Comment("label of the producer used to create the recob::PCAxis collection to be dumped")
        };
      fhicl::Atom<std::string> OutputCategory {
        Name   ("OutputCategory"),
        Comment("the category used for the output (useful for filtering) [\"DumpPCAxes\"]"),
        "DumpPCAxes" /* default value */
        };
      fhicl::Atom<bool> PrintHexFloats {
        Name   ("PrintHexFloats"),
        Comment("print floating point numbers in base 16 [\"DumpPCAxes\"]"),
        false /* default value */
        };
      
    }; // struct Config
    
    /// Default constructor
    explicit DumpPCAxes(art::EDAnalyzer::Table<Config> const& config); 
    
    /// Does the printing
    virtual void analyze (const art::Event& evt) override;

      private:

    art::InputTag fInputTag; ///< input tag of the PCAxis product
    std::string fOutputCategory; ///< category for LogInfo output
    bool fPrintHexFloats; ///< whether to print floats in base 16

  }; // class DumpPCAxes
  
} // namespace recob


//==============================================================================
//===  Implementation section
//==============================================================================

// LArSoft includes
#include "lardata/RecoBase/PCAxis.h"
#include "lardata/RecoBaseArt/Dumpers/NewLine.h" // recob::dumper::makeNewLine()
#include "lardata/RecoBaseArt/Dumpers/PCAxisDumpers.h" // recob::dumper::DumpPCAxis()

// art libraries
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Handle.h"

// support libraries
#include "messagefacility/MessageLogger/MessageLogger.h"

// C//C++ standard libraries
#include <vector>


namespace {
  
  //----------------------------------------------------------------------------
  class PCAxisDumper {
      public:
    
    /// Collection of available printing style options
    struct PrintOptions_t {
      bool hexFloats = false; ///< print all floating point numbers in base 16
    }; // PrintOptions_t
    
    
    /// Constructor; will dump space points from the specified list
    PCAxisDumper(
      std::vector<recob::PCAxis> const& pca_list,
      PrintOptions_t print_options = {}
      )
      : pcas(pca_list)
      , options(print_options)
      {}
    
    
    /// Dump a space point specified by its index in the input list
    template <typename Stream>
    void DumpPCAxis
      (Stream&& out, size_t iPCA, std::string indentstr = "") const
      {
        recob::PCAxis const& pca = pcas.at(iPCA);
        
        //
        // intro
        //
        auto first_nl = recob::dumper::makeNewLine(out, indentstr);
        first_nl()
          << "[#" << iPCA << "] ";
        
        auto nl = recob::dumper::makeNewLine
          (out, indentstr + "  ", true /* follow */);
        recob::dumper::DumpPCAxis(out, pca, nl);
        
        //
        // done
        //
        
      } // DumpPCAxis()
    
    
    /// Dumps all space points in the input list
    template <typename Stream>
    void DumpAllPCAxes(Stream&& out, std::string indentstr = "") const
      {
        indentstr += "  ";
        size_t const nPCAs = pcas.size();
        for (size_t iPCA = 0; iPCA < nPCAs; ++iPCA)
          DumpPCAxis(std::forward<Stream>(out), iPCA, indentstr);
      } // DumpAllPCAxes()
    
    
    
      protected:
    std::vector<recob::PCAxis> const& pcas; ///< input list
    
    PrintOptions_t options; ///< printing and formatting options
    
  }; // PCAxisDumper
  
  
  //----------------------------------------------------------------------------
  
  
} // local namespace



namespace recob {
  
  //----------------------------------------------------------------------------
  DumpPCAxes::DumpPCAxes(art::EDAnalyzer::Table<Config> const& config)
    : EDAnalyzer(config)
    , fInputTag(config().PCAxisModuleLabel())
    , fOutputCategory(config().OutputCategory())
    , fPrintHexFloats(config().PrintHexFloats())
    {}
  
  
  //----------------------------------------------------------------------------
  void DumpPCAxes::analyze(const art::Event& evt) {
    
    //
    // collect all the available information
    //
    // fetch the data to be dumped on screen
    auto PCAxes = evt.getValidHandle<std::vector<recob::PCAxis>>(fInputTag);
    
    size_t const nPCAs = PCAxes->size();
    mf::LogInfo(fOutputCategory)
      << "The event contains " << nPCAs << " PC axes from '"
      << fInputTag.encode() << "'";
    
    // prepare the dumper
    PCAxisDumper::PrintOptions_t options;
    options.hexFloats = fPrintHexFloats;
    PCAxisDumper dumper(*PCAxes, options);
    
    dumper.DumpAllPCAxes(mf::LogVerbatim(fOutputCategory), "  ");
    
    mf::LogVerbatim(fOutputCategory) << "\n"; // two empty lines
    
  } // DumpPCAxes::analyze()

  DEFINE_ART_MODULE(DumpPCAxes)

} // namespace recob
