#!/usr/bin/env bash

# First created: 2018 Feb 15
# Last modified: 2018 Feb 15

# Author: Feng Li
# email: fengggli@yahoo.com


root_dir=`pwd`
BUILD_DIR=${root_dir}/build_debug

for type in std; do
    if [ $type == "std" ]; then
        exe_type=""
    else
        exe_type=_$type
    fi

    if [ 1 = 2 ]; then ## test
    # kmeans
    echo ""
    echo "[info]:execute app kmeans with type type $exe_type"
    $BUILD_DIR/bin/kmeans${exe_type} 

    # histogram
    echo ""
    echo "[info]:execute app histogram with type type $exe_type"
    $BUILD_DIR/bin/histogram${exe_type} data/histogram_datafiles/small.bmp
    
    echo ""
    echo "[info]:execute app linear regression with type type $exe_type"
    $BUILD_DIR/bin/linear_regression${exe_type} data/linear_regression_datafiles/key_file_100MB.txt

    # matrix multiply
    echo ""
    echo "[info]:execute app matrix_multiply with type type $exe_type"
    side_matrix=1000 # size of matrix
    side_block=10 # size of the row block
    results_dir=results/matrix_multiply_${side_matrix}_${side_block}${exe_type}
    mkdir -pv $results_dir
    cd $results_dir

    $BUILD_DIR/bin/matrix_multiply${exe_type}  ${side_matix} $side_block
    cd $root_dir 

    #pca 
    echo ""
    echo "[info]:execute app pca with type type $exe_type"
    num_rows=10
    num_cols=10
    grid_size=100
    $BUILD_DIR/bin/pca${exe_type} -r ${num_rows} -c $num_cols -s $grid_size
fi

    #string match
    echo ""
    echo "[info]:execute app string match with type type $exe_type"
    $BUILD_DIR/bin/string_match${exe_type} data/string_match_datafiles/key_file_100MB.txt

    #word_count
    echo ""
    echo "[info]:execute app word count  with type type $exe_type"
    $BUILD_DIR/bin/word_count${exe_type} data/word_count_datafiles/word_10MB.txt

done
