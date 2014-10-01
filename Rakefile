require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/*_test.rb']
  t.verbose = true
end

task :default => [:build_ext, :test]

require 'rake/clean'
require 'fileutils'

CLEAN.include('ext/**/*{.o,.log,.so,.bundle}')
CLEAN.include('ext/**/Makefile')
CLOBBER.include('lib/*{.so,.bundle}')

desc 'Build the mtex2MML bindings'
task :build_ext do
  host_os = RbConfig::CONFIG['host_os']

  # generate Ruby file with Swig
  Dir.chdir("src/") do
    sh "make ruby"
  end

  # clear the ext dir
  Dir["ext/*"].each do |f|
    should_skip = File.basename( f ) =~ /^extconf\.rb$/
    FileUtils.rm( f ) unless should_skip
  end

  # copy over source files
  Dir.glob("src/*.{c,h}") do |file|
    FileUtils.cp(file, 'ext')
  end

  # build Ruby's Makefile and run it
  Dir.chdir("ext/") do
    ruby "extconf.rb"
    sh "make"
  end

  # move the bundle to the lib folder
  if host_os =~ /darwin|mac os/
    cp "ext/mtex2MML.bundle", "lib/"
  else
    cp "ext/mtex2MML.so", "lib/"
  end
end
