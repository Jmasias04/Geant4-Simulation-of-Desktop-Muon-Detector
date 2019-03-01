######################################### HEP - PUCP #################################################################################
######################################################################################################################################
###This script makes one or several histograms from the files added.
######################################################################################################################################
######################################################################################################################################

import ROOT
from ROOT import*
import sys
from optparse import OptionParser
import time
import math
from ROOT import  gStyle
from array import array

gROOT.Reset()
name=["file1.txt","file2.txt","filex.txt"]
arrvalmax,histogramas,historows, rows, cols, scale = [],[],[],[],[],[]
binwidth=2
length=len(name)

list1=[[] for i in range (length)]

print "list1",list1
for i in range (length):
	with open(name[i]) as f8:
		f8 = f8.readlines()
	#Make a cut according to criteria
	#f8 = f8[6:]
	for line in f8:
        	list1[i].append([float(x) for x in line.split()])
	rows.append(len(list1[i]))
	cols.append(len(list1[i][0]))

nrows=max(rows)
ncols=max(cols)

list2=[[[[]for i in range (nrows)]for j in range (ncols)] for k in range (length)]

for i in range (length-1):
	for j in list1[i]:	
		c=list1[i].index(j)
		for itemk in list1[i][c]:	
			k=list1[i][c].index(itemk)
			list2[i][k][c]=list1[i][c][k]
	for m in range (cols[i]):
		list2[i][m]=[x for x in list2[i][m] if x]			
	arrvalmax.append(max(list2[i][3]))
	
	rows[i]=len(list2[i])
	cols[i]=len(list2[i][0])

#Max SiPM Amplitude
valmax=max(arrvalmax)
valmax=math.ceil(valmax)

#Histograms
#If needed (when normalizing with integral)
integrals=[]
for i in range (length):
	histogramas.append(TH1F("hist "+str(i+1),"Histogram name",int(math.ceil(valmax/binwidth)),0,int(math.ceil(valmax/binwidth))*binwidth))
		
		for j in range (len(list2[i][3])):
			if list2[i][0][j]<=len(list2[i][3]): histogramas[i].Fill(list2[i][3][j]) #This indicates what parameter the histogram is for

	histogramas[i].SetLineWidth(2)	
	histogramas[i].Sumw2(kTRUE)

	#Normalizing with integral	
	scale.append(1.0/(histogramas[i].Integral()))
	histogramas[i].Scale(scale[i])

	#If needed	
	integrales.append(histogramas[i].Integral())
	
	'''#Rate- Normalizing with total time, should be changed
	scale.append(1000.0/list2[i][1][-1])
	histogramas[i].Scale(scale[i])
	'''
	'''#Normalizing with total counts, should be changed
	scale.append(1000.0/list2[i][0][-1])
	histogramas[i].Scale(scale[i])'''
	
	

	#Assigning color to histograms 
	histogramas[i].SetLineColor(i+8)		
	

c1 = TCanvas("c1","c1",2000,1500)
#Logarithmic scale
#c1.SetLogy(1)
c1.SetGrid()
c1.SetGridColor(0)
gStyle.SetOptStat(0)

 
gStyle.SetTitleAlign(33)

for i in range (length):
	if i == 0:
		histogramas[i].Draw("HIST E1") #To graph with error bars
		#histogramas[i].Draw("HIST")
	else:
		histogramas[i].Draw("HIST SAME E1")
		#histogramas[i].Draw("HIST SAME")

gPad.BuildLegend(0.65,0.75,0.9,0.9)
c1.Update()

#Modify title and labels as needed
histogramas[0].SetTitle("Title for all histograms")
histogramas[0].GetXaxis().CenterTitle()
histogramas[0].GetXaxis().SetTitle("X axis [units]")
histogramas[0].GetYaxis().SetTitle("Y axis [units]")
histogramas[0].GetXaxis().SetRangeUser(0,150)
histogramas[0].GetYaxis().SetRangeUser(0,0.2)
closeInput = raw_input("Press ENTER to exit")
print "Closing..."		
