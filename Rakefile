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

desc 'Convert MatJax test suite'
task :convert_mathjax_tests do
  require 'nokogiri'
  mathjax_test_dir = File.join('test', 'fixtures', 'MathJax')
  mathjax_test_src_dir = File.join(mathjax_test_dir, 'LaTeXToMathML-src')
  mathjax_test_tex_dir = File.join(mathjax_test_dir, 'LaTeXToMathML-tex')
  mathjax_test_out_dir = File.join(mathjax_test_dir, 'LaTeXToMathML-out')
  Dir["#{mathjax_test_src_dir}/**/*.html"].each do |file|
    f = File.open(file)
    doc = Nokogiri::XML(f)
    element = doc.css('#reftest-element')
    if element.length == 1
      contents = element.first
      outfile = file.sub(mathjax_test_src_dir + File::SEPARATOR, '')
      outfile_dirname = File.dirname(outfile)
      FileUtils.mkdir_p(File.join(mathjax_test_out_dir, outfile_dirname))
      FileUtils.mkdir_p(File.join(mathjax_test_tex_dir, outfile_dirname))
      if file =~ /-ref.html/
        File.write(File.join(mathjax_test_out_dir, outfile), contents)
      else
        File.write(File.join(mathjax_test_tex_dir, outfile), contents)
      end
    else
      puts "#{file} did not have just one reftest-element: it had #{element.length}"
    end
    f.close
  end
end
