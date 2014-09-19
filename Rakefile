require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/*_test.rb']
  t.verbose = true
end

task :default => [:ch_dir, :test]

task :ch_dir do
  system "cd src && make"
end
