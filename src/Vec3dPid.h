#pragma once


class Vec3dPid {
	osg::Vec3d pid;
	osg::Vec3d minValue;
	osg::Vec3d maxValue;
	osg::Vec3d preError;
	osg::Vec3d integral;
public:
	void setPid(const osg::Vec3d& value) {
		pid = value;
	}

	const osg::Vec3d& getPid() const{
		return pid;
	}

	const osg::Vec3d getPreError() const {
		return preError;
	}

	void setMinValue(const osg::Vec3d& value) {
		minValue = value;
	}

	void setMaxValue(const osg::Vec3d& value) {
		maxValue = value;
	}
	Vec3dPid(osg::Vec3d pid, osg::Vec3d minValue, osg::Vec3d maxValue)
	: pid(pid), minValue(minValue), maxValue(maxValue){
		
	}
	Vec3dPid(osg::Vec3d pid)
		: pid(pid) {

	}
	Vec3dPid(const osg::Vec3d& pid, const osg::Vec3d& limits)
		: pid(pid), minValue(-limits), maxValue(limits) {

	}
	osg::Vec3d calculate(osg::Vec3d setpoint, osg::Vec3d pv, double dt)
	{
		// Calculate error
		auto error = setpoint - pv;

		// Proportional term
		auto pOut = error * pid[0];

		// Integral term
		integral += error * dt;
		auto iOut = integral * pid[1];

		// Derivative term
		auto derivative = (error - preError) / dt;
		auto dOut = derivative * pid[2];

		// Calculate total output
		auto output = pOut + iOut + dOut;

		// Restrict to max/min
		//osg::clampTo(output.x() ,minValue.x(), maxValue.x());
		//osg::clampTo(output.y(), minValue.y(), maxValue.y());
		//osg::clampTo(output.z(), minValue.z(), maxValue.z());
	
		// Save error to previous error
		preError = error;

		return output;
	}

};