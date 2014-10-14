require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/*_test.rb']
  t.verbose = true
end

task :default => [:compile, :test]

require 'rake/clean'
require 'fileutils'

CLEAN.include('ext/**/*{.o,.log,.so,.bundle}')
CLEAN.include('ext/**/Makefile')
CLOBBER.include('lib/*{.so,.bundle}')

desc 'Build the mtex2MML bindings'
task :compile do
  def clear_ext_dir
    # clear the ext dir
    Dir["ext/*"].select { |f| File.file?(f) }.each do |f|
      should_skip = File.basename( f ) =~ /^extconf\.rb$/
      FileUtils.rm( f ) unless should_skip
    end
    Dir["ext/*"].select { |f| !File.file?(f) }.each do |f|
      FileUtils.rm_rf(f)
    end
  end

  host_os = RbConfig::CONFIG['host_os']

  # generate Ruby file with Swig
  Dir.chdir("src/") do
    sh "make ruby"
  end

  # clear the ext dir
  clear_ext_dir

  # copy over source files
  # LOL WTF I DUNNO
  Dir.glob("src/**/*.{c,h}") do |file|
    FileUtils.cp(file, 'ext')
  end
  FileUtils.cp_r 'src/deps', 'ext/deps'
  FileUtils.copy_entry 'src/deps', 'ext'

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

  # clear the ext dir, again
  clear_ext_dir
end

desc 'Convert MathJax test suite'
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
      contents = element.first.inner_html.strip
      outfile = file.sub(mathjax_test_src_dir + File::SEPARATOR, '')
      outfile_dirname = File.dirname(outfile)
      FileUtils.mkdir_p(File.join(mathjax_test_out_dir, outfile_dirname))
      FileUtils.mkdir_p(File.join(mathjax_test_tex_dir, outfile_dirname))

      if file =~ /-ref.html/
        File.write(File.join(mathjax_test_out_dir, outfile), contents)
      else
        File.write(File.join(mathjax_test_tex_dir, outfile.sub('html', 'tex')), "$$\n#{contents}\n$$")
      end
    else
      puts "#{file} did not have just one reftest-element: it had #{element.length}"
    end
    f.close
  end
end

desc 'Pretty format C code'
task :format do
  puts `astyle --indent=spaces=2 --style=1tbs --keep-one-line-blocks $(ack -f --type=cpp --type=cc src/)`
end

task :valgrind  do
  #
  # See:
  # http://blog.flavorjon.es/2009/06/easily-valgrind-gdb-your-ruby-c.html
  #
  def valgrind_errors(what)
    valgrind_cmd="valgrind --log-fd=1 --tool=memcheck --partial-loads-ok=yes --undef-value-errors=no --leak-check=full --show-leak-kinds=all ruby -Ilib:test:ext #{what}"
    puts "Executing: #{valgrind_cmd}"
    output=`#{valgrind_cmd}`
    puts output
    /ERROR SUMMARY: (\d+) ERRORS/i.match(output)[1].to_i
  end

  errors = valgrind_errors('test/mathjax_test.rb')

  if errors > 0
    abort "Memory leaks are present, please check! (#{errors} leaks!)"
  end
end

task :poor_mans_valgrind do
  for i in 1..10 do
    puts `rake test`
  end
end
