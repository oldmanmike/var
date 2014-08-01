#!/usr/bin/python2
#####################################################################
# File:         metadata.py                                         #
# Group:        Michael Carpenter, Laura Corichi                    #
# Class:        Bioinformatics                                      #
# Date:         28/3/13                                             #
# Description:  A python script that takes a given set of .fa files #
#               and calculates various properties about them.       #
#####################################################################

import sys

scaffold_num  = 0
assembled     = [0]
n50           = [0]
avg_size      = [0]
max_size      = [0]
gc_content    = [0]

for arg in range(1, len(sys.argv)):
  f = open(sys.argv[arg])
  
  scaffold_size = []
  genome        = ''
  scaffold      = ''
  scaffold_num  = 0
  maximum       = 0

  for line in f:
    if not ">" in line:
      scaffold = scaffold + line.strip('\n')
    elif ">" in line:
      scaffold_num = scaffold_num + 1
      if len(scaffold) > maximum:
        maximum = len(scaffold)
      genome = genome + scaffold
      scaffold_size.append(len(scaffold))
      scaffold = ''
  genome = genome + scaffold
  scaffold_size.append(len(scaffold))

  squares = [x**2 for x in scaffold_size]
  squares.sort()

  Gnum = float(genome.count('G'))
  Cnum = float(genome.count('C'))
  Gpercent = ("%.3f" % ((Gnum / len(genome)) * 100))
  Cpercent = ("%.3f" % ((Cnum / len(genome)) * 100))
  GCpercent = float(Gpercent) + float(Cpercent)

  assembled.append(len(genome))
  n50.append(squares[len(squares) / 2])
  avg_size.append(len(genome) / scaffold_num)
  max_size.append(maximum)
  gc_content.append(GCpercent)

  f.close()
  
###############################################
print "Sequence file: \t\t",
for arg in range(1, len(sys.argv)):
  print str(sys.argv[arg]).rjust(9),
print ""
###############################################
print "Assembled Genome Size: \t",
for arg in range(1, len(sys.argv)):
  print str(assembled[arg]).rjust(9),
print ""
###############################################
print "Scaffold Size N50: \t",
for arg in range(1, len(sys.argv)):
  print str(n50[arg]).rjust(9),
print ""
###############################################
print "Avg. Scaffold Size: \t",
for arg in range(1, len(sys.argv)):
  print str(avg_size[arg]).rjust(9),
print ""
###############################################
print "Max. Scaffold Size: \t",
for arg in range(1, len(sys.argv)):
  print str(max_size[arg]).rjust(9),
print ""
###############################################
print "GC content: \t\t",
for arg in range(1, len(sys.argv)):
  print str(gc_content[arg]).rjust(9),
print ""
###############################################
