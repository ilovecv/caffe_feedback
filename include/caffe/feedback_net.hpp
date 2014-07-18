// Copyright Xianming Liu, July 2014.

#ifndef CAFFE_FEEDBACK_NET_HPP_
#define CAFFE_FEEDBACK_NET_HPP_

#include <map>
#include <string>
#include <vector>

#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe{

  template <typename Dtype>
  class FeedbackNet : public Net<Dtype>
  {
  public:
    explicit FeedbackNet(const NetParameter& param) : Net<Dtype>(param){}
    explicit FeedbackNet(const string& param_file) : Net<Dtype>(param_file){}
    virtual ~FeedbackNet(){}

    void UpdateEqFilter();

    // By default, the visualization results are straight to the input layer
    // (input_blobs_ as in the father class: Net)
    // Default parameter:
    // startChannelIdx = 0
    // endLayerIdx = 0: using the data layer as visualization target
    // startOffset: visualize the neuron at specific position (pos = startOffset)
    //  if startOffset == -1 (by default), use all the output neurons.
    void Visualize(int startLayerIdx, int startChannelIdx = 0, int startOffset = -1, int endLayerIdx = 0);

    // Search the layer list and get the index
    void Visualize(string startLayer, int startChannelIdx = 0, int startOffset = -1, string endLayer = "data");

    inline Blob<Dtype>* GetVisualization() {return visualization_;}

    //draw visualization: draw visualization_ to files, stored in dir
    void DrawVisualization(string dir);

  protected:
    //Member function
    void InitVisualization();
    //void InitFeedback();

    //Generate the top_filter_ for the startLayer of visualization
    void generateStartTopFilter();

  protected:
    //Stores the visualization results
    //num: input images of minibatch;
    //channels, width, height: size of image (channel by default is rgb)
    Blob<Dtype>* visualization_;
    
    //The vector stores the ptr list of eq_filter for each feedback_layer in fLayers_
    //If the end layer idx of visualization is k,
    //then the visualization results are eq_filter_top_[k]
    vector<Blob<Dtype>* > eq_filter_top_;

    int startLayerIdx_;
    int startChannelIdx_;
    int endLayerIdx_;

    //The synthesized top_filter for the start layer of visualization
    Blob<Dtype>* start_top_filter_;
  };
} // namespace caffe

#endif