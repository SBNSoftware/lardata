////////////////////////////////////////////////////////////////////////
// LArProperties.h
//
// Utility LAr functions
//
// maddalena.antonello@lngs.infn.it
// ornella.palamara@lngs.infn.it
// msoderbe@syr.edu
// joshua.spitz@yale.edu
//
// Optical Properties:
// bjpjones@mit.edu
//
// Separation of service from data provider class:
// jpaley@fnal.gov
//
////////////////////////////////////////////////////////////////////////
#ifndef LARPROPERTIES_H
#define LARPROPERTIES_H

#include <string>
#include <vector>
#include <map>

#include "fhiclcpp/ParameterSet.h"

///General LArSoft Utilities
namespace dataprov {
    class LArProperties {
    public:
      LArProperties();
      LArProperties(fhicl::ParameterSet const& pset);
      virtual ~LArProperties();

      virtual bool   Configure(fhicl::ParameterSet const& pset);
      virtual bool   Update(uint64_t ts=0) = 0;

      virtual double Density(double temperature=0.) const;                          ///< g/cm^3

      virtual double Temperature()                   const; 				///< kelvin	    
      double RadiationLength()  	     const { return fRadiationLength; } ///< g/cm^2      

      double Argon39DecayRate()              const { return fArgon39DecayRate; }  // decays per cm^3 per second

      /// Restricted mean dE/dx energy loss (MeV/cm).
      double Eloss(double mom, double mass, double tcut) const;

      /// Energy loss fluctuation (sigma_E^2 / length in MeV^2/cm).
      double ElossVar(double mom, double mass) const;

      double ScintResolutionScale() const { return fScintResolutionScale; }
      double ScintFastTimeConst()   const { return fScintFastTimeConst;   } 
      double ScintSlowTimeConst()   const { return fScintSlowTimeConst;   }
      double ScintBirksConstant()   const { return fScintBirksConstant;   }

      bool ScintByParticleType()    const { return fScintByParticleType;  }

      double ScintYield(bool prescale = false)         const { return fScintYield * ScintPreScale(prescale);}
      double ScintPreScale(bool prescale = true)       const { return (prescale ? fScintPreScale : 1);      }
      double ScintYieldRatio()                         const { return fScintYieldRatio;                     }

      double ProtonScintYield(bool prescale = false)   const { return fProtonScintYield * ScintPreScale(prescale);  }
      double ProtonScintYieldRatio()                   const { return fProtonScintYieldRatio;                       }
      double MuonScintYield(bool prescale = false)     const { return fMuonScintYield * ScintPreScale(prescale);    }
      double MuonScintYieldRatio()                     const { return fMuonScintYieldRatio;                         }
      double KaonScintYield(bool prescale = false)     const { return fKaonScintYield * ScintPreScale(prescale);    }
      double KaonScintYieldRatio()                     const { return fKaonScintYieldRatio;                         }
      double PionScintYield(bool prescale = false)     const { return fPionScintYield * ScintPreScale(prescale);    }
      double PionScintYieldRatio()                     const { return fPionScintYieldRatio;                         }
      double ElectronScintYield(bool prescale = false) const { return fElectronScintYield * ScintPreScale(prescale);}
      double ElectronScintYieldRatio()                 const { return fElectronScintYieldRatio;                     }
      double AlphaScintYield(bool prescale = false)    const { return fAlphaScintYield * ScintPreScale(prescale);   }
      double AlphaScintYieldRatio()                    const { return fAlphaScintYieldRatio;                        }
      bool CerenkovLightEnabled()                      const { return fEnableCerenkovLight;                         }

      
      std::map<double, double>  SlowScintSpectrum();   
      std::map<double, double>  FastScintSpectrum();
      std::map<double, double>  RIndexSpectrum();
      std::map<double, double>  AbsLengthSpectrum();
      std::map<double, double>  RayleighSpectrum();

      std::map<std::string, std::map<double, double> > SurfaceReflectances();
      std::map<std::string, std::map<double, double> > SurfaceReflectanceDiffuseFractions();
      
      void SetTemperature(double temp) { fTemperature = temp;}
      void SetElectronlifetime(double lt) { fElectronlifetime = lt; }
      void SetRadiationLength(double rl) { fRadiationLength = rl; }
      void SetArgon39DecayRate(double r) { fArgon39DecayRate = r;}
      void SetAtomicNumber(double z) { fZ = z;}
      void SetAtomicMass(double a) { fA = a;}
      void SetMeanExcitationEnergy(double e) { fI = e;}
      void SetSa(double s) { fSa = s;}
      void SetSk(double s) { fSk = s;}
      void SetSx0(double s) { fSx0 = s;}
      void SetSx1(double s) { fSx1 = s;}
      void SetScbar(double s) { fScbar = s;}

      void SetFastScintSpectrum(std::vector<double> s) { fFastScintSpectrum = s;}
      void SetFastScintEnergies(std::vector<double> s) { fFastScintEnergies = s;}
      void SetSlowScintSpectrum(std::vector<double> s) { fSlowScintSpectrum = s;}
      void SetSlowScintEnergies(std::vector<double> s) { fSlowScintSpectrum = s;}
      void SetRIndexSpectrum(std::vector<double> s)    { fRIndexSpectrum = s;}
      void SetRIndexEnergies(std::vector<double> s)    { fRIndexEnergies = s;}
      void SetAbsLengthSpectrum(std::vector<double> s) { fAbsLengthSpectrum = s;}
      void SetAbsLengthEnergies(std::vector<double> s) { fAbsLengthEnergies = s;}
      void SetRayleighSpectrum(std::vector<double> s)  { fRayleighSpectrum = s;}
      void SetRayleighEnergies(std::vector<double> s)  { fRayleighEnergies = s;}

