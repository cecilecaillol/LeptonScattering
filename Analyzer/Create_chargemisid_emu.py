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
    #fTop=ROOT.TFile("output_emu_"+options.year+"/top.root","r")
    #fDY=ROOT.TFile("output_emu_"+options.year+"/DY.root","r")
    fData=ROOT.TFile("output_emu_"+options.year+"/MuonEG.root","r")
    fout=ROOT.TFile("output_emu_"+options.year+"/chargemisid.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):

       dir0=fout.mkdir("em_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]
          #print postfix
          h0=fData.Get("em_"+str(j)+"_OS_anti0/data_obs"+postfix)
          h0.Add(fWZ.Get("em_"+str(j)+"_OS_anti0/WZ3LNu"),-1)
          h0.Add(fZZ.Get("em_"+str(j)+"_OS_anti0/ZZ4L"),-1)
          #h0.Add(fDY.Get("em_"+str(j)+"_anti/ZTT"),-1)
          #h0.Add(fTop.Get("em_"+str(j)+"_anti/top"),-1)
          h0.Scale(0.0001) #FIXME

          fout.cd()
          dir0.cd()
          h0.SetName("chargemisid"+postfix)
          h0.Write()


