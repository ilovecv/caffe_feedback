#!/usr/bin/env sh
# This script converts the cifar data into leveldb format.

EXAMPLES=../../build/examples/cifar2
DATA=../../data/cifar10
TOOLS=../../build/tools

echo "Creating leveldb..."

rm -rf cifar2-leveldb
mkdir cifar2-leveldb

GLOG_logtostderr=1 $EXAMPLES/convert_cifar_data.bin $DATA ./cifar2-leveldb

echo "Computing image mean..."

GLOG_logtostderr=1 $TOOLS/compute_image_mean.bin ./cifar2-leveldb/cifar-train-leveldb mean.binaryproto

echo "Done."