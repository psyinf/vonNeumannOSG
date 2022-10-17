from conans import ConanFile
from conan.tools.cmake import CMake

class vonNeumann(ConanFile):
    name = "vonNeumann"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = [("openscenegraph/3.6.5")
				,("nlohmann_json/3.11.2")
				,("cppkafka/0.4.0")
				,("kangaru/4.2.4")
				,("freetype/2.12.1")
				,("zlib/1.2.12")
				,("glog/0.6.0")
                ,("gtest/1.12.1")
                ,("qt/5.15.6")
                ,("double-conversion/3.2.1")
                ,("yaml-cpp/0.7.0")
                ,("magic_enum/0.8.1")
                ]
    generators = "cmake_find_package_multi"
    
    def configure(self):
        self.options['openscenegraph'].shared = True
        self.options['glog'].shared = True
        self.options['qt'].shared = True
        self.options['qt'].multiconfiguration = False
        
    def imports(self):    
        self.copy("*.dll", "bin", "bin")
        