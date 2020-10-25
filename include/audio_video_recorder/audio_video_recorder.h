#include <boost/thread.hpp>
#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>

#include "audio_common_msgs/AudioData.h"
#include "sensor_msgs/Image.h"

namespace audio_video_recorder
{
  class AudioVideoRecorder
  {
    public:
      AudioVideoRecorder() {}

      typedef message_filters::sync_policies::ExactTime<sensor_msgs::Image, audio_common_msgs::AudioData> ExactSyncPolicy;
      typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, audio_common_msgs::AudioData> ApproximateSyncPolicy;

      void initialize();
      void callbackImage(const sensor_msgs::ImageConstPtr &image_msg);
      void callbackAudio(const audio_common_msgs::AudioDataConstPtr &audio_msg);

    protected:
      boost::shared_ptr<ros::NodeHandle> _nh;
      ros::Subscriber _sub_image, _sub_audio;
      boost::shared_ptr<message_filters::Synchronizer<ExactSyncPolicy> > _sync;
      boost::shared_ptr<message_filters::Synchronizer<ApproximateSyncPolicy> > _async;

      boost::thread _gst_thread;
      GstElement *_pipeline, *_source, *_sink, *_audio, *_filter;
      GMainLoop *_loop;
  };
}
