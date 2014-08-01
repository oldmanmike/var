# Very crude base counter
# Michael Carpenter
import subprocess

fn = 'test.fa' # insert filename in question
tmp = 'tmp.dat'
print "Opening..."
f = open(fn)
sequence = []
for line in f:
  if not ">" in line:
    sequence.append(line)
f.close()

print "Cleaning..."
f = open(tmp, 'w')
f.writelines(sequence)
f.close()

print "Reading..."
in_file = open(tmp, "r")
text = in_file.read()
in_file.close()

print "Analyzing..."
totalnum = len(text)
Anum = float(text.count('A'))
Tnum = float(text.count('T'))
Cnum = float(text.count('C'))
Gnum = float(text.count('G'))
other = float(totalnum - Anum - Tnum - Cnum - Gnum)

Apercent      = ("%.3f" % ((Anum / totalnum) * 100))
Tpercent      = ("%.3f" % ((Tnum / totalnum) * 100))
Cpercent      = ("%.3f" % ((Cnum / totalnum) * 100))
Gpercent      = ("%.3f" % ((Gnum / totalnum) * 100))
Otherpercent  = ("%.3f" % ((other / totalnum) * 100))

print "======================================"
print "Total:       ", totalnum
print "Number of A: ", Anum
print "Number of T: ", Tnum
print "Number of C: ", Cnum
print "Number of G: ", Gnum
print "Others:      ", other
print "% of A:      ", str(Apercent) + "%"
print "% of T:      ", str(Tpercent) + "%"
print "% of C:      ", str(Cpercent) + "%"
print "% of G:      ", str(Gpercent) + "%"
print "% of Others: ", str(Otherpercent) + "%"
print "======================================"
print "GC Content:  ", (Gpercent + Cpercent)
print "======================================"
