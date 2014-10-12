$:.unshift File.expand_path( File.join( File.dirname( __FILE__ ), "../lib" ) )
require 'mtextomml'
require 'minitest/autorun'

def fixture_file(dir, fixture)
  File.read( File.join(File.dirname( __FILE__ ), "fixtures", dir, "#{fixture}.html") ).strip
end

def write_to_test_file(converted)
  File.open("test.html", "w") { |f| f.write(converted) }
end

def write_to_fixture_file(dir, fixture, converted)
  File.open(File.join(File.dirname( __FILE__ ), "fixtures", dir, "#{fixture}.html"), "w") { |f| f.write(converted) }
end
