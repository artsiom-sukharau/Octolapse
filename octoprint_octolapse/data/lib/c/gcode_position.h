////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Octolapse - A plugin for OctoPrint used for making stabilized timelapse videos.
// Copyright(C) 2019  Brad Hochgesang
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.If not, see the following :
// https ://github.com/FormerLurker/Octolapse/blob/master/LICENSE
//
// You can contact the author either through the git - hub repository, or at the
// following email address : FormerLurker@pm.me
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef GCODE_POSITION_H
#define GCODE_POSITION_H
#include <string>
#include <vector>
#include <map>
#include "gcode_parser.h"
#include "position.h"
#include "gcode_wiper.h"
struct gcode_position_args {
	gcode_position_args() {
		// Wipe Variables
		wipe_while_retracting = false;
		retraction_feedrate = -1;
		wipe_feedrate = -1.0;

		autodetect_position = true;
		origin_x = 0;
		origin_y = 0;
		origin_z = 0;
		origin_x_none = false;
		origin_y_none = false;
		origin_z_none = false;
		retraction_length = 0;
		retract_after_wipe_percent = 0;
		retract_before_wipe_percent = 0;
		z_lift_height = 0;
		priming_height = 0;
		minimum_layer_height = 0;
		g90_influences_extruder = false;
		xyz_axis_default_mode = "absolute";
		e_axis_default_mode = "absolute";
		units_default = "millimeters";
		is_bound_ = false;
		x_min_ = 0;
		x_max_ = 0;
		y_min_ = 0;
		y_max_ = 0;
		z_min_ = 0;
		z_max_ = 0;
		std::vector<std::string> location_detection_commands; // Final list of location detection commands
	}
	bool autodetect_position;
	// Wipe variables
	bool wipe_while_retracting;
	double retraction_feedrate;
	double wipe_feedrate;

	double origin_x;
	double origin_y;
	double origin_z;
	bool origin_x_none;
	bool origin_y_none;
	bool origin_z_none;
	double retraction_length;
	double retract_after_wipe_percent;
	double retract_before_wipe_percent;
	double z_lift_height;
	double priming_height;
	double minimum_layer_height;
	bool g90_influences_extruder;
	bool is_bound_;
	double x_min_;
	double x_max_;
	double y_min_;
	double y_max_;
	double z_min_;
	double z_max_;
	std::string xyz_axis_default_mode;
	std::string e_axis_default_mode;
	std::string units_default;
	std::vector<std::string> location_detection_commands; // Final list of location detection commands
};

class gcode_position
{
public:
	typedef void(gcode_position::*posFunctionType)(position*, parsed_command*);
	gcode_position(gcode_position_args* args);
	gcode_position();
	~gcode_position();

	void update(parsed_command* cmd, int file_line_number, int gcode_number);
	void update_position(position*, double x, bool update_x, double y, bool update_y, double z, bool update_z, double e, bool update_e, double f, bool update_f, bool force, bool is_g1);
	void undo_update();
	void get_wipe_steps(std::vector<gcode_wiper_step*> &wipe_steps);
	position * get_current_position();
	position * get_previous_position();
	bool is_wipe_enabled();
private:
	gcode_position(const gcode_position & source);
	
	position* p_previous_pos_;
	position* p_current_pos_;
	position* p_undo_pos_;
	bool autodetect_position_;
	double priming_height_;
	double origin_x_;
	double origin_y_;
	double origin_z_;
	bool origin_x_none_;
	bool origin_y_none_;
	bool origin_z_none_;
	double retraction_length_;
	double z_lift_height_;
	double minimum_layer_height_;
	bool g90_influences_extruder_;
	std::string e_axis_default_mode_;
	std::string xyz_axis_default_mode_;
	std::string units_default_;
	bool is_bound_;
	double x_min_;
	double x_max_;
	double y_min_;
	double y_max_;
	double z_min_;
	double z_max_;
	// Wipe variables
	gcode_wiper* p_wiper_;
	bool wipe_while_retracting_;

	std::map<std::string, posFunctionType> gcode_functions_;
	std::map<std::string, posFunctionType>::iterator gcode_functions_iterator_;
	
	std::map<std::string, posFunctionType> get_gcode_functions();
	/// Process Gcode Command Functions
	void process_g0_g1(position*, parsed_command*);
	void process_g2(position*, parsed_command*);
	void process_g3(position*, parsed_command*);
	void process_g10(position*, parsed_command*);
	void process_g11(position*, parsed_command*);
	void process_g20(position*, parsed_command*);
	void process_g21(position*, parsed_command*);
	void process_g28(position*, parsed_command*);
	void process_g90(position*, parsed_command*);
	void process_g91(position*, parsed_command*);
	void process_g92(position*, parsed_command*);
	void process_m82(position*, parsed_command*);
	void process_m83(position*, parsed_command*);
	void process_m207(position*, parsed_command*);
	void process_m208(position*, parsed_command*);

};

#endif