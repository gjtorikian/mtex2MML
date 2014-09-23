$:.unshift File.expand_path( File.join( File.dirname( __FILE__ ), "../lib" ) )
require 'itextomml'
require 'minitest/autorun'

def fixture_file(name)
  File.read( File.join(File.dirname( __FILE__ ), "fixtures", "#{name}.html") ).strip
end

def write_to_test_file(converted)
  outfile = """
<html>

<body>

#{converted}

</body>

</html>
  """

  File.open("test.html", "w") { |f| f.write(outfile) }
end
