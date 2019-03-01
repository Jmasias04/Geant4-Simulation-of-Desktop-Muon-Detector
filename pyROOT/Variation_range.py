######################################### HEP - PUCP #################################################################################
######################################################################################################################################
###This script takes every event and graphs its (instant or averaged over a specified period of time) rate as a function of time. 
###Times are in ms. 
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
name=["filename.txt"]
list1=[]

with open(name[0]) as f8:
	f8 = f8.readlines()
f8 = f8[6:]
for line in f8:
	list1.append([float(x) for x in line.split()])
rows=len(list1)
cols=len(list1[0])


#For an overall calculation
time=list1[rows-1][1]-list1[0][1]
deadtime=0

for i in range(rows):
	deadtime=deadtime+list1[i][4]

rate=rows*1000/(time-deadtime)
error1=math.sqrt(rows)*1000/(time-deadtime)

'''#For graphing the average rate

timeint=1*60*60*1000 #Assign a time period in ms
auxdead=0
deadtimes=[]
auxevt=0
events=[]
auxtime= list1[0][1] #This is the time of the first event 
times=[]

for i in range(rows):
	auxdead=auxdead+list1[i][4]
	if list1[i][1]>=auxtime+timeint:
		events.append(list1[i][0]-auxevt)
		auxevt=list1[i][0]
		times.append(list1[i][1]-auxtime)
		auxtime=list1[i][1]
		deadtimes.append(auxdead)
		auxdead=0
events.append(list1[rows-1][0]-auxevt)
times.append(list1[rows-1][1]-auxtime)
deadtimes.append(auxdead)
rates=array('d')
xAxis=array('d')			
for i in range(len(events)):
	rates.append(events[i]*1000/(times[i]-deadtimes[i]))
	xAxis.append((i+1)*timeint)
mean=TMath.Mean(len(rates),rates)
meanline=array('d',[mean for i in range(len(events))])

gr=TGraph(len(xAxis),xAxis,rates)
''''


#For graphing instant rate

auxdead=0
deadtimes=[]
auxtime= list1[0][1]
times=array('d')

for i in range(rows):
	auxdead=auxdead+list1[i][4]
	deadtimes.append(auxdead)
	times.append(list1[i][1])
print "number of times", len(times)	
rates=array('d')			
for i in range(len(times)):
	rates.append((i+1)*1000/(times[i]-deadtimes[i]))
	
mean=TMath.Mean(len(rates),rates)

gr=TGraph(len(times),times,rates)



c1 = TCanvas( 'c1', 'Graph', 200, 10, 700, 500 )
c1.SetGrid()

gr.SetLineColor( 48 )
gr.SetLineWidth( 1 )
gr.SetMarkerColor( 46 )
gr.SetMarkerSize( 0.7 )
gr.SetMarkerStyle( 21 )

grm=TGraph(len(xAxis),xAxis,meanline)
grm.SetLineColor( 8 )
grm.SetLineWidth( 2 )
grm.SetLineStyle( 1 )

grTot=TMultiGraph()

c1.Update()
c1.GetFrame().SetFillColor( 21 )
c1.GetFrame().SetBorderSize( 12 )
c1.Modified()

grTot.Add(gr,"lp")
grTot.Add(grm,"l")
grTot.SetTitle("Rate vs Time ; Time [units] ; Rate[1/s]")
grTot.Draw("ALP")

leg = TLegend(0.60,0.7,.9,.90);
leg.AddEntry(grm,"Mean=" + str(mean) , "l")
leg.AddEntry(gr1,"Error (statistic) = " + str(rounderror1), "l")
leg.Draw()

c1.Update()
closeInput = raw_input("Press ENTER to exit")
print "Closing..."
