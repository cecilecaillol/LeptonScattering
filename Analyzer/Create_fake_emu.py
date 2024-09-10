if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=1

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[""]

    nbhist=1 

    fZZ=ROOT.TFile("output_emu_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_emu_"+options.year+"/WZ3LNu.root","r")
    fTT=ROOT.TFile("output_emu_"+options.year+"/TTTo2L2Nu.root","r")
    fVV=ROOT.TFile("output_emu_"+options.year+"/VV2L2Nu.root","r")
    fDY=ROOT.TFile("output_emu_"+options.year+"/DYall.root","r")
    fZG=ROOT.TFile("output_emu_"+options.year+"/ZG.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/nonprompt.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):
       jj =j
       if j==1 or j==2: jj=0
       if j==4 or j==5: jj=3
       if j==7 or j==8: jj=6

       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

	  hPF=fData.Get("em_"+str(j)+"_anti1/data_obs"+postfix).Clone()
          hPF.Add(fWZ.Get("em_"+str(j)+"_anti1/WZ3LNu"),-1)
          hPF.Add(fZZ.Get("em_"+str(j)+"_anti1/ZZ4L"),-1)
          hPF.Add(fTT.Get("em_"+str(j)+"_anti1/TTTo2L2Nu"),-1)
          hPF.Add(fVV.Get("em_"+str(j)+"_anti1/VV2L2Nu"),-1)
          hPF.Add(fDY.Get("em_"+str(j)+"_anti1/DY"),-1)
          hPF.Add(fZG.Get("em_"+str(j)+"_anti1/ZG"),-1)

          hFP=fData.Get("em_"+str(j)+"_anti2/data_obs"+postfix).Clone()
          hFP.Add(fWZ.Get("em_"+str(j)+"_anti2/WZ3LNu"),-1)
          hFP.Add(fZZ.Get("em_"+str(j)+"_anti2/ZZ4L"),-1)
          hFP.Add(fTT.Get("em_"+str(j)+"_anti2/TTTo2L2Nu"),-1)
          hFP.Add(fVV.Get("em_"+str(j)+"_anti2/VV2L2Nu"),-1)
          hFP.Add(fDY.Get("em_"+str(j)+"_anti2/DY"),-1)
          hFP.Add(fZG.Get("em_"+str(j)+"_anti2/ZG"),-1)

          hFF=fData.Get("em_"+str(j)+"_anti0/data_obs"+postfix).Clone()
          hFF.Add(fWZ.Get("em_"+str(j)+"_anti0/WZ3LNu"),-1)
          hFF.Add(fZZ.Get("em_"+str(j)+"_anti0/ZZ4L"),-1)
          hFF.Add(fTT.Get("em_"+str(j)+"_anti0/TTTo2L2Nu"),-1)
          hFF.Add(fVV.Get("em_"+str(j)+"_anti0/VV2L2Nu"),-1)
          hFF.Add(fDY.Get("em_"+str(j)+"_anti0/DY"),-1)
          hFF.Add(fZG.Get("em_"+str(j)+"_anti0/ZG"),-1)

          h0=hPF.Clone()
          h0.Add(hFP)
          h0.Add(hFF,-1)
   
          #if (hPF.Integral()<hFF.Integral() or hFP.Integral()<hFF.Integral()):
          #   h0=hFF.Clone()
	  for k in range(1,hPF.GetSize()):
	     if hPF.GetBinContent(k)+hFP.GetBinContent(k)<hFF.GetBinContent(k): h0.SetBinContent(k,hFF.GetBinContent(k))



	  # take relax shape
	  if is_control==3:

             hPFR=fData.Get("em_"+str(jj)+"_relaxanti1/data_obs"+postfix).Clone()
             hPFR.Add(fWZ.Get("em_"+str(jj)+"_relaxanti1/WZ3LNu"),-1)
             hPFR.Add(fZZ.Get("em_"+str(jj)+"_relaxanti1/ZZ4L"),-1)
             hPFR.Add(fTT.Get("em_"+str(jj)+"_relaxanti1/TTTo2L2Nu"),-1)
             hPFR.Add(fVV.Get("em_"+str(jj)+"_relaxanti1/VV2L2Nu"),-1)
             hPFR.Add(fDY.Get("em_"+str(jj)+"_relaxanti1/DY"),-1)
             hPFR.Add(fZG.Get("em_"+str(jj)+"_relaxanti1/ZG"),-1)

             hFPR=fData.Get("em_"+str(jj)+"_relaxanti2/data_obs"+postfix).Clone()
             hFPR.Add(fWZ.Get("em_"+str(jj)+"_relaxanti2/WZ3LNu"),-1)
             hFPR.Add(fZZ.Get("em_"+str(jj)+"_relaxanti2/ZZ4L"),-1)
             hFPR.Add(fTT.Get("em_"+str(jj)+"_relaxanti2/TTTo2L2Nu"),-1)
             hFPR.Add(fVV.Get("em_"+str(jj)+"_relaxanti2/VV2L2Nu"),-1)
             hFPR.Add(fDY.Get("em_"+str(jj)+"_relaxanti2/DY"),-1)
             hFPR.Add(fZG.Get("em_"+str(jj)+"_relaxanti2/ZG"),-1)

             hFFR=fData.Get("em_"+str(jj)+"_relaxanti0/data_obs"+postfix).Clone()
             hFFR.Add(fWZ.Get("em_"+str(jj)+"_relaxanti0/WZ3LNu"),-1)
             hFFR.Add(fZZ.Get("em_"+str(jj)+"_relaxanti0/ZZ4L"),-1)
             hFFR.Add(fTT.Get("em_"+str(jj)+"_relaxanti0/TTTo2L2Nu"),-1)
             hFFR.Add(fVV.Get("em_"+str(jj)+"_relaxanti0/VV2L2Nu"),-1)
             hFFR.Add(fDY.Get("em_"+str(jj)+"_relaxanti0/DY"),-1)
             hFFR.Add(fZG.Get("em_"+str(jj)+"_relaxanti0/ZG"),-1)

             h0R=hPFR.Clone()
             h0R.Add(hFPR)
             h0R.Add(hFFR,-1)

             #if (hPFR.Integral()<hFF.Integral() or hFPR.Integral()<hFFR.Integral()):
             #   h0R=hFFR.Clone()
             for k in range(1,hPFR.GetSize()):
                if hPFR.GetBinContent(k)+hFPR.GetBinContent(k)<hFFR.GetBinContent(k): h0R.SetBinContent(k,hFFR.GetBinContent(k))



          fout.cd()
          dir0.cd()
	  if is_control==3 and (j==0 or j==1 or j==3 or j==4 or j==6 or j==7):
            h0R.SetName("nonprompt"+postfix)
  	    h0R.Scale(h0.Integral()/h0R.Integral())
            h0R.Write()
	  else:
            h0.SetName("nonprompt"+postfix)
            h0.Write()


    for j in range(0,ncat):
       jj =j
       if j==1 or j==2: jj=0
       if j==4 or j==5: jj=3
       if j==7 or j==8: jj=6

       dir1=fout.mkdir("em_"+str(j)+"_OS")

       for k in range(0,nbhist):
          postfix=postfixName[k]

          h1PF=fData.Get("em_"+str(j)+"_OS_anti1/data_obs"+postfix).Clone()
          h1PF.Add(fWZ.Get("em_"+str(j)+"_OS_anti1/WZ3LNu"),-1)
          h1PF.Add(fZZ.Get("em_"+str(j)+"_OS_anti1/ZZ4L"),-1)
          h1PF.Add(fTT.Get("em_"+str(j)+"_OS_anti1/TTTo2L2Nu"),-1)
          h1PF.Add(fVV.Get("em_"+str(j)+"_OS_anti1/VV2L2Nu"),-1)
          h1PF.Add(fDY.Get("em_"+str(j)+"_OS_anti1/DY"),-1)
          h1PF.Add(fZG.Get("em_"+str(j)+"_OS_anti1/ZG"),-1)

          h1FP=fData.Get("em_"+str(j)+"_OS_anti2/data_obs"+postfix).Clone()
          h1FP.Add(fWZ.Get("em_"+str(j)+"_OS_anti2/WZ3LNu"),-1)
          h1FP.Add(fZZ.Get("em_"+str(j)+"_OS_anti2/ZZ4L"),-1)
          h1FP.Add(fTT.Get("em_"+str(j)+"_OS_anti2/TTTo2L2Nu"),-1)
          h1FP.Add(fVV.Get("em_"+str(j)+"_OS_anti2/VV2L2Nu"),-1)
          h1FP.Add(fDY.Get("em_"+str(j)+"_OS_anti2/DY"),-1)
          h1FP.Add(fZG.Get("em_"+str(j)+"_OS_anti2/ZG"),-1)

          h1FF=fData.Get("em_"+str(j)+"_OS_anti0/data_obs"+postfix).Clone()
          h1FF.Add(fWZ.Get("em_"+str(j)+"_OS_anti0/WZ3LNu"),-1)
          h1FF.Add(fZZ.Get("em_"+str(j)+"_OS_anti0/ZZ4L"),-1)
          h1FF.Add(fTT.Get("em_"+str(j)+"_OS_anti0/TTTo2L2Nu"),-1)
          h1FF.Add(fVV.Get("em_"+str(j)+"_OS_anti0/VV2L2Nu"),-1)
          h1FF.Add(fDY.Get("em_"+str(j)+"_OS_anti0/DY"),-1)
          h1FF.Add(fZG.Get("em_"+str(j)+"_OS_anti0/ZG"),-1)

          h1=h1PF.Clone()
          h1.Add(h1FP)
          h1.Add(h1FF,-1)

          #if (h1PF.Integral()<h1FF.Integral() or h1FP.Integral()<h1FF.Integral()):
          #   h1=h1FF.Clone()

          for k in range(1,h1PF.GetSize()):
             if h1PF.GetBinContent(k)+h1FP.GetBinContent(k)<h1FF.GetBinContent(k): h1.SetBinContent(k,h1FF.GetBinContent(k))

	  if is_control==3:

             h1PFR=fData.Get("em_"+str(jj)+"_OS_relaxanti1/data_obs"+postfix).Clone()
             h1PFR.Add(fWZ.Get("em_"+str(jj)+"_OS_relaxanti1/WZ3LNu"),-1)
             h1PFR.Add(fZZ.Get("em_"+str(jj)+"_OS_relaxanti1/ZZ4L"),-1)
             h1PFR.Add(fTT.Get("em_"+str(jj)+"_OS_relaxanti1/TTTo2L2Nu"),-1)
             h1PFR.Add(fVV.Get("em_"+str(jj)+"_OS_relaxanti1/VV2L2Nu"),-1)
             h1PFR.Add(fDY.Get("em_"+str(jj)+"_OS_relaxanti1/DY"),-1)
             h1PFR.Add(fZG.Get("em_"+str(jj)+"_OS_relaxanti1/ZG"),-1)

             h1FPR=fData.Get("em_"+str(jj)+"_OS_relaxanti2/data_obs"+postfix).Clone()
             h1FPR.Add(fWZ.Get("em_"+str(jj)+"_OS_relaxanti2/WZ3LNu"),-1)
             h1FPR.Add(fZZ.Get("em_"+str(jj)+"_OS_relaxanti2/ZZ4L"),-1)
             h1FPR.Add(fTT.Get("em_"+str(jj)+"_OS_relaxanti2/TTTo2L2Nu"),-1)
             h1FPR.Add(fVV.Get("em_"+str(jj)+"_OS_relaxanti2/VV2L2Nu"),-1)
             h1FPR.Add(fDY.Get("em_"+str(jj)+"_OS_relaxanti2/DY"),-1)
             h1FPR.Add(fZG.Get("em_"+str(jj)+"_OS_relaxanti2/ZG"),-1)

             h1FFR=fData.Get("em_"+str(jj)+"_OS_relaxanti0/data_obs"+postfix).Clone()
             h1FFR.Add(fWZ.Get("em_"+str(jj)+"_OS_relaxanti0/WZ3LNu"),-1)
             h1FFR.Add(fZZ.Get("em_"+str(jj)+"_OS_relaxanti0/ZZ4L"),-1)
             h1FFR.Add(fTT.Get("em_"+str(jj)+"_OS_relaxanti0/TTTo2L2Nu"),-1)
             h1FFR.Add(fVV.Get("em_"+str(jj)+"_OS_relaxanti0/VV2L2Nu"),-1)
             h1FFR.Add(fDY.Get("em_"+str(jj)+"_OS_relaxanti0/DY"),-1)
             h1FFR.Add(fZG.Get("em_"+str(jj)+"_OS_relaxanti0/ZG"),-1)

             h1R=h1PFR.Clone()
             h1R.Add(h1FPR)
             h1R.Add(h1FFR,-1)

             #if (h1PFR.Integral()<h1FFR.Integral() or h1FPR.Integral()<h1FFR.Integral()):
             #   h1R=h1FFR.Clone()

             for k in range(1,h1PFR.GetSize()):
                if h1PFR.GetBinContent(k)+h1FPR.GetBinContent(k)<h1FFR.GetBinContent(k): h1R.SetBinContent(k,h1FFR.GetBinContent(k))



          fout.cd()
          dir1.cd()
          if is_control==3 and (j==0 or j==1 or j==3 or j==4 or j==6 or j==7):
            h1R.SetName("nonprompt"+postfix)
            h1R.Scale(h1.Integral()/h1R.Integral())
            h1R.Write()
          else:
            h1.SetName("nonprompt"+postfix)
            h1.Write()



