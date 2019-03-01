######################################### HEP - PUCP #################################################################################
######################################################################################################################################
###This script takes the number of total events in the files added and graphs it as a function of the assigned parameter in the x axis
######################################################################################################################################
######################################################################################################################################

import ROOT
from ROOT import *
import sys
from optparse import OptionParser
import time
import math
from ROOT import  gStyle
from array import array
from decimal import getcontext, Decimal
#from numpy import *

gROOT.Reset()
#Write one or several file names
name=["file1.txt","file2.txt","filex.txt"]

list1=[[] for i in range (len(name1))]
rows1,cols1=[],[]
for i in range (len(name)):
	with open(name[i]) as f8:
		f8 = f8.readlines()
	#Make a cut according to criteria
	#f8 = f8[:] 
	for line in f8:
        	list1[i].append([float(x) for x in line.split()])
	rows1.append(len(list1[i]))
	cols1.append(len(list1[i][0]))

#To add xaxis values by hand
#xaxis=array('f',[0.5,1.5,2.5,3.5,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10.0,11.0,12.0,13.0])

#To assign xaxis values from the files
xaxis=array('f')

erx=array('f',[0.05 for i in range(len(name2))]) #Point errors on the x axis

yaxis=array('f')
ery=array('f')

for i in range(len(name)):
	yaxis.append(rows1[i])
	ery.append(sqrt(yaxis[i])) #The error defined as the statistic

#For normalization
norm=yaxis[0] #This is a normalization with the first point in the graph, can be changed to criteria
for i in range(len(yaxis)):
	yaxis[i]=yaxis[i]/norm
	ery[i]=ery[i]/norm


c1 = TCanvas( 'c1', 'Graph', 2000, 1500 )
c1.SetGrid()
gStyle.SetTitleFontSize(0.08)

#gr=TGraph(len(yaxis),xaxis,yaxis) #For a graph without errors
gr=TGraphErrors(len(yaxis),xaxis,yaxis,erx,ery)
gr.SetLineColor( 45 )
gr.SetLineWidth( 1 )
gr.SetMarkerColor( 50 )
gr.SetMarkerSize( 0.5 )
gr.SetMarkerStyle( 21 )


#For fitting 
f1=TF1("F1","[0]/x**2") #Write the formula for fitting, assigning the parameters to be defineed
f1.SetLineColor(4)
gr.Fit("F1")
chi2=gr.GetFunction("F1").GetChisquare()
ndf=gr.GetFunction("F1").GetNDF()

grTot1=TMultiGraph()

grTot1.Add(gr,"cp")
leg1 = TLegend(0.65,0.7,0.9,0.9);
leg1.AddEntry(gr,"Label", "lp")

grTot1.SetTitle("Graph Title; x axis label [units] ; y axis label [units]")
grTot1.Draw("ACP")
grTot1.GetYaxis().SetTitleOffset(1.1)
#grTot1.GetYaxis().SetRangeUser(0.3,0.55)
grTot1.GetXaxis().SetTitleOffset(0.85)
#grTot1.GetXaxis().SetRangeUser(0,20)

leg1.Draw()
closeInput = raw_input("Press ENTER to exit")
print "Closing..."
