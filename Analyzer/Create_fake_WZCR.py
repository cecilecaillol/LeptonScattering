if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=1

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    parser.add_argument('--channel')
    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[""]

    nbhist=1 

    fZZ=ROOT.TFile("output_WZ"+options.channel+"CR_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_WZ"+options.channel+"CR_"+options.year+"/WZ3LNu.root","r")
    fData=ROOT.TFile("output_WZ"+options.channel+"CR_"+options.year+"/Data.root","r")
    fout=ROOT.TFile("output_WZ"+options.channel+"CR_"+options.year+"/nonprompt.root","recreate")

    ncat=9

    for j in range(0,ncat):
       dir0=fout.mkdir("wz"+options.channel+"cr_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

	  hPF=fData.Get("wz"+options.channel+"cr_"+str(j)+"_anti/data_obs"+postfix).Clone()
          hPF.Add(fWZ.Get("wz"+options.channel+"cr_"+str(j)+"_anti/WZ3LNu"),-1)
          hPF.Add(fZZ.Get("wz"+options.channel+"cr_"+str(j)+"_anti/ZZ4L"),-1)

          fout.cd()
          dir0.cd()
          hPF.SetName("nonprompt"+postfix)
          hPF.Write()


