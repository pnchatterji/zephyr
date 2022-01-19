/*
 * Copyright (c) 2022 Bosch Sensortec GmbH.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/gpio.h>

#define PWR_CTRL_VDD_SEL	27 	/* P0.27 When LOW, 1.8V is routed to VDD and 2.8V when high*/
#define PWR_CTRL_VDD_EN		3 	/* P0.03 Routes selected VDD Voltage to shuttle VDD pin when HIGH and routes GND when low*/
#define PWR_CTRL_VDDIO_EN	28 	/* P0.28 Routes 1.8V to shuttle VDDIO pin when HIGH and routes GND when low*/

/*configuation flag to select 1.8V or 2.8 V for shuttle board VDD*/
#ifdef CONFIG_BST_AB3_NRF52840_SELECT_VDD_2_8
	#define PWR_CTRL_VDD_SEL_1_8 0
#else
	#define PWR_CTRL_VDD_SEL_1_8 1
#endif

static int board_bst_ab3_nrf52840_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	/* The discrete power management system of the Application Board 3.0 allows 
	 * to configure the voltage supplied to the sensor with the help of GPIOs.
	 * The GPIOs need to be configured before the initialization of the sensor 
	 * drivers during the kernel boot, so that the sensors are powered on 
	 * during the sensor initialization.
	 */


	int ret;
	const struct device *vdd_port;

	vdd_port = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0)));

	if (!vdd_port) {
		return -ENODEV;
	}
	ret = gpio_pin_configure(vdd_port, PWR_CTRL_VDD_SEL, (PWR_CTRL_VDD_SEL_1_8?GPIO_OUTPUT_LOW:GPIO_OUTPUT_HIGH));
	if (ret < 0) {
		return ret;
	}
	ret = gpio_pin_configure(vdd_port, PWR_CTRL_VDD_EN, GPIO_OUTPUT_HIGH);
	if (ret < 0) {
		return ret;
	}

	ret = gpio_pin_configure(vdd_port, PWR_CTRL_VDDIO_EN, GPIO_OUTPUT_HIGH);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

SYS_INIT(board_bst_ab3_nrf52840_init, PRE_KERNEL_1,
	 CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
