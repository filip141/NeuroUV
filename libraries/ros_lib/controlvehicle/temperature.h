#ifndef _ROS_controlvehicle_temperature_h
#define _ROS_controlvehicle_temperature_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ArduinoIncludes.h"

namespace controlvehicle
{

  class temperature : public ros::Msg
  {
    public:
      int32_t pressure;
      float tem;

    temperature():
      pressure(0),
      tem(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pressure;
      u_pressure.real = this->pressure;
      *(outbuffer + offset + 0) = (u_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pressure.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pressure);
      union {
        float real;
        uint32_t base;
      } u_tem;
      u_tem.real = this->tem;
      *(outbuffer + offset + 0) = (u_tem.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tem.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tem.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tem.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tem);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_pressure;
      u_pressure.base = 0;
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pressure.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pressure = u_pressure.real;
      offset += sizeof(this->pressure);
      union {
        float real;
        uint32_t base;
      } u_tem;
      u_tem.base = 0;
      u_tem.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tem.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tem.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tem.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->tem = u_tem.real;
      offset += sizeof(this->tem);
     return offset;
    }

    const char * getType(){ return PSTR( "controlvehicle/temperature" ); };
    const char * getMD5(){ return PSTR( "497bf7bb8f1746bcbb7992d334657900" ); };

  };

}
#endif
