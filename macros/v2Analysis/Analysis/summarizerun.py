


##input tables
import sys

table = sys.argv[1]
tableT = sys.argv[2]
ofilename = sys.argv[3]
BGtightnum = 0.
BGbothnum = 0.

Stightnum =0.
Stighteff = 0.
Stightpure = 0.

SOStightnum =0.
SOStighteff = 0.
SOStightpure = 0.

#BGbothnum=0.

Sbothnum = 0.
Sbotheff =0.
Sbothpure = 0.

SOSbothnum = 0.
SOSbotheff = 0.
SOSbothpure = 0.

ifile = open(table, "r")
lines = ifile.readlines()
for line in lines:
	line = line.split()
	if(line[0] == '**'):
		if(line[1] == 'allBG'):#number start at index 2
			BGtightnum = float( line[2] )

		if(line[1] == 'S'):
			Stightnum = float( line[2] )
			Stighteff = float( line[4] )
			Stightpure = float( line[5] )


		if(line[1] == 'SOS'):
			SOStightnum = float( line[2] )
			SOStighteff = float(line [4] )
			SOStightpure = float(line[5] )
ifile.close()

ifile = open(tableT, "r")
lines = ifile.readlines()
for line in lines:
        line = line.split()
        if(line[0] == '**'):
                if(line[1] == 'allBG'):#number start at index 2
                        BGbothnum = float( line[2] ) + BGtightnum
                
                if(line[1] == 'S'):             
                        Sbothnum = float( line[2] ) + Stightnum
                        Sbotheff = float( line[4] ) + Stighteff
                       ## Sbothpure = float( line[5] )
			Sbothpure = Sbothnum/(Sbothnum + BGbothnum)
                
                
                if(line[1] == 'SOS'):           
                        SOSbothnum = float( line[2] ) + SOStightnum
                        SOSbotheff = float(line [4] ) + SOStighteff
                      ##  SOSbothpure = float(line[5] ) 	
			SOSbothpure = SOSbothnum/(SOSbothnum + BGbothnum)


#make a new file
ofile = open(ofilename,"w")
ofile.write( " \\begin{tabular}{ |p{0.08\\textwidth}|p{0.08\\textwidth}p{0.08\\textwidth}|p{0.08\\textwidth}|p{0.08\\textwidth}p{0.08\\textwidth}p{0.08\\textwidth}|} \n")
ofile.write(" \\hline \n")
ofile.write("   &  \\multicolumn{3}{|l|}{Tight Selection} &  \\multicolumn{3}{|l|}{ Tight + Loose Sel.}  \\\\ ")
ofile.write(" \\hline  \n")
ofile.write(" & Sel. Total & Efficiency & Purity & Sel. Total & Efficiency & Purity \\\\ \n")
ofile.write(" \\hline  \n")
ofile.write(" Bkg. & {:.3g} & & & {:.3g} & &  \\\\ \n".format(BGtightnum,BGbothnum))
ofile.write(" Signal & {:.3g} & {:.3g} & {:.3g} & {:.3g} & {:.3g} & {:.3g} \\\\ \n".format(Stightnum,Stighteff,Stightpure,Sbothnum,Sbotheff,Sbothpure))
ofile.write(" Sig.+O.S. & {:.3g} & {:.3g} & {:.3g} & {:.3g} & {:.3g} & {:.3g} \\\\ \n".format(SOStightnum,SOStighteff,SOStightpure,SOSbothnum,SOSbotheff,SOSbothpure))
ofile.write("\\hline \n")
ofile.write("\\end{tabular} \n")





