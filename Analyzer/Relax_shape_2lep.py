if __name__ == "__main__":

    import ROOT
    import argparse

    is_control=1

    parser = argparse.ArgumentParser()
    parser.add_argument('--year')
    parser.add_argument('--process')
    options = parser.parse_args()

    year4=options.year
    if options.year=="2016pre": year4="2016preVFP"
    if options.year=="2016post": year4="2016postVFP"

    postfixName=[""]

    nbhist=1 

    fin=ROOT.TFile("output_2lep_"+options.year+"/"+options.process+".root","r")
    fout=ROOT.TFile("output_2lep_"+options.year+"/"+options.process+"_relaxed.root","recreate")

    ncat=9
    if is_control==0: 
	ncat=9
        nbhist=1

    for j in range(0,ncat):
       dir0=fout.mkdir("em2l_"+str(j))

       for k in range(0,nbhist):
          postfix=postfixName[k]

          h2=fin.Get("em2l_"+str(j)+"/DY"+postfix)
          h1=fin.Get("em2lR_"+str(j)+"/DY"+postfix).Clone()
          SF=h2.Integral()/(h1.Integral()+0.001)
          h1.Scale(SF)

          fout.cd()
          dir0.cd()
          h1.SetName("DY"+postfix)
          h1.Write()


