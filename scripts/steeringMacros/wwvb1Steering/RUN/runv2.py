import subprocess
import sys
def bash( bashCommand ):
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        #process = subprocess.Popen(bashCommand.split())
        output, error = process.communicate()
        return output ,error


#path = args[0]

#need path RunLogs and Root files
#need path to xml
xml = sys.argv[1]
pathrunlog = sys.argv[2]
dataset = sys.argv[3]
print "starting run with", xml, pathrunlog
bash('rm '+pathrunlog+dataset+'.out.gz')
log = bash('Marlin '+xml)
file = open(pathrunlog+dataset+'.out','w')
file.write(log[0])
bash('gzip '+pathrunlog+dataset+'.out')




