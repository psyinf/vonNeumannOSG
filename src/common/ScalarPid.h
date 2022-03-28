#pragma once
#include <osg/Vec3d>

#include <MathHelpers.h>
#include <numbers>

class ScalarPid
{
private:
    osg::Vec3d pid;
    double     minValue = std::numeric_limits<double>::lowest();
    double     maxValue = std::numeric_limits<double>::max();
    double     preError;
    double     integralError;

    bool reset   = true;
    bool angular = false;

public:
    void setPid(const osg::Vec3d& value)
    {
        pid = value;
    }

    const osg::Vec3d& getPid() const
    {
        return pid;
    }

    const double& getPreError() const
    {
        return preError;
    }

    void setMinValue(double value)
    {
        minValue = value;
    }

    void setMaxValue(double value)
    {
        maxValue = value;
    }

    void setAngluar(bool val)
    {
        angular = val;
    }
    ScalarPid(osg::Vec3d pid, double minValue, double maxValue)
        : pid(pid)
        , minValue(minValue)
        , maxValue(maxValue)
    {
    }

    ScalarPid(const osg::Vec3d& pid, const double& limits)
        : pid(pid)
        , minValue(-limits)
        , maxValue(limits)
    {
    }

    double calculate(double setPoint, double currentValue, double dt)
    {
        if (dt <= 0.0)
        {
            return currentValue;
        }
        auto error = currentValue - setPoint;

        if (angular)
        {
            auto flipOverPos = [](auto error) { return (error > std::numbers::pi) ? error - 2.0 * std::numbers::pi : error; };
            auto flipOverNeg = [](auto error) { return (error < std::numbers::pi) ? error + 2.0 * std::numbers::pi : error; };
            error            = flipOverPos(error);
            error            = flipOverNeg(error);
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

        output = osg::clampTo(output, dt * minValue, dt * maxValue);


        return output;
    }
};
