#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint native_add.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'native_add'
  s.version          = '0.0.1'
  s.summary          = 'A new Flutter FFI plugin project.'
  s.description      = <<-DESC
A new Flutter FFI plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }

  # This will ensure the source files in Classes/ are included in the native
  # builds of apps using this FFI plugin. Podspec does not support relative
  # paths, so Classes contains a forwarder C file that relatively imports
  # `../src/*` so that the C sources can be shared among all target platforms.
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.dependency 'Flutter'
  s.platform = :ios, '11.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'

# telling CocoaPods not to remove framework
 s.preserve_paths = ‘opencv2.framework’
 # telling linker to include opencv2 framework
 s.xcconfig = { ‘OTHER_LDFLAGS’ => ‘-framework opencv2’ }
 # including OpenCV framework
 s.vendored_frameworks = ‘opencv2.framework’
 # including native framework
 s.frameworks = ‘AVFoundation’
 # including C++ library
 s.library = ‘c++’
end
