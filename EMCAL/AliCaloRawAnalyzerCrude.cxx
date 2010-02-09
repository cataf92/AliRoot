/**************************************************************************
 * This file is property of and copyright by the Experimental Nuclear     *
 * Physics Group, Dep. of Physics                                         *
 * University of Oslo, Norway, 2007                                       *
 *                                                                        *
 * Author: Per Thomas Hille <perthi@fys.uio.no> for the ALICE HLT Project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to perthi@fys.uio.no                                *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/
#include "AliCaloRawAnalyzerCrude.h"
#include "AliCaloFitResults.h"
#include "AliCaloBunchInfo.h"


AliCaloRawAnalyzerCrude::AliCaloRawAnalyzerCrude()
{

}


AliCaloRawAnalyzerCrude::~AliCaloRawAnalyzerCrude()
{

}


AliCaloFitResults
AliCaloRawAnalyzerCrude::Evaluate(const vector<AliCaloBunchInfo> &bunchvector, const UInt_t /*altrocfg1*/,  const UInt_t /*altrocfg2*/)
{
  if( bunchvector.size()  <=  0 )
    {
      return AliCaloFitResults(-1, -1, -1, -1 , -1, -1, -1 );
    }

  Int_t amp = 0;
  Float_t tof = -99;
  const UShort_t *sig;
  
  double ped = EvaluatePedestal( bunchvector.at(0).GetData(), bunchvector.at(0).GetLength() ) ;

  for( unsigned int i= 0; i < bunchvector.size(); ++i)
    {
      sig = bunchvector.at(i).GetData();
      int length = bunchvector.at(i).GetLength(); 
      
      for(int j = 0; j < length; j ++)
	if( sig[j] > amp  )
	  {
	    amp   = sig[j];
	    tof   = i;		     
	  }
    }

  //:EvaluatePedestal(const UShort_t * const data, const int length )
  //  double ped = EvaluatePedestal(sig, length) ;
  return  AliCaloFitResults(amp, ped, -1, amp - ped, tof, -1, -1 );
  
} //end Crude


