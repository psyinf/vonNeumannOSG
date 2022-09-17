#include <osg/Group>
#include <osg/Notify>
#include <osgDB/FileNameUtils>
#include <osgDB/ReadFile>
#include <osgDB/Registry>

#include <iostream>
#include <sstream>

class GizmoReader : public osgDB::ReaderWriter
{
public:
    GizmoReader()
    {
        supportsExtension("gizmo", "Gizmo Pseudo loader");
    }

    const char* className() const override { return "Gizmo Pseudo Loader"; }

    bool acceptsExtension(const std::string& extension) const override
    {
        return osgDB::equalCaseInsensitive(extension, "gizmo");
    }

    ReadResult readObject(const std::string& fileName, const Options* opt) const override
    {
        return readNode(fileName, opt);
    }

    ReadResult readNode(const std::string& fileName, const Options* options) const override
    {
        std::string ext = osgDB::getFileExtension(fileName);
        if (!acceptsExtension(ext))
            return ReadResult::FILE_NOT_HANDLED;

        if ("line" == osgDB::getNameLessExtension(fileName))
        {
            osg::ref_ptr<osg::Geode> g      = new osg::Geode;
            std::vector<osg::Vec3d> points = {{0.0, 0.0, 0.0}, {0.0, 0.0, 55.0}};
            std::vector<osg::Vec4d> colors = {{1.0, 1.0, 1.0, 1.0}};

            osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
            geom->setUseVertexBufferObjects(true);
            
            geom->setVertexArray(new osg::Vec3Array(points.begin(), points.end()));
            geom->setColorArray(new osg::Vec4Array(colors.begin(), colors.end()), osg::Array::BIND_OVERALL);

            geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, points.size()));
           
            g->addDrawable(geom);
            g->setName("Kartof´fel");
            return g;
        }

        if ("cross" == osgDB::getNameLessExtension(fileName))
        {
            std::cout << "gizmo cross" << std::endl;
            std::vector<osg::Vec3d> points = {{0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}};

            osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
            geom->setVertexArray(new osg::Vec3Array(points.begin(), points.end()));
            geom->setColorArray(new osg::Vec3Array(points.begin(), points.end()), osg::Array::BIND_PER_VERTEX);

            geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, points.size()));

            return geom.get();
        }
        return nullptr;
    }

private:
    void usage() const
    {
        OSG_INFO << "Normals Plugin usage:  <application> [-O options] <model.ext>.normals\n"
                    "     options: \"scale=<scale>\"                        (default = 1.0)\n"
                    "              \"mode=<VertexNormals|SurfaceNormals>\"  (default = VertexNormals)"
                 << std::endl;
    }
};


REGISTER_OSGPLUGIN(gizmo, GizmoReader)