      void SetScintByParticleType(bool l)        { fScintByParticleType = l;}
      void SetProtonScintYield(double y)         { fProtonScintYield = y;}
      void SetProtonScintYieldRatio(double r)    { fProtonScintYieldRatio = r;}
      void SetMuonScintYield(double y)           { fMuonScintYield = y;}
      void SetMuonScintYieldRatio(double r)      { fMuonScintYieldRatio = r;}
      void SetPionScintYield(double y)           { fPionScintYield = y;}
      void SetPionScintYieldRatio(double r)      { fPionScintYieldRatio = r;}
      void SetKaonScintYield(double y)           { fKaonScintYield = y;}
      void SetKaonScintYieldRatio(double r)      { fKaonScintYieldRatio = r;}
      void SetElectronScintYield(double y)       { fElectronScintYield = y;}
      void SetElectronScintYieldRatio(double r)  { fElectronScintYieldRatio = r;}
      void SetAlphaScintYield(double y)          { fAlphaScintYield = y;}
      void SetAlphaScintYieldRatio(double r)     { fAlphaScintYieldRatio = r;}

      void SetScintYield(double y)               { fScintYield = y;}
      void SetScintPreScale(double s)            { fScintPreScale = s;}
      void SetScintResolutionScale(double r)     { fScintResolutionScale = r; }
      void SetScintFastTimeConst(double t)       { fScintFastTimeConst = t;}
      void SetScintSlowTimeConst(double t)       { fScintSlowTimeConst = t;}
      void SetScintYieldRatio(double r)          { fScintYieldRatio = r;}
      void SetScintBirksConstant(double kb)      { fScintBirksConstant = kb;}
      void SetEnableCerenkovLight(bool f)        { fEnableCerenkovLight = f; }

      void SetReflectiveSurfaceNames(std::vector<std::string> n) { fReflectiveSurfaceNames = n;}
      void SetReflectiveSurfaceEnergies(std::vector<double> e)   { fReflectiveSurfaceEnergies = e;}
      void SetReflectiveSurfaceReflectances(std::vector<std::vector<double> > r) { fReflectiveSurfaceReflectances = r;}
      void SetReflectiveSurfaceDiffuseFractions(std::vector<std::vector<double> > f) { fReflectiveSurfaceDiffuseFractions = f;}

    private:
    protected:

      bool fIsConfigured;
      
      double                         fTemperature;      ///< kelvin
      double                         fElectronlifetime; ///< microseconds
      double                         fRadiationLength;  ///< g/cm^2
      double                         fArgon39DecayRate; ///<  decays per cm^3 per second
      
      // Following parameters are for use in Bethe-Bloch formula for dE/dx.

      double fZ;                ///< Ar atomic number
      double fA;                ///< Ar atomic mass (g/mol)
      double fI;                ///< Ar mean excitation energy (eV)
      double fSa;               ///< Sternheimer parameter a
      double fSk;               ///< Sternheimer parameter k
      double fSx0;              ///< Sternheimer parameter x0
      double fSx1;              ///< Sternheimer parameter x1
      double fScbar;            ///< Sternheimer parameter Cbar


      // Optical parameters for LAr

      std::vector<double> fFastScintSpectrum;
      std::vector<double> fFastScintEnergies;
      std::vector<double> fSlowScintSpectrum;
      std::vector<double> fSlowScintEnergies;
      std::vector<double> fRIndexSpectrum;
      std::vector<double> fRIndexEnergies;
      std::vector<double> fAbsLengthSpectrum;
      std::vector<double> fAbsLengthEnergies;
      std::vector<double> fRayleighSpectrum;
      std::vector<double> fRayleighEnergies;

      bool fScintByParticleType;

      double fProtonScintYield;
      double fProtonScintYieldRatio; 
      double fMuonScintYield;
      double fMuonScintYieldRatio; 
      double fPionScintYield;
      double fPionScintYieldRatio; 
      double fKaonScintYield;
      double fKaonScintYieldRatio; 
      double fElectronScintYield;
      double fElectronScintYieldRatio; 
      double fAlphaScintYield;
      double fAlphaScintYieldRatio; 

      double fScintYield;
      double fScintPreScale;
      double fScintResolutionScale;
      double fScintFastTimeConst;
      double fScintSlowTimeConst;
      double fScintYieldRatio;
      double fScintBirksConstant;

      bool fEnableCerenkovLight;

      std::vector<std::string>          fReflectiveSurfaceNames;
      std::vector<double>               fReflectiveSurfaceEnergies;
      std::vector<std::vector<double> > fReflectiveSurfaceReflectances;
      std::vector<std::vector<double> > fReflectiveSurfaceDiffuseFractions;
      
      
      
    }; // class LArProperties
} //namespace utils
#endif // LARPROPERTIES_H
