$:.unshift File.expand_path( File.join( File.dirname( __FILE__ ), "../lib" ) )
require 'itextomml'
require 'minitest/autorun'

def fixture_file(name)
  File.read( File.join(File.dirname( __FILE__ ), "fixtures", "#{name}.html") ).strip
end
