#ifndef _ROS_controlvehicle_joy_control_msg_h
#define _ROS_controlvehicle_joy_control_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace controlvehicle
{

  class joy_control_msg : public ros::Msg
  {
    public:
      uint8_t sequence;
      int8_t speed;
      int8_t powerLR;

    joy_control_msg():
      sequence(0),
      speed(0),
      powerLR(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->sequence >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sequence);
      union {
        int8_t real;
        uint8_t base;
      } u_speed;
      u_speed.real = this->speed;
      *(outbuffer + offset + 0) = (u_speed.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->speed);
      union {
        int8_t real;
        uint8_t base;
      } u_powerLR;
      u_powerLR.real = this->powerLR;
      *(outbuffer + offset + 0) = (u_powerLR.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->powerLR);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->sequence =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sequence);
      union {
        int8_t real;
        uint8_t base;
      } u_speed;
      u_speed.base = 0;
      u_speed.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->speed = u_speed.real;
      offset += sizeof(this->speed);
      union {
        int8_t real;
        uint8_t base;
      } u_powerLR;
      u_powerLR.base = 0;
      u_powerLR.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->powerLR = u_powerLR.real;
      offset += sizeof(this->powerLR);
     return offset;
    }

    const char * getType(){ return "controlvehicle/joy_control_msg"; };
    const char * getMD5(){ return "499cf4e3d592166be607da2914a0e4a0"; };

  };

}
#endif