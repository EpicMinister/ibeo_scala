#ifndef IBEO_SCALA_ROS_MSG_HANDLER_H
#define IBEO_SCALA_ROS_MSG_HANDLER_H

#include <ibeo_scala_common.h>

namespace AS
{
namespace Drivers
{
namespace IbeoScala
{
  class IbeoScalaRosMsgHandler
  {
    public:
      IbeoScalaRosMsgHandler(unsigned short type_id, ros::Publisher &pub);

      void encode_and_publish(IbeoTxMessage* parser_class, std::string frame_id);
      void encode_pointcloud(std::vector<Point3D> &points, pcl::PointCloud<pcl::PointXYZ> &new_msg);
      void encode_contour_points(std::vector<Point3D> &points, visualization_msgs::Marker &new_msg);
      void encode_marker_array(std::vector<IbeoObject> &objects, visualization_msgs::MarkerArray &new_msg);

    private:
      unsigned short type_id;
      ros::Publisher pub;

      ros::Time ntp_to_ros_time(NTPTime time);

      void encode_ibeo_header(IbeoDataHeader &class_header, ibeo_scala_msgs::IbeoDataHeader &msg_header);

      void encode_2202(ScanData2202* parser_class, ibeo_scala_msgs::ScanData2202 &new_msg);
      void encode_2205(ScanData2205* parser_class, ibeo_scala_msgs::ScanData2205 &new_msg);
      void encode_2208(ScanData2208* parser_class, ibeo_scala_msgs::ScanData2208 &new_msg);
      void encode_2225(ObjectData2225* parser_class, ibeo_scala_msgs::ObjectData2225 &new_msg);
      void encode_2270(ObjectData2270* parser_class, ibeo_scala_msgs::ObjectData2270 &new_msg);
      void encode_2271(ObjectData2271* parser_class, ibeo_scala_msgs::ObjectData2271 &new_msg);
      void encode_2280(ObjectData2280* parser_class, ibeo_scala_msgs::ObjectData2280 &new_msg);
      void encode_2403(CameraImage* parser_class, ibeo_scala_msgs::CameraImage &new_msg);
      void encode_2805(HostsVehicleState2805* parser_class, ibeo_scala_msgs::HostsVehicleState2805 &new_msg);
      void encode_2806(HostsVehicleState2806* parser_class, ibeo_scala_msgs::HostsVehicleState2806 &new_msg);
      void encode_2807(HostsVehicleState2807* parser_class, ibeo_scala_msgs::HostsVehicleState2807 &new_msg);
      void encode_6301(DeviceStatus* parser_class, ibeo_scala_msgs::DeviceStatus &new_msg);
      visualization_msgs::Marker createWireframeMarker(float center_x, float center_y, float size_x, float size_y, float size_z);
  };
}
}
}

#endif
