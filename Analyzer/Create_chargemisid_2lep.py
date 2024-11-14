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

    fZZ=ROOT.TFile("output_2lep_"+options.year+"/ZZ4L.root","r")
    fWZ=ROOT.TFile("output_2lep_"+options.year+"/WZ3LNu.root","r")
    fZG=ROOT.TFile("output_2lep_"+options.year+"/ZG.root","r")
    fTTZ=ROOT.TFile("output_2lep_"+options.year+"/TTZ.root","r")
    fTTW=ROOT.TFile("output_2lep_"+options.year+"/TTW.root","r")
    fWWW=ROOT.TFile("output_2lep_"+options.year+"/WWW.root","r")
    fData=ROOT.TFile("output_2lep_"+options.year+"/Data.root","r")
    fout=ROOT.TFile("output_2lep_"+options.year+"/chargemisid.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):
       dir0=fout.mkdir("em2l_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

	  hOS=fData.Get("em2lOS_"+str(j)+"/data_obs"+postfix).Clone()
          hOS.Add(fWZ.Get("em2lOS_"+str(j)+"/WZ3LNu"),-1)
          hOS.Add(fZZ.Get("em2lOS_"+str(j)+"/ZZ4L"),-1)
          hOS.Add(fZG.Get("em2lOS_"+str(j)+"/VG"),-1)
          hOS.Add(fWWW.Get("em2lOS_"+str(j)+"/VVV"),-1)
          hOS.Add(fTTZ.Get("em2lOS_"+str(j)+"/TTV"),-1)
          hOS.Add(fTTW.Get("em2lOS_"+str(j)+"/TTV"),-1)

          fout.cd()
          dir0.cd()
          hOS.SetName("chargemisid"+postfix)
          hOS.Write()


