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
       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

          hFF=fData.Get("em_"+str(j)+"_anti0/data_obs"+postfix).Clone()
          hFF.Add(fWZ.Get("em_"+str(j)+"_anti0/WZ3LNu"),-1)
          hFF.Add(fZZ.Get("em_"+str(j)+"_anti0/ZZ4L"),-1)
          hFF.Add(fTT.Get("em_"+str(j)+"_anti0/TTTo2L2Nu"),-1)
          hFF.Add(fVV.Get("em_"+str(j)+"_anti0/VV2L2Nu"),-1)
          hFF.Add(fDY.Get("em_"+str(j)+"_anti0/DY"),-1)
          hFF.Add(fZG.Get("em_"+str(j)+"_anti0/ZG"),-1)

          h0=hFF.Clone()
   
          fout.cd()
          dir0.cd()
          h0.SetName("nonprompt"+postfix)
          h0.Write()


    for j in range(0,ncat):
       dir1=fout.mkdir("em_"+str(j)+"_OS")

       for k in range(0,nbhist):
          postfix=postfixName[k]

          h1FF=fData.Get("em_"+str(j)+"_OS_anti0/data_obs"+postfix).Clone()
          h1FF.Add(fWZ.Get("em_"+str(j)+"_OS_anti0/WZ3LNu"),-1)
          h1FF.Add(fZZ.Get("em_"+str(j)+"_OS_anti0/ZZ4L"),-1)
          h1FF.Add(fTT.Get("em_"+str(j)+"_OS_anti0/TTTo2L2Nu"),-1)
          h1FF.Add(fVV.Get("em_"+str(j)+"_OS_anti0/VV2L2Nu"),-1)
          h1FF.Add(fDY.Get("em_"+str(j)+"_OS_anti0/DY"),-1)
          h1FF.Add(fZG.Get("em_"+str(j)+"_OS_anti0/ZG"),-1)

          h1=h1FF.Clone()

          fout.cd()
          dir1.cd()
          h1.SetName("nonprompt"+postfix)
          h1.Write()



