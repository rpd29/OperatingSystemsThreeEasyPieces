#Script to run TLB test for various values of page touches

from zplot import * #Import zplot graphing module
import subprocess #Import subprocess module to enable running other programs from this script

#Run TLB tests and save resulting data to a file
with open("/Users/ravi_deedwania/Documents/OSTEP/Code/Chapter_19/data.txt","w") as data: #Create and open file to store data from tests
	data.write("# num_pages avg_access_time\n") #Write schema for table to data file
	max_num_pages = 1500 #Maximum number of pages to touch (plus one)
	num_trials = 1000 #Number of trials to run for each number of page touches
	page_size = 4096 #Page size of computer being tested
	
	for num_pages in range(1, max_num_pages): #Loop over various numbers of page touches for TLB test and record results in data document
		avg_access_time = subprocess.check_output("/Users/ravi_deedwania/Documents/OSTEP/Code/Chapter_19/tlb " + str(num_pages) + " " + str(num_trials) + " " + str(page_size), shell = True) #Run TLB test program and capture output (average access time)
		data.write(str(num_pages) + " " + str(avg_access_time) + "\n") #Write data to data file


#Graph the data

#Describe drawing surface
ctype = 'eps'
c = canvas(ctype, title="TLB test", dimensions=['5in', '5in'])

#Load data into a table
t = table(file="/Users/ravi_deedwania/Documents/OSTEP/Code/Chapter_19/data.txt") 

#Make a drawable region on canvas for the graph
d = drawable(canvas = c, xrange = [0,max_num_pages], yrange = [0,30], coord = ['0.5in','0.5in'], dimensions = ['4.0in','4.0in'])

#Make axes
axis(drawable = d, title = "TLB Size Measurement", xtitle = "Number of Pages", ytitle = "Average Time Per Access (ns)", xauto = [0, max_num_pages, 200])

#Plot points
p = plotter()
p.line(drawable = d, table = t, xfield='num_pages', yfield = 'avg_access_time', linecolor='black')

#output the graph to a file
c.render()




