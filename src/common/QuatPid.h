#pragma once
#include <osg/Math>
#include <osg/Vec3d>

#include <MathHelpers.h>
#include <OsgMathExtensions.h>
#include <numbers>

class QuatPid
{
private:
    osg::Vec3d pid;

    osg::Quat preError;
    osg::Quat integralError;

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

    const auto getPreError() const
    {
        return preError;
    }

    void setAngluar(bool val)
    {
        angular = val;
    }
    QuatPid(osg::Vec3d pid, osg::Vec3d minValue, osg::Vec3d maxValue)
        : pid(pid)
    {
    }

    QuatPid(const osg::Vec3d& pid, const osg::Vec3d& limits)
        : pid(pid)
    {
    }

    osg::Quat rotOptimize(osg::Quat q)
    {
        if (q.w() < 0.0f)
        {
            q.x() *= -1.0f;
            q.y() *= -1.0f;
            q.z() *= -1.0f;
            q.w() *= -1.0f;
        }

        return q;
    }

    osg::Quat calculate(const osg::Quat& setPoint, const osg::Quat& currentValue, double dt)
    {
        if (dt <= 0.0)
        {
            return currentValue;
        }
        auto error =
            rotOptimize(currentValue * (setPoint.inverse()));


        integralError              = (reset) ? error : integralError;
        preError                   = (reset) ? error : preError;
        integralError              = integralError * (1.0 - dt) + error * dt;
        const auto derivativeError = (error - preError) / dt;
        preError                   = error;
        reset                      = false;

        osg::Quat output;

        output.slerp(pid[0] * dt, osg::Quat(), error);


        // std::cout << std::setprecision(2) << " --- " << output << std::endl;
        //+ integralError * -pid[1]
        //+ derivativeError * -pid[2];

        // std::cout << output << std::endl;
        //  osg::clampBetween(output * dt, 0.0, dt);
        //  osg::Quat ret = currentValue;
        //  ret.slerp(output, currentValue, setPoint);
        return output;
    }
};
