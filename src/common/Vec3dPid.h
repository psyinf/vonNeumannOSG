#pragma once
#include <osg/Vec3d>

#include <MathHelpers.h>
#include <numbers>

class Vec3dPid
{
private:
    osg::Vec3d pid;
    osg::Vec3d minValue = common::makeVec(std::numeric_limits<double>::lowest());
    osg::Vec3d maxValue = common::makeVec(std::numeric_limits<double>::max());
    osg::Vec3d preError;
    osg::Vec3d integralError;
    bool       reset   = true;
    bool       angular = false;

public:
    void setPid(const osg::Vec3d& value)
    {
        pid = value;
    }

    const osg::Vec3d& getPid() const
    {
        return pid;
    }

    const osg::Vec3d& getPreError() const
    {
        return preError;
    }

    void setMinValue(const osg::Vec3d& value)
    {
        minValue = value;
    }

    void setMaxValue(const osg::Vec3d& value)
    {
        maxValue = value;
    }

    Vec3dPid(osg::Vec3d pid, osg::Vec3d minValue, osg::Vec3d maxValue)
        : pid(pid)
        , minValue(minValue)
        , maxValue(maxValue)
    {
    }

    Vec3dPid(const osg::Vec3d& pid, const osg::Vec3d& limits)
        : pid(pid)
        , minValue(-limits)
        , maxValue(limits)
    {
    }

    osg::Vec3d calculate(const osg::Vec3d& setPoint, const osg::Vec3d& currentValue, double dt)
    {
        if (dt <= 0.0)
        {
            return currentValue;
        }
        const auto error = currentValue - setPoint;

        if (angular)
        {
            /* TODO: adapt to 3d
            error = (error < std::numbers::pi) ? error + 2.0 * std::numbers::pi : error;
            error = (error > std::numbers::pi) ? error - 2.0 * std::numbers::pi : error;
            */
        }

        integralError              = (reset) ? error : integralError;
        preError                   = (reset) ? error : preError;
        integralError              = integralError * (1.0 - dt) + error * dt;
        const auto derivativeError = (error - preError) / dt;
        preError                   = error;
        reset                      = false;

        auto output = error * -pid[0]
                    + integralError * -pid[1]
                    + derivativeError * -pid[2];

        output.x() = osg::clampTo(output.x(), dt * minValue.x(), dt * maxValue.x());
        output.y() = osg::clampTo(output.y(), dt * minValue.y(), dt * maxValue.y());
        output.z() = osg::clampTo(output.z(), dt * minValue.z(), dt * maxValue.z());

        return output;
    }
};
