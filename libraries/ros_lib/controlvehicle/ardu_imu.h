#ifndef _ROS_controlvehicle_ardu_imu_h
#define _ROS_controlvehicle_ardu_imu_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ArduinoIncludes.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace controlvehicle
{

  class ardu_imu : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Vector3 gyroValues;
      geometry_msgs::Vector3 accValues;
      geometry_msgs::Vector3 magValues;

    ardu_imu():
      header(),
      gyroValues(),
      accValues(),
      magValues()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->gyroValues.serialize(outbuffer + offset);
      offset += this->accValues.serialize(outbuffer + offset);
      offset += this->magValues.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->gyroValues.deserialize(inbuffer + offset);
      offset += this->accValues.deserialize(inbuffer + offset);
      offset += this->magValues.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return PSTR( "controlvehicle/ardu_imu" ); };
    const char * getMD5(){ return PSTR( "956c793ef60c822d69ca53a1f4eaa0f4" ); };

  };

}
#endif
