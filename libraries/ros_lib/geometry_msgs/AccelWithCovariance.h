#ifndef _ROS_geometry_msgs_AccelWithCovariance_h
#define _ROS_geometry_msgs_AccelWithCovariance_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ArduinoIncludes.h"
#include "geometry_msgs/Accel.h"

namespace geometry_msgs
{

  class AccelWithCovariance : public ros::Msg
  {
    public:
      geometry_msgs::Accel accel;
      float covariance[36];

    AccelWithCovariance():
      accel(),
      covariance()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->accel.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 36; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->covariance[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->accel.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 36; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->covariance[i]));
      }
     return offset;
    }

    const char * getType(){ return PSTR( "geometry_msgs/AccelWithCovariance" ); };
    const char * getMD5(){ return PSTR( "ad5a718d699c6be72a02b8d6a139f334" ); };

  };

}
#endif