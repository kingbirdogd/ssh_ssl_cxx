#!/bin/bash
if [ $# -lt 2 -o $# -gt 3 ]
then
	echo "usage: ./build.sh <build_type> <platform> [lib/teset/all]"
	exit -1;
fi
build_type=$1
platform=$2
source_path=$(dirname $(realpath $0))
make_path="${source_path}/build/${platform}/${build_type}";
cmake "${source_path}" -B "${make_path}" -DCMAKE_BUILD_TYPE=${build_type} -DCMAKE_CXX_FLAGS=-march=${platform};
target=ssh_ssl_cxx
if [ $# -eq 3 ]
then
	target=$3;
fi
if [ "${target}" = "lib" ]
then
	subdir=lib;
	target=ssh_ssl_cxx
elif [ "${target}" = "test" ]
then
	subdir=bin;
	target=ssh_ssl_cxx_test
elif [ "${target}" = "all" ]
then
	cmake --build "${make_path}" --config ${build_type} --target ssh_ssl_cxx;
	cmake --build "${make_path}" --config ${build_type} --target ssh_ssl_cxx_test;
	exit 0;
else
	echo "usage: ./build.sh <build_type> <platform> [lib/teset/all]"
	exit -2;
fi
cmake --build "${make_path}" --config ${build_type} --target ${target};

