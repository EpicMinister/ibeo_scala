#include <ibeo_scala_ros_msg_handler.h>

using namespace AS::Drivers::IbeoScala;

IbeoScalaRosMsgHandler::IbeoScalaRosMsgHandler(ros::Publisher &pub, std::string frame_id) :
  pub(pub),
  frame_id(frame_id)
{
}

void IbeoScalaRosMsgHandler::fillAndPublish(unsigned short type_id,
                                            std::shared_ptr<IbeoTxMessage>& parser_class)
{
  if (type_id == ScanData2202::DATA_TYPE)
  {
    ibeo_msgs::ScanData2202 new_msg;
    fill2202(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ScanData2205::DATA_TYPE)
  {
    ibeo_msgs::ScanData2205 new_msg;
    fill2205(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ScanData2208::DATA_TYPE)
  {
    ibeo_msgs::ScanData2208 new_msg;
    fill2208(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ObjectData2225::DATA_TYPE)
  {
    ibeo_msgs::ObjectData2225 new_msg;
    fill2225(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ObjectData2270::DATA_TYPE)
  {
    ibeo_msgs::ObjectData2270 new_msg;
    fill2270(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ObjectData2271::DATA_TYPE)
  {
    ibeo_msgs::ObjectData2271 new_msg;
    fill2271(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == ObjectData2280::DATA_TYPE)
  {
    ibeo_msgs::ObjectData2280 new_msg;
    fill2280(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == CameraImage::DATA_TYPE)
  {
    ibeo_msgs::CameraImage new_msg;
    fill2403(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == HostVehicleState2805::DATA_TYPE)
  {
    ibeo_msgs::HostVehicleState2805 new_msg;
    fill2805(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == HostVehicleState2806::DATA_TYPE)
  {
    ibeo_msgs::HostVehicleState2806 new_msg;
    fill2806(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == HostVehicleState2807::DATA_TYPE)
  {
    ibeo_msgs::HostVehicleState2807 new_msg;
    fill2807(parser_class, new_msg);
    pub.publish(new_msg);
  }
  else if (type_id == DeviceStatus::DATA_TYPE)
  {
    ibeo_msgs::DeviceStatus new_msg;
    fill6301(parser_class, new_msg);
    pub.publish(new_msg);
  }
}

ros::Time IbeoScalaRosMsgHandler::ntp_to_ros_time(NTPTime time)
{
  return ros::Time(((time & 0xFFFF0000) >> 32), (time & 0x0000FFFF));
}

void IbeoScalaRosMsgHandler::fillIbeoHeader(IbeoDataHeader& class_header, ibeo_msgs::IbeoDataHeader& msg_header)
{
  msg_header.previous_message_size = class_header.previous_message_size;
  msg_header.message_size = class_header.message_size;
  msg_header.device_id = class_header.device_id;
  msg_header.data_type_id = class_header.data_type_id;
  msg_header.stamp = ntp_to_ros_time(class_header.time);
}

void IbeoScalaRosMsgHandler::fill2202(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ScanData2202& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ScanData2202>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.scan_number = dc_parser->scan_number;
  new_msg.scanner_status = dc_parser->scanner_status;
  new_msg.sync_phase_offset = dc_parser->sync_phase_offset;
  new_msg.scan_start_time = ntp_to_ros_time(dc_parser->scan_start_time);
  new_msg.scan_end_time = ntp_to_ros_time(dc_parser->scan_end_time);
  new_msg.angle_ticks_per_rotation = dc_parser->angle_ticks_per_rotation;
  new_msg.start_angle_ticks = dc_parser->start_angle_ticks;
  new_msg.end_angle_ticks = dc_parser->end_angle_ticks;
  new_msg.mounting_yaw_angle_ticks = dc_parser->mounting_yaw_angle_ticks;
  new_msg.mounting_pitch_angle_ticks = dc_parser->mounting_pitch_angle_ticks;
  new_msg.mounting_roll_angle_ticks = dc_parser->mounting_roll_angle_ticks;
  new_msg.mounting_position_x = dc_parser->mounting_position_x;
  new_msg.mounting_position_y = dc_parser->mounting_position_y;
  new_msg.mounting_position_z = dc_parser->mounting_position_z;

  for (auto scan_point : dc_parser->scan_point_list)
  {
    ibeo_msgs::ScanPoint2202 scan_point_msg;

    scan_point_msg.layer = scan_point.layer;
    scan_point_msg.echo = scan_point.echo;
    scan_point_msg.transparent_point = scan_point.transparent_point;
    scan_point_msg.clutter_atmospheric = scan_point.clutter_atmospheric;
    scan_point_msg.ground = scan_point.ground;
    scan_point_msg.dirt = scan_point.dirt;
    scan_point_msg.horizontal_angle = scan_point.horizontal_angle;
    scan_point_msg.radial_distance = scan_point.radial_distance;
    scan_point_msg.echo_pulse_width = scan_point.echo_pulse_width;

    new_msg.scan_point_list.push_back(scan_point_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2205(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ScanData2205& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ScanData2205>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.scan_start_time = ntp_to_ros_time(dc_parser->scan_start_time);
  new_msg.scan_end_time_offset = dc_parser->scan_end_time_offset;
  new_msg.fused_scan = dc_parser->fused_scan;

  if (dc_parser->mirror_side == FRONT)
    new_msg.mirror_side = ibeo_msgs::ScanData2205::FRONT;
  else
    new_msg.mirror_side = ibeo_msgs::ScanData2205::REAR;

  if (dc_parser->coordinate_system == SCANNER)
    new_msg.coordinate_system = ibeo_msgs::ScanData2205::SCANNER;
  else
    new_msg.coordinate_system = ibeo_msgs::ScanData2205::VEHICLE;

  new_msg.scan_number = dc_parser->scan_number;
  new_msg.scan_points = dc_parser->scan_points;
  new_msg.number_of_scanner_infos = dc_parser->number_of_scanner_infos;

  for (auto scanner_info : dc_parser->scanner_info_list)
  {
    ibeo_msgs::ScannerInfo scanner_info_msg;

    scanner_info_msg.device_id = scanner_info.device_id;
    scanner_info_msg.scanner_type = scanner_info.scanner_type;
    scanner_info_msg.scan_number = scanner_info.scan_number;
    scanner_info_msg.start_angle = scanner_info.start_angle;
    scanner_info_msg.end_angle = scanner_info.end_angle;
    scanner_info_msg.scan_start_time = ntp_to_ros_time(scanner_info.scan_start_time);
    scanner_info_msg.scan_end_time = ntp_to_ros_time(scanner_info.scan_end_time);
    scanner_info_msg.scan_start_time_from_device = ntp_to_ros_time(scanner_info.scan_start_time_from_device);
    scanner_info_msg.scan_end_time_from_device = ntp_to_ros_time(scanner_info.scan_end_time_from_device);
    scanner_info_msg.scan_frequency = scanner_info.scan_frequency;
    scanner_info_msg.beam_tilt = scanner_info.beam_tilt;
    scanner_info_msg.scan_flags = scanner_info.scan_flags;

    scanner_info_msg.mounting_position.yaw_angle = scanner_info.mounting_position.yaw_angle;
    scanner_info_msg.mounting_position.pitch_angle = scanner_info.mounting_position.pitch_angle;
    scanner_info_msg.mounting_position.roll_angle = scanner_info.mounting_position.roll_angle;
    scanner_info_msg.mounting_position.x_position = scanner_info.mounting_position.x_position;
    scanner_info_msg.mounting_position.y_position = scanner_info.mounting_position.y_position;
    scanner_info_msg.mounting_position.z_position = scanner_info.mounting_position.z_position;

    for (int i = 0; i < 8; i++)
    {
      scanner_info_msg.resolutions[i].resolution_start_angle = scanner_info.resolutions[i].resolution_start_angle;
      scanner_info_msg.resolutions[i].resolution = scanner_info.resolutions[i].resolution;
    }

    new_msg.scanner_info_list.push_back(scanner_info_msg);
  }

  for (auto scan_point : dc_parser->scan_point_list)
  {
    ibeo_msgs::ScanPoint2205 scan_point_msg;

    scan_point_msg.x_position = scan_point.x_position;
    scan_point_msg.y_position = scan_point.y_position;
    scan_point_msg.z_position = scan_point.z_position;
    scan_point_msg.echo_width = scan_point.echo_width;
    scan_point_msg.device_id = scan_point.device_id;
    scan_point_msg.layer = scan_point.layer;
    scan_point_msg.echo = scan_point.echo;
    scan_point_msg.time_offset = scan_point.time_offset;
    scan_point_msg.ground = scan_point.ground;
    scan_point_msg.dirt = scan_point.dirt;
    scan_point_msg.precipitation = scan_point.precipitation;
    scan_point_msg.transparent = scan_point.transparent;

    new_msg.scan_point_list.push_back(scan_point_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2208(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ScanData2208& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ScanData2208>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.scan_number = dc_parser->scan_number;
  new_msg.scanner_type = (dc_parser->scanner_type == ibeo_msgs::ScanData2208::SCALA_B2) ? ibeo_msgs::ScanData2208::SCALA_B2 : 0;
  new_msg.motor_on = dc_parser->motor_on;
  new_msg.laser_on = dc_parser->laser_on;
  new_msg.frequency_locked = dc_parser->frequency_locked;
  
  if (dc_parser->motor_rotating_direction == CLOCKWISE)
    new_msg.motor_rotating_direction = ibeo_msgs::ScanData2208::CLOCKWISE;
  else if (dc_parser->motor_rotating_direction == COUNTER_CLOCKWISE)
    new_msg.motor_rotating_direction = ibeo_msgs::ScanData2208::COUNTER_CLOCKWISE;

  new_msg.angle_ticks_per_rotation = dc_parser->angle_ticks_per_rotation;
  new_msg.scan_flags = dc_parser->scan_flags;
  new_msg.mounting_yaw_angle_ticks = dc_parser->mounting_yaw_angle_ticks;
  new_msg.mounting_pitch_angle_ticks = dc_parser->mounting_pitch_angle_ticks;
  new_msg.mounting_roll_angle_ticks = dc_parser->mounting_roll_angle_ticks;
  new_msg.mounting_position_x = dc_parser->mounting_position_x;
  new_msg.mounting_position_y = dc_parser->mounting_position_y;
  new_msg.mounting_position_z = dc_parser->mounting_position_z;
  new_msg.device_id = dc_parser->device_id;
  new_msg.scan_start_time = ntp_to_ros_time(dc_parser->scan_start_time);
  new_msg.scan_end_time = ntp_to_ros_time(dc_parser->scan_end_time);
  new_msg.start_angle_ticks = dc_parser->start_angle_ticks;
  new_msg.end_angle_ticks = dc_parser->end_angle_ticks;

  if (dc_parser->mirror_side == FRONT)
    new_msg.mirror_side = ibeo_msgs::ScanData2208::FRONT_MIRROR;
  else if (dc_parser->mirror_side == REAR)
    new_msg.mirror_side = ibeo_msgs::ScanData2208::REAR_MIRROR;

  new_msg.mirror_tilt = dc_parser->mirror_tilt;

  for (auto scan_point : dc_parser->scan_point_list)
  {
    ibeo_msgs::ScanPoint2208 scan_point_msg;

    scan_point_msg.echo = scan_point.echo;
    scan_point_msg.layer = scan_point.layer;
    scan_point_msg.transparent_point = scan_point.transparent_point;
    scan_point_msg.clutter_atmospheric = scan_point.clutter_atmospheric;
    scan_point_msg.ground = scan_point.ground;
    scan_point_msg.dirt = scan_point.dirt;
    scan_point_msg.horizontal_angle = scan_point.horizontal_angle;
    scan_point_msg.radial_distance = scan_point.radial_distance;
    scan_point_msg.echo_pulse_width = scan_point.echo_pulse_width;

    new_msg.scan_point_list.push_back(scan_point_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2225(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ObjectData2225& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ObjectData2225>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.mid_scan_timestamp = ntp_to_ros_time(dc_parser->mid_scan_timestamp);
  new_msg.number_of_objects = dc_parser->number_of_objects;

  for (auto object : dc_parser->object_list)
  {
    ibeo_msgs::Object2225 object_msg;

    object_msg.id = object.id;
    object_msg.age = object.age;
    object_msg.stamp = ntp_to_ros_time(object.timestamp);
    object_msg.hidden_status_age = object.hidden_status_age;
    
    switch (object.classification)
    {
      case UNCLASSIFIED:
        object_msg.classification = ibeo_msgs::Object2225::UNCLASSIFIED;
        break;
      case UNKNOWN_SMALL:
        object_msg.classification = ibeo_msgs::Object2225::UNKNOWN_SMALL;
        break;
      case UNKNOWN_BIG:
        object_msg.classification = ibeo_msgs::Object2225::UNKNOWN_BIG;
        break;
      case PEDESTRIAN:
        object_msg.classification = ibeo_msgs::Object2225::PEDESTRIAN;
        break;
      case BIKE:
        object_msg.classification = ibeo_msgs::Object2225::BIKE;
        break;
      case CAR:
        object_msg.classification = ibeo_msgs::Object2225::CAR;
        break;
      case TRUCK:
        object_msg.classification = ibeo_msgs::Object2225::TRUCK;
        break;
      default:
        object_msg.classification = ibeo_msgs::Object2225::UNCLASSIFIED;
        break;
    }

    object_msg.classification_certainty = object.classification_certainty;
    object_msg.classification_age = object.classification_age;
    object_msg.bounding_box_center.x = object.bounding_box_center.x;
    object_msg.bounding_box_center.y = object.bounding_box_center.y;
    object_msg.bounding_box_size.x = object.bounding_box_size.x;
    object_msg.bounding_box_size.y = object.bounding_box_size.y;
    object_msg.object_box_center.x = object.object_box_center.x;
    object_msg.object_box_center.y = object.object_box_center.y;
    object_msg.object_box_center_sigma.x = object.object_box_center_sigma.x;
    object_msg.object_box_center_sigma.y = object.object_box_center_sigma.y;
    object_msg.object_box_size.x = object.object_box_size.x;
    object_msg.object_box_size.y = object.object_box_size.y;
    object_msg.yaw_angle = object.yaw_angle;
    object_msg.relative_velocity.x = object.relative_velocity.x;
    object_msg.relative_velocity.y = object.relative_velocity.y;
    object_msg.relative_velocity_sigma.x = object.relative_velocity_sigma.x;
    object_msg.relative_velocity_sigma.y = object.relative_velocity_sigma.y;
    object_msg.absolute_velocity.x = object.absolute_velocity.x;
    object_msg.absolute_velocity.y = object.absolute_velocity.y;
    object_msg.absolute_velocity_sigma.x = object.absolute_velocity_sigma.x;
    object_msg.absolute_velocity_sigma.y = object.absolute_velocity_sigma.y;
    object_msg.number_of_contour_points = object.number_of_contour_points;
    object_msg.closest_point_index = object.closest_point_index;
    
    for (auto contour_point : object.contour_point_list)
    {
      ibeo_msgs::Point2DFloat contour_point_msg;

      contour_point_msg.x = contour_point.x;
      contour_point_msg.y = contour_point.y;

      object_msg.contour_point_list.push_back(contour_point_msg);
    }

    new_msg.object_list.push_back(object_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2270(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ObjectData2270& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ObjectData2270>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.start_scan_timestamp = ntp_to_ros_time(dc_parser->start_scan_timestamp);
  new_msg.object_list_number = dc_parser->object_list_number;
  new_msg.number_of_objects = dc_parser->number_of_objects;

  for (auto object : dc_parser->object_list)
  {
    ibeo_msgs::Object2270 object_msg;

    object_msg.id = object.id;
    object_msg.age = object.age;
    object_msg.prediction_age = object.prediction_age;
    object_msg.relative_moment_of_measurement = object.relative_moment_of_measurement;
    
    switch (object.reference_point_location)
    {
      case COG:
        object_msg.reference_point_location = ibeo_msgs::Object2270::CENTER_OF_GRAVITY;
        break;
      case TOP_FRONT_LEFT_CORNER:
        object_msg.reference_point_location = ibeo_msgs::Object2270::TOP_FRONT_LEFT_CORNER;
        break;
      case TOP_FRONT_RIGHT_CORNER:
        object_msg.reference_point_location = ibeo_msgs::Object2270::TOP_FRONT_RIGHT_CORNER;
        break;
      case BOTTOM_REAR_RIGHT_CORNER:
        object_msg.reference_point_location = ibeo_msgs::Object2270::BOTTOM_REAR_RIGHT_CORNER;
        break;
      case BOTTOM_REAR_LEFT_CORNER:
        object_msg.reference_point_location = ibeo_msgs::Object2270::BOTTOM_REAR_LEFT_CORNER;
        break;
      case CENTER_OF_TOP_FRONT_EDGE:
        object_msg.reference_point_location = ibeo_msgs::Object2270::CENTER_OF_TOP_FRONT_EDGE;
        break;
      case CENTER_OF_RIGHT_EDGE:
        object_msg.reference_point_location = ibeo_msgs::Object2270::CENTER_OF_RIGHT_EDGE;
        break;
      case CENTER_OF_BOTTOM_REAR_EDGE:
        object_msg.reference_point_location = ibeo_msgs::Object2270::CENTER_OF_BOTTOM_REAR_EDGE;
        break;
      case CENTER_OF_LEFT_EDGE:
        object_msg.reference_point_location = ibeo_msgs::Object2270::CENTER_OF_LEFT_EDGE;
        break;
      case BOX_CENTER:
        object_msg.reference_point_location = ibeo_msgs::Object2270::BOX_CENTER;
        break;
      case INVALID:
        object_msg.reference_point_location = ibeo_msgs::Object2270::INVALID;
        break;
      default:
        object_msg.reference_point_location = ibeo_msgs::Object2270::INVALID;
        break;
    }

    object_msg.reference_point_position_x = object.reference_point_position_x;
    object_msg.reference_point_position_y = object.reference_point_position_y;
    object_msg.reference_point_position_sigma_x = object.reference_point_position_sigma_x;
    object_msg.reference_point_position_sigma_y = object.reference_point_position_sigma_y;
    object_msg.contour_points_cog_x = object.contour_points_cog_x;
    object_msg.contour_points_cog_y = object.contour_points_cog_y;
    object_msg.object_box_length = object.object_box_length;
    object_msg.object_box_width = object.object_box_width;
    object_msg.object_box_orientation_angle = object.object_box_orientation_angle;
    object_msg.object_box_orientation_angle_sigma = object.object_box_orientation_angle_sigma;
    object_msg.absolute_velocity_x = object.absolute_velocity_x;
    object_msg.absolute_velocity_y = object.absolute_velocity_y;
    object_msg.absolute_velocity_sigma_x = object.absolute_velocity_sigma_x;
    object_msg.absolute_velocity_sigma_y = object.absolute_velocity_sigma_y;
    object_msg.relative_velocity_x = object.relative_velocity_x;
    object_msg.relative_velocity_y = object.relative_velocity_y;
    object_msg.relative_velocity_sigma_x = object.relative_velocity_sigma_x;
    object_msg.relative_velocity_sigma_y = object.relative_velocity_sigma_y;
    
    switch (object.classification)
    {
      case UNCLASSIFIED:
        object_msg.classification = ibeo_msgs::Object2270::UNCLASSIFIED;
        break;
      case UNKNOWN_SMALL:
        object_msg.classification = ibeo_msgs::Object2270::UNKNOWN_SMALL;
        break;
      case UNKNOWN_BIG:
        object_msg.classification = ibeo_msgs::Object2270::UNKNOWN_BIG;
        break;
      case PEDESTRIAN:
        object_msg.classification = ibeo_msgs::Object2270::PEDESTRIAN;
        break;
      case BIKE:
        object_msg.classification = ibeo_msgs::Object2270::BIKE;
        break;
      case CAR:
        object_msg.classification = ibeo_msgs::Object2270::CAR;
        break;
      case TRUCK:
        object_msg.classification = ibeo_msgs::Object2270::TRUCK;
        break;
      default:
        object_msg.classification = ibeo_msgs::Object2270::UNCLASSIFIED;
        break;
    }

    switch (object.tracking_model)
    {
      case STATIC:
        object_msg.tracking_model = ibeo_msgs::Object2270::STATIC_MODEL;
        break;
      case DYNAMIC:
        object_msg.tracking_model = ibeo_msgs::Object2270::DYNAMIC_MODEL;
        break;
      default:
        object_msg.tracking_model = ibeo_msgs::Object2270::DYNAMIC_MODEL;
        break;
    }

    object_msg.mobile_detected = object.mobile_detected;
    object_msg.track_valid = object.track_valid;
    object_msg.classification_age = object.classification_age;
    object_msg.classification_confidence = object.classification_confidence;
    object_msg.number_of_contour_points = object.number_of_contour_points;

    for (auto contour_point : object.contour_point_list)
    {
      ibeo_msgs::Point2Di contour_point_msg;

      contour_point_msg.x = contour_point.x;
      contour_point_msg.y = contour_point.y;
      object_msg.contour_point_list.push_back(contour_point_msg);
    }

    new_msg.object_list.push_back(object_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2271(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ObjectData2271& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ObjectData2271>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.start_scan_timestamp = ntp_to_ros_time(dc_parser->start_scan_timestamp);
  new_msg.scan_number = dc_parser->scan_number;
  new_msg.number_of_objects = dc_parser->number_of_objects;

  for (auto object : dc_parser->object_list)
  {
    ibeo_msgs::Object2271 object_msg;

    object_msg.untracked_properties_available = object.untracked_properties_available;
    object_msg.tracked_properties_available = object.tracked_properties_available;
    
    object_msg.untracked_properties.relative_time_of_measurement = object.untracked_properties.relative_time_of_measurement;
    object_msg.untracked_properties.position_closest_point.x = object.untracked_properties.position_closest_point.x;
    object_msg.untracked_properties.position_closest_point.y = object.untracked_properties.position_closest_point.y;
    object_msg.untracked_properties.object_box_size.x = object.untracked_properties.object_box_size.x;
    object_msg.untracked_properties.object_box_size.y = object.untracked_properties.object_box_size.y;
    object_msg.untracked_properties.object_box_size_sigma.x = object.untracked_properties.object_box_size_sigma.x;
    object_msg.untracked_properties.object_box_size_sigma.y = object.untracked_properties.object_box_size_sigma.y;
    object_msg.untracked_properties.object_box_orientation = object.untracked_properties.object_box_orientation;
    object_msg.untracked_properties.object_box_orientation_sigma = object.untracked_properties.object_box_orientation_sigma;
    object_msg.untracked_properties.tracking_point_coordinate.x = object.untracked_properties.tracking_point_coordinate.x;
    object_msg.untracked_properties.tracking_point_coordinate.y = object.untracked_properties.tracking_point_coordinate.y;
    object_msg.untracked_properties.tracking_point_coordinate_sigma.x = object.untracked_properties.tracking_point_coordinate_sigma.x;
    object_msg.untracked_properties.tracking_point_coordinate_sigma.y = object.untracked_properties.tracking_point_coordinate_sigma.y;
    object_msg.untracked_properties.number_of_contour_points = object.untracked_properties.number_of_contour_points;

    for (auto contour_point : object.untracked_properties.contour_point_list)
    {
      ibeo_msgs::ContourPointSigma contour_point_msg;

      contour_point_msg.x = contour_point.x;
      contour_point_msg.y = contour_point.y;
      contour_point_msg.x_sigma = contour_point.x_sigma;
      contour_point_msg.y_sigma = contour_point.y_sigma;
      object_msg.untracked_properties.contour_point_list.push_back(contour_point_msg);
    }

    object_msg.tracked_properties.object_age = object.tracked_properties.object_age;
    object_msg.tracked_properties.hidden_status_age = object.tracked_properties.hidden_status_age;
    
    switch (object.tracked_properties.object_phase)
    {
      case INITIALIZATION:
        object_msg.tracked_properties.object_phase = ibeo_msgs::TrackedProperties::INITIALIZATION_PHASE;
        break;
      case TRACKING:
        object_msg.tracked_properties.object_phase = ibeo_msgs::TrackedProperties::TRACKING_PHASE;
        break;
    }

    switch (object.tracked_properties.dynamic_property)
    {
      case DYNAMIC_AND_MOVING:
        object_msg.tracked_properties.dynamic_property = ibeo_msgs::TrackedProperties::DYNAMIC_AND_MOVING;
        break;
      case DYNAMIC_AND_STOPPED:
        object_msg.tracked_properties.dynamic_property = ibeo_msgs::TrackedProperties::DYNAMIC_AND_STOPPED;
        break;
      case A_PRIORI_STATIONARY:
        object_msg.tracked_properties.dynamic_property = ibeo_msgs::TrackedProperties::A_PRIORI_STATIONARY;
        break;
    }

    object_msg.tracked_properties.relative_time_of_measure = object.tracked_properties.relative_time_of_measure;
    object_msg.tracked_properties.position_closest_point.x = object.tracked_properties.position_closest_point.x;
    object_msg.tracked_properties.position_closest_point.y = object.tracked_properties.position_closest_point.y;
    object_msg.tracked_properties.relative_velocity.x = object.tracked_properties.relative_velocity.x;
    object_msg.tracked_properties.relative_velocity.y = object.tracked_properties.relative_velocity.y;
    object_msg.tracked_properties.relative_velocity_sigma.x = object.tracked_properties.relative_velocity_sigma.x;
    object_msg.tracked_properties.relative_velocity_sigma.y = object.tracked_properties.relative_velocity_sigma.y;

    switch (object.tracked_properties.classification)
    {
      case UNCLASSIFIED:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::UNCLASSIFIED;
        break;
      case UNKNOWN_SMALL:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::UNKNOWN_SMALL;
        break;
      case UNKNOWN_BIG:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::UNKNOWN_BIG;
        break;
      case PEDESTRIAN:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::PEDESTRIAN;
        break;
      case BIKE:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::BIKE;
        break;
      case CAR:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::CAR;
        break;
      case TRUCK:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::TRUCK;
        break;
      default:
        object_msg.tracked_properties.classification = ibeo_msgs::TrackedProperties::UNCLASSIFIED;
        break;
    }

    object_msg.tracked_properties.classification_age = object.tracked_properties.classification_age;
    object_msg.tracked_properties.object_box_size.x = object.tracked_properties.object_box_size.x;
    object_msg.tracked_properties.object_box_size.y = object.tracked_properties.object_box_size.y;
    object_msg.tracked_properties.object_box_size_sigma.x = object.tracked_properties.object_box_size_sigma.x;
    object_msg.tracked_properties.object_box_size_sigma.y = object.tracked_properties.object_box_size_sigma.y;
    object_msg.tracked_properties.object_box_orientation = object.tracked_properties.object_box_orientation;
    object_msg.tracked_properties.object_box_orientation_sigma = object.tracked_properties.object_box_orientation_sigma;

    switch (object.tracked_properties.tracking_point_location)
    {
      case COG:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::CENTER_OF_GRAVITY;
        break;
      case TOP_FRONT_LEFT_CORNER:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::TOP_FRONT_LEFT_CORNER;
        break;
      case TOP_FRONT_RIGHT_CORNER:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::TOP_FRONT_RIGHT_CORNER;
        break;
      case BOTTOM_REAR_RIGHT_CORNER:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::BOTTOM_REAR_RIGHT_CORNER;
        break;
      case BOTTOM_REAR_LEFT_CORNER:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::BOTTOM_REAR_LEFT_CORNER;
        break;
      case CENTER_OF_TOP_FRONT_EDGE:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::CENTER_OF_TOP_FRONT_EDGE;
        break;
      case CENTER_OF_RIGHT_EDGE:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::CENTER_OF_RIGHT_EDGE;
        break;
      case CENTER_OF_BOTTOM_REAR_EDGE:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::CENTER_OF_BOTTOM_REAR_EDGE;
        break;
      case CENTER_OF_LEFT_EDGE:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::CENTER_OF_LEFT_EDGE;
        break;
      case BOX_CENTER:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::BOX_CENTER;
        break;
      case INVALID:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::INVALID;
        break;
      default:
        object_msg.tracked_properties.tracking_point_location = ibeo_msgs::TrackedProperties::INVALID;
        break;
    }

    object_msg.tracked_properties.tracking_point_coordinate.x = object.tracked_properties.tracking_point_coordinate.x;
    object_msg.tracked_properties.tracking_point_coordinate.y = object.tracked_properties.tracking_point_coordinate.y;
    object_msg.tracked_properties.tracking_point_coordinate_sigma.x = object.tracked_properties.tracking_point_coordinate_sigma.x;
    object_msg.tracked_properties.tracking_point_coordinate_sigma.y = object.tracked_properties.tracking_point_coordinate_sigma.y;
    object_msg.tracked_properties.velocity.x = object.tracked_properties.velocity.x;
    object_msg.tracked_properties.velocity.y = object.tracked_properties.velocity.y;
    object_msg.tracked_properties.velocity_sigma.x = object.tracked_properties.velocity_sigma.x;
    object_msg.tracked_properties.velocity_sigma.y = object.tracked_properties.velocity_sigma.y;
    object_msg.tracked_properties.acceleration.x = object.tracked_properties.acceleration.x;
    object_msg.tracked_properties.acceleration.y = object.tracked_properties.acceleration.y;
    object_msg.tracked_properties.acceleration_sigma.x = object.tracked_properties.acceleration_sigma.x;
    object_msg.tracked_properties.acceleration_sigma.y = object.tracked_properties.acceleration_sigma.y;
    object_msg.tracked_properties.yaw_rate = object.tracked_properties.yaw_rate;
    object_msg.tracked_properties.yaw_rate_sigma = object.tracked_properties.yaw_rate_sigma;
    object_msg.tracked_properties.number_of_contour_points = object.tracked_properties.number_of_contour_points;

    for (auto contour_point : object.tracked_properties.contour_point_list)
    {
      ibeo_msgs::ContourPointSigma contour_point_msg;

      contour_point_msg.x = contour_point.x;
      contour_point_msg.y = contour_point.y;
      contour_point_msg.x_sigma = contour_point.x_sigma;
      contour_point_msg.y_sigma = contour_point.y_sigma;
      object_msg.tracked_properties.contour_point_list.push_back(contour_point_msg);
    }

    new_msg.object_list.push_back(object_msg);
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2280(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::ObjectData2280& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<ObjectData2280>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);
  new_msg.mid_scan_timestamp = ntp_to_ros_time(dc_parser->mid_scan_timestamp);

  for (auto object : dc_parser->object_list)
  {
    ibeo_msgs::Object2280 object_msg;

    object_msg.object_id = object.id;

    if( object.tracking_model == DYNAMIC )
    {
      object_msg.tracking_model = object_msg.DYNAMIC_MODEL;
    } 
    else
    {
      object_msg.tracking_model = object_msg.STATIC_MODEL;
    } 

    object_msg.mobility_of_dyn_object_detected = object.mobility_of_dyn_object_detected;
    object_msg.motion_model_validated = object.motion_model_validated;
    object_msg.object_age = object.object_age;
    object_msg.timestamp = ntp_to_ros_time(object.timestamp);
    object_msg.object_prediction_age = object.object_prediction_age;
   
    switch( object.classification )
    {
      case UNCLASSIFIED:
        object_msg.classification = object_msg.UNCLASSIFIED;
      break;
      case UNKNOWN_SMALL:
        object_msg.classification = object_msg.UNKNOWN_SMALL;
      break;
      case UNKNOWN_BIG:
        object_msg.classification = object_msg.UNKNOWN_BIG;
      break;
      case PEDESTRIAN:
        object_msg.classification = object_msg.PEDESTRIAN;
      break;
      case BIKE:
        object_msg.classification = object_msg.BIKE;
      break;
      case CAR:
        object_msg.classification = object_msg.CAR;
      break;
      case TRUCK:
        object_msg.classification = object_msg.TRUCK;
      break;
    }

    object_msg.classification_certainty = object.classification_certainty;
    object_msg.classification_age = object.classification_age;

    object_msg.object_box_center.x = object.object_box_center.x;
    object_msg.object_box_center.y = object.object_box_center.y;

    object_msg.object_box_center_sigma.x = object.object_box_center_sigma.x;
    object_msg.object_box_center_sigma.y = object.object_box_center_sigma.y;

    object_msg.object_box_size.x = object.object_box_size.x;
    object_msg.object_box_size.y = object.object_box_size.y;

    object_msg.object_box_orientation_angle = object.object_box_orientation_angle;
    object_msg.object_box_orientation_angle_sigma = object.object_box_orientation_angle_sigma;
    
    object_msg.relative_velocity.x = object.relative_velocity.x;
    object_msg.relative_velocity.y = object.relative_velocity.y;
    
    object_msg.relative_velocity_sigma.x = object.relative_velocity_sigma.x;
    object_msg.relative_velocity_sigma.y = object.relative_velocity_sigma.y;
    
    object_msg.absolute_velocity.x = object.absolute_velocity.x;
    object_msg.absolute_velocity.y = object.absolute_velocity.y;
    
    object_msg.absolute_velocity_sigma.x = object.absolute_velocity_sigma.x;
    object_msg.absolute_velocity_sigma.y = object.absolute_velocity_sigma.y;
    
    object_msg.closest_point_index = object.closest_point_index;

    object_msg.reference_point_location = (uint16_t) object.reference_point_location;
    switch(object.reference_point_location)
    {
      case COG:
        object_msg.reference_point_location = object_msg.CENTER_OF_GRAVITY;
      break;
      case TOP_FRONT_LEFT_CORNER:
        object_msg.reference_point_location = object_msg.FRONT_LEFT;
      break;
      case TOP_FRONT_RIGHT_CORNER:
        object_msg.reference_point_location = object_msg.FRONT_RIGHT;
      break;
      case BOTTOM_REAR_RIGHT_CORNER:
        object_msg.reference_point_location = object_msg.REAR_RIGHT;
      break;
      case BOTTOM_REAR_LEFT_CORNER:
        object_msg.reference_point_location = object_msg.REAR_LEFT;
      break;
      case CENTER_OF_TOP_FRONT_EDGE:
        object_msg.reference_point_location = object_msg.FRONT_CENTER;
      break;
      case CENTER_OF_RIGHT_EDGE:
        object_msg.reference_point_location = object_msg.RIGHT_CENTER;
      break;
      case CENTER_OF_BOTTOM_REAR_EDGE:
        object_msg.reference_point_location = object_msg.REAR_CENTER;
      break;
      case CENTER_OF_LEFT_EDGE:
        object_msg.reference_point_location = object_msg.LEFT_CENTER;
      break;
      case BOX_CENTER:
        object_msg.reference_point_location = object_msg.OBJECT_CENTER;
      break;
      case INVALID:
        object_msg.reference_point_location = object_msg.UNKNOWN;
      break;
    }

    object_msg.reference_point_coordinate.x = object.reference_point_coordinate.x;
    object_msg.reference_point_coordinate.y = object.reference_point_coordinate.y;

    object_msg.reference_point_coordinate_sigma.x = object.reference_point_coordinate_sigma.x;
    object_msg.reference_point_coordinate_sigma.y = object.reference_point_coordinate_sigma.y;

    object_msg.object_priority = object.object_priority;
    object_msg.reference_point_position_correction_coefficient = object.reference_point_position_correction_coefficient;
    object_msg.object_priority = object.object_priority;
    object_msg.object_existence_measurement = object.object_existence_measurement;

    object_msg.absolute_velocity.x = object.absolute_velocity.x;
    object_msg.absolute_velocity.y = object.absolute_velocity.y;
    // object.number_of_contour_points;
    int i = 0;
    for (auto contour_point : object.contour_point_list)
    {
      ibeo_msgs::Point2DFloat msg_cp;
      msg_cp.x = contour_point.x;
      msg_cp.y = contour_point.y;

      object_msg.contour_point_list.push_back(msg_cp);
      i++;
    }

    new_msg.objects.push_back(object_msg);

  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2403(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::CameraImage& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<CameraImage>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  switch(dc_parser->image_format)
  {
    case JPEG:
      new_msg.image_format = new_msg.JPEG;
      break;
    case MJPEG:
      new_msg.image_format = new_msg.MJPEG;
      break;
    case GRAY8:
      new_msg.image_format = new_msg.GRAY8;
      break;
    case YUV420:
      new_msg.image_format = new_msg.YUV420;
      break;
    case YUV422:
      new_msg.image_format = new_msg.YUV422;
      break;

  }

  new_msg.us_since_power_on = dc_parser->us_since_power_on;
  new_msg.timestamp = ntp_to_ros_time(dc_parser->timestamp);
  new_msg.device_id = dc_parser->device_id;
  
  new_msg.mounting_position.yaw_angle = dc_parser->mounting_position.yaw_angle;
  new_msg.mounting_position.pitch_angle = dc_parser->mounting_position.pitch_angle;
  new_msg.mounting_position.roll_angle = dc_parser->mounting_position.roll_angle;
  new_msg.mounting_position.x_position = dc_parser->mounting_position.x_position;
  new_msg.mounting_position.y_position = dc_parser->mounting_position.y_position;
  new_msg.mounting_position.z_position = dc_parser->mounting_position.z_position;
  
  new_msg.horizontal_opening_angle = dc_parser->horizontal_opening_angle;
  new_msg.vertical_opening_angle = dc_parser->vertical_opening_angle;
  new_msg.image_width = dc_parser->image_width;
  new_msg.image_height = dc_parser->image_height;
  new_msg.compressed_size = dc_parser->compressed_size;

  for( int i = 0; i < dc_parser->image_width * dc_parser->image_height; i++)
  {
    new_msg.image_buffer[i] = dc_parser->image_buffer[i];
  }

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2805(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::HostVehicleState2805& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<HostVehicleState2805>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.timestamp = ntp_to_ros_time(dc_parser->timestamp);
  new_msg.scan_number = dc_parser->scan_number;
  new_msg.error_flags = dc_parser->error_flags;
  new_msg.longitudinal_velocity = dc_parser->longitudinal_velocity;
  new_msg.steering_wheel_angle = dc_parser->steering_wheel_angle;
  new_msg.front_wheel_angle = dc_parser->front_wheel_angle;
  new_msg.x_position = dc_parser->x_position;
  new_msg.y_position = dc_parser->y_position;
  new_msg.course_angle = dc_parser->course_angle;
  new_msg.time_difference = dc_parser->time_difference;
  new_msg.x_difference = dc_parser->x_difference;
  new_msg.y_difference = dc_parser->y_difference;
  new_msg.heading_difference = dc_parser->heading_difference;
  new_msg.current_yaw_rate = dc_parser->current_yaw_rate;

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2806(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::HostVehicleState2806& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<HostVehicleState2806>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.stamp = ntp_to_ros_time(dc_parser->timestamp);

  new_msg.distance_x = dc_parser->distance_x;
  new_msg.distance_y = dc_parser->distance_y;
  new_msg.course_angle = dc_parser->course_angle;
  new_msg.longitudinal_velocity = dc_parser->longitudinal_velocity;
  new_msg.yaw_rate = dc_parser->yaw_rate;
  new_msg.steering_wheel_angle = dc_parser->steering_wheel_angle;
  new_msg.cross_acceleration = dc_parser->cross_acceleration;
  new_msg.front_wheel_angle = dc_parser->front_wheel_angle;
  new_msg.vehicle_width = dc_parser->vehicle_width;
  new_msg.vehicle_front_to_front_axle = dc_parser->vehicle_front_to_front_axle;
  new_msg.rear_axle_to_front_axle = dc_parser->rear_axle_to_front_axle;
  new_msg.rear_axle_to_vehicle_rear = dc_parser->rear_axle_to_vehicle_rear;
  new_msg.steer_ratio_poly_0 = dc_parser->steer_ratio_poly_0;
  new_msg.steer_ratio_poly_1 = dc_parser->steer_ratio_poly_1;
  new_msg.steer_ratio_poly_2 = dc_parser->steer_ratio_poly_2;
  new_msg.steer_ratio_poly_3 = dc_parser->steer_ratio_poly_3;

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill2807(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::HostVehicleState2807& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<HostVehicleState2807>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.stamp = ntp_to_ros_time(dc_parser->timestamp);

  new_msg.distance_x = dc_parser->distance_x;
  new_msg.distance_y = dc_parser->distance_y;
  new_msg.course_angle = dc_parser->course_angle;
  new_msg.longitudinal_velocity = dc_parser->longitudinal_velocity;
  new_msg.yaw_rate = dc_parser->yaw_rate;
  new_msg.steering_wheel_angle = dc_parser->steering_wheel_angle;
  new_msg.cross_acceleration = dc_parser->cross_acceleration;
  new_msg.front_wheel_angle = dc_parser->front_wheel_angle;
  new_msg.vehicle_width = dc_parser->vehicle_width;
  new_msg.vehicle_front_to_front_axle = dc_parser->vehicle_front_to_front_axle;
  new_msg.rear_axle_to_front_axle = dc_parser->rear_axle_to_front_axle;
  new_msg.rear_axle_to_vehicle_rear = dc_parser->rear_axle_to_vehicle_rear;
  new_msg.steer_ratio_poly_0 = dc_parser->steer_ratio_poly_0;
  new_msg.steer_ratio_poly_1 = dc_parser->steer_ratio_poly_1;
  new_msg.steer_ratio_poly_2 = dc_parser->steer_ratio_poly_2;
  new_msg.steer_ratio_poly_3 = dc_parser->steer_ratio_poly_3;
  new_msg.longitudinal_acceleration = dc_parser->longitudinal_acceleration;

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fill6301(std::shared_ptr<IbeoTxMessage>& parser_class, ibeo_msgs::DeviceStatus& new_msg)
{
  auto dc_parser = std::dynamic_pointer_cast<DeviceStatus>(parser_class);

  fillIbeoHeader(dc_parser->ibeo_header, new_msg.ibeo_header);

  new_msg.scanner_type = dc_parser->scanner_type;
  new_msg.sensor_temperature = dc_parser->sensor_temperature;
  new_msg.frequency = dc_parser->frequency;

  new_msg.header.frame_id = frame_id;
  new_msg.header.stamp = ros::Time::now();
}

void IbeoScalaRosMsgHandler::fillPointcloud(std::vector<Point3D>& points, pcl::PointCloud<pcl::PointXYZ>& new_msg)
{
  for( Point3D p : points )
  {
    pcl::PointXYZ pclp;
    pclp.x = p.x;
    pclp.y = p.y;
    pclp.z = p.z;
    new_msg.push_back(pclp);
  }
}

void IbeoScalaRosMsgHandler::fillContourPoints(std::vector<Point3D>& points, visualization_msgs::Marker& new_msg)
{
  int j = 0;

  new_msg.ns = "scala";
  new_msg.type = visualization_msgs::Marker::POINTS;
  new_msg.color.r = 0.0;
  new_msg.color.g = 1.0;
  new_msg.color.b = 0.0;
  new_msg.color.a = 1.0;
  new_msg.scale.x = 0.05;
  new_msg.scale.y = 0.05;
  new_msg.scale.z = 0.05;

  for(Point3D p : points)
  {
    geometry_msgs::Point point;
    point.x = p.x;
    point.y = p.y;
    point.z = p.z;
    new_msg.points.push_back(point);
  }
}

void IbeoScalaRosMsgHandler::fillMarkerArray(std::vector<IbeoObject>& objects, visualization_msgs::MarkerArray& new_msg)
{
  for( IbeoObject o : objects )
  {
    tf::Quaternion quaternion = tf::createQuaternionFromYaw(o.object_box_orientation * 100/180 * M_PI);
    visualization_msgs::Marker object_marker = createWireframeMarker(o.object_box_center.x,
                                                                     o.object_box_center.y,
                                                                     o.object_box_size.size_x,
                                                                     o.object_box_size.size_y,
                                                                     0.75);
    object_marker.id  = o.id;
    object_marker.pose.orientation.x = quaternion.x();
    object_marker.pose.orientation.y = quaternion.y();
    object_marker.pose.orientation.z = quaternion.z();
    object_marker.pose.orientation.w = quaternion.w();
    object_marker.lifetime = ros::Duration(5);
    object_marker.color.a = 0.5;
    object_marker.color.r = object_marker.color.g = object_marker.color.b = 1.0;
    object_marker.frame_locked = false;

    std::string label;
    switch (o.classification)
    {
      case UNCLASSIFIED:
        label = "Unclassified";
        // Unclassified - white
        break;
      case UNKNOWN_SMALL:
        label = "Unknown Small";
        // Unknown small - blue
        object_marker.color.r = object_marker.color.g = 0;
        break;
      case UNKNOWN_BIG:
        label = "Unknown Big";
        // Unknown big - dark blue
        object_marker.color.r = object_marker.color.g = 0;
        object_marker.color.b = 0.5;
        break;
      case PEDESTRIAN:
        label = "Pedestrian";
        // Pedestrian - red
        object_marker.color.g = object_marker.color.b = 0;
        break;
      case BIKE:
        label = "Bike";
        // Bike - dark red
        object_marker.color.g = object_marker.color.b = 0;
        object_marker.color.r = 0.5;
        break;
      case CAR:
        label = "Car";
        // Car - green
        object_marker.color.b = object_marker.color.r = 0;
        break;
      case TRUCK:
        label = "Truck";
        // Truck - dark green
        object_marker.color.b = object_marker.color.r = 0;
        object_marker.color.g = 0.5;
        break;
      default:
        label = "Unknown";
        object_marker.color.r = object_marker.color.b = object_marker.color.g = 0.0;
        break;
    }

    object_marker.ns = label;
    object_marker.type = visualization_msgs::Marker::CUBE;
    object_marker.action = visualization_msgs::Marker::ADD;
    object_marker.header.stamp = ros::Time::now();
    object_marker.header.frame_id = frame_id;
    object_marker.scale.x = 0.1;
    object_marker.scale.y = 0.1;
    object_marker.scale.z = 0.1;
    
    visualization_msgs::Marker   object_label;
    object_label.id  = o.id + 1000;
    object_label.ns = label;
    object_label.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    object_label.action = visualization_msgs::Marker::ADD;
    object_label.pose.position.x = o.object_box_center.x;
    object_label.pose.position.y = o.object_box_center.y;
    object_label.pose.position.z = 0.5;
    object_label.text = label;
    object_label.scale.x = 0.1;
    object_label.scale.y = 0.1;
    object_label.scale.z = 0.5;
    object_label.lifetime = object_marker.lifetime;
    object_label.color.r = object_label.color.g = object_label.color.b = 1;
    object_label.color.a = 0.5;
    object_label.action = visualization_msgs::Marker::ADD;
    object_label.header.stamp = ros::Time::now();
    object_label.header.frame_id = frame_id;

    visualization_msgs::Marker object_point_marker;
    object_point_marker.type = visualization_msgs::Marker::POINTS;
    object_point_marker.ns = label;
    object_point_marker.lifetime = object_marker.lifetime;
    object_point_marker.scale.x = 0.05;
    object_point_marker.scale.y = 0.05;
    object_point_marker.scale.z = 0.05;
    object_point_marker.color.r = 0;
    object_point_marker.color.g = 1;
    object_point_marker.color.b = 0;
    object_point_marker.color.a = 0.7;
    object_point_marker.header.stamp = ros::Time::now();
    object_point_marker.header.frame_id = frame_id;

    new_msg.markers.push_back(object_marker);
    new_msg.markers.push_back(object_label);
    new_msg.markers.push_back(object_point_marker);
  }
}

visualization_msgs::Marker IbeoScalaRosMsgHandler::createWireframeMarker(const float& center_x,
                                                                         const float& center_y,
                                                                         float size_x,
                                                                         float size_y,
                                                                         const float& size_z)
{
  visualization_msgs::Marker box;
  box.type = visualization_msgs::Marker::LINE_LIST;
  box.action = visualization_msgs::Marker::ADD;
  box.pose.position.x = center_x;
  box.pose.position.y = center_y;
  box.scale.x = 0.05;
  geometry_msgs::Point p1, p2, p3, p4, p5, p6, p7, p8;

  size_y = (size_y <= 0.1f) ? 0.1f : size_y;
  size_x = (size_x <= 0.1f) ? 0.1f : size_x;

  float half_x = (0.5) * size_x;
  float half_y = (0.5) * size_y;

  p1.x = half_x;
  p1.y = half_y;
  p1.z = size_z;
  p2.x = half_x;
  p2.y = -half_y;
  p2.z = size_z;
  p3.x = -half_x;
  p3.y = -half_y;
  p3.z = size_z;
  p4.x = -half_x;
  p4.y = half_y;
  p4.z = size_z;
  p5 = p1;
  p5.z = -size_z;
  p6 = p2;
  p6.z = -size_z;
  p7 = p3;
  p7.z = -size_z;
  p8 = p4;
  p8.z = -size_z;

  box.points.reserve(24);
  
  box.points.push_back(p1);
  box.points.push_back(p2);

  box.points.push_back(p2);
  box.points.push_back(p3);

  box.points.push_back(p3);
  box.points.push_back(p4);

  box.points.push_back(p4);
  box.points.push_back(p1);

  box.points.push_back(p1);
  box.points.push_back(p5);

  box.points.push_back(p2);
  box.points.push_back(p6);

  box.points.push_back(p3);
  box.points.push_back(p7);

  box.points.push_back(p4);
  box.points.push_back(p8);

  box.points.push_back(p5);
  box.points.push_back(p6);

  box.points.push_back(p6);
  box.points.push_back(p7);

  box.points.push_back(p7);
  box.points.push_back(p8);

  box.points.push_back(p8);
  box.points.push_back(p5);

  return box;
}
