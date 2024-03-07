/*
 * Copyright 2021 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);

	//Write codes screen_gauge0
	ui->screen_gauge0 = lv_gauge_create(ui->screen, NULL);

	//Write style LV_GAUGE_PART_MAIN for screen_gauge0
	static lv_style_t style_screen_gauge0_main;
	lv_style_init(&style_screen_gauge0_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_gauge0_main
	lv_style_set_bg_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_gauge0_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_gauge0_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0x39, 0x3c, 0x41));
	lv_style_set_text_font(&style_screen_gauge0_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_gauge0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_inner(&style_screen_gauge0_main, LV_STATE_DEFAULT, 15);
	lv_style_set_line_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0x8b, 0x89, 0x8b));
	lv_style_set_line_width(&style_screen_gauge0_main, LV_STATE_DEFAULT, 3);
	lv_style_set_line_opa(&style_screen_gauge0_main, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0x8b, 0x89, 0x8b));
	lv_style_set_scale_end_color(&style_screen_gauge0_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_scale_width(&style_screen_gauge0_main, LV_STATE_DEFAULT, 9);
	lv_style_set_scale_border_width(&style_screen_gauge0_main, LV_STATE_DEFAULT, 0);
	lv_style_set_scale_end_border_width(&style_screen_gauge0_main, LV_STATE_DEFAULT, 5);
	lv_style_set_scale_end_line_width(&style_screen_gauge0_main, LV_STATE_DEFAULT, 4);
	lv_obj_add_style(ui->screen_gauge0, LV_GAUGE_PART_MAIN, &style_screen_gauge0_main);

	//Write style LV_GAUGE_PART_MAJOR for screen_gauge0
	static lv_style_t style_screen_gauge0_major;
	lv_style_init(&style_screen_gauge0_major);

	//Write style state: LV_STATE_DEFAULT for style_screen_gauge0_major
	lv_style_set_line_color(&style_screen_gauge0_major, LV_STATE_DEFAULT, lv_color_make(0x8b, 0x89, 0x8b));
	lv_style_set_line_width(&style_screen_gauge0_major, LV_STATE_DEFAULT, 5);
	lv_style_set_line_opa(&style_screen_gauge0_major, LV_STATE_DEFAULT, 255);
	lv_style_set_scale_grad_color(&style_screen_gauge0_major, LV_STATE_DEFAULT, lv_color_make(0x8b, 0x89, 0x8b));
	lv_style_set_scale_end_color(&style_screen_gauge0_major, LV_STATE_DEFAULT, lv_color_make(0x00, 0xa1, 0xb5));
	lv_style_set_scale_width(&style_screen_gauge0_major, LV_STATE_DEFAULT, 16);
	lv_style_set_scale_end_line_width(&style_screen_gauge0_major, LV_STATE_DEFAULT, 5);
	lv_obj_add_style(ui->screen_gauge0, LV_GAUGE_PART_MAJOR, &style_screen_gauge0_major);

	//Write style LV_GAUGE_PART_NEEDLE for screen_gauge0
	static lv_style_t style_screen_gauge0_needle;
	lv_style_init(&style_screen_gauge0_needle);

	//Write style state: LV_STATE_DEFAULT for style_screen_gauge0_needle
	lv_style_set_size(&style_screen_gauge0_needle, LV_STATE_DEFAULT, 21);
	lv_style_set_bg_color(&style_screen_gauge0_needle, LV_STATE_DEFAULT, lv_color_make(0x41, 0x48, 0x5a));
	lv_style_set_bg_grad_color(&style_screen_gauge0_needle, LV_STATE_DEFAULT, lv_color_make(0x41, 0x48, 0x5a));
	lv_style_set_bg_grad_dir(&style_screen_gauge0_needle, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_gauge0_needle, LV_STATE_DEFAULT, 255);
	lv_style_set_pad_inner(&style_screen_gauge0_needle, LV_STATE_DEFAULT, 0);
	lv_style_set_line_width(&style_screen_gauge0_needle, LV_STATE_DEFAULT, 4);
	lv_style_set_line_opa(&style_screen_gauge0_needle, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_gauge0, LV_GAUGE_PART_NEEDLE, &style_screen_gauge0_needle);
	lv_obj_set_pos(ui->screen_gauge0, 23, 54);
	lv_obj_set_size(ui->screen_gauge0, 200, 200);
	lv_gauge_set_scale(ui->screen_gauge0, 300, 37, 19);
	lv_gauge_set_range(ui->screen_gauge0, 0, 180);
	static lv_color_t needle_colors_screen_gauge0[1];
	needle_colors_screen_gauge0[0] = lv_color_make(0xff, 0x00, 0x00);
	lv_gauge_set_needle_count(ui->screen_gauge0, 1, needle_colors_screen_gauge0);
	lv_gauge_set_critical_value(ui->screen_gauge0, 120);
	lv_gauge_set_value(ui->screen_gauge0, 0, 0);
}