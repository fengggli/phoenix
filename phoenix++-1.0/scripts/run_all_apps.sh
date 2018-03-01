#!/usr/bin/env bash

# First created: 2018 Feb 15
# Last modified: 2018 Mar 01

# Author: Feng Li
# email: fengggli@yahoo.com

if [ ! -d build_guest ];then
    echo "ERR:run it in project root with build_debug in root/build_guest"
    exit -1
fi
if [ -z "$1" ]; then
    echo "cmd format: cmd result_dir"
    exit -1
else 
    OUTPUTDIR=`realpath $1`
    echo "results will be saved in $OUTPUTDIR"
    mkdir -p $OUTPUTDIR
fi

root_dir=`pwd`
BUILD_DIR=${root_dir}/build_guest

for type in std; do
    if [ $type == "std" ]; then
        exe_type=""
    else
        exe_type=_$type
    fi

#    if [ 1 = 2 ]; then ## test
    # kmeans
    echo ""
    echo "[info]:execute app kmeans with type type $exe_type"
    $BUILD_DIR/bin/kmeans${exe_type} &>$OUTPUTDIR/kmean_$type.log

    # histogram
    echo ""
    echo "[info]:execute app histogram with type type $exe_type"
    $BUILD_DIR/bin/histogram${exe_type} data/histogram_datafiles/small.bmp &>$OUTPUTDIR/histogram_$type.log
    
    echo ""
    echo "[info]:execute app linear regression with type type $exe_type"
    $BUILD_DIR/bin/linear_regression${exe_type} data/linear_regression_datafiles/key_file_100MB.txt &>$OUTPUTDIR/linear_regression_$type.log

    # matrix multiply
    echo ""
    echo "[info]:execute app matrix_multiply with type type $exe_type"
    side_matrix=1000 # size of matrix
    side_block=10 # size of the row block
    results_dir=${OUTPUTDIR}/matrix_multiply_${type}_${side_matrix}_${side_block}${exe_type}
    mkdir -pv $results_dir
    cd $results_dir

    $BUILD_DIR/bin/matrix_multiply${exe_type}  ${side_matix} $side_block  &>$OUTPUTDIR/matrix_mul_${type}_sm_${side_matrix}_sb_${side_block}.log
    cd $root_dir 

    #pca 
    echo ""
    echo "[info]:execute app pca with type type $exe_type"
    num_rows=10
    num_cols=10
    grid_size=100
    $BUILD_DIR/bin/pca${exe_type} -r ${num_rows} -c $num_cols -s $grid_size &>$OUTPUTDIR/pca_${type}_nr_${num_rows}_nc_${num_cols}_gz_${grid_size}.log
#fi

    #string match
    echo ""
    echo "[info]:execute app string match with type type $exe_type"
    $BUILD_DIR/bin/string_match${exe_type} data/string_match_datafiles/key_file_100MB.txt &> $OUTPUTDIR/string_match_$type.log

    #word_count
    echo ""
    echo "[info]:execute app word count  with type type $exe_type"
    $BUILD_DIR/bin/word_count${exe_type} data/word_count_datafiles/word_10MB.txt &>$OUTPUTDIR/word_count_$type.log

done
