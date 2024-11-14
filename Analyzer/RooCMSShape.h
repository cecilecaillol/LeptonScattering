#ifndef ROO_CMS_SHAPE
#define ROO_CMS_SHAPE

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "TMath.h"
#include "RooMath.h"

class RooCMSShape : public RooAbsPdf {
public:
  RooCMSShape() {};
  /*RooCMSShape(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _alpha,
	      RooAbsReal& _beta,
	      RooAbsReal& _gamma,
	      RooAbsReal& _peak) {};*/

   RooCMSShape(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _alpha,
                        RooAbsReal& _beta,
                        RooAbsReal& _gamma,
                        RooAbsReal& _peak) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   alpha("alpha","alpha",this,_alpha),
   beta("beta","beta",this,_beta),
   gamma("gamma","gamma",this,_gamma),
   peak("peak","peak",this,_peak)
 { }; 


  //RooCMSShape(const RooCMSShape& other, const char* name) {};
  //
   RooCMSShape(const RooCMSShape& other, const char* name):
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   alpha("alpha",this,other.alpha),
   beta("beta",this,other.beta),
   gamma("gamma",this,other.gamma),
   peak("peak",this,other.peak)
 { };

  inline virtual TObject* clone(const char* newname) const { return new RooCMSShape(*this,newname); }
  ~RooCMSShape() {};
  Double_t evaluate() const { 
  // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 

  //Double_t erf = TMath::Erfc((alpha - x) * beta);
  Double_t erf = RooMath::erfc((alpha - x) * beta);
  Double_t u = (x - peak)*gamma;

  if(u < -70) u = 1e20;
  else if( u>70 ) u = 0;
  else u = exp(-u);   //exponential decay
  return erf*u;
 } ;
  

  //ClassDef(RooCMSShape,2);

protected:

  RooRealProxy x ;
  RooRealProxy alpha ;
  RooRealProxy beta ;
  RooRealProxy gamma ;
  RooRealProxy peak ;
  
};
 
#endif
