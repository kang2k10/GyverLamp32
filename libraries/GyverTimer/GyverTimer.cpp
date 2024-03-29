#include "GyverTimer.h"
#include <Arduino.h> 

// millis

GTimer_ms::GTimer_ms() {}

GTimer_ms::GTimer_ms(uint32_t interval) {
	_interval = interval;
	_timer = millis();
}

void GTimer_ms::setInterval(uint32_t interval) {
	_interval = interval;
	GTimer_ms::reset();
}
void GTimer_ms::setMode(mode mode) {
	_mode = mode;
}
void GTimer_ms::start() {
	_state = true;
}
void GTimer_ms::stop() {
	_state = false;
}
boolean GTimer_ms::isReady() {	
	if (!_state) return false;
	uint32_t thisMls = millis();
	if (thisMls - _timer >= _interval) {
		if (_mode) {
			do {
				_timer += _interval;
				if (_timer < _interval) break;          // переполнение uint32_t
			} while (_timer < thisMls - _interval);  // защита от пропуска шага			
		}
		return true;
	} else {
		return false;
	}
}

void GTimer_ms::reset() {
	_timer = millis();
}

// micros

GTimer_us::GTimer_us() {}

GTimer_us::GTimer_us(uint32_t interval) {
	_interval = interval;
	_timer = micros();
}

void GTimer_us::setInterval(uint32_t interval) {
	_interval = interval;
	_timer = micros();
}
void GTimer_us::setMode(mode mode) {
	_mode = mode;
}
void GTimer_us::start() {
	_state = true;
}
void GTimer_us::stop() {
	_state = false;
}
boolean GTimer_us::isReady() {
	if (!_state) return false;
	uint32_t thisUs = micros();
	if (thisUs - _timer >= _interval) {
		if (_mode) {
			do {
				_timer += _interval;
				if (_timer < _interval) break;          // переполнение uint32_t
			} while (_timer < thisUs - _interval);  // защита от пропуска шага			
		}
		return true;
	} else {
		return false;
	}
}

void GTimer_us::reset() {
	_timer = micros();
}