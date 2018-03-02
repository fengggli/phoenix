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
        if [ ! -d ${app}_datafiles ]; then
            echo "[INFO]: extract data for $app ... "
            tar -xzf $app.tar.gz
        fi
    done


    # additional data
    # only support 24bit bmp
    wget -P histogram_datafiles http://www.fileformat.info/format/bmp/sample/c192761f189c41e09485ef87e8098b9c/XING_B24.BMP
fi





