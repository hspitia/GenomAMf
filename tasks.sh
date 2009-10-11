#! /bin/sh

make clean
rm app
rm tmp/*.png
tar -zcvf ../GenomAMf_$1.tar.gz ../GenomAMf