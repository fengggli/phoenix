#!/usr/bin/env bash
# get data 

# First created: 2018 Mar 01
# Last modified: 2018 Mar 01

# Author: Feng Li
# email: fengggli@yahoo.com

if [ ! -d scripts ];then
    echo "ERR:run it in project root as scripts/$0"
else
    mkdir -pv data
    cd data
    for app in linear_regression string_match reverse_index word_count histogram; do
        echo "[INFO]: fetch data for $app "
        if [ ! -f $app.tar.gz ]; then
            wget "http://csl.stanford.edu/~christos/data/$app.tar.gz"
        fi
        echo "[INFO]: extract data for $app ... "
        tar -xzf $app.tar.gz
    done
fi





