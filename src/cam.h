// Copyright (C) CamControl Daniel C
#ifndef CMCTRL_H
#define CMCTRL_H

struct CamState {
	int device_type;

	int iso;
	int aperture;
	int white_balance;
	int format;
	int shutter_speed;
};

extern struct CamState cam;

#endif
