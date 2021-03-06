require File.dirname(__FILE__) + '/cmake.rb'
require File.dirname(__FILE__) + '/git.rb'

module Mmdai

class Nvfx < Thor
  include Build::CMake
  include VCS::Git

  desc "build", "build nvFX"
  method_options :flag => :boolean
  def build
    checkout
    invoke_build
  end

  desc "clean", "delete built nvFX libraries"
  def clean
    invoke_clean
  end

protected
  def get_uri
    "https://github.com/hkrn/nvFX"
  end

  def get_directory_name
    "nvFX-src"
  end

  def get_tag_name
    "master"
  end

  def get_build_options(build_type, extra_options)
    glew_location = "#{get_base_path}/libvpvl2/vendor/nvFX"
    build_options = {
      :build_samples => false,
      :glew_include_dir => glew_location,
      :glew_source => "#{glew_location}/nvfx_glew_mock.cc",
      :use_cuda => false,
      :use_optix => false,
      :use_opengl => true,
      :use_svcui => false,
      :use_glut => false
    }
    build_options
  end

end

end

