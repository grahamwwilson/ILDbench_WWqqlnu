#!/bin/sh

VERSION=$1

scp wilson@naf-ilc.desy.de:~/mydust/WWBenchmark/vb1/4f_singleW_semileptonic/4f_singleW_semileptonic.out.gz 4f_singleW_V${VERSION}.out.gz
scp wilson@naf-ilc.desy.de:~/mydust/WWBenchmark/vb1/4f_singleW_semileptonic/4f_singleW_semileptonicfile.root 4f_singleW_V${VERSION}.root

exit
