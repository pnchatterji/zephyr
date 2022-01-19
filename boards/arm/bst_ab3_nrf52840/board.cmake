# BST-AB3-NRF52840 board configuration

# Copyright (c) 2022 Bosch Sensortec GmbH
# SPDX-License-Identifier: Apache-2.0

board_runner_args(dfu-util "--pid=108c:ab3d" "--alt=0" "--dfuse")

include(${ZEPHYR_BASE}/boards/common/dfu-util.board.cmake)
include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)