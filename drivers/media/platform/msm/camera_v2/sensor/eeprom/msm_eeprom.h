/* Copyright (c) 2011-2015, 2018, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef MSM_EEPROM_H
#define MSM_EEPROM_H

#include <linux/i2c.h>
#include <linux/gpio.h>
#include <soc/qcom/camera2.h>
#include <media/v4l2-subdev.h>
#include <media/msmb_camera.h>
#include "msm_camera_i2c.h"
#include "msm_camera_spi.h"
#include "msm_camera_io_util.h"
#include "msm_camera_dt_util.h"

struct msm_eeprom_ctrl_t;

#define DEFINE_MSM_MUTEX(mutexname) \
	static struct mutex mutexname = __MUTEX_INITIALIZER(mutexname)

#define PROPERTY_MAXSIZE 32

struct msm_eeprom_ctrl_t {
	struct platform_device *pdev;
	struct mutex *eeprom_mutex;

	struct v4l2_subdev sdev;
	struct v4l2_subdev_ops *eeprom_v4l2_subdev_ops;
	enum msm_camera_device_type_t eeprom_device_type;
	struct msm_sd_subdev msm_sd;
	enum cci_i2c_master_t cci_master;
	enum i2c_freq_mode_t i2c_freq_mode;

	struct msm_camera_i2c_client i2c_client;
	struct msm_eeprom_board_info *eboard_info;
	uint32_t subdev_id;
	int32_t userspace_probe;
	struct msm_eeprom_memory_block_t cal_data;
	uint8_t is_supported;
#ifdef CONFIG_VENDOR_EDIT
	/*from dts*/
	int32_t position;
	/*for proc file*/
	uint16_t module_info;
	uint16_t vcm_info;
	uint16_t date_info;
	uint16_t lens_id;
	uint16_t vcm_id;
	char sensor_info[20];
	bool mprobe;
#endif
};

#ifdef CONFIG_VENDOR_EDIT
	struct vcm_id_info {
		uint16_t  vcm_id;
		uint16_t  actuator_id;  //we conver vcmid to actuator id
		char  alps_name[20];
	};
	struct lens_id_info {
		uint16_t  lens_id;
		uint16_t  user_lens_id;  //we conver lens_id to user lens id
		char  lens_info[20];
	};
	struct sensor_string_info {
		uint16_t value;
		char string[20];
	};
#endif

#endif
